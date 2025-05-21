//*****************************************************************************************************************************
// Copyright (c) 2018-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*****************************************************************************************************************************

#include "flush_test.h"

namespace tests
{
    void FlushTest::Setup()
    {
        // Initialize parent class
        ChiTestCase::Setup();

        // Create mutex and condition variables
        m_pSignalMutex = Mutex::Create("m_pSignalMutex");
        m_pSignalCond = Condition::Create("m_pSignalCond");

        // Setup the long running thread in charge of triggering flush
        CDKResult result = OsUtils::ThreadCreate(WaitForFlushSignal, this, &m_flushThread);
        NT_ASSERT(CDKResultSuccess == result,"Failed to create flush thread!");
    }

    void FlushTest::Teardown()
    {
        // Shut down flushing thread
        SignalFlushThread(SignalDone);
        OsUtils::ThreadWait(m_flushThread);

        // Clean up mutex/condition variables
        m_pSignalMutex->Destroy();
        m_pSignalCond->Destroy();
        m_pSignalMutex = NULL;
        m_pSignalCond = NULL;

        // Tear down parent class
        ChiTestCase::Teardown();
    }

    /**************************************************************************************************************************
    *   FlushTest::WaitForFlushSignal()
    *
    *   @brief
    *       Should be run in a worker thread, which sleeps until condition variables wakes it up to trigger a flush
    *   @param
    *       [in]    VOID*   pArg    pointer to a FlushTest instance
    *   @return
    *       VOID* not used
    **************************************************************************************************************************/
    VOID* FlushTest::WaitForFlushSignal(VOID* pArg)
    {
        bool isDone = false;
        FlushTest* flushInstance = NULL;

        // Get the FlushTest instance
        if (NULL != pArg)
        {
            flushInstance = reinterpret_cast<FlushTest*>(pArg);
        }
        else
        {
            NT_EXPECT(NULL != pArg, "No FlushTest instance provided!");
            return NULL;
        }

        /* START critical section */
        flushInstance->m_pSignalMutex->Lock();

        // Main loop
        while (!isDone)
        {
            // Wait for next signal
            flushInstance->m_pSignalCond->Wait(flushInstance->m_pSignalMutex->GetNativeHandle());

            switch (flushInstance->m_flushSignaler)
            {
            case SignalReady:
                // Do nothing
                NT_LOG_DEBUG( "Flush thread ready...");
                break;
            case SignalFlush:
                // Delay and trigger flush
                NT_LOG_INFO( "Delay before flush: %u us (%u ms)", flushInstance->m_usFlushDelay,
                    flushInstance->m_usFlushDelay/1000);
                OsUtils::SleepMicroseconds(flushInstance->m_usFlushDelay);

                switch (flushInstance->m_pipelineConfig)
                {
                case RealtimeConfig:
                    flushInstance->TriggerFlush(RealtimeSession);
                    break;
                case OfflineConfig:
                    flushInstance->TriggerFlush(OfflineSession);
                    break;
                case MixedConfig:
                    flushInstance->TriggerFlush(RealtimeSession);
                    flushInstance->TriggerFlush(OfflineSession);
                    break;
                default:
                    NT_LOG_ERROR( "Invalid PipelineConfig provided! %d", flushInstance->m_pipelineConfig);
                    break;
                }
                break;
            case SignalDone:
                // Ready to exit
                NT_LOG_DEBUG( "Flush thread done...");
                isDone = true;
                break;
            default:
                NT_LOG_ERROR( "Invalid FlushSignal! (%d)", flushInstance->m_flushSignaler);
                break;
            }

            // Notify that flush thread is ready for next command
            flushInstance->m_flushSignaler = SignalReady;
            flushInstance->m_pSignalCond->Broadcast();
        }

        flushInstance->m_pSignalMutex->Unlock();
        /* END critical section */

        return NULL;
    }

    /**************************************************************************************************************************
    *   FlushTest::SignalFlushThread()
    *
    *   @brief
    *       Changes the signaler and then notifies the flush thread
    *   @param
    *       [in]    FlushSignal     signal      command to direct the flush thread
    *   @return
    *       void
    **************************************************************************************************************************/
    void FlushTest::SignalFlushThread(FlushSignal signal)
    {
        /* START critical section */
        m_pSignalMutex->Lock();

        // Wait for thread to be ready
        while (SignalReady != m_flushSignaler)
        {
            m_pSignalCond->Wait(m_pSignalMutex->GetNativeHandle());
        }

        // Set the signal
        m_flushSignaler = signal;

        m_pSignalMutex->Unlock();
        /* END critical section */

        // Notify the thread
        NT_LOG_DEBUG( "Signaling flush thread: %s", m_flushSignalStrings[signal]);
        m_pSignalCond->Broadcast();
    }

    /**************************************************************************************************************************
    *   FlushTest::SetupStreams()
    *
    *   @brief
    *       Overridden function implementation which defines the stream information based on the test Id
    *   @param
    *       None
    *   @return
    *       CDKResult success if stream objects could be created or failure
    **************************************************************************************************************************/
    CDKResult FlushTest::SetupStreams()
    {
        CDKResult result = CDKResultSuccess;
        int streamIndex = 0;

        switch (m_testId)
        {
        case FlushNodeIFE:
        case FlushQueueIFE:
        case FlushRecoverIFE:
            m_numStreams = 1;

            //1. IFE full stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IFEOutputPortFull;
            m_isRealtime[streamIndex] = true;

            m_streamInfo.num_streams  = m_numStreams;
            break;

        case FlushNodeStats3A:
        case FlushQueueStats3A:
        case FlushRecoverStats3A:
            m_numStreams = 1;
            //1. Preview stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = PREVIEW;
            m_isRealtime[streamIndex] = true;

            m_streamInfo.num_streams  = m_numStreams;
            break;

        case FlushNodeIPEJpeg:
        case FlushQueueIPEJpeg:
        case FlushRecoverIPEJpeg:
        case FlushNodeBPSIPEJpeg:
        case FlushQueueBPSIPEJpeg:
        case FlushRecoverBPSIPEJpeg:
            m_numStreams = 1;
            m_resolution[streamIndex] = UHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = SNAPSHOT;
            m_isRealtime[streamIndex] = true;

            m_streamInfo.num_streams  = m_numStreams;
            break;

        case FlushNodeFD:
        case FlushQueueFD:
        case FlushRecoverFD:
            m_numStreams = 1;

            m_resolution[streamIndex] = VGA;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = FDManagerOutputPort;
            m_isRealtime[streamIndex] = true;
            m_streamInfo.isJpeg       = false;

            m_streamInfo.num_streams  = m_numStreams;
            break;

        case FlushNodeIPE_offline:
        case FlushQueueIPE_offline:
        case FlushRecoverIPE_offline:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = VGA;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = IPE_COLORBAR_VGA;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            //2. Preview stream
            m_resolution[streamIndex] = VGA;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = PREVIEW;
            m_isRealtime[streamIndex] = false;

            m_streamInfo.num_streams  = m_numStreams;
            break;
        case FlushNodeBPS_IPE_offline:
        case FlushQueueBPS_IPE_offline:
        case FlushRecoverBPS_IPE_offline:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = ChiStreamFormatRaw16;
            m_streamId[streamIndex]   = BPSInputPort;
            m_streamInfo.filename     = BPS_COLORBAR_FHD;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            //2. Preview stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = PREVIEW;
            m_isRealtime[streamIndex] = false;

            m_streamInfo.num_streams = m_numStreams;
            break;
        case FlushNodeBPS_IPE_offline_2Streams:
        case FlushQueueBPS_IPE_offline_2Streams:
        case FlushRecoverBPS_IPE_offline_2Streams:
            m_numStreams = 3;

            //1. Input stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = ChiStreamFormatRaw16;
            m_streamId[streamIndex]   = BPSInputPort;
            m_streamInfo.filename     = BPS_COLORBAR_FHD;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            //2. IPE Display
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEOutputPortDisplay;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            //3. IPE Video
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEOutputPortVideo;
            m_isRealtime[streamIndex] = false;

            m_streamInfo.num_streams = m_numStreams;
            break;
        case FlushNodeBPS_IPE_JPEG_offline:
        case FlushQueueBPS_IPE_JPEG_offline:
        case FlushRecoverBPS_IPE_JPEG_offline:
            m_numStreams = 2;

            //1. RDI stream
            m_resolution[streamIndex] = UHD;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = ChiStreamFormatRaw16;
            m_streamId[streamIndex]   = IFEOutputPortRDI0;
            m_streamInfo.filename     = BPS_COLORBAR_FHD;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            //2. Snapshot stream (JPEG)
            m_resolution[streamIndex] = UHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = SNAPSHOT;
            m_isRealtime[streamIndex] = false;

            m_streamInfo.num_streams = m_numStreams;
            break;
        case FlushNodeFD_offline:
        case FlushQueueFD_offline:
        case FlushRecoverFD_offline:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = VGA;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = ChiNodeInputPort0;
            m_streamInfo.filename     = IPE_COLORBAR_VGA;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            //2. FD manager stream
            m_resolution[streamIndex] = Size(16384, 1);
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = FDManagerOutputPort;
            m_isRealtime[streamIndex] = false;

            m_streamInfo.isJpeg = false;
            m_streamInfo.num_streams = m_numStreams;
            break;
        case FlushNodeChiDepthNode_offline:
        case FlushQueueChiDepthNode_offline:
        case FlushRecoverChiDepthNode_offline:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = ChiStreamFormatRaw16;
            m_streamId[streamIndex]   = ChiNodeInputPort0;
            m_streamInfo.filename     = BPS_COLORBAR_FHD;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            //2. Depth stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatY16;
            m_streamId[streamIndex]   = ChiNodeOutputPort0;
            m_isRealtime[streamIndex] = false;

            m_streamInfo.isJpeg = false;
            m_streamInfo.num_streams = m_numStreams;
            break;
        case FlushNodeChiExternalNode_offline:
        case FlushQueueChiExternalNode_offline:
        case FlushRecoverChiExternalNode_offline:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = ChiStreamFormatRaw16;
            m_streamId[streamIndex]   = ChiNodeInputPort0;
            m_streamInfo.filename     = BPS_COLORBAR_FHD;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            //2. SNAPSHOT stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = SNAPSHOT;
            m_isRealtime[streamIndex] = false;

            m_streamInfo.num_streams = m_numStreams;
            break;
        case FlushNodeChiExternalNodeJpeg_offline:
        case FlushQueueChiExternalNodeJpeg_offline:
        case FlushRecoverChiExternalNodeJpeg_offline:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = UHD;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = ChiStreamFormatRaw16;
            m_streamId[streamIndex]   = ChiNodeInputPort0;
            m_streamInfo.filename     = BPS_IDEALRAW_UHD;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            //2. SNAPSHOT stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = SNAPSHOT;
            m_isRealtime[streamIndex] = false;

            m_streamInfo.num_streams  = m_numStreams;
            break;
        case FlushNode3Streams:
        case FlushQueue3Streams:
        case FlushRecover3Streams:
            m_numStreams = 3;

            //1. Preview stream
            m_resolution[streamIndex] = VGA;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCNV12;
            m_streamId[streamIndex]   = IPEOutputPortDisplay;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //2. RDI stream
            m_resolution[streamIndex] = UHD;
            m_direction[streamIndex]  = ChiStreamTypeBidirectional;
            m_format[streamIndex]     = ChiStreamFormatRaw16;
            m_streamId[streamIndex]   = IFEOutputPortRDI0;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //3. Snapshot stream (YUV)
            m_resolution[streamIndex] = UHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = SNAPSHOT;
            m_isRealtime[streamIndex] = false;

            m_streamInfo.num_streams = m_numStreams;
            break;

        case FlushNodeChiDepthNode:
        case FlushQueueChiDepthNode:
        case FlushRecoverChiDepthNode:
            m_numStreams = 1;

            //1. Depth stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatY16;
            m_streamId[streamIndex]   = PREVIEW;
            m_isRealtime[streamIndex] = true;

            m_streamInfo.isJpeg = false;
            m_streamInfo.num_streams = m_numStreams;
            break;

        case FlushNodeChiExternalNode:
        case FlushQueueChiExternalNode:
        case FlushRecoverChiExternalNode:
        case FlushNodeCustomNode:
        case FlushQueueCustomNode:
        case FlushRecoverCustomNode:
        case FlushNodeBypassNode:
        case FlushQueueBypassNode:
        case FlushRecoverBypassNode:
        case FlushNodeInplaceNode:
        case FlushQueueInplaceNode:
        case FlushRecoverInplaceNode:

            m_numStreams = 1;

            //1. Preview stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = PREVIEW;
            m_isRealtime[streamIndex] = true;
            m_streamInfo.num_streams  = m_numStreams;
            break;

        case FlushNodeLRME_RANSAC:
        case FlushQueueLRME_RANSAC:
        case FlushRecoverLRME_RANSAC:
            m_numStreams = 10;

            //1. IPE Display (A)
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEOutputPortDisplay;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //2. IPE Video (B)
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEOutputPortVideo;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //3. IFE FD (C)
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IFEOutputPortFD;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //4. IFE Stats BF
            m_resolution[streamIndex] = Size(5768, 1);
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = IFEOutputPortStatsBF;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //5. IFE Stats AWBBG
            m_resolution[streamIndex] = Size(691200, 1);
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = IFEOutputPortStatsAWBBG;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //6. IFE Stats TLBG
            m_resolution[streamIndex] = Size(147456, 1);
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = IFEOutputPortStatsTLBG;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //7. IFE Stats IHIST
            m_resolution[streamIndex] = Size(2048, 1);
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = IFEOutputPortStatsIHIST;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //8. IFE Stats RS
            m_resolution[streamIndex] = Size(32768, 1);
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = IFEOutputPortStatsRS;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //9. Offline Input stream
            m_resolution[streamIndex] = HD4K;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = IPE_EMULATEDSENSOR_4K;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            //10. Offline IPE Display
            m_resolution[streamIndex] = HD4K;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = PREVIEW;
            m_isRealtime[streamIndex] = false;

            m_streamInfo.isJpeg = false;
            m_streamInfo.num_streams = m_numStreams;
            break;

        case FlushNodeChiGPUNode:
        case FlushQueueChiGPUNode:
        case FlushRecoverChiGPUNode:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = VGA;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = GPUInputPort;
            m_streamInfo.filename     = IPE_COLORBAR_VGA;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            //2. GPU Full out stream
            m_resolution[streamIndex] = VGA;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = GPUOutputPortFull;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            m_streamInfo.num_streams  = m_numStreams;
            break;

        case FlushNode4Streams:
        case FlushQueue4Streams:
        case FlushRecover4Streams:
            m_numStreams = 4;

            //1. Input stream
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = ChiStreamFormatRaw16;
            m_streamId[streamIndex]   = BPSInputPort;
            m_resolution[streamIndex] = UHD;
            m_streamInfo.filename     = BPS_IDEALRAW_UHD;
            streamIndex++;

            //2. BPS Full stream
            m_resolution[streamIndex] = UHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCTP10;
            m_usageFlag[streamIndex]  = GrallocUsageTP10;
            m_streamId[streamIndex]   = BPSOutputPortFull;
            streamIndex++;

            //3. BPS BG stats stream
            m_resolution[streamIndex] = Size(691200, 1);
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = BPSOutputPortStatsBG;
            streamIndex++;

            //4. BPS bHist stream
            m_resolution[streamIndex] = Size(3072, 1);
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = BPSOutputPortStatsBhist;
            m_streamInfo.isJpeg       = false;

            m_streamInfo.isJpeg = false;
            m_streamInfo.num_streams  = m_numStreams;
            break;

        case FlushNode5Streams:
        case FlushQueue5Streams:
        case FlushRecover5Streams:
            m_numStreams = 5;

            //1. preview stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCNV12;
            m_streamId[streamIndex]   = IPEOutputPortDisplay;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //2. Preview callback stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = PREVIEWCALLBACK;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //3. RDI stream
            m_resolution[streamIndex] = UHD;
            m_direction[streamIndex]  = ChiStreamTypeBidirectional;
            m_format[streamIndex]     = ChiStreamFormatRaw16;
            m_streamId[streamIndex]   = IFEOutputPortRDI1;
            m_isRealtime[streamIndex] = true;
            streamIndex++;

            //4. Snapshot stream (JPEG)
            m_resolution[streamIndex] = UHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = SNAPSHOT;
            m_isRealtime[streamIndex] = false;
            streamIndex++;

            //5. YUV thumbnail
            m_resolution[streamIndex] = VGA;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = THUMBNAIL;
            m_isRealtime[streamIndex] = false;

            m_streamInfo.num_streams = m_numStreams;
            break;

        default:
            NT_LOG_ERROR( "Unknown testcase Id provided: [%d]", m_testId);
            result = CDKResultENoSuch;
            break;
        }

        if (m_streamInfo.num_streams <= 0) {
            NT_LOG_ERROR("Number of streams should be greater than 0, given: %d", m_streamInfo.num_streams);
            result = CDKResultEFailed;
        }

        if (result == CDKResultSuccess)
        {
            m_pRequiredStreams = SAFE_NEW() CHISTREAM[m_streamInfo.num_streams];

            if (NULL == m_pRequiredStreams)
            {
                NT_LOG_ERROR("Failed to initialize CHI streams");
                result = CDKResultEFailed;
            }
            else
            {
                camera3_stream_t* pCamStreams = CreateStreams(m_streamInfo);

                if (nullptr == pCamStreams)
                {
                    NT_LOG_ERROR("Unable to create streams");
                    result = CDKResultEFailed;
                }
                else
                {
                    ConvertCamera3StreamToChiStream(pCamStreams, m_pRequiredStreams, m_streamInfo.num_streams);
                    delete[] pCamStreams;   // No longer needed, converted to m_pRequiredStreams

                    if (NULL == m_pRequiredStreams)
                    {
                        NT_LOG_ERROR("Provided streams could not be configured for testcase Id: [%d]", m_testId);
                        result = CDKResultEFailed;
                    }
                    else
                    {
                        for (int index = 0; index < m_numStreams; index++)
                        {
                            m_streamIdMap[m_streamInfo.streamIds[index]] = &m_pRequiredStreams[index];
                        }
                        if (m_streamIdMap.size() != static_cast<size_t>(m_numStreams))
                        {
                            result = CDKResultEFailed;
                        }
                    }
                }
            }
        }

        return result;
    }

    /**************************************************************************************************************************
    *   FlushTest::SetupPipelines()
    *
    *   @brief
    *       Overridden function implementation which creates pipeline objects based on the test Id
    *   @param
    *       [in]  int                 cameraId    cameraId to be associated with the pipeline
    *       [in]  ChiSensorModeInfo*  sensorMode  sensor mode to be used for the pipeline
    *   @return
    *       CDKResult success if pipelines could be created or failure
    **************************************************************************************************************************/
    CDKResult FlushTest::SetupPipelines(int cameraId, ChiSensorModeInfo * sensorMode)
    {
        CDKResult result = CDKResultSuccess;

        switch (m_testId)
        {
        case FlushNodeIFE:
        case FlushQueueIFE:
        case FlushRecoverIFE:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFE);
            break;
        case FlushNodeStats3A:
        case FlushQueueStats3A:
        case FlushRecoverStats3A:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeStats3A);
            break;
        case FlushNodeIPEJpeg:
        case FlushQueueIPEJpeg:
        case FlushRecoverIPEJpeg:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIPEJpeg);
            break;
        case FlushNodeBPSIPEJpeg:
        case FlushQueueBPSIPEJpeg:
        case FlushRecoverBPSIPEJpeg:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeBPSIPEJpeg);
            break;
        case FlushNodeFD:
        case FlushQueueFD:
        case FlushRecoverFD:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeFD);
            break;
        case FlushNodeChiExternalNode_offline:
        case FlushQueueChiExternalNode_offline:
        case FlushRecoverChiExternalNode_offline:
            m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineExtBPSIPE);
            break;
        case FlushNodeChiExternalNodeJpeg_offline:
        case FlushQueueChiExternalNodeJpeg_offline:
        case FlushRecoverChiExternalNodeJpeg_offline:
            m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineExtBPSIPEJPEG);
            break;
        case FlushNodeIPE_offline:
        case FlushQueueIPE_offline:
        case FlushRecoverIPE_offline:
            m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineIPEDisp);
            break;
        case FlushNodeBPS_IPE_offline:
        case FlushQueueBPS_IPE_offline:
        case FlushRecoverBPS_IPE_offline:
            m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSIPE);
            break;
        case FlushNodeBPS_IPE_offline_2Streams:
        case FlushQueueBPS_IPE_offline_2Streams:
        case FlushRecoverBPS_IPE_offline_2Streams:
            m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSIPEDispVideo);
            break;
        case FlushNodeBPS_IPE_JPEG_offline:
        case FlushQueueBPS_IPE_JPEG_offline:
        case FlushRecoverBPS_IPE_JPEG_offline:
            m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineZSlSnap);
            break;
        case FlushNodeFD_offline:
        case FlushQueueFD_offline:
        case FlushRecoverFD_offline:
            m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineFDPipeline);
            break;
        case FlushNodeChiDepthNode_offline:
        case FlushQueueChiDepthNode_offline:
        case FlushRecoverChiDepthNode_offline:
            m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineDepthNode);
            break;
        case FlushNode3Streams:
        case FlushQueue3Streams:
        case FlushRecover3Streams:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimePrevRDI);
            m_pChiPipeline[Offline]  = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineZSlSnap);
            break;
        case FlushNodeChiDepthNode:
        case FlushQueueChiDepthNode:
        case FlushRecoverChiDepthNode:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeChiDepth);
            break;
        case FlushNodeChiExternalNode:
        case FlushQueueChiExternalNode:
        case FlushRecoverChiExternalNode:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimePrevWithMemcpy);
            break;
        case FlushNodeLRME_RANSAC:
        case FlushQueueLRME_RANSAC:
        case FlushRecoverLRME_RANSAC:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIPEABCStats);
            m_pChiPipeline[Offline]  = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineIPEDisp);
            break;
        case FlushNodeChiGPUNode:
        case FlushQueueChiGPUNode:
        case FlushRecoverChiGPUNode:
            m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineChiGPUNode);
            break;
        case FlushNodeCustomNode:
        case FlushQueueCustomNode:
        case FlushRecoverCustomNode:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::VendorTagWrite);
            break;
        case FlushNodeBypassNode:
        case FlushQueueBypassNode:
        case FlushRecoverBypassNode:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeBypassNode);
            break;
        case FlushNodeInplaceNode:
        case FlushQueueInplaceNode:
        case FlushRecoverInplaceNode:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeInplaceNode);
            break;
        case FlushNode4Streams:
        case FlushQueue4Streams:
        case FlushRecover4Streams:
            m_pChiPipeline[Offline]  = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSStats);
            break;
        case FlushNode5Streams:
        case FlushQueue5Streams:
        case FlushRecover5Streams:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimePrevWithCallbackAndRDIWithStats);
            m_pChiPipeline[Offline]  = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineZSlSnapAndThumbnailWithDSports);
            break;
        default:
            NT_LOG_ERROR( "Unknown testcase Id provided: [%d]", m_testId);
            return CDKResultENoSuch;
        }

        switch (m_pipelineConfig)
        {
        case RealtimeConfig:
            result = (NULL != m_pChiPipeline[Realtime]) ? m_pChiPipeline[Realtime]->CreatePipelineDesc() : CDKResultEInvalidPointer;
            break;
        case OfflineConfig:
            result = (NULL != m_pChiPipeline[Offline]) ? m_pChiPipeline[Offline]->CreatePipelineDesc() : CDKResultEInvalidPointer;
            break;
        case MixedConfig:
            result = (NULL != m_pChiPipeline[Realtime]) ? m_pChiPipeline[Realtime]->CreatePipelineDesc() : CDKResultEInvalidPointer;
            result |= (NULL != m_pChiPipeline[Offline]) ? m_pChiPipeline[Offline]->CreatePipelineDesc() : CDKResultEInvalidPointer;
            break;
        default:
            NT_LOG_ERROR( "Invalid PipelineConfig provided! %d", m_pipelineConfig);
            break;
        }

        return result;
    }

    /**************************************************************************************************************************
    *   FlushTest::CreateSessions()
    *
    *   @brief
    *       Overridden function implementation which creates required number of sessions based on the test Id
    *   @param
    *       None
    *   @return
    *       CDKResult success if sessions could be created or failure
    **************************************************************************************************************************/
    CDKResult FlushTest::CreateSessions()
    {
        CDKResult result = CDKResultSuccess;

        switch (m_pipelineConfig)
        {
        case RealtimeConfig:
            result = CreateSessionHelper(RealtimeSession);
            break;
        case OfflineConfig:
            result = CreateSessionHelper(OfflineSession);
            break;
        case MixedConfig:
            result = CreateSessionHelper(RealtimeSession);
            result |= CreateSessionHelper(OfflineSession);
            break;
        default:
            NT_LOG_ERROR( "Invalid PipelineConfig provided! %d", m_pipelineConfig);
            break;
        }

        return result;
    }

    /**************************************************************************************************************************
    *   FlushTest::CreateSessionHelper()
    *
    *   @brief
    *       Helper function to create a single session, using the session Id given
    *   @param
    *       [in]    SessionId   sessionId   session Id to create session for
    *   @return
    *       CDKResult success if session could be created or failure
    **************************************************************************************************************************/
    CDKResult FlushTest::CreateSessionHelper(SessionId sessionId)
    {
        CDKResult result = CDKResultSuccess;
        ChiCallBacks callbacks = {};
        PipelineIndex pipeIndex = (sessionId == RealtimeSession) ? Realtime : Offline;

        callbacks.ChiNotify                      = ChiTestCase::ProcessMessage;
        callbacks.ChiProcessCaptureResult        = ChiTestCase::QueueCaptureResult;
        callbacks.ChiProcessPartialCaptureResult = ChiTestCase::QueuePartialCaptureResult;

        m_perSessionPvtData[sessionId].pTestInstance = this;
        m_perSessionPvtData[sessionId].sessionId = sessionId;
        m_pChiSession[sessionId] = ChiSession::Create(&m_pChiPipeline[pipeIndex], 1, &callbacks, &m_perSessionPvtData[sessionId]);

        if (NULL == m_pChiSession[sessionId])
        {
            NT_LOG_ERROR( "%s session could not be created", (sessionId == RealtimeSession) ? "Realtime" : "Offline");
            result = CDKResultEFailed;
        }
        else
        {
            result = m_pChiPipeline[pipeIndex]->ActivatePipeline(m_pChiSession[sessionId]->GetSessionHandle());
#ifndef OLD_METADATA
            if (result == CDKResultSuccess)
            {
                result = m_pChiMetadataUtil->GetPipelineinfo(m_pChiModule->GetContext(),
                    m_pChiSession[sessionId]->GetSessionHandle(), m_pChiPipeline[pipeIndex]->GetPipelineHandle(),
                    &m_pPipelineMetadataInfo[pipeIndex]);
            }
#endif // OLD_METADATA
        }

        return result;
    }

    /**************************************************************************************************************************
    *   FlushTest::CommonProcessCaptureResult()
    *
    *   @brief
    *       Overridden function implementation which processes the capture result obtained from driver
    *   @param
    *       [in]    CHICAPTURERESULT*       pCaptureResult          pointer to capture result
    *       [in]    SessionPrivateData*     pPrivateCallbackData    pointer private callback data
    *   @return
    *       None
    **************************************************************************************************************************/
    void FlushTest::CommonProcessCaptureResult(
        ChiCaptureResult* pCaptureResult,
        SessionPrivateData* pSessionPrivateData)
    {
        CDKResult result = CDKResultSuccess;
        uint32_t  resultFrameNum = pCaptureResult->frameworkFrameNum;
        uint32_t  numOutputBuffers = pCaptureResult->numOutputBuffers;
        SessionId sessionId = static_cast<SessionId>(pSessionPrivateData->sessionId);

#ifndef OLD_METADATA
        if (m_pChiMetadataUtil != nullptr)
        {
            m_pChiMetadataUtil->VerifyCaptureResultMetadata(static_cast<CHIMETAHANDLE>(pCaptureResult->pOutputMetadata));
        }
#endif // OLD_METADATA

        if (sessionId == RealtimeSession || sessionId == OfflineSession) // TODO do we need to differentiate?
        {
            for (uint32_t bufferIndex = 0; bufferIndex < numOutputBuffers; bufferIndex++)
            {
                BufferManager::NativeChiBuffer* outBuffer = const_cast<BufferManager::NativeChiBuffer*>(&pCaptureResult->
                    pOutputBuffers[bufferIndex]);
                BufferManager* manager = m_streamBufferMap[outBuffer->pStream];
                if (NULL == manager)
                {
                    NT_LOG_ERROR( "Could not find buffer manger for given stream: %p in frame: %d",
                        outBuffer->pStream, resultFrameNum);
                    result |= CDKResultEInvalidPointer;
                }
                else
                {
                    BufferManager::GenericBuffer genericBuffer(outBuffer);
                    CDKResult processRes = manager->ProcessBufferFromResult(resultFrameNum, &genericBuffer, true);
                    int bufStatus = manager->GetStatusFromBuffer(&genericBuffer);

                    // If session was flushed...
                    if (m_bIsFlushTriggered)
                    {
                        switch (m_testType)
                        {
                        case FlushNodeTest:
                        case FlushRecoverTest:
                        case FlushQueueTest:
                            // If we got an error notify associated with this frame...
                            if (CheckErrorNotifyFlag(resultFrameNum, CHIERRORMESSAGECODE::MessageCodeRequest) ||
                                CheckErrorNotifyFlag(resultFrameNum, CHIERRORMESSAGECODE::MessageCodeBuffer, outBuffer->pStream))
                            {
                                // Then check for buffer status error due to flush
                                NT_EXPECT(processRes == -1 && bufStatus == CAMERA3_BUFFER_STATUS_ERROR,
                                     "Expected a buffer status error (1) due to flush. Got status %d instead!", bufStatus);
                            }
                            else
                            {
                                // Warning that no error notify received for this flushed frame (not a hard requirement)
                               NT_LOG_WARN( "Notify from flush for frame %d did not occur!", resultFrameNum);
                            }
                            break;
                        default:
                            NT_LOG_ERROR( "Invalid TestType provided! %d", m_testType);
                            break;
                        }
                    }

                    // If session was flushed, allow buffer status to be error, otherwise just get result like normal
                    result |= (m_bIsFlushTriggered && processRes == -1 && bufStatus == CAMERA3_BUFFER_STATUS_ERROR) ?
                        CDKResultSuccess : processRes;
                }
            }

            // Only for CustomNode tests : populate vendortag with current processed frame, verify vendor tag frame matches expected frame number
            if (m_testId == FlushNodeCustomNode || m_testId == FlushQueueCustomNode || m_testId == FlushRecoverCustomNode)
            {
                NT_EXPECT(ValidateCustomNodeResult(pCaptureResult) == CDKResultSuccess,"Custom node result validation failure!");
            }
        }
        else
        {
            NT_LOG_ERROR( "Unknown Session Id: %d obtained", sessionId);
            result = CDKResultEInvalidState;
        }

        if (result == CDKResultSuccess)
        {
            AtomicDecrement(numOutputBuffers);
            NT_LOG_DEBUG( "Number of pending buffers remaining: %d after receiving the result for frame: %d",
                GetPendingBufferCount(), resultFrameNum);
        }
    }

    /***************************************************************************************************************************
    *   FlushTest::SetSpecialMetadata()
    *
    *   @brief
    *       Function to set metadata for some testcases
    *   @param
    *       [in] uint64_t      frameNumber     framenumber associated with the request
    *       [in] CHIMETAHANDLE pInputMetadata  input metadata handle
    *   @return
    *       None
    ***************************************************************************************************************************/
    void FlushTest::SetSpecialMetadata(uint64_t frameNumber, CHIMETAHANDLE pInputMetadata)
    {
        CDKResult result;
        UINT32 tagID = ANDROID_STATISTICS_FACE_DETECT_MODE;
        UINT32 pData = ANDROID_STATISTICS_FACE_DETECT_MODE_SIMPLE;
        UINT32 count = 1;

        switch (m_testId)
        {
        case FlushNodeFD:
        case FlushQueueFD:
        case FlushRecoverFD:
        case FlushNodeFD_offline:
        case FlushQueueFD_offline:
        case FlushRecoverFD_offline:
            NT_LOG_DEBUG( "Setting metadata ANDROID_STATISTICS_FACE_DETECT_MODE_SIMPLE for frame:%d", frameNumber);
            result = m_pChiMetadataUtil->GetMetadataOps().pSetTag(pInputMetadata, tagID, &pData, count);
            NT_EXPECT(result == CDKResultSuccess,"Failed to set metadata ANDROID_STATISTICS_FACE_DETECT_MODE_SIMPLE");
            break;
        default:
            // return if no metadata needed to be set
            break;
        }
    }

    /**************************************************************************************************************************
    *   FlushTest::ValidateCustomNodeResult()
    *
    *   @brief
    *       Function implementation to populate vendortag with current processed frame, verify vendor tag frame matches expected frame number
    *   @param
    *       [in]    CHICAPTURERESULT*       pCaptureResult          pointer to capture result
    *   @return
    *       CDKResult
    **************************************************************************************************************************/
    CDKResult FlushTest::ValidateCustomNodeResult(ChiCaptureResult* pCaptureResult)
    {
        CDKResult result = CDKResultSuccess;
        uint32_t  resultFrameNum = pCaptureResult->frameworkFrameNum;
        uint64_t processedFrameHolder = 0;
        uint64_t* pProcessedFrame = &processedFrameHolder;
        UINT32 tagLocation = 0;

        if (NULL != GetOutputMetadata(pCaptureResult))
        {
            result = m_pChiModule->GetTagOps().pQueryVendorTagLocation("com.bots.node.vendortagwrite",
                "ProcessedFrameNumber", &tagLocation);
            if (CDKResultSuccess != result)
            {
                NT_LOG_ERROR( "Could not get vendor tag with section com.bots.node.vendortagwrite");
            }
            else
            {
#ifdef OLD_METADATA
                m_pChiModule->GetTagOps().pGetMetaData(const_cast<CHIMETADATAHANDLE>(GetOutputMetadata(pCaptureResult)),
                    tagLocation, pProcessedFrame, sizeof(uint64_t));
#else
                m_pChiMetadataUtil->GetVendorTag(const_cast<CHIMETADATAHANDLE>(GetOutputMetadata(pCaptureResult)),
                    "com.bots.node.vendortagwrite", "ProcessedFrameNumber", reinterpret_cast<VOID**>(&pProcessedFrame));
#endif // OLD_METADATA

                NT_LOG_DEBUG( "Current frameNumber from result metadata: %" PRIu32, resultFrameNum);
                NT_LOG_DEBUG( "Value of frameNumber written by custom node: %" PRIu64, *pProcessedFrame);

                if (*pProcessedFrame != resultFrameNum)
                {
                    NT_LOG_ERROR( "Vendor tag processed frame does not match framework result frame");
                    result = CDKResultEFailed;
                }
            }
        }

        return result;
    }

    /**************************************************************************************************************************
    *   FlushTest::DestroyResources()
    *
    *   @brief
    *       Overridden function implementation which destroys all created resources / objects
    *   @param
    *       None
    *   @return
    *       None
    **************************************************************************************************************************/
    void FlushTest::DestroyResources()
    {
        // Ensure flush thread is completely done flushing before continuing
        SignalFlushThread(SignalReady);

        switch (m_pipelineConfig)
        {
        case RealtimeConfig:
            DestroyResourcesHelper(RealtimeSession);
            break;
        case OfflineConfig:
            DestroyResourcesHelper(OfflineSession);
            break;
        case MixedConfig:
            DestroyResourcesHelper(RealtimeSession);
            DestroyResourcesHelper(OfflineSession);
            break;
        default:
            NT_LOG_ERROR( "Invalid PipelineConfig provided! %d", m_pipelineConfig);
            break;
        }

        DestroyCommonResources();
    }

    /**************************************************************************************************************************
    *   FlushTest::DestroyResourcesHelper()
    *
    *   @brief
    *       Helper for DestroyResources to destroy resources depending on session Id
    *   @param
    *       [in]    SessionId   sessionId   session Id to destoy resources for
    *   @return
    *       None
    **************************************************************************************************************************/
    void FlushTest::DestroyResourcesHelper(SessionId sessionId)
    {
        PipelineIndex pipeIndex = (sessionId == RealtimeSession) ? Realtime : Offline;
        m_pChiPipeline[pipeIndex]->DeactivatePipeline(m_pChiSession[sessionId]->GetSessionHandle());

        if (NULL != m_pChiSession[sessionId])
        {
            m_pChiSession[sessionId]->DestroySession();
            m_pChiSession[sessionId] = NULL;
        }

        if (NULL != m_pChiPipeline[pipeIndex])
        {
            m_pChiPipeline[pipeIndex]->DestroyPipeline();
            m_pChiPipeline[pipeIndex] = NULL;
        }
    }

    /**************************************************************************************************************************
    *   FlushTest::GenerateRealtimeCaptureRequest()
    *
    *   @brief
    *       Generate a realtime pipeline request
    *   @param
    *       [in] uint64_t   frameNumber     frame number associated with the request
    *   @return
    *       CDKResult success if request could be submitted or failure
    **************************************************************************************************************************/
    CDKResult FlushTest::GenerateRealtimeCaptureRequest(uint64_t frameNumber)
    {
        CDKResult result = CDKResultSuccess;
        uint32_t numOutputBuffers = 0;
        uint32_t streamIndex = 0;

        std::map<ChiStream*, BufferManager*>::iterator it;

        for (it = m_streamBufferMap.begin(); it != m_streamBufferMap.end(); ++it, ++streamIndex)
        {
            // Skip offline streams
            if (!m_isRealtime[streamIndex])
            {
                continue;
            }

            BufferManager* manager = it->second;
            void* buffer = manager->GetOutputBufferForRequest();
            if (NULL == buffer)
            {
                return CDKResultENoMore;
            }

            m_realtimeOutputBuffers[numOutputBuffers++] = *static_cast<BufferManager::NativeChiBuffer*>(buffer);
        }

        uint32_t requestId = FRAME_REQUEST_MOD(frameNumber);
        memset(&m_realtimeRequest[requestId], 0, sizeof(CHICAPTUREREQUEST));

        m_realtimeRequest[requestId].frameNumber     = frameNumber;
        m_realtimeRequest[requestId].hPipelineHandle = m_pChiPipeline[Realtime]->GetPipelineHandle();
        m_realtimeRequest[requestId].numOutputs      = numOutputBuffers;
        m_realtimeRequest[requestId].pOutputBuffers  = m_realtimeOutputBuffers;
        m_realtimeRequest[requestId].pPrivData       = &m_requestPvtData[RealtimeSession];

#ifdef OLD_METADATA
        m_realtimeRequest[requestId].pMetadata = allocate_camera_metadata(METADATA_ENTRIES, 100 * 1024);
        NATIVETEST_UNUSED_PARAM(m_pPipelineMetadataInfo);
#else
        // Get the input metabuffer from the pool
        m_realtimeRequest[requestId].pInputMetadata = m_pChiMetadataUtil->GetInputMetabufferFromPool(requestId);
        NT_EXPECT(m_realtimeRequest[requestId].pInputMetadata != nullptr, "Failed to create Input Metabuffer before sending request");

        // Get the output metabuffer from the pool
        m_realtimeRequest[requestId].pOutputMetadata = m_pChiMetadataUtil->GetOutputMetabufferFromPool(requestId,
            m_pPipelineMetadataInfo[Realtime].publishTagArray, m_pPipelineMetadataInfo[Realtime].publishTagCount);
        NT_EXPECT(m_realtimeRequest[requestId].pOutputMetadata != nullptr, "Failed to create Output Metabuffer before sending request");
#endif // OLD_METADATA

        SetSpecialMetadata(frameNumber, m_realtimeRequest[requestId].pInputMetadata);

        memset(&m_submitRequest, 0, sizeof(CHIPIPELINEREQUEST));
        m_submitRequest.pSessionHandle   = m_pChiSession[RealtimeSession]->GetSessionHandle();
        m_submitRequest.numRequests      = 1;
        m_submitRequest.pCaptureRequests = &m_realtimeRequest[requestId];

        CDKResult submitResult = m_pChiModule->SubmitPipelineRequest(&m_submitRequest);
        if (CDKResultSuccess == submitResult)
        {
            // Only increment pending buffer count if submit pipeline request succeeds
            AtomicIncrement(numOutputBuffers);
            NT_LOG_DEBUG( "Number of pending buffers remaining: %d after sending request for frame: %" PRIu64,
                GetPendingBufferCount(), frameNumber);
        }
        else
        {
            if (m_bIsFlushTriggered)
            {
               NT_LOG_WARN( "SubmitPipelineRequest to driver failed due to session flush");
            }
            else
            {
                NT_LOG_ERROR( "SubmitPipelineRequest to driver failed!");
            }
        }

        // Ignore failures from SubmitPipelineRequest if flush has already been triggered
        result |= (m_bIsFlushTriggered) ? CDKResultSuccess : submitResult;

        return result;
    }

    /***************************************************************************************************************************
    *   FlushTest::GenerateOfflineCaptureRequest()
    *
    *   @brief
    *       Generate an offline pipeline request
    *   @param
    *       [in] uint64_t   frameNumber     frame number associated with the request
    *   @return
    *       CDKResult success if request could be submitted or failure
    ***************************************************************************************************************************/
    CDKResult FlushTest::GenerateOfflineCaptureRequest(uint64_t frameNumber)
    {
        CDKResult result = CDKResultSuccess;
        uint32_t numOutputBuffers = 0;
        uint32_t streamIndex = 0;

        std::map<ChiStream*, BufferManager*>::iterator it;

        uint32_t requestId = FRAME_REQUEST_MOD(frameNumber);
        memset(&m_offlineRequest[requestId], 0, sizeof(CHICAPTUREREQUEST));

        for (it = m_streamBufferMap.begin(); it != m_streamBufferMap.end(); ++it, ++streamIndex)
        {
            void* pBuffer = NULL;
            BufferManager* manager = it->second;

            // Skip if stream is realtime and not bidir (for mixed pipeline config)
            if (m_isRealtime[streamIndex] && it->first->streamType != ChiStreamTypeBidirectional)
            {
                continue;
            }

            switch (it->first->streamType)
            {
            case ChiStreamTypeOutput:
                pBuffer = manager->GetOutputBufferForRequest();
                if (NULL == pBuffer)
                {
                    return CDKResultENoMore;
                }
                m_offlineOutputBuffers[numOutputBuffers++] = *static_cast<BufferManager::NativeChiBuffer*>(pBuffer);
                break;
            case ChiStreamTypeInput:
            case ChiStreamTypeBidirectional:
                pBuffer = manager->GetInputBufferForRequest();
                if (NULL == pBuffer)
                {
                    return CDKResultENoMore;
                }
                m_pInputBuffer = static_cast<BufferManager::NativeChiBuffer*>(pBuffer);
                break;
            default:
                NT_LOG_ERROR( "Invalid ChiStreamType provided! %d", it->first->streamType);
                break;
            }
        }

        m_offlineRequest[requestId].frameNumber     = frameNumber;
        m_offlineRequest[requestId].hPipelineHandle = m_pChiPipeline[Offline]->GetPipelineHandle();
        m_offlineRequest[requestId].pInputBuffers   = m_pInputBuffer;
        m_offlineRequest[requestId].numOutputs      = numOutputBuffers;
        m_offlineRequest[requestId].pOutputBuffers  = m_offlineOutputBuffers;
        m_offlineRequest[requestId].numInputs       = 1;
        m_offlineRequest[requestId].pPrivData       = &m_requestPvtData[OfflineSession];

#ifdef OLD_METADATA
        m_offlineRequest[requestId].pMetadata = allocate_camera_metadata(METADATA_ENTRIES, 100 * 1024);
        NATIVETEST_UNUSED_PARAM(m_pPipelineMetadataInfo);
#else
        // Get the input metabuffer from the pool
        m_offlineRequest[requestId].pInputMetadata = m_pChiMetadataUtil->GetInputMetabufferFromPool(requestId);
        NT_EXPECT(m_offlineRequest[requestId].pInputMetadata != nullptr,"Failed to create Input Metabuffer before sending request");

        // Get the output metabuffer from the pool
        m_offlineRequest[requestId].pOutputMetadata = m_pChiMetadataUtil->GetOutputMetabufferFromPool(requestId,
            m_pPipelineMetadataInfo[Offline].publishTagArray, m_pPipelineMetadataInfo[Offline].publishTagCount);
        NT_EXPECT(m_offlineRequest[requestId].pOutputMetadata != nullptr,"Failed to create Output Metabuffer before sending request");
#endif // OLD_METADATA

        SetSpecialMetadata(frameNumber, m_offlineRequest[requestId].pInputMetadata);

        memset(&m_submitRequest, 0, sizeof(CHIPIPELINEREQUEST));
        m_submitRequest.pSessionHandle   = m_pChiSession[OfflineSession]->GetSessionHandle();
        m_submitRequest.numRequests      = 1;
        m_submitRequest.pCaptureRequests = &m_offlineRequest[requestId];

        CDKResult submitResult = m_pChiModule->SubmitPipelineRequest(&m_submitRequest);
        if (CDKResultSuccess == submitResult)
        {
            // Only increment pending buffer count if submit pipeline request succeeds
            AtomicIncrement(numOutputBuffers);
            NT_LOG_DEBUG( "Number of pending buffers remaining: %d after sending request for frame: %" PRIu64,
                GetPendingBufferCount(), frameNumber);
        }
        else
        {
            if (m_bIsFlushTriggered)
            {
               NT_LOG_WARN( "SubmitPipelineRequest to driver failed due to session flush");
            }
            else
            {
                NT_LOG_ERROR( "SubmitPipelineRequest to driver failed!");
            }
        }

        // Ignore failures from SubmitPipelineRequest if flush has already been triggered
        result |= (m_bIsFlushTriggered) ? CDKResultSuccess : submitResult;

        return result;
    }

    /**************************************************************************************************************************
    *   FlushTest::TriggerFlush
    *
    *   @brief
    *       Flushes the session, sets the flush trigger flag, and starts tracking the flush time
    *   @param
    *       None
    *   @return
    *       None
    **************************************************************************************************************************/
    void FlushTest::TriggerFlush(SessionId sessionId)
    {
        // Check for disabled flush (runtime flag)
        if (false == CmdLineParser::DisableFlush())
        {
            m_bIsFlushTriggered = true;

            // Start tracking flush time
            m_flushStartTime = OsUtils::GetNanoSeconds();
            CDKResult result = m_pChiSession[sessionId]->FlushSession();
            m_flushEndTime = OsUtils::GetNanoSeconds();
            double flushTime = (m_flushEndTime - m_flushStartTime) / 1000000000.0;
            NT_LOG_INFO( "KPI: flush return time took %f seconds", flushTime);

            NT_EXPECT(CDKResultSuccess == result, "FlushSession call to driver failed with result %d !", result);
        }
        else
        {
           NT_LOG_WARN( "Flush is disabled via runtime flag, skipping FlushSession call...");
        }
    }

    /**************************************************************************************************************************
    *   FlushTest::FlushNode
    *
    *   @brief
    *       Send one capture request, then flush after a short delay. Delay is a configurable parameter, but can also be
    *       overridden by a runtime flag. Expect an error notify and bad buffer status.
    *   @param
    *       None
    *   @return
    *       CDKResult
    **************************************************************************************************************************/
    CDKResult FlushTest::FlushNode()
    {
        m_bIsFlushTriggered = false;
        uint64_t frameNumber = START_FRAME;

        // Clear notify flag before sending any capture requests
        ClearErrorNotifyFlag(frameNumber);

        // Create and submit one capture request, depending on pipeline type, then flush immediately
        switch (m_pipelineConfig)
        {
        case RealtimeConfig:
            if (GenerateRealtimeCaptureRequest(frameNumber) != CDKResultSuccess)
            {
                NT_LOG_ERROR( "Submit realtime pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                return CDKResultEFailed;
            }
            break;
        case OfflineConfig:
            if (GenerateOfflineCaptureRequest(frameNumber) != CDKResultSuccess)
            {
                NT_LOG_ERROR( "Submit offline pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                return CDKResultEFailed;
            }
            break;
        case MixedConfig:
            if (GenerateRealtimeCaptureRequest(frameNumber) != CDKResultSuccess)
            {
                NT_LOG_ERROR( "Submit realtime pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                return CDKResultEFailed;
            }
            if (GenerateOfflineCaptureRequest(++frameNumber) != CDKResultSuccess)
            {
                NT_LOG_ERROR( "Submit offline pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                return CDKResultEFailed;
            }
            break;
        default:
            NT_LOG_ERROR( "Invalid PipelineConfig provided! %d", m_pipelineConfig);
            break;
        }

        // Set signal flag to flush and notify flushing thread
        SignalFlushThread(SignalFlush);

        // Wait for all results
        if (WaitForResults() != CDKResultSuccess)
        {
            NT_LOG_ERROR( "There are pending buffers not returned by driver after several retries");
            return CDKResultEFailed;
        }

        return CDKResultSuccess;
    }

    /**************************************************************************************************************************
    *   FlushTest::FlushQueue
    *
    *   @brief
    *       Send 4 capture requests, then flush after a short delay. Delay is a configurable parameter, but can also be
    *       overridden by a runtime flag. For any frame that has an associated error notify, expect bad buffer status on that
    *       frame's buffers.
    *   @param
    *       None
    *   @return
    *       CDKResult
    **************************************************************************************************************************/
    CDKResult FlushTest::FlushQueue()
    {
        m_bIsFlushTriggered = false;

        for (uint64_t frameNumber = START_FRAME; frameNumber < m_flushQueueTriggerFrame; frameNumber++)
        {
            // Clear notify flag
            ClearErrorNotifyFlag(frameNumber);

            // Create and submit capture request, depending on pipeline type
            switch (m_pipelineConfig)
            {
            case RealtimeConfig:
                if (GenerateRealtimeCaptureRequest(frameNumber) != CDKResultSuccess)
                {
                    NT_LOG_ERROR( "Submit realtime pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                    return CDKResultEFailed;
                }
                break;
            case OfflineConfig:
                if (GenerateOfflineCaptureRequest(frameNumber) != CDKResultSuccess)
                {
                    NT_LOG_ERROR( "Submit offline pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                    return CDKResultEFailed;
                }
                break;
            case MixedConfig:
                if (GenerateRealtimeCaptureRequest(frameNumber) != CDKResultSuccess)
                {
                    NT_LOG_ERROR( "Submit realtime pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                    return CDKResultEFailed;
                }
                if (GenerateOfflineCaptureRequest(++frameNumber) != CDKResultSuccess)
                {
                    NT_LOG_ERROR( "Submit offline pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                    return CDKResultEFailed;
                }
                break;
            default:
                NT_LOG_ERROR( "Invalid PipelineConfig provided! %d", m_pipelineConfig);
                break;
            }
        }

        // Set signal flag to flush and notify flushing thread
        SignalFlushThread(SignalFlush);

        // Wait for all results
        if (WaitForResults() != CDKResultSuccess)
        {
            NT_LOG_ERROR( "There are pending buffers not returned by driver after several retries");
            return CDKResultEFailed;
        }

        return CDKResultSuccess;
    }

    /**************************************************************************************************************************
    *   FlushTest::FlushRecover
    *
    *   @brief
    *       Send one capture request, then flush after a short delay. Delay is a configurable parameter, but can also be
    *       overridden by a runtime flag. Expect an error notify and bad buffer status. After, send remaining capture requests
    *       without flushing and expect good buffers back.
    *   @param
    *       None
    *   @return
    *       CDKResult
    **************************************************************************************************************************/
    CDKResult FlushTest::FlushRecover()
    {
        m_bIsFlushTriggered = false;
        uint64_t frameNumber = START_FRAME;

        // Clear notify flag before sending any capture requests
        ClearErrorNotifyFlag(frameNumber);

        // Create and submit one capture request, then flush frame 1 immediately
        switch (m_pipelineConfig)
        {
        case RealtimeConfig:
            if (GenerateRealtimeCaptureRequest(frameNumber) != CDKResultSuccess)
            {
                NT_LOG_ERROR( "Submit realtime pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                return CDKResultEFailed;
            }
            break;
        case OfflineConfig:
            if (GenerateOfflineCaptureRequest(frameNumber) != CDKResultSuccess)
            {
                NT_LOG_ERROR( "Submit offline pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                return CDKResultEFailed;
            }
            break;
        case MixedConfig:
            if (GenerateRealtimeCaptureRequest(frameNumber) != CDKResultSuccess)
            {
                NT_LOG_ERROR( "Submit realtime pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                return CDKResultEFailed;
            }
            if (GenerateOfflineCaptureRequest(++frameNumber) != CDKResultSuccess)
            {
                NT_LOG_ERROR( "Submit offline pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                return CDKResultEFailed;
            }
            break;
        default:
            NT_LOG_ERROR( "Invalid PipelineConfig provided! %d", m_pipelineConfig);
            break;
        }

        // Set signal flag to flush and notify flushing thread
        SignalFlushThread(SignalFlush);

        // Wait for frame 1 to return
        if (WaitForResults() != CDKResultSuccess)
        {
            NT_LOG_ERROR( "Flushed frame 1 result timed out!");
            return CDKResultEFailed;
        }

        // Ensure flush thread is completely done flushing before continuing
        SignalFlushThread(SignalReady);

        // Send remaining frames without flushing
        for (frameNumber += 1; frameNumber <= MAX_REQUESTS; frameNumber++)
        {
            // Clear flush flag and notify flag
            m_bIsFlushTriggered = false;
            ClearErrorNotifyFlag(frameNumber);

            // Create and submit capture request
            switch (m_pipelineConfig)
            {
            case RealtimeConfig:
                if (GenerateRealtimeCaptureRequest(frameNumber) != CDKResultSuccess)
                {
                    NT_LOG_ERROR( "Submit realtime pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                    return CDKResultEFailed;
                }
                break;
            case OfflineConfig:
                if (GenerateOfflineCaptureRequest(frameNumber) != CDKResultSuccess)
                {
                    NT_LOG_ERROR( "Submit offline pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                    return CDKResultEFailed;
                }
                break;
            case MixedConfig:
                if (GenerateRealtimeCaptureRequest(frameNumber) != CDKResultSuccess)
                {
                    NT_LOG_ERROR( "Submit realtime pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                    return CDKResultEFailed;
                }
                if (GenerateOfflineCaptureRequest(++frameNumber) != CDKResultSuccess)
                {
                    NT_LOG_ERROR( "Submit offline pipeline request failed for frameNumber: %" PRIu64, frameNumber);
                    return CDKResultEFailed;
                }
                break;
            default:
                NT_LOG_ERROR( "Invalid PipelineConfig provided! %d", m_pipelineConfig);
                break;
            }
        }

        // Wait for all results
        if (WaitForResults() != CDKResultSuccess)
        {
            NT_LOG_ERROR( "There are pending buffers not returned by driver after several retries");
            return CDKResultEFailed;
        }

        return CDKResultSuccess;
    }

    /**************************************************************************************************************************
    *   FlushTest::TestRealtimeFlush
    *
    *   @brief
    *       Flush test for realtime pipelines
    *   @param
    *       [in]    TestId      testId          Test identifier
    *       [in]    TestType    testType        Test type to perform
    *       [in]    UINT        usFlushDelay    Number of usec to delay flush (default 0)
    *   @return
    *       None
    **************************************************************************************************************************/
    void FlushTest::TestRealtimeFlush(TestId testId, TestType testType, UINT usFlushDelay)
    {
        // Get list of cameras to test
        std::vector <int> camList = m_pChiModule->GetCameraList();

        m_testId = testId;
        m_testType = testType;
        m_pipelineConfig = RealtimeConfig;
        // GetFlushDelay of -1 means user did not set value
        m_usFlushDelay = (CmdLineParser::GetFlushDelay() >= 0) ? CmdLineParser::GetFlushDelay() : usFlushDelay;
        bool isDepthTest = false;

        // Check if test contains ChiDepthNode
        if (m_testId == FlushNodeChiDepthNode    ||
            m_testId == FlushQueueChiDepthNode   ||
            m_testId == FlushRecoverChiDepthNode )
        {
            isDepthTest = true;
        }

        for (size_t camCounter = 0; camCounter < camList.size(); camCounter++)
        {
            // Get the actual camera ID to test
            int cameraId = camList[camCounter];

            // For tests with ChiDepthNode, check that camera can support depth capability
            if (isDepthTest)
            {
                bool bDepthSupported = m_pChiMetadataUtil->CheckAvailableCapability(cameraId, ANDROID_REQUEST_AVAILABLE_CAPABILITIES_DEPTH_OUTPUT);
                if (!bDepthSupported)
                {
                    NT_LOG_UNSUPP( "Depth not supported on camera %d, skipping...", cameraId);
                    continue;
                }
            }

            // Create chistream objects from streamcreatedata
            NT_ASSERT(SetupStreams() == CDKResultSuccess, "Fatal failure at SetupStreams() !");

            ChiSensorModeInfo* testSensorMode = NULL;
            testSensorMode = m_pChiModule->GetClosestSensorMode(cameraId, m_streamInfo.maxRes);

            NT_ASSERT(NULL != testSensorMode, "Sensor mode is NULL for cameraId:%d ",cameraId);

            NT_LOG_INFO( "Camera %d chosen sensor mode: %u, width: %u, height: %u", cameraId,
                testSensorMode->modeIndex, testSensorMode->frameDimension.width, testSensorMode->frameDimension.height);

            // TODO: Set number of batched frames based on usecase
            testSensorMode->batchedFrames = 1;

            // For RDI cases, we need to make sure stream resolution matches sensor mode
            for (int streamIndex = 0; streamIndex < m_numStreams; streamIndex++)
            {
                if (IsRDIStream(m_pRequiredStreams[streamIndex].format))
                {
                    NT_LOG_INFO( "RDI stream found, match resolution to sensormode resolution width: %d, height: %d ",
                        testSensorMode->frameDimension.width, testSensorMode->frameDimension.height);

                    m_pRequiredStreams[streamIndex].width = testSensorMode->frameDimension.width;
                    m_pRequiredStreams[streamIndex].height = testSensorMode->frameDimension.height;
                }
            }

            // Create pipelines
            NT_ASSERT(SetupPipelines(cameraId, testSensorMode) == CDKResultSuccess,"Pipelines Setup failed");

            // Create sessions
            NT_ASSERT(CreateSessions() == CDKResultSuccess, "Necessary sessions could not be created");

            // Initialize buffer manager and metabuffer pools
            NT_ASSERT(InitializeBufferMangers(cameraId) == CDKResultSuccess, "Buffer managers could not be initialized");
#ifndef OLD_METADATA
            NT_ASSERT(m_pChiMetadataUtil->CreateInputMetabufferPool(cameraId, MAX_REQUESTS) == CDKResultSuccess,
                 "Input metabuffer pool for camera Id: %d could not be created!", cameraId);
            NT_ASSERT(m_pChiMetadataUtil->CreateOutputMetabufferPool(MAX_REQUESTS) == CDKResultSuccess,
                 "Output metabuffer pool could not be created!");
#endif // OLD_METADATA

            switch (testType)
            {
            case FlushNodeTest:
                NT_ASSERT(FlushNode() == CDKResultSuccess, "Failure during FlushNode!");
                break;
            case FlushQueueTest:
                NT_ASSERT(FlushQueue() == CDKResultSuccess, "Failure during FlushQueue!");
                break;
            case FlushRecoverTest:
                NT_ASSERT(FlushRecover() == CDKResultSuccess, "Failure during FlushRecover!");
                break;
            default:
                NT_LOG_ERROR( "Invalid TestType provided! %d", testType);
                break;
            }

            // Destroy all resources created
            DestroyResources();
        }
    }

    /**************************************************************************************************************************
    *   FlushTest::TestOfflineFlush
    *
    *   @brief
    *       Flush test for offline pipelines
    *   @param
    *       [in]    TestId      testId          Test identifier
    *       [in]    TestType    testType        Test type to perform
    *       [in]    UINT        usFlushDelay    Number of usec to delay flush (default 0)
    *   @return
    *       None
    **************************************************************************************************************************/
    void FlushTest::TestOfflineFlush(TestId testId, TestType testType, UINT usFlushDelay)
    {
        m_testId = testId;
        m_testType = testType;
        m_pipelineConfig = OfflineConfig;
        // GetFlushDelay of -1 means user did not set value
        m_usFlushDelay = (CmdLineParser::GetFlushDelay() >= 0) ? CmdLineParser::GetFlushDelay() : usFlushDelay;

        int cameraId = 0;
        // For tests with ChiDepthNode, check that device can support depth capability
        if (m_testId == FlushNodeChiDepthNode_offline  ||
            m_testId == FlushQueueChiDepthNode_offline ||
            m_testId == FlushRecoverChiDepthNode_offline)
        {
            bool bDepthSupported = m_pChiMetadataUtil->CheckAvailableCapability(cameraId, ANDROID_REQUEST_AVAILABLE_CAPABILITIES_DEPTH_OUTPUT);
            if (!bDepthSupported)
            {
                NT_LOG_UNSUPP( "Depth capability not supported on device, skipping...");
                return;
            }
        }

        // Create chistream objects from streamcreatedata
        NT_ASSERT(SetupStreams() == CDKResultSuccess, "Fatal failure at SetupStreams() !");

        // Create pipelines - offline pipelines don't require cameraId and sensor mode
        NT_ASSERT(SetupPipelines(0, NULL) == CDKResultSuccess, "Pipelines Setup failed");

        // Create sessions
        NT_ASSERT(CreateSessions() == CDKResultSuccess, "Necessary sessions could not be created");

        // Initialize buffer manager and metabuffer pools
        NT_ASSERT(InitializeBufferMangers(-1) == CDKResultSuccess,"Buffer managers could not be initialized");
#ifndef OLD_METADATA
        NT_ASSERT(m_pChiMetadataUtil->CreateInputMetabufferPool(cameraId, MAX_REQUESTS) == CDKResultSuccess,
             "Input metabuffer pool for camera Id: %d could not be created!", cameraId);
        NT_ASSERT(m_pChiMetadataUtil->CreateOutputMetabufferPool(MAX_REQUESTS) == CDKResultSuccess,
             "Output metabuffer pool could not be created!");
#endif // OLD_METADATA

        switch (testType)
        {
        case FlushNodeTest:
            NT_ASSERT(FlushNode() == CDKResultSuccess, "Failure during FlushNode!");
            break;
        case FlushQueueTest:
            NT_ASSERT(FlushQueue() == CDKResultSuccess,"Failure during FlushQueue!");
            break;
        case FlushRecoverTest:
            NT_ASSERT(FlushRecover() == CDKResultSuccess,"Failure during FlushRecover!");
            break;
        default:
            NT_LOG_ERROR( "Invalid TestType provided! %d", testType);
            break;
        }

        // Destroy all resources created
        DestroyResources();
    }

    /**************************************************************************************************************************
    *   FlushTest::TestMixedFlush
    *
    *   @brief
    *       Flush test for mixed pipelines
    *   @param
    *       [in]    TestId      testId          Test identifier
    *       [in]    TestType    testType        Test type to perform
    *       [in]    UINT        usFlushDelay    Number of usec to delay flush (default 0)
    *   @return
    *       None
    **************************************************************************************************************************/
    void FlushTest::TestMixedFlush(TestId testId, TestType testType, UINT usFlushDelay)
    {
        // Get list of cameras to test
        std::vector <int> camList = m_pChiModule->GetCameraList();

        m_testId = testId;
        m_testType = testType;
        m_pipelineConfig = MixedConfig;
        // GetFlushDelay of -1 means user did not set value
        m_usFlushDelay = (CmdLineParser::GetFlushDelay() >= 0) ? CmdLineParser::GetFlushDelay() : usFlushDelay;

        for (size_t camCounter = 0; camCounter < camList.size(); camCounter++)
        {
            // Get the actual camera ID to test
            int cameraId = camList[camCounter];

            // Create chistream objects from streamcreatedata
            NT_ASSERT(SetupStreams() == CDKResultSuccess, "Fatal failure at SetupStreams() !");

            ChiSensorModeInfo* testSensorMode = NULL;
            testSensorMode = m_pChiModule->GetClosestSensorMode(cameraId, m_streamInfo.maxRes);

            NT_ASSERT(NULL != testSensorMode, "Sensor mode is NULL for cameraId: %d", cameraId);

            NT_LOG_INFO( "Camera %d chosen sensor mode: %u, width: %u, height: %u", cameraId,
                testSensorMode->modeIndex, testSensorMode->frameDimension.width, testSensorMode->frameDimension.height);

            // TODO: Set number of batched frames based on usecase
            testSensorMode->batchedFrames = 1;

            for (int streamIndex = 0; streamIndex < m_numStreams; streamIndex++)
            {
                if (IsRDIStream(m_pRequiredStreams[streamIndex].format))
                {
                    NT_LOG_INFO( "RDI stream found, match resolution to sensormode resolution width: %d, height: %d ",
                        testSensorMode->frameDimension.width, testSensorMode->frameDimension.height);

                    m_pRequiredStreams[streamIndex].width = testSensorMode->frameDimension.width;
                    m_pRequiredStreams[streamIndex].height = testSensorMode->frameDimension.height;
                }
            }

            // Create pipelines
            NT_ASSERT(SetupPipelines(cameraId, testSensorMode) == CDKResultSuccess, "Pipelines Setup failed");

            // Create sessions
            NT_ASSERT(CreateSessions() == CDKResultSuccess, "Necessary sessions could not be created");

            // Initialize buffer manager and metabuffer pools
            NT_ASSERT(InitializeBufferMangers(cameraId) == CDKResultSuccess, "Buffer managers could not be initialized");
#ifndef OLD_METADATA
            NT_ASSERT(m_pChiMetadataUtil->CreateInputMetabufferPool(cameraId, MAX_REQUESTS) == CDKResultSuccess,
                 "Input metabuffer pool for camera Id: %d could not be created!", cameraId);
            NT_ASSERT(m_pChiMetadataUtil->CreateOutputMetabufferPool(MAX_REQUESTS) == CDKResultSuccess,
                 "Output metabuffer pool could not be created!");
#endif // OLD_METADATA

            switch (testType)
            {
            case FlushNodeTest:
                NT_ASSERT(FlushNode() == CDKResultSuccess, "Failure during FlushNode!");
                break;
            case FlushQueueTest:
                NT_ASSERT(FlushQueue() == CDKResultSuccess, "Failure during FlushQueue!");
                break;
            case FlushRecoverTest:
                NT_ASSERT(FlushRecover() == CDKResultSuccess, "Failure during FlushRecover!");
                break;
            default:
                NT_LOG_ERROR( "Invalid TestType provided! %d", testType);
                break;
            }

            //7. Destroy all resources created
            DestroyResources();
        }
    }

} // namespace tests
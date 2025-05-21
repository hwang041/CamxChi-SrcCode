//******************************************************************************
// Copyright (c) 2018-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*******************************************************************************

#include "pip_camera_test.h"

namespace tests
{
    void PIPCameraTest::Setup()
    {
        for (int camEnum = CamA; camEnum < CamMax; camEnum++)
        {
            m_streamInfo[camEnum].streamIds = m_streamId[camEnum];
            m_streamInfo[camEnum].directions = reinterpret_cast<camera3_stream_type_t*>(m_direction[camEnum]);
            m_streamInfo[camEnum].formats = reinterpret_cast<android_pixel_format_t*>(m_format[camEnum]);
            m_streamInfo[camEnum].resolutions = m_resolution[camEnum];
            m_streamInfo[camEnum].usageFlags = m_usageFlag[camEnum];
            m_streamInfo[camEnum].isRealtime = m_isRealtime[camEnum];
            m_streamInfo[camEnum].isJpeg = true;
            m_streamInfo[camEnum].filename = nullptr;

            m_numStreams[camEnum] = 0;
            m_streamBufferMap[camEnum].clear();
            m_streamIdMap[camEnum].clear();
        }

        ChiTestCase::Setup();
    }

    /**************************************************************************************************************************
    *   PIPCameraTest::SetupStreamsForCamera()
    *
    *   @brief
    *       Overridden function implementation which defines the stream information based on the test Id
    *   @param
    *       CamEnum enum of the camera we want to Setup streams for (not to be confused with a camera index)
    *   @return
    *       CDKResult success if stream objects could be created or failure
    **************************************************************************************************************************/
    CDKResult PIPCameraTest::SetupStreamsForCamera(CamEnum camEnum)
    {
        CDKResult result = CDKResultSuccess;
        int streamIndex = 0;
        Size stillRes;

        switch (m_testId)
        {
        case TestStillPreview:
        case TestStillCapture:
            stillRes = (m_testId == TestStillPreview) ? HD : FULLHD;

            //1. IPE Display (A)
            m_resolution[camEnum][streamIndex] = stillRes;
            m_direction[camEnum][streamIndex]  = ChiStreamTypeOutput;
            m_format[camEnum][streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[camEnum][streamIndex]   = IPEOutputPortDisplay;
            streamIndex++;

            if (camEnum == CamA)
            {
                //2. IFE FD (C)
                m_resolution[camEnum][streamIndex] = stillRes;
                m_direction[camEnum][streamIndex]  = ChiStreamTypeOutput;
                m_format[camEnum][streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[camEnum][streamIndex]   = IFEOutputPortFD;
                streamIndex++;
            }

            //3. IFE Stats IHIST
            m_resolution[camEnum][streamIndex] = Size(2048, 1);
            m_direction[camEnum][streamIndex] = ChiStreamTypeOutput;
            m_format[camEnum][streamIndex] = ChiStreamFormatBlob;
            m_streamId[camEnum][streamIndex] = IFEOutputPortStatsIHIST;
            streamIndex++;

            //4. IFE RDI0
            m_resolution[camEnum][streamIndex] = UHD;
            m_direction[camEnum][streamIndex]  = ChiStreamTypeOutput;
            m_format[camEnum][streamIndex]     = ChiStreamFormatRaw16;
            m_streamId[camEnum][streamIndex]   = IFEOutputPortRDI0;
            streamIndex++;

            //5. IFE RDI1
            m_resolution[camEnum][streamIndex] = UHD;
            m_direction[camEnum][streamIndex]  = ChiStreamTypeOutput;
            m_format[camEnum][streamIndex]     = ChiStreamFormatRaw16;
            m_streamId[camEnum][streamIndex]   = IFEOutputPortRDI1;

            m_numStreams[camEnum] = streamIndex + 1;
            m_streamInfo[camEnum].num_streams = m_numStreams[camEnum];
            break;
        case TestVideo:
            if (camEnum == CamA)
            {
                //1. IPE Display (A)
                m_resolution[camEnum][streamIndex] = FULLHD_ALT;
                m_direction[camEnum][streamIndex] = ChiStreamTypeOutput;
                m_format[camEnum][streamIndex] = ChiStreamFormatYCbCr420_888;
                m_streamId[camEnum][streamIndex] = IPEOutputPortDisplay;
                streamIndex++;

                //2. IPE Video (B)
                m_resolution[camEnum][streamIndex] = FULLHD_ALT;
                m_direction[camEnum][streamIndex] = ChiStreamTypeOutput;
                m_format[camEnum][streamIndex] = ChiStreamFormatYCbCr420_888;
                m_streamId[camEnum][streamIndex] = IPEOutputPortVideo;
                streamIndex++;

                //3. IFE FD (C)
                m_resolution[camEnum][streamIndex] = FULLHD_ALT;
                m_direction[camEnum][streamIndex] = ChiStreamTypeOutput;
                m_format[camEnum][streamIndex] = ChiStreamFormatYCbCr420_888;
                m_streamId[camEnum][streamIndex] = IFEOutputPortFD;
                streamIndex++;

                //4. IFE Stats IHIST
                m_resolution[camEnum][streamIndex] = Size(2048, 1);
                m_direction[camEnum][streamIndex] = ChiStreamTypeOutput;
                m_format[camEnum][streamIndex] = ChiStreamFormatBlob;
                m_streamId[camEnum][streamIndex] = IFEOutputPortStatsIHIST;
                streamIndex++;
            }

            //5. IFE RDI1
            m_resolution[camEnum][streamIndex] = UHD;
            m_direction[camEnum][streamIndex] = ChiStreamTypeOutput;
            m_format[camEnum][streamIndex] = ChiStreamFormatRaw16;
            m_streamId[camEnum][streamIndex] = IFEOutputPortRDI1;

            m_streamInfo[camEnum].isJpeg = false;
            m_numStreams[camEnum] = streamIndex + 1;
            m_streamInfo[camEnum].num_streams = m_numStreams[camEnum];
            break;
        default:
            NT_LOG_ERROR( "Unknown testcase Id provided: [%d]", m_testId);
            result = CDKResultENoSuch;
            break;
        }

        if (m_streamInfo[camEnum].num_streams <= 0) {
            NT_LOG_ERROR("Number of streams should be greater than 0, given: %d", m_streamInfo[camEnum].num_streams);
            result = CDKResultEFailed;
        }

        if (result == CDKResultSuccess)
        {
            m_pRequiredStreams[camEnum] = SAFE_NEW() CHISTREAM[m_streamInfo[camEnum].num_streams];
            if (NULL == m_pRequiredStreams[camEnum])
            {
                NT_LOG_ERROR("Failed to initialize CHI streams");
                result = CDKResultEFailed;
            }
            else
            {
                camera3_stream_t* pCamStreams = CreateStreams(m_streamInfo[camEnum]);
                if (nullptr == pCamStreams)
                {
                    NT_LOG_ERROR("Failed to created streams");
                    result = CDKResultEFailed;
                }
                else
                {
                    ConvertCamera3StreamToChiStream(pCamStreams, m_pRequiredStreams[camEnum], m_streamInfo[camEnum].num_streams);
                    delete[] pCamStreams;   // No longer needed, converted to m_pRequiredStreams

                    if (m_pRequiredStreams[camEnum] == nullptr)
                    {
                        NT_LOG_ERROR("Provided streams could not be configured for testcase Id: [%d]", m_testId);
                        result = CDKResultEFailed;
                    }
                    else
                    {
                        for (int index = 0; index < m_numStreams[camEnum]; index++)
                        {
                            m_isRealtime[camEnum][index] = true;
                            m_streamIdMap[camEnum][m_streamInfo[camEnum].streamIds[index]] = &m_pRequiredStreams[camEnum][index];
                        }
                        if (m_streamIdMap[camEnum].size() != static_cast<size_t>(m_numStreams[camEnum]))
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
    *   PIPCameraTest::SetupPIPCameraPipelines()
    *
    *   @brief
    *       Creates pipeline objects for PIP cameras based on the test Id
    *   @param
    *       [in]  int                   cameraIdA       camera index to be associated with the pipeline for camera A
    *       [in]  int                   cameraIdB       camera index to be associated with the pipeline for camera B
    *       [in]  ChiSensorModeInfo*    sensorModeCamA  sensor mode for camera A
    *       [in]  ChiSensorModeInfo*    sensorModeCamB  sensor mode for camera B
    *   @return
    *       CDKResult success if pipelines could be created or failure
    **************************************************************************************************************************/
    CDKResult PIPCameraTest::SetupPIPCameraPipelines(
        int cameraIdA,
        int cameraIdB,
        ChiSensorModeInfo * sensorModeCamA,
        ChiSensorModeInfo * sensorModeCamB)
    {
        CDKResult result = CDKResultSuccess;
        switch (m_testId)
        {
        case TestStillPreview:
        case TestStillCapture:
            m_pChiPipeline[CamA] = ChiPipeline::Create(cameraIdA, sensorModeCamA, m_streamIdMap[CamA], PipelineType::RealtimeIPEACStatsRDI);
            m_pChiPipeline[CamB] = ChiPipeline::Create(cameraIdB, sensorModeCamB, m_streamIdMap[CamB], PipelineType::RealtimeIPEAStatsRDI);
            break;
        case TestVideo:
            m_pChiPipeline[CamA] = ChiPipeline::Create(cameraIdA, sensorModeCamA, m_streamIdMap[CamA], PipelineType::RealtimeIPEABCStatsRDI);
            m_pChiPipeline[CamB] = ChiPipeline::Create(cameraIdB, sensorModeCamB, m_streamIdMap[CamB], PipelineType::RealtimeRDI1Only);
            break;
        default:
            NT_LOG_ERROR( "Unknown testcase Id provided: [%d]", m_testId);
            return CDKResultENoSuch;
        }

        result = (m_pChiPipeline[CamA] != nullptr) ? m_pChiPipeline[CamA]->CreatePipelineDesc() : CDKResultEInvalidPointer;
        result |= (m_pChiPipeline[CamB] != nullptr) ? m_pChiPipeline[CamB]->CreatePipelineDesc() : CDKResultEInvalidPointer;
        return result;
    }

    /**************************************************************************************************************************
    *   PIPCameraTest::CreateSessions()
    *
    *   @brief
    *       Overridden function implementation which creates required number of sessions based on the test Id
    *   @param
    *       None
    *   @return
    *       CDKResult success if sessions could be created or failure
    **************************************************************************************************************************/
    CDKResult PIPCameraTest::CreateSessions()
    {
        CDKResult result = CDKResultSuccess;
        ChiCallBacks callbacks = { 0 };

        callbacks.ChiNotify                      = ChiTestCase::ProcessMessage;
        callbacks.ChiProcessCaptureResult        = ChiTestCase::QueueCaptureResult;
        callbacks.ChiProcessPartialCaptureResult = ChiTestCase::QueuePartialCaptureResult;

        m_perSessionPvtData.pTestInstance = this;
        m_perSessionPvtData.sessionId = RealtimeSession;

        m_pChiSession = ChiSession::Create(m_pChiPipeline,
            CamMax,
            &callbacks,
            &m_perSessionPvtData);

        if (m_pChiSession == nullptr)
        {
            NT_LOG_ERROR( "PIP camera realtime session could not be created");
            result = CDKResultEFailed;
        }
        else
        {
            result = m_pChiPipeline[CamA]->ActivatePipeline(m_pChiSession->GetSessionHandle());
#ifndef OLD_METADATA
            if (result == CDKResultSuccess)
            {
                result = m_pChiMetadataUtil->GetPipelineinfo(m_pChiModule->GetContext(),
                    m_pChiSession->GetSessionHandle(), m_pChiPipeline[CamA]->GetPipelineHandle(), &m_pPipelineMetadataInfo);
            }
#endif // OLD_METADATA

            result |= m_pChiPipeline[CamB]->ActivatePipeline(m_pChiSession->GetSessionHandle());
#ifndef OLD_METADATA
            if (result == CDKResultSuccess)
            {
                result = m_pChiMetadataUtil->GetPipelineinfo(m_pChiModule->GetContext(),
                    m_pChiSession->GetSessionHandle(), m_pChiPipeline[CamB]->GetPipelineHandle(), &m_pPipelineMetadataInfo);
            }
#endif // OLD_METADATA
        }
        return result;
    }

    /**************************************************************************************************************************
    *   PIPCameraTest::CommonProcessCaptureResult()
    *
    *   @brief
    *       Overridden function implementation which processes the capture result obtained from driver
    *   @param
    *        [in]  CHICAPTURERESULT*     pCaptureResult         pointer to capture result
    *        [in]  void*                 pPrivateCallbackData   pointer private callback data
    *   @return
    *       None
    **************************************************************************************************************************/
    void PIPCameraTest::CommonProcessCaptureResult(
        ChiCaptureResult * pCaptureResult,
        SessionPrivateData * pSessionPrivateData)
    {
        CDKResult result = CDKResultSuccess;
        uint32_t  resultFrameNum = pCaptureResult->frameworkFrameNum;
        uint32_t  numOutputBuffers = pCaptureResult->numOutputBuffers;
        uint32_t  numPartialMetadata = pCaptureResult->numPartialMetadata;
        SessionId sessionId = static_cast<SessionId>(pSessionPrivateData->sessionId);

#ifndef OLD_METADATA
        if (m_pChiMetadataUtil != nullptr)
        {
            m_pChiMetadataUtil->VerifyCaptureResultMetadata(static_cast<CHIMETAHANDLE>(pCaptureResult->pOutputMetadata));
        }
#endif // OLD_METADATA

        // Determine camera A or B from frame number (CamA odd, CamB even)
        CamEnum camEnum = (resultFrameNum % 2 == 1) ? CamA : CamB;
        const char* camString = (camEnum == CamA) ? "A" : "B";

        if (sessionId == RealtimeSession)
        {
            for (uint32_t bufferIndex = 0; bufferIndex < numOutputBuffers; bufferIndex++)
            {
                BufferManager::NativeChiBuffer* outBuffer = const_cast<BufferManager::NativeChiBuffer*>(&pCaptureResult->
                    pOutputBuffers[bufferIndex]);
                BufferManager* manager = m_streamBufferMap[camEnum][outBuffer->pStream];
                if (manager == nullptr)
                {
                    NT_LOG_ERROR( "Could not find buffer manger for camera: %s, given stream: %p, frame: %d",
                        camString, outBuffer->pStream, resultFrameNum);
                    result |= CDKResultEInvalidPointer;
                }
                else
                {
                    bool isSnapshotStream = (outBuffer->pStream == m_streamIdMap[camEnum][IFEOutputPortRDI0] ||
                        outBuffer->pStream == m_streamIdMap[camEnum][IFEOutputPortRDI1]);
                    bool isBlobStream = (outBuffer->pStream->format == ChiStreamFormatBlob);
                    // Only dump blob (stats) or raw snapshot streams every 5th frame
                    bool dump = ((isBlobStream || isSnapshotStream) && resultFrameNum % 5 != 0) ? false : true;

                    BufferManager::GenericBuffer genericBuffer(outBuffer);
                    result |= manager->ProcessBufferFromResult(resultFrameNum, &genericBuffer, dump);
                }
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
            NT_LOG_DEBUG( "Number of pending buffers remaining after receiving the result: %d", GetPendingBufferCount());
        }
    }

    /**************************************************************************************************************************
    *   PIPCameraTest::DestroyResources()
    *
    *   @brief
    *       Overridden function implementation which destroys all created resources / objects
    *   @param
    *       None
    *   @return
    *       None
    **************************************************************************************************************************/
    void PIPCameraTest::DestroyResources()
    {
        if (m_pChiPipeline[CamA] != nullptr)
        {
            m_pChiPipeline[CamA]->DeactivatePipeline(m_pChiSession->GetSessionHandle());
        }
        if (m_pChiPipeline[CamB] != nullptr)
        {
            m_pChiPipeline[CamB]->DeactivatePipeline(m_pChiSession->GetSessionHandle());
        }

        if (m_pChiSession != nullptr)
        {
            m_pChiSession->DestroySession();
            m_pChiSession = nullptr;
        }

        if (m_pChiPipeline[CamA] != nullptr)
        {
            m_pChiPipeline[CamA]->DestroyPipeline();
            m_pChiPipeline[CamA] = nullptr;
        }
        if (m_pChiPipeline[CamB] != nullptr)
        {
            m_pChiPipeline[CamB]->DestroyPipeline();
            m_pChiPipeline[CamB] = nullptr;
        }

        // Destroy required streams and buffer managers for camera A and B
        for (int camEnum = CamA; camEnum < CamMax; camEnum++)
        {
            for (int streamIndex = 0; streamIndex < m_numStreams[camEnum]; streamIndex++)
            {
                if (m_streamBufferMap[camEnum].find(&m_pRequiredStreams[camEnum][streamIndex]) != m_streamBufferMap[camEnum].end())
                {
                    BufferManager* manager = m_streamBufferMap[camEnum].at(&m_pRequiredStreams[camEnum][streamIndex]);

                    if (manager != nullptr)
                    {
                        manager->DestroyBuffers();
                        m_streamBufferMap[camEnum].erase(&m_pRequiredStreams[camEnum][streamIndex]);
                    }
                }
            }

            NT_EXPECT(m_streamBufferMap[camEnum].empty(), "There are still pending buffermanagers not freed!");

            if (m_pRequiredStreams[camEnum] != nullptr)
            {
                delete[] m_pRequiredStreams[camEnum];
                m_pRequiredStreams[camEnum] = nullptr;
            }

            m_streamIdMap[camEnum].clear();
            m_numStreams[camEnum] = 0;
        }

        DestroyCommonResources();
    }

    /**************************************************************************************************************************
    *   PIPCameraTest::InitializeBufferMangers
    *
    *   @brief
    *       Initializes buffer manager for each required stream
    *   @param
    *       [in]    CamEnum     camEnum     camera enum
    *       [in]    int         cameraId    Id that corresponds to camera enum
    *   @return
    *       CDKResult success if buffer manager could be created / failure
    **************************************************************************************************************************/
    CDKResult PIPCameraTest::InitializeBufferMangers(CamEnum camEnum, int cameraId)
    {
        CDKResult result = CDKResultSuccess;

        if (m_numStreams[camEnum] <= 0)
        {
            NT_LOG_ERROR( "Cannot create buffermanagers with stream count: %d", m_numStreams[camEnum]);
            result = CDKResultENeedMore;
        }

        if (result == CDKResultSuccess)
        {
            for (int streamIndex = 0; streamIndex < m_numStreams[camEnum]; streamIndex++)
            {
                BufferManager::NativeChiStream* currentStream = &m_pRequiredStreams[camEnum][streamIndex];
                BufferManager::GenericStream genericStream(currentStream);

                BufferManager* manager = SAFE_NEW() ChiBufferManager(m_streamId[camEnum][streamIndex]);

                m_pBufferManagers[camEnum][streamIndex] = manager->Initialize(
                    cameraId,
                    &genericStream,
                    m_streamInfo[camEnum].streamIds[streamIndex],
                    m_streamInfo[camEnum].filename);

                if (m_pBufferManagers[camEnum][streamIndex] == nullptr)
                {
                    NT_LOG_ERROR( "Failed to allocate memory for buffer manager for stream index: %d", streamIndex);
                    result = CDKResultENoMemory;
                    break;
                }

                m_streamBufferMap[camEnum][currentStream] = m_pBufferManagers[camEnum][streamIndex];
            }
        }

        return result;
    }

    /**************************************************************************************************************************
    *   PIPCameraTest::GeneratePIPCaptureRequest()
    *
    *   @brief
    *       Generate a PIP camera pipeline request
    *   @param
    *       [in] uint64_t   frameNumA   frame number for camera A (expect always odd)
    *       [in] uint64_t   frameNumB   frame number for camera B (expect always even)
    *   @return
    *       CDKResult success if request could be submitted or failure
    **************************************************************************************************************************/
    CDKResult PIPCameraTest::GeneratePIPCaptureRequest(uint64_t frameNumA, uint64_t frameNumB)
    {
        CDKResult result = CDKResultSuccess;
        static const uint32_t NumOutBufCamA = m_numStreams[CamA];
        static const uint32_t NumOutBufCamB = m_numStreams[CamB];
        BufferManager::NativeChiBuffer* outputBuffersCamA = SAFE_NEW() BufferManager::NativeChiBuffer[NumOutBufCamA];
        BufferManager::NativeChiBuffer* outputBuffersCamB = SAFE_NEW() BufferManager::NativeChiBuffer[NumOutBufCamB];

        // Issue warnings if frame numbers are not as expected
        if (frameNumA % 2 == 0)
        {
            NT_LOG_WARN( "Frame number for camera A is not odd (%d) as expected!", frameNumA);
        }
        if (frameNumB % 2 == 1)
        {
            NT_LOG_WARN( "Frame number for camera B is not even (%d) as expected!", frameNumB);
        }

        uint32_t requestId = FRAME_REQUEST_MOD(frameNumA);
        memset(&m_pipCamRequest[CamA][requestId], 0, sizeof(CHICAPTUREREQUEST));
        memset(&m_pipCamRequest[CamB][requestId], 0, sizeof(CHICAPTUREREQUEST));

        std::map<BufferManager::NativeChiStream*, BufferManager*>::iterator it;
        uint32_t outputIndex;

        // Prep output buffers for camera A
        for (it = m_streamBufferMap[CamA].begin(), outputIndex = 0; it != m_streamBufferMap[CamA].end(); ++it, outputIndex++)
        {
            BufferManager* manager = it->second;
            void* buffer = manager->GetOutputBufferForRequest();
            if (buffer == nullptr)
            {
                delete[] outputBuffersCamA;
                delete[] outputBuffersCamB;
                return CDKResultENoMore;
            }

            outputBuffersCamA[outputIndex] = *static_cast<BufferManager::NativeChiBuffer*>(buffer);
        }

        // Prep output buffers for camera B
        for (it = m_streamBufferMap[CamB].begin(), outputIndex = 0; it != m_streamBufferMap[CamB].end(); ++it, outputIndex++)
        {
            BufferManager* manager = it->second;
            void* buffer = manager->GetOutputBufferForRequest();
            if (buffer == nullptr)
            {
                delete[] outputBuffersCamA;
                delete[] outputBuffersCamB;
                return CDKResultENoMore;
            }

            outputBuffersCamB[outputIndex] = *static_cast<BufferManager::NativeChiBuffer*>(buffer);
        }

        // Create camera A capture request
        m_pipCamRequest[CamA][requestId].frameNumber      = frameNumA;
        m_pipCamRequest[CamA][requestId].hPipelineHandle  = m_pChiPipeline[CamA]->GetPipelineHandle();
        m_pipCamRequest[CamA][requestId].numOutputs       = NumOutBufCamA;
        m_pipCamRequest[CamA][requestId].pOutputBuffers   = outputBuffersCamA;
        m_pipCamRequest[CamA][requestId].pPrivData        = &m_requestPvtData[CamA];

#ifdef OLD_METADATA
        m_pipCamRequest[CamA][requestId].pMetadata = allocate_camera_metadata(METADATA_ENTRIES, 100 * 1024);
        NATIVETEST_UNUSED_PARAM(m_pPipelineMetadataInfo);
#else
        // Get the input metabuffer from the pool
        m_pipCamRequest[CamA][requestId].pInputMetadata = m_pChiMetadataUtil->GetInputMetabufferFromPool(requestId + CamA);
        NT_EXPECT(m_pipCamRequest[CamA][requestId].pInputMetadata != nullptr, "Failed to create Input Metabuffer before sending request");

        // Get the output metabuffer from the pool
        m_pipCamRequest[CamA][requestId].pOutputMetadata = m_pChiMetadataUtil->GetOutputMetabufferFromPool(requestId + CamA,
            m_pPipelineMetadataInfo.publishTagArray, m_pPipelineMetadataInfo.publishTagCount);
        NT_EXPECT(m_pipCamRequest[CamA][requestId].pOutputMetadata != nullptr, "Failed to create Output Metabuffer before sending request");
#endif // OLD_METADATA

        // Create camera B capture request
        m_pipCamRequest[CamB][requestId].frameNumber      = frameNumB;
        m_pipCamRequest[CamB][requestId].hPipelineHandle  = m_pChiPipeline[CamB]->GetPipelineHandle();
        m_pipCamRequest[CamB][requestId].numOutputs       = NumOutBufCamB;
        m_pipCamRequest[CamB][requestId].pOutputBuffers   = outputBuffersCamB;
        m_pipCamRequest[CamB][requestId].pPrivData        = &m_requestPvtData[CamB];

#ifdef OLD_METADATA
        m_pipCamRequest[CamB][requestId].pMetadata        = allocate_camera_metadata(METADATA_ENTRIES, 100 * 1024);
#else
        // Get the input metabuffer from the pool
        m_pipCamRequest[CamB][requestId].pInputMetadata = m_pChiMetadataUtil->GetInputMetabufferFromPool(requestId + CamB);
        NT_EXPECT(m_pipCamRequest[CamB][requestId].pInputMetadata != nullptr, "Failed to create Input Metabuffer before sending request");

        // Get the output metabuffer from the pool
        m_pipCamRequest[CamB][requestId].pOutputMetadata = m_pChiMetadataUtil->GetOutputMetabufferFromPool(requestId + CamB,
            m_pPipelineMetadataInfo.publishTagArray, m_pPipelineMetadataInfo.publishTagCount);
        NT_EXPECT(m_pipCamRequest[CamB][requestId].pOutputMetadata != nullptr, "Failed to create Output Metabuffer before sending request");
#endif // OLD_METADATA

        memset(&m_submitRequest, 0, sizeof(CHIPIPELINEREQUEST));
        m_submitRequest.pSessionHandle = m_pChiSession->GetSessionHandle();
        m_submitRequest.numRequests = 2;
        m_submitRequest.pCaptureRequests = &m_pipCamRequest[CamA][requestId];

        AtomicIncrement(NumOutBufCamA);
        AtomicIncrement(NumOutBufCamB);

        NT_LOG_DEBUG( "Number of pending buffers remaining: %d after sending request: (%" PRIu64 ", %" PRIu64 ")",
            GetPendingBufferCount(), frameNumA, frameNumB);

        if (result == CDKResultSuccess)
        {
            result = m_pChiModule->SubmitPipelineRequest(&m_submitRequest);
        }

        delete[] outputBuffersCamA;
        delete[] outputBuffersCamB;
        return result;
    }

    /**************************************************************************************************************************
    *   PIPCameraTest::TestPIPCamera
    *
    *   @brief
    *       Test multiple realtime pipelines (multiple sessions) involving Sensor+IFE or Sensor+IFE+IPE depending on pipelineType
    *   @param
    *       [in] TestType             testType       Test identifier
    *   @return
    *       None
    **************************************************************************************************************************/
    void PIPCameraTest::TestPIPCamera(TestId testType)
    {
        int numOfCameras = m_pChiModule->GetNumberCameras();
        NT_ASSERT(numOfCameras > 1, "PIP camera test requires at least 2 cameras. Device reported %d cameras!", numOfCameras); 

        m_testId = testType;

        // Step over available cameras, testing two at a time with all possible combinations [(0,1), (0,2), (1,2), ...])
        for (int cameraIdA = 0; cameraIdA+1 < numOfCameras; cameraIdA++)
        {
            for (int cameraIdB = cameraIdA+1; cameraIdB < numOfCameras; cameraIdB++)
            {
                NT_LOG_INFO( "Testing PIP cameras: CamA %d, CamB %d", cameraIdA, cameraIdB);

                //1. Create chistream objects from streamcreatedata
                NT_ASSERT(SetupStreamsForCamera(CamA) == CDKResultSuccess,"Fatal failure at SetupStreamsForCamera(CamA).");
                NT_ASSERT(SetupStreamsForCamera(CamB) == CDKResultSuccess,"Fatal failure at SetupStreamsForCamera(CamB).");

                ChiSensorModeInfo* testSensorModeCamA = nullptr;
                ChiSensorModeInfo* testSensorModeCamB = nullptr;
                testSensorModeCamA = m_pChiModule->GetClosestSensorMode(cameraIdA, m_streamInfo[CamA].maxRes);
                testSensorModeCamB = m_pChiModule->GetClosestSensorMode(cameraIdB, m_streamInfo[CamB].maxRes);

                NT_ASSERT(testSensorModeCamA != nullptr,"Sensor mode is NULL for camera Id: %d", cameraIdA);
                NT_ASSERT(testSensorModeCamB != nullptr,"Sensor mode is NULL for camera Id: %d", cameraIdB);

                NT_LOG_INFO( "Camera %d chosen sensor mode: %u, width: %u, height: %u", cameraIdA,
                    testSensorModeCamA->modeIndex, testSensorModeCamA->frameDimension.width, testSensorModeCamA->frameDimension.height);
                NT_LOG_INFO( "Camera %d chosen sensor mode: %u, width: %u, height: %u", cameraIdB,
                    testSensorModeCamB->modeIndex, testSensorModeCamB->frameDimension.width, testSensorModeCamB->frameDimension.height);

                // TODO: Set number of batched frames based on usecase
                testSensorModeCamA->batchedFrames = 1;
                testSensorModeCamB->batchedFrames = 1;

                // For RDI cases, we need to make sure stream resolution matches sensor mode
                // Check RDI for camera A
                for (int streamIndex = 0; streamIndex < m_numStreams[CamA]; streamIndex++)
                {
                    if (IsRDIStream(m_pRequiredStreams[CamA][streamIndex].format))
                    {
                        NT_LOG_INFO( "Camera %d RDI stream found, match resolution to sensormode resolution width: %u, height: %u ",
                            cameraIdA, testSensorModeCamA->frameDimension.width, testSensorModeCamA->frameDimension.height);

                        m_pRequiredStreams[CamA][streamIndex].width = testSensorModeCamA->frameDimension.width;
                        m_pRequiredStreams[CamA][streamIndex].height = testSensorModeCamA->frameDimension.height;
                    }
                }

                // Check RDI for camera B
                for (int streamIndex = 0; streamIndex < m_numStreams[CamB]; streamIndex++)
                {
                    if (IsRDIStream(m_pRequiredStreams[CamB][streamIndex].format))
                    {
                        NT_LOG_INFO( "Camera %d RDI stream found, match resolution to sensormode resolution width: %u, height: %u ",
                            cameraIdB, testSensorModeCamB->frameDimension.width, testSensorModeCamB->frameDimension.height);

                        m_pRequiredStreams[CamB][streamIndex].width = testSensorModeCamB->frameDimension.width;
                        m_pRequiredStreams[CamB][streamIndex].height = testSensorModeCamB->frameDimension.height;
                    }
                }

                //2. Create PIP camera pipelines
                NT_ASSERT(SetupPIPCameraPipelines(cameraIdA, cameraIdB, testSensorModeCamA, testSensorModeCamB) == CDKResultSuccess,"Pipelines Setup failed");

                //3. Create sessions
                NT_ASSERT(CreateSessions() == CDKResultSuccess,"Necessary sessions could not be created");

                //4. Initialize buffer manager and metabuffer pools
                NT_ASSERT(InitializeBufferMangers(CamA, cameraIdA) == CDKResultSuccess, "Buffer managers for camera A could not be initialized!");
                NT_ASSERT(InitializeBufferMangers(CamB, cameraIdB) == CDKResultSuccess, "Buffer managers for camera B could not be initialized!");
#ifndef OLD_METADATA
                NT_ASSERT(m_pChiMetadataUtil->CreateInputMetabufferPool(cameraIdB, MAX_REQUESTS) == CDKResultSuccess
                    ,"Input metabuffer pool for camera Id: %d could not be created!", cameraIdB);
                NT_ASSERT(m_pChiMetadataUtil->CreateInputMetabufferPool(cameraIdA, MAX_REQUESTS) == CDKResultSuccess
                    ,"Input metabuffer pool for camera Id: %d could not be created!", cameraIdA);
                NT_ASSERT(m_pChiMetadataUtil->CreateOutputMetabufferPool(MAX_REQUESTS) == CDKResultSuccess
                    ,"Output metabuffer pool could not be created!");
                //// @todo: In case of PIP Camera, is there a need for output meta buffer pool separately for each camera?
#endif // OLD_METADATA

                //5. Create and submit capture requests
                uint64_t frameNumCamA = (START_FRAME % 2) == 1 ? START_FRAME : START_FRAME + 1;  // Camera A frames should always be odd
                uint64_t frameNumCamB = frameNumCamA + 1;  // Camera B frames should always be even
                for (int frameIndex = 1; frameIndex <= CmdLineParser::GetFrameCount(); frameIndex++)
                {
                    NT_ASSERT(GeneratePIPCaptureRequest(frameNumCamA, frameNumCamB) == CDKResultSuccess,
                        "Submit pipeline request failed for PIP capture frames (%d,%d)", frameNumCamA, frameNumCamB);
                    frameNumCamA += 2;
                    frameNumCamB += 2;
                }

                //6. Wait for all results
                NT_ASSERT(WaitForResults() == CDKResultSuccess,
                    "There are pending buffers not returned by driver after several retries");

                //7. Destroy all resources created
                DestroyResources();
            }
        }
    }

} // namespace tests

//*****************************************************************************************************************************
// Copyright (c) 2018-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*****************************************************************************************************************************

#ifndef __FLUSH_TEST__
#define __FLUSH_TEST__

#include "chitestcase.h"

namespace tests
{

    class FlushTest : public ChiTestCase
    {

    public:

        enum TestId
        {
            /* Realtime Tests */
            FlushNodeIFE,
            FlushQueueIFE,
            FlushRecoverIFE,
            FlushNodeStats3A,
            FlushQueueStats3A,
            FlushRecoverStats3A,
            FlushNodeChiDepthNode,
            FlushQueueChiDepthNode,
            FlushRecoverChiDepthNode,
            FlushNodeChiExternalNode,
            FlushQueueChiExternalNode,
            FlushRecoverChiExternalNode,
            FlushNodeChiGPUNode,
            FlushQueueChiGPUNode,
            FlushRecoverChiGPUNode,
            FlushNodeCustomNode,
            FlushQueueCustomNode,
            FlushRecoverCustomNode,
            FlushNodeBypassNode,
            FlushQueueBypassNode,
            FlushRecoverBypassNode,
            FlushNodeInplaceNode,
            FlushQueueInplaceNode,
            FlushRecoverInplaceNode,
            FlushNodeIPEJpeg,
            FlushQueueIPEJpeg,
            FlushRecoverIPEJpeg,
            FlushNodeBPSIPEJpeg,
            FlushQueueBPSIPEJpeg,
            FlushRecoverBPSIPEJpeg,
            FlushNodeFD,
            FlushQueueFD,
            FlushRecoverFD,

            /* Offline Tests */
            FlushNodeIPE_offline,
            FlushQueueIPE_offline,
            FlushRecoverIPE_offline,
            FlushNodeBPS_IPE_offline,
            FlushQueueBPS_IPE_offline,
            FlushRecoverBPS_IPE_offline,
            FlushNodeBPS_IPE_offline_2Streams,
            FlushQueueBPS_IPE_offline_2Streams,
            FlushRecoverBPS_IPE_offline_2Streams,
            FlushNodeChiExternalNode_offline,
            FlushQueueChiExternalNode_offline,
            FlushRecoverChiExternalNode_offline,
            FlushNodeChiExternalNodeJpeg_offline,
            FlushQueueChiExternalNodeJpeg_offline,
            FlushRecoverChiExternalNodeJpeg_offline,
            FlushNodeBPS_IPE_JPEG_offline,
            FlushQueueBPS_IPE_JPEG_offline,
            FlushRecoverBPS_IPE_JPEG_offline,
            FlushNodeFD_offline,
            FlushQueueFD_offline,
            FlushRecoverFD_offline,
            FlushNodeChiDepthNode_offline,
            FlushQueueChiDepthNode_offline,
            FlushRecoverChiDepthNode_offline,
            FlushNode4Streams,
            FlushQueue4Streams,
            FlushRecover4Streams,

            /* Mixed Tests */
            FlushNode3Streams,
            FlushQueue3Streams,
            FlushRecover3Streams,
            FlushNodeLRME_RANSAC,
            FlushQueueLRME_RANSAC,
            FlushRecoverLRME_RANSAC,
            FlushNode5Streams,
            FlushQueue5Streams,
            FlushRecover5Streams,
            FlushNumOfTests
        };

        enum TestType
        {
            FlushNodeTest,
            FlushQueueTest,
            FlushRecoverTest
        };

        virtual VOID  Setup();
        virtual VOID  Teardown();

        void TestRealtimeFlush(TestId testId, TestType testType, UINT usFlushDelay = 0);
        void TestOfflineFlush(TestId testId, TestType testType, UINT usFlushDelay = 0);
        void TestMixedFlush(TestId testId, TestType testType, UINT usFlushDelay = 0);

        FlushTest() = default;
        ~FlushTest() = default;

    protected:

        CDKResult SetupStreams() override;
        CDKResult SetupPipelines(int cameraId, ChiSensorModeInfo* sensorMode) override;
        CDKResult CreateSessions() override;
        void      CommonProcessCaptureResult(ChiCaptureResult* pCaptureResult, SessionPrivateData* pSessionPrivateData) override;
        void      SetSpecialMetadata(uint64_t frameNumber, CHIMETAHANDLE pInputMetadata);
        CDKResult ValidateCustomNodeResult(ChiCaptureResult* pCaptureResult);
        void      DestroyResources() override;

    private:

        enum SessionId
        {
            RealtimeSession,
            OfflineSession,
            MaxSessions
        };

        enum PipelineConfig
        {
            RealtimeConfig,
            OfflineConfig,
            MixedConfig
        };

        enum FlushSignal
        {
            SignalReady,
            SignalFlush,
            SignalDone
        };

        const char* m_flushSignalStrings[3] = { "SignalReady", "SignalFlush", "SignalDone" };

        TestId                  m_testId;                               // differentiate between realtime tests
        TestType                m_testType;                             // differentiate between the type of flush test
        PipelineConfig          m_pipelineConfig;                       // differentiate between pipeline configurations

        ChiPipeline*            m_pChiPipeline[MaxPipelines];           // pipeline instance for realtime tests
        ChiSession*             m_pChiSession[MaxSessions];             // session instance for realtime tests
        SessionPrivateData      m_perSessionPvtData[MaxSessions];       // test specific private data
        ChiPrivateData          m_requestPvtData[MaxSessions];          // request private data
        CHIPIPELINEREQUEST      m_submitRequest;                        // pipeline request
        CHICAPTUREREQUEST       m_realtimeRequest[MAX_REQUESTS];        // array of realtime capture requests
        CHICAPTUREREQUEST       m_offlineRequest[MAX_REQUESTS];         // array of offline capture requests
        CHIPIPELINEMETADATAINFO m_pPipelineMetadataInfo[MaxPipelines];  // pipeline metadata information

        BufferManager::NativeChiBuffer  m_realtimeOutputBuffers[MAX_STREAMS];   // realtime output buffers
        BufferManager::NativeChiBuffer  m_offlineOutputBuffers[MAX_STREAMS];    // offline output buffers
        BufferManager::NativeChiBuffer* m_pInputBuffer;                         // input buffer

        bool                m_bIsFlushTriggered;            // tells if session was flushed
        const uint32_t      m_flushQueueTriggerFrame = 5;   // result frame number of when to trigger the flush for flush queue tests
        UINT                m_usFlushDelay;                 // number of usec to delay flush in FlushNode and FlushQueue tests
        uint64_t            m_flushStartTime;               // time that flush was triggered
        uint64_t            m_flushEndTime;                 // time that flushed request was returned to app

        OSThreadHandle      m_flushThread;                  // worker thread in charge of triggering flush when signaled by main thread
        FlushSignal         m_flushSignaler;                // enum to help signal/command the flush thread
        Mutex*              m_pSignalMutex;                 // mutex to protect the signaler
        Condition*          m_pSignalCond;                  // condition to help coordinate between main and flush thread

        CDKResult   GenerateRealtimeCaptureRequest(uint64_t frameNumber);
        CDKResult   GenerateOfflineCaptureRequest(uint64_t frameNumber);
        CDKResult   CreateSessionHelper(FlushTest::SessionId sessionId);
        void        DestroyResourcesHelper(SessionId sessionId);

        CDKResult       FlushNode();
        CDKResult       FlushQueue();
        CDKResult       FlushRecover();
        void            TriggerFlush(SessionId sessionId);
        static VOID*    WaitForFlushSignal(VOID * pArg);
        void            SignalFlushThread(FlushSignal signal);

    };

} // namespace tests

#endif // __FLUSH_TEST__
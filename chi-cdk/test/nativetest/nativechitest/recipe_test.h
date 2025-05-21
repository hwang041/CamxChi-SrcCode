//*****************************************************************************************************************************
// Copyright (c) 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*****************************************************************************************************************************

#ifndef __RECIPE_TEST__
#define __RECIPE_TEST__

#include "chitestcase.h"

namespace tests
{

class RecipeTest : public ChiTestCase
{

    public:
        enum TestId
        {
            // single out stream
            TestIFEGeneric,
            TestIFEGenericTestgen,
            TestIPEGeneric,
            TestBPSGeneric,
            TestTFEGenericTestgen,
            TestOPEGeneric,

            // double out stream
            TestIFEGeneric2Stream,
            TestIFEGeneric2StreamTestgen,
            TestIFEGeneric2StreamDisplay,
            TestIFEGeneric2StreamDisplayTestgen,
            TestIPEGeneric2StreamDisplay,
            TestBPSGeneric2Stream,
            TestBPSDownscaleGeneric,
            TestIFEDownscaleGenericTestgen,
            TestTFEGeneric2StreamTestgen,
            TestOPEGeneric2StreamDisplay,

            // three out stream
            TestOPEGeneric3StreamDisplayStats,
            RecipeNumOfTests
        };

        void TestRealtimePipeline(TestId testId);
        void TestOfflinePipeline(TestId testId);
        void TestMixedPipeline(TestId testId);

        RecipeTest() = default;
        ~RecipeTest() = default;

    protected:

    void      Setup() override;
    void      Teardown() override;
    CDKResult SetupStreams() override;
    CDKResult SetupPipelines(int cameraId, ChiSensorModeInfo* sensorMode) override;
    CDKResult CreateSessions() override;
    void      CommonProcessCaptureResult(ChiCaptureResult* pCaptureResult, SessionPrivateData* pSessionPrivateData) override;
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

    TestId                  m_testId;                               // differentiate between realtime tests
    PipelineConfig          m_pipelineConfig;                       // differentiate between pipeline configurations
    Size                    m_selectedInputSize;                    // user provided input resolution at runtime
    Size                    m_selectedOutputSize;                   // user provided output resolution at runtime
    Size                    m_selectedRdiOutputSize;                // user provided RDI output resolution at runtime
    CHISTREAMFORMAT         m_selectedInputFormat;                  // user provided input format at runtime
    CHISTREAMFORMAT         m_selectedOutputFormat;                 // user provided output format at runtime

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

    CDKResult   GenerateRealtimeCaptureRequest(uint64_t frameNumber);
    CDKResult   GenerateOfflineCaptureRequest(uint64_t frameNumber);
    CDKResult   CreateSessionHelper(RecipeTest::SessionId sessionId);
    void        DestroyResourcesHelper(SessionId sessionId);

    static RecipeTest*       m_pTestObj;
};

} // namespace tests

#endif // __RECIPE_TEST__
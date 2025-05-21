////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 - 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  realtime_pipeline_test.h
/// @brief Declarations for the realtime test suite.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __REALTIME_PIPELINETEST__
#define __REALTIME_PIPELINETEST__

#include "chitestcase.h"

namespace tests
{

    class RealtimePipelineTest : public ChiTestCase
    {

    public:
        enum TestId
        {
            TestIPEFull = 0,
            TestIFEFull,
            TestIFEFull3A,
            TestIFERDI0RawOpaque,
            TestIFERDI0RawOpaqueTestgen,
            TestIFERDI0RawPlain16,
            TestIFERawCamif,
            TestIFERawLsc,
            TestIFERDI0Raw10Testgen,
            TestIFEFullTestgen,
            TestIPEFullTestgen,
            TestIFEFullStatsTestgen,
            TestIFEFullStats,
            TestRealtimePrevRDI,
            TestPrevRDITestgen,
            TestRealtimePrevWithCallback,
            TestRealtimePrevWith3AWrappers,
            TestPreviewWithMemcpy,
            TestPreviewFromMemcpy,
            TestPreviewHVX,
            TestIPEATestgen,
            TestIPE3ATestgen,
            TestIPEABTestgen,
            TestIPEABStatsTestgen,
            TestIPEABCStatsTestgen,
            TestParamDefaultTestgen,
            TestParamLinearizationTestgen,
            TestParamChannelGainTestgen,
            TestParamBadPixelCorrectionTestgen,
            TestParamAdaptiveBayerFilterTestgen,
            TestParamBlackLevelSubtractionTestgen,
            TestParamLensRollOffTestgen,
            TestParamWhiteBalanceGainTestgen,
            TestParamDemosaicTestgen,
            TestParamGammaIFETestgen,
            TestParamColorSpaceTransformIFETestgen,
            TestParamICATestgen,
            TestParamANRTestgen,
            TestParamTFTestgen,
            TestParamColorSpaceTransformIPETestgen,
            TestParamLTMTestgen,
            TestParamColorCorrectionTestgen,
            TestParamGammaIPETestgen,
            TestParam2DLUTTestgen,
            TestParamColorConversionTestgen,
            TestParamChromaSuppressionTestgen,
            TestParamAdaptiveSpacialFilterTestgen,
            TestParamGrainAdderTestgen,
            TestBypassNodeMemcpy,
            TestTFEFullStatsTestgen,
            TestCVPDME,
            TestCVPDMEDisplayPort,
            TestCVPDMEICA,
            RealtimePipelineNumOfTests
        };

        RealtimePipelineTest() = default;
        ~RealtimePipelineTest() = default;

        void TestRealtimePipeline(TestId testType, bool bUseExternalSensor = false);

    protected:

        CDKResult SetupStreams() override;
        CDKResult SetupPipelines(int cameraId, ChiSensorModeInfo* sensorMode) override;
        CDKResult CreateSessions() override;
        void      CommonProcessCaptureResult(ChiCaptureResult* pCaptureResult, SessionPrivateData* pSessionPrivateData) override;
        void      DestroyResources() override;

    private:

        enum SessionId
        {
            RealtimeSession = 0,
            MaxSessions
        };

        TestId                  m_testId;                           // testId to differentiate between realtime tests
        Size                    m_selectedOutputSize;               // user provided output resolution at runtime
        Size                    m_selectedRdiOutputSize;            // user provided RDI output resolution at runtime
        ChiPipeline*            m_pChiPipeline;                     // pipeline instance for realtime tests
        ChiSession*             m_pChiSession;                      // session instance for realtime tests
        SessionPrivateData      m_perSessionPvtData;                // test specific private data
        ChiPrivateData          m_requestPvtData;                   // request private data
        CHIPIPELINEREQUEST      m_submitRequest;                    // pipeline request
        CHICAPTUREREQUEST       m_realtimeRequest[MAX_REQUESTS];    // array of capture requests
        CHIPIPELINEMETADATAINFO m_pPipelineMetadataInfo;            // pipeline metadata information

        CDKResult GenerateCaptureRequest(uint64_t frameNumber);

    };
} // namespace tests

#endif  //#ifndef __REALTIMEPIPELINETEST__
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 - 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  offline_pipeline_test.h
/// @brief Declarations for the offline test suite.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __OFFLINE_PIPELINETEST__
#define __OFFLINE_PIPELINETEST__

#include "chitestcase.h"

namespace tests
{

    class OfflinePipelineTest : public ChiTestCase
    {
    public:
        enum TestId
        {
            TestIPEInputNV12DisplayNV12 = 0,
            TestIPEInputNV12DisplayUBWCTP10,
            TestIPEInputNV12DisplayUBWCNV12,
            TestIPEInputUBWCTP10DisplayNV12,
            TestIPEInputYUVOutputJPEG,
            TestIPEInputNV12VideoNV12,
            TestIPEInputNV12VideoUBWCNV12,
            TestIPEInputNV12VideoUBWCTP10,
            TestIPEInputNV12DisplayVideoNV12,
            TestIPEInputNV12DisplayVideoUBWCNV12,
            TestIPEInputNV12DisplayVideoUBWCTP10,
            TestIPEInputNV12DisplayNV12VideoUBWCNV12,
            TestIPEInputNV12DisplayUBWCNV12VideoNV12,
            TestIPEInputNV12DisplayNV12VideoUBWCTP10,
            TestIPEInputNV12DisplayUBWCTP10VideoNV12,
            TestBPSInputRaw16OutFullUBWCTP10,
            TestBPSInputRaw10OutFullUBWCTP10,
            TestBPSInputRaw16IPEDispNV12,
            TestBPSInputRaw16IPEJpeg,
            TestBPSInputRaw16IPEDispUBWCNV12,
            TestBPSInputRaw16IPEDispUBWCTP10,
            TestBPSInputRaw16StatsOut,
            TestBPSInputFHDRaw16StatsOut,
            TestBPSInputUHDRaw16StatsOutWithIPE,
            TestBPSInputFHDRaw16StatsOutWithIPE,
            TestBPSInputFHDRaw16BGStatsWithIPE,
            TestBPSInputUHDRaw16BGStatsWithIPE,
            TestBPSInputFHDRaw16HistStatsWithIPE,
            TestBPSInputUHDRaw16HistStatsWithIPE,
            TestJPEGInputNV12VGAOutputBlob,
            TestJPEGInputNV124KOutputBlob,
            TestBPSInputRaw16OutputGPUPorts,
            TestFDInputNV12VGAOutputBlob,
            TestBPSIdealRaw,
            TestBPSInputRaw10WithIPEAndDS,
            TestBPSInputRaw16WithIPEAndDS,
            TestParamRawDefault,
            TestParamRawLinearization,
            TestParamRawPDPC,
            TestParamRawChannelGain,
            TestParamRawGIC,
            TestParamRawAdaptiveBayerFilter,
            TestParamRawBlackLevelSubtraction,
            TestParamRawLensRollOff,
            TestParamRawWhiteBalanceGain,
            TestParamRawDemosaic,
            TestParamRawGammaBPS,
            TestParamRawColorSpaceTransformBPS,
            TestParamRawHNR,
            TestParamRawANR,
            TestParamRawTF,
            TestParamRawColorSpaceTransformIPE,
            TestParamRawLTM,
            TestParamRawColorCorrection,
            TestParamRawGammaIPE,
            TestParamRaw2DLUT,
            TestParamRawColorConversion,
            TestParamYUVDefault,
            TestParamYUVColorSpaceTransform,
            TestParamYUVColorConversion,
            TestParamYUVChromaSuppression,
            TestParamYUVAdaptiveSpacialFilter,
            TestParamYUVGrainAdder,
            OfflinePipelineNumOfTests
        };

        OfflinePipelineTest()  = default;
        ~OfflinePipelineTest() = default;

        void TestOfflinePipeline(TestId testType);
        void SetSpecialMetadata(uint64_t frameNumber, uint64_t requestId);

    protected:

        CDKResult SetupStreams() override;
        CDKResult SetupPipelines(int cameraId, ChiSensorModeInfo* sensorMode) override;
        CDKResult CreateSessions() override;
        void      CommonProcessCaptureResult(ChiCaptureResult* pCaptureResult, SessionPrivateData* pSessionPrivateData) override;
        void      DestroyResources() override;

    private:

        enum SessionId
        {
            OfflineSession = 0,
            MaxSessions
        };

        Size                    m_selectedInputSize;            // user provided input resolution at runtime
        Size                    m_selectedOutputSize;           // user provided output resolution at runtime
        CHISTREAMFORMAT         m_selectedInputFormat;          // user provided input format at runtime
        Size                    m_selectedRdiOutputSize;        // user provided RDI output resolution at runtime
        TestId                  m_testId;                       // testId to differentiate between offline tests
        ChiPipeline*            m_pChiPipeline;                 // pipeline instance for offline tests
        ChiSession*             m_pChiSession;                  // session instance for offline tests
        SessionPrivateData      m_perSessionPvtData;            // test specific private data
        ChiPrivateData          m_requestPvtData;               // request private data
        CHIPIPELINEREQUEST      m_submitRequest;                // pipeline request
        CHICAPTUREREQUEST       m_offlineRequest[MAX_REQUESTS]; // array of offline capture requests
        CHIPIPELINEMETADATAINFO m_pPipelineMetadataInfo;        // pipeline metadata information

        CDKResult GenerateOfflineCaptureRequest(uint64_t frameNumber);

    };
}

#endif  //#ifndef __OFFLINE_PIPELINETEST__

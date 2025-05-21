//******************************************************************************
// Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*******************************************************************************

#ifndef __CUSTOM_NODE_TEST__
#define __CUSTOM_NODE_TEST__

#include "chitestcase.h"

namespace tests
{
    class CustomNodeTest : public ChiTestCase
    {

    public:
        enum TestId
        {
            TestVendorTagWrite
        };

        CustomNodeTest() = default;
        ~CustomNodeTest() = default;

        void TestCustomNode(TestId testType);

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

        TestId                  m_testId;                           // testId to differentiate between different custom node tests
        ChiPipeline*            m_pChiPipeline;                     // pipeline instance for tests
        ChiSession*             m_pChiSession;                      // session instance for tests
        SessionPrivateData      m_perSessionPvtData;                // test specific private data
        ChiPrivateData          m_requestPvtData;                   // request specific private data
        CHIPIPELINEREQUEST      m_submitRequest;                    // pipeline request
        CHICAPTUREREQUEST       m_realtimeRequest[MAX_REQUESTS];    // array of capture requests
        CHIPIPELINEMETADATAINFO m_pPipelineMetadataInfo;            // pipeline metadata information

        CDKResult GenerateCaptureRequest(uint64_t frameNumber);

    };
}

#endif  //#ifndef __CUSTOM_NODE_TEST__
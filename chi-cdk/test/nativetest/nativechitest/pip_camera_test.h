//******************************************************************************
// Copyright (c) 2018-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*******************************************************************************

#ifndef __PIP_CAMERA_TEST__
#define __PIP_CAMERA_TEST__

#include "chitestcase.h"

namespace tests
{
    class PIPCameraTest : public ChiTestCase
    {
    public:

        enum TestId
        {
            PIPCameraParamDefault = 0, // Reserve 0 for IQ params
            TestStillPreview,
            TestStillCapture,
            TestVideo,
            PIPCameraNumOfTests
        };

        PIPCameraTest() = default;
        ~PIPCameraTest() = default;

        void TestPIPCamera(TestId testType);

    protected:

        enum CamEnum
        {
            CamA = 0,
            CamB,
            CamMax
        };

        virtual void Setup() override;

        // START dummy functions to satisfy pure virtual defs of the parent class (DO NOT USE)
        CDKResult SetupStreams() override { return CDKResultEFailed; };
        CDKResult SetupPipelines(int cameraId, ChiSensorModeInfo* sensorMode) override
        {
            NATIVETEST_UNUSED_PARAM(cameraId);
            NATIVETEST_UNUSED_PARAM(sensorMode);
            return CDKResultEFailed;
        };
        // END dummy functions

        CDKResult SetupStreamsForCamera(CamEnum camEnum);
        CDKResult SetupPIPCameraPipelines(int cameraIdA, int cameraIdB, ChiSensorModeInfo* sensorModeCamA, ChiSensorModeInfo* sensorModeCamB);
        CDKResult CreateSessions() override;
        CDKResult InitializeBufferMangers(CamEnum camEnum, int cameraId);
        void      CommonProcessCaptureResult(ChiCaptureResult* pCaptureResult, SessionPrivateData* pSessionPrivateData) override;
        void      DestroyResources() override;

    private:

        enum SessionId
        {
            RealtimeSession = 0,
            MaxSessions
        };

        TestId                  m_testId;                              // testId to differentiate between realtime tests
        ChiSession*             m_pChiSession;                         // session instance for realtime tests
        SessionPrivateData      m_perSessionPvtData;                   // test specific private data
        CHIPIPELINEREQUEST      m_submitRequest;                       // pipeline request
        CHICAPTUREREQUEST       m_pipCamRequest[CamMax][MAX_REQUESTS]; // array of capture requests
        CHIPIPELINEMETADATAINFO m_pPipelineMetadataInfo;               // pipeline metadata information

        ChiPrivateData                          m_requestPvtData[CamMax];   // request private data
        ChiStream*                              m_pRequiredStreams[CamMax]; // pointer to created stream objects for camera A
        ChiPipeline*                            m_pChiPipeline[CamMax];     // pipeline instance for realtime tests
        std::map<StreamUsecases, ChiStream*>    m_streamIdMap[CamMax];      // map storing unique streamId and stream object for camera A
        std::map<ChiStream*, BufferManager*>    m_streamBufferMap[CamMax];  // map storing stream and it's associated buffermanager
        BufferManager*                          m_pBufferManagers[CamMax][MAX_STREAMS];  // pointer to buffermanagers for each stream

        /* StreamCreateData structure and memory allocated for its variables (overriding parent class variables) */
        StreamCreateData         m_streamInfo[CamMax];                    // stream info required for creating stream objects
        int                      m_numStreams[CamMax];                    // total number of streams for given testcase
        CHISTREAMFORMAT          m_format[CamMax][MAX_STREAMS];           // format for the streams
        CHISTREAMTYPE            m_direction[CamMax][MAX_STREAMS];        // stream direction
        Size                     m_resolution[CamMax][MAX_STREAMS];       // resolution for the streams
        StreamUsecases           m_streamId[CamMax][MAX_STREAMS];         // unique identifier for the streams
        uint32_t                 m_usageFlag[CamMax][MAX_STREAMS];        // gralloc usage flags for the streams
        bool                     m_isRealtime[CamMax][MAX_STREAMS];       // bool to indicate if this stream is part of realtime session

        CDKResult GeneratePIPCaptureRequest(uint64_t frameNumA, uint64_t frameNumB);

    };
} // namespace tests

#endif  // __PIP_CAMERA_TEST__

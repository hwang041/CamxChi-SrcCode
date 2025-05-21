//******************************************************************************************************************************
// Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//******************************************************************************************************************************

#include "custom_node_test.h"

namespace tests
{
    /***************************************************************************************************************************
    *   CustomNodeTest::TestCustomNode
    *
    *   @brief
    *       Test a custom node
    *   @param
    *       [in] TestType             testType       Test identifier
    *   @return
    *       None
    ***************************************************************************************************************************/
    void CustomNodeTest::TestCustomNode(TestId testType)
    {
        // Get list of cameras to test
        std::vector <int> camList = m_pChiModule->GetCameraList();

        m_testId = testType;

        for (size_t camCounter = 0; camCounter < camList.size(); camCounter++)
        {
            // Get the actual camera ID to test
            int cameraId = camList[camCounter];

            //1. Create chistream objects from streamcreatedata
            NT_ASSERT(SetupStreams() == CDKResultSuccess, "Fatal failure at SetupStreams() !");

            ChiSensorModeInfo* testSensorMode = nullptr;
            testSensorMode = m_pChiModule->GetClosestSensorMode(cameraId, m_streamInfo.maxRes);

            NT_ASSERT(testSensorMode != nullptr, "Sensor mode is NULL for cameraId: %d", cameraId);

            NT_LOG_INFO( "Camera %d chosen sensor mode: %u, width: %u, height: %u", cameraId,
                testSensorMode->modeIndex, testSensorMode->frameDimension.width, testSensorMode->frameDimension.height);

            // TODO: Set number of batched frames from sensormode based on usecase
            testSensorMode->batchedFrames = 1;

            //2. Create pipelines
            NT_ASSERT(SetupPipelines(cameraId, testSensorMode) == CDKResultSuccess, "Pipelines Setup failed");

            //3. Create sessions
            NT_ASSERT(CreateSessions() == CDKResultSuccess, "Necessary sessions could not be created");

            //4. Initialize buffer manager and metabuffer pools
            NT_ASSERT(InitializeBufferMangers(cameraId) == CDKResultSuccess, "Buffer managers could not be initialized");
#ifndef OLD_METADATA
            NT_ASSERT(m_pChiMetadataUtil->CreateInputMetabufferPool(cameraId, MAX_REQUESTS) == CDKResultSuccess,
                 "Input metabuffer pool for camera Id: %d could not be created!");
            NT_ASSERT(m_pChiMetadataUtil->CreateOutputMetabufferPool(MAX_REQUESTS) == CDKResultSuccess,
                 "Output metabuffer pool could not be created!");
#endif // OLD_METADATA

            //5. Create and submit capture requests
            uint64_t frameNumber = START_FRAME;
            for (int frameIndex = 1; frameIndex <= CmdLineParser::GetFrameCount(); frameIndex++, frameNumber++)
            {
                NT_ASSERT(GenerateCaptureRequest(frameNumber) == CDKResultSuccess,
                     "Submit pipeline request failed");
            }

            //6. Wait for all results
            NT_ASSERT(WaitForResults() == CDKResultSuccess,
                "There are pending buffers not returned by driver after several retries");

            //7. Destroy all resources created
            DestroyResources();
        }
    }

    /***************************************************************************************************************************
    *   CustomNodeTest::SetupStreams()
    *
    *   @brief
    *       Overridden function implementation which defines the stream information based on the test Id
    *   @param
    *       None
    *   @return
    *       CDKResult success if stream objects could be created or failure
    ***************************************************************************************************************************/
    CDKResult CustomNodeTest::SetupStreams()
    {
        CDKResult result = CDKResultSuccess;

        int streamIndex = 0;

        switch (m_testId)
        {
        case TestVendorTagWrite:
            m_numStreams = 1;

            //1. preview stream
            m_resolution[streamIndex] = FULLHD;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = PREVIEW;
            m_streamInfo.num_streams  = m_numStreams;
            break;

        default:
            NT_LOG_ERROR( "Unknown testcase Id provided: [%d]", m_testId);
            result = CDKResultENoSuch;
            break;
        }

        if (result == CDKResultSuccess)
        {
            if (m_streamInfo.num_streams <= 0)
            {
                NT_LOG_ERROR("Number of streams should be greater than 0, given: %d", m_streamInfo.num_streams);
                result = CDKResultEFailed;
            }
            else
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

                        if (m_pRequiredStreams == nullptr)
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
        }

        return result;
    }

    /***************************************************************************************************************************
    *   CustomNodeTest::SetupPipelines()
    *
    *   @brief
    *       Overridden function implementation which creates pipeline objects based on the test Id
    *   @param
    *       [in]  int                 cameraId    cameraId to be associated with the pipeline
    *       [in]  ChiSensorModeInfo*  sensorMode  sensor mode to be used for the pipeline
    *   @return
    *       CDKResult success if pipelines could be created or failure
    ***************************************************************************************************************************/
    CDKResult CustomNodeTest::SetupPipelines(int cameraId, ChiSensorModeInfo * sensorMode)
    {
        CDKResult result = CDKResultSuccess;
        switch (m_testId)
        {
        case TestId::TestVendorTagWrite:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::VendorTagWrite);
            break;
        default:
            NT_LOG_ERROR( "Unknown testcase Id provided: [%d]", m_testId);
            return CDKResultENoSuch;
        }

        result = (m_pChiPipeline != nullptr) ? m_pChiPipeline->CreatePipelineDesc() : CDKResultEInvalidPointer;
        return result;
    }

    /***************************************************************************************************************************
    *   CustomNodeTest::CreateSessions()
    *
    *   @brief
    *       Overridden function implementation which creates required number of sessions based on the test Id
    *   @param
    *       None
    *   @return
    *       CDKResult success if sessions could be created or failure
    ***************************************************************************************************************************/
    CDKResult CustomNodeTest::CreateSessions()
    {
        CDKResult result       = CDKResultSuccess;
        ChiCallBacks callbacks = { 0 };

        callbacks.ChiNotify                      = ChiTestCase::ProcessMessage;
        callbacks.ChiProcessCaptureResult        = ChiTestCase::QueueCaptureResult;
        callbacks.ChiProcessPartialCaptureResult = ChiTestCase::QueuePartialCaptureResult;

        m_perSessionPvtData.pTestInstance = this;
        m_perSessionPvtData.sessionId     = RealtimeSession;

        m_pChiSession = ChiSession::Create(&m_pChiPipeline,
                                           1,
                                           &callbacks,
                                           &m_perSessionPvtData);

        if (m_pChiSession == nullptr)
        {
            result = CDKResultEFailed;
        }
        else
        {
            result = m_pChiPipeline->ActivatePipeline(m_pChiSession->GetSessionHandle());
#ifndef OLD_METADATA
            if (result == CDKResultSuccess)
            {
                result = m_pChiMetadataUtil->GetPipelineinfo(m_pChiModule->GetContext(),
                    m_pChiSession->GetSessionHandle(), m_pChiPipeline->GetPipelineHandle(), &m_pPipelineMetadataInfo);
            }
#endif // OLD_METADATA
        }

        return result;
    }

    /***************************************************************************************************************************
    *   CustomNodeTest::CommonProcessCaptureResult()
    *
    *   @brief
    *       Overridden function implementation which processes the capture result obtained from driver
    *   @param
    *        [in]  CHICAPTURERESULT*     pCaptureResult         pointer to capture result
    *        [in]  void*                 pPrivateCallbackData   pointer private callback data
    *   @return
    *       None
    ***************************************************************************************************************************/
    void CustomNodeTest::CommonProcessCaptureResult(ChiCaptureResult* pCaptureResult, SessionPrivateData* pSessionPrivateData)
    {
        CDKResult result           = CDKResultSuccess;
        uint32_t  resultFrameNum   = pCaptureResult->frameworkFrameNum;
        uint32_t  numOutputBuffers = pCaptureResult->numOutputBuffers;
        SessionId sessionId        = static_cast<SessionId>(pSessionPrivateData->sessionId);

#ifndef OLD_METADATA
        if (m_pChiMetadataUtil != nullptr)
        {
            m_pChiMetadataUtil->VerifyCaptureResultMetadata(static_cast<CHIMETAHANDLE>(pCaptureResult->pOutputMetadata));
        }
#endif // OLD_METADATA

        if (sessionId == RealtimeSession)
        {

            for (uint32_t bufferIndex = 0; bufferIndex < numOutputBuffers; bufferIndex++)
            {
                BufferManager::NativeChiBuffer* outBuffer = const_cast<BufferManager::NativeChiBuffer*>(&pCaptureResult->
                    pOutputBuffers[bufferIndex]);
                BufferManager* manager = m_streamBufferMap[outBuffer->pStream];
                if (manager == nullptr)
                {
                    NT_LOG_ERROR( "Could not find buffer manger for given stream: %p in frame: %d",
                        outBuffer->pStream, resultFrameNum);

                    result |= CDKResultEInvalidPointer;
                }
                else
                {
                    BufferManager::GenericBuffer genericBuffer(outBuffer);
                    result |= manager->ProcessBufferFromResult(resultFrameNum, &genericBuffer, true);
                }
            }

            // CustomNode should populate vendortag with current processed frame, verify vendor tag frame matches expected
            // frame number
            if (GetOutputMetadata(pCaptureResult) != nullptr)
            {
                UINT32 tagLocation = 0;
                uint64_t processedFrameHolder = 0;
                uint64_t* pProcessedFrame = &processedFrameHolder;

                result = m_pChiModule->GetTagOps().pQueryVendorTagLocation("com.bots.node.vendortagwrite",
                    "ProcessedFrameNumber", &tagLocation);
                NT_ASSERT(result == CDKResultSuccess, "Could not get vendor tag with section com.bots.node.vendortagwrite");
#ifdef OLD_METADATA
                m_pChiModule->GetTagOps().pGetMetaData(const_cast<CHIMETADATAHANDLE>(GetOutputMetadata(pCaptureResult)),
                    tagLocation, pProcessedFrame, sizeof(uint64_t));
#else
                m_pChiMetadataUtil->GetVendorTag(const_cast<CHIMETADATAHANDLE>(GetOutputMetadata(pCaptureResult)),
                    "com.bots.node.vendortagwrite", "ProcessedFrameNumber", reinterpret_cast<VOID**>(&pProcessedFrame));
#endif // OLD_METADATA

                NT_LOG_DEBUG( "Current frameNumber from result metadata: %" PRIu32, resultFrameNum);
                NT_LOG_DEBUG( "Value of frameNumber written by custom node: %" PRIu64, *pProcessedFrame);

                NT_EXPECT(*pProcessedFrame == resultFrameNum,
                    "Vendor tag processed frame does not match framework result frame");
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
            NT_LOG_DEBUG( "Number of pending buffers remaining after receiving the result: %d",
                GetPendingBufferCount());
        }

    }

    /***************************************************************************************************************************
    *   CustomNodeTest::DestroyResources()
    *
    *   @brief
    *       Overridden function implementation which destroys all created resources/objects
    *   @param
    *       None
    *   @return
    *       None
    ***************************************************************************************************************************/
    void CustomNodeTest::DestroyResources()
    {
        m_pChiPipeline->DeactivatePipeline(m_pChiSession->GetSessionHandle());

        m_pChiSession->DestroySession();
        m_pChiPipeline->DestroyPipeline();

        DestroyCommonResources();
    }

    /***************************************************************************************************************************
    *   CustomNodeTest::GenerateCaptureRequest()
    *
    *   @brief
    *       Generate a realtime pipeline request
    *   @param
    *       [in] uint64_t    frameNumber    framenumber associated with the request
    *   @return
    *       CDKResult success if request could be submitted or failure
    ***************************************************************************************************************************/
    CDKResult CustomNodeTest::GenerateCaptureRequest(uint64_t frameNumber)
    {
        CDKResult result = CDKResultSuccess;
        static const uint32_t NumOutputBuffers = m_numStreams;
        BufferManager::NativeChiBuffer* outputBuffers = SAFE_NEW() BufferManager::NativeChiBuffer[NumOutputBuffers];
        uint32_t outputIndex = 0;

        std::map<ChiStream*, BufferManager*>::iterator it;

        for (it = m_streamBufferMap.begin(); it != m_streamBufferMap.end(); ++it)
        {
            BufferManager* manager = it->second;
            void* opBufferForRequest = manager->GetOutputBufferForRequest();
            if (nullptr == opBufferForRequest) {
                NT_LOG_ERROR("Failed to get valid void pointer for output buffer");
                return CDKResultEFailed;
            }
            outputBuffers[outputIndex] = *static_cast<BufferManager::NativeChiBuffer*>(opBufferForRequest);
            outputIndex++;
        }

        uint32_t requestId = FRAME_REQUEST_MOD(frameNumber);
        memset(&m_realtimeRequest[requestId], 0, sizeof(CHICAPTUREREQUEST));

        m_realtimeRequest[requestId].frameNumber       = frameNumber;
        m_realtimeRequest[requestId].hPipelineHandle   = m_pChiPipeline->GetPipelineHandle();
        m_realtimeRequest[requestId].numOutputs        = NumOutputBuffers;
        m_realtimeRequest[requestId].pOutputBuffers    = outputBuffers;
        m_realtimeRequest[requestId].pPrivData         = &m_requestPvtData;

#ifdef OLD_METADATA
        m_realtimeRequest[requestId].pMetadata = allocate_camera_metadata(METADATA_ENTRIES, 100 * 1024);
        NATIVETEST_UNUSED_PARAM(m_pPipelineMetadataInfo);
#else
        // Get the input metabuffer from the pool
        m_realtimeRequest[requestId].pInputMetadata = m_pChiMetadataUtil->GetInputMetabufferFromPool(requestId);
        NT_EXPECT(m_realtimeRequest[requestId].pInputMetadata != nullptr, "Failed to create Input Metabuffer before sending request ");

        // Get the output buffer from the metabuffer bool.
        m_realtimeRequest[requestId].pOutputMetadata = m_pChiMetadataUtil->GetOutputMetabufferFromPool(requestId,
            m_pPipelineMetadataInfo.publishTagArray, m_pPipelineMetadataInfo.publishTagCount);
        NT_EXPECT(m_realtimeRequest[requestId].pOutputMetadata != nullptr, "Failed to create Output Metabuffer before sending request");
#endif // OLD_METADATA

        m_submitRequest.pSessionHandle   = m_pChiSession->GetSessionHandle();
        m_submitRequest.numRequests      = 1;
        m_submitRequest.pCaptureRequests = &m_realtimeRequest[requestId];

        AtomicIncrement(NumOutputBuffers);

        NT_LOG_DEBUG( "Number of pending buffers remaining: %d after sending request: %" PRIu64,
            GetPendingBufferCount(), frameNumber);

        result = m_pChiModule->SubmitPipelineRequest(&m_submitRequest);
        delete[] outputBuffers;
        return result;
    }
}

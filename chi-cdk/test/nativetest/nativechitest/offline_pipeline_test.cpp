////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 - 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  realtime_pipeline_test.h
/// @brief Declarations for the offline test suite.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "offline_pipeline_test.h"

namespace tests
{

    /**************************************************************************************************
    *   OfflinePipelineTest::TestOfflinePipeline
    *
    *   @brief
    *       Test a offline pipeline depending on pipelineType
    *   @param
    *       [in] TestId     testType      enum representing test Id
    *   @return
    *       None
    **************************************************************************************************/
    void OfflinePipelineTest::TestOfflinePipeline(TestId testType)
    {
        // Get configurable parameters from command line
        m_selectedInputSize = Size(CmdLineParser::GetInputWidth(), CmdLineParser::GetInputHeight());
        m_selectedInputFormat = static_cast<CHISTREAMFORMAT>(CmdLineParser::GetInputFormat());
        m_selectedOutputSize = Size(CmdLineParser::GetOutputWidth(), CmdLineParser::GetOutputHeight());
        m_selectedRdiOutputSize = Size(CmdLineParser::GetRdiOutputWidth(), CmdLineParser::GetRdiOutputHeight());

        int numOfCameras = m_pChiModule->GetNumberCameras();
        NATIVETEST_UNUSED_PARAM(numOfCameras);

        m_testId = testType;

        //1. Create chistream objects from streamcreatedata
        NT_ASSERT(SetupStreams() == CDKResultSuccess, "Fatal failure in SetupStreams() !");

        //2. Create pipelines
        // offline pipelines don't require cameraId and sensor mode
        NT_ASSERT(SetupPipelines(0, nullptr) == CDKResultSuccess, "Pipelines Setup failed");

        //3. Create sessions
        NT_ASSERT(CreateSessions() == CDKResultSuccess, "Necessary sessions could not be created");

        //4. Initialize buffer managers and metabuffer pools
        NT_ASSERT(InitializeBufferMangers(-1) == CDKResultSuccess,"Buffer managers could not be initialized");
#ifndef OLD_METADATA
        // offline pipelines does not need camera Id, hence hardcoding to 0
        NT_ASSERT(m_pChiMetadataUtil->CreateInputMetabufferPool(0, MAX_REQUESTS) == CDKResultSuccess,
             "Input metabuffer pool could not be created!");
        NT_ASSERT(m_pChiMetadataUtil->CreateOutputMetabufferPool(MAX_REQUESTS) == CDKResultSuccess,
             "Output metabuffer pool could not be created!");
#endif // OLD_METADATA

        //5. Create and submit capture requests
        uint64_t frameNumber = START_FRAME;
        for (int frameIndex = 1; frameIndex <= CmdLineParser::GetFrameCount(); frameIndex++, frameNumber++)
        {
            NT_ASSERT(GenerateOfflineCaptureRequest(frameNumber) == CDKResultSuccess,
                "Submit pipeline request failed for frameNumber: %d", frameNumber);
        }

        //6. Wait for all results
        NT_ASSERT(WaitForResults() == CDKResultSuccess,
            "There are pending buffers not returned by driver after several retries");

        //7. Destroy all resources created
        DestroyResources();
    }

    /***************************************************************************************************************************
    *   OfflinePipelineTest::SetSpecialMetadata()
    *
    *   @brief
    *       Function to set metadata for some testcases
    *   @param
    *       [in] uint64_t   frameNumber     framenumber associated with the request
    *       [in] uint64_t   requestId       capture request ID
    *   @return
    *       None
    ***************************************************************************************************************************/
    void OfflinePipelineTest::SetSpecialMetadata(uint64_t frameNumber, uint64_t requestId)
    {
        if (m_testId == TestFDInputNV12VGAOutputBlob)
        {
            CDKResult result;
            NT_LOG_DEBUG( "Setting metadata ANDROID_STATISTICS_FACE_DETECT_MODE_FULL for frame:%d", frameNumber);
            UINT32 tagID = ANDROID_STATISTICS_FACE_DETECT_MODE;
            UINT32 pData = ANDROID_STATISTICS_FACE_DETECT_MODE_FULL;
            UINT32 count = 1;
            result = m_pChiMetadataUtil->GetMetadataOps().pSetTag(m_offlineRequest[requestId].pInputMetadata, tagID, &pData, count);
            NT_EXPECT(result == CDKResultSuccess, "Failed to set metadata ANDROID_STATISTICS_FACE_DETECT_MODE_FULL");
        }
    }

    /***************************************************************************************************************************
    *   OfflinePipelineTest::SetupStreams()
    *
    *   @brief
    *       Overridden function implementation which defines the stream information based on the test Id
    *   @param
    *       None
    *   @return
    *       CDKResult success if stream objects could be created or failure
    ***************************************************************************************************************************/
    CDKResult OfflinePipelineTest::SetupStreams()
    {
        CDKResult result = CDKResultSuccess;

        int streamIndex = 0;

        CHISTREAMFORMAT noFormatOverride = static_cast<CHISTREAMFORMAT>(-1);

        char const* inputFileName = CmdLineParser::GetInputImage();    // Get user input at runtime;

        // Check if input width and height set for input image at runtime
        if (strlen(inputFileName) != 0)
        {
            if (m_selectedInputSize.isInvalidSize())
            {
                NT_LOG_ERROR("Please provide input width and height required with input image. Aborting.");
                return CDKResultEInvalidArg;
            }
        }
        switch (m_testId)
        {
        case TestIPEInputYUVOutputJPEG:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = (m_selectedInputSize.isInvalidSize()) ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            // 2. Output stream [JPEG Snapshot]
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? UHD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = SNAPSHOT;

            m_streamInfo.num_streams = m_numStreams;
            break;
        case TestIPEInputNV12DisplayNV12:
        case TestParamYUVDefault:
        case TestParamYUVColorSpaceTransform:
        case TestParamYUVColorConversion:
        case TestParamYUVChromaSuppression:
        case TestParamYUVAdaptiveSpacialFilter:
        case TestParamYUVGrainAdder:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = PREVIEW;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputNV12DisplayUBWCTP10:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? HD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCTP10;
            m_usageFlag[streamIndex]  = GrallocUsageTP10;
            m_streamId[streamIndex]   = PREVIEW;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputNV12DisplayUBWCNV12:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCNV12;
            m_streamId[streamIndex]   = PREVIEW;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputUBWCTP10DisplayNV12:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? FULLHD : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatUBWCTP10 : m_selectedInputFormat;
            m_usageFlag[streamIndex]  = GrallocUsageTP10;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_BARBARA_FHD_UBWCTP10 : inputFileName;
            streamIndex++;

            //2. preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = PREVIEW;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputNV12VideoNV12:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. Video stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEOutputPortVideo;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputNV12VideoUBWCNV12:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. video stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCNV12;
            m_streamId[streamIndex]   = IPEOutputPortVideo;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputNV12VideoUBWCTP10:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. video stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? HD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCTP10;
            m_usageFlag[streamIndex]  = GrallocUsageTP10;
            m_streamId[streamIndex]   = IPEOutputPortVideo;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputNV12DisplayVideoNV12:
            m_numStreams = 3;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEOutputPortDisplay;
            streamIndex++;

            //3. video stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEOutputPortVideo;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputNV12DisplayVideoUBWCNV12:
            m_numStreams = 3;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
	    m_format[streamIndex]     = ChiStreamFormatUBWCNV12;
            m_streamId[streamIndex]   = IPEOutputPortDisplay;
            streamIndex++;

            //3. video stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCNV12;
            m_streamId[streamIndex]   = IPEOutputPortVideo;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputNV12DisplayVideoUBWCTP10:
            m_numStreams = 3;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? HD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCTP10;
            m_usageFlag[streamIndex]  = GrallocUsageTP10;
            m_streamId[streamIndex]   = IPEOutputPortDisplay;
            streamIndex++;

            //3. video stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? HD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCTP10;
            m_usageFlag[streamIndex]  = GrallocUsageTP10;
            m_streamId[streamIndex]   = IPEOutputPortVideo;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputNV12DisplayNV12VideoUBWCNV12:
            m_numStreams = 3;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEOutputPortDisplay;
            streamIndex++;

            //3. video stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCNV12;
            m_streamId[streamIndex]   = IPEOutputPortVideo;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputNV12DisplayUBWCNV12VideoNV12:
            m_numStreams = 3;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCNV12;
            m_streamId[streamIndex]   = IPEOutputPortDisplay;
            streamIndex++;

            //3. video stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEOutputPortVideo;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputNV12DisplayNV12VideoUBWCTP10:
            m_numStreams = 3;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEOutputPortDisplay;
            streamIndex++;

            //3. video stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? HD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCTP10;
            m_usageFlag[streamIndex]  = GrallocUsageTP10;
            m_streamId[streamIndex]   = IPEOutputPortVideo;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestIPEInputNV12DisplayUBWCTP10VideoNV12:
            m_numStreams = 3;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = IPEInputPortFull;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? HD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCTP10;
            m_usageFlag[streamIndex]  = GrallocUsageTP10;
            m_streamId[streamIndex]   = IPEOutputPortDisplay;
            streamIndex++;

            //3. video stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = IPEOutputPortVideo;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputRaw16OutFullUBWCTP10:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? FULLHD : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
            m_streamId[streamIndex]   = BPSInputPort;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
            streamIndex++;

            //2. BPS output full stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCTP10;
            m_usageFlag[streamIndex]  = GrallocUsageTP10;
            m_streamId[streamIndex]   = BPSOutputPortFull;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputRaw10OutFullUBWCTP10:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? HD4K_ALT : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw10 : m_selectedInputFormat;
            m_streamId[streamIndex]   = BPSInputPort;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_MIPI_RAW_10_4K : inputFileName;
            streamIndex++;

            //2. BPS output full stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? HD4K_ALT : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCTP10;
            m_usageFlag[streamIndex]  = GrallocUsageTP10;
            m_streamId[streamIndex]   = BPSOutputPortFull;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputRaw16IPEDispNV12:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? FULLHD : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
            m_streamId[streamIndex]   = BPSInputPort;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
            streamIndex++;

            //2. preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = PREVIEW;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputRaw16IPEJpeg:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? FULLHD : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
            m_streamId[streamIndex]   = BPSInputPort;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
            streamIndex++;

            //2. snapshot stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = SNAPSHOT;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputRaw16IPEDispUBWCNV12:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? FULLHD : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
            m_streamId[streamIndex]   = BPSInputPort;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
            streamIndex++;

            //2. Preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCNV12;
            m_streamId[streamIndex]   = PREVIEW;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputRaw16IPEDispUBWCTP10:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? FULLHD : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
            m_streamId[streamIndex]   = BPSInputPort;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
            streamIndex++;

            //2. Preview stream
            m_resolution[streamIndex] =  m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatUBWCTP10;
            m_usageFlag[streamIndex]  = GrallocUsageTP10;
            m_streamId[streamIndex]   = PREVIEW;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputRaw16StatsOut:
        case TestBPSInputFHDRaw16StatsOut:
            m_numStreams = 4;

            //1. Input stream
            m_direction[streamIndex] = ChiStreamTypeInput;
            m_format[streamIndex]    = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
            m_streamId[streamIndex]  = BPSInputPort;
            if (m_testId == TestBPSInputFHDRaw16StatsOut)
            {
                m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? FULLHD : m_selectedInputSize;
                m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
                streamIndex++;

                //2. BPS Full stream (offline preview/reprocess)
                m_resolution[streamIndex] =  m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
            }
            else
            {
                m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? UHD : m_selectedInputSize;
                m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_IDEALRAW_UHD : inputFileName;
                streamIndex++;

                //2. BPS Full stream (offline preview/reprocess)
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? UHD : m_selectedOutputSize;
            }

            m_direction[streamIndex] = ChiStreamTypeOutput;
            m_format[streamIndex]    = ChiStreamFormatUBWCTP10;
            m_usageFlag[streamIndex] = GrallocUsageTP10;
            m_streamId[streamIndex]  = BPSOutputPortFull;
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
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputFHDRaw16StatsOutWithIPE:
        case TestBPSInputUHDRaw16StatsOutWithIPE:
            m_numStreams = 4;

            //1. Input stream
            m_direction[streamIndex] = ChiStreamTypeInput;
            m_format[streamIndex]    = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
            m_streamId[streamIndex]  = BPSInputPort;
            if (m_testId == TestBPSInputFHDRaw16StatsOutWithIPE)
            {
                m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? FULLHD : m_selectedInputSize;
                m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
                streamIndex++;

                //2. IPE Disp stream
                m_resolution[streamIndex] =  m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
            }
            else
            {
                m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? UHD : m_selectedInputSize;
                m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_IDEALRAW_UHD : inputFileName;
                streamIndex++;

                //2. IPE Disp stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? UHD : m_selectedOutputSize;
            }

            m_direction[streamIndex] = ChiStreamTypeOutput;
            m_format[streamIndex]    = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]  = IPEOutputPortDisplay;
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
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputFHDRaw16BGStatsWithIPE:
        case TestBPSInputUHDRaw16BGStatsWithIPE:
            m_numStreams = 3;

            //1. Input stream
            m_direction[streamIndex] = ChiStreamTypeInput;
            m_format[streamIndex]    = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
            m_streamId[streamIndex]  = BPSInputPort;
            if (m_testId == TestBPSInputFHDRaw16BGStatsWithIPE)
            {
                m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? FULLHD : m_selectedInputSize;
                m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
                streamIndex++;

                //2. IPE Disp stream
                m_resolution[streamIndex] =  m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
            }
            else
            {
                m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? UHD : m_selectedInputSize;
                m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_IDEALRAW_UHD : inputFileName;
                streamIndex++;

                //2. IPE Disp stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? UHD : m_selectedOutputSize;
            }

            m_direction[streamIndex] = ChiStreamTypeOutput;
            m_format[streamIndex]    = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]  = IPEOutputPortDisplay;
            streamIndex++;

            //3. BPS BG stats stream
            m_resolution[streamIndex] = Size(691200, 1);
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = BPSOutputPortStatsBG;

            m_streamInfo.isJpeg       = false;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputFHDRaw16HistStatsWithIPE:
        case TestBPSInputUHDRaw16HistStatsWithIPE:
            m_numStreams = 3;

            //1. Input stream
            m_direction[streamIndex] = ChiStreamTypeInput;
            m_format[streamIndex]    = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
            m_streamId[streamIndex]  = BPSInputPort;
            if (m_testId == TestBPSInputFHDRaw16HistStatsWithIPE)
            {
                m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? FULLHD : m_selectedInputSize;
                m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
                streamIndex++;

                //2. IPE Disp stream
                m_resolution[streamIndex] =  m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
            }
            else
            {
                m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? UHD : m_selectedInputSize;
                m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_IDEALRAW_UHD : inputFileName;
                streamIndex++;

                //2. IPE Disp stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? UHD : m_selectedOutputSize;
            }

            m_direction[streamIndex] = ChiStreamTypeOutput;
            m_format[streamIndex]    = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]  = IPEOutputPortDisplay;
            streamIndex++;

            //3. BPS bHist stream
            m_resolution[streamIndex] = Size(3072, 1);
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = BPSOutputPortStatsBhist;

            m_streamInfo.isJpeg       = false;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestJPEGInputNV12VGAOutputBlob:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = JPEGInputPort;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. Snapshot stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? VGA : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = SNAPSHOT;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestJPEGInputNV124KOutputBlob:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = (m_selectedInputSize.isInvalidSize()) ? HD4K : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = JPEGInputPort;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_EMULATEDSENSOR_4K : inputFileName;
            streamIndex++;

            //2. Snapshot stream
            m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? HD4K : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = SNAPSHOT;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputRaw16OutputGPUPorts:
            m_numStreams = 5;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? UHD : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ?  ChiStreamFormatRaw16 : m_selectedInputFormat;
            m_streamId[streamIndex]   = BPSInputPort;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_IDEALRAW_UHD : inputFileName;
            streamIndex++;

            //2. GPU FULL stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? UHD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatP010;
            m_streamId[streamIndex]   = GPUOutputPortFull;
            m_usageFlag[streamIndex]  = GrallocUsageP010;
            streamIndex++;

            //3. GPU DS4 stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? UHD/4 : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatP010;
            m_streamId[streamIndex]   = GPUOutputPortDS4;
            m_usageFlag[streamIndex]  = GrallocUsageP010;
            streamIndex++;

            //4. GPU DS16 stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? UHD/16 : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatP010;
            m_streamId[streamIndex]   = GPUOutputPortDS16;
            m_usageFlag[streamIndex]  = GrallocUsageP010;
            streamIndex++;

            //5. GPU DS64 stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? UHD/64 : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatP010;
            m_streamId[streamIndex]   = GPUOutputPortDS64;
            m_usageFlag[streamIndex]  = GrallocUsageP010;

            m_streamInfo.num_streams = m_numStreams;
            break;
        case TestFDInputNV12VGAOutputBlob:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? VGA : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
            m_streamId[streamIndex]   = ChiNodeInputPort0;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
            streamIndex++;

            //2. FD manager stream
            m_resolution[streamIndex] = Size(16384, 1);
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatBlob;
            m_streamId[streamIndex]   = FDManagerOutputPort;

            m_streamInfo.isJpeg       = false;
            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputRaw10WithIPEAndDS:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = (m_selectedInputSize.isInvalidSize()) ? HD4K_ALT : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw10 : m_selectedInputFormat;
            m_streamId[streamIndex]   = BPSInputPort;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_MIPI_RAW_10_4K : inputFileName;
            streamIndex++;

            //2. Preview stream
            m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? HD4K_ALT : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = PREVIEW;

            m_streamInfo.num_streams  = m_numStreams;
            break;
        case TestBPSInputRaw16WithIPEAndDS:
        case TestParamRawDefault:
        case TestParamRawLinearization:
        case TestParamRawPDPC:
        case TestParamRawChannelGain:
        case TestParamRawGIC:
        case TestParamRawAdaptiveBayerFilter:
        case TestParamRawBlackLevelSubtraction:
        case TestParamRawLensRollOff:
        case TestParamRawWhiteBalanceGain:
        case TestParamRawDemosaic:
        case TestParamRawGammaBPS:
        case TestParamRawColorSpaceTransformBPS:
        case TestParamRawHNR:
        case TestParamRawANR:
        case TestParamRawTF:
        case TestParamRawColorSpaceTransformIPE:
        case TestParamRawLTM:
        case TestParamRawColorCorrection:
        case TestParamRawGammaIPE:
        case TestParamRaw2DLUT:
        case TestParamRawColorConversion:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? UHD : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ?  ChiStreamFormatRaw16 : m_selectedInputFormat;
            m_streamId[streamIndex]   = BPSInputPort;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_IDEALRAW_UHD : inputFileName;
            streamIndex++;

            //2. Preview stream
            m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? UHD : m_selectedOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
            m_streamId[streamIndex]   = PREVIEW;

            m_streamInfo.num_streams = m_numStreams;
            break;
        case TestBPSIdealRaw:
            m_numStreams = 2;

            //1. Input stream
            m_resolution[streamIndex] = m_selectedInputSize.isInvalidSize() ? FULLHD : m_selectedInputSize;
            m_direction[streamIndex]  = ChiStreamTypeInput;
            m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ?  ChiStreamFormatRaw16 : m_selectedInputFormat;
            m_streamId[streamIndex]   = BPSInputPort;
            m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
            streamIndex++;

            //2. Ideal raw stream (DS4) -- why DS4?
            m_resolution[streamIndex] = m_selectedRdiOutputSize.isInvalidSize() ? FULLHD : m_selectedRdiOutputSize;
            m_direction[streamIndex]  = ChiStreamTypeOutput;
            m_format[streamIndex]     = ChiStreamFormatRaw16;
            m_streamId[streamIndex]   = BPSOutputPortDS4;

            m_streamInfo.num_streams = m_numStreams;
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
                                m_isRealtime[index] = false;
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
    *   OfflinePipelineTest::SetupPipelines()
    *
    *   @brief
    *       Overridden function implementation which creates pipeline objects based on the test Id
    *   @param
    *       [in]  int                 cameraId    cameraId to be associated with the pipeline
    *       [in]  ChiSensorModeInfo*  sensorMode  sensor mode to be used for the pipeline
    *   @return
    *       CDKResult success if pipelines could be created or failure
    ***************************************************************************************************************************/
    CDKResult OfflinePipelineTest::SetupPipelines(int cameraId, ChiSensorModeInfo * sensorMode)
    {
        CDKResult result = CDKResultSuccess;
        switch (m_testId)
        {
        case TestIPEInputYUVOutputJPEG:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineIPEJPEG);
            break;
        case TestIPEInputNV12DisplayNV12:
        case TestIPEInputNV12DisplayUBWCTP10:
        case TestIPEInputNV12DisplayUBWCNV12:
        case TestIPEInputUBWCTP10DisplayNV12:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineIPEDisp);
            break;
        case TestIPEInputNV12VideoNV12:
        case TestIPEInputNV12VideoUBWCNV12:
        case TestIPEInputNV12VideoUBWCTP10:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineIPEVideo);
            break;
        case TestIPEInputNV12DisplayVideoNV12:
        case TestIPEInputNV12DisplayVideoUBWCNV12:
        case TestIPEInputNV12DisplayVideoUBWCTP10:
        case TestIPEInputNV12DisplayNV12VideoUBWCNV12:
        case TestIPEInputNV12DisplayUBWCNV12VideoNV12:
        case TestIPEInputNV12DisplayNV12VideoUBWCTP10:
        case TestIPEInputNV12DisplayUBWCTP10VideoNV12:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineIPEDispVideo);
            break;
        case TestBPSInputRaw16OutFullUBWCTP10:
        case TestBPSInputRaw10OutFullUBWCTP10:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPS);
            break;
        case TestBPSInputRaw16IPEDispNV12:
        case TestBPSInputRaw16IPEDispUBWCNV12:
        case TestBPSInputRaw16IPEDispUBWCTP10:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSIPE);
            break;
        case TestBPSInputRaw16IPEJpeg:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSIPEJpeg);
            break;
        case TestBPSInputRaw16StatsOut:
        case TestBPSInputFHDRaw16StatsOut:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSStats);
            break;
        case TestBPSInputFHDRaw16StatsOutWithIPE:
        case TestBPSInputUHDRaw16StatsOutWithIPE:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSStatsWithIPE);
            break;
        case TestBPSInputFHDRaw16BGStatsWithIPE:
        case TestBPSInputUHDRaw16BGStatsWithIPE:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSBGStatsWithIPE);
            break;
        case TestBPSInputFHDRaw16HistStatsWithIPE:
        case TestBPSInputUHDRaw16HistStatsWithIPE:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSHistStatsWithIPE);
            break;
        case TestJPEGInputNV12VGAOutputBlob:
        case TestJPEGInputNV124KOutputBlob:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineJpegSnapshot);
            break;
        case TestBPSInputRaw16OutputGPUPorts:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSGPUpipeline);
            break;
        case TestFDInputNV12VGAOutputBlob:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineFDPipeline);
            break;
        case TestBPSInputRaw10WithIPEAndDS:
        case TestBPSInputRaw16WithIPEAndDS:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSWithIPEAndDS);
            break;
        case TestBPSIdealRaw:
            m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSDS4);
            break;
        default:
            NT_LOG_ERROR( "Unknown testcase Id provided: [%d]", m_testId);
            return CDKResultENoSuch;
        }

        result = (m_pChiPipeline != nullptr) ? m_pChiPipeline->CreatePipelineDesc() : CDKResultEInvalidPointer;
        return result;
    }

    /***************************************************************************************************************************
    *   OfflinePipelineTest::CreateSessions()
    *
    *   @brief
    *       Overridden function implementation which creates required number of sessions based on the test Id
    *   @param
    *       None
    *   @return
    *       CDKResult success if sessions could be created or failure
    ***************************************************************************************************************************/
    CDKResult OfflinePipelineTest::CreateSessions()
    {
        CDKResult result = CDKResultSuccess;
        ChiCallBacks callbacks = { 0 };

        callbacks.ChiNotify                      = ChiTestCase::ProcessMessage;
        callbacks.ChiProcessCaptureResult        = ChiTestCase::QueueCaptureResult;
        callbacks.ChiProcessPartialCaptureResult = ChiTestCase::QueuePartialCaptureResult;

        m_perSessionPvtData.pTestInstance = this;
        m_perSessionPvtData.sessionId = OfflineSession;

        m_pChiSession = ChiSession::Create(&m_pChiPipeline, 1, &callbacks, &m_perSessionPvtData);

        if (m_pChiSession == nullptr)
        {
            NT_LOG_ERROR( "offline session could not be created");
            result = CDKResultEFailed;
        }
        else
        {
            // Start stream on before sending PCRs
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
    *   OfflinePipelineTest::GenerateOfflineCaptureRequest()
    *
    *   @brief
    *       Generate an offline pipeline request
    *   @param
    *       [in] uint64_t   frameNumber     framenumber associated with the request
    *   @return
    *       CDKResult success if request could be submitted or failure
    ***************************************************************************************************************************/
    CDKResult OfflinePipelineTest::GenerateOfflineCaptureRequest(uint64_t frameNumber)
    {
        CDKResult result = CDKResultSuccess;
        static const uint32_t NumOutputBuffers = m_numStreams - 1; // not considering the input stream
        BufferManager::NativeChiBuffer* outputBuffers = SAFE_NEW() BufferManager::NativeChiBuffer[NumOutputBuffers];
        uint32_t outputIndex = 0;

        std::map<ChiStream*, BufferManager*>::iterator it;

        uint32_t requestId = FRAME_REQUEST_MOD(frameNumber);
        memset(&m_offlineRequest[requestId], 0, sizeof(CHICAPTUREREQUEST));

        for (it = m_streamBufferMap.begin(); it != m_streamBufferMap.end(); ++it)
        {
            void* pBuffer = nullptr;
            BufferManager* manager = it->second;
            if (it->first->streamType != ChiStreamTypeInput)
            {
                pBuffer = manager->GetOutputBufferForRequest();
                if (pBuffer == nullptr)
                {
                    delete[] outputBuffers;
                    return CDKResultENoMore;
                }
                outputBuffers[outputIndex] = *static_cast<BufferManager::NativeChiBuffer*>(pBuffer);
                outputIndex++;
            }
            else
            {
                pBuffer = manager->GetInputBufferForRequest();
                if (pBuffer == nullptr)
                {
                    delete[] outputBuffers;
                    return CDKResultENoMore;
                }

                m_offlineRequest[requestId].pInputBuffers = static_cast<BufferManager::NativeChiBuffer*>(pBuffer);
            }
        }

        m_offlineRequest[requestId].frameNumber     = frameNumber;
        m_offlineRequest[requestId].hPipelineHandle = m_pChiPipeline->GetPipelineHandle();
        m_offlineRequest[requestId].numOutputs      = NumOutputBuffers;
        m_offlineRequest[requestId].pOutputBuffers  = outputBuffers;
        m_offlineRequest[requestId].numInputs       = 1;
        m_offlineRequest[requestId].pPrivData       = &m_requestPvtData;

#ifdef OLD_METADATA
        m_offlineRequest[requestId].pMetadata = allocate_camera_metadata(METADATA_ENTRIES, 100 * 1024);
        NATIVETEST_UNUSED_PARAM(m_pPipelineMetadataInfo);
#else
        //Get the input metabuffer from the pool
        m_offlineRequest[requestId].pInputMetadata = m_pChiMetadataUtil->GetInputMetabufferFromPool(requestId);
        NT_EXPECT(m_offlineRequest[requestId].pInputMetadata != nullptr, "Failed to create Input Metabuffer before sending request");

        //For FD node test set metadata tag
        SetSpecialMetadata(frameNumber, requestId);

        //Get the output metabuffer from the pool
        m_offlineRequest[requestId].pOutputMetadata = m_pChiMetadataUtil->GetOutputMetabufferFromPool(requestId,
            &m_pPipelineMetadataInfo.publishTagArray[0], m_pPipelineMetadataInfo.publishTagCount);
        NT_EXPECT(m_offlineRequest[requestId].pOutputMetadata != nullptr, "Failed to create Output Metabuffer before sending request");
#endif // OLD_METADATA

        memset(&m_submitRequest, 0, sizeof(CHIPIPELINEREQUEST));
        m_submitRequest.pSessionHandle   = m_pChiSession->GetSessionHandle();
        m_submitRequest.numRequests      = 1;
        m_submitRequest.pCaptureRequests = &m_offlineRequest[requestId];

        AtomicIncrement(NumOutputBuffers);

        NT_LOG_DEBUG( "Number of pending buffers remaining: %d after sending request: %" PRIu64,
            GetPendingBufferCount(), frameNumber);

        result = m_pChiModule->SubmitPipelineRequest(&m_submitRequest);

        delete[] outputBuffers;
        return result;
    }

    /***************************************************************************************************************************
    *   OfflinePipelineTest::CommonProcessCaptureResult()
    *
    *   @brief
    *       Overridden function implementation which processes the capture result obtained from driver
    *   @param
    *        [in]  CHICAPTURERESULT*     pCaptureResult         pointer to capture result
    *        [in]  void*                 pPrivateCallbackData   pointer private callback data
    *   @return
    *       None
    ***************************************************************************************************************************/
    void OfflinePipelineTest::CommonProcessCaptureResult(
        ChiCaptureResult*   pCaptureResult,
        SessionPrivateData* pSessionPrivateData)
    {
        CDKResult result = CDKResultSuccess;
        uint32_t  resultFrameNum = pCaptureResult->frameworkFrameNum;
        uint32_t  numOutputBuffers = pCaptureResult->numOutputBuffers;
        uint32_t  numPartialMetadata = pCaptureResult->numPartialMetadata;
        SessionId sessionId = static_cast<SessionId>(pSessionPrivateData->sessionId);

        NT_LOG_DEBUG( "Received capture result for frame: %d", resultFrameNum);

#ifndef OLD_METADATA
        if (m_pChiMetadataUtil != nullptr)
        {
            m_pChiMetadataUtil->VerifyCaptureResultMetadata(static_cast<CHIMETAHANDLE>(pCaptureResult->pOutputMetadata));
        }
#endif // OLD_METADATA

        if (sessionId == OfflineSession)
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
    *   OfflinePipelineTest::DestroyResources()
    *
    *   @brief
    *       Overridden function implementation which destroys all created resources/objects
    *   @param
    *       None
    *   @return
    *       None
    ***************************************************************************************************************************/
    void OfflinePipelineTest::DestroyResources()
    {
        if ((nullptr != m_pChiSession) && (nullptr != m_pChiPipeline))
        {
            m_pChiPipeline->DeactivatePipeline(m_pChiSession->GetSessionHandle());

            if (m_pChiSession != nullptr)
            {
                m_pChiSession->DestroySession();
                m_pChiSession = nullptr;
            }

            if (m_pChiPipeline != nullptr)
            {
                m_pChiPipeline->DestroyPipeline();
                m_pChiPipeline = nullptr;
            }
        }

        DestroyCommonResources();
    }

}

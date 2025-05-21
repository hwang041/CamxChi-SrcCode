//*****************************************************************************************************************************
// Copyright (c) 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*****************************************************************************************************************************

#include "recipe_test.h"

namespace tests
{

// Initialize static variables
RecipeTest*        RecipeTest::m_pTestObj;

void RecipeTest::Setup()
{
    // Initialize parent class
    ChiTestCase::Setup();
    // Save instance so static functions can access later
    m_pTestObj = this;
}

void RecipeTest::Teardown()
{
    // Tear down parent class
    ChiTestCase::Teardown();
}

/***************************************************************************************************************************
*   RecipeTest::SetupStreams()
*
*   @brief
*       Overridden function implementation which defines the stream information based on the test Id
*   @param
*       None
*   @return
*       CDKResult success if stream objects could be created or failure
***************************************************************************************************************************/
CDKResult RecipeTest::SetupStreams()
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
            NT_LOG_ERROR("Input width and height required with input image. Aborting.");
            return CDKResultEInvalidArg;
        }
    }

    switch (m_testId)
    {
    case TestIFEGenericTestgen:
    case TestIFEGeneric:
        m_numStreams = 1;

        //1. Configurable output stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedOutputFormat;
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? FULLHD : m_selectedOutputSize;
        }
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = true;

        m_streamInfo.num_streams = m_numStreams;
        break;

    case TestIFEDownscaleGenericTestgen:
        m_numStreams = 3;

        //1. IFE full out stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedOutputFormat;
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? FULLHD : m_selectedOutputSize;
        }
        m_streamId[streamIndex]   = IFEOutputPortFull;
        m_isRealtime[streamIndex] = true;
        streamIndex++;

        //2. DS4 stream
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize/4;
        }
        else
        {
            m_resolution[streamIndex] = ((m_selectedOutputSize.isInvalidSize()) ? FULLHD : m_selectedOutputSize) / 4;
        }
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatPD10;
        m_streamId[streamIndex]   = IFEOutputPortDS4;
        m_isRealtime[streamIndex] = true;
        streamIndex++;

        //2. DS16 stream
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize / 16;
        }
        else
        {
            m_resolution[streamIndex] = ((m_selectedOutputSize.isInvalidSize()) ? FULLHD : m_selectedOutputSize) / 16;
        }
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatPD10;
        m_streamId[streamIndex]   = IFEOutputPortDS16;
        m_isRealtime[streamIndex] = true;

        m_streamInfo.num_streams = m_numStreams;
        break;

    case TestIPEGeneric:
        m_numStreams = 2;

        //1. Configurable input stream
        m_resolution[streamIndex] = (m_selectedInputSize.isInvalidSize()) ? VGA : m_selectedInputSize;
        m_direction[streamIndex]  = ChiStreamTypeInput;
        m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
        m_streamId[streamIndex]   = CONFIG_INPUT;
        m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //2. Configurable output stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedOutputFormat;;
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? FULLHD : m_selectedOutputSize;
        }
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = false;

        m_streamInfo.num_streams = m_numStreams;
        break;

    case TestIPEGeneric2StreamDisplay:

        m_numStreams = 3;

        //1. Configurable input stream
        m_resolution[streamIndex] = (m_selectedInputSize.isInvalidSize()) ? VGA : m_selectedInputSize;
        m_direction[streamIndex]  = ChiStreamTypeInput;
        m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedInputFormat;
        m_streamId[streamIndex]   = CONFIG_INPUT;
        m_streamInfo.filename     = (strlen(inputFileName) == 0) ? IPE_COLORBAR_VGA : inputFileName;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //2. Configurable output stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedOutputFormat;;
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? FULLHD : m_selectedOutputSize;
        }
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //3. Static DISPLAY output stream
        m_resolution[streamIndex] = VGA;
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
        m_streamId[streamIndex]   = IPEOutputPortDisplay;
        m_isRealtime[streamIndex] = false;

        m_streamInfo.num_streams = m_numStreams;
        break;

    case TestBPSGeneric:
        m_numStreams = 2;

        //1. Configurable input stream
        m_resolution[streamIndex] = (m_selectedInputSize.isInvalidSize()) ? FULLHD : m_selectedInputSize;
        m_direction[streamIndex]  = ChiStreamTypeInput;
        m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
        m_streamId[streamIndex]   = CONFIG_INPUT;
        m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //2. Configurable output stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatUBWCTP10 : m_selectedOutputFormat;
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? FULLHD : m_selectedOutputSize;
        }
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = false;

        m_streamInfo.num_streams  = m_numStreams;
        break;

    case TestIFEGeneric2Stream:
    case TestIFEGeneric2StreamDisplay:
        m_numStreams = 2;

        //1. Configurable output stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedOutputFormat;
        // for non-RDI stream/format, use non-RDI size (if given at runtime)
        if (!IsRDIStream(m_format[streamIndex]) && (!m_selectedOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedRdiOutputSize.isInvalidSize()) ? FULLHD : m_selectedRdiOutputSize;
        }
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = true;
        streamIndex++;

        //2. Static out stream
        m_resolution[streamIndex] = FULLHD;
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
        m_streamId[streamIndex]   = (m_testId == TestIFEGeneric2Stream) ? IFEOutputPortFull : IFEOutputPortDisplayFull;;
        m_isRealtime[streamIndex] = true;

        m_streamInfo.num_streams  = m_numStreams;
        break;

    case TestIFEGeneric2StreamTestgen:
    case TestIFEGeneric2StreamDisplayTestgen:
        m_isCamIFTestGen = true;
        m_numStreams = 2;

        //1. Configurable output stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedOutputFormat;
	    // for non-RDI stream/format, use non-RDI size (if given at runtime)
        if (!IsRDIStream(m_format[streamIndex]) && (!m_selectedOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedRdiOutputSize.isInvalidSize()) ? FULLHD : m_selectedRdiOutputSize;
        }
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = true;
        streamIndex++;

        //2. Static output stream
        m_resolution[streamIndex] = FULLHD;
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
        m_streamId[streamIndex]   = (m_testId == TestIFEGeneric2StreamTestgen) ? IFEOutputPortFull : IFEOutputPortDisplayFull;
        m_isRealtime[streamIndex] = true;

        m_streamInfo.num_streams  = m_numStreams;
        break;

    case TestBPSDownscaleGeneric:
        m_numStreams = 5;

        //1. Configurable input stream
        m_resolution[streamIndex] = (m_selectedInputSize.isInvalidSize()) ? HD4K : m_selectedInputSize;
        m_direction[streamIndex]  = ChiStreamTypeInput;
        m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
        m_streamId[streamIndex]   = CONFIG_INPUT;
        m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_IDEALRAW_UHD : inputFileName;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //2. Configurable output stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedOutputFormat;
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? HD4K : m_selectedOutputSize;
        }
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //3. BPS DS4 out stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatPD10;
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize / 4;
        }
        else
        {
            m_resolution[streamIndex] = ((m_selectedOutputSize.isInvalidSize()) ? HD4K : m_selectedOutputSize) / 4;
        }
        m_streamId[streamIndex]   = BPSOutputPortDS4;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //4. BPS DS16 out stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatPD10;
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize / 16;
        }
        else
        {
            m_resolution[streamIndex] = ((m_selectedOutputSize.isInvalidSize()) ? HD4K : m_selectedOutputSize) / 16;
        }
        m_streamId[streamIndex]   = BPSOutputPortDS16;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        // This check needs to be done to highest downscaler being used for a given case, in this case 64
        if (m_selectedInputSize.isICALimitHit(64)) {
            NT_LOG_WARN( "Selected resolution is hitting ICA minimum width and height requirements (%d %d)", ICAMinWidthPixels, ICAMinHeightPixels);
        }

        //5. BPS DS64 out stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatPD10;
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize / 64;
        }
        else
        {
            m_resolution[streamIndex] = ((m_selectedOutputSize.isInvalidSize()) ? HD4K : m_selectedOutputSize) / 64;
        }
        m_streamId[streamIndex]   = BPSOutputPortDS64;
        m_isRealtime[streamIndex] = false;

        m_streamInfo.num_streams = m_numStreams;
        break;

    case TestBPSGeneric2Stream:
        m_numStreams = 3;

        //1. Configurable input stream
        m_resolution[streamIndex] = (m_selectedInputSize.isInvalidSize()) ? FULLHD : m_selectedInputSize;
        m_direction[streamIndex]  = ChiStreamTypeInput;
        m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
        m_streamId[streamIndex]   = CONFIG_INPUT;
        m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //2. Configurable output stream
        // Defaults to DS4 port, so size should be 1/4th default input size
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatPD10 : m_selectedOutputFormat;
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? (FULLHD / 4) : m_selectedOutputSize;
        }
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //3. Static FULL output stream
        m_resolution[streamIndex] = FULLHD;
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatUBWCTP10;
        m_usageFlag[streamIndex]  = GrallocUsageTP10;
        m_streamId[streamIndex]   = BPSOutputPortFull;
        m_isRealtime[streamIndex] = false;

        m_streamInfo.num_streams  = m_numStreams;
        break;

    case TestTFEGenericTestgen:
        m_numStreams = 1;

        //1. Configurable output stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedOutputFormat;
        // for non-RDI stream/format, use non-RDI size (if given at runtime)
        if ((!IsRDIStream(m_format[streamIndex])) && (!m_selectedOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedRdiOutputSize.isInvalidSize()) ? FULLHD : m_selectedRdiOutputSize;
        }
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = true;

        m_streamInfo.num_streams = m_numStreams;
        break;

    case TestOPEGeneric:
        m_numStreams = 2;

        //1. Configurable input stream
        m_resolution[streamIndex] = (m_selectedInputSize.isInvalidSize()) ? FULLHD : m_selectedInputSize;
        m_direction[streamIndex]  = ChiStreamTypeInput;
        m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
        m_streamId[streamIndex]   = CONFIG_INPUT;
        m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //2. Configurable output stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedOutputFormat;
        // for RDI stream/format, use RDI size (if given at runtime)
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? FULLHD : m_selectedOutputSize;
        }
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = false;

        m_streamInfo.num_streams = m_numStreams;
        break;

    case TestTFEGeneric2StreamTestgen:
        m_numStreams = 2;

        //1. Configurable output stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedOutputFormat;
        if ((!IsRDIStream(m_format[streamIndex])) && (!m_selectedOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedRdiOutputSize.isInvalidSize()) ? FULLHD : m_selectedRdiOutputSize;
        }
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = true;
        streamIndex++;

        //2. Static output stream
        m_resolution[streamIndex] = FULLHD;
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatRaw16;
        m_streamId[streamIndex]   = TFEOutputPortFull;
        m_isRealtime[streamIndex] = true;

        m_streamInfo.num_streams = m_numStreams;
        break;

    case TestOPEGeneric2StreamDisplay:

        m_numStreams = 3;

        //1. Configurable input stream
        m_resolution[streamIndex] = (m_selectedInputSize.isInvalidSize()) ? FULLHD : m_selectedInputSize;
        m_direction[streamIndex]  = ChiStreamTypeInput;
        m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
        m_streamId[streamIndex]   = CONFIG_INPUT;
        m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //2. Configurable output stream
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatYCbCr420_888 : m_selectedOutputFormat;
        if (IsRDIStream(m_format[streamIndex]) && (!m_selectedRdiOutputSize.isInvalidSize()))
        {
            m_resolution[streamIndex] = m_selectedRdiOutputSize;
        }
        else
        {
            m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? FULLHD : m_selectedOutputSize;
        }
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //3. Static DISPLAY output stream
        m_resolution[streamIndex] = VGA;
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
        m_streamId[streamIndex]   = OPEOutputPortDisplay;
        m_isRealtime[streamIndex] = false;

        m_streamInfo.num_streams = m_numStreams;
        break;

    case TestOPEGeneric3StreamDisplayStats:

        m_numStreams = 4;

        //1. Configurable input stream
        m_resolution[streamIndex] = (m_selectedInputSize.isInvalidSize()) ? FULLHD : m_selectedInputSize;
        m_direction[streamIndex]  = ChiStreamTypeInput;
        m_format[streamIndex]     = (m_selectedInputFormat == noFormatOverride) ? ChiStreamFormatRaw16 : m_selectedInputFormat;
        m_streamId[streamIndex]   = CONFIG_INPUT;
        m_streamInfo.filename     = (strlen(inputFileName) == 0) ? BPS_COLORBAR_FHD : inputFileName;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //2. Configurable output stream
        m_resolution[streamIndex] = Size(32768, 1);
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = (m_selectedOutputFormat == noFormatOverride) ? ChiStreamFormatBlob : m_selectedOutputFormat;
        m_streamId[streamIndex]   = CONFIG_OUTPUT;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //3. Static VIDEO output stream
        m_resolution[streamIndex] = FULLHD;
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
        m_streamId[streamIndex]   = OPEOutputPortVideo;
        m_isRealtime[streamIndex] = false;
        streamIndex++;

        //4. Static DISPLAY output stream
        m_resolution[streamIndex] = VGA;
        m_direction[streamIndex]  = ChiStreamTypeOutput;
        m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
        m_streamId[streamIndex]   = OPEOutputPortDisplay;
        m_isRealtime[streamIndex] = false;

        m_streamInfo.num_streams = m_numStreams;
        break;

    default:
        NT_LOG_ERROR("Unknown testcase Id provided: [%d]", m_testId);
        result = CDKResultENoSuch;
        break;
    }

    // Log the user input image name
    if (strlen(inputFileName) != 0)
    {
        NT_LOG_DEBUG("Using input image: %s", m_streamInfo.filename);
    }

    if (result == CDKResultSuccess)
    {
        m_pRequiredStreams = SAFE_NEW() CHISTREAM[m_streamInfo.num_streams];
        camera3_stream_t* pCamStreams = CreateStreams(m_streamInfo);
        if (NULL == pCamStreams)
        {
            NT_LOG_ERROR("Failed to create pCamStreams from m_streamInfo!");
            result = CDKResultEFailed;
        }
        else if (NULL == m_pRequiredStreams) {
            NT_LOG_ERROR("Failed to initialize CHI streams");
            result = CDKResultEFailed;
        }
        else
        {
            ConvertCamera3StreamToChiStream(pCamStreams, m_pRequiredStreams, m_streamInfo.num_streams);
            delete[] pCamStreams;   // Clean up after converting to m_pRequiredStreams

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

    return result;
}

/***************************************************************************************************************************
*   RecipeTest::SetupPipelines()
*
*   @brief
*       Overridden function implementation which creates pipeline objects based on the test Id
*   @param
*       [in]  int                 cameraId    cameraId to be associated with the pipeline
*       [in]  ChiSensorModeInfo*  sensorMode  sensor mode to be used for the pipeline
*   @return
*       CDKResult success if pipelines could be created or failure
***************************************************************************************************************************/
CDKResult RecipeTest::SetupPipelines(int cameraId, ChiSensorModeInfo* sensorMode)
{
    CDKResult result = CDKResultSuccess;

    switch (m_testId)
    {
    case TestIFEGenericTestgen:
        m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFEGenericTestgen);
        break;
    case TestIFEDownscaleGenericTestgen:
        m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFEDownscaleGenericTestgen);
        break;
    case TestIFEGeneric:
        m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFEGeneric);
        break;
    case TestIPEGeneric:
        m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineIPEGeneric);
        break;
    case TestBPSGeneric:
        m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSGeneric);
        break;
    case TestBPSGeneric2Stream:
        m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSGeneric2Stream);
        break;
    case TestIFEGeneric2Stream:
        m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFEGeneric2Stream);
        break;
    case TestIFEGeneric2StreamTestgen:
        m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFEGeneric2StreamTestgen);
        break;
    case TestIFEGeneric2StreamDisplay:
        m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFEGeneric2StreamDisplay);
        break;
    case TestIFEGeneric2StreamDisplayTestgen:
        m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFEGeneric2StreamDisplayTestgen);
        break;
    case TestBPSDownscaleGeneric:
        m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineBPSDownscaleGeneric);
        break;
    case TestIPEGeneric2StreamDisplay:
        m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineIPEGeneric2StreamDisplay);
        break;
        case TestTFEGenericTestgen:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeTFEGenericTestgen);
            break;
        case TestOPEGeneric:
            m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineOPEGeneric);
            break;
        case TestTFEGeneric2StreamTestgen:
            m_pChiPipeline[Realtime] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeTFEGeneric2StreamTestgen);
            break;
        case TestOPEGeneric2StreamDisplay:
            m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineOPEGeneric2StreamDisplay);
            break;
        case TestOPEGeneric3StreamDisplayStats:
            m_pChiPipeline[Offline] = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::OfflineOPEGeneric3StreamDisplayStats);
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
        NT_LOG_ERROR("Invalid PipelineConfig provided! %d", m_pipelineConfig);
        break;
    }

    return result;
}

/***************************************************************************************************************************
*   RecipeTest::CreateSessions()
*
*   @brief
*       Overridden function implementation which creates required number of sessions based on the test Id
*   @param
*       None
*   @return
*       CDKResult success if sessions could be created or failure
***************************************************************************************************************************/
CDKResult RecipeTest::CreateSessions()
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
        NT_LOG_ERROR("Invalid PipelineConfig provided! %d", m_pipelineConfig);
        break;
    }

    return result;
}

/***************************************************************************************************************************
*   RecipeTest::CreateSessionHelper()
*
*   @brief
*       Helper function to create a single session, using the session Id given
*   @param
*       [in]    SessionId   sessionId   session Id to create session for
*   @return
*       CDKResult success if session could be created or failure
***************************************************************************************************************************/
CDKResult RecipeTest::CreateSessionHelper(SessionId sessionId)
{
    CDKResult result = CDKResultSuccess;
    ChiCallBacks callbacks = {};
    PipelineIndex pipeIndex = (sessionId == RealtimeSession) ? Realtime : Offline;

    callbacks.ChiNotify = ChiTestCase::ProcessMessage;
    callbacks.ChiProcessCaptureResult = ChiTestCase::QueueCaptureResult;
    callbacks.ChiProcessPartialCaptureResult = ChiTestCase::QueuePartialCaptureResult;

    m_perSessionPvtData[sessionId].pTestInstance = this;
    m_perSessionPvtData[sessionId].sessionId = sessionId;
    m_pChiSession[sessionId] = ChiSession::Create(&m_pChiPipeline[pipeIndex], 1, &callbacks, &m_perSessionPvtData[sessionId]);

    if (NULL == m_pChiSession[sessionId])
    {
        NT_LOG_ERROR("%s session could not be created", (sessionId == RealtimeSession) ? "Realtime" : "Offline");
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

/***************************************************************************************************************************
*   RecipeTest::CommonProcessCaptureResult()
*
*   @brief
*       Overridden function implementation which processes the capture result obtained from driver
*   @param
*       [in]    CHICAPTURERESULT*       pCaptureResult          pointer to capture result
*       [in]    SessionPrivateData*     pPrivateCallbackData    pointer private callback data
*   @return
*       None
***************************************************************************************************************************/
void RecipeTest::CommonProcessCaptureResult(ChiCaptureResult* pCaptureResult, SessionPrivateData* pSessionPrivateData)
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

    if (sessionId == RealtimeSession || sessionId == OfflineSession)
    {
        for (uint32_t bufferIndex = 0; bufferIndex < numOutputBuffers; bufferIndex++)
        {
            BufferManager::NativeChiBuffer* outBuffer = const_cast<BufferManager::NativeChiBuffer*>(&pCaptureResult->
                pOutputBuffers[bufferIndex]);
            BufferManager* manager = m_streamBufferMap[outBuffer->pStream];
            if (NULL == manager)
            {
                NT_LOG_ERROR("Could not find buffer manger for given stream: %p in frame: %d",
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
        NT_LOG_ERROR("Unknown Session Id: %d obtained", sessionId);
        result = CDKResultEInvalidState;
    }

    if (result == CDKResultSuccess)
    {
        AtomicDecrement(numOutputBuffers);
        NT_LOG_INFO("Number of pending buffers remaining: %d after receiving the result for frame: %d",
            GetPendingBufferCount(), resultFrameNum);
    }
}

/***************************************************************************************************************************
*   RecipeTest::DestroyResources()
*
*   @brief
*       Overridden function implementation which destroys all created resources / objects
*   @param
*       None
*   @return
*       None
***************************************************************************************************************************/
void RecipeTest::DestroyResources()
{
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
        NT_LOG_ERROR("Invalid PipelineConfig provided! %d", m_pipelineConfig);
        break;
    }

    DestroyCommonResources();
}

/***************************************************************************************************************************
*   RecipeTest::DestroyResourcesHelper()
*
*   @brief
*       Helper for DestroyResources to destroy resources depending on session Id
*   @param
*       [in]    SessionId   sessionId   session Id to destoy resources for
*   @return
*       None
***************************************************************************************************************************/
void RecipeTest::DestroyResourcesHelper(SessionId sessionId)
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

/***************************************************************************************************************************
*   RecipeTest::GenerateRealtimeCaptureRequest()
*
*   @brief
*       Generate a realtime pipeline request
*   @param
*       [in] uint64_t   frameNumber     frame number associated with the request
*   @return
*       CDKResult success if request could be submitted or failure
***************************************************************************************************************************/
CDKResult RecipeTest::GenerateRealtimeCaptureRequest(uint64_t frameNumber)
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

    memset(&m_submitRequest, 0, sizeof(CHIPIPELINEREQUEST));
    m_submitRequest.pSessionHandle = m_pChiSession[RealtimeSession]->GetSessionHandle();
    m_submitRequest.numRequests = 1;
    m_submitRequest.pCaptureRequests = &m_realtimeRequest[requestId];

    result = m_pChiModule->SubmitPipelineRequest(&m_submitRequest);
    if (CDKResultSuccess == result)
    {
        // Only increment pending buffer count if submit pipeline request succeeds
        AtomicIncrement(numOutputBuffers);
        NT_LOG_DEBUG("Number of pending buffers remaining: %d after sending request for frame: %" PRIu64,
            GetPendingBufferCount(), frameNumber);
    }
    else
    {
        NT_LOG_ERROR("SubmitPipelineRequest to driver failed!");
    }

    return result;
}

/***************************************************************************************************************************
*   RecipeTest::GenerateOfflineCaptureRequest()
*
*   @brief
*       Generate an offline pipeline request
*   @param
*       [in] uint64_t   frameNumber     frame number associated with the request
*   @return
*       CDKResult success if request could be submitted or failure
***************************************************************************************************************************/
CDKResult RecipeTest::GenerateOfflineCaptureRequest(uint64_t frameNumber)
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
            NT_LOG_ERROR("Invalid ChiStreamType provided! %d", it->first->streamType);
            break;
        }
    }

    m_offlineRequest[requestId].frameNumber = frameNumber;
    m_offlineRequest[requestId].hPipelineHandle = m_pChiPipeline[Offline]->GetPipelineHandle();
    m_offlineRequest[requestId].pInputBuffers = m_pInputBuffer;
    m_offlineRequest[requestId].numOutputs = numOutputBuffers;
    m_offlineRequest[requestId].pOutputBuffers = m_offlineOutputBuffers;
    m_offlineRequest[requestId].numInputs = 1;
    m_offlineRequest[requestId].pPrivData = &m_requestPvtData[OfflineSession];

#ifdef OLD_METADATA
    m_offlineRequest[requestId].pMetadata = allocate_camera_metadata(METADATA_ENTRIES, 100 * 1024);
    NATIVETEST_UNUSED_PARAM(m_pPipelineMetadataInfo);
#else
    // Get the input metabuffer from the pool
    m_offlineRequest[requestId].pInputMetadata = m_pChiMetadataUtil->GetInputMetabufferFromPool(requestId);
    NT_EXPECT(m_offlineRequest[requestId].pInputMetadata != nullptr, "Failed to create Input Metabuffer before sending request");

    // Get the output metabuffer from the pool
    m_offlineRequest[requestId].pOutputMetadata = m_pChiMetadataUtil->GetOutputMetabufferFromPool(requestId,
        m_pPipelineMetadataInfo[Offline].publishTagArray, m_pPipelineMetadataInfo[Offline].publishTagCount);
    NT_EXPECT(m_offlineRequest[requestId].pOutputMetadata != nullptr, "Failed to create Output Metabuffer before sending request");
#endif // OLD_METADATA

    memset(&m_submitRequest, 0, sizeof(CHIPIPELINEREQUEST));
    m_submitRequest.pSessionHandle = m_pChiSession[OfflineSession]->GetSessionHandle();
    m_submitRequest.numRequests = 1;
    m_submitRequest.pCaptureRequests = &m_offlineRequest[requestId];

    result = m_pChiModule->SubmitPipelineRequest(&m_submitRequest);
    if (CDKResultSuccess == result)
    {
        // Only increment pending buffer count if submit pipeline request succeeds
        AtomicIncrement(numOutputBuffers);
        NT_LOG_ERROR("Number of pending buffers remaining: %d after sending request for frame: %" PRIu64,
            GetPendingBufferCount(), frameNumber);
    }
    else
    {
        NT_LOG_ERROR("SubmitPipelineRequest to driver failed!");
    }

    return result;
}

/***************************************************************************************************************************
*   RecipeTest::TestRealtimePipeline
*
*   @brief
*       Recipe test for realtime pipelines
*   @param
*       [in]    TestId      testId          Test identifier
*   @return
*       None
***************************************************************************************************************************/
void RecipeTest::TestRealtimePipeline(TestId testId)
{
    // Get list of cameras to test
    std::vector <int> camList = m_pChiModule->GetCameraList();

    m_selectedOutputSize = Size(CmdLineParser::GetOutputWidth(), CmdLineParser::GetOutputHeight());
    m_selectedRdiOutputSize = Size(CmdLineParser::GetRdiOutputWidth(), CmdLineParser::GetRdiOutputHeight());

    m_selectedInputFormat = static_cast<CHISTREAMFORMAT>(CmdLineParser::GetInputFormat());
    m_selectedOutputFormat = static_cast<CHISTREAMFORMAT>(CmdLineParser::GetOutputFormat());

    m_testId = testId;
    m_pipelineConfig = RealtimeConfig;

    for (size_t camCounter = 0; camCounter < camList.size(); camCounter++)
    {
        // Get the actual camera ID to test
        int cameraId = camList[camCounter];

        // Create chistream objects from streamcreatedata
        NT_ASSERT(SetupStreams() == CDKResultSuccess, "SetupStreams Failed");

        ChiSensorModeInfo* testSensorMode = nullptr;
        testSensorMode = m_pChiModule->GetClosestSensorMode(cameraId, m_streamInfo.maxRes);

        NT_ASSERT(nullptr != testSensorMode, "Sensor mode is NULL for cameraId: ",cameraId);

        NT_LOG_INFO("Camera %d chosen sensor mode: %u, width: %u, height: %u", cameraId,
            testSensorMode->modeIndex, testSensorMode->frameDimension.width, testSensorMode->frameDimension.height);

        // TODO: Set number of batched frames based on usecase
        testSensorMode->batchedFrames = 1;

        // For RDI cases, we need to make sure stream resolution matches sensor mode
        for (int streamIndex = 0; streamIndex < m_numStreams; streamIndex++)
        {
            if (IsRDIStream(m_pRequiredStreams[streamIndex].format))
            {
                if (!m_selectedRdiOutputSize.isInvalidSize()) {
                    NT_LOG_INFO("OVERRIDE: RDI resolution set by User width: %d, height: %d ",
                        m_selectedRdiOutputSize.width, m_selectedRdiOutputSize.height);
                    m_pRequiredStreams[streamIndex].width = m_selectedRdiOutputSize.width;
                    m_pRequiredStreams[streamIndex].height = m_selectedRdiOutputSize.height;
                }
                else if (!m_isCamIFTestGen)
                {
                    NT_LOG_INFO("Selected RDI resolution based on Sensor mode width: %d, height: %d ",
                        testSensorMode->frameDimension.width, testSensorMode->frameDimension.height);
                    m_pRequiredStreams[streamIndex].width = testSensorMode->frameDimension.width;
                    m_pRequiredStreams[streamIndex].height = testSensorMode->frameDimension.height;
                }
            }
        }

        // Create pipelines
        NT_ASSERT(SetupPipelines(cameraId, testSensorMode) == CDKResultSuccess, "Pipelines Setup failed");
        // Create sessions
        NT_ASSERT(CreateSessions() == CDKResultSuccess,"Necessary sessions could not be created");

        // Initialize buffer manager and metabuffer pools
        NT_ASSERT(InitializeBufferMangers(cameraId) == CDKResultSuccess, "Buffer managers could not be initialized");
#ifndef OLD_METADATA
        NT_ASSERT(m_pChiMetadataUtil->CreateInputMetabufferPool(cameraId, MAX_REQUESTS) == CDKResultSuccess,
            "Input metabuffer pool for camera Id: %d could not be created!", cameraId);
        NT_ASSERT(m_pChiMetadataUtil->CreateOutputMetabufferPool(MAX_REQUESTS) == CDKResultSuccess,
            "Output metabuffer pool could not be created!");
#endif // OLD_METADATA
        // Create and submit capture requests
        uint64_t frameNumber = START_FRAME;
        for (int frameIndex = 1; frameIndex <= CmdLineParser::GetFrameCount(); frameIndex++, frameNumber++)
        {
            NT_ASSERT(GenerateRealtimeCaptureRequest(frameNumber) == CDKResultSuccess,
                 "Submit pipeline request failed for frameNumber: %d", frameNumber);
        }

        // Wait for all results
        NT_ASSERT(WaitForResults() == CDKResultSuccess,
            "There are pending buffers not returned by driver after several retries");
        // Destroy all resources created
        DestroyResources();
    }
}

/***************************************************************************************************************************
*   RecipeTest::TestOfflinePipeline
*
*   @brief
*       Recipe test for offline pipelines
*   @param
*       [in]    TestId      testId          Test identifier
*   @return
*       None
***************************************************************************************************************************/
void RecipeTest::TestOfflinePipeline(TestId testId)
{
    m_selectedInputSize = Size(CmdLineParser::GetInputWidth(), CmdLineParser::GetInputHeight());
    m_selectedInputFormat = static_cast<CHISTREAMFORMAT>(CmdLineParser::GetInputFormat());

    m_selectedOutputSize = Size(CmdLineParser::GetOutputWidth(), CmdLineParser::GetOutputHeight());
    m_selectedOutputFormat = static_cast<CHISTREAMFORMAT>(CmdLineParser::GetOutputFormat());

    m_testId = testId;
    m_pipelineConfig = OfflineConfig;

    // Create chistream objects from streamcreatedata
    NT_ASSERT(SetupStreams() == CDKResultSuccess, "SetupStreams Failed");

    // Create pipelines - offline pipelines don't require cameraId and sensor mode
    NT_ASSERT(SetupPipelines(0, NULL) == CDKResultSuccess,"Pipelines Setup failed");

    // Create sessions
    NT_ASSERT(CreateSessions() == CDKResultSuccess,"Necessary sessions could not be created");

    // Initialize buffer manager and metabuffer pools
    NT_ASSERT(InitializeBufferMangers(-1) == CDKResultSuccess, "Buffer managers could not be initialized");
#ifndef OLD_METADATA
    // hard coded the camera Id as offline piptlines does not need camera Id
    NT_ASSERT(m_pChiMetadataUtil->CreateInputMetabufferPool(0, MAX_REQUESTS) == CDKResultSuccess,
         "Input metabuffer pool for camera Id: 0 could not be created!");
    NT_ASSERT(m_pChiMetadataUtil->CreateOutputMetabufferPool(MAX_REQUESTS) == CDKResultSuccess,
         "Output metabuffer pool could not be created!");
#endif // OLD_METADATA

    // Create and submit capture requests
    uint64_t frameNumber = START_FRAME;
    for (int frameIndex = 1; frameIndex <= CmdLineParser::GetFrameCount(); frameIndex++, frameNumber++)
    {
        NT_ASSERT(GenerateOfflineCaptureRequest(frameNumber) == CDKResultSuccess,
            "Submit pipeline request failed for frameNumber: ", frameNumber);
    }

    // Wait for all results
    NT_ASSERT(WaitForResults() == CDKResultSuccess,
        "There are pending buffers not returned by driver after several retries");

    // Destroy all resources created
    DestroyResources();
}

/***************************************************************************************************************************
*   RecipeTest::TestMixedPipeline
*
*   @brief
*       Recipe test for mixed pipelines
*   @param
*       [in]    TestId      testId          Test identifier
*   @return
*       None
***************************************************************************************************************************/
void RecipeTest::TestMixedPipeline(TestId testId)
{
    int numOfCameras = m_pChiModule->GetNumberCameras();
    m_selectedOutputSize = Size(CmdLineParser::GetOutputWidth(), CmdLineParser::GetOutputHeight());
    m_selectedRdiOutputSize = Size(CmdLineParser::GetRdiOutputWidth(), CmdLineParser::GetRdiOutputHeight());

    m_selectedInputFormat = static_cast<CHISTREAMFORMAT>(CmdLineParser::GetInputFormat());
    m_selectedOutputFormat = static_cast<CHISTREAMFORMAT>(CmdLineParser::GetOutputFormat());

    m_testId = testId;
    m_pipelineConfig = MixedConfig;

    for (int cameraId = 0; cameraId < numOfCameras; cameraId++)
    {
        // Create chistream objects from streamcreatedata
        NT_ASSERT(SetupStreams() == CDKResultSuccess, "SetupStreams Failed");

        ChiSensorModeInfo* testSensorMode = nullptr;
        testSensorMode = m_pChiModule->GetClosestSensorMode(cameraId, m_streamInfo.maxRes);

        NT_ASSERT(nullptr != testSensorMode, "Sensor mode is NULL for cameraId: ", cameraId);

        NT_LOG_INFO("Camera %d chosen sensor mode: %u, width: %u, height: %u", cameraId,
            testSensorMode->modeIndex, testSensorMode->frameDimension.width, testSensorMode->frameDimension.height);

        // TODO: Set number of batched frames based on usecase
        testSensorMode->batchedFrames = 1;

        NT_LOG_DEBUG("RDI Stream with Testgen set to: %d", m_isCamIFTestGen);

        for (int streamIndex = 0; streamIndex < m_numStreams; streamIndex++)
        {
            if (IsRDIStream(m_pRequiredStreams[streamIndex].format))
            {
                if (!m_selectedRdiOutputSize.isInvalidSize()) {
                    NT_LOG_INFO("OVERRIDE: RDI resolution set by User width: %d, height: %d ",
                        m_selectedRdiOutputSize.width, m_selectedRdiOutputSize.height);
                    m_pRequiredStreams[streamIndex].width = m_selectedRdiOutputSize.width;
                    m_pRequiredStreams[streamIndex].height = m_selectedRdiOutputSize.height;
                }
                else if (!m_isCamIFTestGen)
                {
                    NT_LOG_INFO("Selected RDI resolution based on Sensor mode width: %d, height: %d ",
                        testSensorMode->frameDimension.width, testSensorMode->frameDimension.height);
                    m_pRequiredStreams[streamIndex].width = testSensorMode->frameDimension.width;
                    m_pRequiredStreams[streamIndex].height = testSensorMode->frameDimension.height;
                }
            }
        }

        // Create pipelines
        NT_ASSERT(SetupPipelines(cameraId, testSensorMode) == CDKResultSuccess, "Pipelines Setup failed");

        // Create sessions
        NT_ASSERT(CreateSessions() == CDKResultSuccess, "Necessary sessions could not be created");

        // Initialize buffer manager and metabuffer pools
        NT_ASSERT(InitializeBufferMangers(cameraId) == CDKResultSuccess, "Buffer managers could not be initialized");
#ifndef OLD_METADATA
        NT_ASSERT(m_pChiMetadataUtil->CreateInputMetabufferPool(cameraId,MAX_REQUESTS) == CDKResultSuccess,
             "Input metabuffer pool could not be created!");
        NT_ASSERT(m_pChiMetadataUtil->CreateOutputMetabufferPool(MAX_REQUESTS) == CDKResultSuccess,
             "Output metabuffer pool could not be created!");
#endif // OLD_METADATA

        // Create and submit capture requests
        uint64_t frameNumber = START_FRAME;
        for (int frameIndex = 1; frameIndex <= CmdLineParser::GetFrameCount(); frameIndex++, frameNumber++)
        {
            bool SnapshotRequest = frameIndex % 5 == 0;
            NT_ASSERT(GenerateRealtimeCaptureRequest(frameNumber) == CDKResultSuccess,
                "Submit realtime pipeline request failed for frameNumber: ", frameNumber);

            if (SnapshotRequest)
            {
                frameNumber += 1;
                NT_ASSERT(GenerateOfflineCaptureRequest(frameNumber) == CDKResultSuccess,
                     "Submit offline pipeline request failed for frameNumber: %d", frameNumber);
            }
        }

        // Wait for all results
        NT_ASSERT(WaitForResults() == CDKResultSuccess,
             "There are pending buffers not returned by driver after several retries");

        // Destroy all resources created
        DestroyResources();
    }
}

} // namespace tests

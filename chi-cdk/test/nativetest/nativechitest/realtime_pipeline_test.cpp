////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 - 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  realtime_pipeline_test.cpp
/// @brief Definitions for the realtime test suite.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "realtime_pipeline_test.h"

#ifdef PROFILING
#include <chrono>
#endif

namespace tests
{
    /***************************************************************************************************************************
    *   RealtimePipelineTest::SetupStreams()
    *
    *   @brief
    *       Overridden function implementation which defines the stream information based on the test Id
    *   @param
    *       None
    *   @return
    *       CDKResult success if stream objects could be created or failure
    ***************************************************************************************************************************/
    CDKResult RealtimePipelineTest::SetupStreams()
    {
        CDKResult result = CDKResultSuccess;
        int streamIndex = 0;

        switch (m_testId)
        {
            case TestIPEFull:
            case TestPreviewHVX:
                m_numStreams = 1;

                //1. Preview stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD: m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = PREVIEW;
                m_streamInfo.num_streams  = m_numStreams;
                break;

            case TestIFEFull:
            case TestIFEFullTestgen:
                m_numStreams = 1;

                //1. IFE full stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = IFEOutputPortFull;
                m_streamInfo.num_streams  = m_numStreams;
                break;

            case TestIFEFull3A:
                m_numStreams = 1;

                //1. IFE full stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD_1440 : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = IFEOutputPortFull;
                m_streamInfo.num_streams  = m_numStreams;
                break;

            case TestIPEFullTestgen:
                m_numStreams = 1;

                //1. IPE full stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = IPEOutputPortDisplay;
                m_streamInfo.num_streams  = m_numStreams;
                break;

            case TestIFERDI0RawOpaque:
            case TestIFERDI0RawOpaqueTestgen:
                m_numStreams = 1;

                //1. IFE RDI stream
                m_resolution[streamIndex] = m_selectedRdiOutputSize.isInvalidSize()? RDI4608_2592: m_selectedRdiOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatRawOpaque;
                m_streamId[streamIndex]   = IFEOutputPortRDI0;
                m_streamInfo.num_streams  = m_numStreams;
                break;

            case TestIFERDI0RawPlain16:
                m_numStreams = 1;

                //1. IFE RDI stream
                m_resolution[streamIndex] = m_selectedRdiOutputSize.isInvalidSize() ? RDI4608_2592 : m_selectedRdiOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatRaw16;
                m_streamId[streamIndex]   = IFEOutputPortRDI0;
                m_streamInfo.num_streams  = m_numStreams;
                break;

            case TestIFERawCamif:
                m_numStreams = 1;

                //1. IFE CAMIF stream
                m_resolution[streamIndex] = m_selectedRdiOutputSize.isInvalidSize() ? RDI4608_2592 : m_selectedRdiOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatRaw16;
                m_streamId[streamIndex]   = IFEOutputPortCAMIFRaw;
                m_streamInfo.num_streams  = m_numStreams;
                break;

            case TestIFERawLsc:
                m_numStreams = 1;

                //1. IFE LSC stream
                m_resolution[streamIndex] = m_selectedRdiOutputSize.isInvalidSize() ? RDI4608_2592 : m_selectedRdiOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatRaw16;
                m_streamId[streamIndex]   = IFEOutputPortLSCRaw;
                m_streamInfo.num_streams  = m_numStreams;
                break;

            case TestIFERDI0Raw10Testgen:
                m_numStreams = 1;

                //1. IFE RDI stream
                m_resolution[streamIndex] = m_selectedRdiOutputSize.isInvalidSize() ? RDI4608_2592 : m_selectedRdiOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatRaw10;
                m_streamId[streamIndex]   = IFEOutputPortRDI0;
                m_streamInfo.num_streams  = m_numStreams;
                break;

            case TestIFEFullStatsTestgen:
            case TestIFEFullStats:
                m_numStreams = 10;

                // Stat node resolution sizes were taken from calculations in camxtitan17xdefs.h
                //1. IFE Full stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = IFEOutputPortFull;
                streamIndex++;
                //2. IFE RS
                m_resolution[streamIndex] = Size(32768, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsRS;
                streamIndex++;
                //3. IFE CS
                m_resolution[streamIndex] = Size(12480, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsCS;
                streamIndex++;
                //4. IFE IHIST
                m_resolution[streamIndex] = Size(2048, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsIHIST;
                streamIndex++;
                //5. IFE BHIST
                m_resolution[streamIndex] = Size(16384, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsBHIST;
                streamIndex++;
                //6. IFE HDRBE
                m_resolution[streamIndex] = Size(147456, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsHDRBE;
                streamIndex++;
                //7. IFE HDRBHIST
                m_resolution[streamIndex] = Size(3072, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsHDRBHIST;
                streamIndex++;
                //8. IFE TLBG
                m_resolution[streamIndex] = Size(147456, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsTLBG;
                streamIndex++;
                //9. IFE BF
                m_resolution[streamIndex] = Size(5768, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsBF;
                streamIndex++;
                //10. IFE AWBBG
                m_resolution[streamIndex] = Size(691200, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsAWBBG;

                m_streamInfo.isJpeg        = false;
                m_streamInfo.num_streams   = m_numStreams;
                break;

            case TestRealtimePrevRDI:
            case TestPrevRDITestgen:
                if (m_testId == TestPrevRDITestgen) {
                    m_isCamIFTestGen = true;
                }

                m_numStreams = 2;

                //1. Preview stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = IPEOutputPortDisplay;
                streamIndex++;

                //2. RDI stream
                if (m_isCamIFTestGen) {
                    m_resolution[streamIndex] = m_selectedRdiOutputSize.isInvalidSize() ? FULLHD : m_selectedRdiOutputSize;
                }
                else {
                    m_resolution[streamIndex] = m_selectedRdiOutputSize.isInvalidSize() ? UHD : m_selectedRdiOutputSize;
                }
                m_direction[streamIndex]  = ChiStreamTypeBidirectional;
                m_format[streamIndex]     = ChiStreamFormatRaw16;
                m_streamId[streamIndex]   = IFEOutputPortRDI0;

                m_streamInfo.num_streams = m_numStreams;
                break;
            case TestRealtimePrevWithCallback:
            case TestRealtimePrevWith3AWrappers:
                m_numStreams = 2;

                //1. Preview stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatUBWCNV12;
                m_streamId[streamIndex]   = IPEOutputPortDisplay;
                streamIndex++;

                //2. Preview callback stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = PREVIEWCALLBACK;

                m_streamInfo.num_streams  = m_numStreams;
                break;
            case TestPreviewWithMemcpy:
            case TestPreviewFromMemcpy:
            case TestBypassNodeMemcpy:
                m_numStreams = 1;

                //1. Preview stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = PREVIEW;
                m_streamInfo.num_streams  = m_numStreams;
                break;
            case TestIPEATestgen:
                m_numStreams = 1;

                //1. IPE Display (A)
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = IPEOutputPortDisplay;

                m_streamInfo.num_streams = m_numStreams;
                break;
            case TestIPE3ATestgen:
                m_numStreams = 1;

                //1. preview stream
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatUBWCNV12;
                m_streamId[streamIndex]   = IPEOutputPortDisplay;
                streamIndex++;

                m_streamInfo.num_streams = m_numStreams;
                break;
            case TestIPEABTestgen:
                m_numStreams = 2;

                //1. IPE Display (A)
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = IPEOutputPortDisplay;
                streamIndex++;

                //2. IPE Video (B)
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = IPEOutputPortVideo;

                m_streamInfo.num_streams = m_numStreams;
                break;
            case TestIPEABStatsTestgen:
            case TestIPEABCStatsTestgen:

                //1. IPE Display (A)
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = IPEOutputPortDisplay;
                streamIndex++;

                //2. IPE Video (B)
                m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = IPEOutputPortVideo;
                streamIndex++;

                if (m_testId == TestIPEABCStatsTestgen)
                {
                    //3. IFE FD (C)
                    m_resolution[streamIndex] = m_selectedOutputSize.isInvalidSize() ? FULLHD : m_selectedOutputSize;
                    m_direction[streamIndex]  = ChiStreamTypeOutput;
                    m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                    m_streamId[streamIndex]   = IFEOutputPortFD;
                    streamIndex++;
                }

                //4. IFE Stats BF
                m_resolution[streamIndex] = Size(5768, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsBF;
                streamIndex++;

                //5. IFE Stats AWBBG
                m_resolution[streamIndex] = Size(691200, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsAWBBG;
                streamIndex++;

                //6. IFE Stats TLBG
                m_resolution[streamIndex] = Size(147456, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsTLBG;
                streamIndex++;

                //7. IFE Stats IHIST
                m_resolution[streamIndex] = Size(2048, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsIHIST;
                streamIndex++;

                //8. IFE Stats RS
                m_resolution[streamIndex] = Size(32768, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = IFEOutputPortStatsRS;

                m_streamInfo.isJpeg       = false;
                m_numStreams              = streamIndex + 1;
                m_streamInfo.num_streams  = m_numStreams;
                break;
            case TestTFEFullStatsTestgen:
                m_numStreams = 6;

                // Stat node resolution sizes were taken from calculations in camxtitan5xdefs.h
                //1. TFE Full stream
                m_resolution[streamIndex] = (m_selectedRdiOutputSize.isInvalidSize()) ? FULLHD : m_selectedRdiOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatRaw16;
                m_streamId[streamIndex]   = TFEOutputPortFull;
                streamIndex++;

                //2. TFE AECBG
                m_resolution[streamIndex] = Size(16384, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = TFEOutputPortStatsAECBG;
                streamIndex++;

                //3. TFE BHIST
                m_resolution[streamIndex] = Size(3072, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = TFEOutputPortStatsBHIST;
                streamIndex++;

                //4. TFE TLBG
                m_resolution[streamIndex] = Size(16384, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = TFEOutputPortStatsTLBG;
                streamIndex++;

                //5. TFE BAF
                m_resolution[streamIndex] = Size(16384, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = TFEOutputPortStatsBAF;
                streamIndex++;

                //6. TFE AWBBG
                m_resolution[streamIndex] = Size(16384, 1);
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatBlob;
                m_streamId[streamIndex]   = TFEOutputPortStatsAWBBG;
                streamIndex++;

                m_streamInfo.isJpeg       = false;
                m_streamInfo.num_streams  = m_numStreams;
                break;
            case TestCVPDME:
            case TestCVPDMEICA:
                m_numStreams = 1;
                m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? HD4K : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = IFEOutputPortFull;

                m_streamInfo.num_streams  = m_numStreams;
                break;
            case TestCVPDMEDisplayPort:
                m_numStreams = 1;
                m_resolution[streamIndex] = (m_selectedOutputSize.isInvalidSize()) ? HD4K : m_selectedOutputSize;
                m_direction[streamIndex]  = ChiStreamTypeOutput;
                m_format[streamIndex]     = ChiStreamFormatYCbCr420_888;
                m_streamId[streamIndex]   = IFEOutputPortDisplayFull;

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
                        NT_LOG_ERROR("Failed to created streams");
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
                                m_isRealtime[index] = true;
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
    *   RealtimePipelineTest::SetupPipelines()
    *
    *   @brief
    *       Overridden function implementation which creates pipeline objects based on the test Id
    *   @param
    *       [in]  int                 cameraId    cameraId to be associated with the pipeline
    *       [in]  ChiSensorModeInfo*  sensorMode  sensor mode to be used for the pipeline
    *   @return
    *       CDKResult success if pipelines could be created or failure
    ***************************************************************************************************************************/
    CDKResult RealtimePipelineTest::SetupPipelines(int cameraId, ChiSensorModeInfo * sensorMode)
    {
        CDKResult result = CDKResultSuccess;
        switch (m_testId)
        {
            case TestIPEFull:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealTimeIPE);
                break;
            case TestIFEFull:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFE);
                break;
            case TestIFEFull3A:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFE3A);
                break;
            case TestIFERDI0RawOpaque:
            case TestIFERDI0RawPlain16:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFERDI0);
                break;
            case TestIFERDI0RawOpaqueTestgen:
            case TestIFERDI0Raw10Testgen:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFERDI0TestGen);
                break;
            case TestIFERawCamif:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFERawCamif);
                break;
            case TestIFERawLsc:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFERawLsc);
                break;
            case TestIFEFullTestgen:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFETestGen);
                break;
            case TestIPEFullTestgen:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIPETestGen);
                break;
            case TestIFEFullStats:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFEStats);
                break;
            case TestIFEFullStatsTestgen:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIFEStatsTestGen);
                break;
            case TestRealtimePrevRDI:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimePrevRDI);
                break;
            case TestPrevRDITestgen:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::PrevRDIwithTestGen);
                break;
            case TestRealtimePrevWithCallback:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimePrevWithCallbackWithStats);
                break;
            case TestRealtimePrevWith3AWrappers:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimePrevWith3AWrappers);
                break;
            case TestPreviewWithMemcpy:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimePrevWithMemcpy);
                break;
            case TestPreviewFromMemcpy:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimePrevFromMemcpy);
                break;
            case TestBypassNodeMemcpy:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeBypassNode);
                break;
            case TestPreviewHVX:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimePrevHVX);
                break;
            case TestIPEATestgen:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIPEATestgen);
                break;
            case TestIPE3ATestgen:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIPE3ATestgen);
                break;
            case TestIPEABTestgen:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIPEABTestgen);
                break;
            case TestIPEABStatsTestgen:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIPEABStatsTestgen);
                break;
            case TestIPEABCStatsTestgen:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeIPEABCStatsTestgen);
                break;
            case TestTFEFullStatsTestgen:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeTFEStatsTestgen);
                break;
            case TestCVPDME:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeCVPDME);
                break;
            case TestCVPDMEDisplayPort:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeCVPDMEDisplayPort);
                break;
            case TestCVPDMEICA:
                m_pChiPipeline = ChiPipeline::Create(cameraId, sensorMode, m_streamIdMap, PipelineType::RealtimeCVPDMEICA);
                break;
            default:
                NT_LOG_ERROR( "Unknown testcase Id provided: [%d]", m_testId);
                return CDKResultENoSuch;
        }

        result = (m_pChiPipeline != nullptr) ? m_pChiPipeline->CreatePipelineDesc() : CDKResultEInvalidPointer;
        return result;
    }

    /***************************************************************************************************************************
    *   RealtimePipelineTest::CreateSessions()
    *
    *   @brief
    *       Overridden function implementation which creates required number of sessions based on the test Id
    *   @param
    *       None
    *   @return
    *       CDKResult success if sessions could be created or failure
    ***************************************************************************************************************************/
    CDKResult RealtimePipelineTest::CreateSessions()
    {
        CDKResult result = CDKResultSuccess;
        ChiCallBacks callbacks = { 0 };

        callbacks.ChiNotify                      = ChiTestCase::ProcessMessage;
        callbacks.ChiProcessCaptureResult        = ChiTestCase::QueueCaptureResult;
        callbacks.ChiProcessPartialCaptureResult = ChiTestCase::QueuePartialCaptureResult;

        m_perSessionPvtData.pTestInstance = this;
        m_perSessionPvtData.sessionId = RealtimeSession;

        m_pChiSession = ChiSession::Create(&m_pChiPipeline,
                                           1,
                                           &callbacks,
                                           &m_perSessionPvtData);

        if(m_pChiSession == nullptr)
        {
            NT_LOG_ERROR( "Realtime session could not be created");
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
    *   RealtimePipelineTest::CommonProcessCaptureResult()
    *
    *   @brief
    *       Overridden function implementation which processes the capture result obtained from driver
    *   @param
    *        [in]  CHICAPTURERESULT*     pCaptureResult         pointer to capture result
    *        [in]  void*                 pPrivateCallbackData   pointer private callback data
    *   @return
    *       None
    ***************************************************************************************************************************/
    void RealtimePipelineTest::CommonProcessCaptureResult(
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

        if (sessionId == RealtimeSession)
        {
            for (uint32_t bufferIndex = 0; bufferIndex < numOutputBuffers; bufferIndex++)
            {
                BufferManager::NativeChiBuffer* outBuffer = const_cast<BufferManager::NativeChiBuffer*>(&pCaptureResult->
                    pOutputBuffers[bufferIndex]);
                BufferManager* manager = m_streamBufferMap[outBuffer->pStream];
                if(manager == nullptr)
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
           NT_LOG_DEBUG( "Number of pending buffers remaining after receiving the result: %d", GetPendingBufferCount());
        }
    }

    /***************************************************************************************************************************
    *   RealtimePipelineTest::DestroyResources()
    *
    *   @brief
    *       Overridden function implementation which destroys all created resources / objects
    *   @param
    *       None
    *   @return
    *       None
        ***********************************************************************************************************************/
    void RealtimePipelineTest::DestroyResources()
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

    /***************************************************************************************************************************
    *   RealtimePipelineTest::GenerateCaptureRequest()
    *
    *   @brief
    *       Generate a realtime pipeline request
    *   @param
    *       [in] uint64_t   frameNumber     framenumber associated with the request
    *   @return
    *       CDKResult success if request could be submitted or failure
    ***************************************************************************************************************************/
    CDKResult RealtimePipelineTest::GenerateCaptureRequest(uint64_t frameNumber)
    {
        CDKResult result = CDKResultSuccess;
        static const uint32_t NumOutputBuffers = m_numStreams;
        BufferManager::NativeChiBuffer* outputBuffers = SAFE_NEW() BufferManager::NativeChiBuffer[NumOutputBuffers];
        uint32_t outputIndex = 0;

        std::map<ChiStream*, BufferManager*>::iterator it;

        for (it = m_streamBufferMap.begin(); it != m_streamBufferMap.end(); ++it, outputIndex++)
        {
            BufferManager* manager = it->second;
            void* buffer = manager->GetOutputBufferForRequest();
            if(buffer == nullptr)
            {
                delete[] outputBuffers;
                return CDKResultENoMore;
            }

            outputBuffers[outputIndex] = *static_cast<BufferManager::NativeChiBuffer*>(buffer);
        }

        uint32_t requestId = FRAME_REQUEST_MOD(frameNumber);
        memset(&m_realtimeRequest[requestId], 0, sizeof(CHICAPTUREREQUEST));

        m_realtimeRequest[requestId].frameNumber        = frameNumber;
        m_realtimeRequest[requestId].hPipelineHandle    = m_pChiPipeline->GetPipelineHandle();
        m_realtimeRequest[requestId].numOutputs         = NumOutputBuffers;
        m_realtimeRequest[requestId].pOutputBuffers     = outputBuffers;
        m_realtimeRequest[requestId].pPrivData          = &m_requestPvtData;

#ifdef OLD_METADATA
        m_realtimeRequest[requestId].pMetadata = allocate_camera_metadata(METADATA_ENTRIES, 100 * 1024);
        NATIVETEST_UNUSED_PARAM(m_pPipelineMetadataInfo);
#else
        // Get the input metabuffer from the pool
        m_realtimeRequest[requestId].pInputMetadata = m_pChiMetadataUtil->GetInputMetabufferFromPool(requestId);
        NT_EXPECT(m_realtimeRequest[requestId].pInputMetadata != nullptr, "Failed to create Input Metabuffer before sending request");

        // Get the output metabuffer from the pool
        m_realtimeRequest[requestId].pOutputMetadata = m_pChiMetadataUtil->GetOutputMetabufferFromPool(requestId, m_pPipelineMetadataInfo.publishTagArray,
            m_pPipelineMetadataInfo.publishTagCount);
        NT_EXPECT(m_realtimeRequest[requestId].pOutputMetadata != nullptr, "Failed to create Output Metabuffer before sending request");
#endif // OLD_METADATA

        memset(&m_submitRequest, 0, sizeof(CHIPIPELINEREQUEST));
        m_submitRequest.pSessionHandle   = m_pChiSession->GetSessionHandle();
        m_submitRequest.numRequests      = 1;
        m_submitRequest.pCaptureRequests = &m_realtimeRequest[requestId];

        AtomicIncrement(NumOutputBuffers);

       NT_LOG_DEBUG( "Number of pending buffers remaining: %d after sending request: %" PRIu64,
            GetPendingBufferCount(), frameNumber);

        if (result == CDKResultSuccess)
        {
            result = m_pChiModule->SubmitPipelineRequest(&m_submitRequest);
        }

        delete[] outputBuffers;
        return result;
    }

    /**************************************************************************************************
    *   RealtimePipelineTest::TestRealtimePipeline
    *
    *   @brief
    *       Test a realtime pipeline involving Sensor+IFE or Sensor+IFE+IPE depending on pipelineType
    *   @param
    *       [in] TestType   testType            Test identifier
    *       [in] bool       bUseExternalSensor  Set if test uses external sensor (defaults to false)
    *   @return
    *       None
    **************************************************************************************************/
    void RealtimePipelineTest::TestRealtimePipeline(TestId testType, bool bUseExternalSensor)
    {
        m_selectedOutputSize = Size(CmdLineParser::GetOutputWidth(), CmdLineParser::GetOutputHeight());
        m_selectedRdiOutputSize = Size(CmdLineParser::GetRdiOutputWidth(), CmdLineParser::GetRdiOutputHeight());

        // Get list of cameras to test
        std::vector <int> camList = m_pChiModule->GetCameraList();

        // Only test camera 0 if using external sensor (camera 1 and 2 not supported with external sensor)
        if (bUseExternalSensor)
        {
            camList.clear();
            camList.push_back(0);
        }

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

            NT_LOG_INFO("Camera %d chosen sensor mode: %u, width: %u, height: %u, framerate: %u", cameraId,
                testSensorMode->modeIndex, testSensorMode->frameDimension.width, testSensorMode->frameDimension.height, testSensorMode->frameRate);

            // TODO: Set number of batched frames based on usecase
            testSensorMode->batchedFrames = 1;

            //For RDI cases, we need to make sure stream resolution matches sensor mode
            for (int streamIndex = 0; streamIndex < m_numStreams; streamIndex++)
            {
                if (IsRDIStream(m_pRequiredStreams[streamIndex].format))
                {
                    if (!m_selectedRdiOutputSize.isInvalidSize())
                    {
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

            //2. Create pipelines
            NT_ASSERT(SetupPipelines(cameraId, testSensorMode) == CDKResultSuccess, "Pipelines Setup failed");

            //3. Create sessions
            NT_ASSERT(CreateSessions() == CDKResultSuccess, "Necessary sessions could not be created");

            //4. Initialize buffer manager and metabuffer pools
            NT_ASSERT(InitializeBufferMangers(cameraId) == CDKResultSuccess, "Buffer managers could not be initialized");
#ifndef OLD_METADATA
            NT_ASSERT(m_pChiMetadataUtil->CreateInputMetabufferPool(cameraId, MAX_REQUESTS) == CDKResultSuccess,
                "Input metabuffer pool could not be created!");
            NT_ASSERT(m_pChiMetadataUtil->CreateOutputMetabufferPool(MAX_REQUESTS) == CDKResultSuccess,
                 "Output metabuffer pool could not be created!");
#endif // OLD_METADATA

            //5. Create and submit capture requests
            uint64_t frameNumber = START_FRAME;
            int captureCount = CmdLineParser::GetFrameCount();

#ifdef PROFILING
            /* Start profiling */
            auto startTime = std::chrono::steady_clock::now();
#endif

            for (int frameIndex = 1; frameIndex <= captureCount; frameIndex++, frameNumber++)
            {
                NT_ASSERT(GenerateCaptureRequest(frameNumber) == CDKResultSuccess,
                    "Submit pipeline request failed for frameNumber: %d", frameNumber);
            }

            //6. Wait for all results
            NT_ASSERT(WaitForResults() == CDKResultSuccess,
                "There are pending buffers not returned by driver after several retries");

#ifdef PROFILING
            auto endTime = std::chrono::steady_clock::now();
            double totalTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();

            NT_LOG_WARN( "Total time: %f ms, number of frames %d, avg fps: %f", totalTime, captureCount, captureCount / (totalTime / 1000.0));
            /* End profiling */
#endif

            //7. Destroy all resources created
            DestroyResources();
        }
    }

}

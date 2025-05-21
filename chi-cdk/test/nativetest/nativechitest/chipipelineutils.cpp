//*******************************************************************************************
// Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*******************************************************************************************

#include "chipipelineutils.h"
#include "camera3stream.h"
#include "cmdlineparser.h"

namespace tests {

/**************************************************************************************************
*   PipelineUtils::SetupPipeline
*
*   @brief
*       Setup Pipeline create parameters for a given usecase
*   @param
*       [in]  BufferManager *                      manager                Pointer to buffer manager
*       [out] PipelineCreateData*                  pPipelineCreate        Pointer to PipelineCreateData
*       [in]  PipelineType                         type                   PipeLine type for this usecase
*   @return
*       CDKResult result
**************************************************************************************************/
CDKResult PipelineUtils::SetupPipeline(
    std::map<StreamUsecases, ChiStream*> streamIdMap,
    PipelineCreateData* pPipelineCreate,
    PipelineType type)
{
    NATIVETEST_UNUSED_PARAM(m_nodes);
    NATIVETEST_UNUSED_PARAM(m_ports);
    NATIVETEST_UNUSED_PARAM(m_links);
    NATIVETEST_UNUSED_PARAM(m_inputPorts);
    NATIVETEST_UNUSED_PARAM(m_outputPorts);
    NATIVETEST_UNUSED_PARAM(m_linkNodeDescriptors);

    CDKResult result = CDKResultSuccess;

    switch (type)
    {
        // realtime pipeline
        case PipelineType::RealTimeIPE:
        case PipelineType::RealtimePrevHVX:
        case PipelineType::RealtimeStats3A:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePipelineIPE(streamIdMap, type);
            break;
        case PipelineType::RealtimeIFE:
        case PipelineType::RealtimeIFE3A:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePipelineIFE(streamIdMap, type);
            break;
        case PipelineType::RealtimeIFETestGen:
            pPipelineCreate->numInputs  = 0;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePipelineIFETestgen(streamIdMap);
            break;
        case PipelineType::RealtimeIPETestGen:
            pPipelineCreate->numInputs  = 0;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePipelineIPETestgen(streamIdMap);
            break;
        case PipelineType::RealtimeIFEStatsTestGen:
            pPipelineCreate->numInputs  = 0;
            pPipelineCreate->numOutputs = 10;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePipelineIFEStats(streamIdMap, type);
            break;
        case PipelineType::RealtimeIFEStats:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 10;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePipelineIFEStats(streamIdMap, type);
            break;
        case PipelineType::RealtimeIFERDI0:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePipelineIFERDIO(streamIdMap);
            break;
        case PipelineType::RealtimeIFERDI0TestGen:
            pPipelineCreate->numInputs  = 0;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePipelineIFERDIOTestgen(streamIdMap);
            break;
        case PipelineType::RealtimeIFERawCamif:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePipelineIFERawCamif(streamIdMap);
            break;
        case PipelineType::RealtimeIFERawLsc:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePipelineIFERawLsc(streamIdMap);
            break;
        case PipelineType::RealtimePrevRDI:
        case PipelineType::RealtimePrevRDIWithStats:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 2;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePrevRDI(streamIdMap, type);
            break;
        case PipelineType::PrevRDIwithTestGen:
            pPipelineCreate->numInputs  = 0;
            pPipelineCreate->numOutputs = 2;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePrevRDI(streamIdMap, type);
            break;
        case PipelineType::RealtimePrevAndVideoWithStats:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 3;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupPreviewCallbackSnapshotWithThumbnail(streamIdMap, type);
            break;
        case PipelineType::RealtimePrevWithCallbackWithStats:
        case PipelineType::OfflineZSlSnapAndThumbnailWithDSports:
        case PipelineType::RealtimePrevWith3AWrappers:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 2;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupPreviewCallbackSnapshotWithThumbnail(streamIdMap, type);
            break;
        case PipelineType::RealtimePrevWithCallbackAndRDIWithStats:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 3;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupPreviewCallbackSnapshotWithThumbnail(streamIdMap, type);
            break;
        case PipelineType::RealtimePrevWithMemcpy:
        case PipelineType::RealtimePrevFromMemcpy:
        case PipelineType::RealtimeChiDepth:
        case PipelineType::RealtimeBypassNode:
        case PipelineType::RealtimeInplaceNode:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePipelineExternal(streamIdMap, type);
            break;
        case PipelineType::RealtimeCVPDME:
        case PipelineType::RealtimeCVPDMEDisplayPort:
        case PipelineType::RealtimeCVPDMEICA:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePipelineCVP(streamIdMap, type);
            break;
        case PipelineType::RealtimeIPEATestgen:
        case PipelineType::RealtimeIPE3ATestgen:
            pPipelineCreate->numInputs  = 0;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeIPEABCTestgen(streamIdMap, type);
            break;
        case PipelineType::RealtimeIPEABTestgen:
            pPipelineCreate->numInputs  = 0;
            pPipelineCreate->numOutputs = 2;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeIPEABCTestgen(streamIdMap, type);
            break;
        case PipelineType::RealtimeIPEABStatsTestgen:
            pPipelineCreate->numInputs  = 0;
            pPipelineCreate->numOutputs = 7;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeIPEABCTestgen(streamIdMap, type);
            break;
        case PipelineType::RealtimeIPEABCStatsTestgen:
            pPipelineCreate->numInputs  = 0;
            pPipelineCreate->numOutputs = 8;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeIPEABCTestgen(streamIdMap, type);
            break;
        case PipelineType::RealtimeIPEABCStats:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 8;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeIPEABC(streamIdMap, type);
            break;
        case PipelineType::RealtimeIPEAStatsRDI:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 4;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePIPCam(streamIdMap, type);
            break;
        case PipelineType::RealtimeIPEACStatsRDI:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 5;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePIPCam(streamIdMap, type);
            break;
        case PipelineType::RealtimeIPEABCStatsRDI:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 5;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePIPCam(streamIdMap, type);
            break;
        case PipelineType::RealtimeRDI1Only:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimePIPCam(streamIdMap, type);
            break;
        case PipelineType::RealtimeIPEJpeg:
        case PipelineType::RealtimeBPSIPEJpeg:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeJpeg(streamIdMap, type);
            break;
        case PipelineType::RealtimeFD:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeFD(streamIdMap, type);
            break;
        case PipelineType::RealtimeIFEGeneric:
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeIFEGeneric(streamIdMap, type);
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            break;
        case PipelineType::RealtimeIFEGenericTestgen:
            pPipelineCreate->numInputs  = 0;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeIFEGeneric(streamIdMap, type);
            break;
        case PipelineType::RealtimeIFEGeneric2Stream:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 2;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeIFEGeneric(streamIdMap, type);
            break;
        case PipelineType::RealtimeIFEDownscaleGenericTestgen:
            pPipelineCreate->numInputs  = 0;
            pPipelineCreate->numOutputs = 3;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeIFEDownscaleGenericTestgen(streamIdMap, type);
            break;
        case PipelineType::RealtimeIFEGeneric2StreamDisplay:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 2;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeIFEGeneric(streamIdMap, type);
            break;
        case PipelineType::RealtimeIFEGeneric2StreamTestgen:
        case PipelineType::RealtimeIFEGeneric2StreamDisplayTestgen:
            pPipelineCreate->numInputs  = 0;
            pPipelineCreate->numOutputs = 2;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupRealtimeIFEGeneric(streamIdMap, type);
            break;
        case PipelineType::VendorTagWrite:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupCustomVendorWritePipeline(streamIdMap);
            break;

        // offline pipeline
        case PipelineType::OfflineIPEJPEG:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflinePipelineIPEJPEG(streamIdMap);
            break;
        case PipelineType::OfflineIPEDisp:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflinePipelineIPEDisplay(streamIdMap);
            break;
        case PipelineType::OfflineIPEVideo:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflinePipelineIPEVideo(streamIdMap);
            break;
        case PipelineType::OfflineIPEDispVideo:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 2;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflinePipelineIPEDispVideo(streamIdMap);
            break;
        case PipelineType::OfflineBPS:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflinePipelineBPS(streamIdMap);
            break;
        case PipelineType::OfflineBPSDS4:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflinePipelineBPSDS4(streamIdMap);
            break;
        case PipelineType::OfflineBPSIPE:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflinePipelineBPSIPE(streamIdMap);
            break;
        case PipelineType::OfflineBPSIPEJpeg:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflinePipelineBPSIPEJpeg(streamIdMap);
            break;
        case PipelineType::OfflineBPSIPEDispVideo:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 2;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflinePipelineBPSIPEDispVideo(streamIdMap);
            break;
        case PipelineType::OfflineBPSStats:
        case PipelineType::OfflineBPSStatsWithIPE:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 3;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflinePipelineBPSStats(streamIdMap, type);
            break;
        case PipelineType::OfflineBPSBGStatsWithIPE:
        case PipelineType::OfflineBPSHistStatsWithIPE:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 2;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflinePipelineBPSStats(streamIdMap, type);
            break;
        case PipelineType::OfflineZSlSnap:
        case PipelineType::OfflineZSlSnapWithDSports:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineZSLSnapShot(streamIdMap, type);
            break;
        case PipelineType::OfflineJpegSnapshot:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineJpeg(streamIdMap);
            break;
        case PipelineType::OfflineBPSGPUpipeline:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 4;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineBPSGPUPipeline(streamIdMap);
            break;
        case PipelineType::OfflineFDPipeline:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineFDPipeline(streamIdMap);
            break;
        case PipelineType::OfflineBPSWithIPEAndDS:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineBPSWithIPEAndDSPipeline(streamIdMap);
            break;
        case PipelineType::OfflineChiGPUNode:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineChiGPUNode(streamIdMap);
            break;
        case PipelineType::OfflineExtBPSIPE:
        case PipelineType::OfflineExtBPSIPEJPEG:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineChiExternalNode(streamIdMap, type);
            break;
        case PipelineType::OfflineDepthNode:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineDepthNode(streamIdMap, type);
            break;
        case PipelineType::OfflineIPEGeneric:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineIPEGeneric(streamIdMap, type);
            break;
        case PipelineType::OfflineIPEGeneric2StreamDisplay:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 2;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineIPEGeneric(streamIdMap, type);
            break;
        case PipelineType::OfflineBPSGeneric:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 1;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineBPSGeneric(streamIdMap, type);
            break;
        case PipelineType::OfflineBPSGeneric2Stream:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 2;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineBPSGeneric(streamIdMap, type);
            break;
        case PipelineType::OfflineBPSDownscaleGeneric:
            pPipelineCreate->numInputs  = 1;
            pPipelineCreate->numOutputs = 4;
            InitializePortBufferDescriptor(pPipelineCreate);
            result = SetupOfflineBPSDownscaleGeneric(streamIdMap, type);
            break;
        default:
            result = CDKResultEInvalidArg;
            NT_LOG_ERROR("Invalid pipeline type: [%d]", type);
            break;
    }

    pPipelineCreate->pInputBufferRequirements = &m_pipelineInputBufferRequirements;
    pPipelineCreate->pOutputDescriptors = m_pPipelineOutputBuffer;
    pPipelineCreate->pInputDescriptors = &m_pipelineInputBuffer;
    pPipelineCreate->pPipelineCreateDescriptor = &m_pipelineDescriptor;
    pPipelineCreate->pPipelineName = m_pipelineName;

    return result;
}

    /**************************************************************************************************
    *   PipelineUtils::InitializeNodePorts
    *
    *   @brief
    *       Allocate memory for pNodePort based on numInputs and numOutputs
    *   @param
    *       [in]  PipelineCreateData*     pPipelineCreate     Pointer to PipelineCreateData
    *   @return
    *       None
    **************************************************************************************************/
    void PipelineUtils::InitializePortBufferDescriptor(PipelineCreateData* pPipelineCreate)
    {
        // Only one input supported currently, do not fail if > 1
        if (pPipelineCreate->numInputs > 1)
        {
            NT_LOG_ERROR( "More than 1 input buffers not allowed!");
        }
        m_pipelineInputBuffer.pNodePort = SAFE_NEW() CHILINKNODEDESCRIPTOR;
        m_pipelineInputBuffer.numNodePorts = 1;
        m_pipelineInputBuffer.flagValue = 0;
        m_pipelineInputBuffer.pBufferNegotiationsOptions = NULL;

        for (uint32_t outputIndex = 0; outputIndex <= pPipelineCreate->numOutputs; outputIndex++)
        {
            m_pPipelineOutputBuffer[outputIndex].pNodePort = SAFE_NEW() CHILINKNODEDESCRIPTOR;
            m_pPipelineOutputBuffer[outputIndex].numNodePorts = 1;
            m_pPipelineOutputBuffer[outputIndex].flagValue = 0;
            m_pPipelineOutputBuffer[outputIndex].pBufferNegotiationsOptions = NULL;
        }
    }

    /**************************************************************************************************
    *   PipelineUtils::DestroyNodePorts
    *
    *   @brief
    *       Free memory for pNodePort allocated while initializing
    *   @param
    *       [in]  PipelineCreateData*     pPipelineCreate     Pointer to PipelineCreateData
    *   @return
    *       None
    **************************************************************************************************/
    void PipelineUtils::DestroyNodePorts(PipelineCreateData* pPipelineCreate)
    {
        if (m_pipelineInputBuffer.pNodePort != nullptr)
        {
            delete m_pipelineInputBuffer.pNodePort;
            m_pipelineInputBuffer.pNodePort = nullptr;
        }

        for (uint32_t outputIndex = 0; outputIndex <= pPipelineCreate->numOutputs; outputIndex++)
        {
            if (m_pPipelineOutputBuffer[outputIndex].pNodePort != nullptr)
            {
                delete m_pPipelineOutputBuffer[outputIndex].pNodePort;
                m_pPipelineOutputBuffer[outputIndex].pNodePort = nullptr;
            }
        }
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePipelineIPE
    *
    *   @brief
    *       Setup Pipeline parameters for real time ipe usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePipelineIPE(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        if (type == PipelineType::RealTimeIPE)
        {
            m_pipelineDescriptor = Usecases1Target[TestIPEFullId].pPipelineTargetCreateDesc[Ipefull].pipelineCreateDesc;
            m_pipelineName = Usecases1Target[TestIPEFullId].pPipelineTargetCreateDesc[Ipefull].pPipelineName;
        }
        else if (type == PipelineType::RealtimePrevHVX)
        {
            NT_LOG_WARN( "This test needs enableHVXStreaming=1 in overridesettings");
            m_pipelineDescriptor = Usecases1Target[TestPreviewHVXId].pPipelineTargetCreateDesc[PreviewHVX].pipelineCreateDesc;
            m_pipelineName = Usecases1Target[TestPreviewHVXId].pPipelineTargetCreateDesc[PreviewHVX].pPipelineName;
        }
        else if (type == PipelineType::RealtimeStats3A)
        {
            m_pipelineDescriptor = Usecases1Target[TestPreviewHVXId].pPipelineTargetCreateDesc[PreviewHVX].pipelineCreateDesc;
            m_pipelineName = Usecases1Target[TestPreviewHVXId].pPipelineTargetCreateDesc[PreviewHVX].pPipelineName;
        }
        else
        {
            NT_LOG_ERROR( "Invalid Realtime pipeline type given: %d", static_cast<int>(type));
            return CDKResultEInvalidArg;
        }

        m_pPipelineOutputBuffer[0].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[0].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[0].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[0].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
        if (streamIdMap.find(StreamUsecases::PREVIEW) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for PREVIEW");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[0].pStream = streamIdMap[StreamUsecases::PREVIEW];
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePipelineIFE
    *
    *   @brief
    *       Setup Pipeline parameters for real time ife usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePipelineIFE(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        if (type == PipelineType::RealtimeIFE)
        {
            m_pipelineDescriptor = Usecases1Target[TestIFEFullId].pPipelineTargetCreateDesc[IfeFull].pipelineCreateDesc;
            m_pipelineName = Usecases1Target[TestIFEFullId].pPipelineTargetCreateDesc[IfeFull].pPipelineName;
        }
        else if (type == PipelineType::RealtimeIFE3A)
        {
            m_pipelineDescriptor = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[IFEFull3A].pipelineCreateDesc;
            m_pipelineName = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[IFEFull3A].pPipelineName;
        }
        else
        {
            NT_LOG_ERROR( "Invalid Realtime pipeline type given: %d", static_cast<int>(type));
            return CDKResultEInvalidArg;
        }
        m_pPipelineOutputBuffer[0].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[0].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[0].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[0].pNodePort->nodePortId = ifeportid_t::IFEOutputPortFull;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortFull");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[0].pStream = streamIdMap[StreamUsecases::IFEOutputPortFull];
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePipelineIFETestgen
    *
    *   @brief
    *       Setup Pipeline parameters for real time ife usecase with testgen(no sensor node)
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePipelineIFETestgen(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases1Target[TestIFEFullTestgenId].pPipelineTargetCreateDesc[IfeFullTestgen].pipelineCreateDesc;
        m_pipelineName = Usecases1Target[TestIFEFullTestgenId].pPipelineTargetCreateDesc[IfeFullTestgen].pPipelineName;

        m_pPipelineOutputBuffer[0].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[0].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[0].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[0].pNodePort->nodePortId = ifeportid_t::IFEOutputPortFull;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortFull");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[0].pStream = streamIdMap[StreamUsecases::IFEOutputPortFull];
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePipelineIPETestgen
    *
    *   @brief
    *       Setup Pipeline parameters for real time IPE usecase with testgen(no sensor node)
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePipelineIPETestgen(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases1Target[TestIPEFullTestgenId].pPipelineTargetCreateDesc[IPEFullTestgen].pipelineCreateDesc;
        m_pipelineName = Usecases1Target[TestIPEFullTestgenId].pPipelineTargetCreateDesc[IPEFullTestgen].pPipelineName;

        m_pPipelineOutputBuffer[0].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[0].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[0].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[0].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
        if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[0].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePipelineIFEStats
    *
    *   @brief
    *       Setup Pipeline parameters for real time ife usecase with all stats ports with testgen(no sensor node)
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePipelineIFEStats(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        if(type == PipelineType::RealtimeIFEStatsTestGen)
        {
            m_pipelineDescriptor = Usecases10Target[TestIFEFullStatsTestgenId].pPipelineTargetCreateDesc[IfeFullStatsTestgen].pipelineCreateDesc;
            m_pipelineName = Usecases10Target[TestIFEFullStatsTestgenId].pPipelineTargetCreateDesc[IfeFullStatsTestgen].pPipelineName;
        }
        else
        {
            m_pipelineDescriptor = Usecases10Target[TestIFEFullStatsId].pPipelineTargetCreateDesc[IfeFullStats].pipelineCreateDesc;
            m_pipelineName = Usecases10Target[TestIFEFullStatsId].pPipelineTargetCreateDesc[IfeFullStats].pPipelineName;
        }

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortFull;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortFull");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortFull];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsRS;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsRS) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsRS");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsRS];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsCS;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsCS) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsCS");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsCS];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsIHIST;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsIHIST) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsIHIST");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsIHIST];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsBHIST;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsBHIST) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsBHIST");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsBHIST];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsHDRBE;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsHDRBE) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsHDRBE");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsHDRBE];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsHDRBHIST;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsHDRBHIST) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsHDRBHIST");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsHDRBHIST];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsTLBG;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsTLBG) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsTLBG");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsTLBG];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsBF;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsBF) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsBF");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsBF];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsAWBBG;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsAWBBG) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsAWBBG");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsAWBBG];

        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePipelineIFERawCamif
    *
    *   @brief
    *       Setup Pipeline parameters for real time ife Rawcamif usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePipelineIFERawCamif(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases1Target[UsecaseRawId].pPipelineTargetCreateDesc[Camif].pipelineCreateDesc;
        m_pipelineName = Usecases1Target[UsecaseRawId].pPipelineTargetCreateDesc[Camif].pPipelineName;

        UINT32 outputBufferIndex = 0;

        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortCAMIFRaw;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortCAMIFRaw) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortCAMIFRaw");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortCAMIFRaw];
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePipelineMemcpy
    *
    *   @brief
    *       Setup Pipeline parameters for real time memcpy usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePipelineExternal(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        if (PipelineType::RealtimePrevWithMemcpy == type || PipelineType::RealtimeBypassNode == type)
        {
            if (PipelineType::RealtimePrevWithMemcpy == type)
            {
                m_pipelineDescriptor = Usecases1Target[TestMemcpyId].pPipelineTargetCreateDesc[PreviewWithMemcpy].pipelineCreateDesc;
                m_pipelineName = Usecases1Target[TestMemcpyId].pPipelineTargetCreateDesc[PreviewWithMemcpy].pPipelineName;
            }
            if (PipelineType::RealtimeBypassNode == type)
            {
                m_pipelineDescriptor = Usecases1Target[TestBypassNodeId].pPipelineTargetCreateDesc[BypassNode].pipelineCreateDesc;
                m_pipelineName = Usecases1Target[TestBypassNodeId].pPipelineTargetCreateDesc[BypassNode].pPipelineName;
            }
            m_pPipelineOutputBuffer[0].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[0].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[0].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[0].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
            if (streamIdMap.find(StreamUsecases::PREVIEW) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for PREVIEW");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[0].pStream = streamIdMap[StreamUsecases::PREVIEW];
        }
        else if (PipelineType::RealtimePrevFromMemcpy == type || PipelineType::RealtimeInplaceNode == type || PipelineType::RealtimeChiDepth == type)
        {
            if (PipelineType::RealtimePrevFromMemcpy == type)
            {
                m_pipelineDescriptor = Usecases1Target[TestMemcpyId].pPipelineTargetCreateDesc[PreviewFromMemcpy].pipelineCreateDesc;
                m_pipelineName = Usecases1Target[TestMemcpyId].pPipelineTargetCreateDesc[PreviewFromMemcpy].pPipelineName;
            }
            if (PipelineType::RealtimeInplaceNode == type)
            {
                m_pipelineDescriptor = Usecases1Target[TestInplaceNodeId].pPipelineTargetCreateDesc[InplaceNode].pipelineCreateDesc;
                m_pipelineName = Usecases1Target[TestInplaceNodeId].pPipelineTargetCreateDesc[InplaceNode].pPipelineName;
            }
            if (PipelineType::RealtimeChiDepth == type)
            {
                m_pipelineDescriptor = Usecases2Target[TestChiDepthId].pPipelineTargetCreateDesc[ChiDepthNode].pipelineCreateDesc;
                m_pipelineName = Usecases2Target[TestChiDepthId].pPipelineTargetCreateDesc[ChiDepthNode].pPipelineName;
            }
            m_pPipelineOutputBuffer[0].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[0].pNodePort->nodeId = nodeid_t::External;
            m_pPipelineOutputBuffer[0].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[0].pNodePort->nodePortId = externalportid_t::ChiNodeOutputPort0;
            if (streamIdMap.find(StreamUsecases::PREVIEW) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for PREVIEW");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[0].pStream = streamIdMap[StreamUsecases::PREVIEW];
        }
        else
        {
            NT_LOG_ERROR( "Invalid external pipeline type given: %d", static_cast<int>(type));
            return CDKResultEInvalidArg;
        }
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePipelineIFERawLsc
    *
    *   @brief
    *       Setup Pipeline parameters for real time ife Raw LSC usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePipelineIFERawLsc(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases1Target[UsecaseRawId].pPipelineTargetCreateDesc[Lsc].pipelineCreateDesc;
        m_pipelineName = Usecases1Target[UsecaseRawId].pPipelineTargetCreateDesc[Lsc].pPipelineName;

        UINT32 outputBufferIndex = 0;

        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortLSCRaw;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortLSCRaw) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortLSCRaw");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortLSCRaw];
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflinePipelineIPEDisplay
    *
    *   @brief
    *       Setup Pipeline parameters for offline ipe display usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflinePipelineIPEDisplay(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases2Target[TestOfflineIPEId].pPipelineTargetCreateDesc[IpeDisp].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[TestOfflineIPEId].pPipelineTargetCreateDesc[IpeDisp].pPipelineName;

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
        if (streamIdMap.find(StreamUsecases::PREVIEW) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for PREVIEW");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::PREVIEW];

        m_pipelineInputBuffer.size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::IPE;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = ipeportid_t::IPEInputPortFull;
        if (streamIdMap.find(StreamUsecases::IPEInputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEInputPortFull");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::IPEInputPortFull];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::IPE;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = ipeportid_t::IPEInputPortFull;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflinePipelineIPEJPEG
    *
    *   @brief
    *       Setup Pipeline parameters for offline ipe + jpeg usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflinePipelineIPEJPEG(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases2Target[UsecaseIPEJPEGId].pPipelineTargetCreateDesc[OFflineIPEInputYUVOutputJPEG].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[UsecaseIPEJPEGId].pPipelineTargetCreateDesc[OFflineIPEInputYUVOutputJPEG].pPipelineName;

        m_pipelineInputBuffer.size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::IPE;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = ipeportid_t::IPEInputPortFull;
        if (streamIdMap.find(StreamUsecases::IPEInputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEInputPortFull");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::IPEInputPortFull];

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::JPEGAggregator;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = jpegaggportid_t::JPEGAggregatorOutputPort;
        if (streamIdMap.find(StreamUsecases::SNAPSHOT) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for SNAPSHOT");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::SNAPSHOT];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::IPE;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = ipeportid_t::IPEInputPortFull;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflinePipelineBPS
    *
    *   @brief
    *       Setup Pipeline parameters for offline BPS fullport usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflinePipelineBPS(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases2Target[TestOfflineBPSIPEId].pPipelineTargetCreateDesc[OfflineBPSFull].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[TestOfflineBPSIPEId].pPipelineTargetCreateDesc[OfflineBPSFull].pPipelineName;

        m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::BPS;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = bpsportid_t::BPSInputPort;
        if (streamIdMap.find(StreamUsecases::BPSInputPort) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for BPSInputPort");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::BPSInputPort];

        uint32_t outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::BPS;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = bpsportid_t::BPSOutputPortFull;
        if (streamIdMap.find(StreamUsecases::BPSOutputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for BPSOutputPortFull");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::BPSOutputPortFull];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::BPS;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = bpsportid_t::BPSInputPort;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflinePipelineBPSDS4
    *
    *   @brief
    *       Setup pipeline parameters for offline BPS with DS4 (ideal raw) out usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflinePipelineBPSDS4(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases2Target[TestBPSIdealRawId].pPipelineTargetCreateDesc[BPSIdealRaw].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[TestBPSIdealRawId].pPipelineTargetCreateDesc[BPSIdealRaw].pPipelineName;

        m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::BPS;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = bpsportid_t::BPSInputPort;
        if (streamIdMap.find(StreamUsecases::BPSInputPort) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for BPSInputPort");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::BPSInputPort];

        uint32_t outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::BPS;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = bpsportid_t::BPSOutputPortDS4;
        if (streamIdMap.find(StreamUsecases::BPSOutputPortDS4) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for BPSOutputPortDS4");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::BPSOutputPortDS4];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::BPS;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = bpsportid_t::BPSInputPort;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflinePipelineIPEVideo
    *
    *   @brief
    *       Setup Pipeline parameters for offline IPE video port usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflinePipelineIPEVideo(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases2Target[TestOfflineIPEId].pPipelineTargetCreateDesc[IpeVideo].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[TestOfflineIPEId].pPipelineTargetCreateDesc[IpeVideo].pPipelineName;

        uint32_t outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortVideo;
        if (streamIdMap.find(StreamUsecases::IPEOutputPortVideo) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortVideo");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortVideo];

        m_pipelineInputBuffer.size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::IPE;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = ipeportid_t::IPEInputPortFull;
        if (streamIdMap.find(StreamUsecases::IPEInputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEInputPortFull");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::IPEInputPortFull];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::IPE;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = ipeportid_t::IPEInputPortFull;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflinePipelineIPEDispVideo
    *
    *   @brief
    *       Setup Pipeline parameters for offline IPE Display+Video port usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflinePipelineIPEDispVideo(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases3Target[TestOfflineIPESIMOId].pPipelineTargetCreateDesc[OfflineDispVideo].pipelineCreateDesc;
        m_pipelineName = Usecases3Target[TestOfflineIPESIMOId].pPipelineTargetCreateDesc[OfflineDispVideo].pPipelineName;

        uint32_t outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
        if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];

        outputBufferIndex++;

        // IPE Video --> Sink Buffer
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortVideo;
        if (streamIdMap.find(StreamUsecases::IPEOutputPortVideo) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortVideo");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortVideo];

        m_pipelineInputBuffer.size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::IPE;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = ipeportid_t::IPEInputPortFull;
        if (streamIdMap.find(StreamUsecases::IPEInputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEInputPortFull");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::IPEInputPortFull];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::IPE;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = ipeportid_t::IPEInputPortFull;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflinePipelineBPSIPE
    *
    *   @brief
    *       Setup Pipeline parameters for offline BPS+IPE Display port usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflinePipelineBPSIPE(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases2Target[TestOfflineBPSIPEId].pPipelineTargetCreateDesc[OfflineBPSIPEDisp].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[TestOfflineBPSIPEId].pPipelineTargetCreateDesc[OfflineBPSIPEDisp].pPipelineName;

        UINT32 outputBufferIndex = 0;
        m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::BPS;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = bpsportid_t::BPSInputPort;
        if (streamIdMap.find(StreamUsecases::BPSInputPort) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for BPSInputPort");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::BPSInputPort];

        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
        if (streamIdMap.find(StreamUsecases::PREVIEW) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for PREVIEW");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::PREVIEW];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::BPS;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = bpsportid_t::BPSInputPort;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflinePipelineBPSIPEJpeg
    *
    *   @brief
    *       Setup Pipeline parameters for offline BPS+IPE Jpeg port usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflinePipelineBPSIPEJpeg(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases2Target[TestOfflineBPSIPEJpegId].pPipelineTargetCreateDesc[OfflineBPSIPEJpeg].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[TestOfflineBPSIPEJpegId].pPipelineTargetCreateDesc[OfflineBPSIPEJpeg].pPipelineName;

        UINT32 outputBufferIndex = 0;
        m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::BPS;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = bpsportid_t::BPSInputPort;
        if (streamIdMap.find(StreamUsecases::BPSInputPort) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for BPSInputPort");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::BPSInputPort];

        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::JPEGAggregator;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = jpegaggportid_t::JPEGAggregatorOutputPort;
        if (streamIdMap.find(StreamUsecases::SNAPSHOT) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for SNAPSHOT");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::SNAPSHOT];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::BPS;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = bpsportid_t::BPSInputPort;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflinePipelineBPSIPEDispVideo
    *
    *   @brief
    *       Setup Pipeline parameters for offline BPS+IPE Display and Video port usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map conatining stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflinePipelineBPSIPEDispVideo(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases2Target[TestOfflineBPSIPEId].pPipelineTargetCreateDesc[OfflineBPSIPEDispVideo].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[TestOfflineBPSIPEId].pPipelineTargetCreateDesc[OfflineBPSIPEDispVideo].pPipelineName;

        UINT32 outputBufferIndex = 0;
        m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::BPS;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = bpsportid_t::BPSInputPort;
        if (streamIdMap.find(StreamUsecases::BPSInputPort) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for BPSInputPort");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::BPSInputPort];

        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
        if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortVideo;
        if (streamIdMap.find(StreamUsecases::IPEOutputPortVideo) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortVideo");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortVideo];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::BPS;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = bpsportid_t::BPSInputPort;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflinePipelineBPSStats
    *
    *   @brief
    *       Setup Pipeline parameters for offline BPS full + stats port usecase
    *       Setup Pipeline parameters for offline BPS stats port + IPE display port usecase
    *       Setup Pipeline parameters for offline BPS BGstats port + IPE display port usecase
    *       Setup Pipeline parameters for offline BPS Histstats port + IPE display port usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflinePipelineBPSStats(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::BPS;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = bpsportid_t::BPSInputPort;
        if (streamIdMap.find(StreamUsecases::BPSInputPort) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for BPSInputPort");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::BPSInputPort];

        UINT32 outputBufferIndex = 0;

        switch (type)
        {
        case PipelineType::OfflineBPSStats:
            m_pipelineDescriptor = Usecases4Target[OfflineBPSStatsId].pPipelineTargetCreateDesc[BPSStats].pipelineCreateDesc;
            m_pipelineName = Usecases4Target[OfflineBPSStatsId].pPipelineTargetCreateDesc[BPSStats].pPipelineName;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::BPS;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = bpsportid_t::BPSOutputPortFull;
            if (streamIdMap.find(StreamUsecases::BPSOutputPortFull) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for BPSOutputPortFull");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::BPSOutputPortFull];
            break;

        case PipelineType::OfflineBPSStatsWithIPE:
            m_pipelineDescriptor = Usecases4Target[OfflineBPSStatsWithIPEId].pPipelineTargetCreateDesc[BPSAllStats].pipelineCreateDesc;
            m_pipelineName = Usecases4Target[OfflineBPSStatsWithIPEId].pPipelineTargetCreateDesc[BPSAllStats].pPipelineName;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
            if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];
            break;

        case PipelineType::OfflineBPSBGStatsWithIPE:
            m_pipelineDescriptor = Usecases3Target[OfflineBPSSingleStatWithIPEId].pPipelineTargetCreateDesc[BPSBGStats].pipelineCreateDesc;
            m_pipelineName = Usecases3Target[OfflineBPSSingleStatWithIPEId].pPipelineTargetCreateDesc[BPSBGStats].pPipelineName;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
            if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];
            break;

        case PipelineType::OfflineBPSHistStatsWithIPE:
            m_pipelineDescriptor = Usecases3Target[OfflineBPSSingleStatWithIPEId].pPipelineTargetCreateDesc[BPSHistStats].pipelineCreateDesc;
            m_pipelineName = Usecases3Target[OfflineBPSSingleStatWithIPEId].pPipelineTargetCreateDesc[BPSHistStats].pPipelineName;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
            if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];
            break;

        default:
            NT_LOG_ERROR( "Invalid BPSStats pipeline type given: %d", type);
            return CDKResultEInvalidArg;
        }


        if (type != PipelineType::OfflineBPSHistStatsWithIPE)
        {
            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::BPS;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = bpsportid_t::BPSOutputPortStatsBG;
            if (streamIdMap.find(StreamUsecases::BPSOutputPortStatsBG) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for BPSOutputPortStatsBG");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::BPSOutputPortStatsBG];
        }

        if (type != PipelineType::OfflineBPSBGStatsWithIPE)
        {
            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::BPS;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = bpsportid_t::BPSOutputPortStatsBHist;
            if (streamIdMap.find(StreamUsecases::BPSOutputPortStatsBhist) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for BPSOutputPortStatsBhist");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::BPSOutputPortStatsBhist];
        }

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupPreviewCallbackSnapshotWithThumbnail
    *
    *   @brief
    *       Setup Pipeline parameters for offline preview callback snapshot with thumbnail
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupPreviewCallbackSnapshotWithThumbnail(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {

        if (type == PipelineType::RealtimePrevWithCallbackAndRDIWithStats)
        {
            m_pipelineDescriptor = Usecases5Target[TestPreviewCallbackSnapshotWithThumbnailId].pPipelineTargetCreateDesc[RealtimePrevwithCallbackAndRaw].pipelineCreateDesc;
            m_pipelineName = Usecases5Target[TestPreviewCallbackSnapshotWithThumbnailId].pPipelineTargetCreateDesc[RealtimePrevwithCallbackAndRaw].pPipelineName;

            UINT32 outputBufferIndex = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
            if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];

            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortVideo;
            if (streamIdMap.find(StreamUsecases::PREVIEWCALLBACK) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for PREVIEWCALLBACK");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::PREVIEWCALLBACK];

            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortRDI1;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortRDI1) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortRDI1");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortRDI1];
        }
        else if (type == PipelineType::RealtimePrevWithCallbackWithStats || type == PipelineType::RealtimePrevWith3AWrappers)
        {
            if (type == PipelineType::RealtimePrevWith3AWrappers)
            {
                m_pipelineDescriptor = Usecases5Target[TestPreviewCallbackSnapshotWithThumbnailId].pPipelineTargetCreateDesc[RealtimePrevWithAECWrapper].pipelineCreateDesc;
                m_pipelineName = Usecases5Target[TestPreviewCallbackSnapshotWithThumbnailId].pPipelineTargetCreateDesc[RealtimePrevWithAECWrapper].pPipelineName;
            }
            else if (type == PipelineType::RealtimePrevWithCallbackWithStats)
            {
                m_pipelineDescriptor = Usecases5Target[TestPreviewCallbackSnapshotWithThumbnailId].pPipelineTargetCreateDesc[RealtimePrevwithCallback].pipelineCreateDesc;
                m_pipelineName = Usecases5Target[TestPreviewCallbackSnapshotWithThumbnailId].pPipelineTargetCreateDesc[RealtimePrevwithCallback].pPipelineName;
            }

            UINT32 outputBufferIndex = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
            if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];

            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortVideo;
            if (streamIdMap.find(StreamUsecases::PREVIEWCALLBACK) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for PREVIEWCALLBACK");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::PREVIEWCALLBACK];

        }
        else if(type == PipelineType::RealtimePrevAndVideoWithStats)
        {
            m_pipelineDescriptor = Usecases5Target[TestPreviewCallbackSnapshotWithThumbnailId].pPipelineTargetCreateDesc[RealtimePrevAndVideoWithStats].pipelineCreateDesc;
            m_pipelineName = Usecases5Target[TestPreviewCallbackSnapshotWithThumbnailId].pPipelineTargetCreateDesc[RealtimePrevAndVideoWithStats].pPipelineName;

            UINT32 outputBufferIndex = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
            if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];

            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortVideo;
            if (streamIdMap.find(StreamUsecases::IPEOutputPortVideo) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortVideo");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortVideo];

            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortRDI1;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortRDI1) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortRDI1");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortRDI1];
        }
        else if(type == PipelineType::OfflineZSlSnapAndThumbnailWithDSports)
        {
            m_pipelineDescriptor = Usecases5Target[TestPreviewCallbackSnapshotWithThumbnailId].pPipelineTargetCreateDesc[ZSLSnapshotJpegWithThumbnail].pipelineCreateDesc;
            m_pipelineName = Usecases5Target[TestPreviewCallbackSnapshotWithThumbnailId].pPipelineTargetCreateDesc[ZSLSnapshotJpegWithThumbnail].pPipelineName;

            m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
            m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::BPS;
            m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
            m_pipelineInputBuffer.pNodePort->nodePortId = bpsportid_t::BPSInputPort;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortRDI1) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortRDI1");
                return CDKResultENoSuch;
            }
            m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::IFEOutputPortRDI1];

            UINT32 outputBufferIndex = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::JPEGAggregator;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = jpegaggportid_t::JPEGAggregatorOutputPort;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            if (streamIdMap.find(StreamUsecases::SNAPSHOT) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for SNAPSHOT");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::SNAPSHOT];

            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortVideo;
            if (streamIdMap.find(StreamUsecases::THUMBNAIL) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for PREVIEWCALLBACK");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::THUMBNAIL];
        }
        else
        {
            NT_LOG_ERROR( "Invalid pipeline type");
            return CDKResultEInvalidArg;
        }
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflineJpeg
    *
    *   @brief
    *       Setup Pipeline parameters for offline jpeg snapshot usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflineJpeg(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases2Target[TestOfflineJPEGId].pPipelineTargetCreateDesc[JpegSnapshot].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[TestOfflineJPEGId].pPipelineTargetCreateDesc[JpegSnapshot].pPipelineName;

        UINT32 outputBufferIndex = 0;

        m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::JPEG;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = jpegportid_t::JPEGInputPort;
        if (streamIdMap.find(StreamUsecases::JPEGInputPort) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for JPEGInputPort");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::JPEGInputPort];

        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::JPEGAggregator;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = jpegaggportid_t::JPEGAggregatorOutputPort;
        if (streamIdMap.find(StreamUsecases::SNAPSHOT) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for SNAPSHOT");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::SNAPSHOT];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::JPEG;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = jpegportid_t::JPEGInputPort;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 4096;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupCustomVendorWritePipeline
    *
    *   @brief
    *       Setup Pipeline parameters for real time preview usecase with custom vendortag node
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupCustomVendorWritePipeline(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases1Target[TestCustomNodeId].pPipelineTargetCreateDesc[VendorTagWrite].pipelineCreateDesc;
        m_pipelineName = Usecases1Target[TestCustomNodeId].pPipelineTargetCreateDesc[VendorTagWrite].pPipelineName;

        UINT32 outputBufferIndex = 0;

        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
        if (streamIdMap.find(StreamUsecases::PREVIEW) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for PREVIEW");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::PREVIEW];
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePipelineIFERDIO
    *
    *   @brief
    *       Setup Pipeline parameters for real time ife Raw RDI0 usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePipelineIFERDIO(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases1Target[UsecaseRawId].pPipelineTargetCreateDesc[RDI0].pipelineCreateDesc;
        m_pipelineName = Usecases1Target[UsecaseRawId].pPipelineTargetCreateDesc[RDI0].pPipelineName;

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortRDI0;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortRDI0) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortRDI0");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortRDI0];
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePipelineIFERDIOTestgen
    *
    *   @brief
    *       Setup Pipeline parameters for real time ife Raw RDI0 usecase with testgen
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePipelineIFERDIOTestgen(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases1Target[UsecaseRawId].pPipelineTargetCreateDesc[RDI0Testgen].pipelineCreateDesc;
        m_pipelineName = Usecases1Target[UsecaseRawId].pPipelineTargetCreateDesc[RDI0Testgen].pPipelineName;

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortRDI0;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortRDI0) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortRDI0");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortRDI0];
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePrevRDI
    *
    *   @brief
    *       Setup Pipeline parameters for real time Preview + RDI usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePrevRDI(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
        if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;

        if(type == PipelineType::RealtimePrevRDIWithStats)
        {
            m_pipelineDescriptor = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLPreviewRawWithStats].pipelineCreateDesc;
            m_pipelineName = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLPreviewRawWithStats].pPipelineName;

            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortRDI1;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortRDI1) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortRDI1");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortRDI1];
        }
        else
        {
            if(type == PipelineType::PrevRDIwithTestGen)
            {
                m_pipelineDescriptor = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLPreviewRawWithTestGen].pipelineCreateDesc;
                m_pipelineName = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLPreviewRawWithTestGen].pPipelineName;
            }
            else
            {
                m_pipelineDescriptor = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLPreviewRaw].pipelineCreateDesc;
                m_pipelineName = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLPreviewRaw].pPipelineName;
            }

            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortRDI0;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortRDI0) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortRDI0");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortRDI0];
        }
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflineZSLSnapShot
    *
    *   @brief
    *       Setup Pipeline parameters for offline snapshot usecase, containing BPS+IPE+JPEG nodes or
    *       BPS+IPE nodes based on snapshot stream format
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflineZSLSnapShot(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        UINT32 outputBufferIndex = 0;

        m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::BPS;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = bpsportid_t::BPSInputPort;

        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        if (streamIdMap.find(StreamUsecases::SNAPSHOT) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for SNAPSHOT");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::SNAPSHOT];

        if(type == PipelineType::OfflineZSlSnapWithDSports)
        {
            if (streamIdMap.find(StreamUsecases::IFEOutputPortRDI1) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortRDI1");
                return CDKResultENoSuch;
            }
            m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::IFEOutputPortRDI1];

            if (streamIdMap[StreamUsecases::SNAPSHOT]->format == ChiStreamFormatBlob)
            {
                m_pipelineDescriptor = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLSnapshotJpegWithDS].pipelineCreateDesc;
                m_pipelineName = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLSnapshotJpegWithDS].pPipelineName;

                m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::JPEGAggregator;
                m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
                m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = jpegaggportid_t::JPEGAggregatorOutputPort;

            }
            else if (streamIdMap[StreamUsecases::SNAPSHOT]->format == ChiStreamFormatYCbCr420_888)
            {
                m_pipelineDescriptor = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLSnapshotYUVWithDS].pipelineCreateDesc;
                m_pipelineName = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLSnapshotYUVWithDS].pPipelineName;

                m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
                m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
                m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
            }
            else
            {
                NT_LOG_ERROR( "Invalid stream format for offline snapshot");
                return CDKResultEInvalidArg;
            }
        }
        else
        {
            if (streamIdMap.find(StreamUsecases::IFEOutputPortRDI0) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortRDI0");
                return CDKResultENoSuch;
            }
            m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::IFEOutputPortRDI0];

            if (streamIdMap[StreamUsecases::SNAPSHOT]->format == ChiStreamFormatBlob)
            {
                m_pipelineDescriptor = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLSnapshotJpeg].pipelineCreateDesc;
                m_pipelineName = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLSnapshotJpeg].pPipelineName;

                m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::JPEGAggregator;
                m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
                m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = jpegaggportid_t::JPEGAggregatorOutputPort;

            }
            else if (streamIdMap[StreamUsecases::SNAPSHOT]->format == ChiStreamFormatYCbCr420_888)
            {
                m_pipelineDescriptor = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLSnapshotYUV].pipelineCreateDesc;
                m_pipelineName = Usecases3Target[TestZSLUseCaseId].pPipelineTargetCreateDesc[ZSLSnapshotYUV].pPipelineName;

                m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
                m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
                m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
            }
            else
            {
                NT_LOG_ERROR( "Invalid stream format for offline snapshot: %d", streamIdMap[StreamUsecases::SNAPSHOT]->format);
                return CDKResultEInvalidArg;
            }

        }

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::BPS;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = bpsportid_t::BPSInputPort;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflineBPSGPUPipeline
    *
    *   @brief
    *       Setup Pipeline parameters for offline BPS with GPU node
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflineBPSGPUPipeline(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases5Target[TestGPUDSPortsId].pPipelineTargetCreateDesc[OfflineBPSGPU].pipelineCreateDesc;
        m_pipelineName = Usecases5Target[TestGPUDSPortsId].pPipelineTargetCreateDesc[OfflineBPSGPU].pPipelineName;

        m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::BPS;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = bpsportid_t::BPSInputPort;
        if (streamIdMap.find(StreamUsecases::BPSInputPort) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for BPSInputPort");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::BPSInputPort];

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = 255;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = gpuportid_t::GPUOutputPortFull;
        if (streamIdMap.find(StreamUsecases::GPUOutputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for GPUOutputPortFull");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::GPUOutputPortFull];
        outputBufferIndex++;

        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = 255;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = gpuportid_t::GPUOutputPortDS4;
        if (streamIdMap.find(StreamUsecases::GPUOutputPortDS4) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for GPUOutputPortDS4");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::GPUOutputPortDS4];
        outputBufferIndex++;

        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = 255;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = gpuportid_t::GPUOutputPortDS16;
        if (streamIdMap.find(StreamUsecases::GPUOutputPortDS16) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for GPUOutputPortDS16");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::GPUOutputPortDS16];
        outputBufferIndex++;

        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = 255;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = gpuportid_t::GPUOutputPortDS64;
        if (streamIdMap.find(StreamUsecases::GPUOutputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for GPUOutputPortDS64");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::GPUOutputPortDS64];


        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::BPS;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = bpsportid_t::BPSInputPort;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflineFDPipeline
    *
    *   @brief
    *       Setup Pipeline parameters for offline FD usecases
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflineFDPipeline(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases2Target[TestOfflineFDId].pPipelineTargetCreateDesc[OfflineFD].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[TestOfflineFDId].pPipelineTargetCreateDesc[OfflineFD].pPipelineName;

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::FDManager;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = fdmgrportid_t::FDManagerOutputPort;
        if (streamIdMap.find(StreamUsecases::FDManagerOutputPort) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for FDManagerOutputPort");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::FDManagerOutputPort];

        m_pipelineInputBuffer.size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::External;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = externalportid_t::ChiNodeInputPort0;

        if (streamIdMap.find(StreamUsecases::ChiNodeInputPort0) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for ChiNodeInputPort0");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::ChiNodeInputPort0];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::External;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = externalportid_t::ChiNodeInputPort0;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);

        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimeIPEABCTestgen
    *
    *   @brief
    *       Setup Pipeline parameters for realtime IFE + IPE with ABC ports, dumped stats, and testgen
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimeIPEABCTestgen(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        switch (type)
        {
        case PipelineType::RealtimeIPEATestgen:
            m_pipelineDescriptor = Usecases2Target[TestIPETestgenId].pPipelineTargetCreateDesc[IPEATestgen].pipelineCreateDesc;
            m_pipelineName = Usecases2Target[TestIPETestgenId].pPipelineTargetCreateDesc[IPEATestgen].pPipelineName;
            break;
        case PipelineType::RealtimeIPE3ATestgen:
            m_pipelineDescriptor = Usecases1Target[TestIPE3ATestgenId].pPipelineTargetCreateDesc[IPE3ATestgen].pipelineCreateDesc;
            m_pipelineName = Usecases1Target[TestIPE3ATestgenId].pPipelineTargetCreateDesc[IPE3ATestgen].pPipelineName;
            break;
        case PipelineType::RealtimeIPEABTestgen:
            m_pipelineDescriptor = Usecases2Target[TestIPETestgenId].pPipelineTargetCreateDesc[IPEABTestgen].pipelineCreateDesc;
            m_pipelineName = Usecases2Target[TestIPETestgenId].pPipelineTargetCreateDesc[IPEABTestgen].pPipelineName;
            break;
        case PipelineType::RealtimeIPEABStatsTestgen:
            m_pipelineDescriptor = Usecases2Target[TestIPETestgenId].pPipelineTargetCreateDesc[IPEABStatsTestgen].pipelineCreateDesc;
            m_pipelineName = Usecases2Target[TestIPETestgenId].pPipelineTargetCreateDesc[IPEABStatsTestgen].pPipelineName;
            break;
        case PipelineType::RealtimeIPEABCStatsTestgen:
            m_pipelineDescriptor = Usecases2Target[TestIPETestgenId].pPipelineTargetCreateDesc[IPEABCStatsTestgen].pipelineCreateDesc;
            m_pipelineName = Usecases2Target[TestIPETestgenId].pPipelineTargetCreateDesc[IPEABCStatsTestgen].pPipelineName;
            break;
        default:
            NT_LOG_ERROR( "Invalid RealtimeIPEABCTestgen pipeline type given: %d", static_cast<int>(type));
            return CDKResultEInvalidArg;
        }

        //1. IPEOutputPortDisplay (A)
        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
        if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];

        if (type == PipelineType::RealtimeIPEABTestgen ||
            type == PipelineType::RealtimeIPEABStatsTestgen ||
            type == PipelineType::RealtimeIPEABCStatsTestgen)
        {
            //2. IPEOutputPortVideo (B)
            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortVideo;
            if (streamIdMap.find(StreamUsecases::IPEOutputPortVideo) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortVideo");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortVideo];
        }

        if (type == PipelineType::RealtimeIPEABCStatsTestgen)
        {
            //3. IFEOutputPortFD (C)
            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortFD;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortFD) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortFD");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortFD];
        }

        if (type == PipelineType::RealtimeIPEABStatsTestgen ||
            type == PipelineType::RealtimeIPEABCStatsTestgen)
        {
            //4. IFEOutputPortStatsBF
            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsBF;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsBF) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsBF");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsBF];

            //5. IFEOutputPortStatsAWBBG
            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsAWBBG;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsAWBBG) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsAWBBG");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsAWBBG];

            //6. IFEOutputPortStatsTLBG
            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsTLBG;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsTLBG) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsTLBG");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsTLBG];

            //7. IFEOutputPortStatsIHIST
            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsIHIST;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsIHIST) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsIHIST");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsIHIST];

            //8. IFEOutputPortStatsRS
            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsRS;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsRS) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsRS");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsRS];
        }

        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimeIPEABC
    *
    *   @brief
    *       Setup Pipeline parameters for realtime IFE + IPE with ABC ports and dumped stats
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimeIPEABC(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        switch (type)
        {
        case PipelineType::RealtimeIPEABCStats:
            m_pipelineDescriptor = Usecases2Target[TestIPESensorId].pPipelineTargetCreateDesc[IPEABCStatsSensor].pipelineCreateDesc;
            m_pipelineName = Usecases2Target[TestIPESensorId].pPipelineTargetCreateDesc[IPEABCStatsSensor].pPipelineName;
            break;
        default:
            NT_LOG_ERROR( "Invalid RealtimeIPEABCStats pipeline type given: %d", static_cast<int>(type));
            return CDKResultEInvalidArg;
        }

        //1. IPEOutputPortDisplay (A)
        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
        if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];

        //2. IPEOutputPortVideo (B)
        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortVideo;
        if (streamIdMap.find(StreamUsecases::IPEOutputPortVideo) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortVideo");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortVideo];

        //3. IFEOutputPortFD (C)
        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortFD;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortFD) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortFD");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortFD];

        //4. IFEOutputPortStatsBF
        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsBF;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsBF) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsBF");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsBF];

        //5. IFEOutputPortStatsAWBBG
        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsAWBBG;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsAWBBG) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsAWBBG");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsAWBBG];

        //6. IFEOutputPortStatsTLBG
        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsTLBG;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsTLBG) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsTLBG");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsTLBG];

        //7. IFEOutputPortStatsIHIST
        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsIHIST;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsIHIST) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsIHIST");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsIHIST];

        //8. IFEOutputPortStatsRS
        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsRS;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsRS) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsRS");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsRS];

        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePIPCam
    *
    *   @brief
    *       Setup pipeline parameters for realtime IFE + IPE with ABC ports, dumped stats, and RDI.
    *       Used for PIP camera tests.
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePIPCam(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        switch (type)
        {
        case PipelineType::RealtimeIPEAStatsRDI:
            m_pipelineDescriptor = Usecases3Target[TestPIPCamId].pPipelineTargetCreateDesc[IPEAStats].pipelineCreateDesc;
            m_pipelineName = Usecases3Target[TestPIPCamId].pPipelineTargetCreateDesc[IPEAStats].pPipelineName;
            break;
        case PipelineType::RealtimeIPEACStatsRDI:
            m_pipelineDescriptor = Usecases3Target[TestPIPCamId].pPipelineTargetCreateDesc[IPEACStats].pipelineCreateDesc;
            m_pipelineName = Usecases3Target[TestPIPCamId].pPipelineTargetCreateDesc[IPEACStats].pPipelineName;
            break;
        case PipelineType::RealtimeIPEABCStatsRDI:
            m_pipelineDescriptor = Usecases3Target[TestPIPCamId].pPipelineTargetCreateDesc[IPEABCStats].pipelineCreateDesc;
            m_pipelineName = Usecases3Target[TestPIPCamId].pPipelineTargetCreateDesc[IPEABCStats].pPipelineName;
            break;
        case PipelineType::RealtimeRDI1Only:
            m_pipelineDescriptor = Usecases3Target[TestPIPCamId].pPipelineTargetCreateDesc[RDI1Only].pipelineCreateDesc;
            m_pipelineName = Usecases3Target[TestPIPCamId].pPipelineTargetCreateDesc[RDI1Only].pPipelineName;
            break;
        default:
            NT_LOG_ERROR( "Invalid RealtimePIPCam pipeline type given: %d", static_cast<int>(type));
            return CDKResultEInvalidArg;
        }

        UINT32 outputBufferIndex = 0;

        if (type == PipelineType::RealtimeIPEAStatsRDI ||
            type == PipelineType::RealtimeIPEACStatsRDI ||
            type == PipelineType::RealtimeIPEABCStatsRDI)
        {
            //1. IPEOutputPortDisplay (A)
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
            if (streamIdMap.find(StreamUsecases::IPEOutputPortDisplay) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortDisplay");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];
            outputBufferIndex++;
        }

        if (type == PipelineType::RealtimeIPEABCStatsRDI)
        {
            //2. IPEOutputPortVideo (B)
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortVideo;
            if (streamIdMap.find(StreamUsecases::IPEOutputPortVideo) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IPEOutputPortVideo");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortVideo];
            outputBufferIndex++;
        }

        if (type == PipelineType::RealtimeIPEACStatsRDI ||
            type == PipelineType::RealtimeIPEABCStatsRDI)
        {
            //3. IFEOutputPortFD (C)
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortFD;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortFD) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortFD");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortFD];
            outputBufferIndex++;
        }

        if (type == PipelineType::RealtimeIPEAStatsRDI ||
            type == PipelineType::RealtimeIPEACStatsRDI ||
            type == PipelineType::RealtimeIPEABCStatsRDI)
        {
            //4. IFEOutputPortStatsIHIST
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortStatsIHIST;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortStatsIHIST) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortStatsIHIST");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortStatsIHIST];
            outputBufferIndex++;
        }

        if (type == PipelineType::RealtimeIPEAStatsRDI ||
            type == PipelineType::RealtimeIPEACStatsRDI)
        {
            //5. IFEOutputPortRDI0
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortRDI0;
            if (streamIdMap.find(StreamUsecases::IFEOutputPortRDI0) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortRDI0");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortRDI0];
            outputBufferIndex++;
        }

        //6. IFEOutputPortRDI1
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortRDI1;
        if (streamIdMap.find(StreamUsecases::IFEOutputPortRDI1) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortRDI1");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortRDI1];

        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflineBPSWithIPEAndDSPipeline
    *
    *   @brief
    *       Setup pipeline parameters for BPS -> IPE with raw input and downscaling
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflineBPSWithIPEAndDSPipeline(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases2Target[TestBPSWithIPEAndDSId].pPipelineTargetCreateDesc[BPSWithIPEAndDS].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[TestBPSWithIPEAndDSId].pPipelineTargetCreateDesc[BPSWithIPEAndDS].pPipelineName;

        m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::BPS;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = bpsportid_t::BPSInputPort;
        if (streamIdMap.find(StreamUsecases::BPSInputPort) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for BPSInputPort");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::BPSInputPort];

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
        if (streamIdMap.find(StreamUsecases::PREVIEW) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for PREVIEW");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::PREVIEW];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::BPS;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = bpsportid_t::BPSInputPort;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflineChiGPUNode
    *
    *   @brief
    *       Setup Pipeline parameters for offline ChiGPUNode usecase
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflineChiGPUNode(std::map<StreamUsecases, ChiStream*> streamIdMap)
    {
        m_pipelineDescriptor = Usecases2Target[UsecaseChiGPUNodeId].pPipelineTargetCreateDesc[TestChiGPUNode].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[UsecaseChiGPUNodeId].pPipelineTargetCreateDesc[TestChiGPUNode].pPipelineName;

        m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::External;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = gpuportid_t::GPUInputPort;
        if (streamIdMap.find(StreamUsecases::GPUInputPort) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for GPUInputPort");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::GPUInputPort];

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::External;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = gpuportid_t::GPUOutputPortFull;
        if (streamIdMap.find(StreamUsecases::GPUOutputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for GPUOutputPortFull");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::GPUOutputPortFull];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::External;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = gpuportid_t::GPUInputPort;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimeJpeg
    *
    *   @brief
    *       Setup pipeline parameters for JPEG node tests.
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map conatining stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimeJpeg(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        switch (type)
        {
        case PipelineType::RealtimeIPEJpeg:
            m_pipelineDescriptor = Usecases2Target[RealtimeNodesTestId].pPipelineTargetCreateDesc[SensorIFEIPEJpeg].pipelineCreateDesc;
            m_pipelineName = Usecases2Target[RealtimeNodesTestId].pPipelineTargetCreateDesc[SensorIFEIPEJpeg].pPipelineName;
            break;
        case PipelineType::RealtimeBPSIPEJpeg:
            m_pipelineDescriptor = Usecases2Target[RealtimeNodesTestId].pPipelineTargetCreateDesc[SensorIFEBPSIPEJpeg].pipelineCreateDesc;
            m_pipelineName = Usecases2Target[RealtimeNodesTestId].pPipelineTargetCreateDesc[SensorIFEBPSIPEJpeg].pPipelineName;
            break;
        default:
            NT_LOG_ERROR( "Invalid Realtime JPEG node pipeline type given: %d", static_cast<int>(type));
            return CDKResultEInvalidArg;
        }

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::JPEGAggregator;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = jpegaggportid_t::JPEGAggregatorOutputPort;
        if (streamIdMap.find(StreamUsecases::SNAPSHOT) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for SNAPSHOT");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::SNAPSHOT];

        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimeFD
    *
    *   @brief
    *       Setup pipeline parameters for JPEG and FD nodes tests.
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map conatining stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimeFD(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        switch (type)
        {
        case PipelineType::RealtimeFD:
            m_pipelineDescriptor = Usecases2Target[RealtimeNodesTestId].pPipelineTargetCreateDesc[SensorIFEFD].pipelineCreateDesc;
            m_pipelineName = Usecases2Target[RealtimeNodesTestId].pPipelineTargetCreateDesc[SensorIFEFD].pPipelineName;
            break;
        default:
            NT_LOG_ERROR( "Invalid Realtime FD node pipeline type given: %d", static_cast<int>(type));
            return CDKResultEInvalidArg;
        }

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::FDManager;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = fdmgrportid_t::FDManagerOutputPort;
        if (streamIdMap.find(StreamUsecases::FDManagerOutputPort) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for FDManagerOutputPort");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::FDManagerOutputPort];

        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflineExternalNode
    *
    *   @brief
    *       Setup offline pipeline parameters for using ChiExternalNode tests.
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map conatining stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflineChiExternalNode(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        switch (type)
        {
        case PipelineType::OfflineExtBPSIPE:
            m_pipelineDescriptor = Usecases2Target[UsecaseExternalNodeId].pPipelineTargetCreateDesc[OfflineExtBPSIPE].pipelineCreateDesc;
            m_pipelineName = Usecases2Target[UsecaseExternalNodeId].pPipelineTargetCreateDesc[OfflineExtBPSIPE].pPipelineName;
            break;
        case PipelineType::OfflineExtBPSIPEJPEG:
            m_pipelineDescriptor = Usecases2Target[UsecaseExternalNodeId].pPipelineTargetCreateDesc[OfflineExtBPSIPEJPEG].pipelineCreateDesc;
            m_pipelineName = Usecases2Target[UsecaseExternalNodeId].pPipelineTargetCreateDesc[OfflineExtBPSIPEJPEG].pPipelineName;
            break;
        default:
            NT_LOG_ERROR( "Invalid ExternalNode pipeline type given: %d", static_cast<int>(type));
            return CDKResultEInvalidArg;
        }

        m_pipelineInputBuffer.size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::External;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = externalportid_t::ChiNodeInputPort0;
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::ChiNodeInputPort0];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::External;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = externalportid_t::ChiNodeInputPort0;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);

        UINT32 outputBufferIndex = 0;
        if (type == PipelineType::OfflineExtBPSIPE)
        {
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
            if (streamIdMap.find(StreamUsecases::SNAPSHOT) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for SNAPSHOT");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::SNAPSHOT];
        }
        if (type == PipelineType::OfflineExtBPSIPEJPEG)
        {
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::JPEGAggregator;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = jpegaggportid_t::JPEGAggregatorOutputPort;
            if (streamIdMap.find(StreamUsecases::SNAPSHOT) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for SNAPSHOT");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::SNAPSHOT];
        }

        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflineDepthNode
    *
    *   @brief
    *       Setup pipeline parameters for offline depth node
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map conatining stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflineDepthNode(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        NATIVETEST_UNUSED_PARAM(type);

        m_pipelineDescriptor = Usecases2Target[TestChiDepthId].pPipelineTargetCreateDesc[DepthNodeOffline].pipelineCreateDesc;
        m_pipelineName = Usecases2Target[TestChiDepthId].pPipelineTargetCreateDesc[DepthNodeOffline].pPipelineName;

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::External;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = externalportid_t::ChiNodeOutputPort0;
        if (streamIdMap.find(StreamUsecases::ChiNodeOutputPort0) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for ChiNodeOutputPort0");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::ChiNodeOutputPort0];

        m_pipelineInputBuffer.size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::External;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = externalportid_t::ChiNodeInputPort0;
        if (streamIdMap.find(StreamUsecases::ChiNodeInputPort0) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for ChiNodeInputPort0");
            return CDKResultENoSuch;
        }
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::ChiNodeInputPort0];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::External;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = externalportid_t::ChiNodeInputPort0;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);
        return CDKResultSuccess;
    }

/**************************************************************************************************
*   PipelineUtils::SetupRealtimeIFEGeneric
*
*   @brief
*       Setup pipeline parameters for generic IFE tests
*   @param
*       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map conatining stream objects
*       [in]  Pipeline                                type            differentiate between pipelines
*   @return
*       CDKResult result
**************************************************************************************************/
CDKResult PipelineUtils::SetupRealtimeIFEGeneric(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
{
    ChiUsecase selectUsecase;
    ChiPipelineTargetCreateDescriptor selectTargetCreateDescriptor;

    // Select usecase and target create descriptor based on pipeline type
    switch (type)
    {
    case PipelineType::RealtimeIFEGeneric:
        selectUsecase = Usecases2Target[UsecaseGenericId];
        selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[IFEGeneric];
        break;
    case PipelineType::RealtimeIFEGenericTestgen:
        selectUsecase = Usecases2Target[UsecaseGenericId];
        selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[IFEGenericTestgen];
        break;
    case PipelineType::RealtimeIFEGeneric2Stream:
        selectUsecase = Usecases3Target[UsecaseGeneric2StreamsId];
        selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[IFEGeneric2Stream];
        break;
    case PipelineType::RealtimeIFEGeneric2StreamTestgen:
        selectUsecase = Usecases3Target[UsecaseGeneric2StreamsId];
        selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[IFEGeneric2StreamTestgen];
        break;
    case PipelineType::RealtimeIFEGeneric2StreamDisplay:
        selectUsecase = Usecases3Target[UsecaseGeneric2StreamsId];
        selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[IFEGeneric2StreamDisplay];
        break;
    case PipelineType::RealtimeIFEGeneric2StreamDisplayTestgen:
        selectUsecase = Usecases3Target[UsecaseGeneric2StreamsId];
        selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[IFEGeneric2StreamDisplayTestgen];
        break;
    default:
        NT_LOG_ERROR( "Invalid Realtime IFE Generic pipeline type given : %d", static_cast<int>(type));
        return CDKResultEInvalidArg;
    }

    m_pipelineDescriptor = selectTargetCreateDescriptor.pipelineCreateDesc;
    m_pipelineName = selectTargetCreateDescriptor.pPipelineName;

    if (streamIdMap.find(StreamUsecases::CONFIG_OUTPUT) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for CONFIG_OUTPUT");
        return CDKResultENoSuch;
    }

    IfePortId selectIfePort;
    CHISTREAMFORMAT selectFormat = streamIdMap[StreamUsecases::CONFIG_OUTPUT]->format;

    // Set the default output port based on format
    switch (selectFormat)
    {
    case ChiStreamFormatYCrCb420_SP:
    case ChiStreamFormatYCbCr420_888:
    case ChiStreamFormatImplDefined:
    case ChiStreamFormatUBWCTP10:
    case ChiStreamFormatUBWCNV12:
    case ChiStreamFormatP010:
    case ChiStreamFormatNV12HEIF:
        selectIfePort = ifeportid_t::IFEOutputPortFull;
        break;
    case ChiStreamFormatRaw16:
    case ChiStreamFormatRawOpaque:
    case ChiStreamFormatRaw10:
    case ChiStreamFormatRaw64:
        selectIfePort = ifeportid_t::IFEOutputPortRDI0;
        break;
    case ChiStreamFormatPD10:
        selectIfePort = ifeportid_t::IFEOutputPortDS4;
        break;
    case ChiStreamFormatBlob:
        selectIfePort = ifeportid_t::IFEOutputPortStatsRS;
        break;
    // Formats which we don't know the output port on IFE
    case ChiStreamFormatY8:
    case ChiStreamFormatY16:
        selectIfePort = ifeportid_t::IFEOutputPortFull;
        NT_LOG_WARN( "Output port is unknown for CHISTREAMFORMAT %d on IFE generic pipeline. "
            "Setting to default output port %d...", selectFormat, selectIfePort);
        break;
    default:
        selectIfePort = ifeportid_t::IFEOutputPortFull;
        NT_LOG_WARN( "Unknown format %d. Setting to default output port %d...", selectFormat, selectIfePort);
        break;
    }
    NT_LOG_INFO( "Default output port for format %d is [%d]", selectFormat, selectIfePort);

    // If user provided an output port, override the default from format
    IfePortId overrideIfePort = static_cast<IfePortId>(CmdLineParser::GetOutputPort());
    if (IfePortId::IFEPortInvalid != overrideIfePort)
    {
        selectIfePort = overrideIfePort;
        NT_LOG_INFO( "Overriding default output port with [%d]", overrideIfePort);
    }

    // Edit the pipeline descriptor with selected output port
    const uint32_t CONFIG_INDEX = 0;
    m_pipelineDescriptor.pLinks[CONFIG_INDEX].srcNode.nodePortId = selectIfePort;
    m_pipelineDescriptor.pNodes[CONFIG_INDEX].nodeAllPorts.pOutputPorts[CONFIG_INDEX].portId = selectIfePort;
    selectTargetCreateDescriptor.sinkTarget.pTargetPortDesc[CONFIG_INDEX].pNodePort->nodePortId = selectIfePort;

    // Setup configurable output buffer
    UINT32 outputBufferIndex = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = selectIfePort;
    m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::CONFIG_OUTPUT];

    if (type == PipelineType::RealtimeIFEGeneric2StreamTestgen || type == PipelineType::RealtimeIFEGeneric2Stream)
    {
        // Setup static full output buffer
        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortFull;
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortFull];
        if (streamIdMap.find(StreamUsecases::IFEOutputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortFull");
            return CDKResultENoSuch;
        }
    }
    else if (type == PipelineType::RealtimeIFEGeneric2StreamDisplayTestgen || type == PipelineType::RealtimeIFEGeneric2StreamDisplay)
    {
        // Setup static display full output buffer
        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortDisplayFull;
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortDisplayFull];
        if (streamIdMap.find(StreamUsecases::IFEOutputPortDisplayFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortDisplayFull");
            return CDKResultENoSuch;
        }
    }

    return CDKResultSuccess;
}

/**************************************************************************************************
*   PipelineUtils::SetupRealtimeIFEDownscaleGenericTestgen
*
*   @brief
*       Setup pipeline parameters for IFE -> IPE with downscaling and configurable resolution, output format
*   @param
*       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
*   @return
*       CDKResult result
**************************************************************************************************/
CDKResult PipelineUtils::SetupRealtimeIFEDownscaleGenericTestgen(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
{
    NT_UNUSED_PARAM(type);

    ChiUsecase selectUsecase;
    ChiPipelineTargetCreateDescriptor selectTargetCreateDescriptor;

    selectUsecase = Usecases2Target[UsecaseGenericDownscaleId];
    selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[IFEGenericDownscaleTestgen];

    m_pipelineDescriptor = selectTargetCreateDescriptor.pipelineCreateDesc;
    m_pipelineName = selectTargetCreateDescriptor.pPipelineName;

    // IFE full out stream
    UINT32 outputBufferIndex = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortFull;
    if (streamIdMap.find(StreamUsecases::IFEOutputPortFull) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortFull");
        return CDKResultENoSuch;
    }
    m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortFull];

    // IFE DS4 out stream
    outputBufferIndex++;
    m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortDS4;
    if (streamIdMap.find(StreamUsecases::IFEOutputPortDS4) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortDS4");
        return CDKResultENoSuch;
    }
    m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortDS4];

    // IFE DS16 out stream
    outputBufferIndex++;
    m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ifeportid_t::IFEOutputPortDS16;
    if (streamIdMap.find(StreamUsecases::IFEOutputPortDS16) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortDS16");
        return CDKResultENoSuch;
    }
    m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortDS16];

    return CDKResultSuccess;
}

/**************************************************************************************************
*   PipelineUtils::SetupOfflineIPEGeneric
*
*   @brief
*       Setup pipeline parameters for generic IPE tests
*   @param
*       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
*       [in]  Pipeline                                type            differentiate between pipelines
*   @return
*       CDKResult result
**************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflineIPEGeneric(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
{
    ChiUsecase selectUsecase;
    ChiPipelineTargetCreateDescriptor selectTargetCreateDescriptor;

    switch (type)
    {
        case PipelineType::OfflineIPEGeneric:
            selectUsecase = Usecases2Target[UsecaseGenericId];
            selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[IPEGeneric];
            break;
        case PipelineType::OfflineIPEGeneric2StreamDisplay:
            selectUsecase = Usecases3Target[UsecaseGeneric2StreamsId];
            selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[IPEGeneric2StreamDisplay];
            break;
        default:
            NT_LOG_ERROR("Unknown pipeline type %d", type);
            return CDKResultEFailed;
    }

    m_pipelineDescriptor = selectTargetCreateDescriptor.pipelineCreateDesc;
    m_pipelineName = selectTargetCreateDescriptor.pPipelineName;

    if (streamIdMap.find(StreamUsecases::CONFIG_OUTPUT) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for CONFIG_OUTPUT");
        return CDKResultENoSuch;
    }

    IpePortId selectIpeOutputPort;
    CHISTREAMFORMAT selectOutputFormat = streamIdMap[StreamUsecases::CONFIG_OUTPUT]->format;

    // Set the default output port based on format
    // TODO: Add appropriate outputport for each formats
    switch (selectOutputFormat)
    {
    case ChiStreamFormatYCrCb420_SP:
    case ChiStreamFormatYCbCr420_888:
    case ChiStreamFormatImplDefined:
    case ChiStreamFormatUBWCTP10:
    case ChiStreamFormatUBWCNV12:
    case ChiStreamFormatP010:
        selectIpeOutputPort = ipeportid_t::IPEOutputPortVideo;
        break;
    // Set output port to IPEOutputPortVideo for unknown formats
    case ChiStreamFormatNV12HEIF:
    case ChiStreamFormatRaw16:
    case ChiStreamFormatRawOpaque:
    case ChiStreamFormatRaw10:
    case ChiStreamFormatRaw64:
    case ChiStreamFormatPD10:
    case ChiStreamFormatBlob:
    case ChiStreamFormatY8:
    case ChiStreamFormatY16:
        selectIpeOutputPort = ipeportid_t::IPEOutputPortVideo;
        NT_LOG_WARN( "Output port is unknown for CHISTREAMFORMAT %d on IPE generic pipeline. "
            "Setting to default output port %d...", selectOutputFormat, selectIpeOutputPort);
        break;
    default:
        selectIpeOutputPort = ipeportid_t::IPEOutputPortVideo;
        NT_LOG_WARN( "Unknown format %d. Setting to default output port %d...", selectOutputFormat, selectIpeOutputPort);
            break;
    }
    NT_LOG_INFO( "Default output port for format %d is [%d]", selectOutputFormat, selectIpeOutputPort);

    // If user provided an output port, override the default from format
    IpePortId overrideIpeOutputPort = static_cast<IpePortId>(CmdLineParser::GetOutputPort());
    if (IpePortId::IPEPortInvalid != overrideIpeOutputPort)
    {
        selectIpeOutputPort = overrideIpeOutputPort;
        NT_LOG_INFO( "Overriding default output port with [%d]", overrideIpeOutputPort);
    }

    // Edit the pipeline descriptor with selected output port
    const uint32_t CONFIG_INDEX = 0;
    m_pipelineDescriptor.pLinks[CONFIG_INDEX].srcNode.nodePortId = selectIpeOutputPort;
    m_pipelineDescriptor.pNodes[CONFIG_INDEX].nodeAllPorts.pOutputPorts[CONFIG_INDEX].portId = selectIpeOutputPort;
    selectTargetCreateDescriptor.sinkTarget.pTargetPortDesc[CONFIG_INDEX].pNodePort->nodePortId = selectIpeOutputPort;

    // Setup configurable output buffer
    UINT32 outputBufferIndex = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = selectIpeOutputPort;
    m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::CONFIG_OUTPUT];

    if (type == PipelineType::OfflineIPEGeneric2StreamDisplay)
    {
        // Setup static output buffer
        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = ipeportid_t::IPEOutputPortDisplay;
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IPEOutputPortDisplay];
    }

    if (streamIdMap.find(StreamUsecases::CONFIG_INPUT) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for CONFIG_INPUT");
        return CDKResultENoSuch;
    }

    IpePortId selectIpeInputPort;
    CHISTREAMFORMAT selectInputFormat = streamIdMap[StreamUsecases::CONFIG_INPUT]->format;

    // Set the default input port based on format
    switch (selectInputFormat)
    {
    case ChiStreamFormatYCrCb420_SP:
    case ChiStreamFormatYCbCr420_888:
    case ChiStreamFormatImplDefined:
    case ChiStreamFormatUBWCTP10:
    case ChiStreamFormatUBWCNV12:
    case ChiStreamFormatP010:
        selectIpeInputPort = ipeportid_t::IPEInputPortFull;
        break;
    // Set output port to IPEInputPortFull for unknown formats
    case ChiStreamFormatNV12HEIF:
    case ChiStreamFormatRaw16:
    case ChiStreamFormatRawOpaque:
    case ChiStreamFormatRaw10:
    case ChiStreamFormatRaw64:
    case ChiStreamFormatPD10:
    case ChiStreamFormatBlob:
    case ChiStreamFormatY8:
    case ChiStreamFormatY16:
        selectIpeInputPort = ipeportid_t::IPEInputPortFull;
        NT_LOG_WARN( "Input port is unknown for CHISTREAMFORMAT %d on IPE generic pipeline. "
            "Setting to default output port %d...", selectInputFormat, selectIpeInputPort);
        break;
    default:
        selectIpeInputPort = ipeportid_t::IPEInputPortFull;
        NT_LOG_WARN( "Unknown format %d. Setting to default input port %d...", selectInputFormat, selectIpeInputPort);
        break;
    }
    NT_LOG_INFO( "Default input port for format %d is [%d]", selectInputFormat, selectIpeInputPort);

    // If user provided an input port, override the default from format
    IpePortId overrideIpeInputPort = static_cast<IpePortId>(CmdLineParser::GetInputPort());
    if (IpePortId::IPEPortInvalid != overrideIpeInputPort)
    {
        selectIpeInputPort = overrideIpeInputPort;
        NT_LOG_INFO( "Overriding default input port with [%d]", overrideIpeInputPort);
    }

    // Edit the pipeline descriptor with selected input port
    m_pipelineDescriptor.pNodes[0].nodeAllPorts.pInputPorts[0].portId = selectIpeInputPort;
    selectTargetCreateDescriptor.sourceTarget.pTargetPortDesc[0].pNodePort->nodePortId = selectIpeInputPort;

    // Setup input buffer
    m_pipelineInputBuffer.size = sizeof(CHIPORTBUFFERDESCRIPTOR);
    m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::IPE;
    m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
    m_pipelineInputBuffer.pNodePort->nodePortId = selectIpeInputPort;
    m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::CONFIG_INPUT];

    m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::IPE;
    m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
    m_pipelineInputBufferRequirements.nodePort.nodePortId = selectIpeInputPort;

    m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
    m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
    m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
    m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
    m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
    m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
    m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);

    return CDKResultSuccess;
}

/**************************************************************************************************
*   PipelineUtils::SetupOfflineBPSGeneric
*
*   @brief
*       Setup pipeline parameters for generic BPS tests
*   @param
*       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map conatining stream objects
*       [in]  Pipeline                                type            differentiate between pipelines
*   @return
*       CDKResult result
**************************************************************************************************/
CDKResult PipelineUtils::SetupOfflineBPSGeneric(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
{
    ChiUsecase selectUsecase;
    ChiPipelineTargetCreateDescriptor selectTargetCreateDescriptor;

    // Select usecase and target create descriptor based on pipeline type
    switch (type)
    {
        case PipelineType::OfflineBPSGeneric:
            selectUsecase = Usecases2Target[UsecaseGenericId];
            selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[BPSGeneric];
            break;
        case PipelineType::OfflineBPSGeneric2Stream:
            selectUsecase = Usecases3Target[UsecaseGeneric2StreamsId];
            selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[BPSGeneric2Stream];
            break;
        default:
            NT_LOG_ERROR( "Invalid offline BPS Generic pipeline type given : %d", static_cast<int>(type));
            return CDKResultEInvalidArg;
    }

    m_pipelineDescriptor = selectTargetCreateDescriptor.pipelineCreateDesc;
    m_pipelineName = selectTargetCreateDescriptor.pPipelineName;

    if (streamIdMap.find(StreamUsecases::CONFIG_OUTPUT) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for CONFIG_OUTPUT");
        return CDKResultENoSuch;
    }

    BpsPortId selectBpsOutputPort;
    CHISTREAMFORMAT selectOutputFormat = streamIdMap[StreamUsecases::CONFIG_OUTPUT]->format;

    // Set the default output port based on format
    switch (selectOutputFormat)
    {
    case ChiStreamFormatYCrCb420_SP:
    case ChiStreamFormatYCbCr420_888:
    case ChiStreamFormatImplDefined:
    case ChiStreamFormatUBWCTP10:
    case ChiStreamFormatP010:
        selectBpsOutputPort = bpsportid_t::BPSOutputPortFull;
        break;
    case ChiStreamFormatPD10:
        selectBpsOutputPort = bpsportid_t::BPSOutputPortDS4;
        break;
    case ChiStreamFormatUBWCNV12:
    case ChiStreamFormatNV12HEIF:
        selectBpsOutputPort = bpsportid_t::BPSOutputPortReg1;
        break;
    case ChiStreamFormatBlob:
        selectBpsOutputPort = bpsportid_t::BPSOutputPortStatsBG;
        break;
    // Formats which we don't know the output port on BPS
    case ChiStreamFormatRaw16:
    case ChiStreamFormatRawOpaque:
    case ChiStreamFormatRaw10:
    case ChiStreamFormatRaw64:
    case ChiStreamFormatY8:
    case ChiStreamFormatY16:
        selectBpsOutputPort = bpsportid_t::BPSOutputPortFull;
        NT_LOG_WARN( "Output port is unknown for CHISTREAMFORMAT %d on BPS generic pipeline. "
            "Setting to default output port %d...", selectOutputFormat, selectBpsOutputPort);
        break;
    default:
        selectBpsOutputPort = bpsportid_t::BPSOutputPortFull;
        NT_LOG_WARN( "Unknown format %d. Setting to default output port %d...", selectBpsOutputPort,
            selectBpsOutputPort);
        break;
    }
    NT_LOG_INFO( "Default output port for format %d is [%d]", selectOutputFormat, selectBpsOutputPort);

    // If user provided an output port, override the default from format
    BpsPortId overrideBpsOutputPort = static_cast<BpsPortId>(CmdLineParser::GetOutputPort());
    if (BpsPortId::BPSPortInvalid != overrideBpsOutputPort)
    {
        selectBpsOutputPort = overrideBpsOutputPort;
        NT_LOG_INFO( "Overriding default output port with [%d]", overrideBpsOutputPort);
    }

    // Edit the pipeline descriptor with selected output port
    const uint32_t CONFIG_INDEX = 0;
    m_pipelineDescriptor.pLinks[CONFIG_INDEX].srcNode.nodePortId = selectBpsOutputPort;
    m_pipelineDescriptor.pNodes[CONFIG_INDEX].nodeAllPorts.pOutputPorts[CONFIG_INDEX].portId = selectBpsOutputPort;
    selectTargetCreateDescriptor.sinkTarget.pTargetPortDesc[CONFIG_INDEX].pNodePort->nodePortId = selectBpsOutputPort;

    // Setup configurable output buffer
    UINT32 outputBufferIndex = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::BPS;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = selectBpsOutputPort;
    m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::CONFIG_OUTPUT];

    if (type == PipelineType::OfflineBPSGeneric2Stream)
    {
        // Setup static output buffer
        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::BPS;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = bpsportid_t::BPSOutputPortFull;
        if (streamIdMap.find(StreamUsecases::BPSOutputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for BPSOutputPortFull");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::BPSOutputPortFull];
    }

    if (streamIdMap.find(StreamUsecases::CONFIG_INPUT) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for CONFIG_INPUT");
        return CDKResultENoSuch;
    }

    BpsPortId selectBpsInputPort;
    CHISTREAMFORMAT selectInputFormat = streamIdMap[StreamUsecases::CONFIG_INPUT]->format;

    // Set the default input port based on format
    // TODO: Update input port based on format. Using BPSInputPort for now.
    switch (selectInputFormat)
    {
    case ChiStreamFormatYCrCb420_SP:
    case ChiStreamFormatYCbCr420_888:
    case ChiStreamFormatImplDefined:
    case ChiStreamFormatUBWCTP10:
    case ChiStreamFormatUBWCNV12:
    case ChiStreamFormatP010:
    case ChiStreamFormatNV12HEIF:
    case ChiStreamFormatRaw16:
    case ChiStreamFormatRawOpaque:
    case ChiStreamFormatRaw10:
    case ChiStreamFormatRaw64:
    case ChiStreamFormatPD10:
    case ChiStreamFormatBlob:
    case ChiStreamFormatY8:
    case ChiStreamFormatY16:
        selectBpsInputPort = bpsportid_t::BPSInputPort;
        NT_LOG_WARN( "Input port is unknown for CHISTREAMFORMAT %d on BPS generic pipeline. "
            "Setting to default input port %d...", selectInputFormat, selectBpsInputPort);
        break;
    default:
        selectBpsInputPort = bpsportid_t::BPSInputPort;
        NT_LOG_WARN( "Unknown format %d. Setting to default input port %d...", selectInputFormat, selectBpsInputPort);
        break;
    }
    NT_LOG_INFO( "Default input port for format %d is [%d]", selectInputFormat, selectBpsInputPort);

    // If user provided an input port, override the default from format
    BpsPortId overrideBpsInputPort = static_cast<BpsPortId>(CmdLineParser::GetInputPort());
    if (BpsPortId::BPSPortInvalid != overrideBpsInputPort)
    {
        selectBpsInputPort = overrideBpsInputPort;
        NT_LOG_INFO( "Overriding default input port with [%d]", overrideBpsInputPort);
    }

    // Edit the pipeline descriptor with selected input port
    m_pipelineDescriptor.pNodes[0].nodeAllPorts.pInputPorts[0].portId = selectBpsInputPort;
    selectTargetCreateDescriptor.sourceTarget.pTargetPortDesc[0].pNodePort->nodePortId = selectBpsInputPort;

    // Setup input buffer
    m_pipelineInputBuffer.size = sizeof(CHIPORTBUFFERDESCRIPTOR);
    m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::BPS;
    m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
    m_pipelineInputBuffer.pNodePort->nodePortId = selectBpsInputPort;
    m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::CONFIG_INPUT];

    m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::BPS;
    m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
    m_pipelineInputBufferRequirements.nodePort.nodePortId = selectBpsInputPort;

    m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
    m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
    m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
    m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
    m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
    m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
    m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);

    return CDKResultSuccess;
}

/**************************************************************************************************
*   PipelineUtils::SetupOfflineBPSDownscaleGeneric
*
*   @brief
*       Setup pipeline parameters for generic BPS downscale tests
*   @param
*       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map conatining stream objects
*       [in]  Pipeline                                type            differentiate between pipelines
*   @return
*       CDKResult result
**************************************************************************************************/
CDKResult PipelineUtils::SetupOfflineBPSDownscaleGeneric(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
{
    NT_UNUSED_PARAM(type);

    ChiUsecase selectUsecase;
    ChiPipelineTargetCreateDescriptor selectTargetCreateDescriptor;

    selectUsecase = Usecases2Target[UsecaseGenericDownscaleId];
    selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[BPSDownscaleGeneric];

    m_pipelineDescriptor = selectTargetCreateDescriptor.pipelineCreateDesc;
    m_pipelineName = selectTargetCreateDescriptor.pPipelineName;

    // Setup full output buffer
    UINT32 outputBufferIndex = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::BPS;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = BpsPortId::BPSOutputPortFull;
    if (streamIdMap.find(StreamUsecases::CONFIG_OUTPUT) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for CONFIG_OUTPUT");
        return CDKResultENoSuch;
    }
    m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::CONFIG_OUTPUT];

    // Setup DS4 output buffer
    outputBufferIndex++;
    m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::BPS;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = BpsPortId::BPSOutputPortDS4;
    if (streamIdMap.find(StreamUsecases::BPSOutputPortDS4) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for BPSOutputPortDS4");
        return CDKResultENoSuch;
    }
    m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::BPSOutputPortDS4];

    // Setup DS16 output buffer
    outputBufferIndex++;
    m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::BPS;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = BpsPortId::BPSOutputPortDS16;
    if (streamIdMap.find(StreamUsecases::BPSOutputPortDS16) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for BPSOutputPortDS16");
        return CDKResultENoSuch;
    }
    m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::BPSOutputPortDS16];

    // Setup DS64 output buffer
    outputBufferIndex++;
    m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::BPS;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
    m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = BpsPortId::BPSOutputPortDS64;
    if (streamIdMap.find(StreamUsecases::BPSOutputPortDS64) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for BPSOutputPortDS64");
        return CDKResultENoSuch;
    }
    m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::BPSOutputPortDS64];

    // Setup input buffer requirements
    m_pipelineInputBuffer.size = sizeof(m_pipelineInputBuffer);
    m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::BPS;
    m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
    m_pipelineInputBuffer.pNodePort->nodePortId = bpsportid_t::BPSInputPort;
    if (streamIdMap.find(StreamUsecases::CONFIG_INPUT) == streamIdMap.end())
    {
        NT_LOG_ERROR( "Cannot find chistream for CONFIG_INPUT");
        return CDKResultENoSuch;
    }
    m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::CONFIG_INPUT];

    m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::BPS;
    m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
    m_pipelineInputBufferRequirements.nodePort.nodePortId = bpsportid_t::BPSInputPort;

    m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
    m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
    m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
    m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
    m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
    m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
    m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);

    return CDKResultSuccess;
}

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimeTFEGeneric
    *
    *   @brief
    *       Setup pipeline parameters for generic TFE tests
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map conatining stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimeTFEGeneric(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        ChiUsecase selectUsecase;
        ChiPipelineTargetCreateDescriptor selectTargetCreateDescriptor;

        // Select usecase and target create descriptor based on pipeline type
        switch (type)
        {
        case PipelineType::RealtimeTFEGenericTestgen:
            selectUsecase = Usecases2Target[UsecaseMimasGenericId];
            selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[TFEGenericTestgen];
            break;
        case PipelineType::RealtimeTFEGeneric2StreamTestgen:
            selectUsecase = Usecases3Target[UsecaseMimasGeneric2StreamsId];
            selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[TFEGeneric2StreamTestgen];
            break;
        default:
            NT_LOG_ERROR( "Invalid Realtime TFE Generic pipeline type given : %d", static_cast<int>(type));
            return CDKResultEInvalidArg;
        }

        m_pipelineDescriptor = selectTargetCreateDescriptor.pipelineCreateDesc;
        m_pipelineName = selectTargetCreateDescriptor.pPipelineName;

        if (streamIdMap.find(StreamUsecases::CONFIG_OUTPUT) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for CONFIG_OUTPUT");
            return CDKResultENoSuch;
        }

        TfePortId selectTfePort;
        CHISTREAMFORMAT selectFormat = streamIdMap[StreamUsecases::CONFIG_OUTPUT]->format;

        // Set the default output port based on format
        switch (selectFormat)
        {
        case ChiStreamFormatYCrCb420_SP:
        case ChiStreamFormatYCbCr420_888:
        case ChiStreamFormatImplDefined:
        case ChiStreamFormatUBWCTP10:
        case ChiStreamFormatUBWCNV12:
        case ChiStreamFormatP010:
        case ChiStreamFormatNV12HEIF:
            selectTfePort = tfeportid_t::TFEOutputPortFull;
            break;
        case ChiStreamFormatRaw16:
        case ChiStreamFormatRawOpaque:
        case ChiStreamFormatRaw10:
        case ChiStreamFormatRaw64:
            selectTfePort = tfeportid_t::TFEOutputPortRDI0;
            break;
        case ChiStreamFormatBlob:
            selectTfePort = tfeportid_t::TFEOutputPortStatsBAF;
            break;
            // Formats which we don't know the output port on TFE
        case ChiStreamFormatPD10:
        case ChiStreamFormatY8:
        case ChiStreamFormatY16:
            selectTfePort = tfeportid_t::TFEOutputPortFull;
            NT_LOG_WARN( "Output port is unknown for CHISTREAMFORMAT %d on TFE generic pipeline. "
                "Setting to default output port %d...", selectFormat, selectTfePort);
            break;
        default:
            selectTfePort = tfeportid_t::TFEOutputPortFull;
            NT_LOG_WARN( "Unknown format %d. Setting to default output port %d...", selectFormat, selectTfePort);
            break;
        }
        NT_LOG_INFO( "Default output port for format %d is [%d]", selectFormat, selectTfePort);

        // If user provided an output port, override the default from format
        TfePortId overrideTfePort = static_cast<TfePortId>(CmdLineParser::GetOutputPort());
        if (TfePortId::TFEPortInvalid != overrideTfePort)
        {
            selectTfePort = overrideTfePort;
            NT_LOG_INFO( "Overriding default output port with [%d]", overrideTfePort);
        }

        // Edit the pipeline descriptor with selected output port
        const uint32_t CONFIG_INDEX = 0;
        m_pipelineDescriptor.pLinks[CONFIG_INDEX].srcNode.nodePortId = selectTfePort;
        m_pipelineDescriptor.pNodes[CONFIG_INDEX].nodeAllPorts.pOutputPorts[CONFIG_INDEX].portId = selectTfePort;
        selectTargetCreateDescriptor.sinkTarget.pTargetPortDesc[CONFIG_INDEX].pNodePort->nodePortId = selectTfePort;

        // Setup configurable output buffer
        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::TFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = selectTfePort;
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::CONFIG_OUTPUT];

        if (type == PipelineType::RealtimeTFEGeneric2StreamTestgen)
        {
            // Setup static full output buffer
            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::TFE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = tfeportid_t::TFEOutputPortFull;
            if (streamIdMap.find(StreamUsecases::TFEOutputPortFull) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for TFEOutputPortFull");
                return CDKResultENoSuch;
            }
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::TFEOutputPortFull];
        }
        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePipelineCVP
    *
    *   @brief
    *       Setup pipeline parameters for CVP Node DME and DME+ICA tests
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map conatining stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePipelineCVP(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        IfePortId selectIfePort;
        UINT32 outputBufferIndex = 0;
        switch (type)
        {
        case PipelineType::RealtimeCVPDME:
        case PipelineType::RealtimeCVPDMEICA:
            if (streamIdMap.find(StreamUsecases::IFEOutputPortFull) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortFull");
                return CDKResultENoSuch;
            }
            if (type == PipelineType::RealtimeCVPDME)
            {
                m_pipelineDescriptor = Usecases1Target[TestCVPNodeId].pPipelineTargetCreateDesc[RealtimeCVPDME].pipelineCreateDesc;
                m_pipelineName = Usecases1Target[TestCVPNodeId].pPipelineTargetCreateDesc[RealtimeCVPDME].pPipelineName;
            }
            else
            {
                m_pipelineDescriptor = Usecases1Target[TestCVPNodeId].pPipelineTargetCreateDesc[RealtimeCVPDMEICA].pipelineCreateDesc;
                m_pipelineName = Usecases1Target[TestCVPNodeId].pPipelineTargetCreateDesc[RealtimeCVPDMEICA].pPipelineName;
            }
            selectIfePort = ifeportid_t::IFEOutputPortFull;
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortFull];
            break;
        case PipelineType::RealtimeCVPDMEDisplayPort:
            if (streamIdMap.find(StreamUsecases::IFEOutputPortDisplayFull) == streamIdMap.end())
            {
                NT_LOG_ERROR( "Cannot find chistream for IFEOutputPortDisplayFull");
                return CDKResultENoSuch;
            }
            m_pipelineDescriptor = Usecases1Target[TestCVPNodeId].pPipelineTargetCreateDesc[RealtimeCVPDMEDisplayPort].pipelineCreateDesc;
            m_pipelineName = Usecases1Target[TestCVPNodeId].pPipelineTargetCreateDesc[RealtimeCVPDMEDisplayPort].pPipelineName;
            selectIfePort = ifeportid_t::IFEOutputPortDisplayFull;
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::IFEOutputPortDisplayFull];
            break;
        default:
            NT_LOG_ERROR( "Invalid Realtime CVP pipeline type given : %d", static_cast<int>(type));
            return CDKResultEInvalidArg;
        }

        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::IFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = selectIfePort;

        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupOfflineOPEGeneric
    *
    *   @brief
    *       Setup pipeline parameters for generic OPE tests
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *       [in]  Pipeline                                type            differentiate between pipelines
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupOfflineOPEGeneric(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        ChiUsecase selectUsecase;
        ChiPipelineTargetCreateDescriptor selectTargetCreateDescriptor;

        switch (type)
        {
        case PipelineType::OfflineOPEGeneric:
            selectUsecase = Usecases2Target[UsecaseMimasGenericId];
            selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[OPEGeneric];
            break;
        case PipelineType::OfflineOPEGeneric2StreamDisplay:
            selectUsecase = Usecases3Target[UsecaseMimasGeneric2StreamsId];
            selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[OPEGeneric2StreamDisplay];
            break;
        case PipelineType::OfflineOPEGeneric3StreamDisplayStats:
            selectUsecase = Usecases3Target[UsecaseMimasGeneric2StreamsId];
            selectTargetCreateDescriptor = selectUsecase.pPipelineTargetCreateDesc[OPEGeneric3StreamDisplayStats];
            break;
        default:
            break;
        }

        m_pipelineDescriptor = selectTargetCreateDescriptor.pipelineCreateDesc;
        m_pipelineName = selectTargetCreateDescriptor.pPipelineName;

        if (streamIdMap.find(StreamUsecases::CONFIG_OUTPUT) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for CONFIG_OUTPUT");
            return CDKResultENoSuch;
        }

        OpePortId selectOpeOutputPort;
        CHISTREAMFORMAT selectOutputFormat = streamIdMap[StreamUsecases::CONFIG_OUTPUT]->format;

        // Set the default output port based on format
        // TODO: Add appropriate outputport for each formats
        switch (selectOutputFormat)
        {
        case ChiStreamFormatYCrCb420_SP:
        case ChiStreamFormatYCbCr420_888:
        case ChiStreamFormatImplDefined:
        case ChiStreamFormatUBWCTP10:
        case ChiStreamFormatUBWCNV12:
        case ChiStreamFormatP010:
            selectOpeOutputPort = opeportid_t::OPEOutputPortVideo;
            break;
        case ChiStreamFormatBlob:
            selectOpeOutputPort = opeportid_t::OPEOutputPortStatsRS;
            break;
            // Set output port to OPEOutputPortVideo for unknown formats
        case ChiStreamFormatNV12HEIF:
        case ChiStreamFormatRaw16:
        case ChiStreamFormatRawOpaque:
        case ChiStreamFormatRaw10:
        case ChiStreamFormatRaw64:
        case ChiStreamFormatPD10:
        case ChiStreamFormatY8:
        case ChiStreamFormatY16:
            selectOpeOutputPort = opeportid_t::OPEOutputPortVideo;
            NT_LOG_WARN( "Output port is unknown for CHISTREAMFORMAT %d on OPE generic pipeline. "
                "Setting to default output port %d...", selectOutputFormat, selectOpeOutputPort);
            break;
        default:
            selectOpeOutputPort = opeportid_t::OPEOutputPortVideo;
            NT_LOG_WARN( "Unknown format %d. Setting to default output port %d...", selectOutputFormat, selectOpeOutputPort);
            break;
        }
        NT_LOG_INFO( "Default output port for format %d is [%d]", selectOutputFormat, selectOpeOutputPort);

        // If user provided an output port, override the default from format
        OpePortId overrideOpeOutputPort = static_cast<OpePortId>(CmdLineParser::GetOutputPort());
        if (OpePortId::OPEPortInvalid != overrideOpeOutputPort)
        {
            selectOpeOutputPort = overrideOpeOutputPort;
            NT_LOG_INFO( "Overriding default output port with [%d]", overrideOpeOutputPort);
        }

        // Edit the pipeline descriptor with selected output port
        const uint32_t CONFIG_INDEX = 0;
        m_pipelineDescriptor.pLinks[CONFIG_INDEX].srcNode.nodePortId = selectOpeOutputPort;
        m_pipelineDescriptor.pNodes[CONFIG_INDEX].nodeAllPorts.pOutputPorts[CONFIG_INDEX].portId = selectOpeOutputPort;
        selectTargetCreateDescriptor.sinkTarget.pTargetPortDesc[CONFIG_INDEX].pNodePort->nodePortId = selectOpeOutputPort;

        // Setup configurable output buffer
        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::OPE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = selectOpeOutputPort;
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::CONFIG_OUTPUT];

        if (type == PipelineType::OfflineOPEGeneric3StreamDisplayStats)
        {
            // Setup static output buffer
            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::OPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = opeportid_t::OPEOutputPortVideo;
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::OPEOutputPortVideo];
        }

        if (type == PipelineType::OfflineOPEGeneric2StreamDisplay || type == PipelineType::OfflineOPEGeneric3StreamDisplayStats)
        {
            // Setup static output buffer
            outputBufferIndex++;
            m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(CHIPORTBUFFERDESCRIPTOR);
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::OPE;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
            m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = opeportid_t::OPEOutputPortDisplay;
            m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::OPEOutputPortDisplay];
        }

        if (streamIdMap.find(StreamUsecases::CONFIG_INPUT) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for CONFIG_INPUT");
            return CDKResultENoSuch;
        }

        OpePortId selectOpeInputPort;
        CHISTREAMFORMAT selectInputFormat = streamIdMap[StreamUsecases::CONFIG_INPUT]->format;

        // Set the default input port based on format
        switch (selectInputFormat)
        {
        case ChiStreamFormatYCrCb420_SP:
        case ChiStreamFormatYCbCr420_888:
        case ChiStreamFormatImplDefined:
        case ChiStreamFormatUBWCTP10:
        case ChiStreamFormatUBWCNV12:
        case ChiStreamFormatP010:
        case ChiStreamFormatNV12HEIF:
        case ChiStreamFormatRaw16:
        case ChiStreamFormatRawOpaque:
        case ChiStreamFormatRaw10:
        case ChiStreamFormatRaw64:
        case ChiStreamFormatPD10:
        case ChiStreamFormatBlob:
        case ChiStreamFormatY8:
        case ChiStreamFormatY16:
            selectOpeInputPort = opeportid_t::OPEInputPortFull;
            break;
        default:
            selectOpeInputPort = opeportid_t::OPEInputPortFull;
            NT_LOG_WARN( "Unknown format %d. Setting to default input port %d...", selectInputFormat, selectOpeInputPort);
            break;
        }
        NT_LOG_INFO( "Default input port for format %d is [%d]", selectInputFormat, selectOpeInputPort);

        // If user provided an input port, override the default from format
        OpePortId overrideOpeInputPort = static_cast<OpePortId>(CmdLineParser::GetInputPort());
        if (OpePortId::OPEPortInvalid != overrideOpeInputPort)
        {
            selectOpeInputPort = overrideOpeInputPort;
            NT_LOG_INFO( "Overriding default input port with [%d]", overrideOpeInputPort);
        }

        // Edit the pipeline descriptor with selected input port
        m_pipelineDescriptor.pNodes[0].nodeAllPorts.pInputPorts[0].portId = selectOpeInputPort;
        selectTargetCreateDescriptor.sourceTarget.pTargetPortDesc[0].pNodePort->nodePortId = selectOpeInputPort;

        // Setup input buffer
        m_pipelineInputBuffer.size = sizeof(CHIPORTBUFFERDESCRIPTOR);
        m_pipelineInputBuffer.pNodePort->nodeId = nodeid_t::OPE;
        m_pipelineInputBuffer.pNodePort->nodeInstanceId = 0;
        m_pipelineInputBuffer.pNodePort->nodePortId = selectOpeInputPort;
        m_pipelineInputBuffer.pStream = streamIdMap[StreamUsecases::CONFIG_INPUT];

        m_pipelineInputBufferRequirements.nodePort.nodeId = nodeid_t::OPE;
        m_pipelineInputBufferRequirements.nodePort.nodeInstanceId = 0;
        m_pipelineInputBufferRequirements.nodePort.nodePortId = selectOpeInputPort;

        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.width = 3840;
        m_pipelineInputBufferRequirements.bufferOptions.maxDimension.height = 2160;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.width = 0;
        m_pipelineInputBufferRequirements.bufferOptions.minDimension.height = 0;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.width = 1920;
        m_pipelineInputBufferRequirements.bufferOptions.optimalDimension.height = 1080;
        m_pipelineInputBufferRequirements.bufferOptions.size = sizeof(CHIBUFFEROPTIONS);

        return CDKResultSuccess;
    }

    /**************************************************************************************************
    *   PipelineUtils::SetupRealtimePipelineTFEStats
    *
    *   @brief
    *       Setup Pipeline parameters for real time tfe usecase with all stats ports with testgen(no sensor node)
    *   @param
    *       [in]  std::map<StreamUsecases, ChiStream*>    streamIdMap     Map containing stream objects
    *   @return
    *       CDKResult result
    **************************************************************************************************/
    CDKResult PipelineUtils::SetupRealtimePipelineTFEStats(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type)
    {
        if (type == PipelineType::RealtimeTFEStatsTestgen)
        {
            m_pipelineDescriptor = Usecases6Target[TestTFEFullStatsTestgenId].pPipelineTargetCreateDesc[TfeFullStatsTestgen].pipelineCreateDesc;
            m_pipelineName = Usecases6Target[TestTFEFullStatsTestgenId].pPipelineTargetCreateDesc[TfeFullStatsTestgen].pPipelineName;
        }

        UINT32 outputBufferIndex = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::TFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = tfeportid_t::TFEOutputPortFull;
        if (streamIdMap.find(StreamUsecases::TFEOutputPortFull) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for TFEOutputPortFull");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::TFEOutputPortFull];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::TFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = tfeportid_t::TFEOutputPortStatsAECBG;
        if (streamIdMap.find(StreamUsecases::TFEOutputPortStatsAECBG) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for TFEOutputPortStatsAECBG");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::TFEOutputPortStatsAECBG];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::TFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = tfeportid_t::TFEOutputPortStatsBHIST;
        if (streamIdMap.find(StreamUsecases::TFEOutputPortStatsBHIST) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for TFEOutputPortStatsBHIST");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::TFEOutputPortStatsBHIST];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::TFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = tfeportid_t::TFEOutputPortStatsTLBG;
        if (streamIdMap.find(StreamUsecases::TFEOutputPortStatsTLBG) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for TFEOutputPortStatsTLBG");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::TFEOutputPortStatsTLBG];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::TFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = tfeportid_t::TFEOutputPortStatsBAF;
        if (streamIdMap.find(StreamUsecases::TFEOutputPortStatsBAF) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for TFEOutputPortStatsBAF");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::TFEOutputPortStatsBAF];

        outputBufferIndex++;
        m_pPipelineOutputBuffer[outputBufferIndex].size = sizeof(m_pPipelineOutputBuffer);
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeId = nodeid_t::TFE;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodeInstanceId = 0;
        m_pPipelineOutputBuffer[outputBufferIndex].pNodePort->nodePortId = tfeportid_t::TFEOutputPortStatsAWBBG;
        if (streamIdMap.find(StreamUsecases::TFEOutputPortStatsAWBBG) == streamIdMap.end())
        {
            NT_LOG_ERROR( "Cannot find chistream for TFEOutputPortStatsAWBBG");
            return CDKResultENoSuch;
        }
        m_pPipelineOutputBuffer[outputBufferIndex].pStream = streamIdMap[StreamUsecases::TFEOutputPortStatsAWBBG];

        return CDKResultSuccess;
    }

}

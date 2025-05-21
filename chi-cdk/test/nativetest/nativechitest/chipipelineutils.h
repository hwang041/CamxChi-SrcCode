//*************************************************************************************************
// Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*************************************************************************************************

#ifndef __CHI_PIPELINE_UTILS__
#define __CHI_PIPELINE_UTILS__

#include "test_pipelines.h"
#include "camera3stream.h"

namespace tests {

    /// @brief PipelineType
    enum class PipelineType
    {
        RealtimeIFE = 0,
        RealtimeIFE3A,
        RealTimeIPE,
        RealtimeIFETestGen,
        RealtimeIPETestGen,
        RealtimeIFEGeneric,
        RealtimeIFEGenericTestgen,
        RealtimeIFEGeneric2Stream,
        RealtimeIFEDownscaleGenericTestgen,
        RealtimeIFEGeneric2StreamTestgen,
        RealtimeIFEGeneric2StreamDisplay,
        RealtimeIFEGeneric2StreamDisplayTestgen,
        RealtimeIFEStatsTestGen,
        RealtimeIFEStats,
        RealtimeIFERDI0,
        RealtimeIFERDI0TestGen,
        RealtimeIFERawCamif,
        RealtimeIFERawLsc,
        RealtimeChiDepth,
        RealtimeLRME_RANSAC,
        RealtimeBypassNode,
        RealtimeInplaceNode,
        OfflineBPS,
        OfflineBPSGeneric,
        OfflineBPSGeneric2Stream,
        OfflineBPSDS4,
        OfflineIPEJPEG,
        OfflineIPEDisp,
        OfflineIPEVideo,
        OfflineIPEDispVideo,
        OfflineIPEGeneric,
        OfflineIPEGeneric2StreamDisplay,
        OfflineBPSIPE,
        OfflineBPSIPEJpeg,
        OfflineBPSIPEDispVideo,
        OfflineBPSStats,
        OfflineBPSStatsWithIPE,
        OfflineBPSBGStatsWithIPE,
        OfflineBPSHistStatsWithIPE,
        OfflineBPSDownscaleGeneric,
        RealtimePrevRDI,
        PrevRDIwithTestGen,
        RealtimePrevRDIWithStats,
        RealtimePrevWithCallbackAndRDIWithStats,
        RealtimePrevWithCallbackWithStats,
        RealtimePrevWith3AWrappers,
        RealtimePrevAndVideoWithStats,
        RealtimePrevWithMemcpy,
        RealtimePrevFromMemcpy,
        RealtimePrevHVX,
        OfflineZSlSnap,
        OfflineZSlSnapWithDSports,
        OfflineZSlSnapAndThumbnailWithDSports,
        VendorTagWrite,
        OfflineJpegSnapshot,
        OfflineBPSGPUpipeline,
        OfflineFDPipeline,
        OfflineBPSWithIPEAndDS,
        RealtimeIPEATestgen,
        RealtimeIPE3ATestgen,
        RealtimeIPEABTestgen,
        RealtimeIPEABStatsTestgen,
        RealtimeIPEABCStatsTestgen,
        RealtimeIPEABCStats,
        RealtimeIPEAStatsRDI,
        RealtimeIPEACStatsRDI,
        RealtimeIPEABCStatsRDI,
        RealtimeRDI1Only,
        RealtimeStats3A,
        RealtimeIPEJpeg,
        RealtimeBPSIPEJpeg,
        RealtimeFD,
        OfflineExtBPSIPE,
        OfflineExtBPSIPEJPEG,
        OfflineDepthNode,
        OfflineChiGPUNode,
        RealtimeTFEGenericTestgen,
        OfflineOPEGeneric,
        RealtimeTFEGeneric2StreamTestgen,
        RealtimeTFEStatsTestgen,
        OfflineOPEGeneric2StreamDisplay,
        OfflineOPEGeneric3StreamDisplayStats,
        RealtimeCVPDME,
        RealtimeCVPDMEDisplayPort,
        RealtimeCVPDMEICA
    };

    class PipelineUtils
    {
    public:
        PipelineUtils() = default;
        ~PipelineUtils() = default;

        CDKResult SetupPipeline(
            std::map<StreamUsecases, ChiStream*> streamIdMap,
            PipelineCreateData* pPipelineCreate,
            PipelineType type);

        void InitializePortBufferDescriptor(PipelineCreateData* pPipelineCreate);
        void DestroyNodePorts(PipelineCreateData* pPipelineCreate);

    private:

        /// @brief Nodeid
        typedef enum NodeId
        {
            Sensor           = 0,
            StatsProcessing  = 1,
            JPEGAggregator   = 6,
            FDManager        = 8,
            StatsParse       = 9,
            AutoWhiteBalance = 12,
            External         = 255,
            IFE              = 65536,
            JPEG,
            IPE,
            BPS,
            FDHw,
            CVP              = 65543,
            TFE              = 65544,
            OPE,
        }nodeid_t;

        /// @brief Sensor ports
        typedef enum SensorPortId
        {
            SensorOutputPort0 =0
        }sensorportid_t;

        /// @brief IfePorts
        typedef enum IfePortId
        {
            IFEPortInvalid             = -1,
            IFEOutputPortFull          = 0,
            IFEOutputPortDS4           = 1,
            IFEOutputPortDS16          = 2,
            IFEOutputPortCAMIFRaw      = 3,
            IFEOutputPortLSCRaw        = 4,
            IFEOutputPortGTMRaw        = 5,
            IFEOutputPortFD            = 6,
            IFEOutputPortPDAF          = 7,
            IFEOutputPortRDI0          = 8,
            IFEOutputPortRDI1          = 9,
            IFEOutputPortRDI2          = 10,
            IFEOutputPortRDI3          = 11,
            IFEOutputPortStatsRS       = 12,
            IFEOutputPortStatsCS       = 13,
            IFEOutputPortStatsIHIST    = 15,
            IFEOutputPortStatsBHIST    = 16,
            IFEOutputPortStatsHDRBE    = 17,
            IFEOutputPortStatsHDRBHIST = 18,
            IFEOutputPortStatsTLBG     = 19,
            IFEOutputPortStatsBF       = 20,
            IFEOutputPortStatsAWBBG    = 21,
            IFEOutputPortDisplayFull   = 22,
            IFEOutputPortDisplayDS4    = 23,
            IFEOutputPortDisplayDS16   = 24,
            IFEOutputPortStatsDualPD   = 25,

            IFEInputPortCSIDTPG        = 0,
            IFEInputPortCAMIFTPG       = 1,
            IFEInputPortSensor         = 2,
            IFEInputPortRDI0           = 3,
            IFEInputPortRDI1           = 4,
            IFEInputPortRDI2           = 5,
            IFEInputPortDualPD         = 6
        }ifeportid_t;

        /// @brief IpePorts
        typedef enum IpePortId
        {
            IPEPortInvalid = -1,
            IPEInputPortFull = 0,
            IPEInputPortDS4,
            IPEInputPortDS16,
            IPEInputPortDS64,
            IPEInputPortFullRef,
            IPEInputPortDS4Ref,
            IPEInputPortDS16Ref,
            IPEInputPortDS64Ref,
            IPEOutputPortDisplay,
            IPEOutputPortVideo,
            IPEOutputPortFullRef,
            IPEOutputPortDS4Ref,
            IPEOutputPortDS16Ref,
            IPEOutputPortDS64Ref
        }ipeportid_t;

        /// @brief BpsPorts
        typedef enum BpsPortId
        {
            BPSPortInvalid = -1,
            BPSInputPort = 0,
            BPSOutputPortFull,
            BPSOutputPortDS4,
            BPSOutputPortDS16,
            BPSOutputPortDS64,
            BPSOutputPortStatsBG,
            BPSOutputPortStatsBHist,
            BPSOutputPortReg1,
            BPSOutputPortReg2
        }bpsportid_t;

        /// @brief GpuPorts
        typedef enum GPUPortId
        {
            GPUInputPort = 0,
            GPUOutputPortFull = 0,
            GPUOutputPortDS4,
            GPUOutputPortDS16,
            GPUOutputPortDS64,
        }gpuportid_t;

        /// @brief CVPPorts
        typedef enum CVPPortId
        {
            CVPInstanceName0       = 0,
            CVPOutputPortVector    = 0,
            CVPOutputPortData      = 1,
            CVPOutputPortImage     = 2,
            CVPMaxOutputPorts      = 3,
            CVPInputPortTARIFEFull = 3,
            CVPInputPortREFIFEFull = 4,
            CVPInputPortTARIFEDS4  = 5,
            CVPInputPortREFIFEDS4  = 6,
            CVPInputPortTARIFEDS16 = 7,
            CVPInputPortREFIFEDS16 = 8,
            CVPInputPortData       = 9,
            CVPMaxInputPorts       = 9,
        }cvpportid_t;

        /// @brief JpegPorts
        typedef enum JpegAggPortId
        {
            JPEGAggregatorInputPort0 = 0,
            JPEGAggregatorInputPort1 = 1,
            JPEGAggregatorOutputPort = 2

        }jpegaggportid_t;

        /// @brief JpegPorts
        typedef enum JpegPortId
        {
            JPEGInputPort = 0,
            JPEGOutputPort

        }jpegportid_t;

        /// @brief FDHw
        typedef enum FDHwPortId
        {
            FDHwInputPortImage = 0,

        }fdhwportid_t;

        /// @brief FD manager
        typedef enum FDMgrPortId
        {
            FDManagerInputPort = 0,
            FDManagerOutputPort = 0

        }fdmgrportid_t;

        /// @brief TfePorts
        typedef enum TfePortId
        {
            TFEPortInvalid              = -1,
            TFEInputPortCSIDTPG         = 0,
            TFEInputPortCAMIFTPG        = 1,
            TFEInputPortSensor          = 2,
            TFEInputPortRDI0            = 3,
            TFEInputPortRDI1            = 4,

            TFEOutputPortFull           = 1,
            TFEOutputPortIdealRaw       = 2,
            TFEOutputPortPDAF           = 3,
            TFEOutputPortRDI0           = 4,
            TFEOutputPortRDI1           = 5,
            TFEOutputPortRDI2           = 6,
            TFEOutputPortStatsAECBG     = 7,
            TFEOutputPortStatsBHIST     = 8,
            TFEOutputPortStatsTLBG      = 9,
            TFEOutputPortStatsBAF       = 10,
            TFEOutputPortStatsAWBBG     = 11
        }tfeportid_t;

        /// @brief OpePorts
        typedef enum OpePortId
        {
            OPEPortInvalid              = -1,
            OPEInputPortFull            = 1,

            OPEOutputPortVideo          = 1,
            OPEOutputPortDisplay        = 2,
            OPEOutputPortARGB           = 3,
            OPEOutputPortStatsRS        = 4,
            OPEOutputPortStatsIHIST     = 5,
            OPEOutputPortStatsLTMDC     = 6
        }opeportid_t;

        /// @brief ChiExternalNode
        typedef enum ExternalNodeId
        {
            ChiNodeInputPort0  = 0,
            ChiNodeOutputPort0 = 0,
            ChiNodeOutputPort1
        }externalportid_t;

        static const UINT MAX_NODES = 20;
        static const UINT MAX_NODE_PORTS = 20;
        static const UINT MAX_LINKS = 20;
        static const UINT MAX_PORTS = 20;
        static const UINT MAX_OUTPUT_BUFFERS = 11;


        CHIPIPELINECREATEDESCRIPTOR  m_pipelineDescriptor;
        CHINODE                      m_nodes[MAX_NODES];
        CHINODEPORTS                 m_ports[MAX_NODE_PORTS];
        CHINODELINK                  m_links[MAX_LINKS];
        CHIINPUTPORTDESCRIPTOR       m_inputPorts[MAX_PORTS];
        CHIOUTPUTPORTDESCRIPTOR      m_outputPorts[MAX_PORTS];
        CHILINKNODEDESCRIPTOR        m_linkNodeDescriptors[MAX_LINKS];
        CHIPORTBUFFERDESCRIPTOR      m_pPipelineOutputBuffer[MAX_OUTPUT_BUFFERS];
        CHIPORTBUFFERDESCRIPTOR      m_pipelineInputBuffer;
        CHIPIPELINEINPUTOPTIONS      m_pipelineInputBufferRequirements;
        const CHAR*                  m_pipelineName;

    // realtime pipeline
    CDKResult SetupRealtimePipelineIPE(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupRealtimePipelineIFE(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupRealtimePipelineIFETestgen(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupRealtimePipelineIPETestgen(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupRealtimePipelineIFERDIO(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupRealtimePipelineIFERDIOTestgen(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupRealtimePipelineIFEStats(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupRealtimePipelineIFERawCamif(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupRealtimePipelineIFERawLsc(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupRealtimePipelineExternal(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupRealtimePrevRDI(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupPreviewCallbackSnapshotWithThumbnail(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupRealtimeIPEABCTestgen(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupRealtimeIPEABC(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupRealtimePIPCam(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupRealtimeFD(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupRealtimeJpeg(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupRealtimeIFEDownscaleGenericTestgen(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupRealtimeIFEGeneric(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupCustomVendorWritePipeline(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupRealtimePipelineCVP(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    // offline pipeline
    CDKResult SetupOfflinePipelineIPEJPEG(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflinePipelineIPEDisplay(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflinePipelineBPS(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflinePipelineBPSDS4(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflinePipelineIPEVideo(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflinePipelineIPEDispVideo(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflinePipelineBPSIPE(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflinePipelineBPSIPEJpeg(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflinePipelineBPSIPEDispVideo(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflineZSLSnapShot(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupOfflinePipelineBPSStats(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupOfflineJpeg(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflineBPSGPUPipeline(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflineFDPipeline(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflineDepthNode(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupOfflineBPSWithIPEAndDSPipeline(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflineChiGPUNode(std::map<StreamUsecases, ChiStream*> streamIdMap);
    CDKResult SetupOfflineChiExternalNode(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupOfflineIPEGeneric(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupOfflineBPSGeneric(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupOfflineBPSDownscaleGeneric(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);

    // MIMAS testcases
    CDKResult SetupRealtimeTFEGeneric(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupOfflineOPEGeneric(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
    CDKResult SetupRealtimePipelineTFEStats(std::map<StreamUsecases, ChiStream*> streamIdMap, PipelineType type);
};

}


#endif  //#ifndef CHI_PIPELINE_UTILS

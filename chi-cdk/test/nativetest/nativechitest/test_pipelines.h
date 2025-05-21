////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef USECASEDEFS_H
#define USECASEDEFS_H


#include "nchicommon.h"
// NOWHINE ENTIRE FILE - Temporarily bypassing for existing CHI files

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/// @brief ranges of buffer sizes supported
struct BufferDimension
{
    UINT minWidth;
    UINT minHeight;
    UINT maxWidth;
    UINT maxHeight;
};

/// @brief Collection of information describing how a buffer is used
struct ChiTarget
{
    ChiStreamType       direction;
    BufferDimension     dimension;
    UINT                numFormats;
    ChiBufferFormat*    pBufferFormats;
    ChiStream*          pChiStream;
};

/// @brief Information regarding where a port interacts with a buffer directly
struct ChiTargetPortDescriptor
{
    const CHAR*            pTargetName;
    ChiTarget*             pTarget;
    UINT                   numNodePorts;
    ChiLinkNodeDescriptor* pNodePort;
};

/// @brief List of port->buffer information
struct ChiTargetPortDescriptorInfo
{
    UINT                     numTargets;
    ChiTargetPortDescriptor* pTargetPortDesc;
};

/// @brief Combination of pipeline information with buffer information
struct ChiPipelineTargetCreateDescriptor
{
    const CHAR*                 pPipelineName;
    ChiPipelineCreateDescriptor pipelineCreateDesc;
    ChiTargetPortDescriptorInfo sinkTarget;
    ChiTargetPortDescriptorInfo sourceTarget;
};

/// @brief Collection of information summarizing a usecase
struct ChiUsecase
{
    const CHAR*                        pUsecaseName;
    UINT                               streamConfigMode;
    UINT                               numTargets;
    ChiTarget**                        ppChiTargets;
    UINT                               numPipelines;
    ChiPipelineTargetCreateDescriptor* pPipelineTargetCreateDesc;
    const PruneSettings*               pTargetPruneSettings;
    BOOL                               isOriginalDescriptor;
};

/// @brief Collection of usecases with matching properties (target count at this point)
struct ChiTargetUsecases
{
    UINT        numUsecases;
    ChiUsecase* pChiUsecases;
};

// Enumerator: VariantGroup
enum EVariantGroup
{
    InvalidVariantGroup = 0,
};
static const CHAR* g_stringMapVariantGroup[]
{
};

// Enumerator: VariantType
enum EVariantType
{
    InvalidVariantType = 0,
};
static const CHAR* g_stringMapVariantType[]
{
};

/*==================== USECASE: TestIFEFull =======================*/

static ChiBufferFormat TestIFEFull_TARGET_BUFFER_FULL_formats[] =
{
    ChiFormatYUV420NV12,
};

static ChiTarget TestIFEFull_TARGET_BUFFER_FULL_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2160
    },
    1,
    TestIFEFull_TARGET_BUFFER_FULL_formats,
    NULL
}; // TARGET_BUFFER_FULL

static ChiTarget* TestIFEFull_Targets[] =
{
	&TestIFEFull_TARGET_BUFFER_FULL_target
};

/*****************************Pipeline IfeFull***************************/

static ChiLinkNodeDescriptor TestIFEFull_IfeFull_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __0_TARGET_BUFFER_FULL_Link_NodeDescriptors[] =
{
    {65536, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestIFEFull_IfeFull_Link1_IFE0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_FULL
};

static ChiTargetPortDescriptor TestIFEFull_IfeFull_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_FULL", &TestIFEFull_TARGET_BUFFER_FULL_target, 1, __0_TARGET_BUFFER_FULL_Link_NodeDescriptors}, // TARGET_BUFFER_FULL
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestIFEFull_IfeFullNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestIFEFull_IfeFullNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIFEFull_IfeFullNode65536_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // IFEOutputPortFull
};

static ChiNode TestIFEFull_IfeFullNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestIFEFull_IfeFullNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, TestIFEFull_IfeFullNode65536_0InputPortDescriptors, 1, TestIFEFull_IfeFullNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestIFEFull_IfeFullLinks[] =
{
    {{0, 0, 0, 0}, 1, TestIFEFull_IfeFull_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestIFEFull_IfeFull_Link1_IFE0_Out0Desc, {0}, {0, 0}},
};

enum TestIFEFullPipelineIds
{
    IfeFull = 0,
};

static ChiPipelineTargetCreateDescriptor TestIFEFull_pipelines[] =
{
    {"IfeFull", { 0, 2, TestIFEFull_IfeFullNodes, 2, TestIFEFull_IfeFullLinks, 1}, {1, TestIFEFull_IfeFull_sink_TargetDescriptors}, {0, NULL}},  // IfeFull
};

/*==================== USECASE: TestIPEFull =======================*/

static ChiBufferFormat TestIPEFull_TARGET_BUFFER_PREVIEW_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget TestIPEFull_TARGET_BUFFER_PREVIEW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestIPEFull_TARGET_BUFFER_PREVIEW_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW

static ChiTarget* TestIPEFull_Targets[] =
{
	&TestIPEFull_TARGET_BUFFER_PREVIEW_target
};

/*****************************Pipeline Ipefull***************************/

static ChiLinkNodeDescriptor TestIPEFull_Ipefull_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestIPEFull_Ipefull_Link1_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __1_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestIPEFull_Ipefull_Link2_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiTargetPortDescriptor TestIPEFull_Ipefull_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestIPEFull_TARGET_BUFFER_PREVIEW_target, 1, __1_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPEFull_IpefullNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestIPEFull_IpefullNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPEFull_IpefullNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestIPEFull_IpefullNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPEFull_IpefullNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNode TestIPEFull_IpefullNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestIPEFull_IpefullNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, TestIPEFull_IpefullNode65536_0InputPortDescriptors, 1, TestIPEFull_IpefullNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestIPEFull_IpefullNode65538_0InputPortDescriptors, 1, TestIPEFull_IpefullNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestIPEFull_IpefullLinks[] =
{
    {{0, 0, 0, 0}, 1, TestIPEFull_Ipefull_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestIPEFull_Ipefull_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestIPEFull_Ipefull_Link2_IPE0_Out8Desc, {0}, {0, 0}},
};

enum TestIPEFullPipelineIds
{
    Ipefull = 0,
};

static ChiPipelineTargetCreateDescriptor TestIPEFull_pipelines[] =
{
    {"Ipefull", { 0, 3, TestIPEFull_IpefullNodes, 3, TestIPEFull_IpefullLinks, 1}, {1, TestIPEFull_Ipefull_sink_TargetDescriptors}, {0, NULL}},  // Ipefull
};

/*==================== USECASE: TestIFEFullTestgen =======================*/

static ChiBufferFormat TestIFEFullTestgen_TARGET_BUFFER_FULL_formats[] =
{
    ChiFormatYUV420NV12,
};

static ChiTarget TestIFEFullTestgen_TARGET_BUFFER_FULL_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2160
    },
    1,
    TestIFEFullTestgen_TARGET_BUFFER_FULL_formats,
    NULL
}; // TARGET_BUFFER_FULL

static ChiTarget* TestIFEFullTestgen_Targets[] =
{
	&TestIFEFullTestgen_TARGET_BUFFER_FULL_target
};

/*****************************Pipeline IfeFullTestgen***************************/

static ChiLinkNodeDescriptor __2_TARGET_BUFFER_FULL_Link_NodeDescriptors[] =
{
    {65536, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestIFEFullTestgen_IfeFullTestgen_Link0_IFE0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_FULL
};

static ChiTargetPortDescriptor TestIFEFullTestgen_IfeFullTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_FULL", &TestIFEFullTestgen_TARGET_BUFFER_FULL_target, 1, __2_TARGET_BUFFER_FULL_Link_NodeDescriptors}, // TARGET_BUFFER_FULL
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIFEFullTestgen_IfeFullTestgenNode65536_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // IFEOutputPortFull
};

static ChiNode TestIFEFullTestgen_IfeFullTestgenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 1, TestIFEFullTestgen_IfeFullTestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestIFEFullTestgen_IfeFullTestgenLinks[] =
{
    {{65536, 0, 0, 0}, 1, TestIFEFullTestgen_IfeFullTestgen_Link0_IFE0_Out0Desc, {0}, {0, 0}},
};

enum TestIFEFullTestgenPipelineIds
{
    IfeFullTestgen = 0,
};

static ChiPipelineTargetCreateDescriptor TestIFEFullTestgen_pipelines[] =
{
    {"IfeFullTestgen", { 0, 1, TestIFEFullTestgen_IfeFullTestgenNodes, 1, TestIFEFullTestgen_IfeFullTestgenLinks, 1}, {1, TestIFEFullTestgen_IfeFullTestgen_sink_TargetDescriptors}, {0, NULL}},  // IfeFullTestgen
};

/*==================== USECASE: UsecaseRaw =======================*/

static ChiBufferFormat UsecaseRaw_TARGET_BUFFER_RAW_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiTarget UsecaseRaw_TARGET_BUFFER_RAW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 5488, 4112
    },
    2,
    UsecaseRaw_TARGET_BUFFER_RAW_formats,
    NULL
}; // TARGET_BUFFER_RAW

static ChiTarget* UsecaseRaw_Targets[] =
{
	&UsecaseRaw_TARGET_BUFFER_RAW_target
};

/*****************************Pipeline RDI0***************************/

static ChiLinkNodeDescriptor UsecaseRaw_RDI0_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __3_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 8 }, 
};
static ChiLinkNodeDescriptor UsecaseRaw_RDI0_Link1_IFE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiTargetPortDescriptor UsecaseRaw_RDI0_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &UsecaseRaw_TARGET_BUFFER_RAW_target, 1, __3_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseRaw_RDI0Node0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseRaw_RDI0Node65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseRaw_RDI0Node65536_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI0
};

static ChiNode UsecaseRaw_RDI0Nodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, UsecaseRaw_RDI0Node0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, UsecaseRaw_RDI0Node65536_0InputPortDescriptors, 1, UsecaseRaw_RDI0Node65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseRaw_RDI0Links[] =
{
    {{0, 0, 0, 0}, 1, UsecaseRaw_RDI0_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 8, 0}, 1, UsecaseRaw_RDI0_Link1_IFE0_Out8Desc, {0}, {0, 0}},
};

/*****************************Pipeline RDI0Testgen***************************/

static ChiLinkNodeDescriptor __4_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 8 }, 
};
static ChiLinkNodeDescriptor UsecaseRaw_RDI0Testgen_Link0_IFE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiTargetPortDescriptor UsecaseRaw_RDI0Testgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &UsecaseRaw_TARGET_BUFFER_RAW_target, 1, __4_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseRaw_RDI0TestgenNode65536_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI0
};

static ChiNode UsecaseRaw_RDI0TestgenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 1, UsecaseRaw_RDI0TestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseRaw_RDI0TestgenLinks[] =
{
    {{65536, 0, 8, 0}, 1, UsecaseRaw_RDI0Testgen_Link0_IFE0_Out8Desc, {0}, {0, 0}},
};

/*****************************Pipeline Camif***************************/

static ChiLinkNodeDescriptor UsecaseRaw_Camif_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __5_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 3 }, 
};
static ChiLinkNodeDescriptor UsecaseRaw_Camif_Link1_IFE0_Out3Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiTargetPortDescriptor UsecaseRaw_Camif_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &UsecaseRaw_TARGET_BUFFER_RAW_target, 1, __5_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseRaw_CamifNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseRaw_CamifNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseRaw_CamifNode65536_0OutputPortDescriptors[] =
{
    {3, 1, 1, 0, 0, NULL}, // IFEOutputPortCAMIFRaw
};

static ChiNode UsecaseRaw_CamifNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, UsecaseRaw_CamifNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, UsecaseRaw_CamifNode65536_0InputPortDescriptors, 1, UsecaseRaw_CamifNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseRaw_CamifLinks[] =
{
    {{0, 0, 0, 0}, 1, UsecaseRaw_Camif_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 3, 0}, 1, UsecaseRaw_Camif_Link1_IFE0_Out3Desc, {0}, {0, 0}},
};

/*****************************Pipeline Lsc***************************/

static ChiLinkNodeDescriptor UsecaseRaw_Lsc_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __6_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 4 }, 
};
static ChiLinkNodeDescriptor UsecaseRaw_Lsc_Link1_IFE0_Out4Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiTargetPortDescriptor UsecaseRaw_Lsc_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &UsecaseRaw_TARGET_BUFFER_RAW_target, 1, __6_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseRaw_LscNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseRaw_LscNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseRaw_LscNode65536_0OutputPortDescriptors[] =
{
    {4, 1, 1, 0, 0, NULL}, // IFEOutputPortLSCRaw
};

static ChiNode UsecaseRaw_LscNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, UsecaseRaw_LscNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, UsecaseRaw_LscNode65536_0InputPortDescriptors, 1, UsecaseRaw_LscNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseRaw_LscLinks[] =
{
    {{0, 0, 0, 0}, 1, UsecaseRaw_Lsc_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 4, 0}, 1, UsecaseRaw_Lsc_Link1_IFE0_Out4Desc, {0}, {0, 0}},
};

enum UsecaseRawPipelineIds
{
    RDI0 = 0,
    RDI0Testgen = 1,
    Camif = 2,
    Lsc = 3,
};

static ChiPipelineTargetCreateDescriptor UsecaseRaw_pipelines[] =
{
    {"RDI0", { 0, 2, UsecaseRaw_RDI0Nodes, 2, UsecaseRaw_RDI0Links, 1}, {1, UsecaseRaw_RDI0_sink_TargetDescriptors}, {0, NULL}},  // RDI0
    {"RDI0Testgen", { 0, 1, UsecaseRaw_RDI0TestgenNodes, 1, UsecaseRaw_RDI0TestgenLinks, 1}, {1, UsecaseRaw_RDI0Testgen_sink_TargetDescriptors}, {0, NULL}},  // RDI0Testgen
    {"Camif", { 0, 2, UsecaseRaw_CamifNodes, 2, UsecaseRaw_CamifLinks, 1}, {1, UsecaseRaw_Camif_sink_TargetDescriptors}, {0, NULL}},  // Camif
    {"Lsc", { 0, 2, UsecaseRaw_LscNodes, 2, UsecaseRaw_LscLinks, 1}, {1, UsecaseRaw_Lsc_sink_TargetDescriptors}, {0, NULL}},  // Lsc
};

/*==================== USECASE: TestCustomNode =======================*/

static ChiBufferFormat TestCustomNode_TARGET_BUFFER_PREVIEW_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget TestCustomNode_TARGET_BUFFER_PREVIEW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestCustomNode_TARGET_BUFFER_PREVIEW_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW

static ChiTarget* TestCustomNode_Targets[] =
{
	&TestCustomNode_TARGET_BUFFER_PREVIEW_target
};

/*****************************Pipeline VendorTagWrite***************************/

static ChiLinkNodeDescriptor TestCustomNode_VendorTagWrite_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestCustomNode_VendorTagWrite_Link1_IFE0_Out0Desc[] =
{
    {255, 0, 0, 0, {0, NULL}}, // ChiExternalNode
};

static ChiLinkNodeDescriptor TestCustomNode_VendorTagWrite_Link2_ChiExternalNode0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __7_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestCustomNode_VendorTagWrite_Link3_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiTargetPortDescriptor TestCustomNode_VendorTagWrite_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestCustomNode_TARGET_BUFFER_PREVIEW_target, 1, __7_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestCustomNode_VendorTagWriteNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// ChiExternalNode0 Input Port Descriptors
static ChiInputPortDescriptor TestCustomNode_VendorTagWriteNode255_0InputPortDescriptors[] =
{
    {0, 0, 0}, // ChiNodeInputPortFull
};

// ChiExternalNode0 Output Port Descriptors
static ChiOutputPortDescriptor TestCustomNode_VendorTagWriteNode255_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // ChiNodeOutputPortFull
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestCustomNode_VendorTagWriteNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestCustomNode_VendorTagWriteNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestCustomNode_VendorTagWriteNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestCustomNode_VendorTagWriteNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNodeProperty TestCustomNode_VendorTagWrite_node255_0_properties[] =
{
    {1, "com.bots.node.vendortagwrite"},
};

static ChiNode TestCustomNode_VendorTagWriteNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestCustomNode_VendorTagWriteNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestCustomNode_VendorTagWrite_node255_0_properties, 255, 0, {1, TestCustomNode_VendorTagWriteNode255_0InputPortDescriptors, 1, TestCustomNode_VendorTagWriteNode255_0OutputPortDescriptors}, 1, {0, NULL}},
    {NULL, 65536, 0, {1, TestCustomNode_VendorTagWriteNode65536_0InputPortDescriptors, 1, TestCustomNode_VendorTagWriteNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestCustomNode_VendorTagWriteNode65538_0InputPortDescriptors, 1, TestCustomNode_VendorTagWriteNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestCustomNode_VendorTagWriteLinks[] =
{
    {{0, 0, 0, 0}, 1, TestCustomNode_VendorTagWrite_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestCustomNode_VendorTagWrite_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable}, {0, 0}},
    {{255, 0, 0, 0}, 1, TestCustomNode_VendorTagWrite_Link2_ChiExternalNode0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestCustomNode_VendorTagWrite_Link3_IPE0_Out8Desc, {0}, {0, 0}},
};

enum TestCustomNodePipelineIds
{
    VendorTagWrite = 0,
};

static ChiPipelineTargetCreateDescriptor TestCustomNode_pipelines[] =
{
    {"VendorTagWrite", { 0, 4, TestCustomNode_VendorTagWriteNodes, 4, TestCustomNode_VendorTagWriteLinks, 1}, {1, TestCustomNode_VendorTagWrite_sink_TargetDescriptors}, {0, NULL}},  // VendorTagWrite
};

/*==================== USECASE: TestMemcpy =======================*/

static ChiBufferFormat TestMemcpy_TARGET_BUFFER_PREVIEW_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget TestMemcpy_TARGET_BUFFER_PREVIEW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestMemcpy_TARGET_BUFFER_PREVIEW_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW

static ChiTarget* TestMemcpy_Targets[] =
{
	&TestMemcpy_TARGET_BUFFER_PREVIEW_target
};

/*****************************Pipeline PreviewWithMemcpy***************************/

static ChiLinkNodeDescriptor TestMemcpy_PreviewWithMemcpy_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestMemcpy_PreviewWithMemcpy_Link1_IFE0_Out0Desc[] =
{
    {255, 0, 0, 0, {0, NULL}}, // ChiExternalNode
};

static ChiLinkNodeDescriptor TestMemcpy_PreviewWithMemcpy_Link2_ChiExternalNode0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __8_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestMemcpy_PreviewWithMemcpy_Link3_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiTargetPortDescriptor TestMemcpy_PreviewWithMemcpy_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestMemcpy_TARGET_BUFFER_PREVIEW_target, 1, __8_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestMemcpy_PreviewWithMemcpyNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// ChiExternalNode0 Input Port Descriptors
static ChiInputPortDescriptor TestMemcpy_PreviewWithMemcpyNode255_0InputPortDescriptors[] =
{
    {0, 0, 0}, // ChiNodeInputPortFull
};

// ChiExternalNode0 Output Port Descriptors
static ChiOutputPortDescriptor TestMemcpy_PreviewWithMemcpyNode255_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // ChiNodeOutputPortFull
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestMemcpy_PreviewWithMemcpyNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestMemcpy_PreviewWithMemcpyNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestMemcpy_PreviewWithMemcpyNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestMemcpy_PreviewWithMemcpyNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNodeProperty TestMemcpy_PreviewWithMemcpy_node255_0_properties[] =
{
    {1, "com.qti.node.memcpy"},
    {9, "0"},
};

static ChiNode TestMemcpy_PreviewWithMemcpyNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestMemcpy_PreviewWithMemcpyNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestMemcpy_PreviewWithMemcpy_node255_0_properties, 255, 0, {1, TestMemcpy_PreviewWithMemcpyNode255_0InputPortDescriptors, 1, TestMemcpy_PreviewWithMemcpyNode255_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65536, 0, {1, TestMemcpy_PreviewWithMemcpyNode65536_0InputPortDescriptors, 1, TestMemcpy_PreviewWithMemcpyNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestMemcpy_PreviewWithMemcpyNode65538_0InputPortDescriptors, 1, TestMemcpy_PreviewWithMemcpyNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestMemcpy_PreviewWithMemcpyLinks[] =
{
    {{0, 0, 0, 0}, 1, TestMemcpy_PreviewWithMemcpy_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestMemcpy_PreviewWithMemcpy_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable}, {0, 0}},
    {{255, 0, 0, 0}, 1, TestMemcpy_PreviewWithMemcpy_Link2_ChiExternalNode0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestMemcpy_PreviewWithMemcpy_Link3_IPE0_Out8Desc, {0}, {0, 0}},
};

/*****************************Pipeline PreviewFromMemcpy***************************/

static ChiLinkNodeDescriptor TestMemcpy_PreviewFromMemcpy_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestMemcpy_PreviewFromMemcpy_Link1_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestMemcpy_PreviewFromMemcpy_Link2_IPE0_Out8Desc[] =
{
    {255, 0, 0, 0, {0, NULL}}, // ChiExternalNode
};

static ChiLinkNodeDescriptor __9_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {255, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestMemcpy_PreviewFromMemcpy_Link3_ChiExternalNode0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiTargetPortDescriptor TestMemcpy_PreviewFromMemcpy_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestMemcpy_TARGET_BUFFER_PREVIEW_target, 1, __9_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestMemcpy_PreviewFromMemcpyNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// ChiExternalNode0 Input Port Descriptors
static ChiInputPortDescriptor TestMemcpy_PreviewFromMemcpyNode255_0InputPortDescriptors[] =
{
    {0, 0, 0}, // ChiNodeInputPortFull
};

// ChiExternalNode0 Output Port Descriptors
static ChiOutputPortDescriptor TestMemcpy_PreviewFromMemcpyNode255_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // ChiNodeOutputPortFull
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestMemcpy_PreviewFromMemcpyNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestMemcpy_PreviewFromMemcpyNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestMemcpy_PreviewFromMemcpyNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestMemcpy_PreviewFromMemcpyNode65538_0OutputPortDescriptors[] =
{
    {8, 0, 0, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNodeProperty TestMemcpy_PreviewFromMemcpy_node255_0_properties[] =
{
    {1, "com.qti.node.memcpy"},
    {9, "0"},
};

static ChiNode TestMemcpy_PreviewFromMemcpyNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestMemcpy_PreviewFromMemcpyNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestMemcpy_PreviewFromMemcpy_node255_0_properties, 255, 0, {1, TestMemcpy_PreviewFromMemcpyNode255_0InputPortDescriptors, 1, TestMemcpy_PreviewFromMemcpyNode255_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65536, 0, {1, TestMemcpy_PreviewFromMemcpyNode65536_0InputPortDescriptors, 1, TestMemcpy_PreviewFromMemcpyNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestMemcpy_PreviewFromMemcpyNode65538_0InputPortDescriptors, 1, TestMemcpy_PreviewFromMemcpyNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestMemcpy_PreviewFromMemcpyLinks[] =
{
    {{0, 0, 0, 0}, 1, TestMemcpy_PreviewFromMemcpy_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestMemcpy_PreviewFromMemcpy_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestMemcpy_PreviewFromMemcpy_Link2_IPE0_Out8Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable}, {0, 0}},
    {{255, 0, 0, 0}, 1, TestMemcpy_PreviewFromMemcpy_Link3_ChiExternalNode0_Out0Desc, {0}, {0, 0}},
};

enum TestMemcpyPipelineIds
{
    PreviewWithMemcpy = 0,
    PreviewFromMemcpy = 1,
};

static ChiPipelineTargetCreateDescriptor TestMemcpy_pipelines[] =
{
    {"PreviewWithMemcpy", { 0, 4, TestMemcpy_PreviewWithMemcpyNodes, 4, TestMemcpy_PreviewWithMemcpyLinks, 1}, {1, TestMemcpy_PreviewWithMemcpy_sink_TargetDescriptors}, {0, NULL}},  // PreviewWithMemcpy
    {"PreviewFromMemcpy", { 0, 4, TestMemcpy_PreviewFromMemcpyNodes, 4, TestMemcpy_PreviewFromMemcpyLinks, 1}, {1, TestMemcpy_PreviewFromMemcpy_sink_TargetDescriptors}, {0, NULL}},  // PreviewFromMemcpy
};

/*==================== USECASE: TestPreviewHVX =======================*/

static ChiBufferFormat TestPreviewHVX_TARGET_BUFFER_PREVIEW_formats[] =
{
    ChiFormatYUV420NV12,
};

static ChiTarget TestPreviewHVX_TARGET_BUFFER_PREVIEW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2160
    },
    1,
    TestPreviewHVX_TARGET_BUFFER_PREVIEW_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW

static ChiTarget* TestPreviewHVX_Targets[] =
{
	&TestPreviewHVX_TARGET_BUFFER_PREVIEW_target
};

/*****************************Pipeline PreviewHVX***************************/

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link0_StatsParse0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link1_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link2_Sensor0_Out1Desc[] =
{
    {65536, 0, 4, 2, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link3_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link4_IFE0_Out1Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link5_IFE0_Out2Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link6_StatsProcessing0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link7_AutoWhiteBalance0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link8_IFE0_Out17Desc[] =
{
    {9, 0, 0, 0, {0, NULL}}, // StatsParse
    {1, 0, 0, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link9_IFE0_Out19Desc[] =
{
    {9, 0, 9, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link10_IFE0_Out21Desc[] =
{
    {9, 0, 1, 0, {0, NULL}}, // StatsParse
    {12, 0, 1, 0, {0, NULL}}, // AutoWhiteBalance
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link11_IFE0_Out18Desc[] =
{
    {9, 0, 2, 0, {0, NULL}}, // StatsParse
    {1, 0, 2, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link12_IFE0_Out16Desc[] =
{
    {9, 0, 3, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link13_IFE0_Out12Desc[] =
{
    {9, 0, 7, 0, {0, NULL}}, // StatsParse
    {1, 0, 7, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link14_IFE0_Out20Desc[] =
{
    {5, 0, 4, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link15_IFE0_Out9Desc[] =
{
    {5, 0, 8, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link16_IFE0_Out7Desc[] =
{
    {5, 0, 10, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link17_AutoFocus0_Out0Desc[] =
{
    {3, 3, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor __10_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestPreviewHVX_PreviewHVX_Link18_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiTargetPortDescriptor TestPreviewHVX_PreviewHVX_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestPreviewHVX_TARGET_BUFFER_PREVIEW_target, 1, __10_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewHVX_PreviewHVXNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
    {1, 0, 0, 0, 0, NULL}, // SensorOutputPort1
};

// StatsProcessing0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewHVX_PreviewHVXNode1_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsProcessingInputPortHDRBE
    {2, 0, 0}, // StatsProcessingPortHDRBHist
    {7, 0, 0}, // StatsProcessingInputPortRS
};

// StatsProcessing0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewHVX_PreviewHVXNode1_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsProcessingOutputPort0
};

// AutoWhiteBalance0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewHVX_PreviewHVXNode12_0InputPortDescriptors[] =
{
    {1, 0, 0}, // StatsInputPortAWBBG
};

// AutoWhiteBalance0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewHVX_PreviewHVXNode12_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AWBOutputPort0
};

// AutoFocus0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewHVX_PreviewHVXNode5_0InputPortDescriptors[] =
{
    {4, 0, 0}, // StatsInputPortBF
    {8, 0, 0}, // StatsInputPortRDIPDAF
    {10, 0, 0}, // StatsInputPortPDAFType3
};

// AutoFocus0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewHVX_PreviewHVXNode5_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AutoFocusOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewHVX_PreviewHVXNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
    {4, 0, 2}, // IFEInputPortRDI1
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewHVX_PreviewHVXNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 0, 0, 0, 0, NULL}, // IFEOutputPortDS16
    {17, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBE
    {19, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {21, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
    {18, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBHIST
    {16, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBHIST
    {12, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsRS
    {20, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBF
    {9, 0, 0, 2, 0, NULL}, // IFEOutputPortRDI1
    {7, 0, 0, 0, 0, NULL}, // IFEOutputPortPDAF
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewHVX_PreviewHVXNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewHVX_PreviewHVXNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

// StatsParse0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewHVX_PreviewHVXNode9_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsParseInputPortHDRBE
    {9, 0, 0}, // StatsParseInputPortTintlessBG
    {1, 0, 0}, // StatsParseInputPortAWBBG
    {2, 0, 0}, // StatsParseInputPortHDRBHist
    {3, 0, 0}, // StatsParseInputPortBHist
    {7, 0, 0}, // StatsParseInputPortRS
};

// StatsParse0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewHVX_PreviewHVXNode9_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsParseOutputPort0
};

static ChiNodeProperty TestPreviewHVX_PreviewHVX_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlibwrapper"},
};

static ChiNodeProperty TestPreviewHVX_PreviewHVX_node1_0_properties[] =
{
    {1, "com.qti.stats.aec"},
    {1, "com.qti.stats.afd"},
    {6, "1"},
};

static ChiNodeProperty TestPreviewHVX_PreviewHVX_node12_0_properties[] =
{
    {1, "com.qti.stats.awb"},
    {6, "1"},
};

static ChiNodeProperty TestPreviewHVX_PreviewHVX_node5_0_properties[] =
{
    {1, "com.qti.stats.af"},
    {1, "com.qti.stats.pdlibwrapper"},
    {6, "1"},
};

static ChiNodeProperty TestPreviewHVX_PreviewHVX_node65536_0_properties[] =
{
    {1, "com.qti.hvx.addconstant"},
    {6, "1"},
};

static ChiNodeProperty TestPreviewHVX_PreviewHVX_node9_0_properties[] =
{
    {6, "1"},
};

static ChiNode TestPreviewHVX_PreviewHVXNodes[] =
{
    {TestPreviewHVX_PreviewHVX_node0_0_properties, 0, 0, {0, NULL, 2, TestPreviewHVX_PreviewHVXNode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {TestPreviewHVX_PreviewHVX_node1_0_properties, 1, 0, {3, TestPreviewHVX_PreviewHVXNode1_0InputPortDescriptors, 1, TestPreviewHVX_PreviewHVXNode1_0OutputPortDescriptors}, 3, {0, NULL}},
    {TestPreviewHVX_PreviewHVX_node12_0_properties, 12, 0, {1, TestPreviewHVX_PreviewHVXNode12_0InputPortDescriptors, 1, TestPreviewHVX_PreviewHVXNode12_0OutputPortDescriptors}, 2, {0, NULL}},
    {TestPreviewHVX_PreviewHVX_node5_0_properties, 5, 0, {3, TestPreviewHVX_PreviewHVXNode5_0InputPortDescriptors, 1, TestPreviewHVX_PreviewHVXNode5_0OutputPortDescriptors}, 3, {0, NULL}},
    {TestPreviewHVX_PreviewHVX_node65536_0_properties, 65536, 0, {2, TestPreviewHVX_PreviewHVXNode65536_0InputPortDescriptors, 12, TestPreviewHVX_PreviewHVXNode65536_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65538, 0, {3, TestPreviewHVX_PreviewHVXNode65538_0InputPortDescriptors, 1, TestPreviewHVX_PreviewHVXNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestPreviewHVX_PreviewHVX_node9_0_properties, 9, 0, {6, TestPreviewHVX_PreviewHVXNode9_0InputPortDescriptors, 1, TestPreviewHVX_PreviewHVXNode9_0OutputPortDescriptors}, 1, {0, NULL}},
};

static ChiNodeLink TestPreviewHVX_PreviewHVXLinks[] =
{
    {{9, 0, 0, 0}, 1, TestPreviewHVX_PreviewHVX_Link0_StatsParse0_Out0Desc, {0}, {0, 0}},
    {{0, 0, 0, 0}, 1, TestPreviewHVX_PreviewHVX_Link1_Sensor0_Out0Desc, {0}, {0, 0}},
    {{0, 0, 1, 0}, 1, TestPreviewHVX_PreviewHVX_Link2_Sensor0_Out1Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestPreviewHVX_PreviewHVX_Link3_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 6, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestPreviewHVX_PreviewHVX_Link4_IFE0_Out1Desc, {ChiFormatPD10, 0, 6, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 2, 0}, 1, TestPreviewHVX_PreviewHVX_Link5_IFE0_Out2Desc, {ChiFormatPD10, 0, 6, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{1, 0, 0, 0}, 1, TestPreviewHVX_PreviewHVX_Link6_StatsProcessing0_Out0Desc, {0}, {0, 0}},
    {{12, 0, 0, 0}, 1, TestPreviewHVX_PreviewHVX_Link7_AutoWhiteBalance0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 17, 0}, 2, TestPreviewHVX_PreviewHVX_Link8_IFE0_Out17Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestPreviewHVX_PreviewHVX_Link9_IFE0_Out19Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 21, 0}, 2, TestPreviewHVX_PreviewHVX_Link10_IFE0_Out21Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 18, 0}, 2, TestPreviewHVX_PreviewHVX_Link11_IFE0_Out18Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 16, 0}, 1, TestPreviewHVX_PreviewHVX_Link12_IFE0_Out16Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 12, 0}, 2, TestPreviewHVX_PreviewHVX_Link13_IFE0_Out12Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestPreviewHVX_PreviewHVX_Link14_IFE0_Out20Desc, {ChiFormatRawPlain64, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 9, 2}, 1, TestPreviewHVX_PreviewHVX_Link15_IFE0_Out9Desc, {ChiFormatBlob, 307200, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 7, 0}, 1, TestPreviewHVX_PreviewHVX_Link16_IFE0_Out7Desc, {ChiFormatRawPlain16, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{5, 0, 0, 0}, 1, TestPreviewHVX_PreviewHVX_Link17_AutoFocus0_Out0Desc, {0}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestPreviewHVX_PreviewHVX_Link18_IPE0_Out8Desc, {0}, {0, 0}},
};

enum TestPreviewHVXPipelineIds
{
    PreviewHVX = 0,
};

static ChiPipelineTargetCreateDescriptor TestPreviewHVX_pipelines[] =
{
    {"PreviewHVX", { 0, 7, TestPreviewHVX_PreviewHVXNodes, 19, TestPreviewHVX_PreviewHVXLinks, 1}, {1, TestPreviewHVX_PreviewHVX_sink_TargetDescriptors}, {0, NULL}},  // PreviewHVX
};

/*==================== USECASE: TestBypassNode =======================*/

static ChiBufferFormat TestBypassNode_TARGET_BUFFER_PREVIEW_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget TestBypassNode_TARGET_BUFFER_PREVIEW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestBypassNode_TARGET_BUFFER_PREVIEW_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW

static ChiTarget* TestBypassNode_Targets[] =
{
	&TestBypassNode_TARGET_BUFFER_PREVIEW_target
};

/*****************************Pipeline BypassNode***************************/

static ChiLinkNodeDescriptor TestBypassNode_BypassNode_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestBypassNode_BypassNode_Link1_IFE0_Out0Desc[] =
{
    {255, 0, 0, 0, {0, NULL}}, // ChiExternalNode
};

static ChiLinkNodeDescriptor TestBypassNode_BypassNode_Link2_ChiExternalNode0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __11_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestBypassNode_BypassNode_Link3_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiTargetPortDescriptor TestBypassNode_BypassNode_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestBypassNode_TARGET_BUFFER_PREVIEW_target, 1, __11_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestBypassNode_BypassNodeNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// ChiExternalNode0 Input Port Descriptors
static ChiInputPortDescriptor TestBypassNode_BypassNodeNode255_0InputPortDescriptors[] =
{
    {0, 0, 0}, // ChiNodeInputPortFull
};

static UINT32 TestBypassNode_BypassNodeNode255_0MappedSourceIds_0[] =
{
  0
};

// ChiExternalNode0 Output Port Descriptors
static ChiOutputPortDescriptor TestBypassNode_BypassNodeNode255_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 1, TestBypassNode_BypassNodeNode255_0MappedSourceIds_0}, // ChiNodeOutputPortFull
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestBypassNode_BypassNodeNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestBypassNode_BypassNodeNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestBypassNode_BypassNodeNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestBypassNode_BypassNodeNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNodeProperty TestBypassNode_BypassNode_node255_0_properties[] =
{
    {1, "com.qti.node.memcpy"},
    {11, "1"},
};

static ChiNode TestBypassNode_BypassNodeNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestBypassNode_BypassNodeNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestBypassNode_BypassNode_node255_0_properties, 255, 0, {1, TestBypassNode_BypassNodeNode255_0InputPortDescriptors, 1, TestBypassNode_BypassNodeNode255_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65536, 0, {1, TestBypassNode_BypassNodeNode65536_0InputPortDescriptors, 1, TestBypassNode_BypassNodeNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestBypassNode_BypassNodeNode65538_0InputPortDescriptors, 1, TestBypassNode_BypassNodeNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestBypassNode_BypassNodeLinks[] =
{
    {{0, 0, 0, 0}, 1, TestBypassNode_BypassNode_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestBypassNode_BypassNode_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable}, {0, 0}},
    {{255, 0, 0, 0}, 1, TestBypassNode_BypassNode_Link2_ChiExternalNode0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestBypassNode_BypassNode_Link3_IPE0_Out8Desc, {0}, {0, 0}},
};

enum TestBypassNodePipelineIds
{
    BypassNode = 0,
};

static ChiPipelineTargetCreateDescriptor TestBypassNode_pipelines[] =
{
    {"BypassNode", { 0, 4, TestBypassNode_BypassNodeNodes, 4, TestBypassNode_BypassNodeLinks, 1}, {1, TestBypassNode_BypassNode_sink_TargetDescriptors}, {0, NULL}},  // BypassNode
};

/*==================== USECASE: TestInplaceNode =======================*/

static ChiBufferFormat TestInplaceNode_TARGET_BUFFER_PREVIEW_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget TestInplaceNode_TARGET_BUFFER_PREVIEW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestInplaceNode_TARGET_BUFFER_PREVIEW_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW

static ChiTarget* TestInplaceNode_Targets[] =
{
	&TestInplaceNode_TARGET_BUFFER_PREVIEW_target
};

/*****************************Pipeline InplaceNode***************************/

static ChiLinkNodeDescriptor TestInplaceNode_InplaceNode_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestInplaceNode_InplaceNode_Link1_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestInplaceNode_InplaceNode_Link2_IPE0_Out8Desc[] =
{
    {255, 0, 0, 0, {0, NULL}}, // ChiExternalNode
};

static ChiLinkNodeDescriptor __12_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {255, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestInplaceNode_InplaceNode_Link3_ChiExternalNode0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiTargetPortDescriptor TestInplaceNode_InplaceNode_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestInplaceNode_TARGET_BUFFER_PREVIEW_target, 1, __12_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestInplaceNode_InplaceNodeNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// ChiExternalNode0 Input Port Descriptors
static ChiInputPortDescriptor TestInplaceNode_InplaceNodeNode255_0InputPortDescriptors[] =
{
    {0, 0, 0}, // ChiNodeInputPortFull
};

// ChiExternalNode0 Output Port Descriptors
static ChiOutputPortDescriptor TestInplaceNode_InplaceNodeNode255_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // ChiNodeOutputPortFull
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestInplaceNode_InplaceNodeNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestInplaceNode_InplaceNodeNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestInplaceNode_InplaceNodeNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestInplaceNode_InplaceNodeNode65538_0OutputPortDescriptors[] =
{
    {8, 0, 0, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNodeProperty TestInplaceNode_InplaceNode_node255_0_properties[] =
{
    {1, "com.qti.node.memcpy"},
    {11, "2"},
};

static ChiNode TestInplaceNode_InplaceNodeNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestInplaceNode_InplaceNodeNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestInplaceNode_InplaceNode_node255_0_properties, 255, 0, {1, TestInplaceNode_InplaceNodeNode255_0InputPortDescriptors, 1, TestInplaceNode_InplaceNodeNode255_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65536, 0, {1, TestInplaceNode_InplaceNodeNode65536_0InputPortDescriptors, 1, TestInplaceNode_InplaceNodeNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestInplaceNode_InplaceNodeNode65538_0InputPortDescriptors, 1, TestInplaceNode_InplaceNodeNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestInplaceNode_InplaceNodeLinks[] =
{
    {{0, 0, 0, 0}, 1, TestInplaceNode_InplaceNode_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestInplaceNode_InplaceNode_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestInplaceNode_InplaceNode_Link2_IPE0_Out8Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable}, {0, 0}},
    {{255, 0, 0, 0}, 1, TestInplaceNode_InplaceNode_Link3_ChiExternalNode0_Out0Desc, {0}, {0, LinkFlagSinkInplaceBuffer}},
};

enum TestInplaceNodePipelineIds
{
    InplaceNode = 0,
};

static ChiPipelineTargetCreateDescriptor TestInplaceNode_pipelines[] =
{
    {"InplaceNode", { 0, 4, TestInplaceNode_InplaceNodeNodes, 4, TestInplaceNode_InplaceNodeLinks, 1}, {1, TestInplaceNode_InplaceNode_sink_TargetDescriptors}, {0, NULL}},  // InplaceNode
};

/*==================== USECASE: TestIPEFullTestgen =======================*/

static ChiBufferFormat TestIPEFullTestgen_TARGET_BUFFER_OUTPUT_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget TestIPEFullTestgen_TARGET_BUFFER_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestIPEFullTestgen_TARGET_BUFFER_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_OUTPUT

static ChiTarget* TestIPEFullTestgen_Targets[] =
{
	&TestIPEFullTestgen_TARGET_BUFFER_OUTPUT_target
};

/*****************************Pipeline IPEFullTestgen***************************/

static ChiLinkNodeDescriptor TestIPEFullTestgen_IPEFullTestgen_Link0_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __13_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestIPEFullTestgen_IPEFullTestgen_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiTargetPortDescriptor TestIPEFullTestgen_IPEFullTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &TestIPEFullTestgen_TARGET_BUFFER_OUTPUT_target, 1, __13_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPEFullTestgen_IPEFullTestgenNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestIPEFullTestgen_IPEFullTestgenNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPEFullTestgen_IPEFullTestgenNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNode TestIPEFullTestgen_IPEFullTestgenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 1, TestIPEFullTestgen_IPEFullTestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestIPEFullTestgen_IPEFullTestgenNode65538_0InputPortDescriptors, 1, TestIPEFullTestgen_IPEFullTestgenNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestIPEFullTestgen_IPEFullTestgenLinks[] =
{
    {{65536, 0, 0, 0}, 1, TestIPEFullTestgen_IPEFullTestgen_Link0_IFE0_Out0Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestIPEFullTestgen_IPEFullTestgen_Link1_IPE0_Out8Desc, {0}, {0, 0}},
};

enum TestIPEFullTestgenPipelineIds
{
    IPEFullTestgen = 0,
};

static ChiPipelineTargetCreateDescriptor TestIPEFullTestgen_pipelines[] =
{
    {"IPEFullTestgen", { 0, 2, TestIPEFullTestgen_IPEFullTestgenNodes, 2, TestIPEFullTestgen_IPEFullTestgenLinks, 1}, {1, TestIPEFullTestgen_IPEFullTestgen_sink_TargetDescriptors}, {0, NULL}},  // IPEFullTestgen
};

/*==================== USECASE: TestIPE3ATestgen =======================*/

static ChiBufferFormat TestIPE3ATestgen_TARGET_BUFFER_PREVIEW_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget TestIPE3ATestgen_TARGET_BUFFER_PREVIEW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    3,
    TestIPE3ATestgen_TARGET_BUFFER_PREVIEW_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW

static ChiTarget* TestIPE3ATestgen_Targets[] =
{
	&TestIPE3ATestgen_TARGET_BUFFER_PREVIEW_target
};

/*****************************Pipeline IPE3ATestgen***************************/

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link0_StatsParse0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link1_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link2_IFE0_Out1Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link3_IFE0_Out2Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link4_StatsProcessing0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link5_AutoWhiteBalance0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link6_IFE0_Out17Desc[] =
{
    {9, 0, 0, 0, {0, NULL}}, // StatsParse
    {1, 0, 0, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link7_IFE0_Out19Desc[] =
{
    {9, 0, 9, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link8_IFE0_Out21Desc[] =
{
    {9, 0, 1, 0, {0, NULL}}, // StatsParse
    {12, 0, 1, 0, {0, NULL}}, // AutoWhiteBalance
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link9_IFE0_Out18Desc[] =
{
    {9, 0, 2, 0, {0, NULL}}, // StatsParse
    {1, 0, 2, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link10_IFE0_Out16Desc[] =
{
    {9, 0, 3, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link11_IFE0_Out12Desc[] =
{
    {9, 0, 7, 0, {0, NULL}}, // StatsParse
    {1, 0, 7, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link12_IFE0_Out20Desc[] =
{
    {5, 0, 4, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link13_IFE0_Out8Desc[] =
{
    {5, 0, 8, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link14_IFE0_Out7Desc[] =
{
    {5, 0, 10, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link15_AutoFocus0_Out0Desc[] =
{
    {3, 3, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor __14_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestIPE3ATestgen_IPE3ATestgen_Link16_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiTargetPortDescriptor TestIPE3ATestgen_IPE3ATestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestIPE3ATestgen_TARGET_BUFFER_PREVIEW_target, 1, __14_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

// StatsProcessing0 Input Port Descriptors
static ChiInputPortDescriptor TestIPE3ATestgen_IPE3ATestgenNode1_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsProcessingInputPortHDRBE
    {2, 0, 0}, // StatsProcessingPortHDRBHist
    {7, 0, 0}, // StatsProcessingInputPortRS
};

// StatsProcessing0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPE3ATestgen_IPE3ATestgenNode1_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsProcessingOutputPort0
};

// AutoWhiteBalance0 Input Port Descriptors
static ChiInputPortDescriptor TestIPE3ATestgen_IPE3ATestgenNode12_0InputPortDescriptors[] =
{
    {1, 0, 0}, // StatsInputPortAWBBG
};

// AutoWhiteBalance0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPE3ATestgen_IPE3ATestgenNode12_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AWBOutputPort0
};

// AutoFocus0 Input Port Descriptors
static ChiInputPortDescriptor TestIPE3ATestgen_IPE3ATestgenNode5_0InputPortDescriptors[] =
{
    {4, 0, 0}, // StatsInputPortBF
    {8, 0, 0}, // StatsInputPortRDIPDAF
    {10, 0, 0}, // StatsInputPortPDAFType3
};

// AutoFocus0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPE3ATestgen_IPE3ATestgenNode5_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AutoFocusOutputPort0
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPE3ATestgen_IPE3ATestgenNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 0, 0, 0, 0, NULL}, // IFEOutputPortDS16
    {17, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBE
    {19, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {21, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
    {18, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBHIST
    {16, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBHIST
    {12, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsRS
    {20, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBF
    {8, 0, 0, 2, 0, NULL}, // IFEOutputPortRDI0
    {7, 0, 0, 0, 0, NULL}, // IFEOutputPortPDAF
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestIPE3ATestgen_IPE3ATestgenNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPE3ATestgen_IPE3ATestgenNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

// StatsParse0 Input Port Descriptors
static ChiInputPortDescriptor TestIPE3ATestgen_IPE3ATestgenNode9_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsParseInputPortHDRBE
    {9, 0, 0}, // StatsParseInputPortTintlessBG
    {1, 0, 0}, // StatsParseInputPortAWBBG
    {2, 0, 0}, // StatsParseInputPortHDRBHist
    {3, 0, 0}, // StatsParseInputPortBHist
    {7, 0, 0}, // StatsParseInputPortRS
};

// StatsParse0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPE3ATestgen_IPE3ATestgenNode9_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsParseOutputPort0
};

static ChiNodeProperty TestIPE3ATestgen_IPE3ATestgen_node1_0_properties[] =
{
    {1, "com.qti.stats.aec"},
    {1, "com.qti.stats.afd"},
    {6, "1"},
};

static ChiNodeProperty TestIPE3ATestgen_IPE3ATestgen_node12_0_properties[] =
{
    {1, "com.qti.stats.awb"},
    {6, "1"},
};

static ChiNodeProperty TestIPE3ATestgen_IPE3ATestgen_node5_0_properties[] =
{
    {1, "com.qti.stats.af"},
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestIPE3ATestgen_IPE3ATestgen_node9_0_properties[] =
{
    {6, "1"},
};

static ChiNode TestIPE3ATestgen_IPE3ATestgenNodes[] =
{
    {TestIPE3ATestgen_IPE3ATestgen_node1_0_properties, 1, 0, {3, TestIPE3ATestgen_IPE3ATestgenNode1_0InputPortDescriptors, 1, TestIPE3ATestgen_IPE3ATestgenNode1_0OutputPortDescriptors}, 3, {0, NULL}},
    {TestIPE3ATestgen_IPE3ATestgen_node12_0_properties, 12, 0, {1, TestIPE3ATestgen_IPE3ATestgenNode12_0InputPortDescriptors, 1, TestIPE3ATestgen_IPE3ATestgenNode12_0OutputPortDescriptors}, 2, {0, NULL}},
    {TestIPE3ATestgen_IPE3ATestgen_node5_0_properties, 5, 0, {3, TestIPE3ATestgen_IPE3ATestgenNode5_0InputPortDescriptors, 1, TestIPE3ATestgen_IPE3ATestgenNode5_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65536, 0, {0, NULL, 12, TestIPE3ATestgen_IPE3ATestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {3, TestIPE3ATestgen_IPE3ATestgenNode65538_0InputPortDescriptors, 1, TestIPE3ATestgen_IPE3ATestgenNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestIPE3ATestgen_IPE3ATestgen_node9_0_properties, 9, 0, {6, TestIPE3ATestgen_IPE3ATestgenNode9_0InputPortDescriptors, 1, TestIPE3ATestgen_IPE3ATestgenNode9_0OutputPortDescriptors}, 1, {0, NULL}},
};

static ChiNodeLink TestIPE3ATestgen_IPE3ATestgenLinks[] =
{
    {{9, 0, 0, 0}, 1, TestIPE3ATestgen_IPE3ATestgen_Link0_StatsParse0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestIPE3ATestgen_IPE3ATestgen_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestIPE3ATestgen_IPE3ATestgen_Link2_IFE0_Out1Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 2, 0}, 1, TestIPE3ATestgen_IPE3ATestgen_Link3_IFE0_Out2Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{1, 0, 0, 0}, 1, TestIPE3ATestgen_IPE3ATestgen_Link4_StatsProcessing0_Out0Desc, {0}, {0, 0}},
    {{12, 0, 0, 0}, 1, TestIPE3ATestgen_IPE3ATestgen_Link5_AutoWhiteBalance0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 17, 0}, 2, TestIPE3ATestgen_IPE3ATestgen_Link6_IFE0_Out17Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestIPE3ATestgen_IPE3ATestgen_Link7_IFE0_Out19Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 21, 0}, 2, TestIPE3ATestgen_IPE3ATestgen_Link8_IFE0_Out21Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 18, 0}, 2, TestIPE3ATestgen_IPE3ATestgen_Link9_IFE0_Out18Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 16, 0}, 1, TestIPE3ATestgen_IPE3ATestgen_Link10_IFE0_Out16Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 12, 0}, 2, TestIPE3ATestgen_IPE3ATestgen_Link11_IFE0_Out12Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestIPE3ATestgen_IPE3ATestgen_Link12_IFE0_Out20Desc, {ChiFormatBlob, 16384, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 8, 2}, 1, TestIPE3ATestgen_IPE3ATestgen_Link13_IFE0_Out8Desc, {ChiFormatBlob, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 7, 0}, 1, TestIPE3ATestgen_IPE3ATestgen_Link14_IFE0_Out7Desc, {ChiFormatRawPlain16, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{5, 0, 0, 0}, 1, TestIPE3ATestgen_IPE3ATestgen_Link15_AutoFocus0_Out0Desc, {0}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestIPE3ATestgen_IPE3ATestgen_Link16_IPE0_Out8Desc, {0}, {0, 0}},
};

enum TestIPE3ATestgenPipelineIds
{
    IPE3ATestgen = 0,
};

static ChiPipelineTargetCreateDescriptor TestIPE3ATestgen_pipelines[] =
{
    {"IPE3ATestgen", { 0, 6, TestIPE3ATestgen_IPE3ATestgenNodes, 17, TestIPE3ATestgen_IPE3ATestgenLinks, 1}, {1, TestIPE3ATestgen_IPE3ATestgen_sink_TargetDescriptors}, {0, NULL}},  // IPE3ATestgen
};

/*==================== USECASE: TestCVPNode =======================*/

static ChiBufferFormat TestCVPNode_TARGET_BUFFER_PREVIEW_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget TestCVPNode_TARGET_BUFFER_PREVIEW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 5488, 4112
    },
    3,
    TestCVPNode_TARGET_BUFFER_PREVIEW_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW

static ChiTarget* TestCVPNode_Targets[] =
{
	&TestCVPNode_TARGET_BUFFER_PREVIEW_target
};

/*****************************Pipeline RealtimeCVPDME***************************/

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDME_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __15_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65536, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDME_Link1_IFE0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDME_Link2_IFE0_Out1Desc[] =
{
    {65543, 0, 5, 0, {0, NULL}}, // CVP
    {65543, 0, 6, 0, {0, NULL}}, // CVP
};

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDME_Link3_CVP0_Out1Desc[] =
{
    {65543, 0, 9, 0, {0, NULL}}, // CVP
};

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDME_Link4_CVP0_Out0Desc[] =
{
    {3, 3, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiTargetPortDescriptor TestCVPNode_RealtimeCVPDME_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestCVPNode_TARGET_BUFFER_PREVIEW_target, 1, __15_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestCVPNode_RealtimeCVPDMENode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestCVPNode_RealtimeCVPDMENode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestCVPNode_RealtimeCVPDMENode65536_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // IFEOutputPortFull
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
};

// CVP0 Input Port Descriptors
static ChiInputPortDescriptor TestCVPNode_RealtimeCVPDMENode65543_0InputPortDescriptors[] =
{
    {5, 0, 0}, // CVPInputPortTARIFEDS4
    {6, 0, 0}, // CVPInputPortREFIFEDS4
    {9, 0, 0}, // CVPInputPortData
};

// CVP0 Output Port Descriptors
static ChiOutputPortDescriptor TestCVPNode_RealtimeCVPDMENode65543_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // CVPOutputPortData
    {0, 1, 0, 0, 0, NULL}, // CVPOutputPortVector
};

static ChiNodeProperty TestCVPNode_RealtimeCVPDME_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlibwrapper"},
};

static ChiNodeProperty TestCVPNode_RealtimeCVPDME_node65536_0_properties[] =
{
    {1, "com.qti.hvx.addconstant"},
    {6, "1"},
};

static ChiNode TestCVPNode_RealtimeCVPDMENodes[] =
{
    {TestCVPNode_RealtimeCVPDME_node0_0_properties, 0, 0, {0, NULL, 1, TestCVPNode_RealtimeCVPDMENode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {TestCVPNode_RealtimeCVPDME_node65536_0_properties, 65536, 0, {1, TestCVPNode_RealtimeCVPDMENode65536_0InputPortDescriptors, 2, TestCVPNode_RealtimeCVPDMENode65536_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65543, 0, {3, TestCVPNode_RealtimeCVPDMENode65543_0InputPortDescriptors, 2, TestCVPNode_RealtimeCVPDMENode65543_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestCVPNode_RealtimeCVPDMELinks[] =
{
    {{0, 0, 0, 0}, 1, TestCVPNode_RealtimeCVPDME_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestCVPNode_RealtimeCVPDME_Link1_IFE0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 1, 0}, 2, TestCVPNode_RealtimeCVPDME_Link2_IFE0_Out1Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65543, 0, 1, 0}, 1, TestCVPNode_RealtimeCVPDME_Link3_CVP0_Out1Desc, {ChiFormatBlob, 4096, 8, 8, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{65543, 0, 0, 0}, 1, TestCVPNode_RealtimeCVPDME_Link4_CVP0_Out0Desc, {0}, {0, 0}},
};

/*****************************Pipeline RealtimeCVPDMEDisplayPort***************************/

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDMEDisplayPort_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 6, 0, {0, NULL}}, // IFE
    {65536, 0, 3, 2, {0, NULL}}, // IFE
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __16_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65536, 0, 22 }, 
};
static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDMEDisplayPort_Link1_IFE0_Out22Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDMEDisplayPort_Link2_IFE0_Out23Desc[] =
{
    {65543, 0, 5, 0, {0, NULL}}, // CVP
    {65543, 0, 6, 0, {0, NULL}}, // CVP
};

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDMEDisplayPort_Link3_CVP0_Out1Desc[] =
{
    {65543, 0, 9, 0, {0, NULL}}, // CVP
};

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDMEDisplayPort_Link4_CVP0_Out0Desc[] =
{
    {3, 3, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiTargetPortDescriptor TestCVPNode_RealtimeCVPDMEDisplayPort_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestCVPNode_TARGET_BUFFER_PREVIEW_target, 1, __16_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestCVPNode_RealtimeCVPDMEDisplayPortNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestCVPNode_RealtimeCVPDMEDisplayPortNode65536_0InputPortDescriptors[] =
{
    {6, 0, 0}, // IFEInputPortDualPD
    {3, 0, 2}, // IFEInputPortRDI0
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestCVPNode_RealtimeCVPDMEDisplayPortNode65536_0OutputPortDescriptors[] =
{
    {22, 1, 1, 0, 0, NULL}, // IFEOutputPortDisplayFull
    {23, 0, 0, 0, 0, NULL}, // IFEOutputPortDisplayDS4
};

// CVP0 Input Port Descriptors
static ChiInputPortDescriptor TestCVPNode_RealtimeCVPDMEDisplayPortNode65543_0InputPortDescriptors[] =
{
    {5, 0, 0}, // CVPInputPortTARIFEDS4
    {6, 0, 0}, // CVPInputPortREFIFEDS4
    {9, 0, 0}, // CVPInputPortData
};

// CVP0 Output Port Descriptors
static ChiOutputPortDescriptor TestCVPNode_RealtimeCVPDMEDisplayPortNode65543_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // CVPOutputPortData
    {0, 1, 0, 0, 0, NULL}, // CVPOutputPortVector
};

static ChiNodeProperty TestCVPNode_RealtimeCVPDMEDisplayPort_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlibwrapper"},
};

static ChiNodeProperty TestCVPNode_RealtimeCVPDMEDisplayPort_node65536_0_properties[] =
{
    {1, "com.qti.hvx.addconstant"},
    {6, "1"},
};

static ChiNode TestCVPNode_RealtimeCVPDMEDisplayPortNodes[] =
{
    {TestCVPNode_RealtimeCVPDMEDisplayPort_node0_0_properties, 0, 0, {0, NULL, 1, TestCVPNode_RealtimeCVPDMEDisplayPortNode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {TestCVPNode_RealtimeCVPDMEDisplayPort_node65536_0_properties, 65536, 0, {3, TestCVPNode_RealtimeCVPDMEDisplayPortNode65536_0InputPortDescriptors, 2, TestCVPNode_RealtimeCVPDMEDisplayPortNode65536_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65543, 0, {3, TestCVPNode_RealtimeCVPDMEDisplayPortNode65543_0InputPortDescriptors, 2, TestCVPNode_RealtimeCVPDMEDisplayPortNode65543_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestCVPNode_RealtimeCVPDMEDisplayPortLinks[] =
{
    {{0, 0, 0, 0}, 3, TestCVPNode_RealtimeCVPDMEDisplayPort_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 22, 0}, 1, TestCVPNode_RealtimeCVPDMEDisplayPort_Link1_IFE0_Out22Desc, {0}, {0, 0}},
    {{65536, 0, 23, 0}, 2, TestCVPNode_RealtimeCVPDMEDisplayPort_Link2_IFE0_Out23Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65543, 0, 1, 0}, 1, TestCVPNode_RealtimeCVPDMEDisplayPort_Link3_CVP0_Out1Desc, {ChiFormatBlob, 4096, 8, 8, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{65543, 0, 0, 0}, 1, TestCVPNode_RealtimeCVPDMEDisplayPort_Link4_CVP0_Out0Desc, {0}, {0, 0}},
};

/*****************************Pipeline RealtimeCVPDMEICA***************************/

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDMEICA_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 6, 2, {0, NULL}}, // IFE
    {65536, 0, 3, 2, {0, NULL}}, // IFE
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __17_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65536, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDMEICA_Link1_IFE0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDMEICA_Link2_IFE0_Out1Desc[] =
{
    {65543, 0, 5, 0, {0, NULL}}, // CVP
};

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDMEICA_Link3_CVP0_Out2Desc[] =
{
    {65543, 0, 6, 0, {0, NULL}}, // CVP
};

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDMEICA_Link4_CVP0_Out1Desc[] =
{
    {65543, 0, 9, 0, {0, NULL}}, // CVP
};

static ChiLinkNodeDescriptor TestCVPNode_RealtimeCVPDMEICA_Link5_CVP0_Out0Desc[] =
{
    {3, 3, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiTargetPortDescriptor TestCVPNode_RealtimeCVPDMEICA_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestCVPNode_TARGET_BUFFER_PREVIEW_target, 1, __17_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestCVPNode_RealtimeCVPDMEICANode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestCVPNode_RealtimeCVPDMEICANode65536_0InputPortDescriptors[] =
{
    {6, 0, 2}, // IFEInputPortDualPD
    {3, 0, 2}, // IFEInputPortRDI0
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestCVPNode_RealtimeCVPDMEICANode65536_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // IFEOutputPortFull
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
};

// CVP0 Input Port Descriptors
static ChiInputPortDescriptor TestCVPNode_RealtimeCVPDMEICANode65543_0InputPortDescriptors[] =
{
    {5, 0, 0}, // CVPInputPortTARIFEDS4
    {6, 0, 0}, // CVPInputPortREFIFEDS4
    {9, 0, 0}, // CVPInputPortData
};

// CVP0 Output Port Descriptors
static ChiOutputPortDescriptor TestCVPNode_RealtimeCVPDMEICANode65543_0OutputPortDescriptors[] =
{
    {2, 0, 0, 0, 0, NULL}, // CVPOutputPortImage
    {1, 0, 0, 0, 0, NULL}, // CVPOutputPortData
    {0, 1, 0, 0, 0, NULL}, // CVPOutputPortVector
};

static ChiNodeProperty TestCVPNode_RealtimeCVPDMEICA_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlibwrapper"},
};

static ChiNodeProperty TestCVPNode_RealtimeCVPDMEICA_node65536_0_properties[] =
{
    {1, "com.qti.hvx.addconstant"},
    {6, "1"},
};

static ChiNodeProperty TestCVPNode_RealtimeCVPDMEICA_node65543_0_properties[] =
{
    {2, "1"},
};

static ChiNode TestCVPNode_RealtimeCVPDMEICANodes[] =
{
    {TestCVPNode_RealtimeCVPDMEICA_node0_0_properties, 0, 0, {0, NULL, 1, TestCVPNode_RealtimeCVPDMEICANode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {TestCVPNode_RealtimeCVPDMEICA_node65536_0_properties, 65536, 0, {3, TestCVPNode_RealtimeCVPDMEICANode65536_0InputPortDescriptors, 2, TestCVPNode_RealtimeCVPDMEICANode65536_0OutputPortDescriptors}, 2, {0, NULL}},
    {TestCVPNode_RealtimeCVPDMEICA_node65543_0_properties, 65543, 0, {3, TestCVPNode_RealtimeCVPDMEICANode65543_0InputPortDescriptors, 3, TestCVPNode_RealtimeCVPDMEICANode65543_0OutputPortDescriptors}, 1, {0, NULL}},
};

static ChiNodeLink TestCVPNode_RealtimeCVPDMEICALinks[] =
{
    {{0, 0, 0, 0}, 3, TestCVPNode_RealtimeCVPDMEICA_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestCVPNode_RealtimeCVPDMEICA_Link1_IFE0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestCVPNode_RealtimeCVPDMEICA_Link2_IFE0_Out1Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65543, 0, 2, 0}, 1, TestCVPNode_RealtimeCVPDMEICA_Link3_CVP0_Out2Desc, {ChiFormatUBWCNV124R, 0, 8, 8, BufferHeapIon, 0}, {0, 0}},
    {{65543, 0, 1, 0}, 1, TestCVPNode_RealtimeCVPDMEICA_Link4_CVP0_Out1Desc, {ChiFormatBlob, 4096, 8, 8, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{65543, 0, 0, 0}, 1, TestCVPNode_RealtimeCVPDMEICA_Link5_CVP0_Out0Desc, {0}, {0, 0}},
};

enum TestCVPNodePipelineIds
{
    RealtimeCVPDME = 0,
    RealtimeCVPDMEDisplayPort = 1,
    RealtimeCVPDMEICA = 2,
};

static ChiPipelineTargetCreateDescriptor TestCVPNode_pipelines[] =
{
    {"RealtimeCVPDME", { 0, 3, TestCVPNode_RealtimeCVPDMENodes, 5, TestCVPNode_RealtimeCVPDMELinks, 1}, {1, TestCVPNode_RealtimeCVPDME_sink_TargetDescriptors}, {0, NULL}},  // RealtimeCVPDME
    {"RealtimeCVPDMEDisplayPort", { 0, 3, TestCVPNode_RealtimeCVPDMEDisplayPortNodes, 5, TestCVPNode_RealtimeCVPDMEDisplayPortLinks, 1}, {1, TestCVPNode_RealtimeCVPDMEDisplayPort_sink_TargetDescriptors}, {0, NULL}},  // RealtimeCVPDMEDisplayPort
    {"RealtimeCVPDMEICA", { 0, 3, TestCVPNode_RealtimeCVPDMEICANodes, 6, TestCVPNode_RealtimeCVPDMEICALinks, 1}, {1, TestCVPNode_RealtimeCVPDMEICA_sink_TargetDescriptors}, {0, NULL}},  // RealtimeCVPDMEICA
};

/*==================== USECASE: TestOfflineIPE =======================*/

static ChiBufferFormat TestOfflineIPE_TARGET_BUFFER_IPE_INPUT_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestOfflineIPE_TARGET_BUFFER_OUTPUT_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget TestOfflineIPE_TARGET_BUFFER_IPE_INPUT_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestOfflineIPE_TARGET_BUFFER_IPE_INPUT_formats,
    NULL
}; // TARGET_BUFFER_IPE_INPUT

static ChiTarget TestOfflineIPE_TARGET_BUFFER_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestOfflineIPE_TARGET_BUFFER_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_OUTPUT

static ChiTarget* TestOfflineIPE_Targets[] =
{
	&TestOfflineIPE_TARGET_BUFFER_IPE_INPUT_target,
	&TestOfflineIPE_TARGET_BUFFER_OUTPUT_target
};

/*****************************Pipeline IpeDisp***************************/

static ChiLinkNodeDescriptor TestOfflineIPE_IpeDisp_source_Link_0NodeDescriptors[] =
{
    {65538, 0, 0},
};
static ChiLinkNodeDescriptor __18_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestOfflineIPE_IpeDisp_Link0_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiTargetPortDescriptor TestOfflineIPE_IpeDisp_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &TestOfflineIPE_TARGET_BUFFER_OUTPUT_target, 1, __18_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
};

static ChiTargetPortDescriptor TestOfflineIPE_IpeDisp_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_IPE_INPUT", &TestOfflineIPE_TARGET_BUFFER_IPE_INPUT_target, 1, TestOfflineIPE_IpeDisp_source_Link_0NodeDescriptors}, // TARGET_BUFFER_IPE_INPUT
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineIPE_IpeDispNode65538_0InputPortDescriptors[] =
{
    {0, 1, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineIPE_IpeDispNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNode TestOfflineIPE_IpeDispNodes[] =
{
    {NULL, 65538, 0, {1, TestOfflineIPE_IpeDispNode65538_0InputPortDescriptors, 1, TestOfflineIPE_IpeDispNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestOfflineIPE_IpeDispLinks[] =
{
    {{65538, 0, 8, 0}, 1, TestOfflineIPE_IpeDisp_Link0_IPE0_Out8Desc, {0}, {0, 0}},
};

/*****************************Pipeline IpeVideo***************************/

static ChiLinkNodeDescriptor TestOfflineIPE_IpeVideo_source_Link_0NodeDescriptors[] =
{
    {65538, 0, 0},
};
static ChiLinkNodeDescriptor __19_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestOfflineIPE_IpeVideo_Link0_IPE0_Out9Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiTargetPortDescriptor TestOfflineIPE_IpeVideo_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &TestOfflineIPE_TARGET_BUFFER_OUTPUT_target, 1, __19_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
};

static ChiTargetPortDescriptor TestOfflineIPE_IpeVideo_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_IPE_INPUT", &TestOfflineIPE_TARGET_BUFFER_IPE_INPUT_target, 1, TestOfflineIPE_IpeVideo_source_Link_0NodeDescriptors}, // TARGET_BUFFER_IPE_INPUT
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineIPE_IpeVideoNode65538_0InputPortDescriptors[] =
{
    {0, 1, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineIPE_IpeVideoNode65538_0OutputPortDescriptors[] =
{
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
};

static ChiNode TestOfflineIPE_IpeVideoNodes[] =
{
    {NULL, 65538, 0, {1, TestOfflineIPE_IpeVideoNode65538_0InputPortDescriptors, 1, TestOfflineIPE_IpeVideoNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestOfflineIPE_IpeVideoLinks[] =
{
    {{65538, 0, 9, 0}, 1, TestOfflineIPE_IpeVideo_Link0_IPE0_Out9Desc, {0}, {0, 0}},
};

enum TestOfflineIPEPipelineIds
{
    IpeDisp = 0,
    IpeVideo = 1,
};

static ChiPipelineTargetCreateDescriptor TestOfflineIPE_pipelines[] =
{
    {"IpeDisp", { 0, 1, TestOfflineIPE_IpeDispNodes, 1, TestOfflineIPE_IpeDispLinks, 0}, {1, TestOfflineIPE_IpeDisp_sink_TargetDescriptors}, {1, TestOfflineIPE_IpeDisp_source_TargetDescriptors}},  // IpeDisp
    {"IpeVideo", { 0, 1, TestOfflineIPE_IpeVideoNodes, 1, TestOfflineIPE_IpeVideoLinks, 0}, {1, TestOfflineIPE_IpeVideo_sink_TargetDescriptors}, {1, TestOfflineIPE_IpeVideo_source_TargetDescriptors}},  // IpeVideo
};

/*==================== USECASE: TestOfflineJPEG =======================*/

static ChiBufferFormat TestOfflineJPEG_TARGET_BUFFER_JPEG_INPUT_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestOfflineJPEG_TARGET_BUFFER_SNAPSHOT_formats[] =
{
    ChiFormatBlob,
};

static ChiTarget TestOfflineJPEG_TARGET_BUFFER_JPEG_INPUT_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestOfflineJPEG_TARGET_BUFFER_JPEG_INPUT_formats,
    NULL
}; // TARGET_BUFFER_JPEG_INPUT

static ChiTarget TestOfflineJPEG_TARGET_BUFFER_SNAPSHOT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    1,
    TestOfflineJPEG_TARGET_BUFFER_SNAPSHOT_formats,
    NULL
}; // TARGET_BUFFER_SNAPSHOT

static ChiTarget* TestOfflineJPEG_Targets[] =
{
	&TestOfflineJPEG_TARGET_BUFFER_JPEG_INPUT_target,
	&TestOfflineJPEG_TARGET_BUFFER_SNAPSHOT_target
};

/*****************************Pipeline JpegSnapshot***************************/

static ChiLinkNodeDescriptor TestOfflineJPEG_JpegSnapshot_source_Link_0NodeDescriptors[] =
{
    {65537, 0, 0},
};
static ChiLinkNodeDescriptor TestOfflineJPEG_JpegSnapshot_Link0_JPEG0_Out1Desc[] =
{
    {6, 0, 0, 0, {0, NULL}}, // JPEGAggregator
};

static ChiLinkNodeDescriptor __20_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {6, 0, 2 }, 
};
static ChiLinkNodeDescriptor TestOfflineJPEG_JpegSnapshot_Link1_JPEGAggregator0_Out2Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestOfflineJPEG_JpegSnapshot_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &TestOfflineJPEG_TARGET_BUFFER_SNAPSHOT_target, 1, __20_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestOfflineJPEG_JpegSnapshot_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_JPEG_INPUT", &TestOfflineJPEG_TARGET_BUFFER_JPEG_INPUT_target, 1, TestOfflineJPEG_JpegSnapshot_source_Link_0NodeDescriptors}, // TARGET_BUFFER_JPEG_INPUT
};

// JPEGAggregator0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineJPEG_JpegSnapshotNode6_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGAggregatorInputPort0
};

// JPEGAggregator0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineJPEG_JpegSnapshotNode6_0OutputPortDescriptors[] =
{
    {2, 1, 1, 0, 0, NULL}, // JPEGAggregatorOutputPort0
};

// JPEG0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineJPEG_JpegSnapshotNode65537_0InputPortDescriptors[] =
{
    {0, 1, 0}, // JPEGInputPort0
};

// JPEG0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineJPEG_JpegSnapshotNode65537_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // JPEGOutputPort0
};

static ChiNode TestOfflineJPEG_JpegSnapshotNodes[] =
{
    {NULL, 6, 0, {1, TestOfflineJPEG_JpegSnapshotNode6_0InputPortDescriptors, 1, TestOfflineJPEG_JpegSnapshotNode6_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65537, 0, {1, TestOfflineJPEG_JpegSnapshotNode65537_0InputPortDescriptors, 1, TestOfflineJPEG_JpegSnapshotNode65537_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestOfflineJPEG_JpegSnapshotLinks[] =
{
    {{65537, 0, 1, 0}, 1, TestOfflineJPEG_JpegSnapshot_Link0_JPEG0_Out1Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{6, 0, 2, 0}, 1, TestOfflineJPEG_JpegSnapshot_Link1_JPEGAggregator0_Out2Desc, {0}, {0, 0}},
};

enum TestOfflineJPEGPipelineIds
{
    JpegSnapshot = 0,
};

static ChiPipelineTargetCreateDescriptor TestOfflineJPEG_pipelines[] =
{
    {"JpegSnapshot", { 0, 2, TestOfflineJPEG_JpegSnapshotNodes, 2, TestOfflineJPEG_JpegSnapshotLinks, 0}, {1, TestOfflineJPEG_JpegSnapshot_sink_TargetDescriptors}, {1, TestOfflineJPEG_JpegSnapshot_source_TargetDescriptors}},  // JpegSnapshot
};

/*==================== USECASE: TestOfflineBPSIPE =======================*/

static ChiBufferFormat TestOfflineBPSIPE_TARGET_BUFFER_RAW_IN_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiBufferFormat TestOfflineBPSIPE_TARGET_BUFFER_SNAPSHOT_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget TestOfflineBPSIPE_TARGET_BUFFER_RAW_IN_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    2,
    TestOfflineBPSIPE_TARGET_BUFFER_RAW_IN_formats,
    NULL
}; // TARGET_BUFFER_RAW_IN

static ChiTarget TestOfflineBPSIPE_TARGET_BUFFER_SNAPSHOT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    3,
    TestOfflineBPSIPE_TARGET_BUFFER_SNAPSHOT_formats,
    NULL
}; // TARGET_BUFFER_SNAPSHOT

static ChiTarget* TestOfflineBPSIPE_Targets[] =
{
	&TestOfflineBPSIPE_TARGET_BUFFER_RAW_IN_target,
	&TestOfflineBPSIPE_TARGET_BUFFER_SNAPSHOT_target
};

/*****************************Pipeline OfflineBPSFull***************************/

static ChiLinkNodeDescriptor TestOfflineBPSIPE_OfflineBPSFull_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor __21_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {65539, 0, 1 }, 
};
static ChiLinkNodeDescriptor TestOfflineBPSIPE_OfflineBPSFull_Link0_BPS0_Out1Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestOfflineBPSIPE_OfflineBPSFull_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &TestOfflineBPSIPE_TARGET_BUFFER_SNAPSHOT_target, 1, __21_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestOfflineBPSIPE_OfflineBPSFull_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW_IN", &TestOfflineBPSIPE_TARGET_BUFFER_RAW_IN_target, 1, TestOfflineBPSIPE_OfflineBPSFull_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW_IN
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineBPSIPE_OfflineBPSFullNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineBPSIPE_OfflineBPSFullNode65539_0OutputPortDescriptors[] =
{
    {1, 1, 1, 0, 0, NULL}, // BPSOutputPortFull
};

static ChiNode TestOfflineBPSIPE_OfflineBPSFullNodes[] =
{
    {NULL, 65539, 0, {1, TestOfflineBPSIPE_OfflineBPSFullNode65539_0InputPortDescriptors, 1, TestOfflineBPSIPE_OfflineBPSFullNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestOfflineBPSIPE_OfflineBPSFullLinks[] =
{
    {{65539, 0, 1, 0}, 1, TestOfflineBPSIPE_OfflineBPSFull_Link0_BPS0_Out1Desc, {0}, {0, 0}},
};

/*****************************Pipeline OfflineBPSIPEDisp***************************/

static ChiLinkNodeDescriptor TestOfflineBPSIPE_OfflineBPSIPEDisp_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor TestOfflineBPSIPE_OfflineBPSIPEDisp_Link0_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __22_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestOfflineBPSIPE_OfflineBPSIPEDisp_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestOfflineBPSIPE_OfflineBPSIPEDisp_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &TestOfflineBPSIPE_TARGET_BUFFER_SNAPSHOT_target, 1, __22_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestOfflineBPSIPE_OfflineBPSIPEDisp_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW_IN", &TestOfflineBPSIPE_TARGET_BUFFER_RAW_IN_target, 1, TestOfflineBPSIPE_OfflineBPSIPEDisp_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW_IN
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
};

static ChiNode TestOfflineBPSIPE_OfflineBPSIPEDispNodes[] =
{
    {NULL, 65538, 0, {1, TestOfflineBPSIPE_OfflineBPSIPEDispNode65538_0InputPortDescriptors, 1, TestOfflineBPSIPE_OfflineBPSIPEDispNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, TestOfflineBPSIPE_OfflineBPSIPEDispNode65539_0InputPortDescriptors, 1, TestOfflineBPSIPE_OfflineBPSIPEDispNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestOfflineBPSIPE_OfflineBPSIPEDispLinks[] =
{
    {{65539, 0, 1, 0}, 1, TestOfflineBPSIPE_OfflineBPSIPEDisp_Link0_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestOfflineBPSIPE_OfflineBPSIPEDisp_Link1_IPE0_Out8Desc, {0}, {0, 0}},
};

/*****************************Pipeline OfflineBPSIPEDispVideo***************************/

static ChiLinkNodeDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispVideo_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispVideo_Link0_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __23_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispVideo_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiLinkNodeDescriptor __24_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispVideo_Link2_IPE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispVideo_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &TestOfflineBPSIPE_TARGET_BUFFER_SNAPSHOT_target, 1, __23_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
    {"TARGET_BUFFER_SNAPSHOT", &TestOfflineBPSIPE_TARGET_BUFFER_SNAPSHOT_target, 1, __24_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispVideo_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW_IN", &TestOfflineBPSIPE_TARGET_BUFFER_RAW_IN_target, 1, TestOfflineBPSIPE_OfflineBPSIPEDispVideo_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW_IN
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispVideoNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispVideoNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispVideoNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineBPSIPE_OfflineBPSIPEDispVideoNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
};

static ChiNode TestOfflineBPSIPE_OfflineBPSIPEDispVideoNodes[] =
{
    {NULL, 65538, 0, {1, TestOfflineBPSIPE_OfflineBPSIPEDispVideoNode65538_0InputPortDescriptors, 2, TestOfflineBPSIPE_OfflineBPSIPEDispVideoNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, TestOfflineBPSIPE_OfflineBPSIPEDispVideoNode65539_0InputPortDescriptors, 1, TestOfflineBPSIPE_OfflineBPSIPEDispVideoNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestOfflineBPSIPE_OfflineBPSIPEDispVideoLinks[] =
{
    {{65539, 0, 1, 0}, 1, TestOfflineBPSIPE_OfflineBPSIPEDispVideo_Link0_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestOfflineBPSIPE_OfflineBPSIPEDispVideo_Link1_IPE0_Out8Desc, {0}, {0, 0}},
    {{65538, 0, 9, 0}, 1, TestOfflineBPSIPE_OfflineBPSIPEDispVideo_Link2_IPE0_Out9Desc, {0}, {0, 0}},
};

enum TestOfflineBPSIPEPipelineIds
{
    OfflineBPSFull = 0,
    OfflineBPSIPEDisp = 1,
    OfflineBPSIPEDispVideo = 2,
};

static ChiPipelineTargetCreateDescriptor TestOfflineBPSIPE_pipelines[] =
{
    {"OfflineBPSFull", { 0, 1, TestOfflineBPSIPE_OfflineBPSFullNodes, 1, TestOfflineBPSIPE_OfflineBPSFullLinks, 0}, {1, TestOfflineBPSIPE_OfflineBPSFull_sink_TargetDescriptors}, {1, TestOfflineBPSIPE_OfflineBPSFull_source_TargetDescriptors}},  // OfflineBPSFull
    {"OfflineBPSIPEDisp", { 0, 2, TestOfflineBPSIPE_OfflineBPSIPEDispNodes, 2, TestOfflineBPSIPE_OfflineBPSIPEDispLinks, 0}, {1, TestOfflineBPSIPE_OfflineBPSIPEDisp_sink_TargetDescriptors}, {1, TestOfflineBPSIPE_OfflineBPSIPEDisp_source_TargetDescriptors}},  // OfflineBPSIPEDisp
    {"OfflineBPSIPEDispVideo", { 0, 2, TestOfflineBPSIPE_OfflineBPSIPEDispVideoNodes, 3, TestOfflineBPSIPE_OfflineBPSIPEDispVideoLinks, 0}, {2, TestOfflineBPSIPE_OfflineBPSIPEDispVideo_sink_TargetDescriptors}, {1, TestOfflineBPSIPE_OfflineBPSIPEDispVideo_source_TargetDescriptors}},  // OfflineBPSIPEDispVideo
};

/*==================== USECASE: TestOfflineBPSIPEJpeg =======================*/

static ChiBufferFormat TestOfflineBPSIPEJpeg_TARGET_BUFFER_RAW_IN_formats[] =
{
    ChiFormatRawPlain16,
};

static ChiBufferFormat TestOfflineBPSIPEJpeg_TARGET_BUFFER_SNAPSHOT_formats[] =
{
    ChiFormatJpeg,
};

static ChiTarget TestOfflineBPSIPEJpeg_TARGET_BUFFER_RAW_IN_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    1,
    TestOfflineBPSIPEJpeg_TARGET_BUFFER_RAW_IN_formats,
    NULL
}; // TARGET_BUFFER_RAW_IN

static ChiTarget TestOfflineBPSIPEJpeg_TARGET_BUFFER_SNAPSHOT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2048
    },
    1,
    TestOfflineBPSIPEJpeg_TARGET_BUFFER_SNAPSHOT_formats,
    NULL
}; // TARGET_BUFFER_SNAPSHOT

static ChiTarget* TestOfflineBPSIPEJpeg_Targets[] =
{
	&TestOfflineBPSIPEJpeg_TARGET_BUFFER_RAW_IN_target,
	&TestOfflineBPSIPEJpeg_TARGET_BUFFER_SNAPSHOT_target
};

/*****************************Pipeline OfflineBPSIPEJpeg***************************/

static ChiLinkNodeDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_Link0_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_Link1_IPE0_Out8Desc[] =
{
    {65537, 0, 0, 0, {0, NULL}}, // JPEG
};

static ChiLinkNodeDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_Link2_JPEG0_Out1Desc[] =
{
    {6, 0, 0, 0, {0, NULL}}, // JPEGAggregator
};

static ChiLinkNodeDescriptor __25_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {6, 0, 2 }, 
};
static ChiLinkNodeDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_Link3_JPEGAggregator0_Out2Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &TestOfflineBPSIPEJpeg_TARGET_BUFFER_SNAPSHOT_target, 1, __25_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW_IN", &TestOfflineBPSIPEJpeg_TARGET_BUFFER_RAW_IN_target, 1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW_IN
};

// JPEGAggregator0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode6_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGAggregatorInputPort0
};

// JPEGAggregator0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode6_0OutputPortDescriptors[] =
{
    {2, 1, 1, 0, 0, NULL}, // JPEGAggregatorOutputPort0
};

// JPEG0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode65537_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGInputPort0
};

// JPEG0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode65537_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // JPEGOutputPort0
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode65538_0OutputPortDescriptors[] =
{
    {8, 0, 0, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
};

static ChiNode TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNodes[] =
{
    {NULL, 6, 0, {1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode6_0InputPortDescriptors, 1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode6_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65537, 0, {1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode65537_0InputPortDescriptors, 1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode65537_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode65538_0InputPortDescriptors, 1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode65539_0InputPortDescriptors, 1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegLinks[] =
{
    {{65539, 0, 1, 0}, 1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_Link0_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_Link1_IPE0_Out8Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65537, 0, 1, 0}, 1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_Link2_JPEG0_Out1Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{6, 0, 2, 0}, 1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_Link3_JPEGAggregator0_Out2Desc, {0}, {0, 0}},
};

enum TestOfflineBPSIPEJpegPipelineIds
{
    OfflineBPSIPEJpeg = 0,
};

static ChiPipelineTargetCreateDescriptor TestOfflineBPSIPEJpeg_pipelines[] =
{
    {"OfflineBPSIPEJpeg", { 0, 4, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegNodes, 4, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpegLinks, 0}, {1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_sink_TargetDescriptors}, {1, TestOfflineBPSIPEJpeg_OfflineBPSIPEJpeg_source_TargetDescriptors}},  // OfflineBPSIPEJpeg
};

/*==================== USECASE: TestOfflineFD =======================*/

static ChiBufferFormat TestOfflineFD_TARGET_BUFFER_FD_OUTPUT_formats[] =
{
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestOfflineFD_TARGET_BUFFER_FD_INPUT_formats[] =
{
    ChiFormatYUV420NV12,
};

static ChiTarget TestOfflineFD_TARGET_BUFFER_FD_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 5488, 4112
    },
    1,
    TestOfflineFD_TARGET_BUFFER_FD_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_FD_OUTPUT

static ChiTarget TestOfflineFD_TARGET_BUFFER_FD_INPUT_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 5488, 4112
    },
    1,
    TestOfflineFD_TARGET_BUFFER_FD_INPUT_formats,
    NULL
}; // TARGET_BUFFER_FD_INPUT

static ChiTarget* TestOfflineFD_Targets[] =
{
	&TestOfflineFD_TARGET_BUFFER_FD_OUTPUT_target,
	&TestOfflineFD_TARGET_BUFFER_FD_INPUT_target
};

/*****************************Pipeline OfflineFD***************************/

static ChiLinkNodeDescriptor TestOfflineFD_OfflineFD_source_Link_0NodeDescriptors[] =
{
    {255, 0, 0},
};
static ChiLinkNodeDescriptor TestOfflineFD_OfflineFD_Link0_ChiExternalNode0_Out0Desc[] =
{
    {65540, 0, 0, 0, {0, NULL}}, // FDHw
    {8, 0, 3, 0, {0, NULL}}, // FDManager
};

static ChiLinkNodeDescriptor __26_TARGET_BUFFER_FD_OUTPUT_Link_NodeDescriptors[] =
{
    {8, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestOfflineFD_OfflineFD_Link1_FDManager0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_FD_OUTPUT
};

static ChiLinkNodeDescriptor TestOfflineFD_OfflineFD_Link2_FDHw0_Out0Desc[] =
{
    {8, 0, 0, 0, {0, NULL}}, // FDManager
};

static ChiLinkNodeDescriptor TestOfflineFD_OfflineFD_Link3_FDHw0_Out2Desc[] =
{
    {8, 0, 2, 0, {0, NULL}}, // FDManager
};

static ChiTargetPortDescriptor TestOfflineFD_OfflineFD_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_FD_OUTPUT", &TestOfflineFD_TARGET_BUFFER_FD_OUTPUT_target, 1, __26_TARGET_BUFFER_FD_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_FD_OUTPUT
};

static ChiTargetPortDescriptor TestOfflineFD_OfflineFD_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_FD_INPUT", &TestOfflineFD_TARGET_BUFFER_FD_INPUT_target, 1, TestOfflineFD_OfflineFD_source_Link_0NodeDescriptors}, // TARGET_BUFFER_FD_INPUT
};

// ChiExternalNode0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineFD_OfflineFDNode255_0InputPortDescriptors[] =
{
    {0, 1, 0}, // ChiNodeInputPortFull
};

// ChiExternalNode0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineFD_OfflineFDNode255_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // ChiNodeOutputPortFull
};

// FDHw0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineFD_OfflineFDNode65540_0InputPortDescriptors[] =
{
    {0, 0, 0}, // FDHwInputPortImage
};

// FDHw0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineFD_OfflineFDNode65540_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // FDHwOutputPortResults
    {2, 0, 0, 0, 0, NULL}, // FDHwOutputPortWorkBuffer
};

// FDManager0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineFD_OfflineFDNode8_0InputPortDescriptors[] =
{
    {3, 0, 0}, // FDManagerInputPortImage
    {0, 0, 0}, // FDManagerInputPortHwResults
    {2, 0, 0}, // FDManagerInputPortHwPyramidBuffer
};

// FDManager0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineFD_OfflineFDNode8_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // FDManagerOutputPortResults
};

static ChiNodeProperty TestOfflineFD_OfflineFD_node255_0_properties[] =
{
    {1, "com.qti.node.memcpy"},
};

static ChiNode TestOfflineFD_OfflineFDNodes[] =
{
    {TestOfflineFD_OfflineFD_node255_0_properties, 255, 0, {1, TestOfflineFD_OfflineFDNode255_0InputPortDescriptors, 1, TestOfflineFD_OfflineFDNode255_0OutputPortDescriptors}, 1, {0, NULL}},
    {NULL, 65540, 0, {1, TestOfflineFD_OfflineFDNode65540_0InputPortDescriptors, 2, TestOfflineFD_OfflineFDNode65540_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 8, 0, {3, TestOfflineFD_OfflineFDNode8_0InputPortDescriptors, 1, TestOfflineFD_OfflineFDNode8_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestOfflineFD_OfflineFDLinks[] =
{
    {{255, 0, 0, 0}, 2, TestOfflineFD_OfflineFD_Link0_ChiExternalNode0_Out0Desc, {ChiFormatYUV420NV12, 0, 6, 23, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{8, 0, 0, 0}, 1, TestOfflineFD_OfflineFD_Link1_FDManager0_Out0Desc, {0}, {0, 0}},
    {{65540, 0, 0, 0}, 1, TestOfflineFD_OfflineFD_Link2_FDHw0_Out0Desc, {ChiFormatBlob, 16384, 6, 12, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65540, 0, 2, 0}, 1, TestOfflineFD_OfflineFD_Link3_FDHw0_Out2Desc, {ChiFormatBlob, 218496, 6, 12, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
};

enum TestOfflineFDPipelineIds
{
    OfflineFD = 0,
};

static ChiPipelineTargetCreateDescriptor TestOfflineFD_pipelines[] =
{
    {"OfflineFD", { 0, 3, TestOfflineFD_OfflineFDNodes, 4, TestOfflineFD_OfflineFDLinks, 0}, {1, TestOfflineFD_OfflineFD_sink_TargetDescriptors}, {1, TestOfflineFD_OfflineFD_source_TargetDescriptors}},  // OfflineFD
};

/*==================== USECASE: TestIPETestgen =======================*/

static ChiBufferFormat TestIPETestgen_TARGET_BUFFER_OUTPUT_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestIPETestgen_TARGET_BUFFER_STATS_formats[] =
{
    ChiFormatBlob,
};

static ChiTarget TestIPETestgen_TARGET_BUFFER_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestIPETestgen_TARGET_BUFFER_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_OUTPUT

static ChiTarget TestIPETestgen_TARGET_BUFFER_STATS_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 691200, 1
    },
    1,
    TestIPETestgen_TARGET_BUFFER_STATS_formats,
    NULL
}; // TARGET_BUFFER_STATS

static ChiTarget* TestIPETestgen_Targets[] =
{
	&TestIPETestgen_TARGET_BUFFER_OUTPUT_target,
	&TestIPETestgen_TARGET_BUFFER_STATS_target
};

/*****************************Pipeline IPEATestgen***************************/

static ChiLinkNodeDescriptor TestIPETestgen_IPEATestgen_Link0_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __27_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEATestgen_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEATestgen_Link2_IFE0_Out1Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEATestgen_Link3_IFE0_Out2Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
    {65541, 0, 6, 0, {0, NULL}}, // LRME
    {65541, 0, 7, 0, {0, NULL}}, // LRME
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEATestgen_Link4_IPE0_Out10Desc[] =
{
    {65538, 0, 4, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEATestgen_Link5_IPE0_Out11Desc[] =
{
    {65538, 0, 5, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEATestgen_Link6_IPE0_Out12Desc[] =
{
    {65538, 0, 6, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEATestgen_Link7_LRME0_Out0Desc[] =
{
    {65542, 0, 2, 0, {0, NULL}}, // RANSAC
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEATestgen_Link8_RANSAC0_Out1Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiTargetPortDescriptor TestIPETestgen_IPEATestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &TestIPETestgen_TARGET_BUFFER_OUTPUT_target, 1, __27_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEATestgenNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 0, 0, 0, 0, NULL}, // IFEOutputPortDS16
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestIPETestgen_IPEATestgenNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
    {4, 0, 0}, // IPEInputPortFullRef
    {5, 0, 0}, // IPEInputPortDS4Ref
    {6, 0, 0}, // IPEInputPortDS16Ref
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEATestgenNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
    {10, 0, 0, 0, 0, NULL}, // IPEOutputPortFullRef
    {11, 0, 0, 0, 0, NULL}, // IPEOutputPortDS4Ref
    {12, 0, 0, 0, 0, NULL}, // IPEOutputPortDS16Ref
};

// LRME0 Input Port Descriptors
static ChiInputPortDescriptor TestIPETestgen_IPEATestgenNode65541_0InputPortDescriptors[] =
{
    {6, 0, 0}, // LRMEInputPortTARIFEDS16
    {7, 0, 0}, // LRMEInputPortREFIFEDS16
};

// LRME0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEATestgenNode65541_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // LRMEOutputPortVector
};

// RANSAC0 Input Port Descriptors
static ChiInputPortDescriptor TestIPETestgen_IPEATestgenNode65542_0InputPortDescriptors[] =
{
    {2, 0, 0}, // RANSACInputPortVector
};

// RANSAC0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEATestgenNode65542_0OutputPortDescriptors[] =
{
    {1, 1, 0, 0, 0, NULL}, // RANSACOutputPort0
};

static ChiNode TestIPETestgen_IPEATestgenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 3, TestIPETestgen_IPEATestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {6, TestIPETestgen_IPEATestgenNode65538_0InputPortDescriptors, 4, TestIPETestgen_IPEATestgenNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65541, 0, {2, TestIPETestgen_IPEATestgenNode65541_0InputPortDescriptors, 1, TestIPETestgen_IPEATestgenNode65541_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65542, 0, {1, TestIPETestgen_IPEATestgenNode65542_0InputPortDescriptors, 1, TestIPETestgen_IPEATestgenNode65542_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestIPETestgen_IPEATestgenLinks[] =
{
    {{65536, 0, 0, 0}, 1, TestIPETestgen_IPEATestgen_Link0_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestIPETestgen_IPEATestgen_Link1_IPE0_Out8Desc, {0}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestIPETestgen_IPEATestgen_Link2_IFE0_Out1Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 2, 0}, 3, TestIPETestgen_IPEATestgen_Link3_IFE0_Out2Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 10, 0}, 1, TestIPETestgen_IPEATestgen_Link4_IPE0_Out10Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 11, 0}, 1, TestIPETestgen_IPEATestgen_Link5_IPE0_Out11Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 12, 0}, 1, TestIPETestgen_IPEATestgen_Link6_IPE0_Out12Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65541, 0, 0, 0}, 1, TestIPETestgen_IPEATestgen_Link7_LRME0_Out0Desc, {ChiFormatBlob, 4096, 9, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65542, 0, 1, 0}, 1, TestIPETestgen_IPEATestgen_Link8_RANSAC0_Out1Desc, {0}, {0, 0}},
};

/*****************************Pipeline IPEABTestgen***************************/

static ChiLinkNodeDescriptor TestIPETestgen_IPEABTestgen_Link0_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __28_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABTestgen_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __29_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABTestgen_Link2_IPE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABTestgen_Link3_IFE0_Out1Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABTestgen_Link4_IFE0_Out2Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
    {65541, 0, 6, 0, {0, NULL}}, // LRME
    {65541, 0, 7, 0, {0, NULL}}, // LRME
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABTestgen_Link5_IPE0_Out10Desc[] =
{
    {65538, 0, 4, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABTestgen_Link6_IPE0_Out11Desc[] =
{
    {65538, 0, 5, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABTestgen_Link7_IPE0_Out12Desc[] =
{
    {65538, 0, 6, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABTestgen_Link8_LRME0_Out0Desc[] =
{
    {65542, 0, 2, 0, {0, NULL}}, // RANSAC
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABTestgen_Link9_RANSAC0_Out1Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiTargetPortDescriptor TestIPETestgen_IPEABTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &TestIPETestgen_TARGET_BUFFER_OUTPUT_target, 1, __28_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &TestIPETestgen_TARGET_BUFFER_OUTPUT_target, 1, __29_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEABTestgenNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 0, 0, 0, 0, NULL}, // IFEOutputPortDS16
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestIPETestgen_IPEABTestgenNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
    {4, 0, 0}, // IPEInputPortFullRef
    {5, 0, 0}, // IPEInputPortDS4Ref
    {6, 0, 0}, // IPEInputPortDS16Ref
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEABTestgenNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
    {10, 0, 0, 0, 0, NULL}, // IPEOutputPortFullRef
    {11, 0, 0, 0, 0, NULL}, // IPEOutputPortDS4Ref
    {12, 0, 0, 0, 0, NULL}, // IPEOutputPortDS16Ref
};

// LRME0 Input Port Descriptors
static ChiInputPortDescriptor TestIPETestgen_IPEABTestgenNode65541_0InputPortDescriptors[] =
{
    {6, 0, 0}, // LRMEInputPortTARIFEDS16
    {7, 0, 0}, // LRMEInputPortREFIFEDS16
};

// LRME0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEABTestgenNode65541_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // LRMEOutputPortVector
};

// RANSAC0 Input Port Descriptors
static ChiInputPortDescriptor TestIPETestgen_IPEABTestgenNode65542_0InputPortDescriptors[] =
{
    {2, 0, 0}, // RANSACInputPortVector
};

// RANSAC0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEABTestgenNode65542_0OutputPortDescriptors[] =
{
    {1, 1, 0, 0, 0, NULL}, // RANSACOutputPort0
};

static ChiNode TestIPETestgen_IPEABTestgenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 3, TestIPETestgen_IPEABTestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {6, TestIPETestgen_IPEABTestgenNode65538_0InputPortDescriptors, 5, TestIPETestgen_IPEABTestgenNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65541, 0, {2, TestIPETestgen_IPEABTestgenNode65541_0InputPortDescriptors, 1, TestIPETestgen_IPEABTestgenNode65541_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65542, 0, {1, TestIPETestgen_IPEABTestgenNode65542_0InputPortDescriptors, 1, TestIPETestgen_IPEABTestgenNode65542_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestIPETestgen_IPEABTestgenLinks[] =
{
    {{65536, 0, 0, 0}, 1, TestIPETestgen_IPEABTestgen_Link0_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestIPETestgen_IPEABTestgen_Link1_IPE0_Out8Desc, {0}, {0, 0}},
    {{65538, 0, 9, 0}, 1, TestIPETestgen_IPEABTestgen_Link2_IPE0_Out9Desc, {0}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestIPETestgen_IPEABTestgen_Link3_IFE0_Out1Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 2, 0}, 3, TestIPETestgen_IPEABTestgen_Link4_IFE0_Out2Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 10, 0}, 1, TestIPETestgen_IPEABTestgen_Link5_IPE0_Out10Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 11, 0}, 1, TestIPETestgen_IPEABTestgen_Link6_IPE0_Out11Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 12, 0}, 1, TestIPETestgen_IPEABTestgen_Link7_IPE0_Out12Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65541, 0, 0, 0}, 1, TestIPETestgen_IPEABTestgen_Link8_LRME0_Out0Desc, {ChiFormatBlob, 4096, 9, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65542, 0, 1, 0}, 1, TestIPETestgen_IPEABTestgen_Link9_RANSAC0_Out1Desc, {0}, {0, 0}},
};

/*****************************Pipeline IPEABStatsTestgen***************************/

static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link0_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __30_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __31_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link2_IPE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __32_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 20 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link3_IFE0_Out20Desc[] =
{
    {2, 3, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __33_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 21 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link4_IFE0_Out21Desc[] =
{
    {2, 4, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __34_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 19 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link5_IFE0_Out19Desc[] =
{
    {2, 5, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __35_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 15 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link6_IFE0_Out15Desc[] =
{
    {2, 6, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __36_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 12 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link7_IFE0_Out12Desc[] =
{
    {2, 7, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link8_IFE0_Out1Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link9_IFE0_Out2Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
    {65541, 0, 6, 0, {0, NULL}}, // LRME
    {65541, 0, 7, 0, {0, NULL}}, // LRME
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link10_IPE0_Out10Desc[] =
{
    {65538, 0, 4, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link11_IPE0_Out11Desc[] =
{
    {65538, 0, 5, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link12_IPE0_Out12Desc[] =
{
    {65538, 0, 6, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link13_LRME0_Out0Desc[] =
{
    {65542, 0, 2, 0, {0, NULL}}, // RANSAC
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABStatsTestgen_Link14_RANSAC0_Out1Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiTargetPortDescriptor TestIPETestgen_IPEABStatsTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &TestIPETestgen_TARGET_BUFFER_OUTPUT_target, 1, __30_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &TestIPETestgen_TARGET_BUFFER_OUTPUT_target, 1, __31_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_STATS", &TestIPETestgen_TARGET_BUFFER_STATS_target, 1, __32_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_STATS", &TestIPETestgen_TARGET_BUFFER_STATS_target, 1, __33_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_STATS", &TestIPETestgen_TARGET_BUFFER_STATS_target, 1, __34_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_STATS", &TestIPETestgen_TARGET_BUFFER_STATS_target, 1, __35_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_STATS", &TestIPETestgen_TARGET_BUFFER_STATS_target, 1, __36_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEABStatsTestgenNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {20, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsBF
    {21, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
    {19, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {15, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsIHIST
    {12, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsRS
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 0, 0, 0, 0, NULL}, // IFEOutputPortDS16
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestIPETestgen_IPEABStatsTestgenNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
    {4, 0, 0}, // IPEInputPortFullRef
    {5, 0, 0}, // IPEInputPortDS4Ref
    {6, 0, 0}, // IPEInputPortDS16Ref
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEABStatsTestgenNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
    {10, 0, 0, 0, 0, NULL}, // IPEOutputPortFullRef
    {11, 0, 0, 0, 0, NULL}, // IPEOutputPortDS4Ref
    {12, 0, 0, 0, 0, NULL}, // IPEOutputPortDS16Ref
};

// LRME0 Input Port Descriptors
static ChiInputPortDescriptor TestIPETestgen_IPEABStatsTestgenNode65541_0InputPortDescriptors[] =
{
    {6, 0, 0}, // LRMEInputPortTARIFEDS16
    {7, 0, 0}, // LRMEInputPortREFIFEDS16
};

// LRME0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEABStatsTestgenNode65541_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // LRMEOutputPortVector
};

// RANSAC0 Input Port Descriptors
static ChiInputPortDescriptor TestIPETestgen_IPEABStatsTestgenNode65542_0InputPortDescriptors[] =
{
    {2, 0, 0}, // RANSACInputPortVector
};

// RANSAC0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEABStatsTestgenNode65542_0OutputPortDescriptors[] =
{
    {1, 1, 0, 0, 0, NULL}, // RANSACOutputPort0
};

static ChiNode TestIPETestgen_IPEABStatsTestgenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 8, TestIPETestgen_IPEABStatsTestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {6, TestIPETestgen_IPEABStatsTestgenNode65538_0InputPortDescriptors, 5, TestIPETestgen_IPEABStatsTestgenNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65541, 0, {2, TestIPETestgen_IPEABStatsTestgenNode65541_0InputPortDescriptors, 1, TestIPETestgen_IPEABStatsTestgenNode65541_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65542, 0, {1, TestIPETestgen_IPEABStatsTestgenNode65542_0InputPortDescriptors, 1, TestIPETestgen_IPEABStatsTestgenNode65542_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestIPETestgen_IPEABStatsTestgenLinks[] =
{
    {{65536, 0, 0, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link0_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link1_IPE0_Out8Desc, {0}, {0, 0}},
    {{65538, 0, 9, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link2_IPE0_Out9Desc, {0}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link3_IFE0_Out20Desc, {0}, {0, 0}},
    {{65536, 0, 21, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link4_IFE0_Out21Desc, {0}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link5_IFE0_Out19Desc, {0}, {0, 0}},
    {{65536, 0, 15, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link6_IFE0_Out15Desc, {0}, {0, 0}},
    {{65536, 0, 12, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link7_IFE0_Out12Desc, {0}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link8_IFE0_Out1Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 2, 0}, 3, TestIPETestgen_IPEABStatsTestgen_Link9_IFE0_Out2Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 10, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link10_IPE0_Out10Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 11, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link11_IPE0_Out11Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 12, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link12_IPE0_Out12Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65541, 0, 0, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link13_LRME0_Out0Desc, {ChiFormatBlob, 4096, 9, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65542, 0, 1, 0}, 1, TestIPETestgen_IPEABStatsTestgen_Link14_RANSAC0_Out1Desc, {0}, {0, 0}},
};

/*****************************Pipeline IPEABCStatsTestgen***************************/

static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link0_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __37_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __38_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link2_IPE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __39_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 6 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link3_IFE0_Out6Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __40_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 20 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link4_IFE0_Out20Desc[] =
{
    {2, 3, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __41_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 21 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link5_IFE0_Out21Desc[] =
{
    {2, 4, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __42_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 19 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link6_IFE0_Out19Desc[] =
{
    {2, 5, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __43_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 15 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link7_IFE0_Out15Desc[] =
{
    {2, 6, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __44_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 12 }, 
};
static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link8_IFE0_Out12Desc[] =
{
    {2, 7, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link9_IFE0_Out1Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link10_IFE0_Out2Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
    {65541, 0, 6, 0, {0, NULL}}, // LRME
    {65541, 0, 7, 0, {0, NULL}}, // LRME
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link11_IPE0_Out10Desc[] =
{
    {65538, 0, 4, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link12_IPE0_Out11Desc[] =
{
    {65538, 0, 5, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link13_IPE0_Out12Desc[] =
{
    {65538, 0, 6, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link14_LRME0_Out0Desc[] =
{
    {65542, 0, 2, 0, {0, NULL}}, // RANSAC
};

static ChiLinkNodeDescriptor TestIPETestgen_IPEABCStatsTestgen_Link15_RANSAC0_Out1Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiTargetPortDescriptor TestIPETestgen_IPEABCStatsTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &TestIPETestgen_TARGET_BUFFER_OUTPUT_target, 1, __37_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &TestIPETestgen_TARGET_BUFFER_OUTPUT_target, 1, __38_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &TestIPETestgen_TARGET_BUFFER_OUTPUT_target, 1, __39_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_STATS", &TestIPETestgen_TARGET_BUFFER_STATS_target, 1, __40_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_STATS", &TestIPETestgen_TARGET_BUFFER_STATS_target, 1, __41_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_STATS", &TestIPETestgen_TARGET_BUFFER_STATS_target, 1, __42_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_STATS", &TestIPETestgen_TARGET_BUFFER_STATS_target, 1, __43_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_STATS", &TestIPETestgen_TARGET_BUFFER_STATS_target, 1, __44_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEABCStatsTestgenNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {6, 1, 1, 0, 0, NULL}, // IFEOutputPortFD
    {20, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsBF
    {21, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
    {19, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {15, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsIHIST
    {12, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsRS
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 0, 0, 0, 0, NULL}, // IFEOutputPortDS16
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestIPETestgen_IPEABCStatsTestgenNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
    {4, 0, 0}, // IPEInputPortFullRef
    {5, 0, 0}, // IPEInputPortDS4Ref
    {6, 0, 0}, // IPEInputPortDS16Ref
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEABCStatsTestgenNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
    {10, 0, 0, 0, 0, NULL}, // IPEOutputPortFullRef
    {11, 0, 0, 0, 0, NULL}, // IPEOutputPortDS4Ref
    {12, 0, 0, 0, 0, NULL}, // IPEOutputPortDS16Ref
};

// LRME0 Input Port Descriptors
static ChiInputPortDescriptor TestIPETestgen_IPEABCStatsTestgenNode65541_0InputPortDescriptors[] =
{
    {6, 0, 0}, // LRMEInputPortTARIFEDS16
    {7, 0, 0}, // LRMEInputPortREFIFEDS16
};

// LRME0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEABCStatsTestgenNode65541_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // LRMEOutputPortVector
};

// RANSAC0 Input Port Descriptors
static ChiInputPortDescriptor TestIPETestgen_IPEABCStatsTestgenNode65542_0InputPortDescriptors[] =
{
    {2, 0, 0}, // RANSACInputPortVector
};

// RANSAC0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPETestgen_IPEABCStatsTestgenNode65542_0OutputPortDescriptors[] =
{
    {1, 1, 0, 0, 0, NULL}, // RANSACOutputPort0
};

static ChiNode TestIPETestgen_IPEABCStatsTestgenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 9, TestIPETestgen_IPEABCStatsTestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {6, TestIPETestgen_IPEABCStatsTestgenNode65538_0InputPortDescriptors, 5, TestIPETestgen_IPEABCStatsTestgenNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65541, 0, {2, TestIPETestgen_IPEABCStatsTestgenNode65541_0InputPortDescriptors, 1, TestIPETestgen_IPEABCStatsTestgenNode65541_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65542, 0, {1, TestIPETestgen_IPEABCStatsTestgenNode65542_0InputPortDescriptors, 1, TestIPETestgen_IPEABCStatsTestgenNode65542_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestIPETestgen_IPEABCStatsTestgenLinks[] =
{
    {{65536, 0, 0, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link0_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link1_IPE0_Out8Desc, {0}, {0, 0}},
    {{65538, 0, 9, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link2_IPE0_Out9Desc, {0}, {0, 0}},
    {{65536, 0, 6, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link3_IFE0_Out6Desc, {0}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link4_IFE0_Out20Desc, {0}, {0, 0}},
    {{65536, 0, 21, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link5_IFE0_Out21Desc, {0}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link6_IFE0_Out19Desc, {0}, {0, 0}},
    {{65536, 0, 15, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link7_IFE0_Out15Desc, {0}, {0, 0}},
    {{65536, 0, 12, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link8_IFE0_Out12Desc, {0}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link9_IFE0_Out1Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 2, 0}, 3, TestIPETestgen_IPEABCStatsTestgen_Link10_IFE0_Out2Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 10, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link11_IPE0_Out10Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 11, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link12_IPE0_Out11Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 12, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link13_IPE0_Out12Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65541, 0, 0, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link14_LRME0_Out0Desc, {ChiFormatBlob, 4096, 9, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65542, 0, 1, 0}, 1, TestIPETestgen_IPEABCStatsTestgen_Link15_RANSAC0_Out1Desc, {0}, {0, 0}},
};

enum TestIPETestgenPipelineIds
{
    IPEATestgen = 0,
    IPEABTestgen = 1,
    IPEABStatsTestgen = 2,
    IPEABCStatsTestgen = 3,
};

static ChiPipelineTargetCreateDescriptor TestIPETestgen_pipelines[] =
{
    {"IPEATestgen", { 0, 4, TestIPETestgen_IPEATestgenNodes, 9, TestIPETestgen_IPEATestgenLinks, 0}, {1, TestIPETestgen_IPEATestgen_sink_TargetDescriptors}, {0, NULL}},  // IPEATestgen
    {"IPEABTestgen", { 0, 4, TestIPETestgen_IPEABTestgenNodes, 10, TestIPETestgen_IPEABTestgenLinks, 0}, {2, TestIPETestgen_IPEABTestgen_sink_TargetDescriptors}, {0, NULL}},  // IPEABTestgen
    {"IPEABStatsTestgen", { 0, 4, TestIPETestgen_IPEABStatsTestgenNodes, 15, TestIPETestgen_IPEABStatsTestgenLinks, 0}, {7, TestIPETestgen_IPEABStatsTestgen_sink_TargetDescriptors}, {0, NULL}},  // IPEABStatsTestgen
    {"IPEABCStatsTestgen", { 0, 4, TestIPETestgen_IPEABCStatsTestgenNodes, 16, TestIPETestgen_IPEABCStatsTestgenLinks, 0}, {8, TestIPETestgen_IPEABCStatsTestgen_sink_TargetDescriptors}, {0, NULL}},  // IPEABCStatsTestgen
};

/*==================== USECASE: TestIPESensor =======================*/

static ChiBufferFormat TestIPESensor_TARGET_BUFFER_OUTPUT_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestIPESensor_TARGET_BUFFER_STATS_formats[] =
{
    ChiFormatBlob,
};

static ChiTarget TestIPESensor_TARGET_BUFFER_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestIPESensor_TARGET_BUFFER_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_OUTPUT

static ChiTarget TestIPESensor_TARGET_BUFFER_STATS_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 691200, 1
    },
    1,
    TestIPESensor_TARGET_BUFFER_STATS_formats,
    NULL
}; // TARGET_BUFFER_STATS

static ChiTarget* TestIPESensor_Targets[] =
{
	&TestIPESensor_TARGET_BUFFER_OUTPUT_target,
	&TestIPESensor_TARGET_BUFFER_STATS_target
};

/*****************************Pipeline IPEABCStatsSensor***************************/

static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link1_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __45_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link2_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __46_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link3_IPE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __47_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 6 }, 
};
static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link4_IFE0_Out6Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __48_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 20 }, 
};
static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link5_IFE0_Out20Desc[] =
{
    {2, 3, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __49_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 21 }, 
};
static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link6_IFE0_Out21Desc[] =
{
    {2, 4, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __50_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 19 }, 
};
static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link7_IFE0_Out19Desc[] =
{
    {2, 5, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __51_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 15 }, 
};
static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link8_IFE0_Out15Desc[] =
{
    {2, 6, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __52_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 12 }, 
};
static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link9_IFE0_Out12Desc[] =
{
    {2, 7, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link10_IFE0_Out1Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link11_IFE0_Out2Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
    {65541, 0, 6, 0, {0, NULL}}, // LRME
    {65541, 0, 7, 0, {0, NULL}}, // LRME
};

static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link12_IPE0_Out10Desc[] =
{
    {65538, 0, 4, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link13_IPE0_Out11Desc[] =
{
    {65538, 0, 5, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link14_IPE0_Out12Desc[] =
{
    {65538, 0, 6, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link15_LRME0_Out0Desc[] =
{
    {65542, 0, 2, 0, {0, NULL}}, // RANSAC
};

static ChiLinkNodeDescriptor TestIPESensor_IPEABCStatsSensor_Link16_RANSAC0_Out1Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiTargetPortDescriptor TestIPESensor_IPEABCStatsSensor_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &TestIPESensor_TARGET_BUFFER_OUTPUT_target, 1, __45_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &TestIPESensor_TARGET_BUFFER_OUTPUT_target, 1, __46_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &TestIPESensor_TARGET_BUFFER_OUTPUT_target, 1, __47_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_STATS", &TestIPESensor_TARGET_BUFFER_STATS_target, 1, __48_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_STATS", &TestIPESensor_TARGET_BUFFER_STATS_target, 1, __49_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_STATS", &TestIPESensor_TARGET_BUFFER_STATS_target, 1, __50_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_STATS", &TestIPESensor_TARGET_BUFFER_STATS_target, 1, __51_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_STATS", &TestIPESensor_TARGET_BUFFER_STATS_target, 1, __52_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPESensor_IPEABCStatsSensorNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestIPESensor_IPEABCStatsSensorNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPESensor_IPEABCStatsSensorNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {6, 1, 1, 0, 0, NULL}, // IFEOutputPortFD
    {20, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsBF
    {21, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
    {19, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {15, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsIHIST
    {12, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsRS
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 0, 0, 0, 0, NULL}, // IFEOutputPortDS16
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestIPESensor_IPEABCStatsSensorNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
    {4, 0, 0}, // IPEInputPortFullRef
    {5, 0, 0}, // IPEInputPortDS4Ref
    {6, 0, 0}, // IPEInputPortDS16Ref
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPESensor_IPEABCStatsSensorNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
    {10, 0, 0, 0, 0, NULL}, // IPEOutputPortFullRef
    {11, 0, 0, 0, 0, NULL}, // IPEOutputPortDS4Ref
    {12, 0, 0, 0, 0, NULL}, // IPEOutputPortDS16Ref
};

// LRME0 Input Port Descriptors
static ChiInputPortDescriptor TestIPESensor_IPEABCStatsSensorNode65541_0InputPortDescriptors[] =
{
    {6, 0, 0}, // LRMEInputPortTARIFEDS16
    {7, 0, 0}, // LRMEInputPortREFIFEDS16
};

// LRME0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPESensor_IPEABCStatsSensorNode65541_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // LRMEOutputPortVector
};

// RANSAC0 Input Port Descriptors
static ChiInputPortDescriptor TestIPESensor_IPEABCStatsSensorNode65542_0InputPortDescriptors[] =
{
    {2, 0, 0}, // RANSACInputPortVector
};

// RANSAC0 Output Port Descriptors
static ChiOutputPortDescriptor TestIPESensor_IPEABCStatsSensorNode65542_0OutputPortDescriptors[] =
{
    {1, 1, 0, 0, 0, NULL}, // RANSACOutputPort0
};

static ChiNode TestIPESensor_IPEABCStatsSensorNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestIPESensor_IPEABCStatsSensorNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, TestIPESensor_IPEABCStatsSensorNode65536_0InputPortDescriptors, 9, TestIPESensor_IPEABCStatsSensorNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {6, TestIPESensor_IPEABCStatsSensorNode65538_0InputPortDescriptors, 5, TestIPESensor_IPEABCStatsSensorNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65541, 0, {2, TestIPESensor_IPEABCStatsSensorNode65541_0InputPortDescriptors, 1, TestIPESensor_IPEABCStatsSensorNode65541_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65542, 0, {1, TestIPESensor_IPEABCStatsSensorNode65542_0InputPortDescriptors, 1, TestIPESensor_IPEABCStatsSensorNode65542_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestIPESensor_IPEABCStatsSensorLinks[] =
{
    {{0, 0, 0, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link2_IPE0_Out8Desc, {0}, {0, 0}},
    {{65538, 0, 9, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link3_IPE0_Out9Desc, {0}, {0, 0}},
    {{65536, 0, 6, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link4_IFE0_Out6Desc, {0}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link5_IFE0_Out20Desc, {0}, {0, 0}},
    {{65536, 0, 21, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link6_IFE0_Out21Desc, {0}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link7_IFE0_Out19Desc, {0}, {0, 0}},
    {{65536, 0, 15, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link8_IFE0_Out15Desc, {0}, {0, 0}},
    {{65536, 0, 12, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link9_IFE0_Out12Desc, {0}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link10_IFE0_Out1Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 2, 0}, 3, TestIPESensor_IPEABCStatsSensor_Link11_IFE0_Out2Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 10, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link12_IPE0_Out10Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 11, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link13_IPE0_Out11Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 12, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link14_IPE0_Out12Desc, {ChiFormatPD10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65541, 0, 0, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link15_LRME0_Out0Desc, {ChiFormatBlob, 4096, 9, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65542, 0, 1, 0}, 1, TestIPESensor_IPEABCStatsSensor_Link16_RANSAC0_Out1Desc, {0}, {0, 0}},
};

enum TestIPESensorPipelineIds
{
    IPEABCStatsSensor = 0,
};

static ChiPipelineTargetCreateDescriptor TestIPESensor_pipelines[] =
{
    {"IPEABCStatsSensor", { 0, 5, TestIPESensor_IPEABCStatsSensorNodes, 17, TestIPESensor_IPEABCStatsSensorLinks, 1}, {8, TestIPESensor_IPEABCStatsSensor_sink_TargetDescriptors}, {0, NULL}},  // IPEABCStatsSensor
};

/*==================== USECASE: TestBPSWithIPEAndDS =======================*/

static ChiBufferFormat TestBPSWithIPEAndDS_TARGET_BUFFER_RAW_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiBufferFormat TestBPSWithIPEAndDS_TARGET_BUFFER_PREVIEW_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget TestBPSWithIPEAndDS_TARGET_BUFFER_RAW_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    2,
    TestBPSWithIPEAndDS_TARGET_BUFFER_RAW_formats,
    NULL
}; // TARGET_BUFFER_RAW

static ChiTarget TestBPSWithIPEAndDS_TARGET_BUFFER_PREVIEW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    3,
    TestBPSWithIPEAndDS_TARGET_BUFFER_PREVIEW_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW

static ChiTarget* TestBPSWithIPEAndDS_Targets[] =
{
	&TestBPSWithIPEAndDS_TARGET_BUFFER_RAW_target,
	&TestBPSWithIPEAndDS_TARGET_BUFFER_PREVIEW_target
};

/*****************************Pipeline BPSWithIPEAndDS***************************/

static ChiLinkNodeDescriptor TestBPSWithIPEAndDS_BPSWithIPEAndDS_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor TestBPSWithIPEAndDS_BPSWithIPEAndDS_Link0_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __53_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestBPSWithIPEAndDS_BPSWithIPEAndDS_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiLinkNodeDescriptor TestBPSWithIPEAndDS_BPSWithIPEAndDS_Link2_BPS0_Out2Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestBPSWithIPEAndDS_BPSWithIPEAndDS_Link3_BPS0_Out3Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestBPSWithIPEAndDS_BPSWithIPEAndDS_Link4_BPS0_Out4Desc[] =
{
    {65538, 0, 3, 0, {0, NULL}}, // IPE
};

static ChiTargetPortDescriptor TestBPSWithIPEAndDS_BPSWithIPEAndDS_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestBPSWithIPEAndDS_TARGET_BUFFER_PREVIEW_target, 1, __53_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

static ChiTargetPortDescriptor TestBPSWithIPEAndDS_BPSWithIPEAndDS_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &TestBPSWithIPEAndDS_TARGET_BUFFER_RAW_target, 1, TestBPSWithIPEAndDS_BPSWithIPEAndDS_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestBPSWithIPEAndDS_BPSWithIPEAndDSNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
    {3, 0, 0}, // IPEInputPortDS64
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestBPSWithIPEAndDS_BPSWithIPEAndDSNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor TestBPSWithIPEAndDS_BPSWithIPEAndDSNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor TestBPSWithIPEAndDS_BPSWithIPEAndDSNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
    {2, 0, 0, 0, 0, NULL}, // BPSOutputPortDS4
    {3, 0, 0, 0, 0, NULL}, // BPSOutputPortDS16
    {4, 0, 0, 0, 0, NULL}, // BPSOutputPortDS64
};

static ChiNodeProperty TestBPSWithIPEAndDS_BPSWithIPEAndDS_node65538_0_properties[] =
{
    {5, "1"},
    {13, "9999"},
    {14, "9999"},
};

static ChiNode TestBPSWithIPEAndDS_BPSWithIPEAndDSNodes[] =
{
    {TestBPSWithIPEAndDS_BPSWithIPEAndDS_node65538_0_properties, 65538, 0, {4, TestBPSWithIPEAndDS_BPSWithIPEAndDSNode65538_0InputPortDescriptors, 1, TestBPSWithIPEAndDS_BPSWithIPEAndDSNode65538_0OutputPortDescriptors}, 3, {0, NULL}},
    {NULL, 65539, 0, {1, TestBPSWithIPEAndDS_BPSWithIPEAndDSNode65539_0InputPortDescriptors, 4, TestBPSWithIPEAndDS_BPSWithIPEAndDSNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestBPSWithIPEAndDS_BPSWithIPEAndDSLinks[] =
{
    {{65539, 0, 1, 0}, 1, TestBPSWithIPEAndDS_BPSWithIPEAndDS_Link0_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 4, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestBPSWithIPEAndDS_BPSWithIPEAndDS_Link1_IPE0_Out8Desc, {0}, {0, 0}},
    {{65539, 0, 2, 0}, 1, TestBPSWithIPEAndDS_BPSWithIPEAndDS_Link2_BPS0_Out2Desc, {ChiFormatPD10, 0, 4, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 3, 0}, 1, TestBPSWithIPEAndDS_BPSWithIPEAndDS_Link3_BPS0_Out3Desc, {ChiFormatPD10, 0, 4, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 4, 0}, 1, TestBPSWithIPEAndDS_BPSWithIPEAndDS_Link4_BPS0_Out4Desc, {ChiFormatPD10, 0, 4, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
};

enum TestBPSWithIPEAndDSPipelineIds
{
    BPSWithIPEAndDS = 0,
};

static ChiPipelineTargetCreateDescriptor TestBPSWithIPEAndDS_pipelines[] =
{
    {"BPSWithIPEAndDS", { 0, 2, TestBPSWithIPEAndDS_BPSWithIPEAndDSNodes, 5, TestBPSWithIPEAndDS_BPSWithIPEAndDSLinks, 0}, {1, TestBPSWithIPEAndDS_BPSWithIPEAndDS_sink_TargetDescriptors}, {1, TestBPSWithIPEAndDS_BPSWithIPEAndDS_source_TargetDescriptors}},  // BPSWithIPEAndDS
};

/*==================== USECASE: TestBPSIdealRaw =======================*/

static ChiBufferFormat TestBPSIdealRaw_TARGET_BUFFER_RAW_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiBufferFormat TestBPSIdealRaw_TARGET_BUFFER_IDEAL_RAW_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiTarget TestBPSIdealRaw_TARGET_BUFFER_RAW_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4608, 2592
    },
    2,
    TestBPSIdealRaw_TARGET_BUFFER_RAW_formats,
    NULL
}; // TARGET_BUFFER_RAW

static ChiTarget TestBPSIdealRaw_TARGET_BUFFER_IDEAL_RAW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4608, 2592
    },
    2,
    TestBPSIdealRaw_TARGET_BUFFER_IDEAL_RAW_formats,
    NULL
}; // TARGET_BUFFER_IDEAL_RAW

static ChiTarget* TestBPSIdealRaw_Targets[] =
{
	&TestBPSIdealRaw_TARGET_BUFFER_RAW_target,
	&TestBPSIdealRaw_TARGET_BUFFER_IDEAL_RAW_target
};

/*****************************Pipeline BPSIdealRaw***************************/

static ChiLinkNodeDescriptor TestBPSIdealRaw_BPSIdealRaw_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor __54_TARGET_BUFFER_IDEAL_RAW_Link_NodeDescriptors[] =
{
    {65539, 0, 2 }, 
};
static ChiLinkNodeDescriptor TestBPSIdealRaw_BPSIdealRaw_Link0_BPS0_Out2Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_IDEAL_RAW
};

static ChiTargetPortDescriptor TestBPSIdealRaw_BPSIdealRaw_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_IDEAL_RAW", &TestBPSIdealRaw_TARGET_BUFFER_IDEAL_RAW_target, 1, __54_TARGET_BUFFER_IDEAL_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_IDEAL_RAW
};

static ChiTargetPortDescriptor TestBPSIdealRaw_BPSIdealRaw_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &TestBPSIdealRaw_TARGET_BUFFER_RAW_target, 1, TestBPSIdealRaw_BPSIdealRaw_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor TestBPSIdealRaw_BPSIdealRawNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor TestBPSIdealRaw_BPSIdealRawNode65539_0OutputPortDescriptors[] =
{
    {2, 1, 1, 0, 0, NULL}, // BPSOutputPortDS4
};

static ChiNodeProperty TestBPSIdealRaw_BPSIdealRaw_node65539_0_properties[] =
{
    {2, "5"},
};

static ChiNode TestBPSIdealRaw_BPSIdealRawNodes[] =
{
    {TestBPSIdealRaw_BPSIdealRaw_node65539_0_properties, 65539, 0, {1, TestBPSIdealRaw_BPSIdealRawNode65539_0InputPortDescriptors, 1, TestBPSIdealRaw_BPSIdealRawNode65539_0OutputPortDescriptors}, 1, {0, NULL}},
};

static ChiNodeLink TestBPSIdealRaw_BPSIdealRawLinks[] =
{
    {{65539, 0, 2, 0}, 1, TestBPSIdealRaw_BPSIdealRaw_Link0_BPS0_Out2Desc, {0}, {0, 0}},
};

enum TestBPSIdealRawPipelineIds
{
    BPSIdealRaw = 0,
};

static ChiPipelineTargetCreateDescriptor TestBPSIdealRaw_pipelines[] =
{
    {"BPSIdealRaw", { 0, 1, TestBPSIdealRaw_BPSIdealRawNodes, 1, TestBPSIdealRaw_BPSIdealRawLinks, 0}, {1, TestBPSIdealRaw_BPSIdealRaw_sink_TargetDescriptors}, {1, TestBPSIdealRaw_BPSIdealRaw_source_TargetDescriptors}},  // BPSIdealRaw
};

/*==================== USECASE: TestChiDepth =======================*/

static ChiBufferFormat TestChiDepth_TARGET_BUFFER_RAW_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiBufferFormat TestChiDepth_TARGET_BUFFER_DEPTH_formats[] =
{
    ChiFormatBlob,
    ChiFormatY16,
    ChiFormatY8,
};

static ChiTarget TestChiDepth_TARGET_BUFFER_RAW_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4608, 2592
    },
    2,
    TestChiDepth_TARGET_BUFFER_RAW_formats,
    NULL
}; // TARGET_BUFFER_RAW

static ChiTarget TestChiDepth_TARGET_BUFFER_DEPTH_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 5488, 4112
    },
    3,
    TestChiDepth_TARGET_BUFFER_DEPTH_formats,
    NULL
}; // TARGET_BUFFER_DEPTH

static ChiTarget* TestChiDepth_Targets[] =
{
	&TestChiDepth_TARGET_BUFFER_RAW_target,
	&TestChiDepth_TARGET_BUFFER_DEPTH_target
};

/*****************************Pipeline ChiDepthNode***************************/

static ChiLinkNodeDescriptor TestChiDepth_ChiDepthNode_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestChiDepth_ChiDepthNode_Link1_IFE0_Out8Desc[] =
{
    {255, 0, 0, 0, {0, NULL}}, // ChiDepthNode
};

static ChiLinkNodeDescriptor __55_TARGET_BUFFER_DEPTH_Link_NodeDescriptors[] =
{
    {255, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestChiDepth_ChiDepthNode_Link2_ChiDepthNode0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_DEPTH
};

static ChiTargetPortDescriptor TestChiDepth_ChiDepthNode_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_DEPTH", &TestChiDepth_TARGET_BUFFER_DEPTH_target, 1, __55_TARGET_BUFFER_DEPTH_Link_NodeDescriptors}, // TARGET_BUFFER_DEPTH
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestChiDepth_ChiDepthNodeNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// ChiDepthNode0 Input Port Descriptors
static ChiInputPortDescriptor TestChiDepth_ChiDepthNodeNode255_0InputPortDescriptors[] =
{
    {0, 0, 0}, // ChiNodeInputPort0
};

// ChiDepthNode0 Output Port Descriptors
static ChiOutputPortDescriptor TestChiDepth_ChiDepthNodeNode255_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // ChiNodeOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestChiDepth_ChiDepthNodeNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestChiDepth_ChiDepthNodeNode65536_0OutputPortDescriptors[] =
{
    {8, 0, 0, 0, 0, NULL}, // IFEOutputPortRDI0
};

static ChiNodeProperty TestChiDepth_ChiDepthNode_node255_0_properties[] =
{
    {1, "com.qti.node.depth"},
};

static ChiNode TestChiDepth_ChiDepthNodeNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestChiDepth_ChiDepthNodeNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestChiDepth_ChiDepthNode_node255_0_properties, 255, 0, {1, TestChiDepth_ChiDepthNodeNode255_0InputPortDescriptors, 1, TestChiDepth_ChiDepthNodeNode255_0OutputPortDescriptors}, 1, {0, NULL}},
    {NULL, 65536, 0, {1, TestChiDepth_ChiDepthNodeNode65536_0InputPortDescriptors, 1, TestChiDepth_ChiDepthNodeNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestChiDepth_ChiDepthNodeLinks[] =
{
    {{0, 0, 0, 0}, 1, TestChiDepth_ChiDepthNode_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 8, 0}, 1, TestChiDepth_ChiDepthNode_Link1_IFE0_Out8Desc, {ChiFormatRawMIPI, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{255, 0, 0, 0}, 1, TestChiDepth_ChiDepthNode_Link2_ChiDepthNode0_Out0Desc, {0}, {0, 0}},
};

/*****************************Pipeline DepthNodeOffline***************************/

static ChiLinkNodeDescriptor TestChiDepth_DepthNodeOffline_source_Link_0NodeDescriptors[] =
{
    {255, 0, 0},
};
static ChiLinkNodeDescriptor __56_TARGET_BUFFER_DEPTH_Link_NodeDescriptors[] =
{
    {255, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestChiDepth_DepthNodeOffline_Link0_ChiDepthNode0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_DEPTH
};

static ChiTargetPortDescriptor TestChiDepth_DepthNodeOffline_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_DEPTH", &TestChiDepth_TARGET_BUFFER_DEPTH_target, 1, __56_TARGET_BUFFER_DEPTH_Link_NodeDescriptors}, // TARGET_BUFFER_DEPTH
};

static ChiTargetPortDescriptor TestChiDepth_DepthNodeOffline_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &TestChiDepth_TARGET_BUFFER_RAW_target, 1, TestChiDepth_DepthNodeOffline_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW
};

// ChiDepthNode0 Input Port Descriptors
static ChiInputPortDescriptor TestChiDepth_DepthNodeOfflineNode255_0InputPortDescriptors[] =
{
    {0, 1, 0}, // ChiNodeInputPort0
};

// ChiDepthNode0 Output Port Descriptors
static ChiOutputPortDescriptor TestChiDepth_DepthNodeOfflineNode255_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // ChiNodeOutputPort0
};

static ChiNodeProperty TestChiDepth_DepthNodeOffline_node255_0_properties[] =
{
    {1, "com.qti.node.depth"},
};

static ChiNode TestChiDepth_DepthNodeOfflineNodes[] =
{
    {TestChiDepth_DepthNodeOffline_node255_0_properties, 255, 0, {1, TestChiDepth_DepthNodeOfflineNode255_0InputPortDescriptors, 1, TestChiDepth_DepthNodeOfflineNode255_0OutputPortDescriptors}, 1, {0, NULL}},
};

static ChiNodeLink TestChiDepth_DepthNodeOfflineLinks[] =
{
    {{255, 0, 0, 0}, 1, TestChiDepth_DepthNodeOffline_Link0_ChiDepthNode0_Out0Desc, {0}, {0, 0}},
};

enum TestChiDepthPipelineIds
{
    ChiDepthNode = 0,
    DepthNodeOffline = 1,
};

static ChiPipelineTargetCreateDescriptor TestChiDepth_pipelines[] =
{
    {"ChiDepthNode", { 0, 3, TestChiDepth_ChiDepthNodeNodes, 3, TestChiDepth_ChiDepthNodeLinks, 1}, {1, TestChiDepth_ChiDepthNode_sink_TargetDescriptors}, {0, NULL}},  // ChiDepthNode
    {"DepthNodeOffline", { 0, 1, TestChiDepth_DepthNodeOfflineNodes, 1, TestChiDepth_DepthNodeOfflineLinks, 0}, {1, TestChiDepth_DepthNodeOffline_sink_TargetDescriptors}, {1, TestChiDepth_DepthNodeOffline_source_TargetDescriptors}},  // DepthNodeOffline
};

/*==================== USECASE: UsecaseChiGPUNode =======================*/

static ChiBufferFormat UsecaseChiGPUNode_TARGET_BUFFER_INPUT_formats[] =
{
    ChiFormatP010,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat UsecaseChiGPUNode_TARGET_BUFFER_OUTPUT_formats[] =
{
    ChiFormatP010,
    ChiFormatYUV420NV12,
};

static ChiTarget UsecaseChiGPUNode_TARGET_BUFFER_INPUT_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    2,
    UsecaseChiGPUNode_TARGET_BUFFER_INPUT_formats,
    NULL
}; // TARGET_BUFFER_INPUT

static ChiTarget UsecaseChiGPUNode_TARGET_BUFFER_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    2,
    UsecaseChiGPUNode_TARGET_BUFFER_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_OUTPUT

static ChiTarget* UsecaseChiGPUNode_Targets[] =
{
	&UsecaseChiGPUNode_TARGET_BUFFER_INPUT_target,
	&UsecaseChiGPUNode_TARGET_BUFFER_OUTPUT_target
};

/*****************************Pipeline TestChiGPUNode***************************/

static ChiLinkNodeDescriptor UsecaseChiGPUNode_TestChiGPUNode_source_Link_0NodeDescriptors[] =
{
    {255, 0, 0},
};
static ChiLinkNodeDescriptor __57_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {255, 0, 0 }, 
};
static ChiLinkNodeDescriptor UsecaseChiGPUNode_TestChiGPUNode_Link0_ChiGPUNode0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiTargetPortDescriptor UsecaseChiGPUNode_TestChiGPUNode_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &UsecaseChiGPUNode_TARGET_BUFFER_OUTPUT_target, 1, __57_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
};

static ChiTargetPortDescriptor UsecaseChiGPUNode_TestChiGPUNode_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_INPUT", &UsecaseChiGPUNode_TARGET_BUFFER_INPUT_target, 1, UsecaseChiGPUNode_TestChiGPUNode_source_Link_0NodeDescriptors}, // TARGET_BUFFER_INPUT
};

// ChiGPUNode0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseChiGPUNode_TestChiGPUNodeNode255_0InputPortDescriptors[] =
{
    {0, 1, 0}, // ChiNodeInputPortFull
};

// ChiGPUNode0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseChiGPUNode_TestChiGPUNodeNode255_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // ChiNodeOutputPortFull
};

static ChiNodeProperty UsecaseChiGPUNode_TestChiGPUNode_node255_0_properties[] =
{
    {1, "com.qti.node.gpu"},
    {12, "8"},
};

static ChiNode UsecaseChiGPUNode_TestChiGPUNodeNodes[] =
{
    {UsecaseChiGPUNode_TestChiGPUNode_node255_0_properties, 255, 0, {1, UsecaseChiGPUNode_TestChiGPUNodeNode255_0InputPortDescriptors, 1, UsecaseChiGPUNode_TestChiGPUNodeNode255_0OutputPortDescriptors}, 2, {0, NULL}},
};

static ChiNodeLink UsecaseChiGPUNode_TestChiGPUNodeLinks[] =
{
    {{255, 0, 0, 0}, 1, UsecaseChiGPUNode_TestChiGPUNode_Link0_ChiGPUNode0_Out0Desc, {0}, {0, 0}},
};

enum UsecaseChiGPUNodePipelineIds
{
    TestChiGPUNode = 0,
};

static ChiPipelineTargetCreateDescriptor UsecaseChiGPUNode_pipelines[] =
{
    {"TestChiGPUNode", { 0, 1, UsecaseChiGPUNode_TestChiGPUNodeNodes, 1, UsecaseChiGPUNode_TestChiGPUNodeLinks, 0}, {1, UsecaseChiGPUNode_TestChiGPUNode_sink_TargetDescriptors}, {1, UsecaseChiGPUNode_TestChiGPUNode_source_TargetDescriptors}},  // TestChiGPUNode
};

/*==================== USECASE: RealtimeNodesTest =======================*/

static ChiBufferFormat RealtimeNodesTest_TARGET_BUFFER_PREVIEW_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat RealtimeNodesTest_TARGET_BUFFER_SNAPSHOT_formats[] =
{
    ChiFormatJpeg,
    ChiFormatYUV420NV12,
};

static ChiTarget RealtimeNodesTest_TARGET_BUFFER_PREVIEW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    RealtimeNodesTest_TARGET_BUFFER_PREVIEW_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW

static ChiTarget RealtimeNodesTest_TARGET_BUFFER_SNAPSHOT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    2,
    RealtimeNodesTest_TARGET_BUFFER_SNAPSHOT_formats,
    NULL
}; // TARGET_BUFFER_SNAPSHOT

static ChiTarget* RealtimeNodesTest_Targets[] =
{
	&RealtimeNodesTest_TARGET_BUFFER_PREVIEW_target,
	&RealtimeNodesTest_TARGET_BUFFER_SNAPSHOT_target
};

/*****************************Pipeline SensorIFEIPEJpeg***************************/

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEIPEJpeg_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 0, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEIPEJpeg_Link1_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEIPEJpeg_Link2_IPE0_Out8Desc[] =
{
    {65537, 0, 0, 0, {0, NULL}}, // JPEG
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEIPEJpeg_Link3_JPEG0_Out1Desc[] =
{
    {6, 0, 0, 0, {0, NULL}}, // JPEGAggregator
};

static ChiLinkNodeDescriptor __58_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {6, 0, 2 }, 
};
static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEIPEJpeg_Link4_JPEGAggregator0_Out2Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor RealtimeNodesTest_SensorIFEIPEJpeg_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &RealtimeNodesTest_TARGET_BUFFER_SNAPSHOT_target, 1, __58_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEIPEJpegNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// JPEGAggregator0 Input Port Descriptors
static ChiInputPortDescriptor RealtimeNodesTest_SensorIFEIPEJpegNode6_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGAggregatorInputPort0
};

// JPEGAggregator0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEIPEJpegNode6_0OutputPortDescriptors[] =
{
    {2, 1, 1, 0, 0, NULL}, // JPEGAggregatorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor RealtimeNodesTest_SensorIFEIPEJpegNode65536_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IFEInputPortFull
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEIPEJpegNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
};

// JPEG0 Input Port Descriptors
static ChiInputPortDescriptor RealtimeNodesTest_SensorIFEIPEJpegNode65537_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGInputPort0
};

// JPEG0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEIPEJpegNode65537_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // JPEGOutputPort0
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor RealtimeNodesTest_SensorIFEIPEJpegNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEIPEJpegNode65538_0OutputPortDescriptors[] =
{
    {8, 0, 0, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNodeProperty RealtimeNodesTest_SensorIFEIPEJpeg_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlibwrapper"},
};

static ChiNodeProperty RealtimeNodesTest_SensorIFEIPEJpeg_node65536_0_properties[] =
{
    {6, "1"},
};

static ChiNode RealtimeNodesTest_SensorIFEIPEJpegNodes[] =
{
    {RealtimeNodesTest_SensorIFEIPEJpeg_node0_0_properties, 0, 0, {0, NULL, 1, RealtimeNodesTest_SensorIFEIPEJpegNode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {NULL, 6, 0, {1, RealtimeNodesTest_SensorIFEIPEJpegNode6_0InputPortDescriptors, 1, RealtimeNodesTest_SensorIFEIPEJpegNode6_0OutputPortDescriptors}, 0, {0, NULL}},
    {RealtimeNodesTest_SensorIFEIPEJpeg_node65536_0_properties, 65536, 0, {1, RealtimeNodesTest_SensorIFEIPEJpegNode65536_0InputPortDescriptors, 1, RealtimeNodesTest_SensorIFEIPEJpegNode65536_0OutputPortDescriptors}, 1, {0, NULL}},
    {NULL, 65537, 0, {1, RealtimeNodesTest_SensorIFEIPEJpegNode65537_0InputPortDescriptors, 1, RealtimeNodesTest_SensorIFEIPEJpegNode65537_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, RealtimeNodesTest_SensorIFEIPEJpegNode65538_0InputPortDescriptors, 1, RealtimeNodesTest_SensorIFEIPEJpegNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink RealtimeNodesTest_SensorIFEIPEJpegLinks[] =
{
    {{0, 0, 0, 0}, 1, RealtimeNodesTest_SensorIFEIPEJpeg_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, RealtimeNodesTest_SensorIFEIPEJpeg_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, RealtimeNodesTest_SensorIFEIPEJpeg_Link2_IPE0_Out8Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65537, 0, 1, 0}, 1, RealtimeNodesTest_SensorIFEIPEJpeg_Link3_JPEG0_Out1Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{6, 0, 2, 0}, 1, RealtimeNodesTest_SensorIFEIPEJpeg_Link4_JPEGAggregator0_Out2Desc, {0}, {0, 0}},
};

/*****************************Pipeline SensorIFEBPSIPEJpeg***************************/

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 3, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link1_IFE0_Out8Desc[] =
{
    {65539, 0, 0, 0, {0, NULL}}, // BPS
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link2_BPS0_Out2Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link3_BPS0_Out3Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link4_BPS0_Out4Desc[] =
{
    {65538, 0, 3, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link5_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link6_IPE0_Out8Desc[] =
{
    {65537, 0, 0, 0, {0, NULL}}, // JPEG
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link7_JPEG0_Out1Desc[] =
{
    {6, 0, 0, 0, {0, NULL}}, // JPEGAggregator
};

static ChiLinkNodeDescriptor __59_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {6, 0, 2 }, 
};
static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link8_JPEGAggregator0_Out2Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpeg_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &RealtimeNodesTest_TARGET_BUFFER_SNAPSHOT_target, 1, __59_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpegNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// JPEGAggregator0 Input Port Descriptors
static ChiInputPortDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpegNode6_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGAggregatorInputPort0
};

// JPEGAggregator0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpegNode6_0OutputPortDescriptors[] =
{
    {2, 1, 1, 0, 0, NULL}, // JPEGAggregatorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpegNode65536_0InputPortDescriptors[] =
{
    {3, 0, 0}, // IFEInputPortRDI0
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpegNode65536_0OutputPortDescriptors[] =
{
    {8, 0, 0, 0, 0, NULL}, // IFEOutputPortRDI0
};

// JPEG0 Input Port Descriptors
static ChiInputPortDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpegNode65537_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGInputPort0
};

// JPEG0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpegNode65537_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // JPEGOutputPort0
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpegNode65538_0InputPortDescriptors[] =
{
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
    {3, 0, 0}, // IPEInputPortDS64
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpegNode65538_0OutputPortDescriptors[] =
{
    {8, 0, 0, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpegNode65539_0InputPortDescriptors[] =
{
    {0, 0, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEBPSIPEJpegNode65539_0OutputPortDescriptors[] =
{
    {2, 0, 0, 0, 0, NULL}, // BPSOutputPortDS4
    {3, 0, 0, 0, 0, NULL}, // BPSOutputPortDS16
    {4, 0, 0, 0, 0, NULL}, // BPSOutputPortDS64
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
};

static ChiNodeProperty RealtimeNodesTest_SensorIFEBPSIPEJpeg_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlibwrapper"},
};

static ChiNodeProperty RealtimeNodesTest_SensorIFEBPSIPEJpeg_node65536_0_properties[] =
{
    {6, "1"},
};

static ChiNode RealtimeNodesTest_SensorIFEBPSIPEJpegNodes[] =
{
    {RealtimeNodesTest_SensorIFEBPSIPEJpeg_node0_0_properties, 0, 0, {0, NULL, 1, RealtimeNodesTest_SensorIFEBPSIPEJpegNode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {NULL, 6, 0, {1, RealtimeNodesTest_SensorIFEBPSIPEJpegNode6_0InputPortDescriptors, 1, RealtimeNodesTest_SensorIFEBPSIPEJpegNode6_0OutputPortDescriptors}, 0, {0, NULL}},
    {RealtimeNodesTest_SensorIFEBPSIPEJpeg_node65536_0_properties, 65536, 0, {1, RealtimeNodesTest_SensorIFEBPSIPEJpegNode65536_0InputPortDescriptors, 1, RealtimeNodesTest_SensorIFEBPSIPEJpegNode65536_0OutputPortDescriptors}, 1, {0, NULL}},
    {NULL, 65537, 0, {1, RealtimeNodesTest_SensorIFEBPSIPEJpegNode65537_0InputPortDescriptors, 1, RealtimeNodesTest_SensorIFEBPSIPEJpegNode65537_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {4, RealtimeNodesTest_SensorIFEBPSIPEJpegNode65538_0InputPortDescriptors, 1, RealtimeNodesTest_SensorIFEBPSIPEJpegNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, RealtimeNodesTest_SensorIFEBPSIPEJpegNode65539_0InputPortDescriptors, 4, RealtimeNodesTest_SensorIFEBPSIPEJpegNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink RealtimeNodesTest_SensorIFEBPSIPEJpegLinks[] =
{
    {{0, 0, 0, 0}, 1, RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 8, 0}, 1, RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link1_IFE0_Out8Desc, {ChiFormatRawMIPI, 0, 2, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 2, 0}, 1, RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link2_BPS0_Out2Desc, {ChiFormatPD10, 0, 1, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 3, 0}, 1, RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link3_BPS0_Out3Desc, {ChiFormatPD10, 0, 1, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 4, 0}, 1, RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link4_BPS0_Out4Desc, {ChiFormatPD10, 0, 1, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 1, 0}, 1, RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link5_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 1, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link6_IPE0_Out8Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65537, 0, 1, 0}, 1, RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link7_JPEG0_Out1Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{6, 0, 2, 0}, 1, RealtimeNodesTest_SensorIFEBPSIPEJpeg_Link8_JPEGAggregator0_Out2Desc, {0}, {0, 0}},
};

/*****************************Pipeline SensorIFEFD***************************/

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEFD_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEFD_Link1_IFE0_Out6Desc[] =
{
    {65540, 0, 0, 0, {0, NULL}}, // FDHw
    {8, 0, 3, 0, {0, NULL}}, // FDManager
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEFD_Link2_FDHw0_Out0Desc[] =
{
    {8, 0, 0, 0, {0, NULL}}, // FDManager
};

static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEFD_Link3_FDHw0_Out2Desc[] =
{
    {8, 0, 2, 0, {0, NULL}}, // FDManager
};

static ChiLinkNodeDescriptor __60_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {8, 0, 0 }, 
};
static ChiLinkNodeDescriptor RealtimeNodesTest_SensorIFEFD_Link4_FDManager0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor RealtimeNodesTest_SensorIFEFD_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &RealtimeNodesTest_TARGET_BUFFER_SNAPSHOT_target, 1, __60_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEFDNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor RealtimeNodesTest_SensorIFEFDNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEFDNode65536_0OutputPortDescriptors[] =
{
    {6, 0, 0, 0, 0, NULL}, // IFEOutputPortFD
};

// FDHw0 Input Port Descriptors
static ChiInputPortDescriptor RealtimeNodesTest_SensorIFEFDNode65540_0InputPortDescriptors[] =
{
    {0, 0, 0}, // FDHwInputPortImage
};

// FDHw0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEFDNode65540_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // FDHwOutputPortResults
    {2, 0, 0, 0, 0, NULL}, // FDHwOutputPortWorkBuffer
};

// FDManager0 Input Port Descriptors
static ChiInputPortDescriptor RealtimeNodesTest_SensorIFEFDNode8_0InputPortDescriptors[] =
{
    {3, 0, 0}, // FDManagerInputPortImage
    {0, 0, 0}, // FDManagerInputPortHwResults
    {2, 0, 0}, // FDManagerInputPortHwPyramidBuffer
};

// FDManager0 Output Port Descriptors
static ChiOutputPortDescriptor RealtimeNodesTest_SensorIFEFDNode8_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // FDManagerOutputPortResults
};

static ChiNodeProperty RealtimeNodesTest_SensorIFEFD_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlibwrapper"},
};

static ChiNodeProperty RealtimeNodesTest_SensorIFEFD_node65536_0_properties[] =
{
    {6, "1"},
};

static ChiNode RealtimeNodesTest_SensorIFEFDNodes[] =
{
    {RealtimeNodesTest_SensorIFEFD_node0_0_properties, 0, 0, {0, NULL, 1, RealtimeNodesTest_SensorIFEFDNode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {RealtimeNodesTest_SensorIFEFD_node65536_0_properties, 65536, 0, {1, RealtimeNodesTest_SensorIFEFDNode65536_0InputPortDescriptors, 1, RealtimeNodesTest_SensorIFEFDNode65536_0OutputPortDescriptors}, 1, {0, NULL}},
    {NULL, 65540, 0, {1, RealtimeNodesTest_SensorIFEFDNode65540_0InputPortDescriptors, 2, RealtimeNodesTest_SensorIFEFDNode65540_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 8, 0, {3, RealtimeNodesTest_SensorIFEFDNode8_0InputPortDescriptors, 1, RealtimeNodesTest_SensorIFEFDNode8_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink RealtimeNodesTest_SensorIFEFDLinks[] =
{
    {{0, 0, 0, 0}, 1, RealtimeNodesTest_SensorIFEFD_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 6, 0}, 2, RealtimeNodesTest_SensorIFEFD_Link1_IFE0_Out6Desc, {ChiFormatYUV420NV12, 0, 8, 12, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{65540, 0, 0, 0}, 1, RealtimeNodesTest_SensorIFEFD_Link2_FDHw0_Out0Desc, {ChiFormatBlob, 16384, 8, 12, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65540, 0, 2, 0}, 1, RealtimeNodesTest_SensorIFEFD_Link3_FDHw0_Out2Desc, {ChiFormatBlob, 218496, 6, 12, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{8, 0, 0, 0}, 1, RealtimeNodesTest_SensorIFEFD_Link4_FDManager0_Out0Desc, {0}, {0, 0}},
};

enum RealtimeNodesTestPipelineIds
{
    SensorIFEIPEJpeg = 0,
    SensorIFEBPSIPEJpeg = 1,
    SensorIFEFD = 2,
};

static ChiPipelineTargetCreateDescriptor RealtimeNodesTest_pipelines[] =
{
    {"SensorIFEIPEJpeg", { 0, 5, RealtimeNodesTest_SensorIFEIPEJpegNodes, 5, RealtimeNodesTest_SensorIFEIPEJpegLinks, 1}, {1, RealtimeNodesTest_SensorIFEIPEJpeg_sink_TargetDescriptors}, {0, NULL}},  // SensorIFEIPEJpeg
    {"SensorIFEBPSIPEJpeg", { 0, 6, RealtimeNodesTest_SensorIFEBPSIPEJpegNodes, 9, RealtimeNodesTest_SensorIFEBPSIPEJpegLinks, 1}, {1, RealtimeNodesTest_SensorIFEBPSIPEJpeg_sink_TargetDescriptors}, {0, NULL}},  // SensorIFEBPSIPEJpeg
    {"SensorIFEFD", { 0, 4, RealtimeNodesTest_SensorIFEFDNodes, 5, RealtimeNodesTest_SensorIFEFDLinks, 1}, {1, RealtimeNodesTest_SensorIFEFD_sink_TargetDescriptors}, {0, NULL}},  // SensorIFEFD
};

/*==================== USECASE: UsecaseExternalNode =======================*/

static ChiBufferFormat UsecaseExternalNode_TARGET_BUFFER_RAW_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiBufferFormat UsecaseExternalNode_TARGET_BUFFER_SNAPSHOT_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget UsecaseExternalNode_TARGET_BUFFER_RAW_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4608, 2592
    },
    2,
    UsecaseExternalNode_TARGET_BUFFER_RAW_formats,
    NULL
}; // TARGET_BUFFER_RAW

static ChiTarget UsecaseExternalNode_TARGET_BUFFER_SNAPSHOT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4608, 2592
    },
    3,
    UsecaseExternalNode_TARGET_BUFFER_SNAPSHOT_formats,
    NULL
}; // TARGET_BUFFER_SNAPSHOT

static ChiTarget* UsecaseExternalNode_Targets[] =
{
	&UsecaseExternalNode_TARGET_BUFFER_RAW_target,
	&UsecaseExternalNode_TARGET_BUFFER_SNAPSHOT_target
};

/*****************************Pipeline OfflineExtBPSIPE***************************/

static ChiLinkNodeDescriptor UsecaseExternalNode_OfflineExtBPSIPE_source_Link_0NodeDescriptors[] =
{
    {255, 0, 0},
};
static ChiLinkNodeDescriptor UsecaseExternalNode_OfflineExtBPSIPE_Link0_ChiExternalNode0_Out0Desc[] =
{
    {65539, 0, 0, 0, {0, NULL}}, // BPS
};

static ChiLinkNodeDescriptor UsecaseExternalNode_OfflineExtBPSIPE_Link1_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __61_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor UsecaseExternalNode_OfflineExtBPSIPE_Link2_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor UsecaseExternalNode_OfflineExtBPSIPE_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &UsecaseExternalNode_TARGET_BUFFER_SNAPSHOT_target, 1, __61_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor UsecaseExternalNode_OfflineExtBPSIPE_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &UsecaseExternalNode_TARGET_BUFFER_RAW_target, 1, UsecaseExternalNode_OfflineExtBPSIPE_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW
};

// ChiExternalNode0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPENode255_0InputPortDescriptors[] =
{
    {0, 1, 0}, // ChiNodeInputPort0
};

// ChiExternalNode0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPENode255_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // ChiNodeOutputPort0
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPENode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPENode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPENode65539_0InputPortDescriptors[] =
{
    {0, 0, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPENode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
};

static ChiNodeProperty UsecaseExternalNode_OfflineExtBPSIPE_node255_0_properties[] =
{
    {1, "com.qti.node.memcpy"},
    {9, "0"},
};

static ChiNode UsecaseExternalNode_OfflineExtBPSIPENodes[] =
{
    {UsecaseExternalNode_OfflineExtBPSIPE_node255_0_properties, 255, 0, {1, UsecaseExternalNode_OfflineExtBPSIPENode255_0InputPortDescriptors, 1, UsecaseExternalNode_OfflineExtBPSIPENode255_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65538, 0, {1, UsecaseExternalNode_OfflineExtBPSIPENode65538_0InputPortDescriptors, 1, UsecaseExternalNode_OfflineExtBPSIPENode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, UsecaseExternalNode_OfflineExtBPSIPENode65539_0InputPortDescriptors, 1, UsecaseExternalNode_OfflineExtBPSIPENode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseExternalNode_OfflineExtBPSIPELinks[] =
{
    {{255, 0, 0, 0}, 1, UsecaseExternalNode_OfflineExtBPSIPE_Link0_ChiExternalNode0_Out0Desc, {ChiFormatRawPlain16, 307200, 10, 10, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{65539, 0, 1, 0}, 1, UsecaseExternalNode_OfflineExtBPSIPE_Link1_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, UsecaseExternalNode_OfflineExtBPSIPE_Link2_IPE0_Out8Desc, {0}, {0, 0}},
};

/*****************************Pipeline OfflineExtBPSIPEJPEG***************************/

static ChiLinkNodeDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEG_source_Link_0NodeDescriptors[] =
{
    {255, 0, 0},
};
static ChiLinkNodeDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEG_Link0_ChiExternalNode0_Out0Desc[] =
{
    {65539, 0, 0, 0, {0, NULL}}, // BPS
};

static ChiLinkNodeDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEG_Link1_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEG_Link2_IPE0_Out8Desc[] =
{
    {65537, 0, 0, 0, {0, NULL}}, // JPEG
};

static ChiLinkNodeDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEG_Link3_JPEG0_Out1Desc[] =
{
    {6, 0, 0, 0, {0, NULL}}, // JPEGAggregator
};

static ChiLinkNodeDescriptor __62_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {6, 0, 2 }, 
};
static ChiLinkNodeDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEG_Link4_JPEGAggregator0_Out2Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEG_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &UsecaseExternalNode_TARGET_BUFFER_SNAPSHOT_target, 1, __62_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEG_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &UsecaseExternalNode_TARGET_BUFFER_RAW_target, 1, UsecaseExternalNode_OfflineExtBPSIPEJPEG_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW
};

// ChiExternalNode0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEGNode255_0InputPortDescriptors[] =
{
    {0, 1, 0}, // ChiNodeInputPort0
};

// ChiExternalNode0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEGNode255_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // ChiNodeOutputPort0
};

// JPEGAggregator0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEGNode6_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGAggregatorInputPort0
};

// JPEGAggregator0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEGNode6_0OutputPortDescriptors[] =
{
    {2, 1, 1, 0, 0, NULL}, // JPEGAggregatorOutputPort0
};

// JPEG0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEGNode65537_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGInputPort0
};

// JPEG0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEGNode65537_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // JPEGOutputPort0
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEGNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEGNode65538_0OutputPortDescriptors[] =
{
    {8, 0, 0, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEGNode65539_0InputPortDescriptors[] =
{
    {0, 0, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseExternalNode_OfflineExtBPSIPEJPEGNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
};

static ChiNodeProperty UsecaseExternalNode_OfflineExtBPSIPEJPEG_node255_0_properties[] =
{
    {1, "com.qti.node.memcpy"},
    {9, "0"},
};

static ChiNode UsecaseExternalNode_OfflineExtBPSIPEJPEGNodes[] =
{
    {UsecaseExternalNode_OfflineExtBPSIPEJPEG_node255_0_properties, 255, 0, {1, UsecaseExternalNode_OfflineExtBPSIPEJPEGNode255_0InputPortDescriptors, 1, UsecaseExternalNode_OfflineExtBPSIPEJPEGNode255_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 6, 0, {1, UsecaseExternalNode_OfflineExtBPSIPEJPEGNode6_0InputPortDescriptors, 1, UsecaseExternalNode_OfflineExtBPSIPEJPEGNode6_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65537, 0, {1, UsecaseExternalNode_OfflineExtBPSIPEJPEGNode65537_0InputPortDescriptors, 1, UsecaseExternalNode_OfflineExtBPSIPEJPEGNode65537_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, UsecaseExternalNode_OfflineExtBPSIPEJPEGNode65538_0InputPortDescriptors, 1, UsecaseExternalNode_OfflineExtBPSIPEJPEGNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, UsecaseExternalNode_OfflineExtBPSIPEJPEGNode65539_0InputPortDescriptors, 1, UsecaseExternalNode_OfflineExtBPSIPEJPEGNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseExternalNode_OfflineExtBPSIPEJPEGLinks[] =
{
    {{255, 0, 0, 0}, 1, UsecaseExternalNode_OfflineExtBPSIPEJPEG_Link0_ChiExternalNode0_Out0Desc, {ChiFormatRawPlain16, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65539, 0, 1, 0}, 1, UsecaseExternalNode_OfflineExtBPSIPEJPEG_Link1_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 1, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, UsecaseExternalNode_OfflineExtBPSIPEJPEG_Link2_IPE0_Out8Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65537, 0, 1, 0}, 1, UsecaseExternalNode_OfflineExtBPSIPEJPEG_Link3_JPEG0_Out1Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{6, 0, 2, 0}, 1, UsecaseExternalNode_OfflineExtBPSIPEJPEG_Link4_JPEGAggregator0_Out2Desc, {0}, {0, 0}},
};

enum UsecaseExternalNodePipelineIds
{
    OfflineExtBPSIPE = 0,
    OfflineExtBPSIPEJPEG = 1,
};

static ChiPipelineTargetCreateDescriptor UsecaseExternalNode_pipelines[] =
{
    {"OfflineExtBPSIPE", { 0, 3, UsecaseExternalNode_OfflineExtBPSIPENodes, 3, UsecaseExternalNode_OfflineExtBPSIPELinks, 0}, {1, UsecaseExternalNode_OfflineExtBPSIPE_sink_TargetDescriptors}, {1, UsecaseExternalNode_OfflineExtBPSIPE_source_TargetDescriptors}},  // OfflineExtBPSIPE
    {"OfflineExtBPSIPEJPEG", { 0, 5, UsecaseExternalNode_OfflineExtBPSIPEJPEGNodes, 5, UsecaseExternalNode_OfflineExtBPSIPEJPEGLinks, 0}, {1, UsecaseExternalNode_OfflineExtBPSIPEJPEG_sink_TargetDescriptors}, {1, UsecaseExternalNode_OfflineExtBPSIPEJPEG_source_TargetDescriptors}},  // OfflineExtBPSIPEJPEG
};

/*==================== USECASE: UsecaseGeneric =======================*/

static ChiBufferFormat UsecaseGeneric_TARGET_BUFFER_INPUT_formats[] =
{
    ChiFormatBlob,
    ChiFormatJpeg,
    ChiFormatP010,
    ChiFormatPD10,
    ChiFormatRawDepth,
    ChiFormatRawMIPI,
    ChiFormatRawMIPI8,
    ChiFormatRawMeta8BIT,
    ChiFormatRawPlain16,
    ChiFormatRawPlain64,
    ChiFormatRawPrivate,
    ChiFormatRawYUV8BIT,
    ChiFormatUBWCNV12,
    ChiFormatUBWCNV124R,
    ChiFormatUBWCTP10,
    ChiFormatY16,
    ChiFormatY8,
    ChiFormatYUV420NV12,
    ChiFormatYUV420NV12TP10,
    ChiFormatYUV420NV16,
    ChiFormatYUV420NV21,
    ChiFormatYUV420NV21TP10,
    ChiFormatYUV422NV16TP10,
};

static ChiBufferFormat UsecaseGeneric_TARGET_BUFFER_CONFIG_OUTPUT_formats[] =
{
    ChiFormatBlob,
    ChiFormatJpeg,
    ChiFormatP010,
    ChiFormatPD10,
    ChiFormatRawDepth,
    ChiFormatRawMIPI,
    ChiFormatRawMIPI8,
    ChiFormatRawMeta8BIT,
    ChiFormatRawPlain16,
    ChiFormatRawPlain64,
    ChiFormatRawPrivate,
    ChiFormatRawYUV8BIT,
    ChiFormatUBWCNV12,
    ChiFormatUBWCNV124R,
    ChiFormatUBWCTP10,
    ChiFormatY16,
    ChiFormatY8,
    ChiFormatYUV420NV12,
    ChiFormatYUV420NV12TP10,
    ChiFormatYUV420NV16,
    ChiFormatYUV420NV21,
    ChiFormatYUV420NV21TP10,
    ChiFormatYUV422NV16TP10,
};

static ChiTarget UsecaseGeneric_TARGET_BUFFER_INPUT_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    23,
    UsecaseGeneric_TARGET_BUFFER_INPUT_formats,
    NULL
}; // TARGET_BUFFER_INPUT

static ChiTarget UsecaseGeneric_TARGET_BUFFER_CONFIG_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    23,
    UsecaseGeneric_TARGET_BUFFER_CONFIG_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_CONFIG_OUTPUT

static ChiTarget* UsecaseGeneric_Targets[] =
{
	&UsecaseGeneric_TARGET_BUFFER_INPUT_target,
	&UsecaseGeneric_TARGET_BUFFER_CONFIG_OUTPUT_target
};

/*****************************Pipeline IFEGeneric***************************/

static ChiLinkNodeDescriptor UsecaseGeneric_IFEGeneric_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __63_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 0 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric_IFEGeneric_Link1_IFE0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric_IFEGeneric_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseGeneric_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __63_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric_IFEGenericNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseGeneric_IFEGenericNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric_IFEGenericNode65536_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // IFEOutputPortFull
};

static ChiNode UsecaseGeneric_IFEGenericNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, UsecaseGeneric_IFEGenericNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, UsecaseGeneric_IFEGenericNode65536_0InputPortDescriptors, 1, UsecaseGeneric_IFEGenericNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseGeneric_IFEGenericLinks[] =
{
    {{0, 0, 0, 0}, 1, UsecaseGeneric_IFEGeneric_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, UsecaseGeneric_IFEGeneric_Link1_IFE0_Out0Desc, {0}, {0, 0}},
};

/*****************************Pipeline IFEGenericTestgen***************************/

static ChiLinkNodeDescriptor __64_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 0 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric_IFEGenericTestgen_Link0_IFE0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric_IFEGenericTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseGeneric_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __64_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric_IFEGenericTestgenNode65536_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // IFEOutputPortFull
};

static ChiNode UsecaseGeneric_IFEGenericTestgenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 1, UsecaseGeneric_IFEGenericTestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseGeneric_IFEGenericTestgenLinks[] =
{
    {{65536, 0, 0, 0}, 1, UsecaseGeneric_IFEGenericTestgen_Link0_IFE0_Out0Desc, {0}, {0, 0}},
};

/*****************************Pipeline IPEGeneric***************************/

static ChiLinkNodeDescriptor UsecaseGeneric_IPEGeneric_source_Link_0NodeDescriptors[] =
{
    {65538, 0, 0},
};
static ChiLinkNodeDescriptor __65_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric_IPEGeneric_Link0_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric_IPEGeneric_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseGeneric_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __65_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric_IPEGeneric_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_INPUT", &UsecaseGeneric_TARGET_BUFFER_INPUT_target, 1, UsecaseGeneric_IPEGeneric_source_Link_0NodeDescriptors}, // TARGET_BUFFER_INPUT
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseGeneric_IPEGenericNode65538_0InputPortDescriptors[] =
{
    {0, 1, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric_IPEGenericNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNode UsecaseGeneric_IPEGenericNodes[] =
{
    {NULL, 65538, 0, {1, UsecaseGeneric_IPEGenericNode65538_0InputPortDescriptors, 1, UsecaseGeneric_IPEGenericNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseGeneric_IPEGenericLinks[] =
{
    {{65538, 0, 8, 0}, 1, UsecaseGeneric_IPEGeneric_Link0_IPE0_Out8Desc, {0}, {0, 0}},
};

/*****************************Pipeline BPSGeneric***************************/

static ChiLinkNodeDescriptor UsecaseGeneric_BPSGeneric_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor __66_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65539, 0, 1 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric_BPSGeneric_Link0_BPS0_Out1Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric_BPSGeneric_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseGeneric_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __66_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric_BPSGeneric_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_INPUT", &UsecaseGeneric_TARGET_BUFFER_INPUT_target, 1, UsecaseGeneric_BPSGeneric_source_Link_0NodeDescriptors}, // TARGET_BUFFER_INPUT
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseGeneric_BPSGenericNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric_BPSGenericNode65539_0OutputPortDescriptors[] =
{
    {1, 1, 1, 0, 0, NULL}, // BPSOutputPortFull
};

static ChiNode UsecaseGeneric_BPSGenericNodes[] =
{
    {NULL, 65539, 0, {1, UsecaseGeneric_BPSGenericNode65539_0InputPortDescriptors, 1, UsecaseGeneric_BPSGenericNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseGeneric_BPSGenericLinks[] =
{
    {{65539, 0, 1, 0}, 1, UsecaseGeneric_BPSGeneric_Link0_BPS0_Out1Desc, {0}, {0, 0}},
};

enum UsecaseGenericPipelineIds
{
    IFEGeneric = 0,
    IFEGenericTestgen = 1,
    IPEGeneric = 2,
    BPSGeneric = 3,
};

static ChiPipelineTargetCreateDescriptor UsecaseGeneric_pipelines[] =
{
    {"IFEGeneric", { 0, 2, UsecaseGeneric_IFEGenericNodes, 2, UsecaseGeneric_IFEGenericLinks, 1}, {1, UsecaseGeneric_IFEGeneric_sink_TargetDescriptors}, {0, NULL}},  // IFEGeneric
    {"IFEGenericTestgen", { 0, 1, UsecaseGeneric_IFEGenericTestgenNodes, 1, UsecaseGeneric_IFEGenericTestgenLinks, 1}, {1, UsecaseGeneric_IFEGenericTestgen_sink_TargetDescriptors}, {0, NULL}},  // IFEGenericTestgen
    {"IPEGeneric", { 0, 1, UsecaseGeneric_IPEGenericNodes, 1, UsecaseGeneric_IPEGenericLinks, 0}, {1, UsecaseGeneric_IPEGeneric_sink_TargetDescriptors}, {1, UsecaseGeneric_IPEGeneric_source_TargetDescriptors}},  // IPEGeneric
    {"BPSGeneric", { 0, 1, UsecaseGeneric_BPSGenericNodes, 1, UsecaseGeneric_BPSGenericLinks, 0}, {1, UsecaseGeneric_BPSGeneric_sink_TargetDescriptors}, {1, UsecaseGeneric_BPSGeneric_source_TargetDescriptors}},  // BPSGeneric
};

/*==================== USECASE: UsecaseGenericDownscale =======================*/

static ChiBufferFormat UsecaseGenericDownscale_TARGET_BUFFER_INPUT_formats[] =
{
    ChiFormatBlob,
    ChiFormatJpeg,
    ChiFormatP010,
    ChiFormatPD10,
    ChiFormatRawDepth,
    ChiFormatRawMIPI,
    ChiFormatRawMIPI8,
    ChiFormatRawMeta8BIT,
    ChiFormatRawPlain16,
    ChiFormatRawPlain64,
    ChiFormatRawPrivate,
    ChiFormatRawYUV8BIT,
    ChiFormatUBWCNV12,
    ChiFormatUBWCNV124R,
    ChiFormatUBWCTP10,
    ChiFormatY16,
    ChiFormatY8,
    ChiFormatYUV420NV12,
    ChiFormatYUV420NV12TP10,
    ChiFormatYUV420NV16,
    ChiFormatYUV420NV21,
    ChiFormatYUV420NV21TP10,
    ChiFormatYUV422NV16TP10,
};

static ChiBufferFormat UsecaseGenericDownscale_TARGET_BUFFER_OUTPUT_formats[] =
{
    ChiFormatBlob,
    ChiFormatJpeg,
    ChiFormatP010,
    ChiFormatPD10,
    ChiFormatRawDepth,
    ChiFormatRawMIPI,
    ChiFormatRawMIPI8,
    ChiFormatRawMeta8BIT,
    ChiFormatRawPlain16,
    ChiFormatRawPlain64,
    ChiFormatRawPrivate,
    ChiFormatRawYUV8BIT,
    ChiFormatUBWCNV12,
    ChiFormatUBWCNV124R,
    ChiFormatUBWCTP10,
    ChiFormatY16,
    ChiFormatY8,
    ChiFormatYUV420NV12,
    ChiFormatYUV420NV12TP10,
    ChiFormatYUV420NV16,
    ChiFormatYUV420NV21,
    ChiFormatYUV420NV21TP10,
    ChiFormatYUV422NV16TP10,
};

static ChiTarget UsecaseGenericDownscale_TARGET_BUFFER_INPUT_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    23,
    UsecaseGenericDownscale_TARGET_BUFFER_INPUT_formats,
    NULL
}; // TARGET_BUFFER_INPUT

static ChiTarget UsecaseGenericDownscale_TARGET_BUFFER_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    23,
    UsecaseGenericDownscale_TARGET_BUFFER_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_OUTPUT

static ChiTarget* UsecaseGenericDownscale_Targets[] =
{
	&UsecaseGenericDownscale_TARGET_BUFFER_INPUT_target,
	&UsecaseGenericDownscale_TARGET_BUFFER_OUTPUT_target
};

/*****************************Pipeline IFEGenericDownscaleTestgen***************************/

static ChiLinkNodeDescriptor __67_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 0 }, 
};
static ChiLinkNodeDescriptor UsecaseGenericDownscale_IFEGenericDownscaleTestgen_Link0_IFE0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __68_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 1 }, 
};
static ChiLinkNodeDescriptor UsecaseGenericDownscale_IFEGenericDownscaleTestgen_Link1_IFE0_Out1Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __69_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 2 }, 
};
static ChiLinkNodeDescriptor UsecaseGenericDownscale_IFEGenericDownscaleTestgen_Link2_IFE0_Out2Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGenericDownscale_IFEGenericDownscaleTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &UsecaseGenericDownscale_TARGET_BUFFER_OUTPUT_target, 1, __67_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &UsecaseGenericDownscale_TARGET_BUFFER_OUTPUT_target, 1, __68_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &UsecaseGenericDownscale_TARGET_BUFFER_OUTPUT_target, 1, __69_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGenericDownscale_IFEGenericDownscaleTestgenNode65536_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // IFEOutputPortFull
    {1, 1, 1, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 1, 1, 0, 0, NULL}, // IFEOutputPortDS16
};

static ChiNode UsecaseGenericDownscale_IFEGenericDownscaleTestgenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 3, UsecaseGenericDownscale_IFEGenericDownscaleTestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseGenericDownscale_IFEGenericDownscaleTestgenLinks[] =
{
    {{65536, 0, 0, 0}, 1, UsecaseGenericDownscale_IFEGenericDownscaleTestgen_Link0_IFE0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 1, 0}, 1, UsecaseGenericDownscale_IFEGenericDownscaleTestgen_Link1_IFE0_Out1Desc, {0}, {0, 0}},
    {{65536, 0, 2, 0}, 1, UsecaseGenericDownscale_IFEGenericDownscaleTestgen_Link2_IFE0_Out2Desc, {0}, {0, 0}},
};

/*****************************Pipeline BPSDownscaleGeneric***************************/

static ChiLinkNodeDescriptor UsecaseGenericDownscale_BPSDownscaleGeneric_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor __70_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65539, 0, 1 }, 
};
static ChiLinkNodeDescriptor UsecaseGenericDownscale_BPSDownscaleGeneric_Link0_BPS0_Out1Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __71_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65539, 0, 2 }, 
};
static ChiLinkNodeDescriptor UsecaseGenericDownscale_BPSDownscaleGeneric_Link1_BPS0_Out2Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __72_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65539, 0, 3 }, 
};
static ChiLinkNodeDescriptor UsecaseGenericDownscale_BPSDownscaleGeneric_Link2_BPS0_Out3Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __73_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65539, 0, 4 }, 
};
static ChiLinkNodeDescriptor UsecaseGenericDownscale_BPSDownscaleGeneric_Link3_BPS0_Out4Desc[] =
{
    {2, 3, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGenericDownscale_BPSDownscaleGeneric_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &UsecaseGenericDownscale_TARGET_BUFFER_OUTPUT_target, 1, __70_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &UsecaseGenericDownscale_TARGET_BUFFER_OUTPUT_target, 1, __71_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &UsecaseGenericDownscale_TARGET_BUFFER_OUTPUT_target, 1, __72_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &UsecaseGenericDownscale_TARGET_BUFFER_OUTPUT_target, 1, __73_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGenericDownscale_BPSDownscaleGeneric_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_INPUT", &UsecaseGenericDownscale_TARGET_BUFFER_INPUT_target, 1, UsecaseGenericDownscale_BPSDownscaleGeneric_source_Link_0NodeDescriptors}, // TARGET_BUFFER_INPUT
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseGenericDownscale_BPSDownscaleGenericNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGenericDownscale_BPSDownscaleGenericNode65539_0OutputPortDescriptors[] =
{
    {1, 1, 1, 0, 0, NULL}, // BPSOutputPortFull
    {2, 1, 1, 0, 0, NULL}, // BPSOutputPortDS4
    {3, 1, 1, 0, 0, NULL}, // BPSOutputPortDS16
    {4, 1, 1, 0, 0, NULL}, // BPSOutputPortDS64
};

static ChiNode UsecaseGenericDownscale_BPSDownscaleGenericNodes[] =
{
    {NULL, 65539, 0, {1, UsecaseGenericDownscale_BPSDownscaleGenericNode65539_0InputPortDescriptors, 4, UsecaseGenericDownscale_BPSDownscaleGenericNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseGenericDownscale_BPSDownscaleGenericLinks[] =
{
    {{65539, 0, 1, 0}, 1, UsecaseGenericDownscale_BPSDownscaleGeneric_Link0_BPS0_Out1Desc, {0}, {0, 0}},
    {{65539, 0, 2, 0}, 1, UsecaseGenericDownscale_BPSDownscaleGeneric_Link1_BPS0_Out2Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 3, 0}, 1, UsecaseGenericDownscale_BPSDownscaleGeneric_Link2_BPS0_Out3Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 4, 0}, 1, UsecaseGenericDownscale_BPSDownscaleGeneric_Link3_BPS0_Out4Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
};

enum UsecaseGenericDownscalePipelineIds
{
    IFEGenericDownscaleTestgen = 0,
    BPSDownscaleGeneric = 1,
};

static ChiPipelineTargetCreateDescriptor UsecaseGenericDownscale_pipelines[] =
{
    {"IFEGenericDownscaleTestgen", { 0, 1, UsecaseGenericDownscale_IFEGenericDownscaleTestgenNodes, 3, UsecaseGenericDownscale_IFEGenericDownscaleTestgenLinks, 1}, {3, UsecaseGenericDownscale_IFEGenericDownscaleTestgen_sink_TargetDescriptors}, {0, NULL}},  // IFEGenericDownscaleTestgen
    {"BPSDownscaleGeneric", { 0, 1, UsecaseGenericDownscale_BPSDownscaleGenericNodes, 4, UsecaseGenericDownscale_BPSDownscaleGenericLinks, 0}, {4, UsecaseGenericDownscale_BPSDownscaleGeneric_sink_TargetDescriptors}, {1, UsecaseGenericDownscale_BPSDownscaleGeneric_source_TargetDescriptors}},  // BPSDownscaleGeneric
};

/*==================== USECASE: UsecaseIPEJPEG =======================*/

static ChiBufferFormat UsecaseIPEJPEG_TARGET_BUFFER_INPUT_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat UsecaseIPEJPEG_TARGET_BUFFER_SNAPSHOT_formats[] =
{
    ChiFormatJpeg,
    ChiFormatYUV420NV12,
};

static ChiTarget UsecaseIPEJPEG_TARGET_BUFFER_INPUT_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    UsecaseIPEJPEG_TARGET_BUFFER_INPUT_formats,
    NULL
}; // TARGET_BUFFER_INPUT

static ChiTarget UsecaseIPEJPEG_TARGET_BUFFER_SNAPSHOT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 4000
    },
    2,
    UsecaseIPEJPEG_TARGET_BUFFER_SNAPSHOT_formats,
    NULL
}; // TARGET_BUFFER_SNAPSHOT

static ChiTarget* UsecaseIPEJPEG_Targets[] =
{
	&UsecaseIPEJPEG_TARGET_BUFFER_INPUT_target,
	&UsecaseIPEJPEG_TARGET_BUFFER_SNAPSHOT_target
};

/*****************************Pipeline OFflineIPEInputYUVOutputJPEG***************************/

static ChiLinkNodeDescriptor UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEG_source_Link_0NodeDescriptors[] =
{
    {65538, 0, 0},
};
static ChiLinkNodeDescriptor UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEG_Link0_IPE0_Out8Desc[] =
{
    {65537, 0, 0, 0, {0, NULL}}, // JPEG
};

static ChiLinkNodeDescriptor UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEG_Link1_JPEG0_Out1Desc[] =
{
    {6, 0, 0, 0, {0, NULL}}, // JPEGAggregator
};

static ChiLinkNodeDescriptor __74_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {6, 0, 2 }, 
};
static ChiLinkNodeDescriptor UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEG_Link2_JPEGAggregator0_Out2Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEG_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &UsecaseIPEJPEG_TARGET_BUFFER_SNAPSHOT_target, 1, __74_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEG_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_INPUT", &UsecaseIPEJPEG_TARGET_BUFFER_INPUT_target, 1, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEG_source_Link_0NodeDescriptors}, // TARGET_BUFFER_INPUT
};

// JPEGAggregator0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNode6_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGAggregatorInputPort0
};

// JPEGAggregator0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNode6_0OutputPortDescriptors[] =
{
    {2, 1, 1, 0, 0, NULL}, // JPEGAggregatorOutputPort0
};

// JPEG0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNode65537_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGInputPort0
};

// JPEG0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNode65537_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // JPEGOutputPort0
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNode65538_0InputPortDescriptors[] =
{
    {0, 1, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNode65538_0OutputPortDescriptors[] =
{
    {8, 0, 0, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNode UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNodes[] =
{
    {NULL, 6, 0, {1, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNode6_0InputPortDescriptors, 1, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNode6_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65537, 0, {1, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNode65537_0InputPortDescriptors, 1, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNode65537_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNode65538_0InputPortDescriptors, 1, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGLinks[] =
{
    {{65538, 0, 8, 0}, 1, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEG_Link0_IPE0_Out8Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65537, 0, 1, 0}, 1, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEG_Link1_JPEG0_Out1Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{6, 0, 2, 0}, 1, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEG_Link2_JPEGAggregator0_Out2Desc, {0}, {0, 0}},
};

enum UsecaseIPEJPEGPipelineIds
{
    OFflineIPEInputYUVOutputJPEG = 0,
};

static ChiPipelineTargetCreateDescriptor UsecaseIPEJPEG_pipelines[] =
{
    {"OFflineIPEInputYUVOutputJPEG", { 0, 3, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGNodes, 3, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEGLinks, 0}, {1, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEG_sink_TargetDescriptors}, {1, UsecaseIPEJPEG_OFflineIPEInputYUVOutputJPEG_source_TargetDescriptors}},  // OFflineIPEInputYUVOutputJPEG
};

/*==================== USECASE: UsecaseMimasGeneric =======================*/

static ChiBufferFormat UsecaseMimasGeneric_TARGET_BUFFER_INPUT_formats[] =
{
    ChiFormatBlob,
    ChiFormatJpeg,
    ChiFormatP010,
    ChiFormatPD10,
    ChiFormatRawDepth,
    ChiFormatRawMIPI,
    ChiFormatRawMIPI8,
    ChiFormatRawMeta8BIT,
    ChiFormatRawPlain16,
    ChiFormatRawPlain64,
    ChiFormatRawPrivate,
    ChiFormatRawYUV8BIT,
    ChiFormatUBWCNV12,
    ChiFormatUBWCNV124R,
    ChiFormatUBWCTP10,
    ChiFormatY16,
    ChiFormatY8,
    ChiFormatYUV420NV12,
    ChiFormatYUV420NV12TP10,
    ChiFormatYUV420NV16,
    ChiFormatYUV420NV21,
    ChiFormatYUV420NV21TP10,
    ChiFormatYUV422NV16TP10,
};

static ChiBufferFormat UsecaseMimasGeneric_TARGET_BUFFER_CONFIG_OUTPUT_formats[] =
{
    ChiFormatBlob,
    ChiFormatJpeg,
    ChiFormatP010,
    ChiFormatPD10,
    ChiFormatRawDepth,
    ChiFormatRawMIPI,
    ChiFormatRawMIPI8,
    ChiFormatRawMeta8BIT,
    ChiFormatRawPlain16,
    ChiFormatRawPlain64,
    ChiFormatRawPrivate,
    ChiFormatRawYUV8BIT,
    ChiFormatUBWCNV12,
    ChiFormatUBWCNV124R,
    ChiFormatUBWCTP10,
    ChiFormatY16,
    ChiFormatY8,
    ChiFormatYUV420NV12,
    ChiFormatYUV420NV12TP10,
    ChiFormatYUV420NV16,
    ChiFormatYUV420NV21,
    ChiFormatYUV420NV21TP10,
    ChiFormatYUV422NV16TP10,
};

static ChiTarget UsecaseMimasGeneric_TARGET_BUFFER_INPUT_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    23,
    UsecaseMimasGeneric_TARGET_BUFFER_INPUT_formats,
    NULL
}; // TARGET_BUFFER_INPUT

static ChiTarget UsecaseMimasGeneric_TARGET_BUFFER_CONFIG_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    23,
    UsecaseMimasGeneric_TARGET_BUFFER_CONFIG_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_CONFIG_OUTPUT

static ChiTarget* UsecaseMimasGeneric_Targets[] =
{
	&UsecaseMimasGeneric_TARGET_BUFFER_INPUT_target,
	&UsecaseMimasGeneric_TARGET_BUFFER_CONFIG_OUTPUT_target
};

/*****************************Pipeline TFEGenericTestgen***************************/

static ChiLinkNodeDescriptor __75_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65544, 0, 1 }, 
};
static ChiLinkNodeDescriptor UsecaseMimasGeneric_TFEGenericTestgen_Link0_TFE0_Out1Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiTargetPortDescriptor UsecaseMimasGeneric_TFEGenericTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseMimasGeneric_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __75_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
};

// TFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseMimasGeneric_TFEGenericTestgenNode65544_0OutputPortDescriptors[] =
{
    {1, 1, 1, 0, 0, NULL}, // TFEOutputPortFull
};

static ChiNode UsecaseMimasGeneric_TFEGenericTestgenNodes[] =
{
    {NULL, 65544, 0, {0, NULL, 1, UsecaseMimasGeneric_TFEGenericTestgenNode65544_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseMimasGeneric_TFEGenericTestgenLinks[] =
{
    {{65544, 0, 1, 0}, 1, UsecaseMimasGeneric_TFEGenericTestgen_Link0_TFE0_Out1Desc, {0}, {0, 0}},
};

/*****************************Pipeline OPEGeneric***************************/

static ChiLinkNodeDescriptor UsecaseMimasGeneric_OPEGeneric_source_Link_0NodeDescriptors[] =
{
    {65545, 0, 1},
};
static ChiLinkNodeDescriptor __76_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65545, 0, 1 }, 
};
static ChiLinkNodeDescriptor UsecaseMimasGeneric_OPEGeneric_Link0_OPE0_Out1Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiTargetPortDescriptor UsecaseMimasGeneric_OPEGeneric_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseMimasGeneric_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __76_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiTargetPortDescriptor UsecaseMimasGeneric_OPEGeneric_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_INPUT", &UsecaseMimasGeneric_TARGET_BUFFER_INPUT_target, 1, UsecaseMimasGeneric_OPEGeneric_source_Link_0NodeDescriptors}, // TARGET_BUFFER_INPUT
};

// OPE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseMimasGeneric_OPEGenericNode65545_0InputPortDescriptors[] =
{
    {1, 1, 0}, // OPEInputPortFull
};

// OPE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseMimasGeneric_OPEGenericNode65545_0OutputPortDescriptors[] =
{
    {1, 1, 1, 0, 0, NULL}, // OPEOutputPortVideo
};

static ChiNode UsecaseMimasGeneric_OPEGenericNodes[] =
{
    {NULL, 65545, 0, {1, UsecaseMimasGeneric_OPEGenericNode65545_0InputPortDescriptors, 1, UsecaseMimasGeneric_OPEGenericNode65545_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseMimasGeneric_OPEGenericLinks[] =
{
    {{65545, 0, 1, 0}, 1, UsecaseMimasGeneric_OPEGeneric_Link0_OPE0_Out1Desc, {0}, {0, 0}},
};

enum UsecaseMimasGenericPipelineIds
{
    TFEGenericTestgen = 0,
    OPEGeneric = 1,
};

static ChiPipelineTargetCreateDescriptor UsecaseMimasGeneric_pipelines[] =
{
    {"TFEGenericTestgen", { 0, 1, UsecaseMimasGeneric_TFEGenericTestgenNodes, 1, UsecaseMimasGeneric_TFEGenericTestgenLinks, 1}, {1, UsecaseMimasGeneric_TFEGenericTestgen_sink_TargetDescriptors}, {0, NULL}},  // TFEGenericTestgen
    {"OPEGeneric", { 0, 1, UsecaseMimasGeneric_OPEGenericNodes, 1, UsecaseMimasGeneric_OPEGenericLinks, 0}, {1, UsecaseMimasGeneric_OPEGeneric_sink_TargetDescriptors}, {1, UsecaseMimasGeneric_OPEGeneric_source_TargetDescriptors}},  // OPEGeneric
};

/*==================== USECASE: TestZSLUseCase =======================*/

static ChiBufferFormat TestZSLUseCase_TARGET_BUFFER_PREVIEW_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestZSLUseCase_TARGET_BUFFER_RAW_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiBufferFormat TestZSLUseCase_TARGET_BUFFER_SNAPSHOT_formats[] =
{
    ChiFormatJpeg,
    ChiFormatYUV420NV12,
};

static ChiTarget TestZSLUseCase_TARGET_BUFFER_PREVIEW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestZSLUseCase_TARGET_BUFFER_PREVIEW_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW

static ChiTarget TestZSLUseCase_TARGET_BUFFER_RAW_target =
{
    ChiStreamTypeBidirectional,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 5488, 4112
    },
    2,
    TestZSLUseCase_TARGET_BUFFER_RAW_formats,
    NULL
}; // TARGET_BUFFER_RAW

static ChiTarget TestZSLUseCase_TARGET_BUFFER_SNAPSHOT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    2,
    TestZSLUseCase_TARGET_BUFFER_SNAPSHOT_formats,
    NULL
}; // TARGET_BUFFER_SNAPSHOT

static ChiTarget* TestZSLUseCase_Targets[] =
{
	&TestZSLUseCase_TARGET_BUFFER_PREVIEW_target,
	&TestZSLUseCase_TARGET_BUFFER_RAW_target,
	&TestZSLUseCase_TARGET_BUFFER_SNAPSHOT_target
};

/*****************************Pipeline ZSLPreviewRaw***************************/

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRaw_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRaw_Link1_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __77_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRaw_Link2_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiLinkNodeDescriptor __78_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRaw_Link3_IFE0_Out8Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiTargetPortDescriptor TestZSLUseCase_ZSLPreviewRaw_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestZSLUseCase_TARGET_BUFFER_PREVIEW_target, 1, __77_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
    {"TARGET_BUFFER_RAW", &TestZSLUseCase_TARGET_BUFFER_RAW_target, 1, __78_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLPreviewRawNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLPreviewRawNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLPreviewRawNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {8, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI0
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLPreviewRawNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLPreviewRawNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNode TestZSLUseCase_ZSLPreviewRawNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestZSLUseCase_ZSLPreviewRawNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, TestZSLUseCase_ZSLPreviewRawNode65536_0InputPortDescriptors, 2, TestZSLUseCase_ZSLPreviewRawNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestZSLUseCase_ZSLPreviewRawNode65538_0InputPortDescriptors, 1, TestZSLUseCase_ZSLPreviewRawNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestZSLUseCase_ZSLPreviewRawLinks[] =
{
    {{0, 0, 0, 0}, 1, TestZSLUseCase_ZSLPreviewRaw_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestZSLUseCase_ZSLPreviewRaw_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestZSLUseCase_ZSLPreviewRaw_Link2_IPE0_Out8Desc, {0}, {0, 0}},
    {{65536, 0, 8, 0}, 1, TestZSLUseCase_ZSLPreviewRaw_Link3_IFE0_Out8Desc, {0}, {0, 0}},
};

/*****************************Pipeline ZSLPreviewRawWithTestGen***************************/

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithTestGen_Link0_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __79_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithTestGen_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiLinkNodeDescriptor __80_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithTestGen_Link2_IFE0_Out8Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiTargetPortDescriptor TestZSLUseCase_ZSLPreviewRawWithTestGen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestZSLUseCase_TARGET_BUFFER_PREVIEW_target, 1, __79_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
    {"TARGET_BUFFER_RAW", &TestZSLUseCase_TARGET_BUFFER_RAW_target, 1, __80_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithTestGenNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {8, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI0
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithTestGenNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithTestGenNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNode TestZSLUseCase_ZSLPreviewRawWithTestGenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 2, TestZSLUseCase_ZSLPreviewRawWithTestGenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestZSLUseCase_ZSLPreviewRawWithTestGenNode65538_0InputPortDescriptors, 1, TestZSLUseCase_ZSLPreviewRawWithTestGenNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestZSLUseCase_ZSLPreviewRawWithTestGenLinks[] =
{
    {{65536, 0, 0, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithTestGen_Link0_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithTestGen_Link1_IPE0_Out8Desc, {0}, {0, 0}},
    {{65536, 0, 8, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithTestGen_Link2_IFE0_Out8Desc, {0}, {0, 0}},
};

/*****************************Pipeline ZSLSnapshotJpegWithDS***************************/

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDS_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDS_Link0_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDS_Link1_BPS0_Out2Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDS_Link2_BPS0_Out3Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDS_Link3_BPS0_Out4Desc[] =
{
    {65538, 0, 3, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDS_Link4_IPE0_Out8Desc[] =
{
    {65537, 0, 0, 0, {0, NULL}}, // JPEG
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDS_Link5_JPEG0_Out1Desc[] =
{
    {6, 0, 0, 0, {0, NULL}}, // JPEGAggregator
};

static ChiLinkNodeDescriptor __81_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {6, 0, 2 }, 
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDS_Link6_JPEGAggregator0_Out2Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDS_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &TestZSLUseCase_TARGET_BUFFER_SNAPSHOT_target, 1, __81_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDS_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &TestZSLUseCase_TARGET_BUFFER_RAW_target, 1, TestZSLUseCase_ZSLSnapshotJpegWithDS_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW
};

// JPEGAggregator0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDSNode6_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGAggregatorInputPort0
};

// JPEGAggregator0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDSNode6_0OutputPortDescriptors[] =
{
    {2, 1, 1, 0, 0, NULL}, // JPEGAggregatorOutputPort0
};

// JPEG0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDSNode65537_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGInputPort0
};

// JPEG0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDSNode65537_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // JPEGOutputPort0
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDSNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
    {3, 0, 0}, // IPEInputPortDS64
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDSNode65538_0OutputPortDescriptors[] =
{
    {8, 0, 0, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDSNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegWithDSNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
    {2, 0, 0, 0, 0, NULL}, // BPSOutputPortDS4
    {3, 0, 0, 0, 0, NULL}, // BPSOutputPortDS16
    {4, 0, 0, 0, 0, NULL}, // BPSOutputPortDS64
};

static ChiNode TestZSLUseCase_ZSLSnapshotJpegWithDSNodes[] =
{
    {NULL, 6, 0, {1, TestZSLUseCase_ZSLSnapshotJpegWithDSNode6_0InputPortDescriptors, 1, TestZSLUseCase_ZSLSnapshotJpegWithDSNode6_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65537, 0, {1, TestZSLUseCase_ZSLSnapshotJpegWithDSNode65537_0InputPortDescriptors, 1, TestZSLUseCase_ZSLSnapshotJpegWithDSNode65537_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {4, TestZSLUseCase_ZSLSnapshotJpegWithDSNode65538_0InputPortDescriptors, 1, TestZSLUseCase_ZSLSnapshotJpegWithDSNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, TestZSLUseCase_ZSLSnapshotJpegWithDSNode65539_0InputPortDescriptors, 4, TestZSLUseCase_ZSLSnapshotJpegWithDSNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestZSLUseCase_ZSLSnapshotJpegWithDSLinks[] =
{
    {{65539, 0, 1, 0}, 1, TestZSLUseCase_ZSLSnapshotJpegWithDS_Link0_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 2, 0}, 1, TestZSLUseCase_ZSLSnapshotJpegWithDS_Link1_BPS0_Out2Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 3, 0}, 1, TestZSLUseCase_ZSLSnapshotJpegWithDS_Link2_BPS0_Out3Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 4, 0}, 1, TestZSLUseCase_ZSLSnapshotJpegWithDS_Link3_BPS0_Out4Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestZSLUseCase_ZSLSnapshotJpegWithDS_Link4_IPE0_Out8Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65537, 0, 1, 0}, 1, TestZSLUseCase_ZSLSnapshotJpegWithDS_Link5_JPEG0_Out1Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{6, 0, 2, 0}, 1, TestZSLUseCase_ZSLSnapshotJpegWithDS_Link6_JPEGAggregator0_Out2Desc, {0}, {0, 0}},
};

/*****************************Pipeline ZSLSnapshotJpeg***************************/

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpeg_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpeg_Link0_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpeg_Link1_IPE0_Out8Desc[] =
{
    {65537, 0, 0, 0, {0, NULL}}, // JPEG
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpeg_Link2_JPEG0_Out1Desc[] =
{
    {6, 0, 0, 0, {0, NULL}}, // JPEGAggregator
};

static ChiLinkNodeDescriptor __82_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {6, 0, 2 }, 
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotJpeg_Link3_JPEGAggregator0_Out2Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestZSLUseCase_ZSLSnapshotJpeg_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &TestZSLUseCase_TARGET_BUFFER_SNAPSHOT_target, 1, __82_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestZSLUseCase_ZSLSnapshotJpeg_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &TestZSLUseCase_TARGET_BUFFER_RAW_target, 1, TestZSLUseCase_ZSLSnapshotJpeg_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW
};

// JPEGAggregator0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegNode6_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGAggregatorInputPort0
};

// JPEGAggregator0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegNode6_0OutputPortDescriptors[] =
{
    {2, 1, 1, 0, 0, NULL}, // JPEGAggregatorOutputPort0
};

// JPEG0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegNode65537_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGInputPort0
};

// JPEG0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegNode65537_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // JPEGOutputPort0
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegNode65538_0OutputPortDescriptors[] =
{
    {8, 0, 0, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLSnapshotJpegNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
};

static ChiNode TestZSLUseCase_ZSLSnapshotJpegNodes[] =
{
    {NULL, 6, 0, {1, TestZSLUseCase_ZSLSnapshotJpegNode6_0InputPortDescriptors, 1, TestZSLUseCase_ZSLSnapshotJpegNode6_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65537, 0, {1, TestZSLUseCase_ZSLSnapshotJpegNode65537_0InputPortDescriptors, 1, TestZSLUseCase_ZSLSnapshotJpegNode65537_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestZSLUseCase_ZSLSnapshotJpegNode65538_0InputPortDescriptors, 1, TestZSLUseCase_ZSLSnapshotJpegNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, TestZSLUseCase_ZSLSnapshotJpegNode65539_0InputPortDescriptors, 1, TestZSLUseCase_ZSLSnapshotJpegNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestZSLUseCase_ZSLSnapshotJpegLinks[] =
{
    {{65539, 0, 1, 0}, 1, TestZSLUseCase_ZSLSnapshotJpeg_Link0_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestZSLUseCase_ZSLSnapshotJpeg_Link1_IPE0_Out8Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65537, 0, 1, 0}, 1, TestZSLUseCase_ZSLSnapshotJpeg_Link2_JPEG0_Out1Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{6, 0, 2, 0}, 1, TestZSLUseCase_ZSLSnapshotJpeg_Link3_JPEGAggregator0_Out2Desc, {0}, {0, 0}},
};

/*****************************Pipeline ZSLSnapshotYUVWithDS***************************/

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotYUVWithDS_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotYUVWithDS_Link0_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotYUVWithDS_Link1_BPS0_Out2Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotYUVWithDS_Link2_BPS0_Out3Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotYUVWithDS_Link3_BPS0_Out4Desc[] =
{
    {65538, 0, 3, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __83_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotYUVWithDS_Link4_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestZSLUseCase_ZSLSnapshotYUVWithDS_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &TestZSLUseCase_TARGET_BUFFER_SNAPSHOT_target, 1, __83_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestZSLUseCase_ZSLSnapshotYUVWithDS_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &TestZSLUseCase_TARGET_BUFFER_RAW_target, 1, TestZSLUseCase_ZSLSnapshotYUVWithDS_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLSnapshotYUVWithDSNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
    {3, 0, 0}, // IPEInputPortDS64
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLSnapshotYUVWithDSNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLSnapshotYUVWithDSNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLSnapshotYUVWithDSNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
    {2, 0, 0, 0, 0, NULL}, // BPSOutputPortDS4
    {3, 0, 0, 0, 0, NULL}, // BPSOutputPortDS16
    {4, 0, 0, 0, 0, NULL}, // BPSOutputPortDS64
};

static ChiNode TestZSLUseCase_ZSLSnapshotYUVWithDSNodes[] =
{
    {NULL, 65538, 0, {4, TestZSLUseCase_ZSLSnapshotYUVWithDSNode65538_0InputPortDescriptors, 1, TestZSLUseCase_ZSLSnapshotYUVWithDSNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, TestZSLUseCase_ZSLSnapshotYUVWithDSNode65539_0InputPortDescriptors, 4, TestZSLUseCase_ZSLSnapshotYUVWithDSNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestZSLUseCase_ZSLSnapshotYUVWithDSLinks[] =
{
    {{65539, 0, 1, 0}, 1, TestZSLUseCase_ZSLSnapshotYUVWithDS_Link0_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 2, 0}, 1, TestZSLUseCase_ZSLSnapshotYUVWithDS_Link1_BPS0_Out2Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 3, 0}, 1, TestZSLUseCase_ZSLSnapshotYUVWithDS_Link2_BPS0_Out3Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 4, 0}, 1, TestZSLUseCase_ZSLSnapshotYUVWithDS_Link3_BPS0_Out4Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestZSLUseCase_ZSLSnapshotYUVWithDS_Link4_IPE0_Out8Desc, {0}, {0, 0}},
};

/*****************************Pipeline ZSLSnapshotYUV***************************/

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotYUV_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotYUV_Link0_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __84_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLSnapshotYUV_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestZSLUseCase_ZSLSnapshotYUV_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &TestZSLUseCase_TARGET_BUFFER_SNAPSHOT_target, 1, __84_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
};

static ChiTargetPortDescriptor TestZSLUseCase_ZSLSnapshotYUV_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &TestZSLUseCase_TARGET_BUFFER_RAW_target, 1, TestZSLUseCase_ZSLSnapshotYUV_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLSnapshotYUVNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLSnapshotYUVNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLSnapshotYUVNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLSnapshotYUVNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
};

static ChiNode TestZSLUseCase_ZSLSnapshotYUVNodes[] =
{
    {NULL, 65538, 0, {1, TestZSLUseCase_ZSLSnapshotYUVNode65538_0InputPortDescriptors, 1, TestZSLUseCase_ZSLSnapshotYUVNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, TestZSLUseCase_ZSLSnapshotYUVNode65539_0InputPortDescriptors, 1, TestZSLUseCase_ZSLSnapshotYUVNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestZSLUseCase_ZSLSnapshotYUVLinks[] =
{
    {{65539, 0, 1, 0}, 1, TestZSLUseCase_ZSLSnapshotYUV_Link0_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestZSLUseCase_ZSLSnapshotYUV_Link1_IPE0_Out8Desc, {0}, {0, 0}},
};

/*****************************Pipeline IFEFull3A***************************/

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link0_StatsParse0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link1_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __85_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65536, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link2_IFE0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link3_StatsProcessing0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link4_AutoWhiteBalance0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link5_IFE0_Out17Desc[] =
{
    {9, 0, 0, 0, {0, NULL}}, // StatsParse
    {1, 0, 0, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link6_IFE0_Out19Desc[] =
{
    {9, 0, 9, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link7_IFE0_Out21Desc[] =
{
    {9, 0, 1, 0, {0, NULL}}, // StatsParse
    {12, 0, 1, 0, {0, NULL}}, // AutoWhiteBalance
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link8_IFE0_Out18Desc[] =
{
    {9, 0, 2, 0, {0, NULL}}, // StatsParse
    {1, 0, 2, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link9_IFE0_Out16Desc[] =
{
    {9, 0, 3, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link10_IFE0_Out12Desc[] =
{
    {9, 0, 7, 0, {0, NULL}}, // StatsParse
    {1, 0, 7, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link11_IFE0_Out20Desc[] =
{
    {5, 0, 4, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link12_IFE0_Out8Desc[] =
{
    {5, 0, 8, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link13_IFE0_Out7Desc[] =
{
    {5, 0, 10, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestZSLUseCase_IFEFull3A_Link14_AutoFocus0_Out0Desc[] =
{
    {3, 3, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiTargetPortDescriptor TestZSLUseCase_IFEFull3A_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestZSLUseCase_TARGET_BUFFER_PREVIEW_target, 1, __85_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_IFEFull3ANode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// StatsProcessing0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_IFEFull3ANode1_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsProcessingInputPortHDRBE
    {2, 0, 0}, // StatsProcessingPortHDRBHist
    {7, 0, 0}, // StatsProcessingInputPortRS
};

// StatsProcessing0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_IFEFull3ANode1_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsProcessingOutputPort0
};

// AutoWhiteBalance0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_IFEFull3ANode12_0InputPortDescriptors[] =
{
    {1, 0, 0}, // StatsInputPortAWBBG
};

// AutoWhiteBalance0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_IFEFull3ANode12_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AWBOutputPort0
};

// AutoFocus0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_IFEFull3ANode5_0InputPortDescriptors[] =
{
    {4, 0, 0}, // StatsInputPortBF
    {8, 0, 0}, // StatsInputPortRDIPDAF
    {10, 0, 0}, // StatsInputPortPDAFType3
};

// AutoFocus0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_IFEFull3ANode5_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AutoFocusOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_IFEFull3ANode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_IFEFull3ANode65536_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // IFEOutputPortFull
    {17, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBE
    {19, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {21, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
    {18, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBHIST
    {16, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBHIST
    {12, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsRS
    {20, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBF
    {8, 0, 0, 2, 0, NULL}, // IFEOutputPortRDI0
    {7, 0, 0, 0, 0, NULL}, // IFEOutputPortPDAF
};

// StatsParse0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_IFEFull3ANode9_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsParseInputPortHDRBE
    {9, 0, 0}, // StatsParseInputPortTintlessBG
    {1, 0, 0}, // StatsParseInputPortAWBBG
    {2, 0, 0}, // StatsParseInputPortHDRBHist
    {3, 0, 0}, // StatsParseInputPortBHist
    {7, 0, 0}, // StatsParseInputPortRS
};

// StatsParse0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_IFEFull3ANode9_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsParseOutputPort0
};

static ChiNodeProperty TestZSLUseCase_IFEFull3A_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestZSLUseCase_IFEFull3A_node1_0_properties[] =
{
    {1, "com.qti.stats.aec"},
    {1, "com.qti.stats.afd"},
    {6, "1"},
};

static ChiNodeProperty TestZSLUseCase_IFEFull3A_node12_0_properties[] =
{
    {1, "com.qti.stats.awb"},
    {6, "1"},
};

static ChiNodeProperty TestZSLUseCase_IFEFull3A_node5_0_properties[] =
{
    {1, "com.qti.stats.af"},
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestZSLUseCase_IFEFull3A_node9_0_properties[] =
{
    {6, "1"},
};

static ChiNode TestZSLUseCase_IFEFull3ANodes[] =
{
    {TestZSLUseCase_IFEFull3A_node0_0_properties, 0, 0, {0, NULL, 1, TestZSLUseCase_IFEFull3ANode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {TestZSLUseCase_IFEFull3A_node1_0_properties, 1, 0, {3, TestZSLUseCase_IFEFull3ANode1_0InputPortDescriptors, 1, TestZSLUseCase_IFEFull3ANode1_0OutputPortDescriptors}, 3, {0, NULL}},
    {TestZSLUseCase_IFEFull3A_node12_0_properties, 12, 0, {1, TestZSLUseCase_IFEFull3ANode12_0InputPortDescriptors, 1, TestZSLUseCase_IFEFull3ANode12_0OutputPortDescriptors}, 2, {0, NULL}},
    {TestZSLUseCase_IFEFull3A_node5_0_properties, 5, 0, {3, TestZSLUseCase_IFEFull3ANode5_0InputPortDescriptors, 1, TestZSLUseCase_IFEFull3ANode5_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65536, 0, {1, TestZSLUseCase_IFEFull3ANode65536_0InputPortDescriptors, 10, TestZSLUseCase_IFEFull3ANode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestZSLUseCase_IFEFull3A_node9_0_properties, 9, 0, {6, TestZSLUseCase_IFEFull3ANode9_0InputPortDescriptors, 1, TestZSLUseCase_IFEFull3ANode9_0OutputPortDescriptors}, 1, {0, NULL}},
};

static ChiNodeLink TestZSLUseCase_IFEFull3ALinks[] =
{
    {{9, 0, 0, 0}, 1, TestZSLUseCase_IFEFull3A_Link0_StatsParse0_Out0Desc, {0}, {0, 0}},
    {{0, 0, 0, 0}, 1, TestZSLUseCase_IFEFull3A_Link1_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestZSLUseCase_IFEFull3A_Link2_IFE0_Out0Desc, {0}, {0, 0}},
    {{1, 0, 0, 0}, 1, TestZSLUseCase_IFEFull3A_Link3_StatsProcessing0_Out0Desc, {0}, {0, 0}},
    {{12, 0, 0, 0}, 1, TestZSLUseCase_IFEFull3A_Link4_AutoWhiteBalance0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 17, 0}, 2, TestZSLUseCase_IFEFull3A_Link5_IFE0_Out17Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestZSLUseCase_IFEFull3A_Link6_IFE0_Out19Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 21, 0}, 2, TestZSLUseCase_IFEFull3A_Link7_IFE0_Out21Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 18, 0}, 2, TestZSLUseCase_IFEFull3A_Link8_IFE0_Out18Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 16, 0}, 1, TestZSLUseCase_IFEFull3A_Link9_IFE0_Out16Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 12, 0}, 2, TestZSLUseCase_IFEFull3A_Link10_IFE0_Out12Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestZSLUseCase_IFEFull3A_Link11_IFE0_Out20Desc, {ChiFormatBlob, 16384, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 8, 2}, 1, TestZSLUseCase_IFEFull3A_Link12_IFE0_Out8Desc, {ChiFormatBlob, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 7, 0}, 1, TestZSLUseCase_IFEFull3A_Link13_IFE0_Out7Desc, {ChiFormatRawPlain16, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{5, 0, 0, 0}, 1, TestZSLUseCase_IFEFull3A_Link14_AutoFocus0_Out0Desc, {0}, {0, 0}},
};

/*****************************Pipeline ZSLPreviewRawWithStats***************************/

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link0_StatsParse0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link1_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link2_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link3_IFE0_Out1Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link4_IFE0_Out2Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link5_StatsProcessing0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link6_AutoWhiteBalance0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link7_IFE0_Out17Desc[] =
{
    {9, 0, 0, 0, {0, NULL}}, // StatsParse
    {1, 0, 0, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link8_IFE0_Out19Desc[] =
{
    {9, 0, 9, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link9_IFE0_Out21Desc[] =
{
    {9, 0, 1, 0, {0, NULL}}, // StatsParse
    {12, 0, 1, 0, {0, NULL}}, // AutoWhiteBalance
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link10_IFE0_Out18Desc[] =
{
    {9, 0, 2, 0, {0, NULL}}, // StatsParse
    {1, 0, 2, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link11_IFE0_Out16Desc[] =
{
    {9, 0, 3, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link12_IFE0_Out12Desc[] =
{
    {9, 0, 7, 0, {0, NULL}}, // StatsParse
    {1, 0, 7, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link13_IFE0_Out20Desc[] =
{
    {5, 0, 4, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link14_IFE0_Out8Desc[] =
{
    {5, 0, 8, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link15_IFE0_Out7Desc[] =
{
    {5, 0, 10, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link16_AutoFocus0_Out0Desc[] =
{
    {3, 3, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor __86_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link17_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiLinkNodeDescriptor __87_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_Link18_IFE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiTargetPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStats_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestZSLUseCase_TARGET_BUFFER_PREVIEW_target, 1, __86_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
    {"TARGET_BUFFER_RAW", &TestZSLUseCase_TARGET_BUFFER_RAW_target, 1, __87_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// StatsProcessing0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode1_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsProcessingInputPortHDRBE
    {2, 0, 0}, // StatsProcessingPortHDRBHist
    {7, 0, 0}, // StatsProcessingInputPortRS
};

// StatsProcessing0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode1_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsProcessingOutputPort0
};

// AutoWhiteBalance0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode12_0InputPortDescriptors[] =
{
    {1, 0, 0}, // StatsInputPortAWBBG
};

// AutoWhiteBalance0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode12_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AWBOutputPort0
};

// AutoFocus0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode5_0InputPortDescriptors[] =
{
    {4, 0, 0}, // StatsInputPortBF
    {8, 0, 0}, // StatsInputPortRDIPDAF
    {10, 0, 0}, // StatsInputPortPDAFType3
};

// AutoFocus0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode5_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AutoFocusOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 0, 0, 0, 0, NULL}, // IFEOutputPortDS16
    {17, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBE
    {19, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {21, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
    {18, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBHIST
    {16, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBHIST
    {12, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsRS
    {20, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBF
    {8, 0, 0, 2, 0, NULL}, // IFEOutputPortRDI0
    {7, 0, 0, 0, 0, NULL}, // IFEOutputPortPDAF
    {9, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI1
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

// StatsParse0 Input Port Descriptors
static ChiInputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode9_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsParseInputPortHDRBE
    {9, 0, 0}, // StatsParseInputPortTintlessBG
    {1, 0, 0}, // StatsParseInputPortAWBBG
    {2, 0, 0}, // StatsParseInputPortHDRBHist
    {3, 0, 0}, // StatsParseInputPortBHist
    {7, 0, 0}, // StatsParseInputPortRS
};

// StatsParse0 Output Port Descriptors
static ChiOutputPortDescriptor TestZSLUseCase_ZSLPreviewRawWithStatsNode9_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsParseOutputPort0
};

static ChiNodeProperty TestZSLUseCase_ZSLPreviewRawWithStats_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestZSLUseCase_ZSLPreviewRawWithStats_node1_0_properties[] =
{
    {1, "com.qti.stats.aec"},
    {1, "com.qti.stats.afd"},
    {6, "1"},
};

static ChiNodeProperty TestZSLUseCase_ZSLPreviewRawWithStats_node12_0_properties[] =
{
    {1, "com.qti.stats.awb"},
    {6, "1"},
};

static ChiNodeProperty TestZSLUseCase_ZSLPreviewRawWithStats_node5_0_properties[] =
{
    {1, "com.qti.stats.af"},
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestZSLUseCase_ZSLPreviewRawWithStats_node9_0_properties[] =
{
    {6, "1"},
};

static ChiNode TestZSLUseCase_ZSLPreviewRawWithStatsNodes[] =
{
    {TestZSLUseCase_ZSLPreviewRawWithStats_node0_0_properties, 0, 0, {0, NULL, 1, TestZSLUseCase_ZSLPreviewRawWithStatsNode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {TestZSLUseCase_ZSLPreviewRawWithStats_node1_0_properties, 1, 0, {3, TestZSLUseCase_ZSLPreviewRawWithStatsNode1_0InputPortDescriptors, 1, TestZSLUseCase_ZSLPreviewRawWithStatsNode1_0OutputPortDescriptors}, 3, {0, NULL}},
    {TestZSLUseCase_ZSLPreviewRawWithStats_node12_0_properties, 12, 0, {1, TestZSLUseCase_ZSLPreviewRawWithStatsNode12_0InputPortDescriptors, 1, TestZSLUseCase_ZSLPreviewRawWithStatsNode12_0OutputPortDescriptors}, 2, {0, NULL}},
    {TestZSLUseCase_ZSLPreviewRawWithStats_node5_0_properties, 5, 0, {3, TestZSLUseCase_ZSLPreviewRawWithStatsNode5_0InputPortDescriptors, 1, TestZSLUseCase_ZSLPreviewRawWithStatsNode5_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65536, 0, {1, TestZSLUseCase_ZSLPreviewRawWithStatsNode65536_0InputPortDescriptors, 13, TestZSLUseCase_ZSLPreviewRawWithStatsNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {3, TestZSLUseCase_ZSLPreviewRawWithStatsNode65538_0InputPortDescriptors, 1, TestZSLUseCase_ZSLPreviewRawWithStatsNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestZSLUseCase_ZSLPreviewRawWithStats_node9_0_properties, 9, 0, {6, TestZSLUseCase_ZSLPreviewRawWithStatsNode9_0InputPortDescriptors, 1, TestZSLUseCase_ZSLPreviewRawWithStatsNode9_0OutputPortDescriptors}, 1, {0, NULL}},
};

static ChiNodeLink TestZSLUseCase_ZSLPreviewRawWithStatsLinks[] =
{
    {{9, 0, 0, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link0_StatsParse0_Out0Desc, {0}, {0, 0}},
    {{0, 0, 0, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link1_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link2_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link3_IFE0_Out1Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 2, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link4_IFE0_Out2Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{1, 0, 0, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link5_StatsProcessing0_Out0Desc, {0}, {0, 0}},
    {{12, 0, 0, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link6_AutoWhiteBalance0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 17, 0}, 2, TestZSLUseCase_ZSLPreviewRawWithStats_Link7_IFE0_Out17Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link8_IFE0_Out19Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 21, 0}, 2, TestZSLUseCase_ZSLPreviewRawWithStats_Link9_IFE0_Out21Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 18, 0}, 2, TestZSLUseCase_ZSLPreviewRawWithStats_Link10_IFE0_Out18Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 16, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link11_IFE0_Out16Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 12, 0}, 2, TestZSLUseCase_ZSLPreviewRawWithStats_Link12_IFE0_Out12Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link13_IFE0_Out20Desc, {ChiFormatBlob, 16384, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 8, 2}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link14_IFE0_Out8Desc, {ChiFormatBlob, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 7, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link15_IFE0_Out7Desc, {ChiFormatRawPlain16, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{5, 0, 0, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link16_AutoFocus0_Out0Desc, {0}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link17_IPE0_Out8Desc, {0}, {0, 0}},
    {{65536, 0, 9, 0}, 1, TestZSLUseCase_ZSLPreviewRawWithStats_Link18_IFE0_Out9Desc, {0}, {0, 0}},
};

enum TestZSLUseCasePipelineIds
{
    ZSLPreviewRaw = 0,
    ZSLPreviewRawWithTestGen = 1,
    ZSLSnapshotJpegWithDS = 2,
    ZSLSnapshotJpeg = 3,
    ZSLSnapshotYUVWithDS = 4,
    ZSLSnapshotYUV = 5,
    IFEFull3A = 6,
    ZSLPreviewRawWithStats = 7,
};

static ChiPipelineTargetCreateDescriptor TestZSLUseCase_pipelines[] =
{
    {"ZSLPreviewRaw", { 0, 3, TestZSLUseCase_ZSLPreviewRawNodes, 4, TestZSLUseCase_ZSLPreviewRawLinks, 1}, {2, TestZSLUseCase_ZSLPreviewRaw_sink_TargetDescriptors}, {0, NULL}},  // ZSLPreviewRaw
    {"ZSLPreviewRawWithTestGen", { 0, 2, TestZSLUseCase_ZSLPreviewRawWithTestGenNodes, 3, TestZSLUseCase_ZSLPreviewRawWithTestGenLinks, 1}, {2, TestZSLUseCase_ZSLPreviewRawWithTestGen_sink_TargetDescriptors}, {0, NULL}},  // ZSLPreviewRawWithTestGen
    {"ZSLSnapshotJpegWithDS", { 0, 4, TestZSLUseCase_ZSLSnapshotJpegWithDSNodes, 7, TestZSLUseCase_ZSLSnapshotJpegWithDSLinks, 0}, {1, TestZSLUseCase_ZSLSnapshotJpegWithDS_sink_TargetDescriptors}, {1, TestZSLUseCase_ZSLSnapshotJpegWithDS_source_TargetDescriptors}},  // ZSLSnapshotJpegWithDS
    {"ZSLSnapshotJpeg", { 0, 4, TestZSLUseCase_ZSLSnapshotJpegNodes, 4, TestZSLUseCase_ZSLSnapshotJpegLinks, 0}, {1, TestZSLUseCase_ZSLSnapshotJpeg_sink_TargetDescriptors}, {1, TestZSLUseCase_ZSLSnapshotJpeg_source_TargetDescriptors}},  // ZSLSnapshotJpeg
    {"ZSLSnapshotYUVWithDS", { 0, 2, TestZSLUseCase_ZSLSnapshotYUVWithDSNodes, 5, TestZSLUseCase_ZSLSnapshotYUVWithDSLinks, 0}, {1, TestZSLUseCase_ZSLSnapshotYUVWithDS_sink_TargetDescriptors}, {1, TestZSLUseCase_ZSLSnapshotYUVWithDS_source_TargetDescriptors}},  // ZSLSnapshotYUVWithDS
    {"ZSLSnapshotYUV", { 0, 2, TestZSLUseCase_ZSLSnapshotYUVNodes, 2, TestZSLUseCase_ZSLSnapshotYUVLinks, 0}, {1, TestZSLUseCase_ZSLSnapshotYUV_sink_TargetDescriptors}, {1, TestZSLUseCase_ZSLSnapshotYUV_source_TargetDescriptors}},  // ZSLSnapshotYUV
    {"IFEFull3A", { 0, 6, TestZSLUseCase_IFEFull3ANodes, 15, TestZSLUseCase_IFEFull3ALinks, 1}, {1, TestZSLUseCase_IFEFull3A_sink_TargetDescriptors}, {0, NULL}},  // IFEFull3A
    {"ZSLPreviewRawWithStats", { 0, 7, TestZSLUseCase_ZSLPreviewRawWithStatsNodes, 19, TestZSLUseCase_ZSLPreviewRawWithStatsLinks, 1}, {2, TestZSLUseCase_ZSLPreviewRawWithStats_sink_TargetDescriptors}, {0, NULL}},  // ZSLPreviewRawWithStats
};

/*==================== USECASE: TestOfflineIPESIMO =======================*/

static ChiBufferFormat TestOfflineIPESIMO_TARGET_BUFFER_IPE_INPUT_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestOfflineIPESIMO_TARGET_BUFFER_DISPLAY_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestOfflineIPESIMO_TARGET_BUFFER_VIDEO_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiTarget TestOfflineIPESIMO_TARGET_BUFFER_IPE_INPUT_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestOfflineIPESIMO_TARGET_BUFFER_IPE_INPUT_formats,
    NULL
}; // TARGET_BUFFER_IPE_INPUT

static ChiTarget TestOfflineIPESIMO_TARGET_BUFFER_DISPLAY_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestOfflineIPESIMO_TARGET_BUFFER_DISPLAY_formats,
    NULL
}; // TARGET_BUFFER_DISPLAY

static ChiTarget TestOfflineIPESIMO_TARGET_BUFFER_VIDEO_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestOfflineIPESIMO_TARGET_BUFFER_VIDEO_formats,
    NULL
}; // TARGET_BUFFER_VIDEO

static ChiTarget* TestOfflineIPESIMO_Targets[] =
{
	&TestOfflineIPESIMO_TARGET_BUFFER_IPE_INPUT_target,
	&TestOfflineIPESIMO_TARGET_BUFFER_DISPLAY_target,
	&TestOfflineIPESIMO_TARGET_BUFFER_VIDEO_target
};

/*****************************Pipeline OfflineDispVideo***************************/

static ChiLinkNodeDescriptor TestOfflineIPESIMO_OfflineDispVideo_source_Link_0NodeDescriptors[] =
{
    {65538, 0, 0},
};
static ChiLinkNodeDescriptor __88_TARGET_BUFFER_DISPLAY_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestOfflineIPESIMO_OfflineDispVideo_Link0_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_DISPLAY
};

static ChiLinkNodeDescriptor __89_TARGET_BUFFER_VIDEO_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestOfflineIPESIMO_OfflineDispVideo_Link1_IPE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_VIDEO
};

static ChiTargetPortDescriptor TestOfflineIPESIMO_OfflineDispVideo_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_DISPLAY", &TestOfflineIPESIMO_TARGET_BUFFER_DISPLAY_target, 1, __88_TARGET_BUFFER_DISPLAY_Link_NodeDescriptors}, // TARGET_BUFFER_DISPLAY
    {"TARGET_BUFFER_VIDEO", &TestOfflineIPESIMO_TARGET_BUFFER_VIDEO_target, 1, __89_TARGET_BUFFER_VIDEO_Link_NodeDescriptors}, // TARGET_BUFFER_VIDEO
};

static ChiTargetPortDescriptor TestOfflineIPESIMO_OfflineDispVideo_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_IPE_INPUT", &TestOfflineIPESIMO_TARGET_BUFFER_IPE_INPUT_target, 1, TestOfflineIPESIMO_OfflineDispVideo_source_Link_0NodeDescriptors}, // TARGET_BUFFER_IPE_INPUT
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestOfflineIPESIMO_OfflineDispVideoNode65538_0InputPortDescriptors[] =
{
    {0, 1, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestOfflineIPESIMO_OfflineDispVideoNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
};

static ChiNode TestOfflineIPESIMO_OfflineDispVideoNodes[] =
{
    {NULL, 65538, 0, {1, TestOfflineIPESIMO_OfflineDispVideoNode65538_0InputPortDescriptors, 2, TestOfflineIPESIMO_OfflineDispVideoNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestOfflineIPESIMO_OfflineDispVideoLinks[] =
{
    {{65538, 0, 8, 0}, 1, TestOfflineIPESIMO_OfflineDispVideo_Link0_IPE0_Out8Desc, {0}, {0, 0}},
    {{65538, 0, 9, 0}, 1, TestOfflineIPESIMO_OfflineDispVideo_Link1_IPE0_Out9Desc, {0}, {0, 0}},
};

enum TestOfflineIPESIMOPipelineIds
{
    OfflineDispVideo = 0,
};

static ChiPipelineTargetCreateDescriptor TestOfflineIPESIMO_pipelines[] =
{
    {"OfflineDispVideo", { 0, 1, TestOfflineIPESIMO_OfflineDispVideoNodes, 2, TestOfflineIPESIMO_OfflineDispVideoLinks, 0}, {2, TestOfflineIPESIMO_OfflineDispVideo_sink_TargetDescriptors}, {1, TestOfflineIPESIMO_OfflineDispVideo_source_TargetDescriptors}},  // OfflineDispVideo
};

/*==================== USECASE: OfflineBPSSingleStatWithIPE =======================*/

static ChiBufferFormat OfflineBPSSingleStatWithIPE_TARGET_BUFFER_RAW_IN_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiBufferFormat OfflineBPSSingleStatWithIPE_TARGET_BUFFER_IPE_DISPLAY_formats[] =
{
    ChiFormatYUV420NV12,
};

static ChiBufferFormat OfflineBPSSingleStatWithIPE_TARGET_BUFFER_BPS_STAT_formats[] =
{
    ChiFormatBlob,
};

static ChiTarget OfflineBPSSingleStatWithIPE_TARGET_BUFFER_RAW_IN_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    2,
    OfflineBPSSingleStatWithIPE_TARGET_BUFFER_RAW_IN_formats,
    NULL
}; // TARGET_BUFFER_RAW_IN

static ChiTarget OfflineBPSSingleStatWithIPE_TARGET_BUFFER_IPE_DISPLAY_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    1,
    OfflineBPSSingleStatWithIPE_TARGET_BUFFER_IPE_DISPLAY_formats,
    NULL
}; // TARGET_BUFFER_IPE_DISPLAY

static ChiTarget OfflineBPSSingleStatWithIPE_TARGET_BUFFER_BPS_STAT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 691200, 1
    },
    1,
    OfflineBPSSingleStatWithIPE_TARGET_BUFFER_BPS_STAT_formats,
    NULL
}; // TARGET_BUFFER_BPS_STAT

static ChiTarget* OfflineBPSSingleStatWithIPE_Targets[] =
{
	&OfflineBPSSingleStatWithIPE_TARGET_BUFFER_RAW_IN_target,
	&OfflineBPSSingleStatWithIPE_TARGET_BUFFER_IPE_DISPLAY_target,
	&OfflineBPSSingleStatWithIPE_TARGET_BUFFER_BPS_STAT_target
};

/*****************************Pipeline BPSBGStats***************************/

static ChiLinkNodeDescriptor OfflineBPSSingleStatWithIPE_BPSBGStats_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor OfflineBPSSingleStatWithIPE_BPSBGStats_Link0_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __90_TARGET_BUFFER_IPE_DISPLAY_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor OfflineBPSSingleStatWithIPE_BPSBGStats_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_IPE_DISPLAY
};

static ChiLinkNodeDescriptor __91_TARGET_BUFFER_BPS_STAT_Link_NodeDescriptors[] =
{
    {65539, 0, 5 }, 
};
static ChiLinkNodeDescriptor OfflineBPSSingleStatWithIPE_BPSBGStats_Link2_BPS0_Out5Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BPS_STAT
};

static ChiTargetPortDescriptor OfflineBPSSingleStatWithIPE_BPSBGStats_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_IPE_DISPLAY", &OfflineBPSSingleStatWithIPE_TARGET_BUFFER_IPE_DISPLAY_target, 1, __90_TARGET_BUFFER_IPE_DISPLAY_Link_NodeDescriptors}, // TARGET_BUFFER_IPE_DISPLAY
    {"TARGET_BUFFER_BPS_STAT", &OfflineBPSSingleStatWithIPE_TARGET_BUFFER_BPS_STAT_target, 1, __91_TARGET_BUFFER_BPS_STAT_Link_NodeDescriptors}, // TARGET_BUFFER_BPS_STAT
};

static ChiTargetPortDescriptor OfflineBPSSingleStatWithIPE_BPSBGStats_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW_IN", &OfflineBPSSingleStatWithIPE_TARGET_BUFFER_RAW_IN_target, 1, OfflineBPSSingleStatWithIPE_BPSBGStats_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW_IN
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor OfflineBPSSingleStatWithIPE_BPSBGStatsNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor OfflineBPSSingleStatWithIPE_BPSBGStatsNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor OfflineBPSSingleStatWithIPE_BPSBGStatsNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor OfflineBPSSingleStatWithIPE_BPSBGStatsNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
    {5, 1, 1, 0, 0, NULL}, // BPSOutputPortStatsBG
};

static ChiNode OfflineBPSSingleStatWithIPE_BPSBGStatsNodes[] =
{
    {NULL, 65538, 0, {1, OfflineBPSSingleStatWithIPE_BPSBGStatsNode65538_0InputPortDescriptors, 1, OfflineBPSSingleStatWithIPE_BPSBGStatsNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, OfflineBPSSingleStatWithIPE_BPSBGStatsNode65539_0InputPortDescriptors, 2, OfflineBPSSingleStatWithIPE_BPSBGStatsNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink OfflineBPSSingleStatWithIPE_BPSBGStatsLinks[] =
{
    {{65539, 0, 1, 0}, 1, OfflineBPSSingleStatWithIPE_BPSBGStats_Link0_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, OfflineBPSSingleStatWithIPE_BPSBGStats_Link1_IPE0_Out8Desc, {0}, {0, 0}},
    {{65539, 0, 5, 0}, 1, OfflineBPSSingleStatWithIPE_BPSBGStats_Link2_BPS0_Out5Desc, {0}, {0, 0}},
};

/*****************************Pipeline BPSHistStats***************************/

static ChiLinkNodeDescriptor OfflineBPSSingleStatWithIPE_BPSHistStats_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor OfflineBPSSingleStatWithIPE_BPSHistStats_Link0_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __92_TARGET_BUFFER_IPE_DISPLAY_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor OfflineBPSSingleStatWithIPE_BPSHistStats_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_IPE_DISPLAY
};

static ChiLinkNodeDescriptor __93_TARGET_BUFFER_BPS_STAT_Link_NodeDescriptors[] =
{
    {65539, 0, 6 }, 
};
static ChiLinkNodeDescriptor OfflineBPSSingleStatWithIPE_BPSHistStats_Link2_BPS0_Out6Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BPS_STAT
};

static ChiTargetPortDescriptor OfflineBPSSingleStatWithIPE_BPSHistStats_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_IPE_DISPLAY", &OfflineBPSSingleStatWithIPE_TARGET_BUFFER_IPE_DISPLAY_target, 1, __92_TARGET_BUFFER_IPE_DISPLAY_Link_NodeDescriptors}, // TARGET_BUFFER_IPE_DISPLAY
    {"TARGET_BUFFER_BPS_STAT", &OfflineBPSSingleStatWithIPE_TARGET_BUFFER_BPS_STAT_target, 1, __93_TARGET_BUFFER_BPS_STAT_Link_NodeDescriptors}, // TARGET_BUFFER_BPS_STAT
};

static ChiTargetPortDescriptor OfflineBPSSingleStatWithIPE_BPSHistStats_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW_IN", &OfflineBPSSingleStatWithIPE_TARGET_BUFFER_RAW_IN_target, 1, OfflineBPSSingleStatWithIPE_BPSHistStats_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW_IN
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor OfflineBPSSingleStatWithIPE_BPSHistStatsNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor OfflineBPSSingleStatWithIPE_BPSHistStatsNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor OfflineBPSSingleStatWithIPE_BPSHistStatsNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor OfflineBPSSingleStatWithIPE_BPSHistStatsNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
    {6, 1, 1, 0, 0, NULL}, // BPSOutputPortStatsBHist
};

static ChiNode OfflineBPSSingleStatWithIPE_BPSHistStatsNodes[] =
{
    {NULL, 65538, 0, {1, OfflineBPSSingleStatWithIPE_BPSHistStatsNode65538_0InputPortDescriptors, 1, OfflineBPSSingleStatWithIPE_BPSHistStatsNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, OfflineBPSSingleStatWithIPE_BPSHistStatsNode65539_0InputPortDescriptors, 2, OfflineBPSSingleStatWithIPE_BPSHistStatsNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink OfflineBPSSingleStatWithIPE_BPSHistStatsLinks[] =
{
    {{65539, 0, 1, 0}, 1, OfflineBPSSingleStatWithIPE_BPSHistStats_Link0_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, OfflineBPSSingleStatWithIPE_BPSHistStats_Link1_IPE0_Out8Desc, {0}, {0, 0}},
    {{65539, 0, 6, 0}, 1, OfflineBPSSingleStatWithIPE_BPSHistStats_Link2_BPS0_Out6Desc, {0}, {0, 0}},
};

enum OfflineBPSSingleStatWithIPEPipelineIds
{
    BPSBGStats = 0,
    BPSHistStats = 1,
};

static ChiPipelineTargetCreateDescriptor OfflineBPSSingleStatWithIPE_pipelines[] =
{
    {"BPSBGStats", { 0, 2, OfflineBPSSingleStatWithIPE_BPSBGStatsNodes, 3, OfflineBPSSingleStatWithIPE_BPSBGStatsLinks, 0}, {2, OfflineBPSSingleStatWithIPE_BPSBGStats_sink_TargetDescriptors}, {1, OfflineBPSSingleStatWithIPE_BPSBGStats_source_TargetDescriptors}},  // BPSBGStats
    {"BPSHistStats", { 0, 2, OfflineBPSSingleStatWithIPE_BPSHistStatsNodes, 3, OfflineBPSSingleStatWithIPE_BPSHistStatsLinks, 0}, {2, OfflineBPSSingleStatWithIPE_BPSHistStats_sink_TargetDescriptors}, {1, OfflineBPSSingleStatWithIPE_BPSHistStats_source_TargetDescriptors}},  // BPSHistStats
};

/*==================== USECASE: TestPIPCam =======================*/

static ChiBufferFormat TestPIPCam_TARGET_BUFFER_OUTPUT_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestPIPCam_TARGET_BUFFER_RAW_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiBufferFormat TestPIPCam_TARGET_BUFFER_STATS_formats[] =
{
    ChiFormatBlob,
};

static ChiTarget TestPIPCam_TARGET_BUFFER_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2160
    },
    3,
    TestPIPCam_TARGET_BUFFER_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_OUTPUT

static ChiTarget TestPIPCam_TARGET_BUFFER_RAW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2160
    },
    2,
    TestPIPCam_TARGET_BUFFER_RAW_formats,
    NULL
}; // TARGET_BUFFER_RAW

static ChiTarget TestPIPCam_TARGET_BUFFER_STATS_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 691200, 1
    },
    1,
    TestPIPCam_TARGET_BUFFER_STATS_formats,
    NULL
}; // TARGET_BUFFER_STATS

static ChiTarget* TestPIPCam_Targets[] =
{
	&TestPIPCam_TARGET_BUFFER_OUTPUT_target,
	&TestPIPCam_TARGET_BUFFER_RAW_target,
	&TestPIPCam_TARGET_BUFFER_STATS_target
};

/*****************************Pipeline RDI1Only***************************/

static ChiLinkNodeDescriptor TestPIPCam_RDI1Only_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __94_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_RDI1Only_Link1_IFE0_Out9Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiTargetPortDescriptor TestPIPCam_RDI1Only_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &TestPIPCam_TARGET_BUFFER_RAW_target, 1, __94_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestPIPCam_RDI1OnlyNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestPIPCam_RDI1OnlyNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPIPCam_RDI1OnlyNode65536_0OutputPortDescriptors[] =
{
    {9, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI1
};

static ChiNode TestPIPCam_RDI1OnlyNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestPIPCam_RDI1OnlyNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, TestPIPCam_RDI1OnlyNode65536_0InputPortDescriptors, 1, TestPIPCam_RDI1OnlyNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestPIPCam_RDI1OnlyLinks[] =
{
    {{0, 0, 0, 0}, 1, TestPIPCam_RDI1Only_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 9, 0}, 1, TestPIPCam_RDI1Only_Link1_IFE0_Out9Desc, {0}, {0, 0}},
};

/*****************************Pipeline IPEAStats***************************/

static ChiLinkNodeDescriptor TestPIPCam_IPEAStats_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestPIPCam_IPEAStats_Link1_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __95_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEAStats_Link2_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __96_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEAStats_Link3_IFE0_Out8Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiLinkNodeDescriptor __97_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEAStats_Link4_IFE0_Out9Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiLinkNodeDescriptor __98_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 15 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEAStats_Link5_IFE0_Out15Desc[] =
{
    {2, 3, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiTargetPortDescriptor TestPIPCam_IPEAStats_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &TestPIPCam_TARGET_BUFFER_OUTPUT_target, 1, __95_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_RAW", &TestPIPCam_TARGET_BUFFER_RAW_target, 1, __96_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
    {"TARGET_BUFFER_RAW", &TestPIPCam_TARGET_BUFFER_RAW_target, 1, __97_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
    {"TARGET_BUFFER_STATS", &TestPIPCam_TARGET_BUFFER_STATS_target, 1, __98_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestPIPCam_IPEAStatsNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestPIPCam_IPEAStatsNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPIPCam_IPEAStatsNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {8, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI0
    {9, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI1
    {15, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsIHIST
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestPIPCam_IPEAStatsNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPIPCam_IPEAStatsNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNode TestPIPCam_IPEAStatsNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestPIPCam_IPEAStatsNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, TestPIPCam_IPEAStatsNode65536_0InputPortDescriptors, 4, TestPIPCam_IPEAStatsNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestPIPCam_IPEAStatsNode65538_0InputPortDescriptors, 1, TestPIPCam_IPEAStatsNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestPIPCam_IPEAStatsLinks[] =
{
    {{0, 0, 0, 0}, 1, TestPIPCam_IPEAStats_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestPIPCam_IPEAStats_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestPIPCam_IPEAStats_Link2_IPE0_Out8Desc, {0}, {0, 0}},
    {{65536, 0, 8, 0}, 1, TestPIPCam_IPEAStats_Link3_IFE0_Out8Desc, {0}, {0, 0}},
    {{65536, 0, 9, 0}, 1, TestPIPCam_IPEAStats_Link4_IFE0_Out9Desc, {0}, {0, 0}},
    {{65536, 0, 15, 0}, 1, TestPIPCam_IPEAStats_Link5_IFE0_Out15Desc, {0}, {0, 0}},
};

/*****************************Pipeline IPEACStats***************************/

static ChiLinkNodeDescriptor TestPIPCam_IPEACStats_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestPIPCam_IPEACStats_Link1_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __99_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEACStats_Link2_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __100_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 6 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEACStats_Link3_IFE0_Out6Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __101_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEACStats_Link4_IFE0_Out8Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiLinkNodeDescriptor __102_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEACStats_Link5_IFE0_Out9Desc[] =
{
    {2, 3, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiLinkNodeDescriptor __103_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 15 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEACStats_Link6_IFE0_Out15Desc[] =
{
    {2, 4, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiTargetPortDescriptor TestPIPCam_IPEACStats_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &TestPIPCam_TARGET_BUFFER_OUTPUT_target, 1, __99_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &TestPIPCam_TARGET_BUFFER_OUTPUT_target, 1, __100_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_RAW", &TestPIPCam_TARGET_BUFFER_RAW_target, 1, __101_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
    {"TARGET_BUFFER_RAW", &TestPIPCam_TARGET_BUFFER_RAW_target, 1, __102_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
    {"TARGET_BUFFER_STATS", &TestPIPCam_TARGET_BUFFER_STATS_target, 1, __103_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestPIPCam_IPEACStatsNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestPIPCam_IPEACStatsNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPIPCam_IPEACStatsNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {6, 1, 1, 0, 0, NULL}, // IFEOutputPortFD
    {8, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI0
    {9, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI1
    {15, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsIHIST
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestPIPCam_IPEACStatsNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPIPCam_IPEACStatsNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNode TestPIPCam_IPEACStatsNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestPIPCam_IPEACStatsNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, TestPIPCam_IPEACStatsNode65536_0InputPortDescriptors, 5, TestPIPCam_IPEACStatsNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestPIPCam_IPEACStatsNode65538_0InputPortDescriptors, 1, TestPIPCam_IPEACStatsNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestPIPCam_IPEACStatsLinks[] =
{
    {{0, 0, 0, 0}, 1, TestPIPCam_IPEACStats_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestPIPCam_IPEACStats_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestPIPCam_IPEACStats_Link2_IPE0_Out8Desc, {0}, {0, 0}},
    {{65536, 0, 6, 0}, 1, TestPIPCam_IPEACStats_Link3_IFE0_Out6Desc, {0}, {0, 0}},
    {{65536, 0, 8, 0}, 1, TestPIPCam_IPEACStats_Link4_IFE0_Out8Desc, {0}, {0, 0}},
    {{65536, 0, 9, 0}, 1, TestPIPCam_IPEACStats_Link5_IFE0_Out9Desc, {0}, {0, 0}},
    {{65536, 0, 15, 0}, 1, TestPIPCam_IPEACStats_Link6_IFE0_Out15Desc, {0}, {0, 0}},
};

/*****************************Pipeline IPEABCStats***************************/

static ChiLinkNodeDescriptor TestPIPCam_IPEABCStats_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestPIPCam_IPEABCStats_Link1_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __104_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEABCStats_Link2_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __105_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEABCStats_Link3_IPE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __106_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 6 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEABCStats_Link4_IFE0_Out6Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_OUTPUT
};

static ChiLinkNodeDescriptor __107_TARGET_BUFFER_STATS_Link_NodeDescriptors[] =
{
    {65536, 0, 15 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEABCStats_Link5_IFE0_Out15Desc[] =
{
    {2, 3, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATS
};

static ChiLinkNodeDescriptor __108_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestPIPCam_IPEABCStats_Link6_IFE0_Out9Desc[] =
{
    {2, 4, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiTargetPortDescriptor TestPIPCam_IPEABCStats_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_OUTPUT", &TestPIPCam_TARGET_BUFFER_OUTPUT_target, 1, __104_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &TestPIPCam_TARGET_BUFFER_OUTPUT_target, 1, __105_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_OUTPUT", &TestPIPCam_TARGET_BUFFER_OUTPUT_target, 1, __106_TARGET_BUFFER_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_OUTPUT
    {"TARGET_BUFFER_STATS", &TestPIPCam_TARGET_BUFFER_STATS_target, 1, __107_TARGET_BUFFER_STATS_Link_NodeDescriptors}, // TARGET_BUFFER_STATS
    {"TARGET_BUFFER_RAW", &TestPIPCam_TARGET_BUFFER_RAW_target, 1, __108_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestPIPCam_IPEABCStatsNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestPIPCam_IPEABCStatsNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPIPCam_IPEABCStatsNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {6, 1, 1, 0, 0, NULL}, // IFEOutputPortFD
    {15, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsIHIST
    {9, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI1
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestPIPCam_IPEABCStatsNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPIPCam_IPEABCStatsNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
};

static ChiNode TestPIPCam_IPEABCStatsNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestPIPCam_IPEABCStatsNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, TestPIPCam_IPEABCStatsNode65536_0InputPortDescriptors, 4, TestPIPCam_IPEABCStatsNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {1, TestPIPCam_IPEABCStatsNode65538_0InputPortDescriptors, 2, TestPIPCam_IPEABCStatsNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestPIPCam_IPEABCStatsLinks[] =
{
    {{0, 0, 0, 0}, 1, TestPIPCam_IPEABCStats_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestPIPCam_IPEABCStats_Link1_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 9, 10, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestPIPCam_IPEABCStats_Link2_IPE0_Out8Desc, {0}, {0, 0}},
    {{65538, 0, 9, 0}, 1, TestPIPCam_IPEABCStats_Link3_IPE0_Out9Desc, {0}, {0, 0}},
    {{65536, 0, 6, 0}, 1, TestPIPCam_IPEABCStats_Link4_IFE0_Out6Desc, {0}, {0, 0}},
    {{65536, 0, 15, 0}, 1, TestPIPCam_IPEABCStats_Link5_IFE0_Out15Desc, {0}, {0, 0}},
    {{65536, 0, 9, 0}, 1, TestPIPCam_IPEABCStats_Link6_IFE0_Out9Desc, {0}, {0, 0}},
};

enum TestPIPCamPipelineIds
{
    RDI1Only = 0,
    IPEAStats = 1,
    IPEACStats = 2,
    IPEABCStats = 3,
};

static ChiPipelineTargetCreateDescriptor TestPIPCam_pipelines[] =
{
    {"RDI1Only", { 0, 2, TestPIPCam_RDI1OnlyNodes, 2, TestPIPCam_RDI1OnlyLinks, 1}, {1, TestPIPCam_RDI1Only_sink_TargetDescriptors}, {0, NULL}},  // RDI1Only
    {"IPEAStats", { 0, 3, TestPIPCam_IPEAStatsNodes, 6, TestPIPCam_IPEAStatsLinks, 1}, {4, TestPIPCam_IPEAStats_sink_TargetDescriptors}, {0, NULL}},  // IPEAStats
    {"IPEACStats", { 0, 3, TestPIPCam_IPEACStatsNodes, 7, TestPIPCam_IPEACStatsLinks, 1}, {5, TestPIPCam_IPEACStats_sink_TargetDescriptors}, {0, NULL}},  // IPEACStats
    {"IPEABCStats", { 0, 3, TestPIPCam_IPEABCStatsNodes, 7, TestPIPCam_IPEABCStatsLinks, 1}, {5, TestPIPCam_IPEABCStats_sink_TargetDescriptors}, {0, NULL}},  // IPEABCStats
};

/*==================== USECASE: UsecaseGeneric2Streams =======================*/

static ChiBufferFormat UsecaseGeneric2Streams_TARGET_BUFFER_INPUT_formats[] =
{
    ChiFormatBlob,
    ChiFormatJpeg,
    ChiFormatP010,
    ChiFormatPD10,
    ChiFormatRawDepth,
    ChiFormatRawMIPI,
    ChiFormatRawMIPI8,
    ChiFormatRawMeta8BIT,
    ChiFormatRawPlain16,
    ChiFormatRawPlain64,
    ChiFormatRawPrivate,
    ChiFormatRawYUV8BIT,
    ChiFormatUBWCNV12,
    ChiFormatUBWCNV124R,
    ChiFormatUBWCTP10,
    ChiFormatY16,
    ChiFormatY8,
    ChiFormatYUV420NV12,
    ChiFormatYUV420NV12TP10,
    ChiFormatYUV420NV16,
    ChiFormatYUV420NV21,
    ChiFormatYUV420NV21TP10,
    ChiFormatYUV422NV16TP10,
};

static ChiBufferFormat UsecaseGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_formats[] =
{
    ChiFormatBlob,
    ChiFormatJpeg,
    ChiFormatP010,
    ChiFormatPD10,
    ChiFormatRawDepth,
    ChiFormatRawMIPI,
    ChiFormatRawMIPI8,
    ChiFormatRawMeta8BIT,
    ChiFormatRawPlain16,
    ChiFormatRawPlain64,
    ChiFormatRawPrivate,
    ChiFormatRawYUV8BIT,
    ChiFormatUBWCNV12,
    ChiFormatUBWCNV124R,
    ChiFormatUBWCTP10,
    ChiFormatY16,
    ChiFormatY8,
    ChiFormatYUV420NV12,
    ChiFormatYUV420NV12TP10,
    ChiFormatYUV420NV16,
    ChiFormatYUV420NV21,
    ChiFormatYUV420NV21TP10,
    ChiFormatYUV422NV16TP10,
};

static ChiBufferFormat UsecaseGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_formats[] =
{
    ChiFormatBlob,
    ChiFormatJpeg,
    ChiFormatP010,
    ChiFormatPD10,
    ChiFormatRawDepth,
    ChiFormatRawMIPI,
    ChiFormatRawMIPI8,
    ChiFormatRawMeta8BIT,
    ChiFormatRawPlain16,
    ChiFormatRawPlain64,
    ChiFormatRawPrivate,
    ChiFormatRawYUV8BIT,
    ChiFormatUBWCNV12,
    ChiFormatUBWCNV124R,
    ChiFormatUBWCTP10,
    ChiFormatY16,
    ChiFormatY8,
    ChiFormatYUV420NV12,
    ChiFormatYUV420NV12TP10,
    ChiFormatYUV420NV16,
    ChiFormatYUV420NV21,
    ChiFormatYUV420NV21TP10,
    ChiFormatYUV422NV16TP10,
};

static ChiTarget UsecaseGeneric2Streams_TARGET_BUFFER_INPUT_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    23,
    UsecaseGeneric2Streams_TARGET_BUFFER_INPUT_formats,
    NULL
}; // TARGET_BUFFER_INPUT

static ChiTarget UsecaseGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    23,
    UsecaseGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_STATIC_OUTPUT

static ChiTarget UsecaseGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    23,
    UsecaseGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_CONFIG_OUTPUT

static ChiTarget* UsecaseGeneric2Streams_Targets[] =
{
	&UsecaseGeneric2Streams_TARGET_BUFFER_INPUT_target,
	&UsecaseGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target,
	&UsecaseGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target
};

/*****************************Pipeline IFEGeneric2Stream***************************/

static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IFEGeneric2Stream_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __109_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 8 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IFEGeneric2Stream_Link1_IFE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiLinkNodeDescriptor __110_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 0 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IFEGeneric2Stream_Link2_IFE0_Out0Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric2Streams_IFEGeneric2Stream_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __109_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
    {"TARGET_BUFFER_STATIC_OUTPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target, 1, __110_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_STATIC_OUTPUT
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamNode65536_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI0
    {0, 1, 1, 0, 0, NULL}, // IFEOutputPortFull
};

static ChiNode UsecaseGeneric2Streams_IFEGeneric2StreamNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, UsecaseGeneric2Streams_IFEGeneric2StreamNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, UsecaseGeneric2Streams_IFEGeneric2StreamNode65536_0InputPortDescriptors, 2, UsecaseGeneric2Streams_IFEGeneric2StreamNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseGeneric2Streams_IFEGeneric2StreamLinks[] =
{
    {{0, 0, 0, 0}, 1, UsecaseGeneric2Streams_IFEGeneric2Stream_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 8, 0}, 1, UsecaseGeneric2Streams_IFEGeneric2Stream_Link1_IFE0_Out8Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, UsecaseGeneric2Streams_IFEGeneric2Stream_Link2_IFE0_Out0Desc, {0}, {0, 0}},
};

/*****************************Pipeline IFEGeneric2StreamTestgen***************************/

static ChiLinkNodeDescriptor __111_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 8 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamTestgen_Link0_IFE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiLinkNodeDescriptor __112_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 0 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamTestgen_Link1_IFE0_Out0Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __111_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
    {"TARGET_BUFFER_STATIC_OUTPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target, 1, __112_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_STATIC_OUTPUT
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamTestgenNode65536_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI0
    {0, 1, 1, 0, 0, NULL}, // IFEOutputPortFull
};

static ChiNode UsecaseGeneric2Streams_IFEGeneric2StreamTestgenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 2, UsecaseGeneric2Streams_IFEGeneric2StreamTestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseGeneric2Streams_IFEGeneric2StreamTestgenLinks[] =
{
    {{65536, 0, 8, 0}, 1, UsecaseGeneric2Streams_IFEGeneric2StreamTestgen_Link0_IFE0_Out8Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, UsecaseGeneric2Streams_IFEGeneric2StreamTestgen_Link1_IFE0_Out0Desc, {0}, {0, 0}},
};

/*****************************Pipeline IFEGeneric2StreamDisplay***************************/

static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamDisplay_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __113_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 8 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamDisplay_Link1_IFE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiLinkNodeDescriptor __114_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 22 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamDisplay_Link2_IFE0_Out22Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamDisplay_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __113_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
    {"TARGET_BUFFER_STATIC_OUTPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target, 1, __114_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_STATIC_OUTPUT
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamDisplayNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamDisplayNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamDisplayNode65536_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI0
    {22, 1, 1, 0, 0, NULL}, // IFEOutputPortDisplayFull
};

static ChiNode UsecaseGeneric2Streams_IFEGeneric2StreamDisplayNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, UsecaseGeneric2Streams_IFEGeneric2StreamDisplayNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, UsecaseGeneric2Streams_IFEGeneric2StreamDisplayNode65536_0InputPortDescriptors, 2, UsecaseGeneric2Streams_IFEGeneric2StreamDisplayNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseGeneric2Streams_IFEGeneric2StreamDisplayLinks[] =
{
    {{0, 0, 0, 0}, 1, UsecaseGeneric2Streams_IFEGeneric2StreamDisplay_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 8, 0}, 1, UsecaseGeneric2Streams_IFEGeneric2StreamDisplay_Link1_IFE0_Out8Desc, {0}, {0, 0}},
    {{65536, 0, 22, 0}, 1, UsecaseGeneric2Streams_IFEGeneric2StreamDisplay_Link2_IFE0_Out22Desc, {0}, {0, 0}},
};

/*****************************Pipeline IFEGeneric2StreamDisplayTestgen***************************/

static ChiLinkNodeDescriptor __115_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 8 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamDisplayTestgen_Link0_IFE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiLinkNodeDescriptor __116_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors[] =
{
    {65536, 0, 22 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamDisplayTestgen_Link1_IFE0_Out22Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamDisplayTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __115_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
    {"TARGET_BUFFER_STATIC_OUTPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target, 1, __116_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_STATIC_OUTPUT
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric2Streams_IFEGeneric2StreamDisplayTestgenNode65536_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI0
    {22, 1, 1, 0, 0, NULL}, // IFEOutputPortDisplayFull
};

static ChiNode UsecaseGeneric2Streams_IFEGeneric2StreamDisplayTestgenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 2, UsecaseGeneric2Streams_IFEGeneric2StreamDisplayTestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseGeneric2Streams_IFEGeneric2StreamDisplayTestgenLinks[] =
{
    {{65536, 0, 8, 0}, 1, UsecaseGeneric2Streams_IFEGeneric2StreamDisplayTestgen_Link0_IFE0_Out8Desc, {0}, {0, 0}},
    {{65536, 0, 22, 0}, 1, UsecaseGeneric2Streams_IFEGeneric2StreamDisplayTestgen_Link1_IFE0_Out22Desc, {0}, {0, 0}},
};

/*****************************Pipeline BPSGeneric2Stream***************************/

static ChiLinkNodeDescriptor UsecaseGeneric2Streams_BPSGeneric2Stream_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor __117_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65539, 0, 2 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric2Streams_BPSGeneric2Stream_Link0_BPS0_Out2Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiLinkNodeDescriptor __118_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors[] =
{
    {65539, 0, 1 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric2Streams_BPSGeneric2Stream_Link1_BPS0_Out1Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric2Streams_BPSGeneric2Stream_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __117_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
    {"TARGET_BUFFER_STATIC_OUTPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target, 1, __118_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric2Streams_BPSGeneric2Stream_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_INPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_INPUT_target, 1, UsecaseGeneric2Streams_BPSGeneric2Stream_source_Link_0NodeDescriptors}, // TARGET_BUFFER_INPUT
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseGeneric2Streams_BPSGeneric2StreamNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric2Streams_BPSGeneric2StreamNode65539_0OutputPortDescriptors[] =
{
    {2, 1, 1, 0, 0, NULL}, // BPSOutputPortDS4
    {1, 1, 1, 0, 0, NULL}, // BPSOutputPortFull
};

static ChiNode UsecaseGeneric2Streams_BPSGeneric2StreamNodes[] =
{
    {NULL, 65539, 0, {1, UsecaseGeneric2Streams_BPSGeneric2StreamNode65539_0InputPortDescriptors, 2, UsecaseGeneric2Streams_BPSGeneric2StreamNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseGeneric2Streams_BPSGeneric2StreamLinks[] =
{
    {{65539, 0, 2, 0}, 1, UsecaseGeneric2Streams_BPSGeneric2Stream_Link0_BPS0_Out2Desc, {0}, {0, 0}},
    {{65539, 0, 1, 0}, 1, UsecaseGeneric2Streams_BPSGeneric2Stream_Link1_BPS0_Out1Desc, {0}, {0, 0}},
};

/*****************************Pipeline IPEGeneric2StreamDisplay***************************/

static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IPEGeneric2StreamDisplay_source_Link_0NodeDescriptors[] =
{
    {65538, 0, 0},
};
static ChiLinkNodeDescriptor __119_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IPEGeneric2StreamDisplay_Link0_IPE0_Out9Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiLinkNodeDescriptor __120_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor UsecaseGeneric2Streams_IPEGeneric2StreamDisplay_Link1_IPE0_Out8Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric2Streams_IPEGeneric2StreamDisplay_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __119_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
    {"TARGET_BUFFER_STATIC_OUTPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target, 1, __120_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseGeneric2Streams_IPEGeneric2StreamDisplay_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_INPUT", &UsecaseGeneric2Streams_TARGET_BUFFER_INPUT_target, 1, UsecaseGeneric2Streams_IPEGeneric2StreamDisplay_source_Link_0NodeDescriptors}, // TARGET_BUFFER_INPUT
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseGeneric2Streams_IPEGeneric2StreamDisplayNode65538_0InputPortDescriptors[] =
{
    {0, 1, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseGeneric2Streams_IPEGeneric2StreamDisplayNode65538_0OutputPortDescriptors[] =
{
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

static ChiNode UsecaseGeneric2Streams_IPEGeneric2StreamDisplayNodes[] =
{
    {NULL, 65538, 0, {1, UsecaseGeneric2Streams_IPEGeneric2StreamDisplayNode65538_0InputPortDescriptors, 2, UsecaseGeneric2Streams_IPEGeneric2StreamDisplayNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseGeneric2Streams_IPEGeneric2StreamDisplayLinks[] =
{
    {{65538, 0, 9, 0}, 1, UsecaseGeneric2Streams_IPEGeneric2StreamDisplay_Link0_IPE0_Out9Desc, {0}, {0, 0}},
    {{65538, 0, 8, 0}, 1, UsecaseGeneric2Streams_IPEGeneric2StreamDisplay_Link1_IPE0_Out8Desc, {0}, {0, 0}},
};

enum UsecaseGeneric2StreamsPipelineIds
{
    IFEGeneric2Stream = 0,
    IFEGeneric2StreamTestgen = 1,
    IFEGeneric2StreamDisplay = 2,
    IFEGeneric2StreamDisplayTestgen = 3,
    BPSGeneric2Stream = 4,
    IPEGeneric2StreamDisplay = 5,
};

static ChiPipelineTargetCreateDescriptor UsecaseGeneric2Streams_pipelines[] =
{
    {"IFEGeneric2Stream", { 0, 2, UsecaseGeneric2Streams_IFEGeneric2StreamNodes, 3, UsecaseGeneric2Streams_IFEGeneric2StreamLinks, 1}, {2, UsecaseGeneric2Streams_IFEGeneric2Stream_sink_TargetDescriptors}, {0, NULL}},  // IFEGeneric2Stream
    {"IFEGeneric2StreamTestgen", { 0, 1, UsecaseGeneric2Streams_IFEGeneric2StreamTestgenNodes, 2, UsecaseGeneric2Streams_IFEGeneric2StreamTestgenLinks, 1}, {2, UsecaseGeneric2Streams_IFEGeneric2StreamTestgen_sink_TargetDescriptors}, {0, NULL}},  // IFEGeneric2StreamTestgen
    {"IFEGeneric2StreamDisplay", { 0, 2, UsecaseGeneric2Streams_IFEGeneric2StreamDisplayNodes, 3, UsecaseGeneric2Streams_IFEGeneric2StreamDisplayLinks, 1}, {2, UsecaseGeneric2Streams_IFEGeneric2StreamDisplay_sink_TargetDescriptors}, {0, NULL}},  // IFEGeneric2StreamDisplay
    {"IFEGeneric2StreamDisplayTestgen", { 0, 1, UsecaseGeneric2Streams_IFEGeneric2StreamDisplayTestgenNodes, 2, UsecaseGeneric2Streams_IFEGeneric2StreamDisplayTestgenLinks, 1}, {2, UsecaseGeneric2Streams_IFEGeneric2StreamDisplayTestgen_sink_TargetDescriptors}, {0, NULL}},  // IFEGeneric2StreamDisplayTestgen
    {"BPSGeneric2Stream", { 0, 1, UsecaseGeneric2Streams_BPSGeneric2StreamNodes, 2, UsecaseGeneric2Streams_BPSGeneric2StreamLinks, 0}, {2, UsecaseGeneric2Streams_BPSGeneric2Stream_sink_TargetDescriptors}, {1, UsecaseGeneric2Streams_BPSGeneric2Stream_source_TargetDescriptors}},  // BPSGeneric2Stream
    {"IPEGeneric2StreamDisplay", { 0, 1, UsecaseGeneric2Streams_IPEGeneric2StreamDisplayNodes, 2, UsecaseGeneric2Streams_IPEGeneric2StreamDisplayLinks, 0}, {2, UsecaseGeneric2Streams_IPEGeneric2StreamDisplay_sink_TargetDescriptors}, {1, UsecaseGeneric2Streams_IPEGeneric2StreamDisplay_source_TargetDescriptors}},  // IPEGeneric2StreamDisplay
};

/*==================== USECASE: UsecaseMimasGeneric2Streams =======================*/

static ChiBufferFormat UsecaseMimasGeneric2Streams_TARGET_BUFFER_INPUT_formats[] =
{
    ChiFormatBlob,
    ChiFormatJpeg,
    ChiFormatP010,
    ChiFormatPD10,
    ChiFormatRawDepth,
    ChiFormatRawMIPI,
    ChiFormatRawMIPI8,
    ChiFormatRawMeta8BIT,
    ChiFormatRawPlain16,
    ChiFormatRawPlain64,
    ChiFormatRawPrivate,
    ChiFormatRawYUV8BIT,
    ChiFormatUBWCNV12,
    ChiFormatUBWCNV124R,
    ChiFormatUBWCTP10,
    ChiFormatY16,
    ChiFormatY8,
    ChiFormatYUV420NV12,
    ChiFormatYUV420NV12TP10,
    ChiFormatYUV420NV16,
    ChiFormatYUV420NV21,
    ChiFormatYUV420NV21TP10,
    ChiFormatYUV422NV16TP10,
};

static ChiBufferFormat UsecaseMimasGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_formats[] =
{
    ChiFormatBlob,
    ChiFormatJpeg,
    ChiFormatP010,
    ChiFormatPD10,
    ChiFormatRawDepth,
    ChiFormatRawMIPI,
    ChiFormatRawMIPI8,
    ChiFormatRawMeta8BIT,
    ChiFormatRawPlain16,
    ChiFormatRawPlain64,
    ChiFormatRawPrivate,
    ChiFormatRawYUV8BIT,
    ChiFormatUBWCNV12,
    ChiFormatUBWCNV124R,
    ChiFormatUBWCTP10,
    ChiFormatY16,
    ChiFormatY8,
    ChiFormatYUV420NV12,
    ChiFormatYUV420NV12TP10,
    ChiFormatYUV420NV16,
    ChiFormatYUV420NV21,
    ChiFormatYUV420NV21TP10,
    ChiFormatYUV422NV16TP10,
};

static ChiBufferFormat UsecaseMimasGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_formats[] =
{
    ChiFormatBlob,
    ChiFormatJpeg,
    ChiFormatP010,
    ChiFormatPD10,
    ChiFormatRawDepth,
    ChiFormatRawMIPI,
    ChiFormatRawMIPI8,
    ChiFormatRawMeta8BIT,
    ChiFormatRawPlain16,
    ChiFormatRawPlain64,
    ChiFormatRawPrivate,
    ChiFormatRawYUV8BIT,
    ChiFormatUBWCNV12,
    ChiFormatUBWCNV124R,
    ChiFormatUBWCTP10,
    ChiFormatY16,
    ChiFormatY8,
    ChiFormatYUV420NV12,
    ChiFormatYUV420NV12TP10,
    ChiFormatYUV420NV16,
    ChiFormatYUV420NV21,
    ChiFormatYUV420NV21TP10,
    ChiFormatYUV422NV16TP10,
};

static ChiTarget UsecaseMimasGeneric2Streams_TARGET_BUFFER_INPUT_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    23,
    UsecaseMimasGeneric2Streams_TARGET_BUFFER_INPUT_formats,
    NULL
}; // TARGET_BUFFER_INPUT

static ChiTarget UsecaseMimasGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    23,
    UsecaseMimasGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_STATIC_OUTPUT

static ChiTarget UsecaseMimasGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 8000, 6000
    },
    23,
    UsecaseMimasGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_formats,
    NULL
}; // TARGET_BUFFER_CONFIG_OUTPUT

static ChiTarget* UsecaseMimasGeneric2Streams_Targets[] =
{
	&UsecaseMimasGeneric2Streams_TARGET_BUFFER_INPUT_target,
	&UsecaseMimasGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target,
	&UsecaseMimasGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target
};

/*****************************Pipeline TFEGeneric2StreamTestgen***************************/

static ChiLinkNodeDescriptor __121_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65544, 0, 4 }, 
};
static ChiLinkNodeDescriptor UsecaseMimasGeneric2Streams_TFEGeneric2StreamTestgen_Link0_TFE0_Out4Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiLinkNodeDescriptor __122_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors[] =
{
    {65544, 0, 1 }, 
};
static ChiLinkNodeDescriptor UsecaseMimasGeneric2Streams_TFEGeneric2StreamTestgen_Link1_TFE0_Out1Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseMimasGeneric2Streams_TFEGeneric2StreamTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseMimasGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __121_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
    {"TARGET_BUFFER_STATIC_OUTPUT", &UsecaseMimasGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target, 1, __122_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_STATIC_OUTPUT
};

// TFE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseMimasGeneric2Streams_TFEGeneric2StreamTestgenNode65544_0OutputPortDescriptors[] =
{
    {4, 1, 1, 0, 0, NULL}, // TFEOutputPortRDI0
    {1, 1, 1, 0, 0, NULL}, // TFEOutputPortFull
};

static ChiNode UsecaseMimasGeneric2Streams_TFEGeneric2StreamTestgenNodes[] =
{
    {NULL, 65544, 0, {0, NULL, 2, UsecaseMimasGeneric2Streams_TFEGeneric2StreamTestgenNode65544_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseMimasGeneric2Streams_TFEGeneric2StreamTestgenLinks[] =
{
    {{65544, 0, 4, 0}, 1, UsecaseMimasGeneric2Streams_TFEGeneric2StreamTestgen_Link0_TFE0_Out4Desc, {0}, {0, 0}},
    {{65544, 0, 1, 0}, 1, UsecaseMimasGeneric2Streams_TFEGeneric2StreamTestgen_Link1_TFE0_Out1Desc, {0}, {0, 0}},
};

/*****************************Pipeline OPEGeneric2StreamDisplay***************************/

static ChiLinkNodeDescriptor UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplay_source_Link_0NodeDescriptors[] =
{
    {65545, 0, 1},
};
static ChiLinkNodeDescriptor __123_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65545, 0, 1 }, 
};
static ChiLinkNodeDescriptor UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplay_Link0_OPE0_Out1Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiLinkNodeDescriptor __124_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors[] =
{
    {65545, 0, 2 }, 
};
static ChiLinkNodeDescriptor UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplay_Link1_OPE0_Out2Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplay_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseMimasGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __123_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
    {"TARGET_BUFFER_STATIC_OUTPUT", &UsecaseMimasGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target, 1, __124_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplay_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_INPUT", &UsecaseMimasGeneric2Streams_TARGET_BUFFER_INPUT_target, 1, UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplay_source_Link_0NodeDescriptors}, // TARGET_BUFFER_INPUT
};

// OPE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplayNode65545_0InputPortDescriptors[] =
{
    {1, 1, 0}, // OPEInputPortFull
};

// OPE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplayNode65545_0OutputPortDescriptors[] =
{
    {1, 1, 1, 0, 0, NULL}, // OPEOutputPortVideo
    {2, 1, 1, 0, 0, NULL}, // OPEOutputPortDisplay
};

static ChiNode UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplayNodes[] =
{
    {NULL, 65545, 0, {1, UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplayNode65545_0InputPortDescriptors, 2, UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplayNode65545_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplayLinks[] =
{
    {{65545, 0, 1, 0}, 1, UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplay_Link0_OPE0_Out1Desc, {0}, {0, 0}},
    {{65545, 0, 2, 0}, 1, UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplay_Link1_OPE0_Out2Desc, {0}, {0, 0}},
};

/*****************************Pipeline OPEGeneric3StreamDisplayStats***************************/

static ChiLinkNodeDescriptor UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStats_source_Link_0NodeDescriptors[] =
{
    {65545, 0, 1},
};
static ChiLinkNodeDescriptor __125_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors[] =
{
    {65545, 0, 4 }, 
};
static ChiLinkNodeDescriptor UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStats_Link0_OPE0_Out4Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CONFIG_OUTPUT
};

static ChiLinkNodeDescriptor __126_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors[] =
{
    {65545, 0, 1 }, 
};
static ChiLinkNodeDescriptor UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStats_Link1_OPE0_Out1Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATIC_OUTPUT
};

static ChiLinkNodeDescriptor __127_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors[] =
{
    {65545, 0, 2 }, 
};
static ChiLinkNodeDescriptor UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStats_Link2_OPE0_Out2Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStats_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_CONFIG_OUTPUT", &UsecaseMimasGeneric2Streams_TARGET_BUFFER_CONFIG_OUTPUT_target, 1, __125_TARGET_BUFFER_CONFIG_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_CONFIG_OUTPUT
    {"TARGET_BUFFER_STATIC_OUTPUT", &UsecaseMimasGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target, 1, __126_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_STATIC_OUTPUT
    {"TARGET_BUFFER_STATIC_OUTPUT", &UsecaseMimasGeneric2Streams_TARGET_BUFFER_STATIC_OUTPUT_target, 1, __127_TARGET_BUFFER_STATIC_OUTPUT_Link_NodeDescriptors}, // TARGET_BUFFER_STATIC_OUTPUT
};

static ChiTargetPortDescriptor UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStats_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_INPUT", &UsecaseMimasGeneric2Streams_TARGET_BUFFER_INPUT_target, 1, UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStats_source_Link_0NodeDescriptors}, // TARGET_BUFFER_INPUT
};

// OPE0 Input Port Descriptors
static ChiInputPortDescriptor UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStatsNode65545_0InputPortDescriptors[] =
{
    {1, 1, 0}, // OPEInputPortFull
};

// OPE0 Output Port Descriptors
static ChiOutputPortDescriptor UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStatsNode65545_0OutputPortDescriptors[] =
{
    {4, 1, 1, 0, 0, NULL}, // OPEOutputPortStat
    {1, 1, 1, 0, 0, NULL}, // OPEOutputPortVideo
    {2, 1, 1, 0, 0, NULL}, // OPEOutputPortDisplay
};

static ChiNode UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStatsNodes[] =
{
    {NULL, 65545, 0, {1, UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStatsNode65545_0InputPortDescriptors, 3, UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStatsNode65545_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStatsLinks[] =
{
    {{65545, 0, 4, 0}, 1, UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStats_Link0_OPE0_Out4Desc, {0}, {0, 0}},
    {{65545, 0, 1, 0}, 1, UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStats_Link1_OPE0_Out1Desc, {0}, {0, 0}},
    {{65545, 0, 2, 0}, 1, UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStats_Link2_OPE0_Out2Desc, {0}, {0, 0}},
};

enum UsecaseMimasGeneric2StreamsPipelineIds
{
    TFEGeneric2StreamTestgen = 0,
    OPEGeneric2StreamDisplay = 1,
    OPEGeneric3StreamDisplayStats = 2,
};

static ChiPipelineTargetCreateDescriptor UsecaseMimasGeneric2Streams_pipelines[] =
{
    {"TFEGeneric2StreamTestgen", { 0, 1, UsecaseMimasGeneric2Streams_TFEGeneric2StreamTestgenNodes, 2, UsecaseMimasGeneric2Streams_TFEGeneric2StreamTestgenLinks, 1}, {2, UsecaseMimasGeneric2Streams_TFEGeneric2StreamTestgen_sink_TargetDescriptors}, {0, NULL}},  // TFEGeneric2StreamTestgen
    {"OPEGeneric2StreamDisplay", { 0, 1, UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplayNodes, 2, UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplayLinks, 0}, {2, UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplay_sink_TargetDescriptors}, {1, UsecaseMimasGeneric2Streams_OPEGeneric2StreamDisplay_source_TargetDescriptors}},  // OPEGeneric2StreamDisplay
    {"OPEGeneric3StreamDisplayStats", { 0, 1, UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStatsNodes, 3, UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStatsLinks, 0}, {3, UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStats_sink_TargetDescriptors}, {1, UsecaseMimasGeneric2Streams_OPEGeneric3StreamDisplayStats_source_TargetDescriptors}},  // OPEGeneric3StreamDisplayStats
};

/*==================== USECASE: OfflineBPSStats =======================*/

static ChiBufferFormat OfflineBPSStats_TARGET_BUFFER_RAW_IN_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiBufferFormat OfflineBPSStats_TARGET_BUFFER_BPS_FULL_formats[] =
{
    ChiFormatUBWCTP10,
};

static ChiBufferFormat OfflineBPSStats_TARGET_BUFFER_BPS_BG_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat OfflineBPSStats_TARGET_BUFFER_BPS_BHIST_formats[] =
{
    ChiFormatBlob,
};

static ChiTarget OfflineBPSStats_TARGET_BUFFER_RAW_IN_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    2,
    OfflineBPSStats_TARGET_BUFFER_RAW_IN_formats,
    NULL
}; // TARGET_BUFFER_RAW_IN

static ChiTarget OfflineBPSStats_TARGET_BUFFER_BPS_FULL_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    1,
    OfflineBPSStats_TARGET_BUFFER_BPS_FULL_formats,
    NULL
}; // TARGET_BUFFER_BPS_FULL

static ChiTarget OfflineBPSStats_TARGET_BUFFER_BPS_BG_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 691200, 1
    },
    1,
    OfflineBPSStats_TARGET_BUFFER_BPS_BG_formats,
    NULL
}; // TARGET_BUFFER_BPS_BG

static ChiTarget OfflineBPSStats_TARGET_BUFFER_BPS_BHIST_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 3072, 1
    },
    1,
    OfflineBPSStats_TARGET_BUFFER_BPS_BHIST_formats,
    NULL
}; // TARGET_BUFFER_BPS_BHIST

static ChiTarget* OfflineBPSStats_Targets[] =
{
	&OfflineBPSStats_TARGET_BUFFER_RAW_IN_target,
	&OfflineBPSStats_TARGET_BUFFER_BPS_FULL_target,
	&OfflineBPSStats_TARGET_BUFFER_BPS_BG_target,
	&OfflineBPSStats_TARGET_BUFFER_BPS_BHIST_target
};

/*****************************Pipeline BPSStats***************************/

static ChiLinkNodeDescriptor OfflineBPSStats_BPSStats_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor __128_TARGET_BUFFER_BPS_FULL_Link_NodeDescriptors[] =
{
    {65539, 0, 1 }, 
};
static ChiLinkNodeDescriptor OfflineBPSStats_BPSStats_Link0_BPS0_Out1Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BPS_FULL
};

static ChiLinkNodeDescriptor __129_TARGET_BUFFER_BPS_BG_Link_NodeDescriptors[] =
{
    {65539, 0, 5 }, 
};
static ChiLinkNodeDescriptor OfflineBPSStats_BPSStats_Link1_BPS0_Out5Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BPS_BG
};

static ChiLinkNodeDescriptor __130_TARGET_BUFFER_BPS_BHIST_Link_NodeDescriptors[] =
{
    {65539, 0, 6 }, 
};
static ChiLinkNodeDescriptor OfflineBPSStats_BPSStats_Link2_BPS0_Out6Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BPS_BHIST
};

static ChiTargetPortDescriptor OfflineBPSStats_BPSStats_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_BPS_FULL", &OfflineBPSStats_TARGET_BUFFER_BPS_FULL_target, 1, __128_TARGET_BUFFER_BPS_FULL_Link_NodeDescriptors}, // TARGET_BUFFER_BPS_FULL
    {"TARGET_BUFFER_BPS_BG", &OfflineBPSStats_TARGET_BUFFER_BPS_BG_target, 1, __129_TARGET_BUFFER_BPS_BG_Link_NodeDescriptors}, // TARGET_BUFFER_BPS_BG
    {"TARGET_BUFFER_BPS_BHIST", &OfflineBPSStats_TARGET_BUFFER_BPS_BHIST_target, 1, __130_TARGET_BUFFER_BPS_BHIST_Link_NodeDescriptors}, // TARGET_BUFFER_BPS_BHIST
};

static ChiTargetPortDescriptor OfflineBPSStats_BPSStats_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW_IN", &OfflineBPSStats_TARGET_BUFFER_RAW_IN_target, 1, OfflineBPSStats_BPSStats_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW_IN
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor OfflineBPSStats_BPSStatsNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor OfflineBPSStats_BPSStatsNode65539_0OutputPortDescriptors[] =
{
    {1, 1, 1, 0, 0, NULL}, // BPSOutputPortFull
    {5, 1, 1, 0, 0, NULL}, // BPSOutputPortStatsBG
    {6, 1, 1, 0, 0, NULL}, // BPSOutputPortStatsBHist
};

static ChiNode OfflineBPSStats_BPSStatsNodes[] =
{
    {NULL, 65539, 0, {1, OfflineBPSStats_BPSStatsNode65539_0InputPortDescriptors, 3, OfflineBPSStats_BPSStatsNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink OfflineBPSStats_BPSStatsLinks[] =
{
    {{65539, 0, 1, 0}, 1, OfflineBPSStats_BPSStats_Link0_BPS0_Out1Desc, {0}, {0, 0}},
    {{65539, 0, 5, 0}, 1, OfflineBPSStats_BPSStats_Link1_BPS0_Out5Desc, {0}, {0, 0}},
    {{65539, 0, 6, 0}, 1, OfflineBPSStats_BPSStats_Link2_BPS0_Out6Desc, {0}, {0, 0}},
};

enum OfflineBPSStatsPipelineIds
{
    BPSStats = 0,
};

static ChiPipelineTargetCreateDescriptor OfflineBPSStats_pipelines[] =
{
    {"BPSStats", { 0, 1, OfflineBPSStats_BPSStatsNodes, 3, OfflineBPSStats_BPSStatsLinks, 0}, {3, OfflineBPSStats_BPSStats_sink_TargetDescriptors}, {1, OfflineBPSStats_BPSStats_source_TargetDescriptors}},  // BPSStats
};

/*==================== USECASE: OfflineBPSStatsWithIPE =======================*/

static ChiBufferFormat OfflineBPSStatsWithIPE_TARGET_BUFFER_RAW_IN_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiBufferFormat OfflineBPSStatsWithIPE_TARGET_BUFFER_IPE_DISPLAY_formats[] =
{
    ChiFormatYUV420NV12,
};

static ChiBufferFormat OfflineBPSStatsWithIPE_TARGET_BUFFER_BPS_BG_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat OfflineBPSStatsWithIPE_TARGET_BUFFER_BPS_BHIST_formats[] =
{
    ChiFormatBlob,
};

static ChiTarget OfflineBPSStatsWithIPE_TARGET_BUFFER_RAW_IN_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    2,
    OfflineBPSStatsWithIPE_TARGET_BUFFER_RAW_IN_formats,
    NULL
}; // TARGET_BUFFER_RAW_IN

static ChiTarget OfflineBPSStatsWithIPE_TARGET_BUFFER_IPE_DISPLAY_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    1,
    OfflineBPSStatsWithIPE_TARGET_BUFFER_IPE_DISPLAY_formats,
    NULL
}; // TARGET_BUFFER_IPE_DISPLAY

static ChiTarget OfflineBPSStatsWithIPE_TARGET_BUFFER_BPS_BG_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 691200, 1
    },
    1,
    OfflineBPSStatsWithIPE_TARGET_BUFFER_BPS_BG_formats,
    NULL
}; // TARGET_BUFFER_BPS_BG

static ChiTarget OfflineBPSStatsWithIPE_TARGET_BUFFER_BPS_BHIST_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 3072, 1
    },
    1,
    OfflineBPSStatsWithIPE_TARGET_BUFFER_BPS_BHIST_formats,
    NULL
}; // TARGET_BUFFER_BPS_BHIST

static ChiTarget* OfflineBPSStatsWithIPE_Targets[] =
{
	&OfflineBPSStatsWithIPE_TARGET_BUFFER_RAW_IN_target,
	&OfflineBPSStatsWithIPE_TARGET_BUFFER_IPE_DISPLAY_target,
	&OfflineBPSStatsWithIPE_TARGET_BUFFER_BPS_BG_target,
	&OfflineBPSStatsWithIPE_TARGET_BUFFER_BPS_BHIST_target
};

/*****************************Pipeline BPSAllStats***************************/

static ChiLinkNodeDescriptor OfflineBPSStatsWithIPE_BPSAllStats_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor OfflineBPSStatsWithIPE_BPSAllStats_Link0_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor __131_TARGET_BUFFER_IPE_DISPLAY_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor OfflineBPSStatsWithIPE_BPSAllStats_Link1_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_IPE_DISPLAY
};

static ChiLinkNodeDescriptor __132_TARGET_BUFFER_BPS_BG_Link_NodeDescriptors[] =
{
    {65539, 0, 5 }, 
};
static ChiLinkNodeDescriptor OfflineBPSStatsWithIPE_BPSAllStats_Link2_BPS0_Out5Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BPS_BG
};

static ChiLinkNodeDescriptor __133_TARGET_BUFFER_BPS_BHIST_Link_NodeDescriptors[] =
{
    {65539, 0, 6 }, 
};
static ChiLinkNodeDescriptor OfflineBPSStatsWithIPE_BPSAllStats_Link3_BPS0_Out6Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BPS_BHIST
};

static ChiTargetPortDescriptor OfflineBPSStatsWithIPE_BPSAllStats_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_IPE_DISPLAY", &OfflineBPSStatsWithIPE_TARGET_BUFFER_IPE_DISPLAY_target, 1, __131_TARGET_BUFFER_IPE_DISPLAY_Link_NodeDescriptors}, // TARGET_BUFFER_IPE_DISPLAY
    {"TARGET_BUFFER_BPS_BG", &OfflineBPSStatsWithIPE_TARGET_BUFFER_BPS_BG_target, 1, __132_TARGET_BUFFER_BPS_BG_Link_NodeDescriptors}, // TARGET_BUFFER_BPS_BG
    {"TARGET_BUFFER_BPS_BHIST", &OfflineBPSStatsWithIPE_TARGET_BUFFER_BPS_BHIST_target, 1, __133_TARGET_BUFFER_BPS_BHIST_Link_NodeDescriptors}, // TARGET_BUFFER_BPS_BHIST
};

static ChiTargetPortDescriptor OfflineBPSStatsWithIPE_BPSAllStats_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW_IN", &OfflineBPSStatsWithIPE_TARGET_BUFFER_RAW_IN_target, 1, OfflineBPSStatsWithIPE_BPSAllStats_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW_IN
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor OfflineBPSStatsWithIPE_BPSAllStatsNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor OfflineBPSStatsWithIPE_BPSAllStatsNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor OfflineBPSStatsWithIPE_BPSAllStatsNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor OfflineBPSStatsWithIPE_BPSAllStatsNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
    {5, 1, 1, 0, 0, NULL}, // BPSOutputPortStatsBG
    {6, 1, 1, 0, 0, NULL}, // BPSOutputPortStatsBHist
};

static ChiNode OfflineBPSStatsWithIPE_BPSAllStatsNodes[] =
{
    {NULL, 65538, 0, {1, OfflineBPSStatsWithIPE_BPSAllStatsNode65538_0InputPortDescriptors, 1, OfflineBPSStatsWithIPE_BPSAllStatsNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, OfflineBPSStatsWithIPE_BPSAllStatsNode65539_0InputPortDescriptors, 3, OfflineBPSStatsWithIPE_BPSAllStatsNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink OfflineBPSStatsWithIPE_BPSAllStatsLinks[] =
{
    {{65539, 0, 1, 0}, 1, OfflineBPSStatsWithIPE_BPSAllStats_Link0_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, OfflineBPSStatsWithIPE_BPSAllStats_Link1_IPE0_Out8Desc, {0}, {0, 0}},
    {{65539, 0, 5, 0}, 1, OfflineBPSStatsWithIPE_BPSAllStats_Link2_BPS0_Out5Desc, {0}, {0, 0}},
    {{65539, 0, 6, 0}, 1, OfflineBPSStatsWithIPE_BPSAllStats_Link3_BPS0_Out6Desc, {0}, {0, 0}},
};

enum OfflineBPSStatsWithIPEPipelineIds
{
    BPSAllStats = 0,
};

static ChiPipelineTargetCreateDescriptor OfflineBPSStatsWithIPE_pipelines[] =
{
    {"BPSAllStats", { 0, 2, OfflineBPSStatsWithIPE_BPSAllStatsNodes, 4, OfflineBPSStatsWithIPE_BPSAllStatsLinks, 0}, {3, OfflineBPSStatsWithIPE_BPSAllStats_sink_TargetDescriptors}, {1, OfflineBPSStatsWithIPE_BPSAllStats_source_TargetDescriptors}},  // BPSAllStats
};

/*==================== USECASE: TestPreviewCallbackSnapshotWithThumbnail =======================*/

static ChiBufferFormat TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_CALLBACK_formats[] =
{
    ChiFormatUBWCNV12,
    ChiFormatUBWCTP10,
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_RAW_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiBufferFormat TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_SNAPSHOT_formats[] =
{
    ChiFormatJpeg,
};

static ChiBufferFormat TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_YUV_THUMBNAIL_formats[] =
{
    ChiFormatYUV420NV12,
};

static ChiTarget TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW

static ChiTarget TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_CALLBACK_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    3,
    TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_CALLBACK_formats,
    NULL
}; // TARGET_BUFFER_PREVIEW_CALLBACK

static ChiTarget TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_RAW_target =
{
    ChiStreamTypeBidirectional,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 5488, 4112
    },
    2,
    TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_RAW_formats,
    NULL
}; // TARGET_BUFFER_RAW

static ChiTarget TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_SNAPSHOT_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 5488, 4112
    },
    1,
    TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_SNAPSHOT_formats,
    NULL
}; // TARGET_BUFFER_SNAPSHOT

static ChiTarget TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_YUV_THUMBNAIL_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    1,
    TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_YUV_THUMBNAIL_formats,
    NULL
}; // TARGET_BUFFER_YUV_THUMBNAIL

static ChiTarget* TestPreviewCallbackSnapshotWithThumbnail_Targets[] =
{
	&TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_target,
	&TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_CALLBACK_target,
	&TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_RAW_target,
	&TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_SNAPSHOT_target,
	&TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_YUV_THUMBNAIL_target
};

/*****************************Pipeline ZSLSnapshotJpegWithThumbnail***************************/

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link0_BPS0_Out1Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link1_BPS0_Out2Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link2_BPS0_Out3Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link3_BPS0_Out4Desc[] =
{
    {65538, 0, 3, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link4_IPE0_Out8Desc[] =
{
    {65537, 0, 0, 0, {0, NULL}}, // JPEG
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link5_JPEG0_Out1Desc[] =
{
    {6, 0, 0, 0, {0, NULL}}, // JPEGAggregator
};

static ChiLinkNodeDescriptor __134_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors[] =
{
    {6, 0, 2 }, 
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link6_JPEGAggregator0_Out2Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_SNAPSHOT
};

static ChiLinkNodeDescriptor __135_TARGET_BUFFER_YUV_THUMBNAIL_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link7_IPE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_YUV_THUMBNAIL
};

static ChiTargetPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_SNAPSHOT", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_SNAPSHOT_target, 1, __134_TARGET_BUFFER_SNAPSHOT_Link_NodeDescriptors}, // TARGET_BUFFER_SNAPSHOT
    {"TARGET_BUFFER_YUV_THUMBNAIL", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_YUV_THUMBNAIL_target, 1, __135_TARGET_BUFFER_YUV_THUMBNAIL_Link_NodeDescriptors}, // TARGET_BUFFER_YUV_THUMBNAIL
};

static ChiTargetPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_RAW_target, 1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW
};

// JPEGAggregator0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode6_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGAggregatorInputPort0
};

// JPEGAggregator0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode6_0OutputPortDescriptors[] =
{
    {2, 1, 1, 0, 0, NULL}, // JPEGAggregatorOutputPort0
};

// JPEG0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode65537_0InputPortDescriptors[] =
{
    {0, 0, 0}, // JPEGInputPort0
};

// JPEG0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode65537_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // JPEGOutputPort0
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
    {3, 0, 0}, // IPEInputPortDS64
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode65538_0OutputPortDescriptors[] =
{
    {8, 0, 0, 0, 0, NULL}, // IPEOutputPortDisplay
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
    {2, 0, 0, 0, 0, NULL}, // BPSOutputPortDS4
    {3, 0, 0, 0, 0, NULL}, // BPSOutputPortDS16
    {4, 0, 0, 0, 0, NULL}, // BPSOutputPortDS64
};

static ChiNode TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNodes[] =
{
    {NULL, 6, 0, {1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode6_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode6_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65537, 0, {1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode65537_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode65537_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {4, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode65538_0InputPortDescriptors, 2, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65539, 0, {1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode65539_0InputPortDescriptors, 4, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailLinks[] =
{
    {{65539, 0, 1, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link0_BPS0_Out1Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 2, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link1_BPS0_Out2Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 3, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link2_BPS0_Out3Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65539, 0, 4, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link3_BPS0_Out4Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link4_IPE0_Out8Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65537, 0, 1, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link5_JPEG0_Out1Desc, {ChiFormatYUV420NV12, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable|BufferMemFlagCache}, {0, 0}},
    {{6, 0, 2, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link6_JPEGAggregator0_Out2Desc, {0}, {0, 0}},
    {{65538, 0, 9, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_Link7_IPE0_Out9Desc, {0}, {0, 0}},
};

/*****************************Pipeline RealtimePrevwithCallbackAndRaw***************************/

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link0_StatsParse0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link1_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link2_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link3_IFE0_Out1Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link4_IFE0_Out2Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link5_StatsProcessing0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link6_AutoWhiteBalance0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link7_IFE0_Out17Desc[] =
{
    {9, 0, 0, 0, {0, NULL}}, // StatsParse
    {1, 0, 0, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link8_IFE0_Out19Desc[] =
{
    {9, 0, 9, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link9_IFE0_Out21Desc[] =
{
    {9, 0, 1, 0, {0, NULL}}, // StatsParse
    {12, 0, 1, 0, {0, NULL}}, // AutoWhiteBalance
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link10_IFE0_Out18Desc[] =
{
    {9, 0, 2, 0, {0, NULL}}, // StatsParse
    {1, 0, 2, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link11_IFE0_Out16Desc[] =
{
    {9, 0, 3, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link12_IFE0_Out12Desc[] =
{
    {9, 0, 7, 0, {0, NULL}}, // StatsParse
    {1, 0, 7, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link13_IFE0_Out20Desc[] =
{
    {5, 0, 4, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link14_IFE0_Out8Desc[] =
{
    {5, 0, 8, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link15_IFE0_Out7Desc[] =
{
    {5, 0, 10, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link16_AutoFocus0_Out0Desc[] =
{
    {3, 3, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor __136_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link17_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiLinkNodeDescriptor __137_TARGET_BUFFER_PREVIEW_CALLBACK_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link18_IPE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW_CALLBACK
};

static ChiLinkNodeDescriptor __138_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link19_IFE0_Out9Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiTargetPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_target, 1, __136_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
    {"TARGET_BUFFER_PREVIEW_CALLBACK", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_CALLBACK_target, 1, __137_TARGET_BUFFER_PREVIEW_CALLBACK_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW_CALLBACK
    {"TARGET_BUFFER_RAW", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_RAW_target, 1, __138_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// StatsProcessing0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode1_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsProcessingInputPortHDRBE
    {2, 0, 0}, // StatsProcessingPortHDRBHist
    {7, 0, 0}, // StatsProcessingInputPortRS
};

// StatsProcessing0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode1_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsProcessingOutputPort0
};

// AutoWhiteBalance0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode12_0InputPortDescriptors[] =
{
    {1, 0, 0}, // StatsInputPortAWBBG
};

// AutoWhiteBalance0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode12_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AWBOutputPort0
};

// AutoFocus0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode5_0InputPortDescriptors[] =
{
    {4, 0, 0}, // StatsInputPortBF
    {8, 0, 0}, // StatsInputPortRDIPDAF
    {10, 0, 0}, // StatsInputPortPDAFType3
};

// AutoFocus0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode5_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AutoFocusOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 0, 0, 0, 0, NULL}, // IFEOutputPortDS16
    {17, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBE
    {19, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {21, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
    {18, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBHIST
    {16, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBHIST
    {12, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsRS
    {20, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBF
    {8, 0, 0, 2, 0, NULL}, // IFEOutputPortRDI0
    {7, 0, 0, 0, 0, NULL}, // IFEOutputPortPDAF
    {9, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI1
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
};

// StatsParse0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode9_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsParseInputPortHDRBE
    {9, 0, 0}, // StatsParseInputPortTintlessBG
    {1, 0, 0}, // StatsParseInputPortAWBBG
    {2, 0, 0}, // StatsParseInputPortHDRBHist
    {3, 0, 0}, // StatsParseInputPortBHist
    {7, 0, 0}, // StatsParseInputPortRS
};

// StatsParse0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode9_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsParseOutputPort0
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_node1_0_properties[] =
{
    {1, "com.qti.stats.aec"},
    {1, "com.qti.stats.afd"},
    {6, "1"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_node12_0_properties[] =
{
    {1, "com.qti.stats.awb"},
    {6, "1"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_node5_0_properties[] =
{
    {1, "com.qti.stats.af"},
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_node9_0_properties[] =
{
    {6, "1"},
};

static ChiNode TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNodes[] =
{
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_node0_0_properties, 0, 0, {0, NULL, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_node1_0_properties, 1, 0, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode1_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode1_0OutputPortDescriptors}, 3, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_node12_0_properties, 12, 0, {1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode12_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode12_0OutputPortDescriptors}, 2, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_node5_0_properties, 5, 0, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode5_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode5_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65536, 0, {1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode65536_0InputPortDescriptors, 13, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode65538_0InputPortDescriptors, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_node9_0_properties, 9, 0, {6, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode9_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNode9_0OutputPortDescriptors}, 1, {0, NULL}},
};

static ChiNodeLink TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawLinks[] =
{
    {{9, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link0_StatsParse0_Out0Desc, {0}, {0, 0}},
    {{0, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link1_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link2_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link3_IFE0_Out1Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 2, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link4_IFE0_Out2Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{1, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link5_StatsProcessing0_Out0Desc, {0}, {0, 0}},
    {{12, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link6_AutoWhiteBalance0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 17, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link7_IFE0_Out17Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link8_IFE0_Out19Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 21, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link9_IFE0_Out21Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 18, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link10_IFE0_Out18Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 16, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link11_IFE0_Out16Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 12, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link12_IFE0_Out12Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link13_IFE0_Out20Desc, {ChiFormatBlob, 16384, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 8, 2}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link14_IFE0_Out8Desc, {ChiFormatBlob, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 7, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link15_IFE0_Out7Desc, {ChiFormatRawPlain16, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{5, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link16_AutoFocus0_Out0Desc, {0}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link17_IPE0_Out8Desc, {0}, {0, 0}},
    {{65538, 0, 9, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link18_IPE0_Out9Desc, {0}, {0, 0}},
    {{65536, 0, 9, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_Link19_IFE0_Out9Desc, {0}, {0, 0}},
};

/*****************************Pipeline RealtimePrevWithAECWrapper***************************/

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link0_StatsParse0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link1_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link2_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link3_IFE0_Out1Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link4_IFE0_Out2Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link5_StatsProcessing0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link6_StatsProcessing0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link7_AutoWhiteBalance0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link8_IFE0_Out17Desc[] =
{
    {9, 0, 0, 0, {0, NULL}}, // StatsParse
    {1, 0, 0, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link9_IFE0_Out19Desc[] =
{
    {9, 0, 9, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link10_IFE0_Out21Desc[] =
{
    {9, 0, 1, 0, {0, NULL}}, // StatsParse
    {12, 0, 1, 0, {0, NULL}}, // AutoWhiteBalance
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link11_IFE0_Out18Desc[] =
{
    {9, 0, 2, 0, {0, NULL}}, // StatsParse
    {1, 0, 2, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link12_IFE0_Out16Desc[] =
{
    {9, 0, 3, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link13_IFE0_Out12Desc[] =
{
    {9, 0, 7, 0, {0, NULL}}, // StatsParse
    {1, 0, 7, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link14_IFE0_Out20Desc[] =
{
    {5, 0, 4, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link15_IFE0_Out8Desc[] =
{
    {5, 0, 8, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link16_IFE0_Out7Desc[] =
{
    {5, 0, 10, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link17_AutoFocus0_Out0Desc[] =
{
    {3, 3, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor __139_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link18_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiLinkNodeDescriptor __140_TARGET_BUFFER_PREVIEW_CALLBACK_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link19_IPE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW_CALLBACK
};

static ChiTargetPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_target, 1, __139_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
    {"TARGET_BUFFER_PREVIEW_CALLBACK", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_CALLBACK_target, 1, __140_TARGET_BUFFER_PREVIEW_CALLBACK_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW_CALLBACK
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// StatsProcessing0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode1_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsProcessingInputPortHDRBE
    {2, 0, 0}, // StatsProcessingPortHDRBHist
    {7, 0, 0}, // StatsProcessingInputPortRS
};

// StatsProcessing0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode1_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsProcessingOutputPort0
    {0, 1, 0, 0, 0, NULL}, // StatsProcessingOutputPort0
};

// AutoWhiteBalance0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode12_0InputPortDescriptors[] =
{
    {1, 0, 0}, // StatsInputPortAWBBG
};

// AutoWhiteBalance0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode12_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AWBOutputPort0
};

// AutoFocus0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode5_0InputPortDescriptors[] =
{
    {4, 0, 0}, // StatsInputPortBF
    {8, 0, 0}, // StatsInputPortRDIPDAF
    {10, 0, 0}, // StatsInputPortPDAFType3
};

// AutoFocus0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode5_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AutoFocusOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 0, 0, 0, 0, NULL}, // IFEOutputPortDS16
    {17, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBE
    {19, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {21, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
    {18, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBHIST
    {16, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBHIST
    {12, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsRS
    {20, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBF
    {8, 0, 0, 2, 0, NULL}, // IFEOutputPortRDI0
    {7, 0, 0, 0, 0, NULL}, // IFEOutputPortPDAF
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
};

// StatsParse0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode9_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsParseInputPortHDRBE
    {9, 0, 0}, // StatsParseInputPortTintlessBG
    {1, 0, 0}, // StatsParseInputPortAWBBG
    {2, 0, 0}, // StatsParseInputPortHDRBHist
    {3, 0, 0}, // StatsParseInputPortBHist
    {7, 0, 0}, // StatsParseInputPortRS
};

// StatsParse0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode9_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsParseOutputPort0
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_node1_0_properties[] =
{
    {1, "com.qti.stats.aecwrapper"},
    {1, "com.qti.stats.afd"},
    {6, "1"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_node12_0_properties[] =
{
    {1, "com.qti.stats.awbwrapper"},
    {6, "1"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_node5_0_properties[] =
{
    {1, "com.qti.stats.afwrapper"},
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_node9_0_properties[] =
{
    {6, "1"},
};

static ChiNode TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNodes[] =
{
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_node0_0_properties, 0, 0, {0, NULL, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_node1_0_properties, 1, 0, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode1_0InputPortDescriptors, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode1_0OutputPortDescriptors}, 3, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_node12_0_properties, 12, 0, {1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode12_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode12_0OutputPortDescriptors}, 2, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_node5_0_properties, 5, 0, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode5_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode5_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65536, 0, {1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode65536_0InputPortDescriptors, 12, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode65538_0InputPortDescriptors, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_node9_0_properties, 9, 0, {6, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode9_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNode9_0OutputPortDescriptors}, 1, {0, NULL}},
};

static ChiNodeLink TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperLinks[] =
{
    {{9, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link0_StatsParse0_Out0Desc, {0}, {0, 0}},
    {{0, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link1_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link2_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link3_IFE0_Out1Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 2, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link4_IFE0_Out2Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{1, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link5_StatsProcessing0_Out0Desc, {0}, {0, 0}},
    {{1, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link6_StatsProcessing0_Out0Desc, {0}, {0, 0}},
    {{12, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link7_AutoWhiteBalance0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 17, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link8_IFE0_Out17Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link9_IFE0_Out19Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 21, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link10_IFE0_Out21Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 18, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link11_IFE0_Out18Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 16, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link12_IFE0_Out16Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 12, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link13_IFE0_Out12Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link14_IFE0_Out20Desc, {ChiFormatBlob, 16384, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 8, 2}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link15_IFE0_Out8Desc, {ChiFormatBlob, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 7, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link16_IFE0_Out7Desc, {ChiFormatRawPlain16, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{5, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link17_AutoFocus0_Out0Desc, {0}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link18_IPE0_Out8Desc, {0}, {0, 0}},
    {{65538, 0, 9, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_Link19_IPE0_Out9Desc, {0}, {0, 0}},
};

/*****************************Pipeline RealtimePrevwithCallback***************************/

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link0_StatsParse0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link1_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link2_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link3_IFE0_Out1Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link4_IFE0_Out2Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link5_StatsProcessing0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link6_StatsProcessing0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link7_AutoWhiteBalance0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link8_IFE0_Out17Desc[] =
{
    {9, 0, 0, 0, {0, NULL}}, // StatsParse
    {1, 0, 0, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link9_IFE0_Out19Desc[] =
{
    {9, 0, 9, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link10_IFE0_Out21Desc[] =
{
    {9, 0, 1, 0, {0, NULL}}, // StatsParse
    {12, 0, 1, 0, {0, NULL}}, // AutoWhiteBalance
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link11_IFE0_Out18Desc[] =
{
    {9, 0, 2, 0, {0, NULL}}, // StatsParse
    {1, 0, 2, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link12_IFE0_Out16Desc[] =
{
    {9, 0, 3, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link13_IFE0_Out12Desc[] =
{
    {9, 0, 7, 0, {0, NULL}}, // StatsParse
    {1, 0, 7, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link14_IFE0_Out20Desc[] =
{
    {5, 0, 4, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link15_IFE0_Out8Desc[] =
{
    {5, 0, 8, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link16_IFE0_Out7Desc[] =
{
    {5, 0, 10, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link17_AutoFocus0_Out0Desc[] =
{
    {3, 3, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor __141_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link18_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiLinkNodeDescriptor __142_TARGET_BUFFER_PREVIEW_CALLBACK_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link19_IPE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW_CALLBACK
};

static ChiTargetPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_target, 1, __141_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
    {"TARGET_BUFFER_PREVIEW_CALLBACK", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_CALLBACK_target, 1, __142_TARGET_BUFFER_PREVIEW_CALLBACK_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW_CALLBACK
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// StatsProcessing0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode1_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsProcessingInputPortHDRBE
    {2, 0, 0}, // StatsProcessingPortHDRBHist
    {7, 0, 0}, // StatsProcessingInputPortRS
};

// StatsProcessing0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode1_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsProcessingOutputPort0
    {0, 1, 0, 0, 0, NULL}, // StatsProcessingOutputPort0
};

// AutoWhiteBalance0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode12_0InputPortDescriptors[] =
{
    {1, 0, 0}, // StatsInputPortAWBBG
};

// AutoWhiteBalance0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode12_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AWBOutputPort0
};

// AutoFocus0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode5_0InputPortDescriptors[] =
{
    {4, 0, 0}, // StatsInputPortBF
    {8, 0, 0}, // StatsInputPortRDIPDAF
    {10, 0, 0}, // StatsInputPortPDAFType3
};

// AutoFocus0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode5_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AutoFocusOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 0, 0, 0, 0, NULL}, // IFEOutputPortDS16
    {17, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBE
    {19, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {21, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
    {18, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBHIST
    {16, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBHIST
    {12, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsRS
    {20, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBF
    {8, 0, 0, 2, 0, NULL}, // IFEOutputPortRDI0
    {7, 0, 0, 0, 0, NULL}, // IFEOutputPortPDAF
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
};

// StatsParse0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode9_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsParseInputPortHDRBE
    {9, 0, 0}, // StatsParseInputPortTintlessBG
    {1, 0, 0}, // StatsParseInputPortAWBBG
    {2, 0, 0}, // StatsParseInputPortHDRBHist
    {3, 0, 0}, // StatsParseInputPortBHist
    {7, 0, 0}, // StatsParseInputPortRS
};

// StatsParse0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode9_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsParseOutputPort0
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_node1_0_properties[] =
{
    {1, "com.qti.stats.aec"},
    {1, "com.qti.stats.afd"},
    {6, "1"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_node12_0_properties[] =
{
    {1, "com.qti.stats.awb"},
    {6, "1"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_node5_0_properties[] =
{
    {1, "com.qti.stats.af"},
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_node9_0_properties[] =
{
    {6, "1"},
};

static ChiNode TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNodes[] =
{
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_node0_0_properties, 0, 0, {0, NULL, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_node1_0_properties, 1, 0, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode1_0InputPortDescriptors, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode1_0OutputPortDescriptors}, 3, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_node12_0_properties, 12, 0, {1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode12_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode12_0OutputPortDescriptors}, 2, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_node5_0_properties, 5, 0, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode5_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode5_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65536, 0, {1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode65536_0InputPortDescriptors, 12, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode65538_0InputPortDescriptors, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_node9_0_properties, 9, 0, {6, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode9_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNode9_0OutputPortDescriptors}, 1, {0, NULL}},
};

static ChiNodeLink TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackLinks[] =
{
    {{9, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link0_StatsParse0_Out0Desc, {0}, {0, 0}},
    {{0, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link1_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link2_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link3_IFE0_Out1Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 2, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link4_IFE0_Out2Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{1, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link5_StatsProcessing0_Out0Desc, {0}, {0, 0}},
    {{1, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link6_StatsProcessing0_Out0Desc, {0}, {0, 0}},
    {{12, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link7_AutoWhiteBalance0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 17, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link8_IFE0_Out17Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link9_IFE0_Out19Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 21, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link10_IFE0_Out21Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 18, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link11_IFE0_Out18Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 16, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link12_IFE0_Out16Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 12, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link13_IFE0_Out12Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link14_IFE0_Out20Desc, {ChiFormatBlob, 16384, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 8, 2}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link15_IFE0_Out8Desc, {ChiFormatBlob, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 7, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link16_IFE0_Out7Desc, {ChiFormatRawPlain16, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{5, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link17_AutoFocus0_Out0Desc, {0}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link18_IPE0_Out8Desc, {0}, {0, 0}},
    {{65538, 0, 9, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_Link19_IPE0_Out9Desc, {0}, {0, 0}},
};

/*****************************Pipeline RealtimePrevAndVideoWithStats***************************/

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link0_StatsParse0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link1_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link2_IFE0_Out0Desc[] =
{
    {65538, 0, 0, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link3_IFE0_Out1Desc[] =
{
    {65538, 0, 1, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link4_IFE0_Out2Desc[] =
{
    {65538, 0, 2, 0, {0, NULL}}, // IPE
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link5_StatsProcessing0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link6_StatsProcessing0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link7_AutoWhiteBalance0_Out0Desc[] =
{
    {3, 0, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link8_IFE0_Out17Desc[] =
{
    {9, 0, 0, 0, {0, NULL}}, // StatsParse
    {1, 0, 0, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link9_IFE0_Out19Desc[] =
{
    {9, 0, 9, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link10_IFE0_Out21Desc[] =
{
    {9, 0, 1, 0, {0, NULL}}, // StatsParse
    {12, 0, 1, 0, {0, NULL}}, // AutoWhiteBalance
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link11_IFE0_Out18Desc[] =
{
    {9, 0, 2, 0, {0, NULL}}, // StatsParse
    {1, 0, 2, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link12_IFE0_Out16Desc[] =
{
    {9, 0, 3, 0, {0, NULL}}, // StatsParse
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link13_IFE0_Out12Desc[] =
{
    {9, 0, 7, 0, {0, NULL}}, // StatsParse
    {1, 0, 7, 0, {0, NULL}}, // StatsProcessing
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link14_IFE0_Out20Desc[] =
{
    {5, 0, 4, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link15_IFE0_Out8Desc[] =
{
    {5, 0, 8, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link16_IFE0_Out7Desc[] =
{
    {5, 0, 10, 0, {0, NULL}}, // AutoFocus
};

static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link17_AutoFocus0_Out0Desc[] =
{
    {3, 3, 0, 0, {0, NULL}}, // SinkNoBuffer
};

static ChiLinkNodeDescriptor __143_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors[] =
{
    {65538, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link18_IPE0_Out8Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW
};

static ChiLinkNodeDescriptor __144_TARGET_BUFFER_PREVIEW_CALLBACK_Link_NodeDescriptors[] =
{
    {65538, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link19_IPE0_Out9Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_PREVIEW_CALLBACK
};

static ChiLinkNodeDescriptor __145_TARGET_BUFFER_RAW_Link_NodeDescriptors[] =
{
    {65536, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link20_IFE0_Out9Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RAW
};

static ChiTargetPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_PREVIEW", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_target, 1, __143_TARGET_BUFFER_PREVIEW_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW
    {"TARGET_BUFFER_PREVIEW_CALLBACK", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_PREVIEW_CALLBACK_target, 1, __144_TARGET_BUFFER_PREVIEW_CALLBACK_Link_NodeDescriptors}, // TARGET_BUFFER_PREVIEW_CALLBACK
    {"TARGET_BUFFER_RAW", &TestPreviewCallbackSnapshotWithThumbnail_TARGET_BUFFER_RAW_target, 1, __145_TARGET_BUFFER_RAW_Link_NodeDescriptors}, // TARGET_BUFFER_RAW
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// StatsProcessing0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode1_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsProcessingInputPortHDRBE
    {2, 0, 0}, // StatsProcessingPortHDRBHist
    {7, 0, 0}, // StatsProcessingInputPortRS
};

// StatsProcessing0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode1_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsProcessingOutputPort0
    {0, 1, 0, 0, 0, NULL}, // StatsProcessingOutputPort0
};

// AutoWhiteBalance0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode12_0InputPortDescriptors[] =
{
    {1, 0, 0}, // StatsInputPortAWBBG
};

// AutoWhiteBalance0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode12_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AWBOutputPort0
};

// AutoFocus0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode5_0InputPortDescriptors[] =
{
    {4, 0, 0}, // StatsInputPortBF
    {8, 0, 0}, // StatsInputPortRDIPDAF
    {10, 0, 0}, // StatsInputPortPDAFType3
};

// AutoFocus0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode5_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // AutoFocusOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode65536_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // IFEOutputPortFull
    {1, 0, 0, 0, 0, NULL}, // IFEOutputPortDS4
    {2, 0, 0, 0, 0, NULL}, // IFEOutputPortDS16
    {17, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBE
    {19, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {21, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
    {18, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsHDRBHIST
    {16, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBHIST
    {12, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsRS
    {20, 0, 0, 0, 0, NULL}, // IFEOutputPortStatsBF
    {8, 0, 0, 2, 0, NULL}, // IFEOutputPortRDI0
    {7, 0, 0, 0, 0, NULL}, // IFEOutputPortPDAF
    {9, 1, 1, 0, 0, NULL}, // IFEOutputPortRDI1
};

// IPE0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode65538_0InputPortDescriptors[] =
{
    {0, 0, 0}, // IPEInputPortFull
    {1, 0, 0}, // IPEInputPortDS4
    {2, 0, 0}, // IPEInputPortDS16
};

// IPE0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode65538_0OutputPortDescriptors[] =
{
    {8, 1, 1, 0, 0, NULL}, // IPEOutputPortDisplay
    {9, 1, 1, 0, 0, NULL}, // IPEOutputPortVideo
};

// StatsParse0 Input Port Descriptors
static ChiInputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode9_0InputPortDescriptors[] =
{
    {0, 0, 0}, // StatsParseInputPortHDRBE
    {9, 0, 0}, // StatsParseInputPortTintlessBG
    {1, 0, 0}, // StatsParseInputPortAWBBG
    {2, 0, 0}, // StatsParseInputPortHDRBHist
    {3, 0, 0}, // StatsParseInputPortBHist
    {7, 0, 0}, // StatsParseInputPortRS
};

// StatsParse0 Output Port Descriptors
static ChiOutputPortDescriptor TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode9_0OutputPortDescriptors[] =
{
    {0, 1, 0, 0, 0, NULL}, // StatsParseOutputPort0
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_node0_0_properties[] =
{
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_node1_0_properties[] =
{
    {1, "com.qti.stats.aec"},
    {1, "com.qti.stats.afd"},
    {6, "1"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_node12_0_properties[] =
{
    {1, "com.qti.stats.awb"},
    {6, "1"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_node5_0_properties[] =
{
    {1, "com.qti.stats.af"},
    {1, "com.qti.stats.pdlib"},
};

static ChiNodeProperty TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_node9_0_properties[] =
{
    {6, "1"},
};

static ChiNode TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNodes[] =
{
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_node0_0_properties, 0, 0, {0, NULL, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode0_0OutputPortDescriptors}, 1, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_node1_0_properties, 1, 0, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode1_0InputPortDescriptors, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode1_0OutputPortDescriptors}, 3, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_node12_0_properties, 12, 0, {1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode12_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode12_0OutputPortDescriptors}, 2, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_node5_0_properties, 5, 0, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode5_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode5_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65536, 0, {1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode65536_0InputPortDescriptors, 13, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65538, 0, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode65538_0InputPortDescriptors, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode65538_0OutputPortDescriptors}, 0, {0, NULL}},
    {TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_node9_0_properties, 9, 0, {6, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode9_0InputPortDescriptors, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNode9_0OutputPortDescriptors}, 1, {0, NULL}},
};

static ChiNodeLink TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsLinks[] =
{
    {{9, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link0_StatsParse0_Out0Desc, {0}, {0, 0}},
    {{0, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link1_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link2_IFE0_Out0Desc, {ChiFormatUBWCTP10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 1, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link3_IFE0_Out1Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 2, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link4_IFE0_Out2Desc, {ChiFormatPD10, 0, 8, 8, BufferHeapIon, BufferMemFlagHw}, {0, 0}},
    {{1, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link5_StatsProcessing0_Out0Desc, {0}, {0, 0}},
    {{1, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link6_StatsProcessing0_Out0Desc, {0}, {0, 0}},
    {{12, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link7_AutoWhiteBalance0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 17, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link8_IFE0_Out17Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link9_IFE0_Out19Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 21, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link10_IFE0_Out21Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 18, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link11_IFE0_Out18Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 16, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link12_IFE0_Out16Desc, {ChiFormatBlob, 3072, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 12, 0}, 2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link13_IFE0_Out12Desc, {ChiFormatBlob, 16384, 6, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link14_IFE0_Out20Desc, {ChiFormatBlob, 16384, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 8, 2}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link15_IFE0_Out8Desc, {ChiFormatBlob, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw}, {0, 0}},
    {{65536, 0, 7, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link16_IFE0_Out7Desc, {ChiFormatRawPlain16, 307200, 10, 10, BufferHeapIon, BufferMemFlagLockable|BufferMemFlagHw|BufferMemFlagCache}, {0, 0}},
    {{5, 0, 0, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link17_AutoFocus0_Out0Desc, {0}, {0, 0}},
    {{65538, 0, 8, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link18_IPE0_Out8Desc, {0}, {0, 0}},
    {{65538, 0, 9, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link19_IPE0_Out9Desc, {0}, {0, 0}},
    {{65536, 0, 9, 0}, 1, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_Link20_IFE0_Out9Desc, {0}, {0, 0}},
};

enum TestPreviewCallbackSnapshotWithThumbnailPipelineIds
{
    ZSLSnapshotJpegWithThumbnail = 0,
    RealtimePrevwithCallbackAndRaw = 1,
    RealtimePrevWithAECWrapper = 2,
    RealtimePrevwithCallback = 3,
    RealtimePrevAndVideoWithStats = 4,
};

static ChiPipelineTargetCreateDescriptor TestPreviewCallbackSnapshotWithThumbnail_pipelines[] =
{
    {"ZSLSnapshotJpegWithThumbnail", { 0, 4, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailNodes, 8, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnailLinks, 0}, {2, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_sink_TargetDescriptors}, {1, TestPreviewCallbackSnapshotWithThumbnail_ZSLSnapshotJpegWithThumbnail_source_TargetDescriptors}},  // ZSLSnapshotJpegWithThumbnail
    {"RealtimePrevwithCallbackAndRaw", { 0, 7, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawNodes, 20, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRawLinks, 1}, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackAndRaw_sink_TargetDescriptors}, {0, NULL}},  // RealtimePrevwithCallbackAndRaw
    {"RealtimePrevWithAECWrapper", { 0, 7, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperNodes, 20, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapperLinks, 1}, {2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevWithAECWrapper_sink_TargetDescriptors}, {0, NULL}},  // RealtimePrevWithAECWrapper
    {"RealtimePrevwithCallback", { 0, 7, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackNodes, 20, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallbackLinks, 1}, {2, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevwithCallback_sink_TargetDescriptors}, {0, NULL}},  // RealtimePrevwithCallback
    {"RealtimePrevAndVideoWithStats", { 0, 7, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsNodes, 21, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStatsLinks, 1}, {3, TestPreviewCallbackSnapshotWithThumbnail_RealtimePrevAndVideoWithStats_sink_TargetDescriptors}, {0, NULL}},  // RealtimePrevAndVideoWithStats
};

/*==================== USECASE: TestGPUDSPorts =======================*/

static ChiBufferFormat TestGPUDSPorts_TARGET_BUFFER_RAW_IN_formats[] =
{
    ChiFormatRawMIPI,
    ChiFormatRawPlain16,
};

static ChiBufferFormat TestGPUDSPorts_TARGET_BUFFER_FULL_formats[] =
{
    ChiFormatP010,
};

static ChiBufferFormat TestGPUDSPorts_TARGET_BUFFER_DS4_formats[] =
{
    ChiFormatP010,
};

static ChiBufferFormat TestGPUDSPorts_TARGET_BUFFER_DS16_formats[] =
{
    ChiFormatP010,
};

static ChiBufferFormat TestGPUDSPorts_TARGET_BUFFER_DS64_formats[] =
{
    ChiFormatP010,
};

static ChiTarget TestGPUDSPorts_TARGET_BUFFER_RAW_IN_target =
{
    ChiStreamTypeInput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4608, 2592
    },
    2,
    TestGPUDSPorts_TARGET_BUFFER_RAW_IN_formats,
    NULL
}; // TARGET_BUFFER_RAW_IN

static ChiTarget TestGPUDSPorts_TARGET_BUFFER_FULL_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    1,
    TestGPUDSPorts_TARGET_BUFFER_FULL_formats,
    NULL
}; // TARGET_BUFFER_FULL

static ChiTarget TestGPUDSPorts_TARGET_BUFFER_DS4_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    1,
    TestGPUDSPorts_TARGET_BUFFER_DS4_formats,
    NULL
}; // TARGET_BUFFER_DS4

static ChiTarget TestGPUDSPorts_TARGET_BUFFER_DS16_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    1,
    TestGPUDSPorts_TARGET_BUFFER_DS16_formats,
    NULL
}; // TARGET_BUFFER_DS16

static ChiTarget TestGPUDSPorts_TARGET_BUFFER_DS64_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2448
    },
    1,
    TestGPUDSPorts_TARGET_BUFFER_DS64_formats,
    NULL
}; // TARGET_BUFFER_DS64

static ChiTarget* TestGPUDSPorts_Targets[] =
{
	&TestGPUDSPorts_TARGET_BUFFER_RAW_IN_target,
	&TestGPUDSPorts_TARGET_BUFFER_FULL_target,
	&TestGPUDSPorts_TARGET_BUFFER_DS4_target,
	&TestGPUDSPorts_TARGET_BUFFER_DS16_target,
	&TestGPUDSPorts_TARGET_BUFFER_DS64_target
};

/*****************************Pipeline OfflineBPSGPU***************************/

static ChiLinkNodeDescriptor TestGPUDSPorts_OfflineBPSGPU_source_Link_0NodeDescriptors[] =
{
    {65539, 0, 0},
};
static ChiLinkNodeDescriptor TestGPUDSPorts_OfflineBPSGPU_Link0_BPS0_Out1Desc[] =
{
    {255, 0, 0, 0, {0, NULL}}, // ChiGPUNode
};

static ChiLinkNodeDescriptor __146_TARGET_BUFFER_FULL_Link_NodeDescriptors[] =
{
    {255, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestGPUDSPorts_OfflineBPSGPU_Link1_ChiGPUNode0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_FULL
};

static ChiLinkNodeDescriptor __147_TARGET_BUFFER_DS4_Link_NodeDescriptors[] =
{
    {255, 0, 1 }, 
};
static ChiLinkNodeDescriptor TestGPUDSPorts_OfflineBPSGPU_Link2_ChiGPUNode0_Out1Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_DS4
};

static ChiLinkNodeDescriptor __148_TARGET_BUFFER_DS16_Link_NodeDescriptors[] =
{
    {255, 0, 2 }, 
};
static ChiLinkNodeDescriptor TestGPUDSPorts_OfflineBPSGPU_Link3_ChiGPUNode0_Out2Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_DS16
};

static ChiLinkNodeDescriptor __149_TARGET_BUFFER_DS64_Link_NodeDescriptors[] =
{
    {255, 0, 3 }, 
};
static ChiLinkNodeDescriptor TestGPUDSPorts_OfflineBPSGPU_Link4_ChiGPUNode0_Out3Desc[] =
{
    {2, 3, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_DS64
};

static ChiTargetPortDescriptor TestGPUDSPorts_OfflineBPSGPU_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_FULL", &TestGPUDSPorts_TARGET_BUFFER_FULL_target, 1, __146_TARGET_BUFFER_FULL_Link_NodeDescriptors}, // TARGET_BUFFER_FULL
    {"TARGET_BUFFER_DS4", &TestGPUDSPorts_TARGET_BUFFER_DS4_target, 1, __147_TARGET_BUFFER_DS4_Link_NodeDescriptors}, // TARGET_BUFFER_DS4
    {"TARGET_BUFFER_DS16", &TestGPUDSPorts_TARGET_BUFFER_DS16_target, 1, __148_TARGET_BUFFER_DS16_Link_NodeDescriptors}, // TARGET_BUFFER_DS16
    {"TARGET_BUFFER_DS64", &TestGPUDSPorts_TARGET_BUFFER_DS64_target, 1, __149_TARGET_BUFFER_DS64_Link_NodeDescriptors}, // TARGET_BUFFER_DS64
};

static ChiTargetPortDescriptor TestGPUDSPorts_OfflineBPSGPU_source_TargetDescriptors[] =
{
    {"TARGET_BUFFER_RAW_IN", &TestGPUDSPorts_TARGET_BUFFER_RAW_IN_target, 1, TestGPUDSPorts_OfflineBPSGPU_source_Link_0NodeDescriptors}, // TARGET_BUFFER_RAW_IN
};

// ChiGPUNode0 Input Port Descriptors
static ChiInputPortDescriptor TestGPUDSPorts_OfflineBPSGPUNode255_0InputPortDescriptors[] =
{
    {0, 0, 0}, // ChiNodeInputPortFull
};

// ChiGPUNode0 Output Port Descriptors
static ChiOutputPortDescriptor TestGPUDSPorts_OfflineBPSGPUNode255_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // ChiNodeOutputPortFull
    {1, 1, 1, 0, 0, NULL}, // ChiNodeOutputPortDS4
    {2, 1, 1, 0, 0, NULL}, // ChiNodeOutputPortDS16
    {3, 1, 1, 0, 0, NULL}, // ChiNodeOutputPortDS64
};

// BPS0 Input Port Descriptors
static ChiInputPortDescriptor TestGPUDSPorts_OfflineBPSGPUNode65539_0InputPortDescriptors[] =
{
    {0, 1, 0}, // BPSInputPort
};

// BPS0 Output Port Descriptors
static ChiOutputPortDescriptor TestGPUDSPorts_OfflineBPSGPUNode65539_0OutputPortDescriptors[] =
{
    {1, 0, 0, 0, 0, NULL}, // BPSOutputPortFull
};

static ChiNodeProperty TestGPUDSPorts_OfflineBPSGPU_node255_0_properties[] =
{
    {1, "com.qti.node.gpu"},
    {2048, "8"},
};

static ChiNode TestGPUDSPorts_OfflineBPSGPUNodes[] =
{
    {TestGPUDSPorts_OfflineBPSGPU_node255_0_properties, 255, 0, {1, TestGPUDSPorts_OfflineBPSGPUNode255_0InputPortDescriptors, 4, TestGPUDSPorts_OfflineBPSGPUNode255_0OutputPortDescriptors}, 2, {0, NULL}},
    {NULL, 65539, 0, {1, TestGPUDSPorts_OfflineBPSGPUNode65539_0InputPortDescriptors, 1, TestGPUDSPorts_OfflineBPSGPUNode65539_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestGPUDSPorts_OfflineBPSGPULinks[] =
{
    {{65539, 0, 1, 0}, 1, TestGPUDSPorts_OfflineBPSGPU_Link0_BPS0_Out1Desc, {ChiFormatP010, 0, 8, 8, BufferHeapIon, BufferMemFlagHw|BufferMemFlagLockable}, {0, 0}},
    {{255, 0, 0, 0}, 1, TestGPUDSPorts_OfflineBPSGPU_Link1_ChiGPUNode0_Out0Desc, {0}, {0, 0}},
    {{255, 0, 1, 0}, 1, TestGPUDSPorts_OfflineBPSGPU_Link2_ChiGPUNode0_Out1Desc, {0}, {0, 0}},
    {{255, 0, 2, 0}, 1, TestGPUDSPorts_OfflineBPSGPU_Link3_ChiGPUNode0_Out2Desc, {0}, {0, 0}},
    {{255, 0, 3, 0}, 1, TestGPUDSPorts_OfflineBPSGPU_Link4_ChiGPUNode0_Out3Desc, {0}, {0, 0}},
};

enum TestGPUDSPortsPipelineIds
{
    OfflineBPSGPU = 0,
};

static ChiPipelineTargetCreateDescriptor TestGPUDSPorts_pipelines[] =
{
    {"OfflineBPSGPU", { 0, 2, TestGPUDSPorts_OfflineBPSGPUNodes, 5, TestGPUDSPorts_OfflineBPSGPULinks, 0}, {4, TestGPUDSPorts_OfflineBPSGPU_sink_TargetDescriptors}, {1, TestGPUDSPorts_OfflineBPSGPU_source_TargetDescriptors}},  // OfflineBPSGPU
};

/*==================== USECASE: TestTFEFullStatsTestgen =======================*/

static ChiBufferFormat TestTFEFullStatsTestgen_TARGET_BUFFER_FULL_formats[] =
{
    ChiFormatRawMIPI,
};

static ChiBufferFormat TestTFEFullStatsTestgen_TARGET_BUFFER_AECBG_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestTFEFullStatsTestgen_TARGET_BUFFER_BHIST_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestTFEFullStatsTestgen_TARGET_BUFFER_TLBG_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestTFEFullStatsTestgen_TARGET_BUFFER_BAF_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestTFEFullStatsTestgen_TARGET_BUFFER_AWBBG_formats[] =
{
    ChiFormatBlob,
};

static ChiTarget TestTFEFullStatsTestgen_TARGET_BUFFER_FULL_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2160
    },
    1,
    TestTFEFullStatsTestgen_TARGET_BUFFER_FULL_formats,
    NULL
}; // TARGET_BUFFER_FULL

static ChiTarget TestTFEFullStatsTestgen_TARGET_BUFFER_AECBG_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 16384, 1
    },
    1,
    TestTFEFullStatsTestgen_TARGET_BUFFER_AECBG_formats,
    NULL
}; // TARGET_BUFFER_AECBG

static ChiTarget TestTFEFullStatsTestgen_TARGET_BUFFER_BHIST_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 3072, 1
    },
    1,
    TestTFEFullStatsTestgen_TARGET_BUFFER_BHIST_formats,
    NULL
}; // TARGET_BUFFER_BHIST

static ChiTarget TestTFEFullStatsTestgen_TARGET_BUFFER_TLBG_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 16384, 1
    },
    1,
    TestTFEFullStatsTestgen_TARGET_BUFFER_TLBG_formats,
    NULL
}; // TARGET_BUFFER_TLBG

static ChiTarget TestTFEFullStatsTestgen_TARGET_BUFFER_BAF_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 16384, 1
    },
    1,
    TestTFEFullStatsTestgen_TARGET_BUFFER_BAF_formats,
    NULL
}; // TARGET_BUFFER_BAF

static ChiTarget TestTFEFullStatsTestgen_TARGET_BUFFER_AWBBG_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 16384, 1
    },
    1,
    TestTFEFullStatsTestgen_TARGET_BUFFER_AWBBG_formats,
    NULL
}; // TARGET_BUFFER_AWBBG

static ChiTarget* TestTFEFullStatsTestgen_Targets[] =
{
	&TestTFEFullStatsTestgen_TARGET_BUFFER_FULL_target,
	&TestTFEFullStatsTestgen_TARGET_BUFFER_AECBG_target,
	&TestTFEFullStatsTestgen_TARGET_BUFFER_BHIST_target,
	&TestTFEFullStatsTestgen_TARGET_BUFFER_TLBG_target,
	&TestTFEFullStatsTestgen_TARGET_BUFFER_BAF_target,
	&TestTFEFullStatsTestgen_TARGET_BUFFER_AWBBG_target
};

/*****************************Pipeline TfeFullStatsTestgen***************************/

static ChiLinkNodeDescriptor __150_TARGET_BUFFER_FULL_Link_NodeDescriptors[] =
{
    {65544, 0, 1 }, 
};
static ChiLinkNodeDescriptor TestTFEFullStatsTestgen_TfeFullStatsTestgen_Link0_TFE0_Out1Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_FULL
};

static ChiLinkNodeDescriptor __151_TARGET_BUFFER_AECBG_Link_NodeDescriptors[] =
{
    {65544, 0, 7 }, 
};
static ChiLinkNodeDescriptor TestTFEFullStatsTestgen_TfeFullStatsTestgen_Link1_TFE0_Out7Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_AECBG
};

static ChiLinkNodeDescriptor __152_TARGET_BUFFER_BHIST_Link_NodeDescriptors[] =
{
    {65544, 0, 8 }, 
};
static ChiLinkNodeDescriptor TestTFEFullStatsTestgen_TfeFullStatsTestgen_Link2_TFE0_Out8Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BHIST
};

static ChiLinkNodeDescriptor __153_TARGET_BUFFER_TLBG_Link_NodeDescriptors[] =
{
    {65544, 0, 9 }, 
};
static ChiLinkNodeDescriptor TestTFEFullStatsTestgen_TfeFullStatsTestgen_Link3_TFE0_Out9Desc[] =
{
    {2, 3, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_TLBG
};

static ChiLinkNodeDescriptor __154_TARGET_BUFFER_BAF_Link_NodeDescriptors[] =
{
    {65544, 0, 10 }, 
};
static ChiLinkNodeDescriptor TestTFEFullStatsTestgen_TfeFullStatsTestgen_Link4_TFE0_Out10Desc[] =
{
    {2, 4, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BAF
};

static ChiLinkNodeDescriptor __155_TARGET_BUFFER_AWBBG_Link_NodeDescriptors[] =
{
    {65544, 0, 11 }, 
};
static ChiLinkNodeDescriptor TestTFEFullStatsTestgen_TfeFullStatsTestgen_Link5_TFE0_Out11Desc[] =
{
    {2, 5, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_AWBBG
};

static ChiTargetPortDescriptor TestTFEFullStatsTestgen_TfeFullStatsTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_FULL", &TestTFEFullStatsTestgen_TARGET_BUFFER_FULL_target, 1, __150_TARGET_BUFFER_FULL_Link_NodeDescriptors}, // TARGET_BUFFER_FULL
    {"TARGET_BUFFER_AECBG", &TestTFEFullStatsTestgen_TARGET_BUFFER_AECBG_target, 1, __151_TARGET_BUFFER_AECBG_Link_NodeDescriptors}, // TARGET_BUFFER_AECBG
    {"TARGET_BUFFER_BHIST", &TestTFEFullStatsTestgen_TARGET_BUFFER_BHIST_target, 1, __152_TARGET_BUFFER_BHIST_Link_NodeDescriptors}, // TARGET_BUFFER_BHIST
    {"TARGET_BUFFER_TLBG", &TestTFEFullStatsTestgen_TARGET_BUFFER_TLBG_target, 1, __153_TARGET_BUFFER_TLBG_Link_NodeDescriptors}, // TARGET_BUFFER_TLBG
    {"TARGET_BUFFER_BAF", &TestTFEFullStatsTestgen_TARGET_BUFFER_BAF_target, 1, __154_TARGET_BUFFER_BAF_Link_NodeDescriptors}, // TARGET_BUFFER_BAF
    {"TARGET_BUFFER_AWBBG", &TestTFEFullStatsTestgen_TARGET_BUFFER_AWBBG_target, 1, __155_TARGET_BUFFER_AWBBG_Link_NodeDescriptors}, // TARGET_BUFFER_AWBBG
};

// TFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestTFEFullStatsTestgen_TfeFullStatsTestgenNode65544_0OutputPortDescriptors[] =
{
    {1, 1, 1, 0, 0, NULL}, // TFEOutputPortFull
    {7, 1, 1, 0, 0, NULL}, // TFEOutputPortStatsAECBG
    {8, 1, 1, 0, 0, NULL}, // TFEOutputPortStatsBHIST
    {9, 1, 1, 0, 0, NULL}, // TFEOutputPortStatsTLBG
    {10, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsBAF
    {11, 1, 1, 0, 0, NULL}, // TFEOutputPortStatsAWBBG
};

static ChiNode TestTFEFullStatsTestgen_TfeFullStatsTestgenNodes[] =
{
    {NULL, 65544, 0, {0, NULL, 6, TestTFEFullStatsTestgen_TfeFullStatsTestgenNode65544_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestTFEFullStatsTestgen_TfeFullStatsTestgenLinks[] =
{
    {{65544, 0, 1, 0}, 1, TestTFEFullStatsTestgen_TfeFullStatsTestgen_Link0_TFE0_Out1Desc, {0}, {0, 0}},
    {{65544, 0, 7, 0}, 1, TestTFEFullStatsTestgen_TfeFullStatsTestgen_Link1_TFE0_Out7Desc, {0}, {0, 0}},
    {{65544, 0, 8, 0}, 1, TestTFEFullStatsTestgen_TfeFullStatsTestgen_Link2_TFE0_Out8Desc, {0}, {0, 0}},
    {{65544, 0, 9, 0}, 1, TestTFEFullStatsTestgen_TfeFullStatsTestgen_Link3_TFE0_Out9Desc, {0}, {0, 0}},
    {{65544, 0, 10, 0}, 1, TestTFEFullStatsTestgen_TfeFullStatsTestgen_Link4_TFE0_Out10Desc, {0}, {0, 0}},
    {{65544, 0, 11, 0}, 1, TestTFEFullStatsTestgen_TfeFullStatsTestgen_Link5_TFE0_Out11Desc, {0}, {0, 0}},
};

enum TestTFEFullStatsTestgenPipelineIds
{
    TfeFullStatsTestgen = 0,
};

static ChiPipelineTargetCreateDescriptor TestTFEFullStatsTestgen_pipelines[] =
{
    {"TfeFullStatsTestgen", { 0, 1, TestTFEFullStatsTestgen_TfeFullStatsTestgenNodes, 6, TestTFEFullStatsTestgen_TfeFullStatsTestgenLinks, 1}, {6, TestTFEFullStatsTestgen_TfeFullStatsTestgen_sink_TargetDescriptors}, {0, NULL}},  // TfeFullStatsTestgen
};

/*==================== USECASE: TestIFEFullStatsTestgen =======================*/

static ChiBufferFormat TestIFEFullStatsTestgen_TARGET_BUFFER_FULL_formats[] =
{
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestIFEFullStatsTestgen_TARGET_BUFFER_RS_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStatsTestgen_TARGET_BUFFER_CS_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStatsTestgen_TARGET_BUFFER_IHIST_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStatsTestgen_TARGET_BUFFER_BHIST_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStatsTestgen_TARGET_BUFFER_HDRBE_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStatsTestgen_TARGET_BUFFER_HDRBHIST_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStatsTestgen_TARGET_BUFFER_TLBG_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStatsTestgen_TARGET_BUFFER_BF_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStatsTestgen_TARGET_BUFFER_AWBBG_formats[] =
{
    ChiFormatBlob,
};

static ChiTarget TestIFEFullStatsTestgen_TARGET_BUFFER_FULL_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2160
    },
    1,
    TestIFEFullStatsTestgen_TARGET_BUFFER_FULL_formats,
    NULL
}; // TARGET_BUFFER_FULL

static ChiTarget TestIFEFullStatsTestgen_TARGET_BUFFER_RS_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 32768, 1
    },
    1,
    TestIFEFullStatsTestgen_TARGET_BUFFER_RS_formats,
    NULL
}; // TARGET_BUFFER_RS

static ChiTarget TestIFEFullStatsTestgen_TARGET_BUFFER_CS_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 12480, 1
    },
    1,
    TestIFEFullStatsTestgen_TARGET_BUFFER_CS_formats,
    NULL
}; // TARGET_BUFFER_CS

static ChiTarget TestIFEFullStatsTestgen_TARGET_BUFFER_IHIST_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 2048, 1
    },
    1,
    TestIFEFullStatsTestgen_TARGET_BUFFER_IHIST_formats,
    NULL
}; // TARGET_BUFFER_IHIST

static ChiTarget TestIFEFullStatsTestgen_TARGET_BUFFER_BHIST_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 16384, 1
    },
    1,
    TestIFEFullStatsTestgen_TARGET_BUFFER_BHIST_formats,
    NULL
}; // TARGET_BUFFER_BHIST

static ChiTarget TestIFEFullStatsTestgen_TARGET_BUFFER_HDRBE_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 147456, 1
    },
    1,
    TestIFEFullStatsTestgen_TARGET_BUFFER_HDRBE_formats,
    NULL
}; // TARGET_BUFFER_HDRBE

static ChiTarget TestIFEFullStatsTestgen_TARGET_BUFFER_HDRBHIST_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 3072, 1
    },
    1,
    TestIFEFullStatsTestgen_TARGET_BUFFER_HDRBHIST_formats,
    NULL
}; // TARGET_BUFFER_HDRBHIST

static ChiTarget TestIFEFullStatsTestgen_TARGET_BUFFER_TLBG_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 147456, 1
    },
    1,
    TestIFEFullStatsTestgen_TARGET_BUFFER_TLBG_formats,
    NULL
}; // TARGET_BUFFER_TLBG

static ChiTarget TestIFEFullStatsTestgen_TARGET_BUFFER_BF_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 5768, 1
    },
    1,
    TestIFEFullStatsTestgen_TARGET_BUFFER_BF_formats,
    NULL
}; // TARGET_BUFFER_BF

static ChiTarget TestIFEFullStatsTestgen_TARGET_BUFFER_AWBBG_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 691200, 1
    },
    1,
    TestIFEFullStatsTestgen_TARGET_BUFFER_AWBBG_formats,
    NULL
}; // TARGET_BUFFER_AWBBG

static ChiTarget* TestIFEFullStatsTestgen_Targets[] =
{
	&TestIFEFullStatsTestgen_TARGET_BUFFER_FULL_target,
	&TestIFEFullStatsTestgen_TARGET_BUFFER_RS_target,
	&TestIFEFullStatsTestgen_TARGET_BUFFER_CS_target,
	&TestIFEFullStatsTestgen_TARGET_BUFFER_IHIST_target,
	&TestIFEFullStatsTestgen_TARGET_BUFFER_BHIST_target,
	&TestIFEFullStatsTestgen_TARGET_BUFFER_HDRBE_target,
	&TestIFEFullStatsTestgen_TARGET_BUFFER_HDRBHIST_target,
	&TestIFEFullStatsTestgen_TARGET_BUFFER_TLBG_target,
	&TestIFEFullStatsTestgen_TARGET_BUFFER_BF_target,
	&TestIFEFullStatsTestgen_TARGET_BUFFER_AWBBG_target
};

/*****************************Pipeline IfeFullStatsTestgen***************************/

static ChiLinkNodeDescriptor __156_TARGET_BUFFER_FULL_Link_NodeDescriptors[] =
{
    {65536, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link0_IFE0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_FULL
};

static ChiLinkNodeDescriptor __157_TARGET_BUFFER_RS_Link_NodeDescriptors[] =
{
    {65536, 0, 12 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link1_IFE0_Out12Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RS
};

static ChiLinkNodeDescriptor __158_TARGET_BUFFER_CS_Link_NodeDescriptors[] =
{
    {65536, 0, 13 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link2_IFE0_Out13Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CS
};

static ChiLinkNodeDescriptor __159_TARGET_BUFFER_IHIST_Link_NodeDescriptors[] =
{
    {65536, 0, 15 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link3_IFE0_Out15Desc[] =
{
    {2, 3, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_IHIST
};

static ChiLinkNodeDescriptor __160_TARGET_BUFFER_BHIST_Link_NodeDescriptors[] =
{
    {65536, 0, 16 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link4_IFE0_Out16Desc[] =
{
    {2, 4, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BHIST
};

static ChiLinkNodeDescriptor __161_TARGET_BUFFER_HDRBE_Link_NodeDescriptors[] =
{
    {65536, 0, 17 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link5_IFE0_Out17Desc[] =
{
    {2, 5, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_HDRBE
};

static ChiLinkNodeDescriptor __162_TARGET_BUFFER_HDRBHIST_Link_NodeDescriptors[] =
{
    {65536, 0, 18 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link6_IFE0_Out18Desc[] =
{
    {2, 6, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_HDRBHIST
};

static ChiLinkNodeDescriptor __163_TARGET_BUFFER_TLBG_Link_NodeDescriptors[] =
{
    {65536, 0, 19 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link7_IFE0_Out19Desc[] =
{
    {2, 7, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_TLBG
};

static ChiLinkNodeDescriptor __164_TARGET_BUFFER_BF_Link_NodeDescriptors[] =
{
    {65536, 0, 20 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link8_IFE0_Out20Desc[] =
{
    {2, 8, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BF
};

static ChiLinkNodeDescriptor __165_TARGET_BUFFER_AWBBG_Link_NodeDescriptors[] =
{
    {65536, 0, 21 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link9_IFE0_Out21Desc[] =
{
    {2, 9, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_AWBBG
};

static ChiTargetPortDescriptor TestIFEFullStatsTestgen_IfeFullStatsTestgen_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_FULL", &TestIFEFullStatsTestgen_TARGET_BUFFER_FULL_target, 1, __156_TARGET_BUFFER_FULL_Link_NodeDescriptors}, // TARGET_BUFFER_FULL
    {"TARGET_BUFFER_RS", &TestIFEFullStatsTestgen_TARGET_BUFFER_RS_target, 1, __157_TARGET_BUFFER_RS_Link_NodeDescriptors}, // TARGET_BUFFER_RS
    {"TARGET_BUFFER_CS", &TestIFEFullStatsTestgen_TARGET_BUFFER_CS_target, 1, __158_TARGET_BUFFER_CS_Link_NodeDescriptors}, // TARGET_BUFFER_CS
    {"TARGET_BUFFER_IHIST", &TestIFEFullStatsTestgen_TARGET_BUFFER_IHIST_target, 1, __159_TARGET_BUFFER_IHIST_Link_NodeDescriptors}, // TARGET_BUFFER_IHIST
    {"TARGET_BUFFER_BHIST", &TestIFEFullStatsTestgen_TARGET_BUFFER_BHIST_target, 1, __160_TARGET_BUFFER_BHIST_Link_NodeDescriptors}, // TARGET_BUFFER_BHIST
    {"TARGET_BUFFER_HDRBE", &TestIFEFullStatsTestgen_TARGET_BUFFER_HDRBE_target, 1, __161_TARGET_BUFFER_HDRBE_Link_NodeDescriptors}, // TARGET_BUFFER_HDRBE
    {"TARGET_BUFFER_HDRBHIST", &TestIFEFullStatsTestgen_TARGET_BUFFER_HDRBHIST_target, 1, __162_TARGET_BUFFER_HDRBHIST_Link_NodeDescriptors}, // TARGET_BUFFER_HDRBHIST
    {"TARGET_BUFFER_TLBG", &TestIFEFullStatsTestgen_TARGET_BUFFER_TLBG_target, 1, __163_TARGET_BUFFER_TLBG_Link_NodeDescriptors}, // TARGET_BUFFER_TLBG
    {"TARGET_BUFFER_BF", &TestIFEFullStatsTestgen_TARGET_BUFFER_BF_target, 1, __164_TARGET_BUFFER_BF_Link_NodeDescriptors}, // TARGET_BUFFER_BF
    {"TARGET_BUFFER_AWBBG", &TestIFEFullStatsTestgen_TARGET_BUFFER_AWBBG_target, 1, __165_TARGET_BUFFER_AWBBG_Link_NodeDescriptors}, // TARGET_BUFFER_AWBBG
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIFEFullStatsTestgen_IfeFullStatsTestgenNode65536_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // IFEOutputPortFull
    {12, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsRS
    {13, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsCS
    {15, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsIHIST
    {16, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsBHIST
    {17, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsHDRBE
    {18, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsHDRBHIST
    {19, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {20, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsBF
    {21, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
};

static ChiNode TestIFEFullStatsTestgen_IfeFullStatsTestgenNodes[] =
{
    {NULL, 65536, 0, {0, NULL, 10, TestIFEFullStatsTestgen_IfeFullStatsTestgenNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestIFEFullStatsTestgen_IfeFullStatsTestgenLinks[] =
{
    {{65536, 0, 0, 0}, 1, TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link0_IFE0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 12, 0}, 1, TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link1_IFE0_Out12Desc, {0}, {0, 0}},
    {{65536, 0, 13, 0}, 1, TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link2_IFE0_Out13Desc, {0}, {0, 0}},
    {{65536, 0, 15, 0}, 1, TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link3_IFE0_Out15Desc, {0}, {0, 0}},
    {{65536, 0, 16, 0}, 1, TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link4_IFE0_Out16Desc, {0}, {0, 0}},
    {{65536, 0, 17, 0}, 1, TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link5_IFE0_Out17Desc, {0}, {0, 0}},
    {{65536, 0, 18, 0}, 1, TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link6_IFE0_Out18Desc, {0}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link7_IFE0_Out19Desc, {0}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link8_IFE0_Out20Desc, {0}, {0, 0}},
    {{65536, 0, 21, 0}, 1, TestIFEFullStatsTestgen_IfeFullStatsTestgen_Link9_IFE0_Out21Desc, {0}, {0, 0}},
};

enum TestIFEFullStatsTestgenPipelineIds
{
    IfeFullStatsTestgen = 0,
};

static ChiPipelineTargetCreateDescriptor TestIFEFullStatsTestgen_pipelines[] =
{
    {"IfeFullStatsTestgen", { 0, 1, TestIFEFullStatsTestgen_IfeFullStatsTestgenNodes, 10, TestIFEFullStatsTestgen_IfeFullStatsTestgenLinks, 1}, {10, TestIFEFullStatsTestgen_IfeFullStatsTestgen_sink_TargetDescriptors}, {0, NULL}},  // IfeFullStatsTestgen
};

/*==================== USECASE: TestIFEFullStats =======================*/

static ChiBufferFormat TestIFEFullStats_TARGET_BUFFER_FULL_formats[] =
{
    ChiFormatYUV420NV12,
};

static ChiBufferFormat TestIFEFullStats_TARGET_BUFFER_RS_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStats_TARGET_BUFFER_CS_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStats_TARGET_BUFFER_IHIST_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStats_TARGET_BUFFER_BHIST_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStats_TARGET_BUFFER_HDRBE_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStats_TARGET_BUFFER_HDRBHIST_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStats_TARGET_BUFFER_TLBG_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStats_TARGET_BUFFER_BF_formats[] =
{
    ChiFormatBlob,
};

static ChiBufferFormat TestIFEFullStats_TARGET_BUFFER_AWBBG_formats[] =
{
    ChiFormatBlob,
};

static ChiTarget TestIFEFullStats_TARGET_BUFFER_FULL_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 4096, 2160
    },
    1,
    TestIFEFullStats_TARGET_BUFFER_FULL_formats,
    NULL
}; // TARGET_BUFFER_FULL

static ChiTarget TestIFEFullStats_TARGET_BUFFER_RS_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 32768, 1
    },
    1,
    TestIFEFullStats_TARGET_BUFFER_RS_formats,
    NULL
}; // TARGET_BUFFER_RS

static ChiTarget TestIFEFullStats_TARGET_BUFFER_CS_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 12480, 1
    },
    1,
    TestIFEFullStats_TARGET_BUFFER_CS_formats,
    NULL
}; // TARGET_BUFFER_CS

static ChiTarget TestIFEFullStats_TARGET_BUFFER_IHIST_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 2048, 1
    },
    1,
    TestIFEFullStats_TARGET_BUFFER_IHIST_formats,
    NULL
}; // TARGET_BUFFER_IHIST

static ChiTarget TestIFEFullStats_TARGET_BUFFER_BHIST_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 16384, 1
    },
    1,
    TestIFEFullStats_TARGET_BUFFER_BHIST_formats,
    NULL
}; // TARGET_BUFFER_BHIST

static ChiTarget TestIFEFullStats_TARGET_BUFFER_HDRBE_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 147456, 1
    },
    1,
    TestIFEFullStats_TARGET_BUFFER_HDRBE_formats,
    NULL
}; // TARGET_BUFFER_HDRBE

static ChiTarget TestIFEFullStats_TARGET_BUFFER_HDRBHIST_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 3072, 1
    },
    1,
    TestIFEFullStats_TARGET_BUFFER_HDRBHIST_formats,
    NULL
}; // TARGET_BUFFER_HDRBHIST

static ChiTarget TestIFEFullStats_TARGET_BUFFER_TLBG_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 147456, 1
    },
    1,
    TestIFEFullStats_TARGET_BUFFER_TLBG_formats,
    NULL
}; // TARGET_BUFFER_TLBG

static ChiTarget TestIFEFullStats_TARGET_BUFFER_BF_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 5768, 1
    },
    1,
    TestIFEFullStats_TARGET_BUFFER_BF_formats,
    NULL
}; // TARGET_BUFFER_BF

static ChiTarget TestIFEFullStats_TARGET_BUFFER_AWBBG_target =
{
    ChiStreamTypeOutput,
    {   // (MinW, MinH, MaxW, MaxH)
        0, 0, 691200, 1
    },
    1,
    TestIFEFullStats_TARGET_BUFFER_AWBBG_formats,
    NULL
}; // TARGET_BUFFER_AWBBG

static ChiTarget* TestIFEFullStats_Targets[] =
{
	&TestIFEFullStats_TARGET_BUFFER_FULL_target,
	&TestIFEFullStats_TARGET_BUFFER_RS_target,
	&TestIFEFullStats_TARGET_BUFFER_CS_target,
	&TestIFEFullStats_TARGET_BUFFER_IHIST_target,
	&TestIFEFullStats_TARGET_BUFFER_BHIST_target,
	&TestIFEFullStats_TARGET_BUFFER_HDRBE_target,
	&TestIFEFullStats_TARGET_BUFFER_HDRBHIST_target,
	&TestIFEFullStats_TARGET_BUFFER_TLBG_target,
	&TestIFEFullStats_TARGET_BUFFER_BF_target,
	&TestIFEFullStats_TARGET_BUFFER_AWBBG_target
};

/*****************************Pipeline IfeFullStats***************************/

static ChiLinkNodeDescriptor TestIFEFullStats_IfeFullStats_Link0_Sensor0_Out0Desc[] =
{
    {65536, 0, 2, 0, {0, NULL}}, // IFE
};

static ChiLinkNodeDescriptor __166_TARGET_BUFFER_FULL_Link_NodeDescriptors[] =
{
    {65536, 0, 0 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStats_IfeFullStats_Link1_IFE0_Out0Desc[] =
{
    {2, 0, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_FULL
};

static ChiLinkNodeDescriptor __167_TARGET_BUFFER_RS_Link_NodeDescriptors[] =
{
    {65536, 0, 12 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStats_IfeFullStats_Link2_IFE0_Out12Desc[] =
{
    {2, 1, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RS
};

static ChiLinkNodeDescriptor __168_TARGET_BUFFER_CS_Link_NodeDescriptors[] =
{
    {65536, 0, 13 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStats_IfeFullStats_Link3_IFE0_Out13Desc[] =
{
    {2, 2, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_CS
};

static ChiLinkNodeDescriptor __169_TARGET_BUFFER_RS_Link_NodeDescriptors[] =
{
    {65536, 0, 15 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStats_IfeFullStats_Link4_IFE0_Out15Desc[] =
{
    {2, 3, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_RS
};

static ChiLinkNodeDescriptor __170_TARGET_BUFFER_BHIST_Link_NodeDescriptors[] =
{
    {65536, 0, 16 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStats_IfeFullStats_Link5_IFE0_Out16Desc[] =
{
    {2, 4, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BHIST
};

static ChiLinkNodeDescriptor __171_TARGET_BUFFER_HDRBE_Link_NodeDescriptors[] =
{
    {65536, 0, 17 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStats_IfeFullStats_Link6_IFE0_Out17Desc[] =
{
    {2, 5, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_HDRBE
};

static ChiLinkNodeDescriptor __172_TARGET_BUFFER_HDRBHIST_Link_NodeDescriptors[] =
{
    {65536, 0, 18 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStats_IfeFullStats_Link7_IFE0_Out18Desc[] =
{
    {2, 6, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_HDRBHIST
};

static ChiLinkNodeDescriptor __173_TARGET_BUFFER_TLBG_Link_NodeDescriptors[] =
{
    {65536, 0, 19 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStats_IfeFullStats_Link8_IFE0_Out19Desc[] =
{
    {2, 7, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_TLBG
};

static ChiLinkNodeDescriptor __174_TARGET_BUFFER_BF_Link_NodeDescriptors[] =
{
    {65536, 0, 20 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStats_IfeFullStats_Link9_IFE0_Out20Desc[] =
{
    {2, 8, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_BF
};

static ChiLinkNodeDescriptor __175_TARGET_BUFFER_AWBBG_Link_NodeDescriptors[] =
{
    {65536, 0, 21 }, 
};
static ChiLinkNodeDescriptor TestIFEFullStats_IfeFullStats_Link10_IFE0_Out21Desc[] =
{
    {2, 9, 0, 0, {0, NULL}}, // SinkBuffer ]-> TARGET_BUFFER_AWBBG
};

static ChiTargetPortDescriptor TestIFEFullStats_IfeFullStats_sink_TargetDescriptors[] =
{
    {"TARGET_BUFFER_FULL", &TestIFEFullStats_TARGET_BUFFER_FULL_target, 1, __166_TARGET_BUFFER_FULL_Link_NodeDescriptors}, // TARGET_BUFFER_FULL
    {"TARGET_BUFFER_RS", &TestIFEFullStats_TARGET_BUFFER_RS_target, 1, __167_TARGET_BUFFER_RS_Link_NodeDescriptors}, // TARGET_BUFFER_RS
    {"TARGET_BUFFER_CS", &TestIFEFullStats_TARGET_BUFFER_CS_target, 1, __168_TARGET_BUFFER_CS_Link_NodeDescriptors}, // TARGET_BUFFER_CS
    {"TARGET_BUFFER_RS", &TestIFEFullStats_TARGET_BUFFER_RS_target, 1, __169_TARGET_BUFFER_RS_Link_NodeDescriptors}, // TARGET_BUFFER_RS
    {"TARGET_BUFFER_BHIST", &TestIFEFullStats_TARGET_BUFFER_BHIST_target, 1, __170_TARGET_BUFFER_BHIST_Link_NodeDescriptors}, // TARGET_BUFFER_BHIST
    {"TARGET_BUFFER_HDRBE", &TestIFEFullStats_TARGET_BUFFER_HDRBE_target, 1, __171_TARGET_BUFFER_HDRBE_Link_NodeDescriptors}, // TARGET_BUFFER_HDRBE
    {"TARGET_BUFFER_HDRBHIST", &TestIFEFullStats_TARGET_BUFFER_HDRBHIST_target, 1, __172_TARGET_BUFFER_HDRBHIST_Link_NodeDescriptors}, // TARGET_BUFFER_HDRBHIST
    {"TARGET_BUFFER_TLBG", &TestIFEFullStats_TARGET_BUFFER_TLBG_target, 1, __173_TARGET_BUFFER_TLBG_Link_NodeDescriptors}, // TARGET_BUFFER_TLBG
    {"TARGET_BUFFER_BF", &TestIFEFullStats_TARGET_BUFFER_BF_target, 1, __174_TARGET_BUFFER_BF_Link_NodeDescriptors}, // TARGET_BUFFER_BF
    {"TARGET_BUFFER_AWBBG", &TestIFEFullStats_TARGET_BUFFER_AWBBG_target, 1, __175_TARGET_BUFFER_AWBBG_Link_NodeDescriptors}, // TARGET_BUFFER_AWBBG
};

// Sensor0 Output Port Descriptors
static ChiOutputPortDescriptor TestIFEFullStats_IfeFullStatsNode0_0OutputPortDescriptors[] =
{
    {0, 0, 0, 0, 0, NULL}, // SensorOutputPort0
};

// IFE0 Input Port Descriptors
static ChiInputPortDescriptor TestIFEFullStats_IfeFullStatsNode65536_0InputPortDescriptors[] =
{
    {2, 0, 0}, // IFEInputPortSensor
};

// IFE0 Output Port Descriptors
static ChiOutputPortDescriptor TestIFEFullStats_IfeFullStatsNode65536_0OutputPortDescriptors[] =
{
    {0, 1, 1, 0, 0, NULL}, // IFEOutputPortFull
    {12, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsRS
    {13, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsCS
    {15, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsIHIST
    {16, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsBHIST
    {17, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsHDRBE
    {18, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsHDRBHIST
    {19, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsTLBG
    {20, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsBF
    {21, 1, 1, 0, 0, NULL}, // IFEOutputPortStatsAWBBG
};

static ChiNode TestIFEFullStats_IfeFullStatsNodes[] =
{
    {NULL, 0, 0, {0, NULL, 1, TestIFEFullStats_IfeFullStatsNode0_0OutputPortDescriptors}, 0, {0, NULL}},
    {NULL, 65536, 0, {1, TestIFEFullStats_IfeFullStatsNode65536_0InputPortDescriptors, 10, TestIFEFullStats_IfeFullStatsNode65536_0OutputPortDescriptors}, 0, {0, NULL}},
};

static ChiNodeLink TestIFEFullStats_IfeFullStatsLinks[] =
{
    {{0, 0, 0, 0}, 1, TestIFEFullStats_IfeFullStats_Link0_Sensor0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 0, 0}, 1, TestIFEFullStats_IfeFullStats_Link1_IFE0_Out0Desc, {0}, {0, 0}},
    {{65536, 0, 12, 0}, 1, TestIFEFullStats_IfeFullStats_Link2_IFE0_Out12Desc, {0}, {0, 0}},
    {{65536, 0, 13, 0}, 1, TestIFEFullStats_IfeFullStats_Link3_IFE0_Out13Desc, {0}, {0, 0}},
    {{65536, 0, 15, 0}, 1, TestIFEFullStats_IfeFullStats_Link4_IFE0_Out15Desc, {0}, {0, 0}},
    {{65536, 0, 16, 0}, 1, TestIFEFullStats_IfeFullStats_Link5_IFE0_Out16Desc, {0}, {0, 0}},
    {{65536, 0, 17, 0}, 1, TestIFEFullStats_IfeFullStats_Link6_IFE0_Out17Desc, {0}, {0, 0}},
    {{65536, 0, 18, 0}, 1, TestIFEFullStats_IfeFullStats_Link7_IFE0_Out18Desc, {0}, {0, 0}},
    {{65536, 0, 19, 0}, 1, TestIFEFullStats_IfeFullStats_Link8_IFE0_Out19Desc, {0}, {0, 0}},
    {{65536, 0, 20, 0}, 1, TestIFEFullStats_IfeFullStats_Link9_IFE0_Out20Desc, {0}, {0, 0}},
    {{65536, 0, 21, 0}, 1, TestIFEFullStats_IfeFullStats_Link10_IFE0_Out21Desc, {0}, {0, 0}},
};

enum TestIFEFullStatsPipelineIds
{
    IfeFullStats = 0,
};

static ChiPipelineTargetCreateDescriptor TestIFEFullStats_pipelines[] =
{
    {"IfeFullStats", { 0, 2, TestIFEFullStats_IfeFullStatsNodes, 11, TestIFEFullStats_IfeFullStatsLinks, 1}, {10, TestIFEFullStats_IfeFullStats_sink_TargetDescriptors}, {0, NULL}},  // IfeFullStats
};

static ChiUsecase Usecases1Target[] =
{
    {"TestIFEFull"                                                         , 0, 1, TestIFEFull_Targets                                                   , 1, TestIFEFull_pipelines,                                                 NULL, TRUE},
    {"TestIPEFull"                                                         , 0, 1, TestIPEFull_Targets                                                   , 1, TestIPEFull_pipelines,                                                 NULL, TRUE},
    {"TestIFEFullTestgen"                                                  , 0, 1, TestIFEFullTestgen_Targets                                            , 1, TestIFEFullTestgen_pipelines,                                          NULL, TRUE},
    {"UsecaseRaw"                                                          , 0, 1, UsecaseRaw_Targets                                                    , 4, UsecaseRaw_pipelines,                                                  NULL, TRUE},
    {"TestCustomNode"                                                      , 0, 1, TestCustomNode_Targets                                                , 1, TestCustomNode_pipelines,                                              NULL, TRUE},
    {"TestMemcpy"                                                          , 0, 1, TestMemcpy_Targets                                                    , 2, TestMemcpy_pipelines,                                                  NULL, TRUE},
    {"TestPreviewHVX"                                                      , 0, 1, TestPreviewHVX_Targets                                                , 1, TestPreviewHVX_pipelines,                                              NULL, TRUE},
    {"TestBypassNode"                                                      , 0, 1, TestBypassNode_Targets                                                , 1, TestBypassNode_pipelines,                                              NULL, TRUE},
    {"TestInplaceNode"                                                     , 0, 1, TestInplaceNode_Targets                                               , 1, TestInplaceNode_pipelines,                                             NULL, TRUE},
    {"TestIPEFullTestgen"                                                  , 0, 1, TestIPEFullTestgen_Targets                                            , 1, TestIPEFullTestgen_pipelines,                                          NULL, TRUE},
    {"TestIPE3ATestgen"                                                    , 0, 1, TestIPE3ATestgen_Targets                                              , 1, TestIPE3ATestgen_pipelines,                                            NULL, TRUE},
    {"TestCVPNode"                                                         , 0, 1, TestCVPNode_Targets                                                   , 3, TestCVPNode_pipelines,                                                 NULL, TRUE},
};

static ChiUsecase Usecases2Target[] =
{
    {"TestOfflineIPE"                                                      , 0, 2, TestOfflineIPE_Targets                                                , 2, TestOfflineIPE_pipelines,                                              NULL, TRUE},
    {"TestOfflineJPEG"                                                     , 0, 2, TestOfflineJPEG_Targets                                               , 1, TestOfflineJPEG_pipelines,                                             NULL, TRUE},
    {"TestOfflineBPSIPE"                                                   , 0, 2, TestOfflineBPSIPE_Targets                                             , 3, TestOfflineBPSIPE_pipelines,                                           NULL, TRUE},
    {"TestOfflineBPSIPEJpeg"                                               , 0, 2, TestOfflineBPSIPEJpeg_Targets                                         , 1, TestOfflineBPSIPEJpeg_pipelines,                                       NULL, TRUE},
    {"TestOfflineFD"                                                       , 0, 2, TestOfflineFD_Targets                                                 , 1, TestOfflineFD_pipelines,                                               NULL, TRUE},
    {"TestIPETestgen"                                                      , 0, 2, TestIPETestgen_Targets                                                , 4, TestIPETestgen_pipelines,                                              NULL, TRUE},
    {"TestIPESensor"                                                       , 0, 2, TestIPESensor_Targets                                                 , 1, TestIPESensor_pipelines,                                               NULL, TRUE},
    {"TestBPSWithIPEAndDS"                                                 , 0, 2, TestBPSWithIPEAndDS_Targets                                           , 1, TestBPSWithIPEAndDS_pipelines,                                         NULL, TRUE},
    {"TestBPSIdealRaw"                                                     , 0, 2, TestBPSIdealRaw_Targets                                               , 1, TestBPSIdealRaw_pipelines,                                             NULL, TRUE},
    {"TestChiDepth"                                                        , 0, 2, TestChiDepth_Targets                                                  , 2, TestChiDepth_pipelines,                                                NULL, TRUE},
    {"UsecaseChiGPUNode"                                                   , 0, 2, UsecaseChiGPUNode_Targets                                             , 1, UsecaseChiGPUNode_pipelines,                                           NULL, TRUE},
    {"RealtimeNodesTest"                                                   , 0, 2, RealtimeNodesTest_Targets                                             , 3, RealtimeNodesTest_pipelines,                                           NULL, TRUE},
    {"UsecaseExternalNode"                                                 , 0, 2, UsecaseExternalNode_Targets                                           , 2, UsecaseExternalNode_pipelines,                                         NULL, TRUE},
    {"UsecaseGeneric"                                                      , 0, 2, UsecaseGeneric_Targets                                                , 4, UsecaseGeneric_pipelines,                                              NULL, TRUE},
    {"UsecaseGenericDownscale"                                             , 0, 2, UsecaseGenericDownscale_Targets                                       , 2, UsecaseGenericDownscale_pipelines,                                     NULL, TRUE},
    {"UsecaseIPEJPEG"                                                      , 0, 2, UsecaseIPEJPEG_Targets                                                , 1, UsecaseIPEJPEG_pipelines,                                              NULL, TRUE},
    {"UsecaseMimasGeneric"                                                 , 0, 2, UsecaseMimasGeneric_Targets                                           , 2, UsecaseMimasGeneric_pipelines,                                         NULL, TRUE},
};

static ChiUsecase Usecases3Target[] =
{
    {"TestZSLUseCase"                                                      , 0, 3, TestZSLUseCase_Targets                                                , 8, TestZSLUseCase_pipelines,                                              NULL, TRUE},
    {"TestOfflineIPESIMO"                                                  , 0, 3, TestOfflineIPESIMO_Targets                                            , 1, TestOfflineIPESIMO_pipelines,                                          NULL, TRUE},
    {"OfflineBPSSingleStatWithIPE"                                         , 0, 3, OfflineBPSSingleStatWithIPE_Targets                                   , 2, OfflineBPSSingleStatWithIPE_pipelines,                                 NULL, TRUE},
    {"TestPIPCam"                                                          , 0, 3, TestPIPCam_Targets                                                    , 4, TestPIPCam_pipelines,                                                  NULL, TRUE},
    {"UsecaseGeneric2Streams"                                              , 0, 3, UsecaseGeneric2Streams_Targets                                        , 6, UsecaseGeneric2Streams_pipelines,                                      NULL, TRUE},
    {"UsecaseMimasGeneric2Streams"                                         , 0, 3, UsecaseMimasGeneric2Streams_Targets                                   , 3, UsecaseMimasGeneric2Streams_pipelines,                                 NULL, TRUE},
};

static ChiUsecase Usecases4Target[] =
{
    {"OfflineBPSStats"                                                     , 0, 4, OfflineBPSStats_Targets                                               , 1, OfflineBPSStats_pipelines,                                             NULL, TRUE},
    {"OfflineBPSStatsWithIPE"                                              , 0, 4, OfflineBPSStatsWithIPE_Targets                                        , 1, OfflineBPSStatsWithIPE_pipelines,                                      NULL, TRUE},
};

static ChiUsecase Usecases5Target[] =
{
    {"TestPreviewCallbackSnapshotWithThumbnail"                            , 0, 5, TestPreviewCallbackSnapshotWithThumbnail_Targets                      , 5, TestPreviewCallbackSnapshotWithThumbnail_pipelines,                    NULL, TRUE},
    {"TestGPUDSPorts"                                                      , 0, 5, TestGPUDSPorts_Targets                                                , 1, TestGPUDSPorts_pipelines,                                              NULL, TRUE},
};

static ChiUsecase Usecases6Target[] =
{
    {"TestTFEFullStatsTestgen"                                             , 0, 6, TestTFEFullStatsTestgen_Targets                                       , 1, TestTFEFullStatsTestgen_pipelines,                                     NULL, TRUE},
};

static ChiUsecase Usecases10Target[] =
{
    {"TestIFEFullStatsTestgen"                                             , 0, 10, TestIFEFullStatsTestgen_Targets                                       , 1, TestIFEFullStatsTestgen_pipelines,                                     NULL, TRUE},
    {"TestIFEFullStats"                                                    , 0, 10, TestIFEFullStats_Targets                                              , 1, TestIFEFullStats_pipelines,                                            NULL, TRUE},
};

static const UINT ChiMaxNumTargets = 10;

static struct ChiTargetUsecases PerNumTargetUsecases[] =
{	{12, Usecases1Target},
	{17, Usecases2Target},
	{6, Usecases3Target},
	{2, Usecases4Target},
	{2, Usecases5Target},
	{1, Usecases6Target},
	{0, NULL},
	{0, NULL},
	{0, NULL},
	{2, Usecases10Target},
};


enum UsecaseId1Target
{
    TestIFEFullId  = 0,
    TestIPEFullId,
    TestIFEFullTestgenId,
    UsecaseRawId,
    TestCustomNodeId,
    TestMemcpyId,
    TestPreviewHVXId,
    TestBypassNodeId,
    TestInplaceNodeId,
    TestIPEFullTestgenId,
    TestIPE3ATestgenId,
    TestCVPNodeId,
};

enum UsecaseId2Target
{
    TestOfflineIPEId  = 0,
    TestOfflineJPEGId,
    TestOfflineBPSIPEId,
    TestOfflineBPSIPEJpegId,
    TestOfflineFDId,
    TestIPETestgenId,
    TestIPESensorId,
    TestBPSWithIPEAndDSId,
    TestBPSIdealRawId,
    TestChiDepthId,
    UsecaseChiGPUNodeId,
    RealtimeNodesTestId,
    UsecaseExternalNodeId,
    UsecaseGenericId,
    UsecaseGenericDownscaleId,
    UsecaseIPEJPEGId,
    UsecaseMimasGenericId,
};

enum UsecaseId3Target
{
    TestZSLUseCaseId  = 0,
    TestOfflineIPESIMOId,
    OfflineBPSSingleStatWithIPEId,
    TestPIPCamId,
    UsecaseGeneric2StreamsId,
    UsecaseMimasGeneric2StreamsId,
};

enum UsecaseId4Target
{
    OfflineBPSStatsId  = 0,
    OfflineBPSStatsWithIPEId,
};

enum UsecaseId5Target
{
    TestPreviewCallbackSnapshotWithThumbnailId  = 0,
    TestGPUDSPortsId,
};

enum UsecaseId6Target
{
    TestTFEFullStatsTestgenId  = 0,
};

enum UsecaseId10Target
{
    TestIFEFullStatsTestgenId  = 0,
    TestIFEFullStatsId,
};

#define g_pOfflineBPSSingleStatWithIPE (&Usecases3Target[OfflineBPSSingleStatWithIPEId])
#define g_pOfflineBPSStats (&Usecases4Target[OfflineBPSStatsId])
#define g_pOfflineBPSStatsWithIPE (&Usecases4Target[OfflineBPSStatsWithIPEId])
#define g_pRealtimeNodesTest (&Usecases2Target[RealtimeNodesTestId])
#define g_pTestBPSIdealRaw (&Usecases2Target[TestBPSIdealRawId])
#define g_pTestBPSWithIPEAndDS (&Usecases2Target[TestBPSWithIPEAndDSId])
#define g_pTestBypassNode (&Usecases1Target[TestBypassNodeId])
#define g_pTestCVPNode (&Usecases1Target[TestCVPNodeId])
#define g_pTestChiDepth (&Usecases2Target[TestChiDepthId])
#define g_pTestCustomNode (&Usecases1Target[TestCustomNodeId])
#define g_pTestGPUDSPorts (&Usecases5Target[TestGPUDSPortsId])
#define g_pTestIFEFull (&Usecases1Target[TestIFEFullId])
#define g_pTestIFEFullStats (&Usecases10Target[TestIFEFullStatsId])
#define g_pTestIFEFullStatsTestgen (&Usecases10Target[TestIFEFullStatsTestgenId])
#define g_pTestIFEFullTestgen (&Usecases1Target[TestIFEFullTestgenId])
#define g_pTestIPE3ATestgen (&Usecases1Target[TestIPE3ATestgenId])
#define g_pTestIPEFull (&Usecases1Target[TestIPEFullId])
#define g_pTestIPEFullTestgen (&Usecases1Target[TestIPEFullTestgenId])
#define g_pTestIPESensor (&Usecases2Target[TestIPESensorId])
#define g_pTestIPETestgen (&Usecases2Target[TestIPETestgenId])
#define g_pTestInplaceNode (&Usecases1Target[TestInplaceNodeId])
#define g_pTestMemcpy (&Usecases1Target[TestMemcpyId])
#define g_pTestOfflineBPSIPE (&Usecases2Target[TestOfflineBPSIPEId])
#define g_pTestOfflineBPSIPEJpeg (&Usecases2Target[TestOfflineBPSIPEJpegId])
#define g_pTestOfflineFD (&Usecases2Target[TestOfflineFDId])
#define g_pTestOfflineIPE (&Usecases2Target[TestOfflineIPEId])
#define g_pTestOfflineIPESIMO (&Usecases3Target[TestOfflineIPESIMOId])
#define g_pTestOfflineJPEG (&Usecases2Target[TestOfflineJPEGId])
#define g_pTestPIPCam (&Usecases3Target[TestPIPCamId])
#define g_pTestPreviewCallbackSnapshotWithThumbnail (&Usecases5Target[TestPreviewCallbackSnapshotWithThumbnailId])
#define g_pTestPreviewHVX (&Usecases1Target[TestPreviewHVXId])
#define g_pTestTFEFullStatsTestgen (&Usecases6Target[TestTFEFullStatsTestgenId])
#define g_pTestZSLUseCase (&Usecases3Target[TestZSLUseCaseId])
#define g_pUsecaseChiGPUNode (&Usecases2Target[UsecaseChiGPUNodeId])
#define g_pUsecaseExternalNode (&Usecases2Target[UsecaseExternalNodeId])
#define g_pUsecaseGeneric (&Usecases2Target[UsecaseGenericId])
#define g_pUsecaseGeneric2Streams (&Usecases3Target[UsecaseGeneric2StreamsId])
#define g_pUsecaseGenericDownscale (&Usecases2Target[UsecaseGenericDownscaleId])
#define g_pUsecaseIPEJPEG (&Usecases2Target[UsecaseIPEJPEGId])
#define g_pUsecaseMimasGeneric (&Usecases2Target[UsecaseMimasGenericId])
#define g_pUsecaseMimasGeneric2Streams (&Usecases3Target[UsecaseMimasGeneric2StreamsId])
#define g_pUsecaseRaw (&Usecases1Target[UsecaseRawId])
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USECASEDEFS_H

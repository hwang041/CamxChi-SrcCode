////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  camxbpspipelinetitan175.cpp
/// @brief BPS Pipeline for Titan 175
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "camxbpsabf40.h"
#include "camxbpsawbbgstats14.h"
#include "camxbpsbpcpdpc20.h"
#include "camxbpscc13.h"
#include "camxbpscst12.h"
#include "camxbpsdemosaic36.h"
#include "camxbpsdemux13.h"
#include "camxbpsgamma16.h"
#include "camxbpsgic30.h"
#include "camxbpsgtm10.h"
#include "camxbpshdr22.h"
#include "camxbpshdrbhiststats13.h"
#include "camxbpshnr10.h"
#include "camxbpslinearization34.h"
#include "camxbpslsc34.h"
#include "camxbpspedestal13.h"
#include "camxbpswb13.h"
#include "camxswtmc11.h"
#include "camxswtmc12.h"

#include "camxbpspipelinetitan175.h"

CAMX_NAMESPACE_BEGIN

/// @brief List of BPS IQ modules. Order of modules depends on inter dependency and not pipeline order
static BPSIQModuleInfo BPSPipeline175ModuleList[] =
{
    {
        ISPIQModuleType::SWTMC,
        TRUE,
        SWTMC12::CreateBPS,
        0x00000000
    },
    {
        ISPIQModuleType::BPSPedestalCorrection,
        FALSE,
        BPSPedestal13::Create,
        0x10030000
    },
    {
        ISPIQModuleType::BPSABF,
        TRUE,
        BPSABF40::Create,
        0x40000000
    },
    {
        ISPIQModuleType::BPSLinearization,
        TRUE,
        BPSLinearization34::Create,
        0x30040000
    },
    {
        ISPIQModuleType::BPSHDR,
        TRUE,
        BPSHDR22::Create,
        0x20020000
    },
    {
        ISPIQModuleType::BPSBPCPDPC,
        TRUE,
        BPSBPCPDPC20::Create,
        0x20000000
    },
    {
        ISPIQModuleType::BPSDemux,
        TRUE,
        BPSDemux13::Create,
        0x10000000
    },
    {
        ISPIQModuleType::BPSGIC,
        TRUE,
        BPSGIC30::Create,
        0x30000000
    },
    {
        ISPIQModuleType::BPSLSC,
        TRUE,
        BPSLSC34::Create,
        0x30040000
    },
    {
        ISPIQModuleType::BPSWB,
        TRUE,
        BPSWB13::Create,
        // WB and Demosaic are combined as one HW block, it will have one HW version
        0x30060000
    },
    {
        ISPIQModuleType::BPSDemosaic,
        TRUE,
        BPSDemosaic36::Create,
        0x30060000
    },
    {
        ISPIQModuleType::BPSCC,
        TRUE,
        BPSCC13::Create,
        0x10030000
    },
    {
        ISPIQModuleType::BPSGTM,
        TRUE,
        BPSGTM10::Create,
        0x10010000
    },
    {
        ISPIQModuleType::BPSGamma,
        TRUE,
        BPSGamma16::Create,
        0x10060000
    },
    {
        ISPIQModuleType::BPSCST,
        TRUE,
        BPSCST12::Create,
        0x10020000
    },
    {
        ISPIQModuleType::BPSHNR,
        TRUE,
        BPSHNR10::Create,
        0x10000002
    },
    {
        ISPIQModuleType::BPSAWBBG,
        TRUE,
        BPSAWBBGStats14::Create,
        0x10040000
    },
    {
        ISPIQModuleType::BPSHDRBHist,
        FALSE,
        BPSHDRBHist13Stats::Create,
        0x10030000
    },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BPSPipelineTitan175::GetModuleListForMode
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CamxResult BPSPipelineTitan175::GetModuleListForMode(
    BPSIQModuleList* pIQmoduleInfo,
    UINT32 mode)
{
    CAMX_UNREFERENCED_PARAM(pIQmoduleInfo);
    CAMX_UNREFERENCED_PARAM(mode);

    return CamxResultSuccess;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BPSPipelineTitan175::GetModuleList
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CamxResult BPSPipelineTitan175::GetModuleList(
    BPSIQModuleList* pIQmoduleInfo)
{
    CamxResult result = CamxResultSuccess;

    if (NULL != pIQmoduleInfo)
    {
        Utils::Memset(pIQmoduleInfo, 0, sizeof(BPSIQModuleList));

        UINT32 numBPSModules = sizeof(BPSPipeline175ModuleList) / sizeof(BPSIQModuleInfo);

        for (UINT32 i = 0; i < numBPSModules; i++)
        {
            if (TRUE == BPSPipeline175ModuleList[i].isEnabled)
            {
                pIQmoduleInfo->pBPSIQModule[pIQmoduleInfo->numBPSIQModules] = &BPSPipeline175ModuleList[i];
                pIQmoduleInfo->numBPSIQModules++;
            }
        }
    }
    else
    {
        CAMX_LOG_ERROR(CamxLogGroupIQMod, "Invalid Argument");
        result = CamxResultEInvalidArg;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BPSPipelineTitan175::GetCapability
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CamxResult BPSPipelineTitan175::GetCapability(
    VOID* pCapabilityInfo)
{
    BPSCapabilityInfo* pBPSCapabilityInfo = static_cast<BPSCapabilityInfo*>(pCapabilityInfo);
    CamxResult         result             = CamxResultSuccess;
    if (NULL != pBPSCapabilityInfo)
    {
        pBPSCapabilityInfo->UBWCSupportedVersionMask = UBWCVersion2Mask | UBWCVersion3Mask;
        pBPSCapabilityInfo->UBWCLossySupport         = UBWCLossless;
        pBPSCapabilityInfo->ICAVersion               = ICAVersion20;
        pBPSCapabilityInfo->LDCSupport               = TRUE;
    }

    return result;
}

CAMX_NAMESPACE_END

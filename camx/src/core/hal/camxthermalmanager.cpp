////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file camxthermalmanager.cpp
/// @brief Implements thermal mitigation for camera
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "camxdebug.h"
#include "camxosutils.h"
#include "camxthermalmanager.h"
#include "camxtrace.h"
#include "camxutils.h"


CAMX_NAMESPACE_BEGIN

CHAR ThermalManager::s_clientName[] = "camera";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ThermalManager::ThermalManager
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ThermalManager::ThermalManager()
{
    // No need to explicitly set anything to NULL or zero since we're using CAMX_NEW which already zeroes out all
    // members during object creation
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ThermalManager::Initialize
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CamxResult ThermalManager::Initialize()
{
    CamxResult result = CamxResultEFailed;

    if (NULL == m_hThermalEngineLib)
    {
        CHAR libFilename[FILENAME_MAX];

        OsUtils::SNPrintF(libFilename, FILENAME_MAX, "%s%s%s.%s",
                          VendorLibPath, PathSeparator, "libthermalclient", SharedLibraryExtension);

        m_hThermalEngineLib = OsUtils::LibMap(libFilename);
    }

    if (NULL != m_hThermalEngineLib)
    {
        if (0 >= m_hThermalHandle)
        {
            CAMX_RegisterThermalFunc  pRegisterFunc = reinterpret_cast<CAMX_RegisterThermalFunc>(
               CamX::OsUtils::LibGetAddr(m_hThermalEngineLib, "thermal_client_register_callback"));

            if (NULL != pRegisterFunc)
            {
                // Register for camera callbacks
                m_hThermalHandle = pRegisterFunc(s_clientName, ThermalCallback, this);
                if (m_hThermalHandle < 0)
                {
                    CAMX_LOG_ERROR(CamxLogGroupHAL, "thermal_client_register_callback failed");
                    m_hThermalHandle = 0;
                }
                else
                {
                    CAMX_LOG_CONFIG(CamxLogGroupHAL, "Successfully registered with the Thermal Engine");
                    result = CamxResultSuccess;
                }
            }
            else
            {
                CAMX_LOG_ERROR(CamxLogGroupHAL, "Failed to get register function");
            }
        }
    }
    else
    {
        CAMX_LOG_ERROR(CamxLogGroupHAL, "Unable to load thermal lib");
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ThermalManager::RegisterHALDevice
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CamxResult ThermalManager::RegisterHALDevice(
    HALDevice* pHALDevice)
{
    CamxResult result = CamxResultEFailed;

    // Sometimes init fails at boot. So let's retry
    Initialize();

    if ((NULL != pHALDevice) && (0 < m_hThermalHandle))
    {
        // Only register if this HALDevice is not already in our list

        LDLLNode* pNode = m_HALDevices.FindByValue(pHALDevice);

        if (NULL == pNode)
        {
            if (CameraThermalLevel::ThermalLevelShutDown > m_currentLevel)
            {
                pNode = reinterpret_cast<LDLLNode*>(CAMX_CALLOC(sizeof(LDLLNode)));
                if (NULL != pNode)
                {
                    pNode->pData = pHALDevice;
                    m_HALDevices.InsertToTail(pNode);
                    CAMX_LOG_CONFIG(CamxLogGroupHAL, "Registered pHALDevice=%p CameraId=%u",
                                    pHALDevice, pHALDevice->GetCameraId());
                    result = CamxResultSuccess;

                }
                else
                {
                    result = CamxResultENoMemory;
                }
            }
            else
            {
                // Already in mitigation, force the device creation to fail
                result = CamxResultEResource;
            }
        }
        else
        {
            CAMX_LOG_VERBOSE(CamxLogGroupHAL, "pHALDevice=%p already registered");
            result = CamxResultSuccess;
        }
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ThermalManager::UnregisterHALDevice
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VOID ThermalManager::UnregisterHALDevice(
    HALDevice* pHALDevice)
{
    if (NULL != pHALDevice)
    {
        m_HALDevices.RemoveByValue(pHALDevice);
        CAMX_LOG_CONFIG(CamxLogGroupHAL, "Unregistered pHALDevice=%p CameraId=%u",
            pHALDevice, pHALDevice->GetCameraId());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ThermalManager::~ThermalManager
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ThermalManager::~ThermalManager()
{
    if (NULL != m_hThermalEngineLib)
    {
        if (0 != m_hThermalHandle)
        {
            CAMX_UnregisterThermalFunc  pUnregisterFunc = reinterpret_cast<CAMX_UnregisterThermalFunc>(
               CamX::OsUtils::LibGetAddr(m_hThermalEngineLib, "thermal_client_unregister_callback"));

            if (NULL != pUnregisterFunc)
            {
                pUnregisterFunc(m_hThermalHandle);
                m_hThermalHandle = 0;
            }
        }
        OsUtils::LibUnmap(m_hThermalEngineLib);
        m_hThermalEngineLib = NULL;
    }
    m_HALDevices.FreeAllNodes();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ThermalManager::ThermalCallback
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT ThermalManager::ThermalCallback(
    INT   level,
    VOID* pUserdata,
    VOID* pData)
{
    CAMX_UNREFERENCED_PARAM(pData);

    INT rc = -1;

    CAMX_LOG_INFO(CamxLogGroupHAL, "Thermal Level=%d", level);

    ThermalManager* pThermalManagerInstance = static_cast<ThermalManager*>(pUserdata);
    if (NULL != pThermalManagerInstance)
    {
        rc = pThermalManagerInstance->ThermalCallbackHandler(level);
    }
    else
    {
        CAMX_LOG_ERROR(CamxLogGroupHAL, "pThermalManagerInstance is NULL");
    }

    return rc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ThermalManager::ThermalCallbackHandler
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INT ThermalManager::ThermalCallbackHandler(
    INT level)
{
    m_currentLevel = static_cast<CameraThermalLevel>(level);
    if (CameraThermalLevel::ThermalLevelShutDown != level)
    {
        CAMX_LOG_VERBOSE(CamxLogGroupHAL, "Level=%d is not highest, returning without mitigation", level);
    }
    else
    {
        Camera3NotifyMessage camera_msg;

        CamX::Utils::Memset(&camera_msg, 0, sizeof(Camera3NotifyMessage));

        camera_msg.messageType                           = Camera3MessageType::MessageTypeError;
        camera_msg.message.errorMessage.errorMessageCode = Camera3ErrorMessageCode::MessageCodeDevice;

        LDLLNode* pNode = m_HALDevices.Head();

        while (NULL != pNode)
        {
            HALDevice* pHALDevice = reinterpret_cast<HALDevice*>(pNode->pData);
            if (NULL != pHALDevice)
            {
                CAMX_LOG_WARN(CamxLogGroupHAL, "ThermalLevel=%d is CRITICAL! Issuing Device error for CameraId=%u",
                              level, pHALDevice->GetCameraId());
                pHALDevice->NotifyMessage(pHALDevice, &camera_msg);
            }
            pNode = m_HALDevices.NextNode(pNode);
        }
    }

    return 0;
}

CAMX_NAMESPACE_END

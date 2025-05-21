//******************************************************************************************************************************
// Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//******************************************************************************************************************************
//==============================================================================================================================
// IMPLEMENTATION of ChiModule
//==============================================================================================================================

#include "chimodule.h"

namespace tests {

///@brief ChiModule singleton
ChiModule* ChiModule::m_pModuleInstance = nullptr;

/***************************************************************************************************************************
* ChiModule::GetInstance
*
* @brief
*     Gets the singleton instance for ChiModule
* @param
*     None
* @return
*     ChiModule singleton
***************************************************************************************************************************/
ChiModule* ChiModule::GetInstance()
{
    if (m_pModuleInstance == nullptr)
    {
        m_pModuleInstance = SAFE_NEW() ChiModule();
        if (m_pModuleInstance->Initialize() != CDKResultSuccess)
        {
            NT_LOG_ERROR("Failed to initialize ChiModule singleton!");
            return nullptr;
        }
    }

    return m_pModuleInstance;
}

/***************************************************************************************************************************
* ChiModule::DestroyInstance
*
* @brief
*     Destroy the singleton instance of the ChiModule class
* @param
*     None
* @return
*     void
***************************************************************************************************************************/
void ChiModule::DestroyInstance()
{
    if (m_pModuleInstance != nullptr)
    {
        delete m_pModuleInstance;
        m_pModuleInstance = nullptr;
    }
}

/***************************************************************************************************************************
* ChiModule::ChiModule
*
* @brief
*     Constructor for ChiModule
***************************************************************************************************************************/
ChiModule::ChiModule() :
    m_camList(),
    m_pCameraInfo(nullptr),
    m_pLegacyCameraInfo(nullptr),
    m_pSensorInfo(nullptr),
    m_numOfCameras(0),
    m_hContext(nullptr),
    m_vendortagOps{},
    m_fenceOps{},
    hLibrary(nullptr),
    m_chiOps{},
    m_vendoTagOps{},
    m_pCameraModule(nullptr)
{
}

/***************************************************************************************************************************
* ChiModule::~ChiModule
*
* @brief
*     Destructor for ChiModule
***************************************************************************************************************************/
ChiModule::~ChiModule()
{
    if (m_hContext)
    {
        if (CloseContext() != CDKResultSuccess)
        {
            NT_LOG_ERROR("Failed to close camera context!");
        }
    }

#ifndef _LINUX
    // free the library
    if (nullptr != hLibrary)
    {
        if (!FreeLibrary(static_cast<HMODULE>(hLibrary)))
        {
            NT_LOG_ERROR("Failed to free library handle");
        }
    }
#endif

    for (int currCamera = 0; currCamera < m_numOfCameras; currCamera++)
    {
        if (m_pSensorInfo[currCamera])
        {
            delete[] m_pSensorInfo[currCamera];
            m_pSensorInfo[currCamera] = nullptr;
        }
    }

    if (m_pLegacyCameraInfo)
    {
        delete[] m_pLegacyCameraInfo;
        m_pLegacyCameraInfo = nullptr;
    }

    if (m_pSensorInfo)
    {
        delete[] m_pSensorInfo;
        m_pSensorInfo = nullptr;
    }

    if (m_pCameraInfo)
    {
        delete[] m_pCameraInfo;
        m_pCameraInfo = nullptr;
    }
}

/***************************************************************************************************************************
* ChiModule::Initialize
*
* @brief
*     Initialize member variables using driver calls
* @param
*     None
* @return
*     CDKResult result code
***************************************************************************************************************************/
CDKResult ChiModule::Initialize()
{
    CDKResult result = CDKResultSuccess;

    result = LoadLibraries();
    if (result != CDKResultSuccess)
    {
        return result;
    }
    result = OpenContext();
    if (result != CDKResultSuccess)
    {
        return result;
    }

    m_numOfCameras = m_chiOps.pGetNumCameras(m_hContext);

    NT_LOG_INFO("Number of cameras reported by device: %d", m_numOfCameras);

    m_pCameraInfo = SAFE_NEW() CHICAMERAINFO[m_numOfCameras];
    m_pLegacyCameraInfo = SAFE_NEW() camera_info[m_numOfCameras];
    m_pSensorInfo = SAFE_NEW() CHISENSORMODEINFO*[m_numOfCameras];

    for (int currCamera = 0; currCamera < m_numOfCameras; currCamera++)
    {
        m_pCameraInfo[currCamera].pLegacy = &m_pLegacyCameraInfo[currCamera];

        m_chiOps.pGetCameraInfo(m_hContext, currCamera, &m_pCameraInfo[currCamera]);

        uint32_t numSensorModes = m_pCameraInfo[currCamera].numSensorModes;

        m_pSensorInfo[currCamera] = SAFE_NEW() CHISENSORMODEINFO[numSensorModes];

        m_chiOps.pEnumerateSensorModes(m_hContext, currCamera, numSensorModes, m_pSensorInfo[currCamera]);

        NT_LOG_DEBUG("Listing available sensor modes for camera %d...", currCamera)

        for (uint32_t sensorMode = 0; sensorMode < numSensorModes; sensorMode++)
        {
            NT_LOG_DEBUG("Camera %d sensormode %u: width %u, height %u, framerate %u, bpp %u",
                currCamera,
                sensorMode,
                m_pSensorInfo[currCamera][sensorMode].frameDimension.width,
                m_pSensorInfo[currCamera][sensorMode].frameDimension.height,
                m_pSensorInfo[currCamera][sensorMode].frameRate,
                m_pSensorInfo[currCamera][sensorMode].bpp,
                m_pSensorInfo[currCamera][sensorMode].sensorModeCaps.u.Normal,
                m_pSensorInfo[currCamera][sensorMode].sensorModeCaps.u.PDAF);
        }
    }

    // Check if --camera flag set
    uint32_t testCameraID = CmdLineParser::GetCamera();
    // If camera ID within range, add to test list
    if (testCameraID >= 0 && testCameraID < static_cast<uint32_t>(m_numOfCameras))
    {
        m_camList.push_back(testCameraID);
    }
    else // Else add all available cameras for test
    {
        for (uint32_t currCamera = 0; currCamera < static_cast<uint32_t>(m_numOfCameras); currCamera++)
        {
            m_camList.push_back(currCamera);
        }
    }

    return result;
}

/***************************************************************************************************************************
* ChiModule::LoadLibraries
*
* @brief
*     Load chi and vendor tag operation libraries
* @param
*     None
* @return
*     CDKResult result code
***************************************************************************************************************************/
CDKResult ChiModule::LoadLibraries()
{
    PFNCHIENTRY pChiHalOpen;

#ifdef _LINUX
    hLibrary = dlopen(m_libPath, RTLD_NOW);
    if (hLibrary == NULL)
    {
        NT_LOG_ERROR( "Failed to load android library");
        return CDKResultEUnableToLoad;
    }
    pChiHalOpen = reinterpret_cast<PFNCHIENTRY>(dlsym(hLibrary, "ChiEntry"));
    if (pChiHalOpen == NULL)
    {
        NT_LOG_ERROR( "ChiEntry missing in library");
        return CDKResultEUnableToLoad;
    }
    m_pCameraModule = reinterpret_cast<camera_module_t*>(dlsym(hLibrary, "HMI"));
    if (m_pCameraModule == NULL)
    {
        NT_LOG_ERROR( "CameraModule missing in library");
        return CDKResultEUnableToLoad;
    }
#else
    hLibrary = LoadLibrary("hal.dll");
    if (hLibrary == NULL)
    {
        NT_LOG_ERROR("Failed to load hal library");
        return CDKResultEUnableToLoad;
    }
    void *hmi = GetProcAddress(static_cast<HMODULE>(hLibrary), "ChiEntry");
    pChiHalOpen = reinterpret_cast<PFNCHIENTRY>(hmi);
    if (pChiHalOpen == NULL)
    {
        NT_LOG_ERROR("ChiEntry missing in library");
        return CDKResultEUnableToLoad;
    }
    hmi = GetProcAddress(static_cast<HMODULE>(hLibrary), "HMI");
    m_pCameraModule = reinterpret_cast<camera_module_t*>(hmi);
    if (m_pCameraModule == NULL)
    {
        NT_LOG_ERROR("CameraModule missing in library");
        return CDKResultEUnableToLoad;
    }
#endif // _LINUX

    (*pChiHalOpen)(&m_chiOps);

    m_pCameraModule->get_vendor_tag_ops(&m_vendoTagOps);
        int ret = set_camera_metadata_vendor_ops(const_cast<vendor_tag_ops_t*>(&m_vendoTagOps));
    if (ret != 0)
    {
        NT_LOG_ERROR("Failed to set vendor tag ops");
        return CDKResultEFailed;
        }

    return CDKResultSuccess;
}

/***************************************************************************************************************************
* ChiModule::OpenContext
*
* @brief
*     Opens a camera context
* @param
*     None
* @return
*     CDKResult result code
***************************************************************************************************************************/
CDKResult ChiModule::OpenContext()
{
    UINT32 majorVersion = m_chiOps.majorVersion;
    UINT32 minorVersion = m_chiOps.minorVersion;
    UINT32 subVersion = m_chiOps.subVersion;

    NT_LOG_INFO("Opening chi context");
    m_hContext = m_chiOps.pOpenContext();
    m_chiOps.pTagOps(&m_vendortagOps);
    m_chiOps.pGetFenceOps(&m_fenceOps);
    if (m_hContext == nullptr)
    {
        NT_LOG_ERROR("Open context failed!");
        return CDKResultEFailed;
    }
    return CDKResultSuccess;
}

/***************************************************************************************************************************
* ChiModule::CloseContext
*
* @brief
*     Close camera context
* @param
*     None
* @return
*     CDKResult result code
***************************************************************************************************************************/
CDKResult ChiModule::CloseContext()
{
    CDKResult result = CDKResultSuccess;

    NT_LOG_INFO("Closing Context: %p", m_hContext);
    if (m_hContext != nullptr)
    {
        m_chiOps.pCloseContext(m_hContext);
        m_hContext = nullptr;
    }
    else
    {
        NT_LOG_ERROR("Requested context %p is not open", m_hContext);
        result = CDKResultEInvalidState;
    }
    return result;
}

/***************************************************************************************************************************
* ChiModule::GetNumCams
*
* @brief
*     Gets number of cameras reported by the driver
* @param
*     None
* @return
*     int number of cameras reported by the module
***************************************************************************************************************************/
int ChiModule::GetNumberCameras() const
{
    return m_numOfCameras;
}

/***************************************************************************************************************************
* ChiModule::GetCameraList
*
* @brief
*     Gets list of cameras reported by the driver
* @param
*     None
* @return
*     int number of cameras reported by the module
***************************************************************************************************************************/
std::vector <int> ChiModule::GetCameraList() const
{
    return m_camList;
}

/***************************************************************************************************************************
* ChiModule::GetCameraInfo
*
* @brief
*     Gets camera info for given camera Id
* @param
*     [in]  uint32_t   cameraId    cameraid associated
* @return
*     CHICAMERAINFO* camerainfo for given camera Id
***************************************************************************************************************************/
const CHICAMERAINFO* ChiModule::GetCameraInfo(uint32_t cameraId) const
{
    const CHICAMERAINFO* pCameraInfo = nullptr;
    if ((m_pCameraInfo != nullptr) && (&m_pCameraInfo[cameraId] != nullptr))
    {
        pCameraInfo = &m_pCameraInfo[cameraId];
    }

    return pCameraInfo;
}

/***************************************************************************************************************************
* ChiModule::GetCameraSensorModeInfo
*
* @brief
*     Gets sensormode for given index
* @param
*     [in] uint32_t cameraId id of the camera
*     [in] uint32_t modeId   index of the mode to use
* @return
*     CHISENSORMODEINFO for given cameraId and index
****************************************************************************************************************************/
CHISENSORMODEINFO* ChiModule::GetCameraSensorModeInfo(uint32_t cameraId, uint32_t modeId) const
{
    CHISENSORMODEINFO* pSensorModeInfo = nullptr;
    if ((m_pSensorInfo != nullptr) && (&m_pSensorInfo[cameraId] != nullptr))
    {
        pSensorModeInfo = &m_pSensorInfo[cameraId][modeId];
    }
    return pSensorModeInfo;
}

    /***************************************************************************************************************************
    * ChiModule::GetClosestSensorMode
    *
    * @brief
    *     Chooses a sensormode closest to given resolution
    * @param
    *     [in] uint32_t cameraId id of the camera
    *     [in] Size res          resolution used
    * @return
    *     CHISENSORMODEINFO for given resolution which is closest
    ****************************************************************************************************************************/
    CHISENSORMODEINFO* ChiModule::GetClosestSensorMode(uint32_t cameraId, Size resolution) const
    {
        if((nullptr == m_pSensorInfo) || (nullptr == &m_pSensorInfo[cameraId])) {
            NT_LOG_ERROR("Sensor information for camera %u is not available", cameraId);
            return nullptr;
        }
        else
        {
            uint32_t index = 0; // select sensor mode 0 by default
            CHISENSORMODEINFO* pSensorModeInfo = m_pSensorInfo[cameraId];


            // check if sensor mode overriden at run time and is within available range for current camera
            uint32_t overrideSensorMode = static_cast<uint32_t>(CmdLineParser::GetSensorMode());

            if ((overrideSensorMode != static_cast<uint32_t>(-1)) && (overrideSensorMode < m_pCameraInfo[cameraId].numSensorModes))
            {
                NT_LOG_WARN("Overriding sensor mode from %u to %d for camera %u.", index, CmdLineParser::GetSensorMode(), cameraId);
                index = overrideSensorMode;
            }
            // pick best matching sensor mode if not overriden at run time
            else
            {
                bool hasNormalMode = false;
                std::vector<SensorMode> sensorModePDAFList;
                std::vector<SensorMode> sensorModeNormalList;
                for (uint32_t mode = 0; mode < m_pCameraInfo[cameraId].numSensorModes; mode++)
                {
                    if (pSensorModeInfo[mode].sensorModeCaps.u.Normal == 1)
                    {
                        hasNormalMode = true;
                        if (pSensorModeInfo[mode].sensorModeCaps.u.PDAF == 1) //Check PDAF bit for AF/stats usage
                        {
                            sensorModePDAFList.push_back({ mode,
                                    pSensorModeInfo[mode].frameDimension.width,
                                    pSensorModeInfo[mode].frameDimension.height });
                            NT_LOG_DEBUG("Select from CameraID[%d] Sensor[PDAF] Mode[%d] %d x %d",
                                cameraId,
                                mode,
                                pSensorModeInfo[mode].frameDimension.width,
                                pSensorModeInfo[mode].frameDimension.height);
                        }
                        else
                        {
                            sensorModeNormalList.push_back({ mode,
                                    pSensorModeInfo[mode].frameDimension.width,
                                    pSensorModeInfo[mode].frameDimension.height });
                            NT_LOG_DEBUG("Select from CameraID[%d] Sensor[Normal] Mode[%d] %d x %d",
                                cameraId,
                                mode,
                                pSensorModeInfo[mode].frameDimension.width,
                                pSensorModeInfo[mode].frameDimension.height);
                        }
                    }
                }
                if (!hasNormalMode)
                {
                    NT_LOG_ERROR("Normal bit is not set for any sensor mode for Camera %d!", cameraId);
                    index = 0; // select sensor mode 0 if normal mode not found
                }
                std::vector<SensorMode> sensorModeList = sensorModePDAFList.empty() == true ? sensorModeNormalList : sensorModePDAFList;
                sort(sensorModeList.begin(), sensorModeList.end(),
                    [](const SensorMode& lhs, const SensorMode& rhs)
                    {
                        return lhs.height < rhs.height;
                    });
                while (!sensorModeList.empty())
                {
                    SensorMode sensorMode = sensorModeList.back();
                    sensorModeList.pop_back();
                    if (resolution.width <= sensorMode.width && resolution.height <= sensorMode.height)
                    {
                        index = sensorMode.mode;
                    }
                }
            }
            return &pSensorModeInfo[index];
        }
    }

/***************************************************************************************************************************
*   ChiModule::SubmitPipelineRequest
*
*   @brief
*       Submit the pipeline request (capture)
*   @param
*     [in]  CHIPIPELINEREQUEST            pRequest       pointer to the capture request
*   @return
*       CDKResult result code
****************************************************************************************************************************/
CDKResult ChiModule::SubmitPipelineRequest(CHIPIPELINEREQUEST * pRequest) const
{
    for (uint32_t requestCount = 0; requestCount < pRequest->numRequests; requestCount++)
    {
        uint64_t frameNum = pRequest->pCaptureRequests[requestCount].frameNumber;
        NT_LOG_DEBUG("Sending pipeline request for frame number: %" PRIu64, frameNum);
    }

    return m_chiOps.pSubmitPipelineRequest(m_hContext, pRequest);
}

/***************************************************************************************************************************
* ChiModule::GetContext
*
* @brief
*     Gets the camera context
* @param
*     None
* @return
*     CHIHANDLE  camera context
***************************************************************************************************************************/
CHIHANDLE ChiModule::GetContext() const
{
    return m_hContext;
}

/***************************************************************************************************************************
* ChiModule::GetChiOps
*
* @brief
*     Gets pointer to ChiOps
* @param
*     None
* @return
*     CHICONTEXTOPS*  pointer to chi APIs
***************************************************************************************************************************/
const CHICONTEXTOPS* ChiModule::GetChiOps() const
{
    return &m_chiOps;
}

/***************************************************************************************************************************
* ChiModule::GetFenceOps
*
* @brief
*     Gets pointer to fenceOps
* @param
*     None
* @return
*     CHIFENCEOPS*  pointer to chi fence APIs
***************************************************************************************************************************/
const CHIFENCEOPS* ChiModule::GetFenceOps() const
{
    return &m_fenceOps;
}

} //namespace tests

/***************************************************************************************************************************
* ChiModule::GetLibrary
*
* @brief
*     Gets symbols loaded through the dll/.so
* @param
*     None
* @return
*     VOID* Function pointer to library loaded
***************************************************************************************************************************/
VOID* tests::ChiModule::GetLibrary() const
{
    return hLibrary;
}

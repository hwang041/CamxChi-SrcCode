//*************************************************************************************************
// Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*************************************************************************************************

#ifndef __CHI_MODULE__
#define __CHI_MODULE__

#include "nchicommon.h"

//TODO: Remove this once chi.h has this typedef
typedef VOID(*PFNCHIENTRY)(CHICONTEXTOPS* pContextOps);

namespace tests {

class ChiModule
{
public:

    static ChiModule*       GetInstance();
    static void             DestroyInstance();
    int                     GetNumberCameras() const;
    const CHICAMERAINFO*    GetCameraInfo(uint32_t cameraId) const;
    CHISENSORMODEINFO*      GetCameraSensorModeInfo(uint32_t cameraId, uint32_t modeId) const;
    CHISENSORMODEINFO *     GetClosestSensorMode(uint32_t cameraId, Size resolution) const;
    CDKResult               SubmitPipelineRequest(CHIPIPELINEREQUEST* pRequest) const;
    CHIHANDLE               GetContext() const;
    const CHICONTEXTOPS*    GetChiOps() const;
    const CHIFENCEOPS*      GetFenceOps() const;
    VOID*                   GetLibrary() const;
    std::vector <int>       GetCameraList() const;

    CHITAGSOPS GetTagOps()
    {
        return m_vendortagOps;
    }

    camera_info* GetLegacyCameraInfo(uint32_t cameraId) const
    {
        return &m_pLegacyCameraInfo[cameraId];
    }

    private:
        std::vector <int>   m_camList;              // list of cameras to test
        static ChiModule*   m_pModuleInstance;      // Singleton instance of ChiModule
        CHICAMERAINFO*      m_pCameraInfo;          // pointer to camera info
        camera_info*        m_pLegacyCameraInfo;    // pointer to legacy camera info
        CHISENSORMODEINFO** m_pSensorInfo;          // pointer to sensor mode info
        int                 m_numOfCameras;         // number of cameras present
        CHIHANDLE           m_hContext;             // Handle to the context
        CHITAGSOPS          m_vendortagOps;         // vendor tag related functions
        CHIFENCEOPS         m_fenceOps;             // chi fence operations

    void*               hLibrary;               // pointer to the loaded driver dll/.so library
    CHICONTEXTOPS       m_chiOps;               // function pointers to all chi related APIs
    vendor_tag_ops_t    m_vendoTagOps;          // function pointers for finding/enumerating vendor tags
    camera_module_t*    m_pCameraModule;        // pointer to camera module functions

#ifdef ENVIRONMENT64
    const char*         m_libPath = "/vendor/lib64/hw/camera.qcom.so";
#else
    const char*         m_libPath = "/vendor/lib/hw/camera.qcom.so";
#endif
        struct SensorMode
        {
            uint32_t mode;
            uint32_t width;
            uint32_t height;

            SensorMode(uint32_t mode, uint32_t width, uint32_t height)
            {
                this->mode   = mode;
                this->width  = width;
                this->height = height;
            }
        };

    CDKResult           Initialize();
    CDKResult           LoadLibraries();
    CDKResult           OpenContext();
    CDKResult           CloseContext();

    ChiModule();
    ~ChiModule();
    /// Do not allow the copy constructor or assignment operator
    ChiModule(const ChiModule&) = delete;
    ChiModule& operator= (const ChiModule&) = delete;

};

} //namespace tests

#endif  //#ifndef __CHI_MODULE__

//******************************************************************************
// Copyright (c) 2017 - 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*******************************************************************************

#include "camera_manager_test.h"

namespace tests
{
    /**************************************************************************************************
    *   CameramanagerTest::Setup
    *
    *   @brief
    *       Entry point to the test
    **************************************************************************************************/
    void CameraManagerTest::Setup()
    {
        m_pChiModule = ChiModule::GetInstance();
    }

    /**************************************************************************************************
    *   CameramanagerTest::Teardown
    *
    *   @brief
    *       Teardown point to the test
    **************************************************************************************************/
    void CameraManagerTest::Teardown()
    {
       m_pChiModule->DestroyInstance();
    }

    /**************************************************************************************************
    *   CameramanagerTest::TestOpenInvalidCamera
    *
    *   @brief
    *       Negative test to expect opening camera with invalid ID
    **************************************************************************************************/
    void CameraManagerTest::TestOpenInvalidCamera()
    {
        NT_ASSERT(nullptr != m_pChiModule->GetContext(),
             "Camera open() is unimplemented");
        int invalidId = -1;
        const CHIHANDLE hContext = m_pChiModule->GetContext();
        CHICAMERAINFO info;
        NT_ASSERT(0 != m_pChiModule->GetChiOps()->pGetCameraInfo(hContext, invalidId, &info),
             "Shouldn't get camera info for camera id -1");
    }

    /**************************************************************************************************
    *   CameramanagerTest::TestOpenCamerasSerially
    *
    *   @brief
    *       Tests that each camera device can be opened one at a time, several times.
    **************************************************************************************************/
    void CameraManagerTest::TestOpenCloseContextSerially()
    {
        int numOfCameras = m_pChiModule->GetNumberCameras();
        NT_ASSERT(0 < numOfCameras, "No cameras found");

        for (int i = 0; i < numOfCameras; i++)
        {
            for (int j = 0; j < NUM_CAMERA_REOPENS; j++)
            {
                CHIHANDLE hContext = m_pChiModule->GetChiOps()->pOpenContext();
                m_pChiModule->GetChiOps()->pCloseContext(hContext);
            }

        }
    }
}
//******************************************************************************
// Copyright (c) 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*******************************************************************************

#ifndef __CHI_BUFFER_MANAGER__
#define __CHI_BUFFER_MANAGER__

#include "buffermanager.h"
#include "chimodule.h"
#include "nativetestlog.h"

namespace tests
{
class ChiBufferManager : public BufferManager
{

public:

    ChiBufferManager(StreamUsecases streamId) : BufferManager(streamId)
    {
        m_pChiModule = ChiModule::GetInstance();
    }
    ~ChiBufferManager() {};

    int GetStatusFromBuffer(GenericBuffer* buffer);

private:

    ChiModule* m_pChiModule;

    int GenerateOutputBuffer(GenericBuffer* buffer, GenericStream* stream);
    int GenerateInputBuffer(GenericBuffer* buffer, GenericStream* stream, const char* filename);
    int SaveImageToFile(GenericBuffer* resultbuffer, std::string filename);

    /* Buffer Allocation Helpers */
    GenericBuffer* CreateGenericBuffer();
    void DestroyGenericBuffer(GenericBuffer* buffer);

    /* Fence Helpers */
    CHIFENCEINFO CreateFence(bool isValid = true);
    void DestroyFence(CHIFENCEINFO fenceInfo);

    /* Stream Getters */
    int GetTypeFromStream(GenericStream* stream);
    uint32_t GetMaxBuffersFromStream(GenericStream* stream);

    /* Buffer Getters */
    void* GetNativeBufferFromGeneric(GenericBuffer* buffer);
    NativeChiBufferHandle GetHandleFromBuffer(GenericBuffer* buffer);
    int GetReleaseFenceFromBuffer(GenericBuffer* buffer);
    void SetAcquireFenceInBuffer(GenericBuffer* buffer, int setVal);
    uint32_t GetMaxBuffersFromBuffer(GenericBuffer* buffer);

    /// Do not allow the copy constructor or assignment operator
    ChiBufferManager(const BufferManager&) = delete;
    ChiBufferManager& operator= (const BufferManager&) = delete;
};
}

#endif //__CHI_BUFFER_MANAGER__

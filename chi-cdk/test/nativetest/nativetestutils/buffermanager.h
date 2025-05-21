//******************************************************************************
// Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*******************************************************************************

#ifndef __BUFFER_MANAGER__
#define __BUFFER_MANAGER__

#include <queue>

#include "camxpresilmem.h"
#include "camera3stream.h"
#include "commonutils.h"
#include "chi.h"
#include "chxutils.h"

namespace tests
{
class BufferManager
{

public:

    typedef camera3_stream_t        NativeHalStream;
    typedef camera3_stream_buffer_t NativeHalBuffer;
    typedef CHISTREAM               NativeChiStream;
    typedef CHISTREAMBUFFER         NativeChiBuffer;
    typedef CHIBUFFERHANDLE         NativeChiBufferHandle;

    struct GenericStream
    {
        union
        {
            NativeHalStream* halStream;
            NativeChiStream* chiStream;
        };
        GenericStream() {};
        GenericStream(NativeHalStream* stream) : halStream(stream) {};
        GenericStream(NativeChiStream* stream) : chiStream(stream) {};
    };

    struct GenericBuffer
    {
        union
        {
            NativeHalBuffer* halBuffer;
            NativeChiBuffer* chiBuffer;
        };
        GenericBuffer() {};
        GenericBuffer(NativeHalBuffer* buffer) : halBuffer(buffer) {};
        GenericBuffer(NativeChiBuffer* buffer) : chiBuffer(buffer) {};
    };

    static int LoadBufferLibs(void* pLib);
    BufferManager* Initialize(
        int cameraId,
        GenericStream* configuredStream,
        StreamUsecases streamId,
        const char* filename);
    void* GetOutputBufferForRequest();
    void* GetInputBufferForRequest();

    virtual int   ProcessBufferFromResult(const int frameNumber, GenericBuffer* resultBuffer, bool dump);
    virtual void  DestroyBuffers();

    virtual int GetStatusFromBuffer(GenericBuffer* buffer) = 0;

protected:

#ifdef _LINUX
    std::map<native_handle_t*, sp<GraphicBuffer>> m_GBmap;
#endif

    static CamxMemAllocFunc        m_pCamxMemAlloc;
    static CamxMemReleaseFunc      m_pCamxMemRelease;
    static CamxMemGetImageSizeFunc m_pCamxMemGetImageSize;

    int GenerateBuffers(int cameraId, GenericStream* configuredStream, StreamUsecases streamId, const char* filename);

    BufferManager(StreamUsecases streamId);
    virtual ~BufferManager();

private:

    std::deque<GenericBuffer*>*  m_inputImageQueue;
    std::queue<GenericBuffer*>*  m_emptyQueue;
    std::queue<GenericBuffer*>*  m_filledQueue;

    Mutex*              m_pQueueMutex;
    Condition*          m_pQueueCond;
    bool                m_bBufferAvailable;
    std::string         m_OutFileName;
    int                 m_streamType;

    virtual int GenerateOutputBuffer(GenericBuffer* buffer, GenericStream* stream) = 0;
    virtual int GenerateInputBuffer(GenericBuffer* buffer, GenericStream* stream, const char* filename) = 0;
    virtual int SaveImageToFile(GenericBuffer* resultbuffer, std::string filename) = 0;

    /* Buffer Allocation Helpers */
    virtual GenericBuffer* CreateGenericBuffer() = 0;
    virtual void DestroyGenericBuffer(GenericBuffer* buffer) = 0;

    /* Stream Getters */
    virtual int GetTypeFromStream(GenericStream* stream) = 0;
    virtual uint32_t GetMaxBuffersFromStream(GenericStream* stream) = 0;

    /* Buffer Getters */
    virtual void* GetNativeBufferFromGeneric(GenericBuffer* buffer) = 0;
    virtual NativeChiBufferHandle GetHandleFromBuffer(GenericBuffer* buffer) = 0;
    virtual int GetReleaseFenceFromBuffer(GenericBuffer* buffer) = 0;
    virtual void SetAcquireFenceInBuffer(GenericBuffer* buffer, int setVal) = 0;
    virtual uint32_t GetMaxBuffersFromBuffer(GenericBuffer* buffer) = 0;

    /// Do not allow the copy constructor or assignment operator
    BufferManager(const BufferManager&) = delete;
    BufferManager& operator= (const BufferManager&) = delete;
};
}

#endif //__BUFFER_MANAGER__

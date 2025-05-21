//******************************************************************************
// Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*******************************************************************************

#include "buffermanager.h"

namespace tests
{
CamxMemAllocFunc        BufferManager::m_pCamxMemAlloc;
CamxMemReleaseFunc      BufferManager::m_pCamxMemRelease;
CamxMemGetImageSizeFunc BufferManager::m_pCamxMemGetImageSize;

BufferManager::BufferManager(StreamUsecases streamId) :
    m_inputImageQueue(nullptr),
    m_emptyQueue(nullptr),
    m_filledQueue(nullptr),
    m_bBufferAvailable(false),
    m_OutFileName(""),
    m_streamType(-1)
{
    // Initialize mutex and condition member variables
    m_pQueueMutex = Mutex::Create((mapStreamStr[streamId]).c_str());
    m_pQueueCond = Condition::Create((mapStreamStr[streamId]).c_str());
}

BufferManager::~BufferManager()
{
    m_inputImageQueue = nullptr;
    m_emptyQueue = nullptr;
    m_filledQueue = nullptr;
    m_bBufferAvailable = false;
    m_OutFileName = "";
    m_streamType = -1;

    // Destroy mutex and condition member variables
    if (nullptr != m_pQueueMutex)
    {
        m_pQueueMutex->Destroy();
        m_pQueueMutex = nullptr;
    }
    if (nullptr != m_pQueueCond)
    {
        m_pQueueCond->Destroy();
        m_pQueueCond = nullptr;
    }
}

/*******************************************************************************************************************************
*   BufferManager::LoadBufferLibs
*
*   @brief
*       Initialize the function pointers from the library
*   @return
*       0 on success or -1 on failure
*******************************************************************************************************************************/
int BufferManager::LoadBufferLibs(
    void* pLib) //[in] library to be loaded
{
    // CamxMemGetImageSizeFunc available on both Android and Windows
    m_pCamxMemGetImageSize = reinterpret_cast<CamxMemGetImageSizeFunc>(ChxUtils::LibGetAddr(pLib, "CamxMemGetImageSize"));
    if (m_pCamxMemGetImageSize == NULL)
    {
        NT_LOG_ERROR("CamxMemGetImageSize not available in the library");
        return -1;
    }

#ifndef _LINUX
    // CamxMemAllocFunc and CamxMemReleaseFunc not available on Android
    m_pCamxMemAlloc = reinterpret_cast<CamxMemAllocFunc>(ChxUtils::LibGetAddr(pLib, "CamxMemAlloc"));
    if (nullptr == m_pCamxMemAlloc)
    {
        NT_LOG_ERROR("CamxMemAllocFunc not available in the library");
        return -1;
    }

    m_pCamxMemRelease = reinterpret_cast<CamxMemReleaseFunc>(ChxUtils::LibGetAddr(pLib, "CamxMemRelease"));
    if (nullptr == m_pCamxMemRelease)
    {
        NT_LOG_ERROR("CamxMemRelease not available in the library");
        return -1;
    }
#endif // _LINUX
    return 0;
}

/**************************************************************************************************************************
*   BufferManager::Initialize
*
*   @brief
*       Initialize new instance of BufferManager
*   @return
*       Pointer to initialized BufferManager object or nullptr on failure
**************************************************************************************************************************/
BufferManager* BufferManager::Initialize(
    int cameraId,                       //[in] camera Id for generating buffers
    GenericStream* configuredStream,    //[in] streams to for generating buffers
    StreamUsecases streamId,            //[in] stream Id for generating buffers
    const char* filename)               //[in] filename for generating buffers

{
    int result = GenerateBuffers(cameraId, configuredStream, streamId, filename);

    if (result != 0)
    {
        DestroyBuffers();
        return nullptr;
    }

    return this;
}

/**************************************************************************************************************************
*   BufferManager::GenerateBuffers
*
*   @brief
*       Generates output buffers for given stream
*   @return
*       0 on success or -1 on failure
**************************************************************************************************************************/
int BufferManager::GenerateBuffers(
    int cameraId,                       //[in] camera Id for the filename
    GenericStream* configuredStream,    //[in] configured stream for a given session
    StreamUsecases streamId,            //[in] stream Id for stream
    const char* filename)               //[in] filename for input stream to be read
{
    if (configuredStream == nullptr)
    {
        NT_LOG_ERROR( "Cannot create buffers for NULL stream");
        return -1;
    }

    m_streamType = GetTypeFromStream(configuredStream);
    if (m_streamType == CAMERA3_STREAM_INPUT)
    {
        m_inputImageQueue = SAFE_NEW() std::deque<GenericBuffer*>();
    }
    else if (m_streamType == CAMERA3_STREAM_BIDIRECTIONAL)
    {
        m_inputImageQueue = SAFE_NEW() std::deque<GenericBuffer*>();
        m_emptyQueue = SAFE_NEW() std::queue<GenericBuffer*>();
        m_filledQueue = SAFE_NEW() std::queue<GenericBuffer*>();
    }
    else
    {
        m_emptyQueue = SAFE_NEW() std::queue<GenericBuffer*>();
        m_filledQueue = SAFE_NEW() std::queue<GenericBuffer*>();
    }

    m_OutFileName = ConstructOutputFileName(cameraId).append(mapStreamStr[streamId]);

    uint32_t maxBuffers = GetMaxBuffersFromStream(configuredStream);
    if (0 == maxBuffers)
    {
        NT_LOG_ERROR( "Stream %d cannot have maxBuffers of 0!", streamId);
        return -1;
    }

    for (uint32_t bufferIndex = 0; bufferIndex < maxBuffers; bufferIndex++)
    {
        GenericBuffer* streamBuffer = CreateGenericBuffer();
        if (streamBuffer == nullptr)
        {
            return -1;
        }

        if (m_streamType == CAMERA3_STREAM_INPUT)
        {
            if (0 != GenerateInputBuffer(streamBuffer, configuredStream, filename))
            {
                return -1;
            }
            m_inputImageQueue->push_back(streamBuffer);
        }
        else
        {
            if (0 != GenerateOutputBuffer(streamBuffer, configuredStream))
            {
                return -1;
            }
            m_emptyQueue->push(streamBuffer);
        }
    }

    return 0;
}

/**************************************************************************************************************************
*   BufferManager::GetOutputBufferForRequest
*
*   @brief
*       Provides void pointer to a native buffer for a process capture request
*   @return
*       Valid void pointer on success, nullptr on failure
**************************************************************************************************************************/
void* BufferManager::GetOutputBufferForRequest()
{
    m_pQueueMutex->Lock();

    GenericBuffer* pBuffer = !m_emptyQueue->empty() ? m_emptyQueue->front() : nullptr;
    int retries = 0;
    int bufferCount = 0;
    int statusCode = 0;
    int timeout = CmdLineParser::GetTimeoutOverride();

    while (nullptr == pBuffer && bufferCount < TIMEOUT_RETRIES)
    {
        while (false == m_bBufferAvailable && retries < TIMEOUT_RETRIES)
        {
            m_pQueueCond->TimedWait(m_pQueueMutex->GetNativeHandle(), timeout);
            retries++;
        }

        if (m_bBufferAvailable == false)
        {
            NT_LOG_ERROR( "There is no buffer available to serve next request");
            statusCode = -1;
            break;
        }
        m_bBufferAvailable = false;
        pBuffer = !m_emptyQueue->empty() ? m_emptyQueue->front() : nullptr;
        bufferCount++;
    }

    if (pBuffer == nullptr && bufferCount >= TIMEOUT_RETRIES)
    {
        NT_LOG_ERROR( "All buffers in queue are NULL");
        statusCode = -1;
    }

    if (statusCode == 0)
    {
        m_emptyQueue->pop();
        m_filledQueue->push(pBuffer);
    }

    m_pQueueMutex->Unlock();
    return (statusCode == 0 && pBuffer != nullptr) ? GetNativeBufferFromGeneric(pBuffer) : nullptr;
}

/**************************************************************************************************************************
*   BufferManager::GetInputBufferForRequest
*
*   @brief
*       Provides void pointer to a native buffer for a process capture request
*   @return
*       Valid pointer on success, nullptr on failure
**************************************************************************************************************************/
void* BufferManager::GetInputBufferForRequest()
{
    m_pQueueMutex->Lock();
    GenericBuffer* pBuffer = nullptr;
    int retries = 0;
    int statusCode = 0;
    int timeout = CmdLineParser::GetTimeoutOverride();

    while (m_inputImageQueue->empty() && retries < TIMEOUT_RETRIES)
    {
        while (!m_bBufferAvailable && retries < TIMEOUT_RETRIES)
        {
            m_pQueueCond->TimedWait(m_pQueueMutex->GetNativeHandle(), timeout);
            retries++;
        }
        if (m_streamType == CAMERA3_STREAM_BIDIRECTIONAL)
        {
            m_bBufferAvailable = false;
        }
    }

    if (!m_inputImageQueue->empty())
    {
        pBuffer = m_inputImageQueue->front();
        retries = 0;
    }
    while (NULL == pBuffer && retries < TIMEOUT_RETRIES)
    {
        if (m_streamType == CAMERA3_STREAM_BIDIRECTIONAL)
        {
            while (!m_bBufferAvailable && retries < TIMEOUT_RETRIES)
            {
                m_pQueueCond->TimedWait(m_pQueueMutex->GetNativeHandle(), timeout);
                retries++;
            }
            m_bBufferAvailable = false;
        }
        else // m_streamType == CAMERA3_STREAM_INPUT
        {
            if (!m_inputImageQueue->empty())
            {
                m_inputImageQueue->pop_front();
            }
            m_inputImageQueue->push_back(pBuffer);
        }

        pBuffer = !m_inputImageQueue->empty() ? m_inputImageQueue->front() : nullptr;
        retries++;
    }

    if (nullptr == pBuffer && retries >= TIMEOUT_RETRIES)
    {
        NT_LOG_ERROR( "All buffers in queue are NULL");
        statusCode = -1;
    }

    if (NULL != pBuffer)
    {
        if (!m_inputImageQueue->empty())
        {
            m_inputImageQueue->pop_front();
        }
        m_inputImageQueue->push_back(pBuffer);
    }

    m_pQueueMutex->Unlock();
    return (statusCode == 0 && pBuffer != nullptr) ? GetNativeBufferFromGeneric(pBuffer) : nullptr;
}

/**************************************************************************************************************************
*   BufferManager::ProcessBufferFromResult
*
*   @brief
*       Process the image buffer obtained from result
*   @return
*       0 on success or -1 on failure
**************************************************************************************************************************/
int BufferManager::ProcessBufferFromResult(
    const int frameNumber,          //[in] frame number of result
    GenericBuffer* resultBuffer,    //[in] result buffer to process
    bool dump)                      //[in] should image be dumped
{
    int result;

    if (nullptr != m_filledQueue)
    {
        m_pQueueMutex->Lock();

        result = 0;

        GenericBuffer* pQueuedStreamBuffer = static_cast<GenericBuffer*>(m_filledQueue->front());

        if (pQueuedStreamBuffer == nullptr)
        {
            NT_LOG_ERROR( "Filled Queue has a NULL buffer");
            m_pQueueMutex->Unlock();
            return -1;
        }

        m_filledQueue->pop();

        if (GetHandleFromBuffer(pQueuedStreamBuffer) == GetHandleFromBuffer(resultBuffer))
        {
            if (CAMERA3_BUFFER_STATUS_OK == GetStatusFromBuffer(resultBuffer))
            {
                if (GetReleaseFenceFromBuffer(resultBuffer) == -1)
                {
                    if (CmdLineParser::NoImageDump())
                    {
                        NT_LOG_WARN( "Result image dump is disabled, skipping...");
                    }
                    else if (dump)
                    {
                        std::ostringstream outputName;
                        outputName << m_OutFileName;
                        if (frameNumber != -1)
                        {
                            outputName << "_Frame" << frameNumber;
                        }

                        result = SaveImageToFile(resultBuffer, outputName.str());
                    }

                    if (m_streamType == CAMERA3_STREAM_BIDIRECTIONAL)
                    {
                        if (m_inputImageQueue != nullptr)
                        {
                            if (m_inputImageQueue->size() == GetMaxBuffersFromBuffer(resultBuffer))
                            {
                                m_inputImageQueue->pop_back();
                            }

                            m_inputImageQueue->push_front(pQueuedStreamBuffer);
                        }
                        else
                        {
                            NT_LOG_ERROR( "inputImage Queue is NULL");
                            result = -1;
                        }
                    }

                    SetAcquireFenceInBuffer(pQueuedStreamBuffer, -1);
                    m_emptyQueue->push(pQueuedStreamBuffer);
                }
                else
                {
                    NT_LOG_ERROR( "Release fence is not set for frame: %d", frameNumber);
                    result = -1;
                }
            }
            else
            {
                NT_LOG_ERROR( "Received buffer in error for frame: %d", frameNumber);
                result = -1;
            }
        }
        else
        {
            NT_LOG_ERROR( "Received buffer in non-FIFO order for frame: %d!", frameNumber);
            result = -1;
        }

        m_pQueueMutex->Unlock();

        if (result == 0)
        {
            m_bBufferAvailable = true;
            m_pQueueCond->Signal();
        }
    }
    else
    {
        NT_LOG_ERROR( "Filled buffer queue is NULL");
        result = -1;
    }

    return result;
}

/**************************************************************************************************************************
*   BufferManager::DestroyBuffers
*
*   @brief
*       Cleanup function to free all the memory allocated
*   @return
*       0 on success or -1 on failure
**************************************************************************************************************************/
void BufferManager::DestroyBuffers()
{
    if (m_emptyQueue != nullptr)
    {
        while (!m_emptyQueue->empty())
        {
            GenericBuffer* currBuffer = static_cast<GenericBuffer*>(m_emptyQueue->front());
            if (currBuffer == nullptr || GetReleaseFenceFromBuffer(currBuffer) != -1)
            {
                m_emptyQueue->pop();
                continue;
            }

            native_handle_t* phandle = *static_cast<native_handle_t**>(GetHandleFromBuffer(currBuffer));
            if (phandle == nullptr)
            {
                m_emptyQueue->pop();
                DestroyGenericBuffer(currBuffer);
                continue;
            }

#ifdef _LINUX
            m_GBmap[phandle].clear();
            m_GBmap.erase(phandle);
#else
            (*m_pCamxMemRelease)(reinterpret_cast<CamxMemHandle>(phandle));
#endif
            DestroyGenericBuffer(currBuffer);
            m_emptyQueue->pop();
        }

        delete m_emptyQueue;
        m_emptyQueue = nullptr;
    }

    if (m_filledQueue != nullptr)
    {
        while (!m_filledQueue->empty())
        {
            GenericBuffer* currBuffer = reinterpret_cast<GenericBuffer*>(m_filledQueue->front());
            if (currBuffer == nullptr || GetReleaseFenceFromBuffer(currBuffer) != -1)
            {
                m_filledQueue->pop();
                continue;
            }

            native_handle_t* phandle = *static_cast<native_handle_t**>(GetHandleFromBuffer(currBuffer));
            if (phandle == nullptr)
            {
                m_filledQueue->pop();
                DestroyGenericBuffer(currBuffer);
                continue;
            }

#ifdef _LINUX
            m_GBmap[phandle].clear();
            m_GBmap.erase(phandle);
#else
            (*m_pCamxMemRelease)(reinterpret_cast<CamxMemHandle>(phandle));
#endif
            DestroyGenericBuffer(currBuffer);
            m_filledQueue->pop();
        }

        delete m_filledQueue;
        m_filledQueue = nullptr;
    }

    if (m_inputImageQueue != nullptr)
    {
        // No new buffers created for m_inputImageQueue for bidirectional streams, so do not deallocate
        if (m_streamType != CAMERA3_STREAM_BIDIRECTIONAL)
        {
            while (!m_inputImageQueue->empty())
            {
                GenericBuffer* currBuffer = reinterpret_cast<GenericBuffer*>(m_inputImageQueue->front());
                if (currBuffer == nullptr || GetReleaseFenceFromBuffer(currBuffer) != -1)
                {
                    m_inputImageQueue->pop_front();
                    continue;
                }

                native_handle_t* phandle = *static_cast<native_handle_t**>(GetHandleFromBuffer(currBuffer));
                if (phandle == nullptr)
                {
                    m_inputImageQueue->pop_front();
                    DestroyGenericBuffer(currBuffer);
                    continue;
                }

#ifdef _LINUX
                m_GBmap[phandle].clear();
                m_GBmap.erase(phandle);
#else
                (*m_pCamxMemRelease)(reinterpret_cast<CamxMemHandle>(phandle));
#endif
                DestroyGenericBuffer(currBuffer);
                m_inputImageQueue->pop_front();
            }
        }

        delete m_inputImageQueue;
        m_inputImageQueue = nullptr;
    }

    delete this;
}

} // namespace tests

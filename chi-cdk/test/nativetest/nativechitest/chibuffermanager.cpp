//******************************************************************************
// Copyright (c) 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*******************************************************************************

#include "chibuffermanager.h"

namespace tests
{

/**************************************************************************************************************************
*   ChiBufferManager::GenerateOutputBuffer
*
*   @brief
*       Overloaded helper function to generate a Chi native buffer and NativeChiBuffer for a given input stream
*   @return
*       0 on success or -1 on failure
**************************************************************************************************************************/
int ChiBufferManager::GenerateOutputBuffer(
    GenericBuffer* requiredBuffer,  //[out] buffer to be populated
    GenericStream* inputStream)     //[in]  input stream to be associated with
{
    uint32_t width = inputStream->chiStream->width;
    uint32_t height = inputStream->chiStream->height;
    int outputFormat = inputStream->chiStream->format;
    int dataspace = inputStream->chiStream->dataspace;

    requiredBuffer->chiBuffer->pStream = inputStream->chiStream;

#ifdef _LINUX

    //output native buffer
    uint32_t usage = inputStream->chiStream->grallocUsage;

    Size grallocResolution = GetGrallocSize(width, height, outputFormat, dataspace);

    sp<GraphicBuffer> nativeBuffer = SAFE_NEW() GraphicBuffer(
        grallocResolution.width,
        grallocResolution.height,
        outputFormat,
        usage);

    ANativeWindowBuffer *anbOutput = nativeBuffer->getNativeBuffer();
    if (anbOutput == nullptr)
    {
        NT_LOG_ERROR( "Native window buffer for output stream is NULL");
        return -1;
    }
    requiredBuffer->chiBuffer->bufferInfo.phBuffer = &(anbOutput->handle);
    requiredBuffer->chiBuffer->bufferInfo.bufferType = CHIBUFFERTYPE::ChiGralloc;
    native_handle_t* pHandle = *static_cast<native_handle_t**>(requiredBuffer->chiBuffer->bufferInfo.phBuffer);
    m_GBmap[pHandle] = nativeBuffer;
#else
        // if PD10 format tests fail in Pre-Silicon, CamxMemAllocFunc in CamX needs implementation of PD10 memory allocation
        NT_LOG_DEBUG( "if PD10 format tests fail in Pre-Silicon,"
            "CamxMemAllocFunc in CamX needs implementation of PD10 memory allocation");
        CamxMemHandle bufferHandle;
        (*m_pCamxMemAlloc)(&bufferHandle, width, height, outputFormat, 0);
        requiredBuffer->chiBuffer->bufferInfo.phBuffer = reinterpret_cast<NativeChiBufferHandle*>(bufferHandle);
        requiredBuffer->chiBuffer->bufferInfo.bufferType = CHIBUFFERTYPE::ChiNative;
#endif
    requiredBuffer->chiBuffer->acquireFence = CreateFence(false);

    return 0;
}

/**************************************************************************************************
*   ChiBufferManager::GenerateInputBuffer
*
*   @brief
*       Helper function to read an image file and copy it over to image buffer
*   @return
*       0 on success or -1 on failure
**************************************************************************************************/
int ChiBufferManager::GenerateInputBuffer(
    GenericBuffer* requiredBuffer,  //[out] buffer property to be populated
    GenericStream* inputStream,     //[in] input stream to be associated with
    const char* filename)           //[in] filename to read contents
{
    if (filename == nullptr)
    {
        NT_LOG_ERROR( "Filename is NULL");
        return -1;
    }
    void *pData;

    std::ostringstream completeFilePath;

    completeFilePath << RootPath << filename;

    FILE* pFile = OsUtils::FOpen(completeFilePath.str().c_str(), "rb");

    if (pFile == nullptr)
    {
        NT_LOG_ERROR( "Input file read failed");
        return -1;
    }

    OsUtils::FSeek(pFile, 0L, SEEK_END);    // Seek to end of file
    long long fileSize = OsUtils::FTell(pFile);
    NT_LOG_DEBUG("Input file %s: size is: %lld", completeFilePath.str().c_str(), fileSize);
    OsUtils::FSeek(pFile, 0L, SEEK_SET);    // Seek back to beginning of file

    int res = 0;

#ifdef _LINUX
    sp<GraphicBuffer> nativeBuffer = SAFE_NEW() GraphicBuffer(
        inputStream->chiStream->width,
        inputStream->chiStream->height,
        inputStream->chiStream->format,
        inputStream->chiStream->grallocUsage);

    ANativeWindowBuffer *anbOutput = nativeBuffer->getNativeBuffer();
    if (anbOutput == nullptr)
    {
        NT_LOG_ERROR( "Native window buffer for input stream is NULL");
        return -1;
    }

    res = nativeBuffer->lock(GraphicBuffer::USAGE_SW_WRITE_OFTEN, reinterpret_cast<void**>(&pData));

    if (res != 0)
    {
        NT_LOG_ERROR( "Failed to lock the nativebuffer for reading");
        return -1;
    }

    requiredBuffer->chiBuffer->bufferInfo.phBuffer = &(anbOutput->handle);
    requiredBuffer->chiBuffer->bufferInfo.bufferType = CHIBUFFERTYPE::ChiGralloc;
    native_handle_t* pHandle = *static_cast<native_handle_t**>(requiredBuffer->chiBuffer->bufferInfo.phBuffer);
    m_GBmap[pHandle] = nativeBuffer;
#else
    CamxMemHandle bufferHandle;
    (*m_pCamxMemAlloc)(&bufferHandle, inputStream->chiStream->width, inputStream->chiStream->height, inputStream->chiStream->format, 0);
    requiredBuffer->chiBuffer->bufferInfo.phBuffer = reinterpret_cast<buffer_handle_t*>(bufferHandle);
    requiredBuffer->chiBuffer->bufferInfo.bufferType = CHIBUFFERTYPE::ChiNative;

    native_handle_t* pHandle = *reinterpret_cast<native_handle_t**>(requiredBuffer->chiBuffer->bufferInfo.phBuffer);
    pData = *reinterpret_cast<void**>(pHandle->data);
#endif
    if (NULL != pData) {
        size_t read = OsUtils::FRead(pData, /*unknown dest buffer size*/fileSize, 1, fileSize, pFile);
        res = OsUtils::FClose(pFile);
        if (static_cast<long>(read) != fileSize)
        {
            NT_LOG_ERROR("Failed to read file, read: %d bytes.", read);
            return -1;
        }
    }
    else
    {
        NT_LOG_ERROR("pData is null");
        return -1;
    }
#ifdef _LINUX
    if (NULL != pData)
    {
        res = nativeBuffer->unlock();
    }
#endif
    requiredBuffer->chiBuffer->pStream = inputStream->chiStream;
    requiredBuffer->chiBuffer->acquireFence = CreateFence(false);
    return 0;
}

/**************************************************************************************************************************
*   ChiBufferManager::SaveImageToFile
*
*   @brief
*       Helper function to save an image to the file
*   @return
*       0 on success or -1 on failure
**************************************************************************************************************************/
int ChiBufferManager::SaveImageToFile(
    GenericBuffer* resultBuffer,  //[in] result to save image from
    std::string filename)         //[in] filename to save image as
{
    int res;
    void* pData = nullptr;

    native_handle_t* phBuffer = *static_cast<native_handle_t**>(resultBuffer->chiBuffer->bufferInfo.phBuffer);
    NativeChiStream* resultStream = resultBuffer->chiBuffer->pStream;

    uint32_t output_width  = resultStream->width;
    uint32_t output_height = resultStream->height;
    uint32_t format        = resultStream->format;
    uint32_t usage         = resultStream->grallocUsage;


#ifdef _LINUX

    if (m_GBmap.find(phBuffer) == m_GBmap.end())
    {
        NT_LOG_ERROR( "Cannot find nativehandle for outputBuffer");
        return -1;
    }
    res = m_GBmap.at(phBuffer)->lock(GraphicBuffer::USAGE_SW_READ_OFTEN, reinterpret_cast<void**>(&pData));
    if (res != 0)
    {
        NT_LOG_ERROR( "outputNativeBuffer lock failed");
        return -1;
    }

    // Ensure capture folder gets created or exists
    // Make upper camera folder first
    if (mkdir(ImageUpperPath.c_str(), 0777) != 0 && EEXIST != errno)
    {
        NT_LOG_ERROR( "Failed to create capture camera folder, Error: %d", errno);
        return -1;
    }

    // Make lower nativetest folder second
    if (mkdir(ImageRootPath.c_str(), 0777) != 0 && EEXIST != errno)
    {
        NT_LOG_ERROR( "Failed to create capture root folder, Error: %d", errno);
        return -1;
    }
#else

    pData = *reinterpret_cast<void**>(phBuffer->data);

    if (pData == nullptr)
    {
        NT_LOG_ERROR( "Buffer data is NULL");
        return -1;
    }

    // make sure capture folder gets created or exists
    if (_mkdir(ImageRootPath.c_str()) != 0)
    {
        DWORD error = GetLastError();
        if (ERROR_ALREADY_EXISTS != error)
        {
            NT_LOG_ERROR( "Failed to create capture folder, Error: %d", error);
            return -1;
        }
    }

#endif

    size_t imageSize = 0;
    // Image formats we know how to calculate size for...
    if (format == HAL_PIXEL_FORMAT_BLOB ||
        format == HAL_PIXEL_FORMAT_RAW_OPAQUE ||
        format == HAL_PIXEL_FORMAT_RAW10 ||
        format == HAL_PIXEL_FORMAT_Y8 ||
        format == HAL_PIXEL_FORMAT_Y16)
    {
        imageSize = GetGrallocSize(output_width, output_height, format, resultStream->dataspace, reinterpret_cast<unsigned char *>(pData)).width;
    }
    else // Unknown image format size calculations: PD10, RAW64, NV12HEIF, P010
    {
        // PD10 && non-pre-silicon
        if (format == PRIVATE_PIXEL_FORMAT_PD10)
        {
#if defined (_LINUX)
            NT_LOG_DEBUG( "Migration to CamxChi function needed");
            imageSize = GetGrallocSize(output_width, output_height, format, resultStream->dataspace, reinterpret_cast<unsigned char *>(pData)).width;
#endif
        }

        // it will enter the below block if it is pre-silicon. In case of actual target, it will go to below block for all formats except PD10
        if (0 == imageSize)
        {
            NT_LOG_WARN( "CamxMemGetImageSize must have implementation for PD10 size calculation, may tend to fail in pre-silicon");
            imageSize = (*m_pCamxMemGetImageSize)(output_width, output_height, format, usage);
        }
    }

    if (0 == imageSize)
    {
        NT_LOG_ERROR("Calculated gralloc image size should not be 0!");
        return -1;
    }

    NT_LOG_DEBUG( "Image size to be saved is: %zu", imageSize);
    filename.append(GetFileExt(format));
    NT_LOG_DEBUG( "Saving image to file: %s", filename.c_str());

    char out_fname[256];
    OsUtils::SNPrintF(out_fname, sizeof(out_fname), "%s", filename.c_str());

    FILE* pFile = OsUtils::FOpen(out_fname, "wb");
    if (pFile == nullptr)
    {
        NT_LOG_ERROR( "Output file creation failed");
        return -1;
    }

    size_t written = 0;

    written = OsUtils::FWrite(reinterpret_cast<unsigned char *>(pData), 1, imageSize, pFile);

    if (written != imageSize)
    {
        NT_LOG_ERROR("failed to write: %s", out_fname);
        return -1;
    }

#ifdef _LINUX
    res = m_GBmap.at(phBuffer)->unlock();
    if (res != 0)
    {
        NT_LOG_ERROR( "outputNativeBuffer unlock failed");
        return -1;
    }
#endif //_LINUX
    res = OsUtils::FClose(pFile);
    if (res != 0)
    {
        NT_LOG_ERROR( "Close file failed");
        return -1;
    }
    return 0;
}

/**************************************************************************************************************************
*   ChiBufferManager::CreateGenericBuffer
*
*   @brief
*       Helper function to initialize a generic buffer with a chi buffer
*   @return
*       GenericBuffer pointer on success, nullptr otherwise
**************************************************************************************************************************/
BufferManager::GenericBuffer* ChiBufferManager::CreateGenericBuffer()
{
    GenericBuffer* newGenericBuffer = SAFE_NEW() GenericBuffer();
    if (newGenericBuffer != nullptr)
    {
        NativeChiBuffer* newChiBuffer = SAFE_NEW() NativeChiBuffer();
        if (newChiBuffer != nullptr)
        {
            newChiBuffer->size = sizeof(NativeChiBuffer);
            newGenericBuffer->chiBuffer = newChiBuffer;
            return newGenericBuffer;
        }
    }
    return nullptr;
}

/**************************************************************************************************************************
*   ChiBufferManager::DestroyGenericBuffer
*
*   @brief
*       Helper function to destroy a generic buffer along with its associated chi buffer
*   @return
*       int 0 on success, otherwise -1
**************************************************************************************************************************/
void ChiBufferManager::DestroyGenericBuffer(GenericBuffer* buffer)
{
    if (buffer != nullptr)
    {
        if (buffer->chiBuffer != nullptr)
        {
            DestroyFence(buffer->chiBuffer->acquireFence);
            DestroyFence(buffer->chiBuffer->releaseFence);

            delete buffer->chiBuffer;
        }
        delete buffer;
    }
}

/**************************************************************************************************************************
*   ChiBufferManager::GetTypeFromStream
*
*   @brief
*       Get stream type from generic stream
*   @return
*       int stream type
**************************************************************************************************************************/
int ChiBufferManager::GetTypeFromStream(GenericStream* stream)
{
    return stream->chiStream->streamType;
}

/**************************************************************************************************************************
*   ChiBufferManager::GetMaxBuffersFromStream
*
*   @brief
*       Get max number of buffers from generic stream
*   @return
*       uint32_t max number of buffers
**************************************************************************************************************************/
uint32_t ChiBufferManager::GetMaxBuffersFromStream(GenericStream* stream)
{
    return stream->chiStream->maxNumBuffers;
}

/**************************************************************************************************************************
*   ChiBufferManager::GetNativeBufferFromGeneric
*
*   @brief
*       Get void pointer to a NativeChiBuffer from a GenericBuffer
*   @return
*       void pointer to the associated NativeChiBuffer
**************************************************************************************************************************/
void* ChiBufferManager::GetNativeBufferFromGeneric(GenericBuffer* buffer)
{
    return static_cast<void*>(buffer->chiBuffer);
}

/**************************************************************************************************************************
*   ChiBufferManager::GetHandleFromBuffer
*
*   @brief
*       Get buffer handle from generic buffer
*   @return
*       NativeChiBufferHandle
**************************************************************************************************************************/
BufferManager::NativeChiBufferHandle ChiBufferManager::GetHandleFromBuffer(GenericBuffer* buffer)
{
    return buffer->chiBuffer->bufferInfo.phBuffer;
}

/**************************************************************************************************************************
*   ChiBufferManager::GetStatusFromBuffer
*
*   @brief
*       Get buffer status from generic buffer
*   @return
*       int buffer status
**************************************************************************************************************************/
int ChiBufferManager::GetStatusFromBuffer(GenericBuffer* buffer)
{
    return buffer->chiBuffer->bufferStatus;
}

/**************************************************************************************************************************
*   ChiBufferManager::GetReleaseFenceFromBuffer
*
*   @brief
*       Get release fence from generic buffer
*   @return
*       int release fence status, where -1 means no waiting
**************************************************************************************************************************/
int ChiBufferManager::GetReleaseFenceFromBuffer(GenericBuffer* buffer)
{
    if (buffer->chiBuffer->releaseFence.valid == true)
    {
        CDKResult* pFenceResult = NULL;
        CDKResult res = m_pChiModule->GetFenceOps()->pGetFenceStatus(m_pChiModule->GetContext(),
            buffer->chiBuffer->releaseFence.hChiFence, pFenceResult);
        if (CDKResultSuccess == res && NULL != pFenceResult)
        {
            if (CDKResultSuccess != *pFenceResult)
            {
                return 0;   // TODO fence is busy?
            }
            else
            {
                return -1;  // Fence not busy
            }
        }
        NT_LOG_ERROR( "Failure when getting release fence status!");
        return -1;  // TODO what to return for failure?
    }
    // If fence not valid, then assume no waiting
    return -1;
}

/**************************************************************************************************************************
*   ChiBufferManager::SetAcquireFenceInBuffer
*
*   @brief
*       Set the acquire fence in generic buffer
*   @return
*       void
**************************************************************************************************************************/
void ChiBufferManager::SetAcquireFenceInBuffer(GenericBuffer* buffer, int setVal)
{
    if (-1 == setVal)
    {
        DestroyFence(buffer->chiBuffer->acquireFence);
    }
    else if (buffer->chiBuffer->acquireFence.valid == true)
    {
        // TODO hold the fence?
        PFNCHIFENCECALLBACK dummyCallback = NULL;
        VOID* pData = NULL;
        m_pChiModule->GetFenceOps()->pWaitFenceAsync(m_pChiModule->GetContext(), dummyCallback,
            buffer->chiBuffer->acquireFence.hChiFence, pData);
    }
    // If not valid, do nothing
}

/**************************************************************************************************************************
*   ChiBufferManager::GetMaxBuffersFromBuffer
*
*   @brief
*       Get the max number of buffers from generic buffer's associated stream
*   @return
*       uint32_t max number of buffers
**************************************************************************************************************************/
uint32_t ChiBufferManager::GetMaxBuffersFromBuffer(GenericBuffer* buffer)
{
    return buffer->chiBuffer->pStream->maxNumBuffers;
}

/**************************************************************************************************************************
*   ChiBufferManager::CreateFence
*
*   @brief
*       Creates a fence handle using the driver and assembles a CHIFENCEINFO object out of it
*   @params
*       [in]    bool    isValid     if set false, the returned fence will not have any memory allocated for its handle
*   @return
*       CHIFENCEINFO object, which may have its valid flag true or false
**************************************************************************************************************************/
CHIFENCEINFO ChiBufferManager::CreateFence(bool isValid)
{
    CHIFENCEINFO fenceInfo;
    fenceInfo.valid = false;
    fenceInfo.type = ChiFenceTypeInternal;

    if (isValid)
    {
        CHIFENCEHANDLE* pFenceHandle = SAFE_NEW() CHIFENCEHANDLE;
        CDKResult res = m_pChiModule->GetFenceOps()->pCreateFence(m_pChiModule->GetContext(), NULL/*TODO*/, pFenceHandle);

        if (res == CDKResultSuccess)
        {
            fenceInfo.valid = true;
            fenceInfo.hChiFence = *pFenceHandle;
        }
    }

    return fenceInfo;
}

/**************************************************************************************************************************
*   ChiBufferManager::DestroyFence
*
*   @brief
*       Destroys a fence by releasing it on driver side and deallocating its fence handle. No action if fence not valid.
*   @return
*       None
**************************************************************************************************************************/
void ChiBufferManager::DestroyFence(CHIFENCEINFO fenceInfo)
{
    if (fenceInfo.valid == true)
    {
        fenceInfo.valid = false;
        CHIFENCEHANDLE* pFenceHandle = &(fenceInfo.hChiFence);

        m_pChiModule->GetFenceOps()->pReleaseFence(m_pChiModule->GetContext(), fenceInfo.hChiFence);
        if (pFenceHandle != NULL)
        {
            delete pFenceHandle;
        }
    }
    // If not valid, then no action needed
}

} // namespace tests

//******************************************************************************************************************************
// Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//******************************************************************************************************************************
//==============================================================================================================================
// IMPLEMENTATION of chitestcase
//==============================================================================================================================

#include <string.h>
#include "chitestcase.h"
#include "chibuffermanager.h"

namespace tests
{
// Initialize static variables
uint32_t                                        ChiTestCase::m_errorNotifyBitFlag[MAX_REQUESTS];
std::queue<ChiCaptureResult*>                   ChiTestCase::m_pResultsToProcess;
std::queue<ChiTestCase::SessionPrivateData*>    ChiTestCase::m_pPrivateDataToProcess;
Mutex*                                          ChiTestCase::m_pResultQueueMutex;
Condition*                                      ChiTestCase::m_pBufferCountCond;

ChiTestCase::ProcessSignal                      ChiTestCase::m_processingSignaler;
Mutex*                                          ChiTestCase::m_pProcessingMutex;
Condition*                                      ChiTestCase::m_pProcessingCond;

    std::list<ChiStream*>                           ChiTestCase::m_bufferErrorStreams;

void ChiTestCase::Setup()
{
    // Setup mutexes, conditions, and threads first in case emergency Teardown happens
    m_pBufferCountMutex = Mutex::Create("m_pBufferCountMutex");
    m_pBufferCountCond = Condition::Create("m_pBufferCountCond");
    m_pResultQueueMutex = Mutex::Create("m_pResultQueueMutex");
    m_pProcessingMutex = Mutex::Create("m_pProcessingMutex");
    m_pProcessingCond = Condition::Create("m_pProcessingCond");

    // Setup the long running thread in charge of processing capture results
    CDKResult result = OsUtils::ThreadCreate(ProcessCaptureResults, this, &m_processingThread);
    NT_ASSERT(CDKResultSuccess == result, "Failed to create processing thread!");

    m_pChiModule = ChiModule::GetInstance();
    NT_ASSERT(m_pChiModule != nullptr, " ChiModule could not be instantiated");
    if (nullptr != m_pChiModule)
    {
        // Setup buffer manager library
        NT_EXPECT(0 == ChiBufferManager::LoadBufferLibs(m_pChiModule->GetLibrary()),
            "Failed to load symbols for buffer manager!");
    }
    m_streamInfo.streamIds = m_streamId;
    //TODO: Let common framework do the typecasting
    m_streamInfo.directions = reinterpret_cast<camera3_stream_type_t*>(m_direction);
    m_streamInfo.formats = reinterpret_cast<android_pixel_format_t*>(m_format);
    m_streamInfo.resolutions = m_resolution;
    m_streamInfo.usageFlags = m_usageFlag;
    m_streamInfo.isRealtime = m_isRealtime;
    m_streamInfo.isJpeg = true;
    m_streamInfo.filename = nullptr;

    m_numStreams = 0;
    m_isCamIFTestGen = false;
    m_buffersRemaining = 0;
    m_streamBufferMap.clear();
    m_streamIdMap.clear();

    for (uint32_t i = 0; i < NATIVETEST_ELEMENTS(m_errorNotifyBitFlag); i++)
    {
        ClearErrorNotifyFlag(i);
    }

#ifndef OLD_METADATA
    // Setup metadata util instance
    m_pChiMetadataUtil = ChiMetadataUtil::GetInstance();
    NT_ASSERT(m_pChiMetadataUtil != nullptr, " ChiMetadataUtil could not be instantiated");
#endif // OLD_METADATA
}

void ChiTestCase::Teardown()
{
    // Shut down process capture result thread
    SignalProcessingThread(SignalDone);
    OsUtils::ThreadWait(m_processingThread);

    // Do not destroy mutex/condition variables in DestroyCommonResources(),
    // as that function is called multiple times per testcase (and these variables are only created once)
    if (nullptr != m_pBufferCountMutex)
    {
        m_pBufferCountMutex->Destroy();
        m_pBufferCountMutex = nullptr;
    }
    if (nullptr != m_pBufferCountCond)
    {
        m_pBufferCountCond->Destroy();
        m_pBufferCountCond = nullptr;
    }
    if (nullptr != m_pResultQueueMutex)
    {
        m_pResultQueueMutex->Destroy();
        m_pResultQueueMutex = nullptr;
    }
    if (nullptr != m_pProcessingMutex)
    {
        m_pProcessingMutex->Destroy();
        m_pProcessingMutex = nullptr;
    }
    if (nullptr != m_pProcessingCond)
    {
        m_pProcessingCond->Destroy();
        m_pProcessingCond = nullptr;
    }

    DestroyCommonResources();
    ChiModule::DestroyInstance();
    m_pChiModule = nullptr;
}

/***************************************************************************************************************************
*   ChiTestCase::CommonProcessCaptureResult
*
*   @brief
*       Common Process capture result redirected from the static method, this is base class implementation which can be used
*       for common operations done by all testcases
*   @param
*        [in]  CHICAPTURERESULT*     pResult                pointer to capture result
*        [in]  void*                 pPrivateCallbackData   pointer private callback data
*   @return
*       none
***************************************************************************************************************************/
void ChiTestCase::CommonProcessCaptureResult(CHICAPTURERESULT* pResult, SessionPrivateData* pPrivateCallbackData)
{
    NATIVETEST_UNUSED_PARAM(pResult);
    NATIVETEST_UNUSED_PARAM(pPrivateCallbackData);
}

/***************************************************************************************************************************
*   ChiTestCase::QueueCaptureResult
*
*   @brief
*       Copy and queue up capture results returned from driver for later processing in the main thread
*   @param
*        [in]  CHICAPTURERESULT*     pResult                pointer to capture result
*        [in]  void*                 pPrivateCallbackData   pointer private callback data
*   @return
*       None
***************************************************************************************************************************/
void ChiTestCase::QueueCaptureResult(CHICAPTURERESULT* pResult, void* pPrivateCallbackData)
{
    SessionPrivateData* pSessionPrivateData = static_cast<SessionPrivateData*>(pPrivateCallbackData);

    /* START critical section */
    m_pResultQueueMutex->Lock();

    // Copy the result (since pResult is volatile, needs to be in critical section)
    ChiCaptureResult* pSavedResult = NULL;
    pSavedResult = DeepCopyCaptureResult(pResult);
    if (NULL == pSavedResult)
    {
        m_pResultQueueMutex->Unlock();
        NT_ASSERT(NULL != pSavedResult, "Failed to copy ChiCaptureResult!");
    }


    // Copy the private data
    SessionPrivateData* pSavedPrivate = SAFE_NEW() SessionPrivateData();
    memcpy(pSavedPrivate, pSessionPrivateData, sizeof(SessionPrivateData));

    // Push copied data on queue
    m_pResultsToProcess.push(pSavedResult);
    m_pPrivateDataToProcess.push(pSavedPrivate);
    //NT_LOG_DEBUG( "Queuing result to process for frame %d", pSavedResult->frameworkFrameNum);
    //NT_LOG_DEBUG( "Number of results to process: %d", m_pResultsToProcess.size());

    m_pResultQueueMutex->Unlock();
    /* END critical section */

    // Signal the processing thread to process the queued capture result
    SignalProcessingThread(SignalProcess);
}

/***************************************************************************************************************************
*   ChiTestCase::ProcessCaptureResults
*
*   @brief
*       Process queued up capture results, dispatching to the correct instance of the testcase.
*       This is designed to be run in a separate worker thread from the main thread.
*   @param
*       [in]    VOID*   pArg    pointer to a ChiTestCase instance
*   @return
*       VOID* not used
***************************************************************************************************************************/
VOID* ChiTestCase::ProcessCaptureResults(VOID* pArg)
{
    bool isDone = false;
    ChiTestCase* testInstance = NULL;
    ChiCaptureResult* pCurrResult = NULL;
    SessionPrivateData* pCurrPrivateData = NULL;

    // Get the ChiTestCase instance
    if (NULL != pArg)
    {
        testInstance = reinterpret_cast<ChiTestCase*>(pArg);
    }
    else
    {
        NT_EXPECT(NULL != pArg, "No ChiTestCase instance provided!");
        return NULL;
    }

    /* START critical section */
    testInstance->m_pProcessingMutex->Lock();

    while (!isDone)
    {
        // Wait for next signal
        testInstance->m_pProcessingCond->Wait(testInstance->m_pProcessingMutex->GetNativeHandle());

        switch (testInstance->m_processingSignaler)
        {
        case SignalReady:
            // Do nothing
            NT_LOG_DEBUG( "Process thread ready...");
            break;
        case SignalProcess:
            // Process all queued results
            while (true)
            {
                // Thread-safe queue operations
                m_pResultQueueMutex->Lock();
                if (!m_pResultsToProcess.empty() && !m_pPrivateDataToProcess.empty())
                {
                    // Get pointers and remove from queue
                    pCurrResult = m_pResultsToProcess.front();
                    pCurrPrivateData = m_pPrivateDataToProcess.front();
                    m_pResultsToProcess.pop();
                    m_pPrivateDataToProcess.pop();

                    // Verify pointers are valid
                    if (NULL != pCurrResult && NULL != pCurrPrivateData)
                    {
                        // Reset wait retry count, so we don't time out
                        testInstance->ResetWaitForResultsRetryCount();
                    }
                    else
                    {
                        NT_LOG_ERROR( "Found invalid CaptureResult/PrivateData pair! (at least one is NULL)");
                        m_pResultQueueMutex->Unlock();
                        break;
                    }
                }
                else  // No more results to process
                {
                    m_pResultQueueMutex->Unlock();
                    break;
                }
                m_pResultQueueMutex->Unlock();

                //NT_LOG_DEBUG( "Processing result for frame %d", pCurrResult->frameworkFrameNum);
                pCurrPrivateData->pTestInstance->CommonProcessCaptureResult(pCurrResult, pCurrPrivateData);

                // Clean up pointers after processing complete
                DeepDestroyCaptureResult(pCurrResult);
                if (NULL != pCurrPrivateData)
                {
                    delete pCurrPrivateData;
                }
            }

            // Notify main thread that results have been processed
            m_pBufferCountCond->Signal();

            break;
        case SignalDone:
            // Ready to exit
            NT_LOG_DEBUG( "Process thread done...");
            isDone = true;
            break;
        default:
            NT_LOG_ERROR( "Invalid ProcessSignal! (%d)", testInstance->m_processingSignaler);
            break;
        }

        // Notify main thread that process thread is ready for next command
        testInstance->m_processingSignaler = SignalReady;
        testInstance->m_pProcessingCond->Broadcast();
    }

    testInstance->m_pProcessingMutex->Unlock();
    /* END critical section */

    return NULL;
}

/***************************************************************************************************************************
*   ChiTestCase::QueuePartialCaptureResult
*
*   @brief
*       Copy and queue up capture results returned from driver for later processing in the main thread
*   @param
*        [in]  CHIPARTIALCAPTURERESULT*     pPartialResult          pointer to capture result
*        [in]  void*                        pPrivateCallbackData    pointer private callback data
*   @return
*       None
***************************************************************************************************************************/
void ChiTestCase::QueuePartialCaptureResult(CHIPARTIALCAPTURERESULT* pPartialResult, void* pPrivateCallbackData)
{
    NATIVETEST_UNUSED_PARAM(pPartialResult);
    NATIVETEST_UNUSED_PARAM(pPrivateCallbackData);
    // TODO TDEV-2292
}

/**************************************************************************************************************************
*   ChiTestCase::SignalProcessingThread()
*
*   @brief
*       Changes the signaler and then notifies the process thread
*   @param
*       [in]    ProcessSignal     signal      command to direct the flush thread
*   @return
*       void
**************************************************************************************************************************/
void ChiTestCase::SignalProcessingThread(ProcessSignal signal)
{
    /* START critical section */
    m_pProcessingMutex->Lock();

    // Wait for thread to be ready
    while (SignalReady != m_processingSignaler)
    {
        m_pProcessingCond->Wait(m_pProcessingMutex->GetNativeHandle());
    }

    // Set the signal
    m_processingSignaler = signal;

    // Notify the thread
    const char* processSignalStrings[3] = { "SignalReady", "SignalProcess", "SignalDone" };
    NT_LOG_DEBUG( "Signaling process thread: %s", processSignalStrings[signal]);
    m_pProcessingCond->Broadcast();

    m_pProcessingMutex->Unlock();
    /* END critical section */
}

/***************************************************************************************************************************
*   ChiTestCase::ProcessMessage
*
*   @brief
*       Process Notify message from driver
*   @param
*     [in]  CHIMESSAGEDESCRIPTOR*     pMessageDescriptor       pointer to message descriptor
*     [in]  void*                     pPrivateCallbackData     pointer private callback data
*   @return
*       none
***************************************************************************************************************************/
void ChiTestCase::ProcessMessage(
    const CHIMESSAGEDESCRIPTOR* pMessageDescriptor,
    void*                       pPrivateCallbackData)
{
    NATIVETEST_UNUSED_PARAM(pPrivateCallbackData);
    NT_LOG_INFO( "Received notify from driver");

    switch (pMessageDescriptor->messageType)
    {
    case CHIMESSAGETYPE::ChiMessageTypeError:
    {
        CHIERRORMESSAGE errMessage = pMessageDescriptor->message.errorMessage;
        NT_LOG_ERROR( "Notify ERROR message when processing frame %d, stream %p",
            errMessage.frameworkFrameNum, errMessage.pErrorStream);

        switch (errMessage.errorMessageCode)
        {
        case CHIERRORMESSAGECODE::MessageCodeDevice:
            SetErrorNotifyFlag(errMessage.frameworkFrameNum, MessageCodeDevice);
            NT_LOG_ERROR( "Notify ERROR [DEVICE]: serious failure occurred and no further frames will be"
                " produced by the device");
            //TODO:Stop sending requests for this type of error
            break;
        case CHIERRORMESSAGECODE::MessageCodeRequest:
            SetErrorNotifyFlag(errMessage.frameworkFrameNum, MessageCodeRequest);
            NT_LOG_ERROR( "Notify ERROR [REQUEST]: error has occurred in processing a request and no output"
                " will be produced for this request");
            break;
        case CHIERRORMESSAGECODE::MessageCodeResult:
            SetErrorNotifyFlag(errMessage.frameworkFrameNum, MessageCodeResult);
            NT_LOG_ERROR( "Notify ERROR [RESULT]: error has occurred in producing an output result metadata"
                " buffer for a request");
            break;
        case CHIERRORMESSAGECODE::MessageCodeBuffer:
            SetErrorNotifyFlag(errMessage.frameworkFrameNum, MessageCodeBuffer, errMessage.pErrorStream);
            NT_LOG_ERROR( "Notify ERROR [BUFFER]: error has occurred in placing an output buffer into a"
                " stream for a request");
            break;
        case CHIERRORMESSAGECODE::MessageCodeTriggerRecovery:
            SetErrorNotifyFlag(errMessage.frameworkFrameNum, MessageCodeTriggerRecovery);
            NT_LOG_ERROR( "Notify ERROR [RECOVERY]: error has occurred and we need to trigger recovery");
            break;
        default:
            NT_LOG_ERROR( "Notify ERROR [UNKNOWN]: unknown error message code %d",
                errMessage.errorMessageCode);
            break;
        }
        break;
    }
    case CHIMESSAGETYPE::ChiMessageTypeShutter:
    {
        CHISHUTTERMESSAGE shutterMessage = pMessageDescriptor->message.shutterMessage;
        NT_LOG_INFO( "Notify shutter message frame: %d, timestamp: %llu",
            shutterMessage.frameworkFrameNum, shutterMessage.timestamp);
        break;
    }
    case CHIMESSAGETYPE::ChiMessageTypeSof:
        NT_LOG_INFO( "Start of frame event triggered");
        break;
    case CHIMESSAGETYPE::ChiMessageTypeMetaBufferDone:
        NT_LOG_INFO( "Metabuffer is done processing");
        break;
        // This message type was removed in a later version of chi.h
        //case CHIMESSAGETYPE::ChiMessageTypePartialMetaBufferDone:
        //    NT_LOG_INFO( "Partial metabuffer is available");
        //    break;
    case CHIMESSAGETYPE::ChiMessageTypeTriggerRecovery:
        NT_LOG_INFO( "Bubble maximum hit for recovery");
        break;
    default:
        NT_LOG_ERROR( "Unknown message type %d", pMessageDescriptor->messageType);
        break;
    }
}

/***************************************************************************************************************************
*   ChiTestCase::WaitForResults
*
*   @brief
*       Common waiting condition for all testcases, Once the test sends required number of requests this waiting condition
*       is invoked to wait for all results to be returned back by driver
*   @param
*        None
*   @return
*       CDKResult success if all results returned by driver/ fail if buffers were not returned within buffer timeout
***************************************************************************************************************************/
CDKResult ChiTestCase::WaitForResults()
{
    m_pBufferCountMutex->Lock();
    CDKResult result = CDKResultSuccess;
    int timeout = CmdLineParser::GetTimeoutOverride();

    if (timeout <= 0) // no timeout
    {
        while (m_buffersRemaining.load() != 0)
        {
            // Wait forever for buffer(s)
            m_pBufferCountCond->Wait(m_pBufferCountMutex->GetNativeHandle());
        }
        m_pBufferCountMutex->Unlock();
    }
    else
    {
        m_waitForResultsRetries = 0;
        while (m_buffersRemaining.load() != 0 && m_waitForResultsRetries < TIMEOUT_RETRIES)
        {
            NT_LOG_DEBUG( "Waiting for buffers to be returned, pending buffer count: %d", m_buffersRemaining.load());
            m_pBufferCountCond->TimedWait(m_pBufferCountMutex->GetNativeHandle(), timeout);
            m_waitForResultsRetries++;
        }
        m_pBufferCountMutex->Unlock();

        if (m_buffersRemaining.load() != 0)
        {
            NT_LOG_ERROR( "Buffer wait condition timed out");
            result = CDKResultETimeout;
        }
    }

    return result;
}

/***************************************************************************************************************************
*   ChiTestCase::InitializeBufferMangers
*
*   @brief
*       Initializes buffer manager for each required stream
*   @param
*       [in]    int cameraId    camera to initialize buffers for (used in file naming)
*   @return
*       CDKResult success if buffer manager could be created / failure
***************************************************************************************************************************/
CDKResult ChiTestCase::InitializeBufferMangers(int cameraId)
{
    CDKResult result = CDKResultSuccess;

    if (m_numStreams <= 0)
    {
        NT_LOG_ERROR( "Cannot create buffermanagers with stream count: %d", m_numStreams);
        result = CDKResultENeedMore;
    }

    if (result == CDKResultSuccess)
    {
        for (int streamIndex = 0; streamIndex < m_numStreams; streamIndex++)
        {
            BufferManager::NativeChiStream* currentStream = &m_pRequiredStreams[streamIndex];
            BufferManager::GenericStream genericStream(currentStream);

            BufferManager* manager = SAFE_NEW() ChiBufferManager(m_streamId[streamIndex]);
            m_pBufferManagers[streamIndex] = manager->Initialize(
                cameraId,
                &genericStream,
                m_streamInfo.streamIds[streamIndex],
                m_streamInfo.filename);

            if (m_pBufferManagers[streamIndex] == nullptr)
            {
                NT_LOG_ERROR( "Failed to allocate memory for buffer manager for stream index: %d", streamIndex);
                result = CDKResultENoMemory;
                break;
            }

            m_streamBufferMap[currentStream] = m_pBufferManagers[streamIndex];
        }
    }

    return result;
}

/**************************************************************************************************
*   ChiTestCase::IsRDIStream
*
*   @brief
*       Helper function to determine if stream is RDI
*   @param
*       [in] CHISTREAMFORMAT    format    Stream format
*   @return
*       bool indicating whether the stream is RDI
**************************************************************************************************/
bool ChiTestCase::IsRDIStream(CHISTREAMFORMAT format)
{
    return (format == ChiStreamFormatRaw10 ||
        format == ChiStreamFormatRawOpaque ||
        format == ChiStreamFormatRaw16);
}

/***************************************************************************************************************************
*   ChiTestCase::DestroyCommonResources
*
*   @brief
*       Destroy member variables present in the base class, i.e., common to all testcases
*   @param
*        None
*   @return
*       None
***************************************************************************************************************************/
void ChiTestCase::DestroyCommonResources()
{
#ifndef OLD_METADATA
    if (NULL != m_pChiMetadataUtil)
    {
        NT_EXPECT(m_pChiMetadataUtil->DestroyMetabufferPools() == CDKResultSuccess,
             "Failed to destroy metabuffer pools!");
    }
#endif // OLD_METADATA

    NT_LOG_DEBUG( "Deleting allocated buffermanagers");
    for (int streamIndex = 0; streamIndex < m_numStreams; streamIndex++)
    {
        if (m_streamBufferMap.find(&m_pRequiredStreams[streamIndex]) != m_streamBufferMap.end())
        {
            BufferManager* manager = m_streamBufferMap.at(&m_pRequiredStreams[streamIndex]);

            if (manager != nullptr)
            {
                manager->DestroyBuffers();
                m_streamBufferMap.erase(&m_pRequiredStreams[streamIndex]);
            }
        }
    }

    NT_EXPECT(m_streamBufferMap.empty(), "There are still pending buffermanagers not freed!");

    if (m_pRequiredStreams != nullptr)
    {
        delete[] m_pRequiredStreams;
        m_pRequiredStreams = nullptr;
    }

    m_streamIdMap.clear();
    m_numStreams = 0;
    m_buffersRemaining = 0;
}

/***************************************************************************************************************************
*   ChiTestCase::AtomicIncrement
*
*   @brief
*       Thread safe increment of buffers remaining
*   @param
*        [in]   int count   increment by count, this is an optional variable by default it will be incremented by 1
*   @return
*       None
***************************************************************************************************************************/
void ChiTestCase::AtomicIncrement(int count)
{
    m_buffersRemaining += count;
}

/***************************************************************************************************************************
*   ChiTestCase::AtomicDecrement
*
*   @brief
*       Thread safe decerement of buffers remaining, if buffers remaining reached zero then it will signal all results
*       obtained
*   @param
*        [in]   int count   decrement by count, this is an optional variable by default it will be decremented by 1
*   @return
*       None
***************************************************************************************************************************/
void ChiTestCase::AtomicDecrement(int count)
{
    m_buffersRemaining -= count;
    if (m_buffersRemaining == 0)
    {
        m_pBufferCountCond->Signal();
    }
}

/***************************************************************************************************************************
*   ChiTestCase::GetPendingBufferCount
*
*   @brief
*       gets the buffer remaining count in a thread safe manner
*   @param
*        None
*   @return
*       uint32_t buffer remaining count
***************************************************************************************************************************/
uint32_t ChiTestCase::GetPendingBufferCount() const
{
    return m_buffersRemaining.load();
}

/***************************************************************************************************************************
*   ChiTestCase::ConvertCamera3StreamToChiStream
*
*   @brief
*       Convert a camera3_stream_t object to a CHISTREAM object
*   @param
*       [in]    camera3_stream_t*   inCamStreams     array of input streams to convert from
*       [out]   CHISTREAM*          outChiStreams    array of output streams to convert to
*       [in]    int                 numStreams      number of streams
*   @return
*       None
***************************************************************************************************************************/
void ChiTestCase::ConvertCamera3StreamToChiStream(camera3_stream_t* inCamStreams, CHISTREAM* outChiStreams, int numStreams)
{
    for (int i = 0; i < numStreams; i++)
    {
        outChiStreams[i].streamType = static_cast<CHISTREAMTYPE>(inCamStreams[i].stream_type);
        outChiStreams[i].width = inCamStreams[i].width;
        outChiStreams[i].height = inCamStreams[i].height;
        outChiStreams[i].format = static_cast<CHISTREAMFORMAT>(inCamStreams[i].format);
        outChiStreams[i].grallocUsage = inCamStreams[i].usage;
        outChiStreams[i].maxNumBuffers = inCamStreams[i].max_buffers;
        outChiStreams[i].pPrivateInfo = inCamStreams[i].priv;
        outChiStreams[i].dataspace = static_cast<CHIDATASPACE>(inCamStreams[i].data_space);
        outChiStreams[i].rotation = static_cast<CHISTREAMROTATION>(inCamStreams[i].rotation);
#if defined(CAMX_ANDROID_API) && (CAMX_ANDROID_API >= 28) // Android-P or better
        outChiStreams[i].physicalCameraId = inCamStreams->physical_camera_id;
#endif
        outChiStreams[i].pHalStream = NULL;
        outChiStreams[i].streamParams.planeStride = 0;
        outChiStreams[i].streamParams.sliceHeight = 0;
    }
};

/**************************************************************************************************************************
*   ChiTestCase::ClearErrorNotifyFlag
*
*   @brief
*       Clears the error notify flag bits
*   @param
*       None
*   @return
*       void
**************************************************************************************************************************/
void ChiTestCase::ClearErrorNotifyFlag(uint32_t frameNum)
{
    m_errorNotifyBitFlag[frameNum % MAX_REQUESTS] &= 0;
        m_bufferErrorStreams.clear();
}

/**************************************************************************************************************************
*   ChiTestCase::CheckErrorNotifyFlag
*
*   @brief
*       Gets the desired bit from the error notify bit flag
*   @param
*       [in]   uint32_t    pos     position of the bit to get (between 0 and 31)
*   @return
*       int bit of the position requested if no error, otherwise -1
**************************************************************************************************************************/
    int ChiTestCase::CheckErrorNotifyFlag(uint32_t frameNum, uint32_t pos, CHISTREAM* pCurrentStream)
{
    if (pos <= 31)
    {
            // check if this stream had a buffer error notify
            if (pos == CHIERRORMESSAGECODE::MessageCodeBuffer)
            {
                bool found = (std::find(m_bufferErrorStreams.begin(), m_bufferErrorStreams.end(), pCurrentStream) != m_bufferErrorStreams.end());
                if (found)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        return m_errorNotifyBitFlag[frameNum % MAX_REQUESTS] & (1 << pos);
    }
    else
    {
        NT_LOG_ERROR( "Invalid error notify flag position! %u", pos);
        return -1;
    }
}

/**************************************************************************************************************************
*   ChiTestCase::SetErrorNotifyFlag
*
*   @brief
*       Gets the desired bit from the error notify bit flag
*   @param
*       [in]   uint32_t    pos     position of the bit to get (between 0 and 31)
*   @return
*       void
**************************************************************************************************************************/
    void ChiTestCase::SetErrorNotifyFlag(uint32_t frameNum, uint32_t pos, CHISTREAM* pCurrentStream)
{
    if (pos <= 31)
    {
            // maintain a list of streams for which driver sent buffer error notify
            if (pos == CHIERRORMESSAGECODE::MessageCodeBuffer)
            {
                m_bufferErrorStreams.push_back(pCurrentStream);
            }
            else
            {
        m_errorNotifyBitFlag[frameNum % MAX_REQUESTS] |= (1 << pos);
            }
    }
    else
    {
        NT_LOG_ERROR( "Invalid error notify flag position! %u", pos);
    }
}

/**************************************************************************************************************************
*   ChiTestCase::DeepCopyCaptureResult
*
*   @brief
*       Deep copies all parts of a ChiCaptureResult, allocating memory as necessary
*   @param
*       [in]    ChiCaptureResult*   pCaptureResult  capture result to deep copy
*   @return
*       ChiCaptureResult* if succeeded or NULL if failed
**************************************************************************************************************************/
ChiCaptureResult* ChiTestCase::DeepCopyCaptureResult(ChiCaptureResult* pCaptureResult)
{
    // Allocate structures
    ChiCaptureResult* pCopiedResult = SAFE_NEW() ChiCaptureResult();
#ifdef OLD_METADATA
    const VOID* pCopiedMetadata = clone_camera_metadata(
        reinterpret_cast<const camera_metadata_t*>(pCaptureResult->pResultMetadata));
#else
    CHIMETAHANDLE pCopiedInputMetadata = pCaptureResult->pInputMetadata;
    CHIMETAHANDLE pCopiedOutputMetadata = pCaptureResult->pOutputMetadata;
#endif // OLD_METADATA
    CHISTREAMBUFFER* pCopiedOutputBuffers = SAFE_NEW() CHISTREAMBUFFER[pCaptureResult->numOutputBuffers];
    CHISTREAMBUFFER* pCopiedInputBuffer = SAFE_NEW() CHISTREAMBUFFER();
    CHIPRIVDATA* pCopiedPrivData = SAFE_NEW() CHIPRIVDATA;

    // Allocate and copy PIP camera variables
#if defined(CAMX_ANDROID_API) && (CAMX_ANDROID_API >= 28) // Android-P or better
    CHAR** ppCopiedPhysCamIds = SAFE_NEW() CHAR*[pCaptureResult->numPhysCamMetadata];
    camera_metadata_t** ppCopiedPhysCamMetadata = SAFE_NEW() camera_metadata_t*[pCaptureResult->numPhysCamMetadata];

    if (NULL == ppCopiedPhysCamIds || NULL == ppCopiedPhysCamMetadata)
    {
        NT_LOG_ERROR( "Failed to allocate memory for ChiCaptureResult deep copy!");
        return NULL;
    }

    for (uint32_t i = 0; i < pCaptureResult->numPhysCamMetadata; i++)
    {
        size_t length = strlen(pCaptureResult->physCamIds[i]);
        ppCopiedPhysCamIds[i] = SAFE_NEW() CHAR[length + 1];
        ppCopiedPhysCamMetadata[i] = clone_camera_metadata(
            reinterpret_cast<const camera_metadata_t*>(pCaptureResult->physCamMetadata[i]));

        if (NULL == ppCopiedPhysCamIds[i] || NULL == ppCopiedPhysCamMetadata[i])
        {
            NT_LOG_ERROR( "Failed to allocate memory for ChiCaptureResult deep copy!");
            return NULL;
        }
        // using temp variables to convert each char* in array to string to avoid banned API strcpy
        std::string tempCopiedPhysCamId(ppCopiedPhysCamIds[i]);
        std::string tempPhysCamId(pCaptureResult->physCamIds[i]);
        tempCopiedPhysCamId = tempPhysCamId; // deep copy
        ppCopiedPhysCamIds[i] = const_cast<CHAR*>(tempCopiedPhysCamId.c_str());
    }
#endif

    // Check allocating succeeded
    if (NULL == pCopiedResult ||
#ifdef OLD_METADATA
    (NULL == pCopiedMetadata && NULL != pCaptureResult->pResultMetadata) || // May be NULL
#endif // OLD_METADATA
        NULL == pCopiedOutputBuffers ||
        NULL == pCopiedInputBuffer ||
        NULL == pCopiedPrivData)
    {
        NT_LOG_ERROR( "Failed to allocate memory for ChiCaptureResult deep copy!");
        return NULL;
    }

    // Memcpy all structures
    memcpy(pCopiedResult, pCaptureResult, sizeof(ChiCaptureResult));    // Shallow copy of capture result
    memcpy(pCopiedOutputBuffers, pCaptureResult->pOutputBuffers, sizeof(CHISTREAMBUFFER)*pCaptureResult->numOutputBuffers);
    if (NULL != pCaptureResult->pInputBuffer)   // May be NULL
    {
        memcpy(pCopiedInputBuffer, pCaptureResult->pInputBuffer, sizeof(CHISTREAMBUFFER));
    }
    memcpy(pCopiedPrivData, pCaptureResult->pPrivData, sizeof(CHIPRIVDATA));

    // Assemble copied capture result
#ifdef OLD_METADATA
    pCopiedResult->pResultMetadata = pCopiedMetadata;
#else
    pCopiedResult->pInputMetadata = pCopiedInputMetadata;
    pCopiedResult->pOutputMetadata = pCopiedOutputMetadata;
#endif // OLD_METADATA
    pCopiedResult->pOutputBuffers = pCopiedOutputBuffers;
    pCopiedResult->pInputBuffer = pCopiedInputBuffer;
#if defined(CAMX_ANDROID_API) && (CAMX_ANDROID_API >= 28) // Android-P or better
    pCopiedResult->physCamIds = const_cast<const CHAR**>(ppCopiedPhysCamIds);
    pCopiedResult->physCamMetadata = const_cast<const VOID**>(reinterpret_cast<VOID**>(ppCopiedPhysCamMetadata));
    pCopiedResult->pPrivData = pCopiedPrivData;
#endif

    return pCopiedResult;
}

/**************************************************************************************************************************
*   ChiTestCase::DeepDestroyCaptureResult
*
*   @brief
*       Destroys all parts of a ChiCaptureResult that was dynamically allocated
*   @param
*       [in]    ChiCaptureResult*   pCaptureResult  capture result to deep destroy
*   @return
*       void
**************************************************************************************************************************/
void ChiTestCase::DeepDestroyCaptureResult(ChiCaptureResult* pCaptureResult)
{
    if (NULL != pCaptureResult)
    {
        // Destroy sub-structures
#ifdef OLD_METADATA
        if (NULL != pCaptureResult->pResultMetadata)
        {
            free_camera_metadata(const_cast<camera_metadata_t*>(
                reinterpret_cast<const camera_metadata_t*>(pCaptureResult->pResultMetadata)));
        }
#endif // OLD_METADATA
        if (NULL != pCaptureResult->pOutputBuffers)
        {
            delete[] pCaptureResult->pOutputBuffers;
        }
        if (NULL != pCaptureResult->pInputBuffer)
        {
            delete pCaptureResult->pInputBuffer;
        }
#if defined(CAMX_ANDROID_API) && (CAMX_ANDROID_API >= 28) // Android-P or better
        for (uint32_t i = 0; i < pCaptureResult->numPhysCamMetadata; i++)
        {
            delete pCaptureResult->physCamIds[i];
            free_camera_metadata(const_cast<camera_metadata_t*>(
                reinterpret_cast<const camera_metadata_t*>(pCaptureResult->physCamMetadata[i])));
        }
        delete[] pCaptureResult->physCamIds;
        delete[] pCaptureResult->physCamMetadata;
#endif
        if (NULL != pCaptureResult->pPrivData)
        {
            delete static_cast<CHIPRIVDATA*>(pCaptureResult->pPrivData);
        }

        // Destroy capture result
        delete pCaptureResult;
    }
}

/**************************************************************************************************************************
*   ChiTestCase::ResetWaitForResultsRetryCount
*
*   @brief
*       Resets the retry count when waiting for results, in a thread-safe way. Used when a result comes back during the
*       wait for results period of a test.
*   @param
*       None
*   @return
*       void
**************************************************************************************************************************/
void ChiTestCase::ResetWaitForResultsRetryCount()
{
    m_pBufferCountMutex->Lock();
    m_waitForResultsRetries = 0;
    m_pBufferCountMutex->Unlock();
}

}



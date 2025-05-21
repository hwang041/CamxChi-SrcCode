//*******************************************************************************************
// Copyright (c) 2017-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*******************************************************************************************

#ifndef __CHI_TESTCASE__
#define __CHI_TESTCASE__

#include "nativetest.h"
#include "commonutils.h"
#include "chipipeline.h"
#include "chisession.h"
#include "chibuffermanager.h"
#include "chimetadatautil.h"
#include <atomic>
#include <queue>
#include <list>

#define FRAME_REQUEST_MOD(frame) (((frame) - 1) % MAX_REQUESTS)

namespace tests
{
static const int MAX_STREAMS    = 10;
static const int MAX_REQUESTS   = 8;
static const int START_FRAME    = 1;
static const int ONE_FRAME_TIME = 33000;

static const char* IPE_COLORBAR_VGA         = "ipe-unittest-input_full_vga_colorbar-1.yuv";
static const char* IPE_BARBARA_FHD_UBWCTP10 = "ipe-unittest-input_1_barbara_1920x1080_TP10.ubwc";
static const char* BPS_COLORBAR_FHD         = "bps-unittest-input_1080p_colorbar.raw"; //8-bit RAW image
static const char* BPS_MIPI_RAW_10          = "MIPI_RAW_10.raw";           //10-bit RAW HD image
static const char* BPS_MIPI_RAW_10_4K       = "MIPI_RAW_10_4656x3496.raw"; //10-bit RAW 4K image
static const char* BPS_IDEALRAW_UHD         = "bps-idealraw-input.raw";
static const char* IPE_EMULATEDSENSOR_4K    = "emulatedsensor_nv12_4096_2160.yuv";

class ChiTestCase : public NativeTest
{
public:
    virtual VOID  Setup();
    virtual VOID  Teardown();

    // Perform base class functionality for processing the capture result
    static void QueueCaptureResult(
        CHICAPTURERESULT* pResult,
        void*             pPrivateCallbackData);

    static void QueuePartialCaptureResult(
        CHIPARTIALCAPTURERESULT* pPartialResult,
        void*                    pPrivateCallbackData);

    // Perform any base class functionality for processing the message notification
    static void ProcessMessage(
        const CHIMESSAGEDESCRIPTOR* pMessageDescriptor,
        void*                       pPrivateCallbackData);

protected:

    /// Session private data
    struct SessionPrivateData
    {
        ChiTestCase* pTestInstance;    ///< Per usecase class
        uint32_t     sessionId;        ///< Session Id that is meaningful to the usecase in which the session belongs
    };

    static VOID*      ProcessCaptureResults(VOID* pArg);
    virtual void      CommonProcessCaptureResult(CHICAPTURERESULT* pResult, SessionPrivateData* pPrivateCallbackData);
    virtual CDKResult WaitForResults();
    // @brief functions to be implemented by derived class
    virtual CDKResult SetupStreams() = 0;
    virtual CDKResult SetupPipelines(int cameraId, ChiSensorModeInfo* sensorMode) = 0;
    virtual CDKResult CreateSessions() = 0;
    virtual void      DestroyResources() = 0;

    CDKResult         InitializeBufferMangers(int cameraId);
    void              DestroyCommonResources();
    void              AtomicIncrement(int count = 1);
    void              AtomicDecrement(int count = 1);
    uint32_t          GetPendingBufferCount() const;
    static bool       IsRDIStream(CHISTREAMFORMAT format);
    void              ConvertCamera3StreamToChiStream(camera3_stream_t* inCamStreams, CHISTREAM* outChiStreams, int numStreams);

    void              ClearErrorNotifyFlag(uint32_t frameNum);
        int               CheckErrorNotifyFlag(uint32_t frameNum, uint32_t pos, CHISTREAM* pCurrentStream = NULL);

    // making constructor default since Setup() will take care of initializing
    ChiTestCase() = default;
    // making destructor default since Teardown() will take care of destroying
    ~ChiTestCase() = default;

    /* StreamCreateData structure and memory allocated for its variables */
    bool                     m_isCamIFTestGen;                // set true if the test is camif test gen based
    StreamCreateData         m_streamInfo;                    // stream info required for creating stream objects
    int                      m_numStreams;                    // total number of streams for given testcase
    CHISTREAMFORMAT          m_format[MAX_STREAMS];           // format for the streams
    CHISTREAMTYPE            m_direction[MAX_STREAMS];        // stream direction
    Size                     m_resolution[MAX_STREAMS];       // resolution for the streams
    StreamUsecases           m_streamId[MAX_STREAMS];         // unique identifier for the streams
    uint32_t                 m_usageFlag[MAX_STREAMS];        // gralloc usage flags for the streams
    bool                     m_isRealtime[MAX_STREAMS];       // bool to indicate if this stream is part of realtime session


    ChiStream*               m_pRequiredStreams;              // pointer to created stream objects
    BufferManager*           m_pBufferManagers[MAX_STREAMS];  // pointer to buffermanagers for each stream
    ChiModule*               m_pChiModule;                    // pointer to the ChiModule singleton
    ChiMetadataUtil*         m_pChiMetadataUtil;              // pointer to chi metadata util singleton
    std::map<ChiStream*, BufferManager*> m_streamBufferMap;   // map storing stream and it's associated buffermanager
    std::map<StreamUsecases, ChiStream*> m_streamIdMap;       // map storing unique streamId and stream object

        static std::list<ChiStream*> m_bufferErrorStreams;        // list of stream pointers for which driver sent buffer error notify

                                                              /* Process Capture Result Task Offloading */
    static std::queue<ChiCaptureResult*>    m_pResultsToProcess;        // queue of capture results that need to be processed
    static std::queue<SessionPrivateData*>  m_pPrivateDataToProcess;    // queue of private data associated with a capture result

                                                                        /* Metadata getters */
    static inline const VOID* GetInputMetadata(CHICAPTUREREQUEST* pRequest)
    {
#ifdef OLD_METADATA
        return pRequest->pMetadata;
#else
        return pRequest->pInputMetadata;
#endif // OLD_METADATA
    }
    static inline const VOID* GetOutputMetadata(CHICAPTURERESULT* pResult)
    {
#ifdef OLD_METADATA
        return pResult->pResultMetadata;
#else
        return pResult->pOutputMetadata;
#endif // OLD_METADATA
    }

private:
    std::atomic<uint32_t>    m_buffersRemaining;              // pending number of buffers
    Mutex*                   m_pBufferCountMutex;             // mutex associated with buffer remaining
    static Condition*        m_pBufferCountCond;              // cond variable to signal/wait on buffer remaining
    static Mutex*            m_pResultQueueMutex;             // mutex for accessing capture result and private data queues

                                                              /* Wait for results helpers */
    int                      m_waitForResultsRetries;         // number of tries NativeChiTest has waited for result
    void                     ResetWaitForResultsRetryCount(); // resets the number of retries waiting for result

                                                              /* Error notify flags (used for flush tests) */
    static uint32_t          m_errorNotifyBitFlag[MAX_REQUESTS];                    // bits to encode which notify errors were received
        static void              SetErrorNotifyFlag(uint32_t frameNum, uint32_t pos, CHISTREAM* pCurrentStream = NULL);   // set a bit of the error notify flag

                                                                                    /* Capture result copy and destroy operations */
    static ChiCaptureResult* DeepCopyCaptureResult(ChiCaptureResult* pCaptureResult);       // Copies all parts of the capture result
    static void              DeepDestroyCaptureResult(ChiCaptureResult* pCaptureResult);    // Destroys all parts of the capture result

                                                                                            /* Processing capture results */
    enum ProcessSignal
    {
        SignalReady,
        SignalProcess,
        SignalDone
    };
    OSThreadHandle          m_processingThread;     // worker thread in charge of processing capture results when signaled by main thread
    static ProcessSignal    m_processingSignaler;   // enum to help signal/command the processing thread
    static Mutex*           m_pProcessingMutex;     // mutex to protect the signaler
    static Condition*       m_pProcessingCond;      // condition to help coordinate between main and processing thread
    static void             SignalProcessingThread(ProcessSignal signal);   // Signals processing thread to perform a task

                                                                            // Do not allow the copy constructor or assignment operator
    ChiTestCase(const ChiTestCase& rUsecase) = delete;
    ChiTestCase& operator= (const ChiTestCase& rUsecase) = delete;
};

} // namespace tests

#endif  //#ifndef __CHI_TESTCASE__

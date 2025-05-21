//******************************************************************************************************************************
// Copyright (c) 2016-2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//******************************************************************************************************************************
//==============================================================================================================================
// IMPLEMENTATION of ChiSession
//==============================================================================================================================

#include "chisession.h"

namespace tests
{

/***************************************************************************************************************************
*   ChiSession::ChiSession
*
*   @brief
*       Constructor for ChiSession
***************************************************************************************************************************/
ChiSession::ChiSession()
{
    m_hSession = nullptr;
    m_pChiModule = ChiModule::GetInstance();
    if (nullptr == m_pChiModule) {
        NT_LOG_ERROR("ChiModule could not be instantiated");
    }
}

/***************************************************************************************************************************
*   ChiSession::~ChiSession
*
*   @brief
*       Destructor for ChiSession
***************************************************************************************************************************/
ChiSession::~ChiSession()
{
    m_hSession = nullptr;
    m_pChiModule = ChiModule::GetInstance();
    if (nullptr == m_pChiModule) {
        NT_LOG_ERROR("ChiModule could not be instantiated");
    }
}

/***************************************************************************************************************************
*   ChiSession::Create
*
*   @brief
*       static function to create an instance of the chisession
*   @param
*        [in]  ChiPipeline**   ppPipelines    pointer to all created pipelines
*        [in]  int             numPipelines   number of pipelines present for the session
*        [in]  ChiCallBacks*   pCallbacks     callback function for driver to return the result
*        [in]  void*           pPrivateData   pointer to privatedata specific to the testcase
*   @return
*       ChiSession*  instance to the newly created session
***************************************************************************************************************************/
ChiSession* ChiSession::Create(ChiPipeline** ppPipelines, int numPipelines, ChiCallBacks* pCallbacks, void* pPrivateData)
{
    CDKResult result = CDKResultSuccess;
    ChiSession* pNewSession = SAFE_NEW() ChiSession();

    if (pNewSession != nullptr)
    {
        result = pNewSession->Initialize(ppPipelines, numPipelines, pCallbacks, pPrivateData);

        if (result != CDKResultSuccess)
        {
            delete pNewSession;
            pNewSession = nullptr;
        }
    }

    return pNewSession;
}

/***************************************************************************************************************************
*   ChiSession::Initialize
*
*   @brief
*       member function to initialize newly created instance of the chisession
*   @param
*        [in]  ChiPipeline**   ppPipelines    pointer to all created pipelines
*        [in]  int             numPipelines   number of pipelines present for the session
*        [in]  ChiCallBacks*   pCallbacks     callback function for driver to return the result
*        [in]  void*           pPrivateData   pointer to privatedata specific to the testcase
*   @return
*       CDKResult  result code to determine outcome of the function
***************************************************************************************************************************/
CDKResult ChiSession::Initialize(ChiPipeline** ppPipelines, int numPipelines, ChiCallBacks* pCallbacks, void* pPrivateData)
{
    CDKResult         result = CDKResultSuccess;

    memset(&m_sessionCreateData, 0, sizeof(SessionCreateData));   // Zero out session create data
    m_sessionCreateData.numPipelines = numPipelines;
    m_sessionCreateData.pCallbacks = pCallbacks;
    m_sessionCreateData.pPrivateCallbackData = pPrivateData;

    if (numPipelines > MaxPipelinesPerSession)
    {
        NT_LOG_ERROR( "Session cannot have more than %d pipelines", MaxPipelinesPerSession);
        return CDKResultEFailed;
    }

    for (int i = 0; i < numPipelines; i++)
    {
        m_sessionCreateData.pPipelineInfos[i] = ppPipelines[i]->GetPipelineInfo();
    }

    m_hSession = CreateSession(&m_sessionCreateData);

   NT_LOG_DEBUG( "Created session handle: %p", m_hSession);

    if (NULL == m_hSession)
    {
        result = CDKResultEFailed;
    }

    return result;
}

/***************************************************************************************************************************
*   ChiSession::CreateSession
*
*   @brief
*       Create a chi session based on the given parameters
*   @param
*     [in]  SessionCreateData*   pSessionCreate     pointer to SessionCreateData structure
*   @return
*       CHIHANDLE    handle to the created session
***************************************************************************************************************************/
CHIHANDLE ChiSession::CreateSession(SessionCreateData* pSessionCreate)
{
    ChiModule* pChiModule = ChiModule::GetInstance();
    if (nullptr == pChiModule) {
        NT_LOG_ERROR("ChiModule could not be instantiated");
        return NULL;
    }

    NT_LOG_INFO( "Creating session on context: %p", pChiModule->GetContext());
    CHISESSIONFLAGS flags;
    flags.u.isNativeChi = 1;
    NT_LOG_DEBUG( "ChiContext = %p, PipelineInfo = %p, Callback = %p", pChiModule->GetContext(),
        pSessionCreate->pPipelineInfos, pSessionCreate->pCallbacks);

    return pChiModule->GetChiOps()->pCreateSession(
        pChiModule->GetContext(),
        pSessionCreate->numPipelines,
        pSessionCreate->pPipelineInfos,
        pSessionCreate->pCallbacks,
        pSessionCreate->pPrivateCallbackData,
        flags);
}

/***************************************************************************************************************************
*   ChiSession::GetSessionHandle
*
*   @brief
*       return the created session handle
*   @return
*       CHIHANDLE created session handle
***************************************************************************************************************************/
CHIHANDLE ChiSession::GetSessionHandle() const
{
    return m_hSession;
}

/***************************************************************************************************************************
*   ChiSession::FlushSession
*
*   @brief
*       Flush the session
*   @return
*       CDKResult
***************************************************************************************************************************/
CDKResult ChiSession::FlushSession() const
{
    // passing session handle through flush session info for pipeline flush imeplementation
    CHISESSIONFLUSHINFO hSessionFlushInfo = { 0 };
    hSessionFlushInfo.pSessionHandle = m_hSession;

    NT_LOG_INFO( "Flushing session: %p on context: %p", m_hSession, m_pChiModule->GetContext());
    return m_pChiModule->GetChiOps()->pFlushSession(m_pChiModule->GetContext(), hSessionFlushInfo);
}

/***************************************************************************************************************************
*   ChiSession::DestroySession
*
*   @brief
*       Destroy session
*   @return
*      none
***************************************************************************************************************************/
void ChiSession::DestroySession() const
{
    NT_LOG_INFO( "Destroying session: %p on context: %p", m_hSession, m_pChiModule->GetContext());
    m_pChiModule->GetChiOps()->pDestroySession(m_pChiModule->GetContext(), m_hSession, false);
    delete this;
}
}

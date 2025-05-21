//*************************************************************************************************
// Copyright (c) 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*************************************************************************************************

#ifndef __CHI_SESSION__
#define __CHI_SESSION__

#include "chipipeline.h"
#include "chimodule.h"

namespace tests {

class ChiSession
{

public:

    static ChiSession* Create(ChiPipeline** ppPipelines, int numPipelines, ChiCallBacks* pCallbacks, void* pPrivateData);
    CDKResult          Initialize(ChiPipeline** ppPipelines, int numPipelines, ChiCallBacks* pCallbacks, void* pPrivateData);
    static CHIHANDLE   CreateSession(SessionCreateData* pSessionCreate);
    CHIHANDLE          GetSessionHandle() const;
    CDKResult          FlushSession() const;
    void               DestroySession() const;

private:
    CHIHANDLE              m_hSession;  // created session handle
    SessionCreateData      m_sessionCreateData; // data required for session creation
    ChiModule*             m_pChiModule; // pointer to the ChiModule singleton

    ChiSession();
    ~ChiSession();

    /// Do not allow the copy constructor or assignment operator
    ChiSession(const ChiSession&) = delete;
    ChiSession& operator= (const ChiSession&) = delete;
};

} //namespace tests

#endif  //#ifndef __CHI_SESSION_
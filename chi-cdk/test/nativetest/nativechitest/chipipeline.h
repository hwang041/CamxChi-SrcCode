//*************************************************************************************************
// Copyright (c) 2019 Qualcomm Technologies, Inc.
// All Rights Reserved.
// Confidential and Proprietary - Qualcomm Technologies, Inc.
//*************************************************************************************************

#ifndef __CHI_PIPELINE__
#define __CHI_PIPELINE__

#include "chipipelineutils.h"
#include "chimodule.h"
#include "nativetestlog.h"
#include "camera3stream.h"

namespace tests {

class ChiPipeline
{

public:

    static ChiPipeline*  Create(int cameraId,
        CHISENSORMODEINFO* sensorMode,
        std::map<StreamUsecases, ChiStream*> streamIdMap,
        PipelineType type);

    CDKResult            Initialize(int cameraId,
        CHISENSORMODEINFO* sensorMode,
        std::map<StreamUsecases, ChiStream*> streamIdMap,
        PipelineType type);

    CDKResult            CreatePipelineDesc();
    CHIPIPELINEINFO      GetPipelineInfo() const;
    CDKResult            ActivatePipeline(CHIHANDLE hSession) const;
    CDKResult            DeactivatePipeline(CHIHANDLE hSession) const;
    void                 DestroyPipeline();
    CHIPIPELINEHANDLE    GetPipelineHandle() const;

private:
    ChiModule*            m_pChiModule;          // pointer to the ChiModule singleton
    PipelineUtils         m_PipelineUtils;       // instance to pipeline utils for creating pipelines
    CHIPIPELINEDESCRIPTOR m_createdPipeline;     // pipeline descriptor of created pipeline
    PipelineCreateData    m_pipelineCreateData;  // pipeline data required for creating pipeline
    CHIPIPELINEINFO       m_pipelineInfo;        // struct containing pipeline info
    int                   m_cameraId;            // cameraId for the pipeline
    CHISENSORMODEINFO*    m_selectedSensorMode;  // sensor mode to be used for the pipeline

    ChiPipeline();
    ~ChiPipeline();

    /// Do not allow the copy constructor or assignment operator
    ChiPipeline(const ChiPipeline&) = delete;
    ChiPipeline& operator= (const ChiPipeline&) = delete;

};

} //namespace tests

#endif  //#ifndef __CHI_PIPELINE__
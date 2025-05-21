 //*******************************************************************************
 // Copyright (c) 2016-2019 Qualcomm Technologies, Inc.
 // All Rights Reserved.
 // Confidential and Proprietary - Qualcomm Technologies, Inc.
 //*******************************************************************************

#include "nativetest.h"
#include "cmdlineparser.h"
#include "nativetestlog.h"
#include "binary_comp_test.h"
#include "camera_module_test.h"
#include "camera_manager_test.h"
#include "chimetadata_test.h"
#include "custom_node_test.h"
#include "chimetadata_test.h"
#include "flush_test.h"
#include "mixed_pipeline_test.h"
#include "offline_pipeline_test.h"
#include "pip_camera_test.h"
#include "realtime_pipeline_test.h"
#include "recipe_test.h"

namespace tests
{

    /* Register Testcases */

    // Basic testcase for number of cameras on device
    NATIVETEST_TEST(CameraModuleTest,  TestNumberOfCamera)                 { TestNumberOfCamera(); }
    NATIVETEST_TEST(CameraModuleTest,  TestStaticCameraInfoAndMetadata)    { TestStaticCameraInfoAndMetadata(); }

    NATIVETEST_TEST(CameraManagerTest, TestOpenInvalidCamera)              { TestOpenInvalidCamera(); }
    NATIVETEST_TEST(CameraManagerTest, TestOpenCloseContext)               { TestOpenCloseContextSerially(); }

    // Custom node tests
    NATIVETEST_TEST(CustomNodeTest, TestVendorTagWrite)                   { TestCustomNode(TestVendorTagWrite); }

    // Chimetadata tests
    NATIVETEST_TEST(ChiMetadataTest, TestCreateMetadata)                  { TestCreateMetadata(); }
    NATIVETEST_TEST(ChiMetadataTest, TestCreateDefaultMetadata)           { TestCreateDefaultMetadata(); }
    NATIVETEST_TEST(ChiMetadataTest, TestCreateWithAndroidMetadata)       { TestCreateWithAndroidMetadata(); }
    NATIVETEST_TEST(ChiMetadataTest, TestSetTag)                          { TestSetTag(); }
    NATIVETEST_TEST(ChiMetadataTest, TestGetTag)                          { TestGetTag(); }
    NATIVETEST_TEST(ChiMetadataTest, TestCreateWithTagArray)              { TestCreateWithTagArray(); }
    NATIVETEST_TEST(ChiMetadataTest, TestDump)                            { TestDump(); }
    NATIVETEST_TEST(ChiMetadataTest, TestPrint)                           { TestPrint(); }
    NATIVETEST_TEST(ChiMetadataTest, TestGetMetadataOps)                  { TestGetMetadataOps(); }
    NATIVETEST_TEST(ChiMetadataTest, TestGetTagCount)                     { TestGetTagCount(); }
    NATIVETEST_TEST(ChiMetadataTest, TestGetMetadataEntry)                { TestGetMetadataEntry(); }
    NATIVETEST_TEST(ChiMetadataTest, TestDeleteTag)                       { TestDeleteTag(); }
    NATIVETEST_TEST(ChiMetadataTest, TestVendorTagOps)                    { TestVendorTagOps(); }
    NATIVETEST_TEST(ChiMetadataTest, TestMergeDisjoint)                   { TestMergeDisjoint(); }
    NATIVETEST_TEST(ChiMetadataTest, TestMerge)                           { TestMerge(); }
    NATIVETEST_TEST(ChiMetadataTest, TestCopy)                            { TestCopy(); }
    NATIVETEST_TEST(ChiMetadataTest, TestClone)                           { TestClone(); }
    NATIVETEST_TEST(ChiMetadataTest, TestCopyDisjoint)                    { TestCopyDisjoint(); }
    NATIVETEST_TEST(ChiMetadataTest, TestCapacity)                        { TestCapacity(); }
    NATIVETEST_TEST(ChiMetadataTest, TestGetMetadataTable)                { TestGetMetadataTable(); }
    NATIVETEST_TEST(ChiMetadataTest, TestIterator)                        { TestIterator(); }
    NATIVETEST_TEST(ChiMetadataTest, TestMetadataReference)               { TestMetadataReference(); }
    NATIVETEST_TEST(ChiMetadataTest, TestInvalidate)                      { TestInvalidate(); }
    NATIVETEST_TEST(ChiMetadataTest, TestCopyPerformance)                 { TestCopyPerformance(); }
    NATIVETEST_TEST(ChiMetadataTest, TestMergePerformance)                { TestMergePerformance(); }
    NATIVETEST_TEST(ChiMetadataTest, TestDestroyMetadata)                 { TestDestroyMetadata(); }

    // Realtime pipeline test cases
    NATIVETEST_TEST(RealtimePipelineTest, TestIPEFull)                    { TestRealtimePipeline(TestIPEFull); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIFEFull)                    { TestRealtimePipeline(TestIFEFull); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIFEFull3A)                  { TestRealtimePipeline(TestIFEFull3A); }
    NATIVETEST_TEST(RealtimePipelineTest, TestPreviewHVX)                 { TestRealtimePipeline(TestPreviewHVX); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIFERDI0RawOpaque)           { TestRealtimePipeline(TestIFERDI0RawOpaque); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIFERDI0RawOpaqueTestgen)    { TestRealtimePipeline(TestIFERDI0RawOpaqueTestgen); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIFERDI0RawPlain16)          { TestRealtimePipeline(TestIFERDI0RawPlain16); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIFERawCamif)                { TestRealtimePipeline(TestIFERawCamif); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIFERawLsc)                  { TestRealtimePipeline(TestIFERawLsc); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIFERDI0Raw10Testgen)        { TestRealtimePipeline(TestIFERDI0Raw10Testgen); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIFEFullTestgen)             { TestRealtimePipeline(TestIFEFullTestgen); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIPEFullTestgen)             { TestRealtimePipeline(TestIPEFullTestgen); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIFEFullStatsTestgen)        { TestRealtimePipeline(TestIFEFullStatsTestgen); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIFEFullStats)               { TestRealtimePipeline(TestIFEFullStats); }
    NATIVETEST_TEST(RealtimePipelineTest, TestRealtimePrevRDI)            { TestRealtimePipeline(TestRealtimePrevRDI); }
    NATIVETEST_TEST(RealtimePipelineTest, TestPrevRDITestgen)             { TestRealtimePipeline(TestPrevRDITestgen); }
    NATIVETEST_TEST(RealtimePipelineTest, TestRealtimePrevWith3AWrappers) { TestRealtimePipeline(TestRealtimePrevWith3AWrappers); }
    NATIVETEST_TEST(RealtimePipelineTest, TestRealtimePrevWithCallback)   { TestRealtimePipeline(TestRealtimePrevWithCallback); }
    NATIVETEST_TEST(RealtimePipelineTest, TestPreviewWithMemcpy)          { TestRealtimePipeline(TestPreviewWithMemcpy); }
    NATIVETEST_TEST(RealtimePipelineTest, TestPreviewFromMemcpy)          { TestRealtimePipeline(TestPreviewFromMemcpy); }
    NATIVETEST_TEST(RealtimePipelineTest, TestBypassNode)                 { TestRealtimePipeline(TestBypassNodeMemcpy); }

    NATIVETEST_TEST(RealtimePipelineTest, TestIPEATestgen)                { TestRealtimePipeline(TestIPEATestgen); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIPEABTestgen)               { TestRealtimePipeline(TestIPEABTestgen); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIPEABStatsTestgen)          { TestRealtimePipeline(TestIPEABStatsTestgen); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIPEABCStatsTestgen)         { TestRealtimePipeline(TestIPEABCStatsTestgen); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIPE3ATestgen)               { TestRealtimePipeline(TestIPE3ATestgen); }

    NATIVETEST_TEST(RealtimePipelineTest, TestIPEAExternal)               { TestRealtimePipeline(TestIPEATestgen, true); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIPEABExternal)              { TestRealtimePipeline(TestIPEABTestgen, true); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIPEABStatsExternal)         { TestRealtimePipeline(TestIPEABStatsTestgen, true); }
    NATIVETEST_TEST(RealtimePipelineTest, TestIPEABCStatsExternal)        { TestRealtimePipeline(TestIPEABCStatsTestgen, true); }

    NATIVETEST_TEST(RealtimePipelineTest, TestCVPDME)                     { TestRealtimePipeline(TestCVPDME, true); }
    NATIVETEST_TEST(RealtimePipelineTest, TestCVPDMEDisplayPort)          { TestRealtimePipeline(TestCVPDMEDisplayPort, true); }
    NATIVETEST_TEST(RealtimePipelineTest, TestCVPDMEICA)                  { TestRealtimePipeline(TestCVPDMEICA, true); }

    // Offline pipeline test cases
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12DisplayNV12)              { TestOfflinePipeline(TestIPEInputNV12DisplayNV12); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12DisplayUBWCTP10)          { TestOfflinePipeline(TestIPEInputNV12DisplayUBWCTP10); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12DisplayUBWCNV12)          { TestOfflinePipeline(TestIPEInputNV12DisplayUBWCNV12); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputYUVOutputJPEG)                { TestOfflinePipeline(TestIPEInputYUVOutputJPEG); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12VideoNV12)                { TestOfflinePipeline(TestIPEInputNV12VideoNV12); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12VideoUBWCNV12)            { TestOfflinePipeline(TestIPEInputNV12VideoUBWCNV12); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12VideoUBWCTP10)            { TestOfflinePipeline(TestIPEInputNV12VideoUBWCTP10); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12DisplayVideoNV12)         { TestOfflinePipeline(TestIPEInputNV12DisplayVideoNV12); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12DisplayVideoUBWCNV12)     { TestOfflinePipeline(TestIPEInputNV12DisplayVideoUBWCNV12); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12DisplayVideoUBWCTP10)     { TestOfflinePipeline(TestIPEInputNV12DisplayVideoUBWCTP10); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12DisplayNV12VideoUBWCNV12) { TestOfflinePipeline(TestIPEInputNV12DisplayNV12VideoUBWCNV12); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12DisplayUBWCNV12VideoNV12) { TestOfflinePipeline(TestIPEInputNV12DisplayUBWCNV12VideoNV12); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12DisplayNV12VideoUBWCTP10) { TestOfflinePipeline(TestIPEInputNV12DisplayNV12VideoUBWCTP10); }
    NATIVETEST_TEST(OfflinePipelineTest, TestIPEInputNV12DisplayUBWCTP10VideoNV12) { TestOfflinePipeline(TestIPEInputNV12DisplayUBWCTP10VideoNV12); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputRaw16OutFullUBWCTP10)         { TestOfflinePipeline(TestBPSInputRaw16OutFullUBWCTP10); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputRaw10OutFullUBWCTP10)         { TestOfflinePipeline(TestBPSInputRaw10OutFullUBWCTP10); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputRaw16IPEDispNV12)             { TestOfflinePipeline(TestBPSInputRaw16IPEDispNV12); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputRaw16IPEJpeg)                 { TestOfflinePipeline(TestBPSInputRaw16IPEJpeg); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputRaw16IPEDispUBWCNV12)         { TestOfflinePipeline(TestBPSInputRaw16IPEDispUBWCNV12); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputRaw16IPEDispUBWCTP10)         { TestOfflinePipeline(TestBPSInputRaw16IPEDispUBWCTP10); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputRaw16StatsOut)                { TestOfflinePipeline(TestBPSInputRaw16StatsOut); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputFHDRaw16StatsOut)             { TestOfflinePipeline(TestBPSInputFHDRaw16StatsOut); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputUHDRaw16StatsOutWithIPE)      { TestOfflinePipeline(TestBPSInputUHDRaw16StatsOutWithIPE); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputFHDRaw16StatsOutWithIPE)      { TestOfflinePipeline(TestBPSInputFHDRaw16StatsOutWithIPE); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputFHDRaw16BGStatsWithIPE)       { TestOfflinePipeline(TestBPSInputFHDRaw16BGStatsWithIPE); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputUHDRaw16BGStatsWithIPE)       { TestOfflinePipeline(TestBPSInputUHDRaw16BGStatsWithIPE); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputFHDRaw16HistStatsWithIPE)     { TestOfflinePipeline(TestBPSInputFHDRaw16HistStatsWithIPE); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputUHDRaw16HistStatsWithIPE)     { TestOfflinePipeline(TestBPSInputUHDRaw16HistStatsWithIPE); }
    NATIVETEST_TEST(OfflinePipelineTest, TestJPEGInputNV12VGAOutputBlob)           { TestOfflinePipeline(TestJPEGInputNV12VGAOutputBlob); }
    NATIVETEST_TEST(OfflinePipelineTest, TestJPEGInputNV124KOutputBlob)            { TestOfflinePipeline(TestJPEGInputNV124KOutputBlob); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputRaw16OutputGPUPorts)          { TestOfflinePipeline(TestBPSInputRaw16OutputGPUPorts); }
    NATIVETEST_TEST(OfflinePipelineTest, TestFDInputNV12VGAOutputBlob)             { TestOfflinePipeline(TestFDInputNV12VGAOutputBlob); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputRaw16WithIPEAndDS)            { TestOfflinePipeline(TestBPSInputRaw16WithIPEAndDS); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSInputRaw10WithIPEAndDS)            { TestOfflinePipeline(TestBPSInputRaw10WithIPEAndDS); }
    NATIVETEST_TEST(OfflinePipelineTest, TestBPSIdealRaw)                          { TestOfflinePipeline(TestBPSIdealRaw); }

    // binary compatability tests
    NATIVETEST_TEST(BinaryCompatibilityTest, TestCHIVENDORTAGSOPS)                 { TestCHIVENDORTAGSOPS(); }
    NATIVETEST_TEST(BinaryCompatibilityTest, TestCHICAMERAINFO)                    { TestCHICAMERAINFO(); }
    NATIVETEST_TEST(BinaryCompatibilityTest, TestCHISENSORMODEINFO)                { TestCHISENSORMODEINFO(); }
    NATIVETEST_TEST(BinaryCompatibilityTest, TestCHIPIPELINECREATEDESCRIPTOR)      { TestCHIPIPELINECREATEDESCRIPTOR(); }
    NATIVETEST_TEST(BinaryCompatibilityTest, TestCHIPORTBUFFERDESCRIPTOR)          { TestCHIPORTBUFFERDESCRIPTOR(); }
    NATIVETEST_TEST(BinaryCompatibilityTest, TestCHIBUFFEROPTIONS)                 { TestCHIBUFFEROPTIONS(); }
    NATIVETEST_TEST(BinaryCompatibilityTest, TestCHIPIPELINEINFO)                  { TestCHIPIPELINEINFO(); }
    NATIVETEST_TEST(BinaryCompatibilityTest, TestCHICALLBACKS)                     { TestCHICALLBACKS(); }
    NATIVETEST_TEST(BinaryCompatibilityTest, TestCHIPIPELINEREQUEST)               { TestCHIPIPELINEREQUEST(); }

    // Mixed pipeline test cases
    NATIVETEST_TEST(MixedPipelineTest, TestPreviewZSLYuvSnapshot)                  { TestMixedPipelineTest(PreviewZSLYuvSnapshot); }
    NATIVETEST_TEST(MixedPipelineTest, TestPreviewZSLJpegSnapshot)                 { TestMixedPipelineTest(PreviewZSLJpegSnapshot); }
    NATIVETEST_TEST(MixedPipelineTest, TestPreviewZSLYuvSnapshotWithStats)         { TestMixedPipelineTest(PreviewZSLYuvSnapshotWithStats); }
    NATIVETEST_TEST(MixedPipelineTest, TestPreviewZSLJpegSnapshotWithStats)        { TestMixedPipelineTest(PreviewZSLJpegSnapshotWithStats); }
    NATIVETEST_TEST(MixedPipelineTest, TestPreviewNZSLYuvSnapshot)                 { TestMixedPipelineTest(PreviewZSLYuvSnapshot); }
    NATIVETEST_TEST(MixedPipelineTest, TestPreviewNZSLJpegSnapshot)                { TestMixedPipelineTest(PreviewZSLJpegSnapshot); }
    NATIVETEST_TEST(MixedPipelineTest, TestPreviewNZSLYuvSnapshotWithStats)        { TestMixedPipelineTest(PreviewZSLYuvSnapshotWithStats); }
    NATIVETEST_TEST(MixedPipelineTest, TestPreviewNZSLJpegSnapshotWithStats)       { TestMixedPipelineTest(PreviewZSLJpegSnapshotWithStats); }
    NATIVETEST_TEST(MixedPipelineTest, TestPreviewCallbackSnapshotWithThumbnail)   { TestMixedPipelineTest(TestPreviewCallbackSnapshotWithThumbnail); }
    NATIVETEST_TEST(MixedPipelineTest, TestLiveVideoSnapShot)                      { TestMixedPipelineTest(LiveVideoSnapShot); }
    NATIVETEST_TEST(MixedPipelineTest, TestIPEABCStatsTestgenOfflineJPEG)          { TestMixedPipelineTest(TestIPEABCStatsTestgenOfflineJPEG); }
    NATIVETEST_TEST(MixedPipelineTest, TestIPEABCStatsTestgenOfflineYUV)           { TestMixedPipelineTest(TestIPEABCStatsTestgenOfflineYUV); }
    NATIVETEST_TEST(MixedPipelineTest, TestIPEABCStatsTestgenOfflineRaw)           { TestMixedPipelineTest(TestIPEABCStatsTestgenOfflineRaw); }
    NATIVETEST_TEST(MixedPipelineTest, TestIPEABCStatsExternalOfflineJPEG)         { TestMixedPipelineTest(TestIPEABCStatsTestgenOfflineJPEG, true); }
    NATIVETEST_TEST(MixedPipelineTest, TestIPEABCStatsExternalOfflineYUV)          { TestMixedPipelineTest(TestIPEABCStatsTestgenOfflineYUV, true); }
    NATIVETEST_TEST(MixedPipelineTest, TestIPEABCStatsExternalOfflineRaw)          { TestMixedPipelineTest(TestIPEABCStatsTestgenOfflineRaw, true); }
    NATIVETEST_TEST(MixedPipelineTest, TestIPEABCStatsOfflineJPEG)                 { TestMixedPipelineTest(TestIPEABCStatsOfflineJPEG); }
    NATIVETEST_TEST(MixedPipelineTest, TestIPEABCStatsOfflineYUV)                  { TestMixedPipelineTest(TestIPEABCStatsOfflineYUV); }
    NATIVETEST_TEST(MixedPipelineTest, TestIPEABCStatsOfflineRaw)                  { TestMixedPipelineTest(TestIPEABCStatsOfflineRaw); }

    // Picture-in-picture tests
    NATIVETEST_TEST(PIPCameraTest, TestStillPreview)                 { TestPIPCamera(TestStillPreview); }
    NATIVETEST_TEST(PIPCameraTest, TestStillCapture)                 { TestPIPCamera(TestStillCapture); }
    NATIVETEST_TEST(PIPCameraTest, TestVideo)                        { TestPIPCamera(TestVideo); }

    /* Recipe Test Suite*/
    // Single output stream tests with configurable resolution, output format and output port
    NATIVETEST_TEST(RecipeTest, TestIFEGeneric) { TestRealtimePipeline(TestIFEGeneric); }
    NATIVETEST_TEST(RecipeTest, TestIFEGenericTestgen) { TestRealtimePipeline(TestIFEGenericTestgen); }
    NATIVETEST_TEST(RecipeTest, TestIPEGeneric) { TestOfflinePipeline(TestIPEGeneric); }
    NATIVETEST_TEST(RecipeTest, TestBPSGeneric) { TestOfflinePipeline(TestBPSGeneric); }

    // Single output stream tests with configurable resolution, output format and fixed output Downscale ports
    NATIVETEST_TEST(RecipeTest, TestBPSDownscaleGeneric) { TestOfflinePipeline(TestBPSDownscaleGeneric); }
    NATIVETEST_TEST(RecipeTest, TestIFEDownscaleGenericTestgen) { TestRealtimePipeline(TestIFEDownscaleGenericTestgen); }

    // Double output stream tests (static + configurable); configurable resolution, output format, output port
    NATIVETEST_TEST(RecipeTest, TestIFEGeneric2Stream) { TestRealtimePipeline(TestIFEGeneric2Stream); }
    NATIVETEST_TEST(RecipeTest, TestIFEGeneric2StreamTestgen) { TestRealtimePipeline(TestIFEGeneric2StreamTestgen); }
    NATIVETEST_TEST(RecipeTest, TestIFEGeneric2StreamDisplay) { TestRealtimePipeline(TestIFEGeneric2StreamDisplay); }
    NATIVETEST_TEST(RecipeTest, TestIFEGeneric2StreamDisplayTestgen) { TestRealtimePipeline(TestIFEGeneric2StreamDisplayTestgen); }
    NATIVETEST_TEST(RecipeTest, TestIPEGeneric2StreamDisplay) { TestOfflinePipeline(TestIPEGeneric2StreamDisplay); }
    NATIVETEST_TEST(RecipeTest, TestBPSGeneric2Stream) { TestOfflinePipeline(TestBPSGeneric2Stream); }


    // Flush Realtime Tests
    NATIVETEST_TEST(FlushTest, FlushNodeIFE)                         { TestRealtimeFlush(FlushNodeIFE, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueIFE)                        { TestRealtimeFlush(FlushQueueIFE, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverIFE)                      { TestRealtimeFlush(FlushRecoverIFE, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeStats3A)                     { TestRealtimeFlush(FlushNodeStats3A, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueStats3A)                    { TestRealtimeFlush(FlushQueueStats3A, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverStats3A)                  { TestRealtimeFlush(FlushRecoverStats3A, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeIPEJpeg)                     { TestRealtimeFlush(FlushNodeIPEJpeg, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueIPEJpeg)                    { TestRealtimeFlush(FlushQueueIPEJpeg, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverIPEJpeg)                  { TestRealtimeFlush(FlushRecoverIPEJpeg, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeBPSIPEJpeg)                  { TestRealtimeFlush(FlushNodeBPSIPEJpeg, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueBPSIPEJpeg)                 { TestRealtimeFlush(FlushQueueBPSIPEJpeg, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverBPSIPEJpeg)               { TestRealtimeFlush(FlushRecoverBPSIPEJpeg, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeFD)                          { TestRealtimeFlush(FlushNodeFD, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueFD)                         { TestRealtimeFlush(FlushQueueFD, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverFD)                       { TestRealtimeFlush(FlushRecoverFD, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeChiDepthNode)                { TestRealtimeFlush(FlushNodeChiDepthNode, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueChiDepthNode)               { TestRealtimeFlush(FlushQueueChiDepthNode, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverChiDepthNode)             { TestRealtimeFlush(FlushRecoverChiDepthNode, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeChiExternalNode)             { TestRealtimeFlush(FlushNodeChiExternalNode, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueChiExternalNode)            { TestRealtimeFlush(FlushQueueChiExternalNode, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverChiExternalNode)          { TestRealtimeFlush(FlushRecoverChiExternalNode, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeCustomNode)                  { TestRealtimeFlush(FlushNodeCustomNode, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueCustomNode)                 { TestRealtimeFlush(FlushQueueCustomNode, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverCustomNode)               { TestRealtimeFlush(FlushRecoverCustomNode, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeBypassNode)                  { TestRealtimeFlush(FlushNodeBypassNode, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueBypassNode)                 { TestRealtimeFlush(FlushQueueBypassNode, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverBypassNode)               { TestRealtimeFlush(FlushRecoverBypassNode, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeInplaceNode)                 { TestRealtimeFlush(FlushNodeInplaceNode, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueInplaceNode)                { TestRealtimeFlush(FlushQueueInplaceNode, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverInplaceNode)              { TestRealtimeFlush(FlushRecoverInplaceNode, FlushRecoverTest); }

    // Flush Offline Tests
    NATIVETEST_TEST(FlushTest, FlushNodeIPE_offline)                 { TestOfflineFlush(FlushNodeIPE_offline, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueIPE_offline)                { TestOfflineFlush(FlushQueueIPE_offline, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverIPE_offline)              { TestOfflineFlush(FlushRecoverIPE_offline, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeBPS_IPE_offline)             { TestOfflineFlush(FlushNodeBPS_IPE_offline, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueBPS_IPE_offline)            { TestOfflineFlush(FlushQueueBPS_IPE_offline, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverBPS_IPE_offline)          { TestOfflineFlush(FlushRecoverBPS_IPE_offline, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeBPS_IPE_offline_2Streams)    { TestOfflineFlush(FlushNodeBPS_IPE_offline_2Streams, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueBPS_IPE_offline_2Streams)       { TestOfflineFlush(FlushQueueBPS_IPE_offline_2Streams, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverBPS_IPE_offline_2Streams)     { TestOfflineFlush(FlushRecoverBPS_IPE_offline_2Streams, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeChiExternalNode_offline)         { TestOfflineFlush(FlushNodeChiExternalNode_offline, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueChiExternalNode_offline)        { TestOfflineFlush(FlushQueueChiExternalNode_offline, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverChiExternalNode_offline)      { TestOfflineFlush(FlushRecoverChiExternalNode_offline, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeChiExternalNodeJpeg_offline)     { TestOfflineFlush(FlushNodeChiExternalNodeJpeg_offline, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueChiExternalNodeJpeg_offline)    { TestOfflineFlush(FlushQueueChiExternalNodeJpeg_offline, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverChiExternalNodeJpeg_offline)  { TestOfflineFlush(FlushRecoverChiExternalNodeJpeg_offline, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeBPS_IPE_JPEG_offline) { TestOfflineFlush(FlushNodeBPS_IPE_JPEG_offline, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueBPS_IPE_JPEG_offline) { TestOfflineFlush(FlushQueueBPS_IPE_JPEG_offline, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverBPS_IPE_JPEG_offline) { TestOfflineFlush(FlushRecoverBPS_IPE_JPEG_offline, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeFD_offline) { TestOfflineFlush(FlushNodeFD_offline, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueFD_offline) { TestOfflineFlush(FlushQueueFD_offline, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverFD_offline) { TestOfflineFlush(FlushRecoverFD_offline, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeChiGPUNode) { TestOfflineFlush(FlushNodeChiGPUNode, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueChiGPUNode) { TestOfflineFlush(FlushQueueChiGPUNode, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverChiGPUNode) { TestOfflineFlush(FlushRecoverChiGPUNode, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNode4Streams) { TestOfflineFlush(FlushNode4Streams, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueue4Streams) { TestOfflineFlush(FlushQueue4Streams, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecover4Streams) { TestOfflineFlush(FlushRecover4Streams, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, DISABLED_FlushNodeChiDepthNode_offline) { TestOfflineFlush(FlushNodeChiDepthNode_offline, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, DISABLED_FlushQueueChiDepthNode_offline) { TestOfflineFlush(FlushQueueChiDepthNode_offline, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, DISABLED_FlushRecoverChiDepthNode_offline) { TestOfflineFlush(FlushRecoverChiDepthNode_offline, FlushRecoverTest); }

    // Flush Mixed Tests
    NATIVETEST_TEST(FlushTest, FlushNode3Streams) { TestMixedFlush(FlushNode3Streams, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueue3Streams) { TestMixedFlush(FlushQueue3Streams, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecover3Streams) { TestMixedFlush(FlushRecover3Streams, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNodeLRME_RANSAC) { TestMixedFlush(FlushNodeLRME_RANSAC, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueueLRME_RANSAC) { TestMixedFlush(FlushQueueLRME_RANSAC, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecoverLRME_RANSAC) { TestMixedFlush(FlushRecoverLRME_RANSAC, FlushRecoverTest); }
    NATIVETEST_TEST(FlushTest, FlushNode5Streams) { TestMixedFlush(FlushNode5Streams, FlushNodeTest); }
    NATIVETEST_TEST(FlushTest, FlushQueue5Streams) { TestMixedFlush(FlushQueue5Streams, FlushQueueTest); }
    NATIVETEST_TEST(FlushTest, FlushRecover5Streams) { TestMixedFlush(FlushRecover5Streams, FlushRecoverTest); }

    // Specific to Mimas Architecture (TFE->OPE vs IFE->BPS->IPE)
    /*NATIVETEST_TEST(RealtimePipelineTest, TestTFEFullStatsTestgen) { TestRealtimePipeline(TestTFEFullStatsTestgen); }
    NATIVETEST_TEST(RecipeTest, TestTFEGenericTestgen) { TestRealtimePipeline(TestTFEGenericTestgen); }
    NATIVETEST_TEST(RecipeTest, TestOPEGeneric) { TestOfflinePipeline(TestOPEGeneric); }
    NATIVETEST_TEST(RecipeTest, TestTFEGeneric2StreamTestgen) { TestRealtimePipeline(TestTFEGeneric2StreamTestgen); }
    NATIVETEST_TEST(RecipeTest, TestOPEGeneric2StreamDisplay) { TestOfflinePipeline(TestOPEGeneric2StreamDisplay); }
    NATIVETEST_TEST(RecipeTest, TestOPEGeneric3StreamDisplayStats) { TestOfflinePipeline(TestOPEGeneric3StreamDisplayStats); }*/

    // Convenience helper to run main code inside tests namespace
    int RunNativeChiTest(int argc, char** argv)
    {
        // print the title with app version and platform info
#ifdef ENVIRONMENT64 // 64-bit
        NT_LOG_INFO("===== NativeChiTest %s (64-bit %s %s) =====", NATIVECHITEST_VERSION,
            CmdLineParser::GetTargetProduct(), CmdLineParser::GetPlatformVersion());
#else // 32-bit
        NT_LOG_INFO("===== NativeChiTest %s (32-bit %s %s) =====", NATIVECHITEST_VERSION,
            CmdLineParser::GetTargetProduct(), CmdLineParser::GetPlatformVersion());
#endif

        // parse all command line options, print help menu if illegal option provided
        if (-1 == CmdLineParser::ParseCommandLine(argc, argv))
        {
            CmdLineParser::PrintCommandLineUsage();
            return 0;
        }

        // set the verbose level
        verboseSeverity eSev = static_cast<verboseSeverity>(CmdLineParser::GetLogLevel());
        if (-1 == NTLog.SetLogLevel(eSev))
        {
            NT_LOG_ERROR("Invalid log level %d", CmdLineParser::GetLogLevel());
            return 1;
        }

        // Run tests
        int result = RunTests();
        return (result);
    }

} //namespace tests

int main(int argc, char** argv)
{
    return tests::RunNativeChiTest(argc, argv);
}
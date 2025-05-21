ifeq ($(CAMX_CHICDK_PATH),)
LOCAL_PATH := $(abspath $(call my-dir)/../../..)
CAMX_CHICDK_PATH := $(abspath $(LOCAL_PATH)/../../..)
else
LOCAL_PATH := $(CAMX_CHICDK_PATH)/test/nativetest/nativechitest
endif

NATIVETEST_PATH := $(CAMX_CHICDK_PATH)/test/nativetest

include $(CLEAR_VARS)

# Module supports function call tracing via ENABLE_FUNCTION_CALL_TRACE
# Required before including common.mk
SUPPORT_FUNCTION_CALL_TRACE := 1

# Get definitions common to the CAMX project here
include $(CAMX_CHICDK_PATH)/core/build/android/common.mk

LOCAL_SRC_FILES :=                          \
    binary_comp_test.cpp                    \
    camera_manager_test.cpp                 \
    camera_module_test.cpp                  \
    chibuffermanager.cpp                    \
    chimetadatautil.cpp                     \
    chimetadata_test.cpp                    \
    chimodule.cpp                           \
    chipipeline.cpp                         \
    chipipelineutils.cpp                    \
    chisession.cpp                          \
    chitestcase.cpp                         \
    chitests.cpp                            \
    custom_node_test.cpp                    \
    flush_test.cpp                          \
    mixed_pipeline_test.cpp                 \
    offline_pipeline_test.cpp               \
    pip_camera_test.cpp                     \
    recipe_test.cpp                         \
    realtime_pipeline_test.cpp              \

LOCAL_INC_FILES :=                          \
    binary_comp_test.h                      \
    camera_manager_test.h                   \
    camera_module_test.h                    \
    chibuffermanager.h                      \
    chimetadatautil.h                       \
    chimetadata_test.h                      \
    chimodule.h                             \
    chipipeline.h                           \
    chipipelineutils.h                      \
    chisession.h                            \
    chitestcase.h                           \
    custom_node_test.h                      \
    flush_test.h                            \
    mixed_pipeline_test.h                   \
    nchicommon.h                            \
    offline_pipeline_test.h                 \
    pip_camera_test.h                       \
    recipe_test.h                           \
    realtime_pipeline_test.h                \
    test_pipelines.h                        \
    $(NATIVETEST_PATH)/nativetestutils/     \

# Put here any libraries that should be linked by CAMX projects
LOCAL_C_LIBS := $(CAMX_C_LIBS)

# Paths to included headers
LOCAL_C_INCLUDES :=                                     \
    $(CAMX_C_INCLUDES)                                  \
    $(CAMX_CHICDK_PATH)/api/common/                     \
    $(CAMX_CHICDK_PATH)/api/utils/                      \
    $(NATIVETEST_PATH)/nativetestutils/                 \
    $(NATIVETEST_PATH)/nativechitest/                   \
    system/media/camera/include/system/                 \
    $(TARGET_OUT_INTERMEDIATES)/include/common/inc      \
    $(TARGET_OUT_INTERMEDIATES)/include/xmllib/inc      \
    $(TARGET_OUT_HEADERS)/camx                          \
    hardware/libhardware/include                        \
    $(CAMX_CHICDK_PATH)/../ext/                         \
    $(CAMX_CHICDK_PATH)/../ext/hardware/                \
    $(CAMX_CHICDK_PATH)/../ext/system/                  \

# Compiler flags
LOCAL_CFLAGS := $(CAMX_CFLAGS)
LOCAL_CFLAGS += -fexceptions            \
                -g                      \
                -Wno-unused-variable

LOCAL_CFLAGS += -DFEATURE_XMLLIB

LOCAL_CPPFLAGS := $(CAMX_CPPFLAGS)

# Libraries to statically link
LOCAL_STATIC_LIBRARIES :=               \
    libnativetestutils                  \
    libchiutils

# Libraries to statically link
LOCAL_WHOLE_STATIC_LIBRARIES :=

# Libraries to link
LOCAL_SHARED_LIBRARIES +=           \
    $(NATIVETEST_SHARED_LIBRARIES)  \
    libui                           \
    libcamera_metadata              \
    libcutils                       \
    libhardware                     \
    libhidlbase                     \
    libhidltransport                \
    liblog                          \
    libqdMetaData                   \
    libsync                         \
    libutils                        \

LOCAL_HEADER_LIBRARIES +=           \
    display_headers

LOCAL_LDLIBS :=                 \
    -llog                       \
    -lz                         \
    -ldl

LOCAL_LDFLAGS :=

# Binary name
LOCAL_MODULE := nativechitest.bitra

# Deployment path under bin
LOCAL_MODULE_RELATIVE_PATH := ../bin
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_EXECUTABLE)

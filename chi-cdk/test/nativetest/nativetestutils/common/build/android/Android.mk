ifeq ($(CAMX_CHICDK_PATH),)
LOCAL_PATH := $(abspath $(call my-dir)/../../..)
CAMX_CHICDK_PATH := $(abspath $(LOCAL_PATH)/../../..)
else
LOCAL_PATH := $(CAMX_CHICDK_PATH)/test/nativetest/nativetestutils
endif

NATIVETEST_PATH := $(CAMX_CHICDK_PATH)/test/nativetest

include $(CLEAR_VARS)

# Module supports function call tracing via ENABLE_FUNCTION_CALL_TRACE
# Required before including common.mk
SUPPORT_FUNCTION_CALL_TRACE := 1

# Get definitions common to the CAMX project here
include $(CAMX_CHICDK_PATH)/core/build/android/common.mk

LOCAL_SRC_FILES :=                          \
    buffermanager.cpp                       \
    cmdlineparser.cpp                       \
    camera3stream.cpp                       \
    camera3metadata.cpp                     \
    commonutilslinux.cpp                    \
    commonutilswin32.cpp                    \
    nativetestlog.cpp                       \
    nativetest.cpp                          \

LOCAL_INC_FILES :=                          \
    buffermanager.h                         \
    cmdlineparser.h                         \
    camera3stream.h                         \
    camera3metadata.h                       \
    commonutils.h                           \
    camera3common.h                         \
    nativetestlog.h                         \
    nativetest.h                            \


# Put here any libraries that should be linked by CAMX projects
LOCAL_C_LIBS := $(CAMX_C_LIBS)

# Paths to included headers
LOCAL_C_INCLUDES :=                                  \
    $(CAMX_C_INCLUDES)                               \
    $(CAMX_CHICDK_PATH)/../camx/src/core/hal/        \
    $(NATIVETEST_PATH)/nativetestutils/              \
    $(CAMX_CHICDK_PATH)/api/common/                  \
    $(CAMX_CHICDK_PATH)/api/utils/                   \
    $(TARGET_OUT_INTERMEDIATES)/include/common/inc   \
    $(TARGET_OUT_INTERMEDIATES)/include/xmllib/inc   \
    $(TARGET_OUT_HEADERS)/camx                       \
    system/media/camera/include/system/              \
    hardware/libhardware/include                     \
    $(CAMX_CHICDK_PATH)/../ext/                      \
    $(CAMX_CHICDK_PATH)/../ext/hardware/             \
    $(CAMX_CHICDK_PATH)/../ext/system/               \

# Compiler flags
LOCAL_CFLAGS := $(CAMX_CFLAGS)
LOCAL_CFLAGS += -fexceptions            \
                -g                      \
                -Wno-unused-variable

LOCAL_CFLAGS += -DFEATURE_XMLLIB

LOCAL_CPPFLAGS := $(CAMX_CPPFLAGS)

# Libraries to statically link
LOCAL_STATIC_LIBRARIES :=          \
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

LOCAL_LDLIBS :=
LOCAL_LDFLAGS :=

# Binary name
LOCAL_PROPRIETARY_MODULE    := true
LOCAL_MODULE                := libnativetestutils

include $(BUILD_STATIC_LIBRARY)

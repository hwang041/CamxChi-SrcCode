ifneq ($(strip $(USE_CAMERA_STUB)),true)

PLATFORM_SDK_PPDK = 28
PLATFORM_SDK_QPDK = 29

# Helper function to check SDK version
ifeq ($(CAMX_EXT_VBUILD),)
# Linux Build
CHECK_VERSION_LT = $(shell if [ $(1) -lt $(2) ] ; then echo true ; else echo false ; fi)
CHECK_VERSION_GE = $(shell if [ $(1) -ge $(2) ] ; then echo true ; else echo false ; fi)
endif # ifeq ($(CAMX_EXT_VBUILD),)

CAMX_CHICDK_PATH := $(call my-dir)
CAMX_CHICDK_API_PATH := $(CAMX_CHICDK_PATH)/api
CAMX_CHICDK_CORE_PATH := $(CAMX_CHICDK_PATH)/core
CAMX_CHICDK_OEM_PATH := $(CAMX_CHICDK_PATH)/oem
CAMX_CHICDK_TEST_PATH := $(CAMX_CHICDK_PATH)/test
CAMX_CHICDK_TOPOLOGY_PATH := $(CAMX_CHICDK_OEM_PATH)/qcom/topology/

# Take backup of SDLLVM specific flag and version defs as other modules (adreno)
# also maintain their own version of it.
OLD_SDCLANG_FLAG_DEFS    := $(SDCLANG_FLAG_DEFS)
OLD_SDCLANG_VERSION_DEFS := $(SDCLANG_VERSION_DEFS)

include $(CAMX_CHICDK_API_PATH)/generated/build/android/Android.mk
include $(CAMX_CHICDK_CORE_PATH)/Android.mk
include $(CAMX_CHICDK_OEM_PATH)/Android.mk
include $(CAMX_CHICDK_TEST_PATH)/Android.mk

# Restore previous value of sdllvm flag and version defs
SDCLANG_FLAG_DEFS    := $(OLD_SDCLANG_FLAG_DEFS)
SDCLANG_VERSION_DEFS := $(OLD_SDCLANG_VERSION_DEFS)

endif #!USE_CAMERA_STUB

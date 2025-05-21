ifneq ($(CAMX_CHICDK_PATH),)
LOCAL_PATH := $(CAMX_CHICDK_PATH)/test
#CAMX_CHICDK_TEST_PATH := $(LOCAL_PATH)
else
LOCAL_PATH := $(call my-dir)
endif

include $(CAMX_CHICDK_TEST_PATH)/chifeature2test/common/build/android/Android.mk
include $(CAMX_CHICDK_TEST_PATH)/chifeature2testframework/common/build/android/Android.mk
include $(CAMX_CHICDK_TEST_PATH)/chiofflinepostproctest/common/build/android/Android.mk
include $(CAMX_CHICDK_TEST_PATH)/f2player/common/build/android/Android.mk
include $(CAMX_CHICDK_TEST_PATH)/nativetest/Android.mk

ifeq ($(TARGET_BOARD_PLATFORM),lito)
    include $(CAMX_CHICDK_TEST_PATH)/chifeature2test/bitra/build/android/Android.mk
    include $(CAMX_CHICDK_TEST_PATH)/chifeature2testframework/bitra/build/android/Android.mk
    include $(CAMX_CHICDK_TEST_PATH)/chiofflinepostproctest/bitra/build/android/Android.mk
    include $(CAMX_CHICDK_TEST_PATH)/f2player/bitra/build/android/Android.mk
endif

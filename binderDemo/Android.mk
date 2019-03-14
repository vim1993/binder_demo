LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := \
    libutils \
    libbinder \
    liblog

LOCAL_SRC_FILES := \
    ./src/DemoService.cpp \
    ./src/DemoDataCenter.cpp

LOCAL_MODULE := BinderDemoService

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/inc

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := \
    libutils \
    libbinder \
    liblog

LOCAL_MODULE := BinderDemoClient

LOCAL_SRC_FILES := \
    ./src/DemoClient.cpp \
    ./src/DemoDataCenter.cpp

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/inc

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)

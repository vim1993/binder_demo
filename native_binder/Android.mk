LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libutils \
    libbinder
LOCAL_MODULE    := TestNativeServer
LOCAL_SRC_FILES := \
    ./src/server/test_server.cpp

LOCAL_C_INCLUDES := \
    ./inc

LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libutils \
    libbinder
LOCAL_MODULE    := TestNativeClient

LOCAL_SRC_FILES := \
    ./src/client/test_client.cpp

LOCAL_C_INCLUDES := \
    ./inc

LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)
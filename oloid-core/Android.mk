LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := oloid_core
LOCAL_SRC_FILES := src/main.cpp src/scanner.cpp src/hooker.cpp
LOCAL_LDLIBS    := -llog -landroid -lGLESv2

include $(BUILD_SHARED_LIBRARY)

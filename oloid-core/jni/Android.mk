LOCAL_PATH := $(call my-dir)

# 1. Deklarasikan Dobby sebagai Prebuilt Static
include $(CLEAR_VARS)
LOCAL_MODULE := dobby_static
LOCAL_SRC_FILES := ../libs/arm64-v8a/libdobby.so
include $(PREBUILT_SHARED_LIBRARY)

# 2. Bangun Oloid Core dan telan Dobby
include $(CLEAR_VARS)
LOCAL_MODULE := oloid_core
LOCAL_SRC_FILES := main.cpp
LOCAL_LDLIBS := -llog -landroid
LOCAL_SHARED_LIBRARIES := dobby_static

include $(BUILD_SHARED_LIBRARY)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := oloid_core

# Ambil semua file dari dobby_src yang udah kita copy tadi
FILE_LIST := $(wildcard $(LOCAL_PATH)/dobby_src/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/dobby_src/*.cc)

LOCAL_SRC_FILES := main.cpp $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/dobby_src
LOCAL_LDLIBS := -llog -landroid -ldl
LOCAL_CFLAGS := -O2 -fPIC -DDOBBY_GENERIC_ABI

include $(BUILD_SHARED_LIBRARY)

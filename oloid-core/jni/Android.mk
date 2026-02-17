LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := oloid_core

# Cari semua file cpp dan cc di folder dobby_src secara otomatis
FILE_LIST := $(wildcard $(LOCAL_PATH)/dobby_src/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/dobby_src/*.cc)

LOCAL_SRC_FILES := main.cpp $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/dobby_src
LOCAL_LDLIBS := -llog -landroid -ldl
LOCAL_CFLAGS := -O2 -fPIC -DDOBBY_GENERIC_ABI

include $(BUILD_SHARED_LIBRARY)

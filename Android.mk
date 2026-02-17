LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := oloid_core

# Tambahkan jalur ke folder external agar TINYSTL ditemukan
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH) \
    $(LOCAL_PATH)/../Dobby/include \
    $(LOCAL_PATH)/../Dobby/source \
    $(LOCAL_PATH)/../Dobby/external

LOCAL_SRC_FILES := main.cpp \
    ../Dobby/source/dobby.cpp \
    ../Dobby/source/interceptor.cpp \
    ../Dobby/source/TrampolineBridge/Trampoline/trampoline_arm64.cc \
    ../Dobby/source/InstructionRelocation/arm64/InstructionRelocationARM64.cc \
    ../Dobby/source/Backend/UserMode/PlatformUtil/Linux/ProcessRuntime.cc \
    ../Dobby/source/Backend/UserMode/ExecMemory/code-patch-tool-posix.cc

LOCAL_LDLIBS := -llog -landroid -ldl
LOCAL_CFLAGS := -O2 -fPIC -DDOBBY_GENERIC_ABI
include $(BUILD_SHARED_LIBRARY)

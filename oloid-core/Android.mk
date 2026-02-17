LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := oloid_core

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH) \
    $(LOCAL_PATH)/common \
    $(LOCAL_PATH)/external \
    $(LOCAL_PATH)/external/TINYSTL \
    $(LOCAL_PATH)/external/logging \
    $(LOCAL_PATH)/dobby_src \
    $(LOCAL_PATH)/dobby_src/include

LOCAL_SRC_FILES := main.cpp \
    dobby_src/dobby.cpp \
    dobby_src/interceptor.cpp \
    dobby_src/TrampolineBridge/Trampoline/trampoline_arm64.cc \
    dobby_src/InstructionRelocation/arm64/InstructionRelocationARM64.cc \
    dobby_src/Backend/UserMode/PlatformUtil/Linux/ProcessRuntime.cc \
    dobby_src/Backend/UserMode/ExecMemory/code-patch-tool-posix.cc

LOCAL_LDLIBS := -llog -landroid -ldl
LOCAL_CFLAGS := -O2 -fPIC -DDOBBY_GENERIC_ABI -Wno-error=implicit-function-declaration

include $(BUILD_SHARED_LIBRARY)

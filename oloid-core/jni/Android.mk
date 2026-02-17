LOCAL_PATH := $(call my-dir)
DOBBY_ROOT := $(LOCAL_PATH)/../../Dobby

include $(CLEAR_VARS)
LOCAL_MODULE := oloid_core

# Ambil source dari folder Dobby yang asli
LOCAL_SRC_FILES := main.cpp \
    $(DOBBY_ROOT)/source/dobby.cpp \
    $(DOBBY_ROOT)/source/Interceptor.cpp \
    $(DOBBY_ROOT)/source/TrampolineBridge/Trampoline/trampoline_arm64.cc \
    $(DOBBY_ROOT)/source/InstructionRelocation/arm64/InstructionRelocationARM64.cc \
    $(DOBBY_ROOT)/source/Backend/UserMode/PlatformUtil/Linux/ProcessRuntime.cc \
    $(DOBBY_ROOT)/source/Backend/UserMode/ExecMemory/code-patch-tool-posix.cc

# Paksa compiler liat folder include di dalem jni dan folder source Dobby
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include \
    $(DOBBY_ROOT)/source \
    $(DOBBY_ROOT)/include

LOCAL_LDLIBS := -llog -landroid -ldl
LOCAL_CFLAGS := -O2 -fPIC -DDOBBY_GENERIC_ABI

include $(BUILD_SHARED_LIBRARY)

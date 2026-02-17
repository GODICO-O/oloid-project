LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := oloid_core

# Pastikan path ke Dobby benar sesuai struktur tree lo
DOBBY_SRC := ../../Dobby/source

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Dobby/include $(LOCAL_PATH)/../../Dobby/source

# HANYA compile main.cpp dan biner Dobby
LOCAL_SRC_FILES := main.cpp \
    $(DOBBY_SRC)/dobby.cpp \
    $(DOBBY_SRC)/Interceptor.cpp \
    $(DOBBY_SRC)/TrampolineBridge/Trampoline/trampoline_arm64.cc \
    $(DOBBY_SRC)/InstructionRelocation/arm64/InstructionRelocationARM64.cc \
    $(DOBBY_SRC)/Backend/UserMode/PlatformUtil/Linux/ProcessRuntime.cc \
    $(DOBBY_SRC)/Backend/UserMode/ExecMemory/code-patch-tool-posix.cc

LOCAL_LDLIBS := -llog -landroid -ldl
LOCAL_CFLAGS := -O2 -fPIC -DDOBBY_GENERIC_ABI

include $(BUILD_SHARED_LIBRARY)

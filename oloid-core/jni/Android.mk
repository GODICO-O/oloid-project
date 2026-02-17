LOCAL_PATH := $(call my-dir)
# Arahkan ke root Dobby yang asli
DOBBY_ROOT := $(LOCAL_PATH)/../../Dobby

include $(CLEAR_VARS)
LOCAL_MODULE := oloid_core

# Ambil semua source Dobby yang dibutuhin buat arm64
LOCAL_SRC_FILES := main.cpp \
    $(DOBBY_ROOT)/source/dobby.cpp \
    $(DOBBY_ROOT)/source/Interceptor.cpp \
    $(DOBBY_ROOT)/source/TrampolineBridge/Trampoline/trampoline_arm64.cc \
    $(DOBBY_ROOT)/source/InstructionRelocation/arm64/InstructionRelocationARM64.cc \
    $(DOBBY_ROOT)/source/Backend/UserMode/PlatformUtil/Linux/ProcessRuntime.cc \
    $(DOBBY_ROOT)/source/Backend/UserMode/ExecMemory/code-patch-tool-posix.cc

# KUNCI UTAMA: Tambahin semua jalur header agar #include "dobby/common.h" dkk ketemu
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH) \
    $(DOBBY_ROOT)/include \
    $(DOBBY_ROOT)/source \
    $(DOBBY_ROOT)/source/Objects \
    $(DOBBY_ROOT)/source/Backend/UserMode/ExecMemory

LOCAL_LDLIBS := -llog -landroid -ldl
LOCAL_CFLAGS := -O2 -fPIC -DDOBBY_GENERIC_ABI

include $(BUILD_SHARED_LIBRARY)

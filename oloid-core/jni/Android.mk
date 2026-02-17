LOCAL_PATH := $(call my-dir)
# Jalur dari oloid-core/jni ke root project
ROOT_PROJECT := $(LOCAL_PATH)/../..

include $(CLEAR_VARS)
LOCAL_MODULE := oloid_core

# Tambahkan include path yang presisi
LOCAL_C_INCLUDES := $(ROOT_PROJECT)/Dobby/include $(ROOT_PROJECT)/Dobby/source

# Source utama
LOCAL_SRC_FILES := main.cpp

# Masukkan Dobby Source dengan path yang benar
LOCAL_SRC_FILES += \
    ../../Dobby/source/dobby.cpp \
    ../../Dobby/source/Interceptor.cpp \
    ../../Dobby/source/TrampolineBridge/Trampoline/trampoline_arm64.cc \
    ../../Dobby/source/InstructionRelocation/arm64/InstructionRelocationARM64.cc \
    ../../Dobby/source/Backend/UserMode/PlatformUtil/Linux/ProcessRuntime.cc \
    ../../Dobby/source/Backend/UserMode/ExecMemory/code-patch-tool-posix.cc

LOCAL_LDLIBS := -llog -landroid -ldl
LOCAL_CFLAGS := -O2 -fPIC -DDOBBY_GENERIC_ABI

include $(BUILD_SHARED_LIBRARY)

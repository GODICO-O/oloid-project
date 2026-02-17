LOCAL_PATH := $(call my-dir)
DOBBY_SRC_PATH := $(LOCAL_PATH)/../../Dobby

include $(CLEAR_VARS)
LOCAL_MODULE := oloid_core

# Tambahkan main.cpp kita
LOCAL_SRC_FILES := main.cpp

# --- MULAI INTEGRASI DOBBY SOURCE (IDENTIK DENGAN GEODE) ---
LOCAL_C_INCLUDES := $(DOBBY_SRC_PATH)/include $(DOBBY_SRC_PATH)/source
LOCAL_CFLAGS := -fPIC -O2 -DDOBBY_GENERIC_ABI

# Masukkan source code inti Dobby agar ter-compile jadi satu
LOCAL_SRC_FILES += \
    ../../Dobby/source/dobby.cpp \
    ../../Dobby/source/Interceptor.cpp \
    ../../Dobby/source/TrampolineBridge/Trampoline/trampoline_arm64.cc \
    ../../Dobby/source/InstructionRelocation/arm64/InstructionRelocationARM64.cc \
    ../../Dobby/source/Backend/UserMode/PlatformUtil/Linux/ProcessRuntime.cc \
    ../../Dobby/source/Backend/UserMode/ExecMemory/code-patch-tool-posix.cc

# Log & Android system libs
LOCAL_LDLIBS := -llog -landroid -ldl
include $(BUILD_SHARED_LIBRARY)

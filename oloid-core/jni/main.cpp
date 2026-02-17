#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include "dobby.h"

#define LOG_TAG "OLOID_PROJECT"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static bool (*MenuLayer_init_original)(void* self);

bool MenuLayer_init_hook(void* self) {
    LOGI("Oloid: Hook Aktif! MenuLayer Geode-Style Sukses! 🚀");
    return MenuLayer_init_original(self);
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Oloid Core: Memulai proses Hooking Aktif (Unified Core)... 🕵️‍♂️");

    void* cocos_handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (cocos_handle) {
        void* target = dlsym(cocos_handle, "_ZN9MenuLayer4initEv");
        if (target) {
            DobbyHook(target, (void*)MenuLayer_init_hook, (void**)&MenuLayer_init_original);
            LOGI("Oloid: HOOKING SUKSES! ✅");
        }
        dlclose(cocos_handle);
    }
    return JNI_VERSION_1_6;
}

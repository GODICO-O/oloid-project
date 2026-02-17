#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>

#define LOG_TAG "OLOID_PROJECT"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Deklarasikan DobbyHook secara eksternal karena dia sudah ada di dalam
extern "C" int DobbyHook(void* address, void* replace_call, void** origin_call);

static bool (*MenuLayer_init_original)(void* self);

bool MenuLayer_init_hook(void* self) {
    LOGI("Oloid: Hook Aktif! Manifestasi MenuLayer Berhasil! 🚀");
    return MenuLayer_init_original(self);
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Oloid Core: Memulai proses Hooking Aktif (Static Mode)... 🕵️‍♂️");

    void* cocos_handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (cocos_handle) {
        void* target = dlsym(cocos_handle, "_ZN9MenuLayer4initEv");
        if (target) {
            // Langsung panggil DobbyHook tanpa dlsym lagi!
            DobbyHook(target, (void*)MenuLayer_init_hook, (void**)&MenuLayer_init_original);
            LOGI("Oloid: HOOKING SUKSES! ✅");
        } else {
            LOGI("Oloid: Gagal nemu MenuLayer!");
        }
        dlclose(cocos_handle);
    } else {
        LOGI("Oloid: libcocos2dcpp.so tidak ditemukan!");
    }

    return JNI_VERSION_1_6;
}

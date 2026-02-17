#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string>

#define LOG_TAG "OLOID_PROJECT"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

typedef int (*DobbyHook_t)(void*, void*, void**);
static bool (*MenuLayer_init_original)(void* self);

bool MenuLayer_init_hook(void* self) {
    LOGI("Oloid: Hook Aktif! MenuLayer kebuka! 🚀");
    return MenuLayer_init_original(self);
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Oloid Core: Memulai proses Hooking Aktif... 🕵️‍♂️");

    // Taktik KLOS: Cari folder library aplikasi secara dinamis
    char path[256];
    sprintf(path, "/data/data/com.robtopx.geometryjump/lib/arm64-v8a/libdobby.so");

    // Kalau lo pake GD sub-zero/world, sesuaikan package name-nya di atas!
    
    void* dobby_handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
    if (!dobby_handle) {
        LOGI("Oloid: Jalur full gagal, coba jalur standar...");
        dobby_handle = dlopen("libdobby.so", RTLD_NOW | RTLD_GLOBAL);
    }

    void* cocos_handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (cocos_handle && dobby_handle) {
        void* target = dlsym(cocos_handle, "_ZN9MenuLayer4initEv");
        void* dobby_ptr = dlsym(dobby_handle, "DobbyHook");

        if (target && dobby_ptr) {
            DobbyHook_t dobby_hook = (DobbyHook_t)dobby_ptr;
            dobby_hook(target, (void*)MenuLayer_init_hook, (void**)&MenuLayer_init_original);
            LOGI("Oloid: HOOKING SUKSES! ✅ Manifestasi Xenom Dimulai.");
        } else {
            LOGI("Oloid: Simbol nggak ketemu. Target: %p, Dobby: %p", target, dobby_ptr);
        }
    } else {
        LOGI("Oloid: Lib gagal dimuat. Dobby: %s", dlerror());
    }

    return JNI_VERSION_1_6;
}

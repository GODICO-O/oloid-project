#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <stdint.h>

// Kita pake logging biar ketahuan pas proses ngebajak (hooking)
#define LOG_TAG "OLOID_PROJECT"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Definisi pointer buat nyimpen alamat asli fungsi MenuLayer::init
static bool (*MenuLayer_init_original)(void* self);

// Fungsi "palsu" kita yang bakal dijalanin sama GD
bool MenuLayer_init_hook(void* self) {
    // 1. Jalankan fungsi aslinya dulu biar menu GD muncul
    bool result = MenuLayer_init_original(self);
    
    // 2. Di sini Oloid beraksi!
    LOGI("Oloid: MenuLayer terdeteksi! Saatnya munculin logo... 🚀");
    
    // Nanti di sini kita panggil CCSprite::create("oloid_logo.png")
    // dan addChild(logo) ke 'self' (MenuLayer)
    
    return result;
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Oloid Core: Memulai proses Hooking... 🕵️‍♂️");
    
    void* handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (handle) {
        // Alamat memori MenuLayer::init buat GD 2.2 (contoh alamat)
        // Di KL Phone nanti, Xenom bakal nyari alamat ini otomatis via scanner.cpp
        uintptr_t menuLayerInitAddr = (uintptr_t)dlsym(handle, "_ZN9MenuLayer4initEv"); 

        if (menuLayerInitAddr) {
            LOGI("Oloid: Alamat MenuLayer::init ketemu! Sedang ngebajak... ⚡");
            
            // Di sini kita pake Dobby buat gantiin fungsi aslinya ke fungsi kita
            // DobbyHook((void*)menuLayerInitAddr, (void*)MenuLayer_init_hook, (void**)&MenuLayer_init_original);
        }
        dlclose(handle);
    }

    return JNI_VERSION_1_6;
}

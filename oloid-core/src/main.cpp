#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <stdint.h>

#define LOG_TAG "OLOID_PROJECT"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Definisi fungsi internal Cocos2d-x yang akan kita panggil
typedef void* (*CCSprite_create_t)(const char*);
typedef void (*CCNode_addChild_t)(void*, void*);

static bool (*MenuLayer_init_original)(void* self);

bool MenuLayer_init_hook(void* self) {
    bool result = MenuLayer_init_original(self);
    LOGI("Oloid: MenuLayer terdeteksi! Mengeksekusi render logo... 🚀");

    void* handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (handle) {
        // Mencari alamat fungsi create sprite dan addChild
        auto create_sprite = (CCSprite_create_t)dlsym(handle, "_ZN7cocos2d8CCSprite6createEPKc");
        auto add_child = (CCNode_addChild_t)dlsym(handle, "_ZN7cocos2d6CCNode8addChildEPS0_");

        if (create_sprite && add_child) {
            // Membuat objek sprite dari oloid_logo.png di assets
            void* logo = create_sprite("oloid_logo.png");
            if (logo) {
                // Menambahkan logo ke dalam MenuLayer (self)
                add_child(self, logo);
                LOGI("Oloid: Logo berhasil ditempel ke layar! 🎨");
            }
        }
        dlclose(handle);
    }
    return result;
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Oloid Core: Memulai proses Hooking... 🕵️‍♂️");
    // ... Logika hooking Dobby lu di sini ...
    return JNI_VERSION_1_6;
}

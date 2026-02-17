#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <stdint.h>

#define LOG_TAG "OLOID_PROJECT"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Definisi fungsi internal Cocos2d-x
typedef void* (*CCSprite_create_t)(const char*);
typedef void (*CCNode_addChild_t)(void*, void*, int);
typedef void (*CCNode_setPosition_t)(void*, float, float);

void renderOloidLogo(void* menuLayer) {
    LOGI("Oloid: Menjalankan protokol render logo... 🚀");

    void* handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (!handle) {
        LOGI("Oloid: Gagal membuka engine game!");
        return;
    }

    auto create_sprite = (CCSprite_create_t)dlsym(handle, "_ZN7cocos2d8CCSprite6createEPKc");
    auto add_child = (CCNode_addChild_t)dlsym(handle, "_ZN7cocos2d6CCNode8addChildEPS0_i");
    auto set_pos = (CCNode_setPosition_t)dlsym(handle, "_ZN7cocos2d6CCNode11setPositionEff");

    if (create_sprite && add_child && set_pos) {
        void* logo = create_sprite("oloid_logo.png");
        if (logo) {
            set_pos(logo, 150.0f, 150.0f);
            if (menuLayer) {
                add_child(menuLayer, logo, 100);
                LOGI("Oloid: Logo berhasil menembus layar GD! 🎨✅");
            } else {
                LOGI("Oloid: Pointer MenuLayer null, logo hanya dibuat di memori.");
            }
        } else {
            LOGI("Oloid: File oloid_logo.png tidak ditemukan di assets!");
        }
    } else {
        LOGI("Oloid: Gagal menemukan simbol render di engine.");
    }
    dlclose(handle);
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Oloid Core: Terdeteksi di Memori GD! 🕵️‍♂️");
    
    void* handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (handle) {
        LOGI("Oloid Core: Berhasil salaman sama Cocos2d-x! 🤝");
        renderOloidLogo(nullptr); 
        dlclose(handle);
    }
    
    return JNI_VERSION_1_6;
}

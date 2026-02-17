#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <stdint.h>

#define LOG_TAG "OLOID_PROJECT"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

typedef void* (*CCSprite_create_t)(const char*);
typedef void (*CCNode_addChild_t)(void*, void*, int);
typedef void (*CCNode_setPosition_t)(void*, float, float);

void renderOloidLogo(void* menuLayer) {
    // Safety Check: Jangan lanjut kalau menuLayer-nya belum siap (nullptr)
    if (!menuLayer) {
        LOGI("Oloid: Menunggu MenuLayer siap... ⏳");
        return;
    }

    void* handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (!handle) return;

    auto create_sprite = (CCSprite_create_t)dlsym(handle, "_ZN7cocos2d8CCSprite6createEPKc");
    auto add_child = (CCNode_addChild_t)dlsym(handle, "_ZN7cocos2d6CCNode8addChildEPS0_i");
    auto set_pos = (CCNode_setPosition_t)dlsym(handle, "_ZN7cocos2d6CCNode11setPositionEff");

    if (create_sprite && add_child && set_pos) {
        void* logo = create_sprite("oloid_logo.png");
        if (logo) {
            set_pos(logo, 150.0f, 150.0f);
            add_child(menuLayer, logo, 100);
            LOGI("Oloid: Logo berhasil menembus layar GD! 🎨✅");
        } else {
            LOGI("Oloid: EROR! oloid_logo.png belum ada di assets! ❌");
        }
    }
    dlclose(handle);
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Oloid Core: Terdeteksi di Memori GD! 🕵️‍♂️");
    // Kita hapus pemanggilan renderOloidLogo(nullptr) di sini buat cegah FC
    return JNI_VERSION_1_6;
}

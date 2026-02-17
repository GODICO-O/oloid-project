#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <stdint.h>

#define LOG_TAG "OLOID_PROJECT"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

typedef void* (*CCSprite_create_t)(const char*);
typedef void (*CCNode_addChild_t)(void*, void*, int);
typedef void (*CCNode_setPosition_t)(void*, float, float);

static bool (*MenuLayer_init_original)(void* self);

bool MenuLayer_init_hook(void* self) {
    bool result = MenuLayer_init_original(self);
    LOGI("Oloid: MenuLayer terdeteksi! Saatnya manifestasi visual... 🚀");

    void* handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (handle) {
        auto create_sprite = (CCSprite_create_t)dlsym(handle, "_ZN7cocos2d8CCSprite6createEPKc");
        auto add_child = (CCNode_addChild_t)dlsym(handle, "_ZN7cocos2d6CCNode8addChildEPS0_i");
        auto set_pos = (CCNode_setPosition_t)dlsym(handle, "_ZN7cocos2d6CCNode11setPositionEff");

        if (create_sprite && add_child && set_pos) {
            void* logo = create_sprite("oloid_logo.png");
            if (logo) {
                set_pos(logo, 200.0f, 200.0f);
                add_child(self, logo, 100);
                LOGI("Oloid: Logo resmi nongol di layar! 🎨✅");
            }
        }
        dlclose(handle);
    }
    return result;
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Oloid Core: Memulai proses Hooking Aktif... 🕵️‍♂️");
    void* handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (handle) {
        void* target = dlsym(handle, "_ZN9MenuLayer4initEv");
        if (target) {
            LOGI("Oloid: Target MenuLayer ketemu di %p. Menunggu aktivasi Dobby...", target);
        }
        dlclose(handle);
    }
    return JNI_VERSION_1_6;
}

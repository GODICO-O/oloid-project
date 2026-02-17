#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <stdint.h>

#define LOG_TAG "OLOID_PROJECT"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

typedef void* (*CCSprite_create_t)(const char*);
typedef void (*CCNode_addChild_t)(void*, void*, int);
typedef void (*CCNode_setPosition_t)(void*, float, float);
typedef int (*DobbyHook_t)(void*, void*, void**);

static bool (*MenuLayer_init_original)(void* self);

bool MenuLayer_init_hook(void* self) {
    bool result = MenuLayer_init_original(self);
    LOGI("Oloid: Hook Aktif! MenuLayer kebuka! 🚀");

    void* handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (handle) {
        auto create_sprite = (CCSprite_create_t)dlsym(handle, "_ZN7cocos2d8CCSprite6createEPKc");
        auto add_child = (CCNode_addChild_t)dlsym(handle, "_ZN7cocos2d6CCNode8addChildEPS0_i");
        auto set_pos = (CCNode_setPosition_t)dlsym(handle, "_ZN7cocos2d6CCNode11setPositionEff");

        if (create_sprite && add_child && set_pos) {
            void* logo = create_sprite("oloid_logo.png");
            if (logo) {
                set_pos(logo, 300.0f, 300.0f);
                add_child(self, logo, 100);
                LOGI("Oloid: MANIFESTASI VISUAL BERHASIL! 🎨✅");
            }
        }
        dlclose(handle);
    }
    return result;
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Oloid Core: Memulai proses Hooking Aktif... 🕵️‍♂️");

    void* dobby_handle = dlopen("libdobby.so", RTLD_NOW | RTLD_GLOBAL);
    if (!dobby_handle) {
        dobby_handle = dlopen("libdobby.so", RTLD_LAZY);
    }

    void* cocos_handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (!cocos_handle) return JNI_VERSION_1_6;

    void* target = dlsym(cocos_handle, "_ZN9MenuLayer4initEv");
    void* dobby_ptr = nullptr;
    if (dobby_handle) {
        dobby_ptr = dlsym(dobby_handle, "DobbyHook");
    }

    if (target && dobby_ptr) {
        LOGI("Oloid: Target & Dobby SIAP. Menjalankan pembajakan... ⚡");
        DobbyHook_t dobby_hook = (DobbyHook_t)dobby_ptr;
        dobby_hook(target, (void*)MenuLayer_init_hook, (void**)&MenuLayer_init_original);
        LOGI("Oloid: HOOKING SUKSES! ✅");
    } else {
        if (!target) LOGI("Oloid: Gagal nemu MenuLayer!");
        if (!dobby_ptr) {
            const char* err = dlerror();
            LOGI("Oloid: DobbyHook gagal dimuat! Info: %s", (err ? err : "Unknown Error"));
        }
    }
    dlclose(cocos_handle);
    return JNI_VERSION_1_6;
}

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

// Pointer untuk fungsi asli
static bool (*MenuLayer_init_original)(void* self);

// Fungsi Hook yang akan dipanggil saat MenuLayer terbuka
bool MenuLayer_init_hook(void* self) {
    bool result = MenuLayer_init_original(self);
    LOGI("Oloid: MenuLayer terdeteksi! Mengeksekusi manifestasi visual... 🚀");

    void* handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (handle) {
        auto create_sprite = (CCSprite_create_t)dlsym(handle, "_ZN7cocos2d8CCSprite6createEPKc");
        auto add_child = (CCNode_addChild_t)dlsym(handle, "_ZN7cocos2d6CCNode8addChildEPS0_i");
        auto set_pos = (CCNode_setPosition_t)dlsym(handle, "_ZN7cocos2d6CCNode11setPositionEff");

        if (create_sprite && add_child && set_pos) {
            void* logo = create_sprite("oloid_logo.png");
            if (logo) {
                // Posisi: X=300, Y=300 (biar agak ke tengah layar Poco M5)
                set_pos(logo, 300.0f, 300.0f);
                add_child(self, logo, 100);
                LOGI("Oloid: LOGO BERHASIL DITEMPEL! 🎨✅");
            }
        }
        dlclose(handle);
    }
    return result;
}

// Tipe data fungsi Dobby
typedef int (*DobbyHook_t)(void*, void*, void**);

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Oloid Core: Memulai proses Hooking Aktif... 🕵️‍♂️");

    void* gd_handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (gd_handle) {
        void* target = dlsym(gd_handle, "_ZN9MenuLayer4initEv");
        
        // Sesuai visi KLOS: Kita pakai Dobby secara dinamis
        void* dobby_handle = dlopen("libdobby.so", RTLD_LAZY);
        if (!dobby_handle) dobby_handle = dlopen("liboloid_core.so", RTLD_LAZY); // Cek internal

        if (target && dobby_handle) {
            auto dobby_hook = (DobbyHook_t)dlsym(dobby_handle, "DobbyHook");
            if (dobby_hook) {
                dobby_hook(target, (void*)MenuLayer_init_hook, (void**)&MenuLayer_init_original);
                LOGI("Oloid: Hooking Berhasil! Menunggu lo masuk Menu Utama... ⚡");
            }
        }
        dlclose(gd_handle);
    }
    return JNI_VERSION_1_6;
}

#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>

#define LOG_TAG "OLOID_PROJECT"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Oloid Core: Terdeteksi di Memori GD! 🕵️‍♂️");
    
    // Cek apakah kita bisa liat Cocos2d-x
    void* handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (handle) {
        LOGI("Oloid Core: Berhasil salaman sama Cocos2d-x! 🤝");
        dlclose(handle);
    } else {
        LOGI("Oloid Core: Belum nemu libcocos2dcpp.so, nunggu loading...");
    }

    return JNI_VERSION_1_6;
}

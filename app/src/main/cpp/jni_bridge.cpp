#include <jni.h>
#include <android/log.h>

#define LOG_TAG "PFEngine"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

extern "C" {

JNIEXPORT jint JNICALL
Java_com_promptforge_app_PFEngineBridge_initEngine(JNIEnv *, jobject) {
    LOGD("引擎初始化成功");
    return 0;
}

JNIEXPORT jbyteArray JNICALL
Java_com_promptforge_app_PFEngineBridge_generateImage(JNIEnv *env, jobject, jstring prompt) {
    if (!prompt) return nullptr;
    const char *str = env->GetStringUTFChars(prompt, nullptr);
    LOGD("提示词：%s", str);
    env->ReleaseStringUTFChars(prompt, str);
    return nullptr;
}

JNIEXPORT void JNICALL
Java_com_promptforge_app_PFEngineBridge_releaseEngine(JNIEnv *, jobject) {
    LOGD("引擎释放");
}

}

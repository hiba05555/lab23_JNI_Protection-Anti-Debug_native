#include <jni.h>
#include <string>
#include <algorithm>
#include <climits>
#include <android/log.h>

#define LOG_TAG "HC_NATIVE"
#define HC_LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define HC_LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_lab22_1jnidemo_MainActivity_helloFromJNI(
        JNIEnv* env, jobject) {
    HC_LOGI("helloFromJNI chargee avec succes");
    return env->NewStringUTF("Hello from C++ via JNI !");
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_lab22_1jnidemo_MainActivity_factorial(
        JNIEnv* env, jobject, jint n) {
    if (n < 0) { HC_LOGE("Valeur invalide : n negatif"); return -1; }
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
        if (result > INT_MAX) { HC_LOGE("Depassement detecte pour n=%d", n); return -2; }
    }
    HC_LOGI("Calcul factoriel : %d -> %lld", n, result);
    return static_cast<jint>(result);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_lab22_1jnidemo_MainActivity_reverseString(
        JNIEnv* env, jobject, jstring javaString) {
    if (javaString == nullptr) return env->NewStringUTF("Erreur : entree nulle");
    const char* raw = env->GetStringUTFChars(javaString, nullptr);
    std::string hcStr(raw);
    env->ReleaseStringUTFChars(javaString, raw);
    std::reverse(hcStr.begin(), hcStr.end());
    HC_LOGI("Chaine inversee : %s", hcStr.c_str());
    return env->NewStringUTF(hcStr.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_lab22_1jnidemo_MainActivity_sumArray(
        JNIEnv* env, jobject, jintArray array) {
    if (array == nullptr) return -1;
    jsize len = env->GetArrayLength(array);
    jint* hcElements = env->GetIntArrayElements(array, nullptr);
    if (hcElements == nullptr) return -2;
    long long total = 0;
    for (jsize i = 0; i < len; i++) total += hcElements[i];
    env->ReleaseIntArrayElements(array, hcElements, 0);
    HC_LOGI("Total tableau HC : %lld", total);
    return static_cast<jint>(total);
}
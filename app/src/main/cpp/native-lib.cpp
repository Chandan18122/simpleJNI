#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_einfochips_JNI_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from JNI...";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_einfochips_JNI_MainActivity_addTwoNumberJNI(
        JNIEnv* env,
        jobject /* this */, jint num1, jint num2) {
    return num1 + num2;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_einfochips_JNI_MainActivity_randomNumberJNI(JNIEnv* env, jobject ){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int lower_bound = 100000;
    int upper_bound = 999999;
    return lower_bound + std::rand() % (upper_bound - lower_bound + 1);
}
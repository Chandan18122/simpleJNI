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

extern "C" __attribute__((unused)) JNIEXPORT jobject JNICALL
Java_com_einfochips_JNI_MainActivity_createStudentJNI(JNIEnv *env, jobject thiz, jint roll, jstring name, jint age, jint score) {
    jclass studentClass = env->FindClass("com/einfochips/JNI/Student");
    if (studentClass == nullptr) return env->NewStringUTF("Class not found");

    jmethodID constructor = env->GetMethodID(studentClass, "<init>", "(ILjava/lang/String;II)V");
    jobject student = env->NewObject(studentClass, constructor,roll, name, age, score);
    return student;
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_einfochips_JNI_MainActivity_getStudentDetailsJNI(JNIEnv *env, jobject thiz, jobject student) {
    jclass studentClass = env->FindClass("com/einfochips/JNI/Student");
    if (studentClass == nullptr) return env->NewStringUTF("Class not found");

    jfieldID rollField = env->GetFieldID(studentClass, "roll", "I");
    jfieldID nameField = env->GetFieldID(studentClass, "name", "Ljava/lang/String;");
    jfieldID ageField = env->GetFieldID(studentClass, "age", "I");
    jfieldID gradeField = env->GetFieldID(studentClass, "score", "I");

    if (nameField == nullptr || ageField == nullptr || gradeField == nullptr) return env->NewStringUTF("Field not found");

    jint roll = env->GetIntField(student, rollField);
    jstring name = (jstring) env->GetObjectField(student, nameField);
    jint age = env->GetIntField(student, ageField);
    jint score = env->GetIntField(student, gradeField);

    const char *nameStr = env->GetStringUTFChars(name, nullptr);

    std::string result =
            "Roll: "+ std::to_string(roll)+", Name: " + std::string(nameStr) + ", Age: " + std::to_string(age) + ", Score: " +
            std::to_string(score);

    env->ReleaseStringUTFChars(name, nameStr);

    return env->NewStringUTF(result.c_str());
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_einfochips_JNI_MainActivity_getResultJNI(JNIEnv *env, jobject thiz, jobject student){
    jclass resultClass = env->FindClass("com/einfochips/JNI/Result");
    if (resultClass == nullptr) return env->NewStringUTF("Class not found");
    jmethodID constructor = env->GetMethodID(resultClass, "<init>",
                                             "(ILjava/lang/String;Ljava/lang/String;)V");

    jclass studentClass = env->FindClass("com/einfochips/JNI/Student");
    if (studentClass == nullptr) return env->NewStringUTF("Class not found");

    jfieldID rollField = env->GetFieldID(studentClass, "roll", "I");
    jfieldID scoreField = env->GetFieldID(studentClass, "score", "I");

    jint roll = env->GetIntField(student, rollField);
    jstring status;
    jstring grade ;

    jint score = env->GetIntField(student, scoreField);
    if(score >= 40) {
        status = env->NewStringUTF("Passed");
        if (score >= 85)
            grade = env->NewStringUTF("A");
        else if (score >= 70)
            grade = env->NewStringUTF("B");
        else if (score >= 55)
            grade = env->NewStringUTF("C");
        else
            grade = env->NewStringUTF("D");
    } else{
        status = env->NewStringUTF("Failed");
        grade = env->NewStringUTF("F");
    }

    jobject result = env->NewObject(resultClass, constructor, roll, status, grade);
    return result;
}
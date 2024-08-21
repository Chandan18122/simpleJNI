#include <jni.h>
#include <string>
#include <array>

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
Java_com_einfochips_JNI_MainActivity_createStudentJNI(JNIEnv *env, jobject thiz, jint roll, jstring name, jint age, jint score, jobject marksList) {
    jclass studentClass = env->FindClass("com/einfochips/JNI/Student");
    if (studentClass == nullptr) return env->NewStringUTF("Class not found");

    jmethodID constructor = env->GetMethodID(studentClass, "<init>", "(ILjava/lang/String;IILjava/util/List;)V");
    jobject student = env->NewObject(studentClass, constructor,roll, name, age, score, marksList);
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
    jfieldID marksField = env->GetFieldID(studentClass,"marks", "Ljava/util/List;");

    if (rollField == nullptr || nameField == nullptr || ageField == nullptr || gradeField == nullptr || marksField == nullptr)
        return env->NewStringUTF("Field not found");

    jint roll = env->GetIntField(student, rollField);
    jstring name = (jstring) env->GetObjectField(student, nameField);
    jint age = env->GetIntField(student, ageField);
    jint score = env->GetIntField(student, gradeField);

    jobject marksList = env->GetObjectField(student, marksField);
    jclass  marksClass = env->GetObjectClass(marksList);
    jmethodID sizeMethod = env->GetMethodID(marksClass, "size", "()I");
    if(sizeMethod == nullptr) return env->NewStringUTF("size method not found");
    jmethodID getMethod = env->GetMethodID(marksClass, "get", "(I)Ljava/lang/Object;");
    if(getMethod == nullptr) return env->NewStringUTF("getMethod not found");

    jint size = env->CallIntMethod(marksList, sizeMethod);
    std::string marksResult;
    for (jint i = 0; i < size; i++) {
        jobject marksObj = env->CallObjectMethod(marksList, getMethod, i);
        jclass marksClass = env->GetObjectClass(marksObj);
        jfieldID subjectField = env->GetFieldID(marksClass, "subjectName", "Ljava/lang/String;");
        jfieldID subjectMarkField = env->GetFieldID(marksClass, "subjectMark", "I");

        if (subjectField == nullptr || subjectMarkField == nullptr) return env->NewStringUTF("Field not found...");

        auto subjectName = (jstring) env->GetObjectField(marksObj, subjectField);
        jint subjectMark = env->GetIntField(marksObj, subjectMarkField);

        marksResult += std::to_string(i + 1) + ". " + std::string(env->GetStringUTFChars(subjectName, nullptr)) + ": "+ std::to_string(subjectMark);
        if(i < size-1) marksResult += ", ";
        env->DeleteLocalRef(subjectName);
        env->DeleteLocalRef(marksObj);
    }

    const char *nameStr = env->GetStringUTFChars(name, nullptr);

    std::string result =
            "Roll: "+ std::to_string(roll)+", Name: " + std::string(nameStr) + ", Age: " + std::to_string(age) + ", Score: " +
            std::to_string(score)+", Subject Marks: ["+ std::string(marksResult)+ " ]";

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
extern "C" JNIEXPORT jstring JNICALL
Java_com_einfochips_JNI_MainActivity_createStudentFromBundleJNT(JNIEnv *env, jobject thiz,
                                                                jobject bundle) {
    // Get the Bundle class
    jclass bundleClass = env->GetObjectClass(bundle);

    // Get the method ID for 'getParcelable'
    jmethodID getParcelableMethod = env->GetMethodID(bundleClass, "getParcelable", "(Ljava/lang/String;)Landroid/os/Parcelable;");
    if (getParcelableMethod == nullptr) {
        // Handle error if the method is not found
        return reinterpret_cast<jstring>(env->ThrowNew(
                env->FindClass("java/lang/NoSuchMethodError"),
                "No such method getParcelable in Bundle class."));
    }

    // Create a Java String for the key
    jstring key = env->NewStringUTF("student");

    // Call getParcelable to get the Student object
    jobject studentObject = env->CallObjectMethod(bundle, getParcelableMethod, key);

    // Clean up the local reference to the key
    env->DeleteLocalRef(key);

    // Check if the returned object is null
    if (studentObject == nullptr) {
        // Handle the case where the object is not found
        return reinterpret_cast<jstring>(env->ThrowNew(
                env->FindClass("java/lang/NullPointerException"),
                "No Parcelable object found in Bundle with the specified key."));
    }

    // Get the Student class
    jclass studentClass = env->GetObjectClass(studentObject);

    // Get the methods for the fields in Student
    jmethodID getRollMethod = env->GetMethodID(studentClass, "getRoll", "()I");
    jmethodID getNameMethod = env->GetMethodID(studentClass, "getName", "()Ljava/lang/String;");
    jmethodID getAgeMethod = env->GetMethodID(studentClass, "getAge", "()I");
    jmethodID getScoreMethod = env->GetMethodID(studentClass, "getScore", "()I");

    if (getRollMethod == nullptr || getNameMethod == nullptr || getAgeMethod == nullptr || getScoreMethod == nullptr) {
        return reinterpret_cast<jstring>(env->ThrowNew(
                env->FindClass("java/lang/NoSuchMethodError"),
                "No such methods in Student class."));
    }

    // Call the methods to get the field values
    jint roll = env->CallIntMethod(studentObject, getRollMethod);
    auto name = (jstring) env->CallObjectMethod(studentObject, getNameMethod);
    jint age = env->CallIntMethod(studentObject, getAgeMethod);
    jint score = env->CallIntMethod(studentObject, getScoreMethod);

    const char *nameStr = env->GetStringUTFChars(name, nullptr);

    std::string result =
            "Roll: "+ std::to_string(roll)+", Name: " + std::string(nameStr) + ", Age: " + std::to_string(age) + ", Score: " +
            std::to_string(score);

    env->ReleaseStringUTFChars(name, nameStr);

    env->DeleteLocalRef(studentObject);
    env->DeleteLocalRef(studentClass);
    env->DeleteLocalRef(name);

    return env->NewStringUTF(result.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_einfochips_JNI_MainActivity_sendStudentsJNI(JNIEnv *env, jobject thiz,
                                                                jobject arrayListOfStudents) {

    jclass arrayListClass = env->GetObjectClass(arrayListOfStudents);
    if(arrayListClass == nullptr) return env->NewStringUTF("ArrayList class not found");

    jmethodID sizeMethod = env->GetMethodID(arrayListClass, "size", "()I");
    if(sizeMethod == nullptr) return env->NewStringUTF("size method not found");

    jmethodID getMethod = env->GetMethodID(arrayListClass, "get", "(I)Ljava/lang/Object;");
    if(getMethod == nullptr) return env->NewStringUTF("getMethod not found");

    jint size = env->CallIntMethod(arrayListOfStudents, sizeMethod);

    std::string result;
    for (jint i = 0; i < size; i++) {
        jobject student = env->CallObjectMethod(arrayListOfStudents, getMethod, i);
        jclass studentClass = env->GetObjectClass(student);
        jfieldID nameField = env->GetFieldID(studentClass, "name", "Ljava/lang/String;");
        if (nameField == nullptr) return env->NewStringUTF("Field not found...");

        auto name = (jstring) env->GetObjectField(student, nameField);

        const char *nameStr = env->GetStringUTFChars(name, nullptr);
        result += nameStr;
        if(i < size-1) result += ", ";
        env->ReleaseStringUTFChars(name, nameStr);
        env->DeleteLocalRef(name);
        env->DeleteLocalRef(student);
    }

    return env->NewStringUTF(result.c_str());

}

extern "C" JNIEXPORT jint JNICALL
Java_com_einfochips_JNI_MainActivity_sendStudentEnumJNT(JNIEnv *env, jobject thiz,
                                                        jobject studentEnum) {
    jclass enumClass = env->GetObjectClass(studentEnum);
    jmethodID getMethod = env->GetMethodID(enumClass, "getId", "()I");
    jint ordinalValue = env->CallIntMethod(studentEnum, getMethod);
    return ordinalValue;
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_einfochips_JNI_MainActivity_basicTypes(JNIEnv *env, jobject thiz, jint an_int,
                                                jlong a_long, jboolean a_boolean, jfloat a_float,
                                                jdouble a_double, jstring a_string) {
    jclass stringClass = env->FindClass("java/lang/String");
    jboolean isString = env->IsInstanceOf(a_string, stringClass);
    env->DeleteLocalRef(stringClass);

    if(an_int == (int) an_int && a_long == (long) a_long && a_boolean == (bool) a_boolean && a_float == (float) a_float &&
       a_double == (double) a_double && isString) return true;
    else return false;

}
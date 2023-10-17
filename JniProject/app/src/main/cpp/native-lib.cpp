#include <jni.h>
#include <string>


//引入工程的头文件 #include ""
//引入系统的头文件 #inclue <>

//#ifdef/#define  用来打一个标记  c在编译的时候会把头文件 copy 到引入的地方，不管重复引用还是相互引用都会引入一次
//#ifdef  相当于if语句
//extern "C"  采用C的编译方式   在C里面是不允许函数重载的
//JNIEXPORT JNI的一个关键字  不能少 标记为该方法可以被外部调用
//jstring  代表Java中的String
//JNICALL  JNI的一个关键字  可少
//JNIEnv  C和Java相互调用的桥梁
//jobject Java传递下来的对象
//jclass  java传递下来的class对象


/**
 * 构建Java对象
 */

extern "C"
JNIEXPORT jobject JNICALL
Java_com_jni_dome_MainActivity_createPoint(JNIEnv *env, jobject jobj) {

    jclass j_clzz = env->FindClass("com/jni/dome/Point");
    jmethodID j_mid = env->GetMethodID(j_clzz, "<init>", "(II)V");
    jobject point = env->NewObject(j_clzz, j_mid, 23, 34);


    jfieldID j_fid = env->GetFieldID(j_clzz, "x", "I");
    env->SetIntField(point, j_fid, 18);

    jmethodID j_set_y_mid = env->GetMethodID(j_clzz, "setY", "(I)V");
    env->CallVoidMethod(point, j_set_y_mid, 18);
    return point;
}



/**
 * 修改Java属性
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_jni_dome_MainActivity_changeName(JNIEnv *env, jobject jobj) {

    jclass j_clzz = env->GetObjectClass(jobj);
    jfieldID j_fid = env->GetFieldID(j_clzz, "name", "Ljava/lang/String;");
    auto j_str = (jstring) env->GetObjectField(jobj, j_fid);
    // const char *c_str =env->GetStringUTFChars(j_str,NULL);

    jstring j_name = env->NewStringUTF("Dian");
    env->SetObjectField(jobj, j_fid, j_name);

}

/**
 * 修改Java静态属性
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_jni_dome_MainActivity_changeAge(JNIEnv *env, jclass clazz) {
    jfieldID j_fid = env->GetStaticFieldID(clazz, "age", "I");
    jint age = env->GetStaticIntField(clazz, j_fid);
    age+=10;
    env->SetStaticIntField(clazz,j_fid,age);
}


/**
 * 调用Java方法
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_jni_dome_MainActivity_callPlusMethod(JNIEnv *env, jobject jobj) {

   jclass j_clzz = env->GetObjectClass(jobj);

    jmethodID j_mid = env->GetMethodID(j_clzz,"onPlus","(II)I");

    env->CallIntMethod(jobj,j_mid,3,6);
}


/**
 * 调用Java静态方法
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_jni_dome_MainActivity_callUuidMethod(JNIEnv *env, jclass clazz) {

    jmethodID j_mid = env->GetStaticMethodID(clazz,"getUuid","()Ljava/lang/String;");
    auto j_str =(jstring)env->CallStaticObjectMethod(clazz,j_mid);
    return j_str;
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_jni_dome_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


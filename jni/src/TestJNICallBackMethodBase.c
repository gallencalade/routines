#include <jni.h>
#include <stdio.h>
#include "../include/myjni_TestJNICallBackMethodBase.h"

JNIEXPORT void JNICALL Java_myjni_TestJNICallBackMethodBase_nativeMethod
  (JNIEnv *env, jobject thisObj) {
   // Get a class reference for this object
   jclass thisClass = env->GetObjectClass(thisObj);

   // Get the Method ID for method "callback", which takes no arg and return void
   jmethodID midCallBack = env->GetMethodID(thisClass, "callback", "()V");
   if (NULL == midCallBack) return;
   printf("In C, call back Java's callback()\n");
   // Call back the method (which returns void), baed on the Method ID
   env->CallVoidMethod(thisObj, midCallBack);

   jmethodID midCallBackStr = env->GetMethodID(thisClass,
                               "callback", "(Ljava/lang/String;)V");
   if (NULL == midCallBackStr) return;
   printf("In C, call back Java's called(String)\n");
   jstring message = env->NewStringUTF("Hello from C");
   env->CallVoidMethod(thisObj, midCallBackStr, message);

   jmethodID midCallBackAverage = env->GetMethodID(thisClass,
                                  "callbackAverage", "(II)D");
   if (NULL == midCallBackAverage) return;
   jdouble average = env->CallDoubleMethod(thisObj, midCallBackAverage, 2, 3);
   printf("In C, the average is %f\n", average);

   jmethodID midCallBackStatic = env->GetStaticMethodID(thisClass,
                                 "callbackStatic", "()Ljava/lang/String;");
   if (NULL == midCallBackStatic) return;
   jstring resultJNIStr = (jstring)env->CallStaticObjectMethod(thisClass, midCallBackStatic);
   const char *resultCStr = env->GetStringUTFChars(resultJNIStr, NULL);
   if (NULL == resultCStr) return;
   printf("In C, the returned string is %s\n", resultCStr);
   env->ReleaseStringUTFChars(resultJNIStr, resultCStr);
}

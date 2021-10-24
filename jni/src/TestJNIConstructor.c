#include <jni.h>
#include <stdio.h>
#include "../include/myjni_TestJNIConstructor.h"
 
JNIEXPORT jobject JNICALL Java_myjni_TestJNIConstructor_getIntegerObject
          (JNIEnv *env, jobject thisObj, jint number) {
   // Get a class reference for java.lang.Integer
   jclass cls = (*env)->FindClass(env, "java/lang/Integer");
 
   // Get the Method ID of the constructor which takes an int
   jmethodID midInit = (*env)->GetMethodID(env, cls, "<init>", "(I)V");
   if (NULL == midInit) return NULL;
   // Call back constructor to allocate a new instance, with an int argument
   jobject newObj = (*env)->NewObject(env, cls, midInit, number);
 
   // Try running the toString() on this newly create object
   jmethodID midToString = (*env)->GetMethodID(env, cls, "toString", "()Ljava/lang/String;");
   if (NULL == midToString) return NULL;
   jstring resultStr = (*env)->CallObjectMethod(env, newObj, midToString);
   const char *resultCStr = (*env)->GetStringUTFChars(env, resultStr, NULL);
   printf("In C: the number is %s\n", resultCStr);

   //May need to call releaseStringUTFChars() before return
   return newObj;
}

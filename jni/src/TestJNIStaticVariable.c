#include <jni.h>
#include <stdio.h>
#include "../include/myjni_TestJNIStaticVariable.h"
 
JNIEXPORT void JNICALL Java_myjni_TestJNIStaticVariable_modifyStaticVariable
          (JNIEnv *env, jobject thisObj) {
   // Get a reference to this object's class
   jclass cls = (*env)->GetObjectClass(env, thisObj);
 
   // Read the int static variable and modify its value
   jfieldID fidNumber = (*env)->GetStaticFieldID(env, cls, "number", "D");
   if (NULL == fidNumber) return;
   jdouble number = (*env)->GetStaticDoubleField(env, cls, fidNumber);
   printf("In C, the double is %f\n", number);
   number = 77.88;
   (*env)->SetStaticDoubleField(env, cls, fidNumber, number);
}

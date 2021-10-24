#include <jni.h>
#include <stdio.h>
#include "../include/myjni_TestJNIObjectArray.h"
 
JNIEXPORT jobjectArray JNICALL Java_myjni_TestJNIObjectArray_sumAndAverage
          (JNIEnv *env, jobject thisObj, jobjectArray inJNIArray) {
   // Get a class reference for java.lang.Integer
   jclass classInteger = (*env)->FindClass(env, "java/lang/Integer");
   // Use Integer.intValue() to retrieve the int
   jmethodID midIntValue = (*env)->GetMethodID(env, classInteger, "intValue", "()I");
   if (NULL == midIntValue) return NULL;
 
   // Get the value of each Integer object in the array
   jsize length = (*env)->GetArrayLength(env, inJNIArray);
   jint sum = 0;
   int i;
   for (i = 0; i < length; i++) {
      jobject objInteger = (*env)->GetObjectArrayElement(env, inJNIArray, i);
      if (NULL == objInteger) return NULL;
      jint value = (*env)->CallIntMethod(env, objInteger, midIntValue);
      sum += value;
   }
   double average = (double)sum / length;
   printf("In C, the sum is %d\n", sum);
   printf("In C, the average is %f\n", average);
 
   // Get a class reference for java.lang.Double
   jclass classDouble = (*env)->FindClass(env, "java/lang/Double");
 
   // Allocate a jobjectArray of 2 java.lang.Double
   jobjectArray outJNIArray = (*env)->NewObjectArray(env, 2, classDouble, NULL);
 
   // Construct 2 Double objects by calling the constructor
   jmethodID midDoubleInit = (*env)->GetMethodID(env, classDouble, "<init>", "(D)V");
   if (NULL == midDoubleInit) return NULL;
   jobject objSum = (*env)->NewObject(env, classDouble, midDoubleInit, (double)sum);
   jobject objAve = (*env)->NewObject(env, classDouble, midDoubleInit, average);
   // Set to the jobjectArray
   (*env)->SetObjectArrayElement(env, outJNIArray, 0, objSum);
   (*env)->SetObjectArrayElement(env, outJNIArray, 1, objAve);
 
   return outJNIArray;
}

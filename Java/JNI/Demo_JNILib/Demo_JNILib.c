/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Demo_JNILib.c
 * Author: Yen
 *
 * Created on August 19, 2016, 11:29 AM
 */

#include "jni.h"
#include <stdio.h>
#include <stdlib.h>
#include "Demo_JNILib.h"
/*
 * 
 */
JNIEXPORT void JNICALL Java_demo_1jni_Main_sayHelloWorld
  (JNIEnv *env, jobject obj){
    printf("Hello World");
}

/*
 *  MapboxVectorTileParser_jni.cpp
 *  WhirlyGlobeLib
 *
 *  Created by Steve Gifford on 5/25/16.
 *  Copyright 2011-2016 mousebird consulting
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#import <jni.h>
#import "Maply_jni.h"
#import "com_mousebird_maply_MapboxVectorTileParser.h"
#import "WhirlyGlobe.h"

using namespace Eigen;
using namespace WhirlyKit;
using namespace Maply;

JNIEXPORT void JNICALL Java_com_mousebird_maply_MapboxVectorTileParser_nativeInit
(JNIEnv *env, jclass cls)
{
    MapboxVectorTileParserClassInfo::getClassInfo(env,cls);
}

JNIEXPORT void JNICALL Java_com_mousebird_maply_MapboxVectorTileParser_initialise
(JNIEnv *env, jobject obj)
{
    try
    {
        MapboxVectorTileParserClassInfo *classInfo = MapboxVectorTileParserClassInfo::getClassInfo();
        MapboxVectorTileParser *inst = new MapboxVectorTileParser();
        classInfo->setHandle(env,obj,inst);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapboxVectorTileParser::initialise()");
    }
}

JNIEXPORT void JNICALL Java_com_mousebird_maply_MapboxVectorTileParser_dispose
(JNIEnv *env, jobject obj)
{
    try
    {
        MapboxVectorTileParserClassInfo *classInfo = MapboxVectorTileParserClassInfo::getClassInfo();
        MapboxVectorTileParser *inst = classInfo->getObject(env,obj);
        if (!inst)
            return;
        delete inst;
        
        classInfo->clearHandle(env,obj);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapboxVectorTileParser::dispose()");
    }
}

JNIEXPORT jobjectArray JNICALL Java_com_mousebird_maply_MapboxVectorTileParser_parseDataNative
(JNIEnv *env, jobject obj, jbyteArray data)
{
    try
    {
        MapboxVectorTileParserClassInfo *classInfo = MapboxVectorTileParserClassInfo::getClassInfo();
        MapboxVectorTileParser *inst = classInfo->getObject(env,obj);
        if (!inst)
            return NULL;
        
        jbyte *bytes = env->GetByteArrayElements(data,NULL);
        RawDataWrapper rawData(bytes,env->GetArrayLength(data),false);
        env->ReleaseByteArrayElements(data,bytes, 0);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in MapboxVectorTileParser::parseDataNative()");
    }
    
    return NULL;
}
#include <MasonryWrapper.h>
#include "MasonryCore.h"
#include "DiscreteRect.h"
#include <vector>

#include <android/log.h>

#define  LOG_TAG    "Masonry"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

/* Source for class me_clocko_photonow_masonry_Masonry */

#ifdef __cplusplus
extern "C" {
#endif

DiscreteRect javaDiscreteRectToCppDiscreteRect(JNIEnv * jenv, jobject object) {
    DiscreteRect empty(0, 0, 0, 0);
    jclass discreteRectClass = jenv->FindClass("me/clocko/photonow/masonry/DiscreteRect");
    if (discreteRectClass == NULL) {
        LOGE("DiscreteRect class not found");
        return empty;
    }

    jfieldID xFieldID = jenv->GetFieldID (discreteRectClass, "x", "I");    
    if (xFieldID == NULL) {
        return empty;
    }

    jfieldID yFieldID = jenv->GetFieldID (discreteRectClass, "y", "I");    
    if (yFieldID == NULL) {
        return empty;
    }

    jfieldID widthFieldID = jenv->GetFieldID (discreteRectClass, "width", "I");    
    if (widthFieldID == NULL) {
        return empty;
    }

    jfieldID heightFieldID = jenv->GetFieldID (discreteRectClass, "height", "I");    
    if (heightFieldID == NULL) {
        return empty;
    }

    int x = reinterpret_cast<int> (jenv->GetIntField(object, xFieldID)); 
    int y = reinterpret_cast<int> (jenv->GetIntField(object, yFieldID)); 
    int width = reinterpret_cast<int> (jenv->GetIntField(object, widthFieldID)); 
    int height = reinterpret_cast<int> (jenv->GetIntField(object, heightFieldID)); 

    return DiscreteRect(x, y, width, height);
}

jobject cppDiscreteRectToJavaDiscreteRect(JNIEnv * jenv, const DiscreteRect& discreteRect) {
    jclass discreteRectClass = jenv->FindClass("me/clocko/photonow/masonry/DiscreteRect");
    if (discreteRectClass == NULL) {
        return NULL;
    }
    
    jmethodID constructorID = jenv->GetMethodID(discreteRectClass, "<init>", "(IIII)V");
    if (constructorID == NULL) {
        return NULL;
    }

    jobject result = jenv->NewObject(discreteRectClass, constructorID, discreteRect.x, discreteRect.y, discreteRect.width, discreteRect.height);

    return result;
}

std::vector<DiscreteRect> javaListToDiscreteRectVector(JNIEnv * jenv, jobject javaList) {
    std::vector<DiscreteRect> emptyList;
    jclass listClass = jenv->FindClass("java/util/List");
    if (listClass == NULL) {
        LOGE("List not found");
        return emptyList;
    }

    // Get "java.util.List.get(int location)" MethodID
    jmethodID getMethodID = jenv->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
    if (getMethodID == NULL) {
        return emptyList;
    }

    // Get "int java.util.List.size()" MethodID
    jmethodID sizeMethodID = jenv->GetMethodID (listClass, "size", "()I");
    if (sizeMethodID == NULL) {
        return emptyList;
    }

    // Call "int java.util.List.size()" method and get count of items in the list.
    int listItemsCount = (int)jenv->CallIntMethod(javaList, sizeMethodID);

    std::vector<DiscreteRect> result;

    for (int i = 0; i < listItemsCount; ++i) {
        // Call "java.util.List.get" method and get IdentParams object by index.
        jobject item = jenv->CallObjectMethod(javaList, getMethodID, i);
        if (item == NULL) {
            return emptyList;
        }
        result.push_back(javaDiscreteRectToCppDiscreteRect(jenv, item));
    }
    return result;
}

jobject discreteRectVectorToJavaList(JNIEnv * jenv, const std::vector<DiscreteRect>& discreteRectVector) {
    jclass listClass = jenv->FindClass("java/util/ArrayList");
    if (listClass == NULL) {
        LOGE("ArrayList not found");
        return NULL;
    }

    jmethodID constructorID = jenv->GetMethodID(listClass, "<init>", "()V");
    if (constructorID == NULL) {
        LOGE("ArrayList constructor not found");
        return NULL;
    }

    jmethodID addMethodID = jenv->GetMethodID(listClass, "add", "(Ljava/lang/Object;)Z");
    if (addMethodID == NULL) {
        LOGE("ArrayList add method not found");
        return NULL;
    }

    jobject result = jenv->NewObject(listClass, constructorID);

    for (DiscreteRect rect: discreteRectVector) {
        jobject javaRect = cppDiscreteRectToJavaDiscreteRect(jenv, rect);
        if (javaRect == NULL) {
            LOGE("Unable to convert C++ DiscreteRect to Java DiscreteRect");
            return NULL;
        }
        jenv->CallBooleanMethod(result, addMethodID, javaRect);
    }
    return result;
}

/*
 * Class:     me_clocko_photonow_masonry_Masonry
 * Method:    masonry
 * Signature: (ILjava/util/List;)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_me_clocko_photonow_masonry_Masonry_masonry
  (JNIEnv * jenv, jclass jcls, jint gridWidth, jobject photos) {
    
    std::vector<DiscreteRect> photoVector = javaListToDiscreteRectVector(jenv, photos);
    int width = reinterpret_cast<int> (gridWidth);
    
    std::vector<DiscreteRect> result = masonry(width, photoVector);

    return discreteRectVectorToJavaList(jenv, result);
}


#ifdef __cplusplus
}
#endif

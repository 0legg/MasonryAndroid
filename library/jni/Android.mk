LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)                       
LOCAL_MODULE    := masonry
LOCAL_SRC_FILES := MasonryWrapper.cpp
LOCAL_SRC_FILES += Masonry/DiscreteRect.cpp \
                   Masonry/MasonryCore.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/Masonry
LOCAL_CPPFLAGS  += -std=c++11
LOCAL_LDLIBS    := -lm -llog
include $(BUILD_SHARED_LIBRARY)
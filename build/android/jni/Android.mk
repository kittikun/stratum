LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)

APP_STL = gnustl_static

LOCAL_CFLAGS += -I$(LOCAL_PATH)/include/ \
		-I$(NDK_ROOT)/platforms/android-5/arch-arm/usr/include \
		-I$(NDK_ROOT)/sources/cxx-stl/gnu-libstdc++/4.7/include \
		-I$(NDK_ROOT)/sources/cxx-stl/gnu-libstdc++/4.7/libs/armeabi/include

LOCAL_LDLIBS += -L$(LOCAL_PATH)/lib/  \
		-L$(NDK_ROOT)/sources/cxx-stl/gnu-libstdc++/4.7/libs/armeabi \
		-lgnustl_static \
		-lboost_system -lboost_chrono -lboost_date_time -lboost_filesystem \
		-lboost_iostreams -lboost_log -lboost_program_options -lboost_thread \
		-lboost_regex-gcc -lboost_signals -lboost_system \

$(warning $(LOCAL_PATH))

#LOCAL_CPPFLAGS += -std=gnu++0x
LOCAL_CPPFLAGS += -fexceptions
LOCAL_CPPFLAGS += -frtti 
  
LOCAL_MODULE    := stratum
LOCAL_SRC_FILES := stratum.c

LOCAL_SRC_FILES += ../../../src/log.cpp

 
include $(BUILD_SHARED_LIBRARY)
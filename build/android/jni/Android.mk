LOCAL_PATH := $(call my-dir)

include $(call all-subdir-makefiles) 

include $(CLEAR_VARS)

APP_STL = gnustl_static

LOCAL_CFLAGS += -I$(LOCAL_PATH)/include/ \
		-I$(NDK_ROOT)/platforms/android-14/arch-arm/usr/include \
#		-I$(NDK_ROOT)/sources/cxx-stl/gnu-libstdc++/4.7/include \
#		-I$(NDK_ROOT)/sources/cxx-stl/gnu-libstdc++/4.7/libs/armeabi-v7a/include

LOCAL_LDLIBS += -L$(LOCAL_PATH)/lib/
#		-L$(NDK_ROOT)/sources/cxx-stl/gnu-libstdc++/4.7/libs/armeabi \
#		-lgnustl_static \
#		-L$(LOCAL_PATH)/lib/libboost_log_setup-gcc-mt-1_53.a \
#       	-llibboost_chrono-gcc-mt-1_53 -llibboost_date_time-gcc-mt-1_53 -llibboost_filesystem-gcc-mt-1_53 \
#       	-llibboost_iostreams-gcc-mt-1_53 -llibboost_log_setup-gcc-mt-1_53 -llibboost_program_options-gcc-mt-1_53 \
#       	-llibboost_thread-gcc-mt-1_53 \
#       	-llibboost_regex-gcc-mt-1_53 -llibboost_signals-gcc-mt-1_53 -llibboost_system-gcc-mt-1_53 \

$(warning $(LOCAL_PATH))

LOCAL_CPPFLAGS += -std=gnu++0x
LOCAL_CPPFLAGS += -fexceptions
LOCAL_CPPFLAGS += -frtti 
  
LOCAL_MODULE    := stratum
LOCAL_SRC_FILES := stratum.c

LOCAL_SRC_FILES += ../../../src/log.cpp

LOCAL_STATIC_LIBRARIES := boost_system boost_log boost_iostreams

 
include $(BUILD_SHARED_LIBRARY)
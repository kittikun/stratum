#include <string.h>
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

jstring Java_com_kittikun_stratum_stratum_StratumActivity_invokeNativeFunction(JNIEnv* env, jobject javaThis)
{
    return (*env)->NewStringUTF(env, "Hello from native code!");
}

#ifdef __cplusplus
}
#endif

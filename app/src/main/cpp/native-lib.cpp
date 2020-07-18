
#include <jni.h>
#include <string>
#include <android/native_window_jni.h>

#include "XLog.h"
#include "IPlayerPorxy.h"
extern "C"
{


JNIEXPORT
jint JNI_OnLoad(JavaVM *vm,void *res)
{
    IPlayerPorxy::Get()->Init(vm);

    /*IPlayerPorxy::Get()->Open("/sdcard/v1080.mp4");
    IPlayerPorxy::Get()->Start();


    IPlayerPorxy::Get()->Open("/sdcard/1080.mp4");
    IPlayerPorxy::Get()->Start();*/

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL
Java_derek_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    // TODO
    ANativeWindow *win = ANativeWindow_fromSurface(env,surface);
    IPlayerPorxy::Get()->InitView(win);
}


JNIEXPORT void JNICALL
Java_derek_xplay_OpenUrl_Open(JNIEnv *env, jobject instance, jstring url_) {
    const char *url = env->GetStringUTFChars(url_, 0);

    IPlayerPorxy::Get()->Open(url);
    IPlayerPorxy::Get()->Start();
    //IPlayerPorxy::Get()->Seek(0.5);

    env->ReleaseStringUTFChars(url_, url);
}

JNIEXPORT jdouble JNICALL
Java_derek_xplay_MainActivity_PlayPos(JNIEnv *env, jobject instance) {

    // TODO
    return IPlayerPorxy::Get()->PlayPos();

}

JNIEXPORT void JNICALL
Java_derek_xplay_MainActivity_Seek(JNIEnv *env, jobject instance, jdouble pos) {

    IPlayerPorxy::Get()->Seek(pos);

}

JNIEXPORT void JNICALL
Java_derek_xplay_XPlay_PlayOrPause(JNIEnv *env, jobject instance) {

    IPlayerPorxy::Get()->SetPause(!IPlayerPorxy::Get()->IsPause());

}

}
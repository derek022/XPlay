#include <jni.h>
#include <string>
extern "C"{
#include <libavformat/avformat.h>
}

#include <android/native_window_jni.h>
#include <android/native_window.h>

#include "FFDemux.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"


class TestObs : public IObserver
{
public:
    virtual void Update(XData d){
//        XLOGI("Test Obs Update data size is %d",d.size);
    }
};

IVideoView * view = nullptr;


extern "C"
{


JNIEXPORT jstring JNICALL
Java_derek_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject  jobject1,jstring jurl) {
    std::string hello = "Hello from C++";
    const char* url = env->GetStringUTFChars(jurl,NULL);


    ///////////////////////////////////////////
    // 测试代码
    IObserver* tobs = new TestObs();




    IDemux * de = new FFDemux();
    de->Open(url);

    IDecode * vdecode = new FFDecode();
    IDecode * adecode = new FFDecode();

    vdecode->Open(de->GetVPara());
    adecode->Open(de->GetAPara());

    de->AddObs(vdecode);
    de->AddObs(adecode);


    vdecode->AddObs(view);

    de->Start();
    vdecode->Start();
    adecode->Start();

//    XSleep(3000);
//    de->Stop();

//    while(true)
//    {
//        XData d = de->Read();
//
//    }

    env->ReleaseStringUTFChars(jurl,url);
    return env->NewStringUTF(hello.c_str());
}


JNIEXPORT void JNICALL
Java_derek_xplay_XPlay_InitView(JNIEnv *env, jobject thiz, jobject holder) {

    ANativeWindow * nativeWindow = ANativeWindow_fromSurface(env,holder);

    view = new GLVideoView();
    view->SetRender(nativeWindow);

    //XEGL::Get()->Init(nativeWindow);

    //XShader shader;
    //shader.Init();



}


}
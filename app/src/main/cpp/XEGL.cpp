//
// Created by derek on 2020-03-08.
//

#include <android/native_window.h>
#include "XEGL.h"
#include "XLog.h"
#include <EGL/egl.h>

class CXEGL : public XEGL
{
public:
    EGLDisplay  display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;

    virtual void Draw()
    {
        if (display == EGL_NO_DISPLAY || surface == EGL_NO_SURFACE)
        {
            return;
        }
        eglSwapBuffers(display,surface);
    }

    virtual bool Init(void* win)
    {
        ANativeWindow * nwin = (ANativeWindow*)win;

        // 初始化EGL

        // 1、获取EGLDisplay 对象，显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY)
        {

        }
        XLOGD("eglGetDisplay success");
        // 2、初始化display
        if (EGL_TRUE != eglInitialize(display,0,0))
        {
            XLOGD("eglInitialize failed");
            return false;
        }
        XLOGD("eglInitialize success");
        //3、 获取配置并创建surface

        EGLint configSpec[] = {
                EGL_RED_SIZE,8,
                EGL_GREEN_SIZE,8,
                EGL_BLUE_SIZE,8,
                EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
                EGL_NONE
        };
        EGLConfig config = 0;
        EGLint configNum = 0;
        if(EGL_TRUE != eglChooseConfig(display,configSpec,&config,1,&configNum))
        {
            XLOGD("eglChooseConfig failed");
            return false;
        }

        XLOGD("eglChooseConfig success");

        // 创建surface
        surface = eglCreateWindowSurface(display,config,nwin, nullptr);
        if (surface == EGL_NO_SURFACE)
        {
            XLOGD("eglCreateWindowSurface failed");
            return false;
        }

        // 4、 创建并打开EGL上下文
        const EGLint ctxAttr[] = {
                EGL_CONTEXT_CLIENT_VERSION,2,
                EGL_NONE
        };
        context = eglCreateContext(display,config,EGL_NO_CONTEXT,ctxAttr);
        if (config == EGL_NO_CONTEXT)
        {
            XLOGD("eglCreateContext failed");
            return false;
        }
        XLOGD("eglCreateContext success");

        if (EGL_TRUE != eglMakeCurrent(display,surface,surface,context))
        {
            XLOGD("eglMakeCurrent failed");
            return false;
        }
        XLOGD("eglMakeCurrent success");
        return true;
    }

};


XEGL * XEGL::Get()
{
    static CXEGL egl;

    return &egl;
}
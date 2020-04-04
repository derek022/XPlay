//
// Created by derek on 2020-03-08.
//

#ifndef XPLAY_GLVIDEOVIEW_H
#define XPLAY_GLVIDEOVIEW_H


#include "XData.h"
#include "IVideoView.h"

class XTexture;

class GLVideoView : public IVideoView
{
public:
    virtual void SetRender(void * win);

    virtual void Render(XData data);

protected:
    void * view = nullptr;
    XTexture * txt = nullptr;
};


#endif //XPLAY_GLVIDEOVIEW_H

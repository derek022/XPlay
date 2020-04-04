//
// Created by derek on 2020-02-15.
//

#ifndef XPLAY_FFDEMUX_H
#define XPLAY_FFDEMUX_H



#include "IDemux.h"
#include "XLog.h"

// 前项声明
struct AVFormatContext;

class FFDemux : public IDemux{
public:
    virtual bool Open(const char *url);

    virtual XData Read();

    virtual XParameter GetVPara();

    // 获取音频流参数
    virtual XParameter GetAPara();


    FFDemux();

private:
    AVFormatContext * ic = nullptr;
    int audioStreamIdx = 0;
    int videoStreamIdx = 1;
};


#endif //XPLAY_FFDEMUX_H

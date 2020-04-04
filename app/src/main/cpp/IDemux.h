//
// Created by derek on 2020-02-15.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H

#include <android/log.h>

#include "XData.h"
#include "IObserver.h"
#include "XParameter.h"

class IDemux : public IObserver {
public:
    // 打开文件，视频文件，rtmp,http rtsp
    virtual bool Open(const char * url) = 0;

    // 获取视频流参数
    virtual XParameter GetVPara() = 0;

    // 获取音频流参数
    virtual XParameter GetAPara() = 0;

    // 读取数据，数据由调用者清理
    virtual XData Read() = 0;

    // 总时长 （毫秒）
    int totalMs = 0;

    virtual void Main();
};


#endif //XPLAY_IDEMUX_H

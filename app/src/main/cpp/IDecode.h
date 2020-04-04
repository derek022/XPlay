//
// Created by derek on 2020-02-22.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H


#include "XParameter.h"
#include "IObserver.h"
#include <list>

class IDecode : public IObserver
{
public:
    virtual bool Open(XParameter x) = 0;

    // future 模型， 发送数据
    virtual bool SendPacket(XData pkt) = 0;

    // 接受数据
    virtual XData RecvFrame() = 0;

    // 由主体notify的数据,  阻塞式
    virtual void Update(XData pkt);

    bool isAudio = false;

    //最大的缓存队列：  100 帧，每秒25帧的话，缓存4秒
    int maxList = 100;

protected:
    virtual void Main();
    std::list<XData> packts;

    std::mutex packsMutes;
};


#endif //XPLAY_IDECODE_H

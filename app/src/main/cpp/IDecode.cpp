//
// Created by derek on 2020-02-22.
//

#include "IDecode.h"
#include "XLog.h"

void IDecode::Update(XData pkt)
{
    if(this->isAudio != pkt.isAudio)
    {
        return;
    }

    // s生产者
    while (!isExit)
    {
        packsMutes.lock();

        // 阻塞
        if (packts.size()<maxList)
        {
            packts.push_back(pkt);
            packsMutes.unlock();
            break;
        }
        packsMutes.unlock();

        XSleep(1);
    }


}

void IDecode::Main()
{
    while (!isExit)
    {

        packsMutes.lock();

        if (packts.empty())
        {
//            packts.unique();
            packsMutes.unlock();
            // 休眠

            XSleep(1);

            continue;
        }
        // 取出packet  消费者
        XData data = packts.front();
        packts.pop_front();

        if (this->SendPacket(data))
        {
            // 获取解码帧数据
            XData frame = RecvFrame();
            if (!frame.data) break;

            XLOGI("RecvFrame() %d ",frame.size);
            // 发送数据 观察者
            this->Notify(frame);

        }

        data.Drop();

        packsMutes.unlock();
    }



}
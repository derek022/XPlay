//
// Created by derek on 2020-02-22.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H



#include "IDecode.h"
struct AVCodecContext;
struct AVFrame;

class FFDecode : public IDecode {
public:
    virtual bool Open(XParameter x);

    virtual bool SendPacket(XData pkt);

    //从线程中获取解码结果， 再次调用会复用上次空间，线程不安全
    virtual XData RecvFrame();

protected:
    AVCodecContext* codecc = nullptr;
    AVFrame * frame = nullptr;
};


#endif //XPLAY_FFDECODE_H

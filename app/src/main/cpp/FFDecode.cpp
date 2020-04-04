//
// Created by derek on 2020-02-22.
//

#include "FFDecode.h"
#include "XLog.h"

extern "C"{
#include <libavcodec/avcodec.h>
}

bool FFDecode::Open(XParameter x)
{
    if ( !x.para ) return false;

    AVCodecParameters* p = x.para;
    //1. 查找解码器
    AVCodec* cd = avcodec_find_decoder(p->codec_id);
    if (!cd)
    {
        XLOGE(" avcodec_find_decoder %d ",p->codec_id);
        return false;
    }
    //2. 创建解码器上下文,并复制参数
    codecc = avcodec_alloc_context3(cd);
    avcodec_parameters_to_context(codecc,p);
    // 多线程解码
    codecc->thread_count = 8;

    //3. 打开解码器
    int re = avcodec_open2(codecc,0,0);
    if (re != 0)
    {
        XLOGE("avcodec_open2 failed %d ",codecc->codec_id);
        ffcode2str(re);
        return false;
    }

    XLOGI(" avcodec_open2 success ");

    if (codecc->codec_type == AVMEDIA_TYPE_AUDIO){
        this->isAudio = true;
    }else {
        this->isAudio = false;
    }

    return true;
}

bool FFDecode::SendPacket(XData pkt)
{
    if (pkt.size == 0 || !pkt.data ) return false;
    if (!codecc)
    {
        return false;
    }

    int re = avcodec_send_packet(codecc, reinterpret_cast<const AVPacket *>(pkt.data));
    if (re != 0)
    {
//        XLOGE(" avcodec_send_packet failed. ");
        ffcode2str(re);
        return false;
    }

    return  true;
}

XData FFDecode::RecvFrame()
{
    if (!codecc)
    {
        return XData();
    }
    if (!frame)
    {
        frame = av_frame_alloc();
    }

    int re = avcodec_receive_frame(codecc,frame);
    if (re != 0)
    {
        return XData();
    }

    XData d;
    d.data = (unsigned char *)(frame);
    if (codecc->codec_type == AVMEDIA_TYPE_VIDEO)
    {
        // 平面格式
        d.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2])*frame->height;

        // 视频的宽高
        d.width = frame->width;
        d.height = frame->height;
    }
    else
    {
        // 样本字节数 *  单通道样本数 * 通道数
        d.size = av_get_bytes_per_sample((AVSampleFormat)frame->format) * frame->nb_samples * 2;
    }

    memcpy(d.datas,frame->data, sizeof(d.datas));

    return d;
}


//
// Created by derek on 2020-02-15.
//


#include "FFDemux.h"
extern  "C" {
#include "libavformat/avformat.h"
}



bool FFDemux::Open(const char *url) {

    XLOGI("open file %s ",url);

    int re = avformat_open_input(&ic,url,0,0);
    if (re != 0)
    {
        XLOGE("open file %s failed.",url);
        ffcode2str(re);
        return false;
    }
    XLOGI("open file  %s  success!",url);

    re = avformat_find_stream_info(ic,0);
    if (re != 0)
    {
        XLOGE("ffmepg  avformat_find_stream_info %s failed. ",url);
        ffcode2str(re);
        return false;
    }

    totalMs = ic->duration/(AV_TIME_BASE/1000);
    XLOGI("duration = %d ",totalMs);

    return true;
}


XParameter FFDemux::GetVPara()
{
    if (!ic)
    {
        XLOGE("GetVPara failed, ic is null.");
        return XParameter();
    }
    // 查找视频流索引
    int re = av_find_best_stream(ic,AVMEDIA_TYPE_VIDEO,-1,-1,0,0);
    if (re < 0)
    {
        XLOGE("av_find_best_stream failed.");
        return XParameter();
    }

    videoStreamIdx = re;
    XParameter para ;
    para.para = ic->streams[re]->codecpar;
    return para;
}

XParameter FFDemux::GetAPara()
{
    if (!ic)
    {
        XLOGE("GetAPara failed, ic is null.");
        return XParameter();
    }
    // 查找视频流索引
    int re = av_find_best_stream(ic,AVMEDIA_TYPE_AUDIO,-1,-1,0,0);
    if (re < 0)
    {
        XLOGE("av_find_best_stream failed.");
        return XParameter();
    }

    audioStreamIdx = re;
    XParameter para ;
    para.para = ic->streams[re]->codecpar;
    return para;
}

XData FFDemux::Read() {
    XData d;
    if (!ic) return d;

    AVPacket * pkt = av_packet_alloc();
    int re = av_read_frame(ic,pkt);
    if (re != 0)
    {
        av_packet_free(&pkt);
        return d;
    }

    d.data = reinterpret_cast<unsigned char *>(pkt);
    d.size = pkt->size;
//    XLOGI("pkt  pts is %ld size is %d",pkt->pts,pkt->size);
    if (pkt->stream_index == audioStreamIdx){
        d.isAudio = true;
    }else if (pkt->stream_index == videoStreamIdx){
        d.isAudio = false;
    }else{
        av_packet_free(&pkt);
        return XData();
    }
    return d;
}


FFDemux::FFDemux():ic(nullptr) {
    static bool  isFirst = true;
    if (isFirst){
        isFirst = false;

        // 封装格式
        av_register_all();

        // 网络初始化
        avformat_network_init();

        // 初始化解码格式
        avcodec_register_all();

    }

}

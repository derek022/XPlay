//
// Created by derek on 2020-04-04.
//

#include "FFResample.h"
#include "XLog.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h"
}

bool FFResample::Open(XParameter in,XParameter out)
{
    actx = swr_alloc();

    actx = swr_alloc_set_opts(actx,
            av_get_default_channel_layout(2),
            AV_SAMPLE_FMT_S16,
            (AVSampleFormat)in.para->sample_rate,
            av_get_default_channel_layout(in.para->channels),
            (AVSampleFormat)in.para->format,in.para->sample_rate,
            0,0
            );

    int re = swr_init(actx);
    if (re != 0)
    {
        XLOGE("swr init failed");
        return false;
    }
    


    return true;

}
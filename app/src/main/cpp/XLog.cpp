//
// Created by derek on 2020-02-22.
//

extern "C"{
#include <libavutil/error.h>
}

#include "XLog.h"

void ffcode2str(int code)
{
    char buf[1024] = {0};
    av_strerror(code,buf, sizeof(buf));
    XLOGE("msg: %s",buf);
}
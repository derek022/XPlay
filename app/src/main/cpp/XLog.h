//
// Created by derek on 2020-02-15.
//

#ifndef XPLAY_XLOG_H
#define XPLAY_XLOG_H

#ifdef ANDROID
#include <android/log.h>
#define TAG "XPlay"
#define XLOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define XLOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define XLOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)

void ffcode2str(int code);

#else


#endif
#endif //XPLAY_XLOG_H

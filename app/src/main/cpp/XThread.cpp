//
// Created by derek on 2020-02-16.
//

#include "XThread.h"
#include "XLog.h"
#include <thread>
using namespace std;

/**
 * 线程睡眠 ,毫秒级别
 * @param mis
 */
void XSleep(int mis)
{
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}

// 启动
void XThread::Start()
{
    isExit = false;
    thread th(&XThread::ThreadMain,this);
    th.detach();
}

// 停止，isExit 不安全的退出
void XThread::Stop()
{
    XLOGI("停止线程begin");
    isExit = true;

    for (int i = 0; i < 200; ++i) {
        if(!isRunning){
            XLOGI("停止线程成功");
            return;
        }
        XSleep(1);
    }

    XLOGI("停止线程超时。。。");
}


void XThread::ThreadMain()
{
    isRunning = true;
    XLOGI("进入线程");
    Main();
    XLOGI("线程退出");
    isRunning = false;
}
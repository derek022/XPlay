//
// Created by derek on 2020-02-16.
//

#ifndef XPLAY_XTHREAD_H
#define XPLAY_XTHREAD_H

void XSleep(int mis);

// c++ 11 线程
class XThread {
public:
    // 启动
    virtual void Start();
    // 停止，isExit 不安全的退出
    virtual void Stop();
    // 主函数
    virtual void Main(){}

protected:
    bool isExit = false;
    bool isRunning = false;

private:
    virtual void ThreadMain();
};


#endif //XPLAY_XTHREAD_H

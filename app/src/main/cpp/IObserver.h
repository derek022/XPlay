//
// Created by derek on 2020-02-22.
//

#ifndef XPLAY_IOBSERVER_H
#define XPLAY_IOBSERVER_H


#include "XData.h"
#include "XThread.h"
#include <vector>
#include <mutex>

// 观察者，主体
class IObserver : public XThread {
public:
    // 更新数据
    virtual void Update(XData data){}
    // 添加观察者，(线程安全）
    void AddObs(IObserver * obs);

    // 通知观察者
    void Notify(XData data);

protected:
    std::vector<IObserver *> obss;
    std::mutex mtx;
};


#endif //XPLAY_IOBSERVER_H

//
// Created by derek on 2020-02-22.
//

#include "IObserver.h"

void IObserver::AddObs(IObserver * obs)
{
    if (!obs)
        return;
    mtx.lock();
    obss.push_back(obs);
    mtx.unlock();
}


void IObserver::Notify(XData data)
{
    mtx.lock();
    for (int i = 0; i < obss.size(); ++i) {
        obss[i]->Update(data);
    }
    mtx.unlock();
}

//
// Created by derek on 2020-04-04.
//

#ifndef XPLAY_IRESAMPLE_H
#define XPLAY_IRESAMPLE_H


#include "IObserver.h"
#include "XParameter.h"

class IResample: public IObserver
{
public:
    virtual bool Open(XParameter in,XParameter out = XParameter()) = 0;

};


#endif //XPLAY_IRESAMPLE_H

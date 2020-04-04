//
// Created by derek on 2020-03-08.
//

#ifndef XPLAY_XEGL_H
#define XPLAY_XEGL_H


class XEGL {

public:
    virtual bool Init(void* win) = 0;
    virtual void Draw() = 0;

    static XEGL *Get();

protected:
    XEGL(){}

};


#endif //XPLAY_XEGL_H

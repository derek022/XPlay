//
// Created by derek on 2020-03-08.
//

#ifndef XPLAY_XSHADER_H
#define XPLAY_XSHADER_H


class XShader {
public:
    virtual bool Init();

    // 获取材质并映射到内存,索引对应纹理的层次
    void GetTexture(unsigned int index,int width,int height, unsigned char * buf);

    virtual void Draw();

protected:
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0};
};


#endif //XPLAY_XSHADER_H

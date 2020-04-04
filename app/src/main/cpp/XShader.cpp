//
// Created by derek on 2020-03-08.
//

#include "XShader.h"
#include "XLog.h"
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <cstdio>

#define GET_STR(x) #x
// 顶点着色器 glsl
static const char * vertexShader = GET_STR(
        attribute vec4 aPosition; // 顶点坐标
        attribute vec2 aTexCoord; // 材质坐标
        varying vec2 vTexCoord;   // 输出的材质坐标
        void main(){
            vTexCoord = vec2(aTexCoord.x,1.0-aTexCoord.y);
            gl_Position = aPosition;
        }
);

// 片元着色器glsl， 软解码和部分x86硬解码
static const char * fragYUV420P = GET_STR(
        // 传入参数
varying vec2 vTexCoord; // 顶点着色器传递的坐标

        precision mediump float; // 精度
        uniform sampler2D yTexture;  // 输入的材质 （不透明灰度，单像素）
uniform sampler2D uTexture;
uniform sampler2D vTexture;

void main(){
    vec3 yuv;
    vec3 rgb;
    // 计算yuv的值
    yuv.r = texture2D(yTexture,vTexCoord).r;
    yuv.g = texture2D(uTexture,vTexCoord).r - 0.5;
    yuv.b = texture2D(vTexture,vTexCoord).r - 0.5;
    rgb = mat3(1.0,     1.0,   1.0,
               0.0,-0.39465,2.03211,
               1.13983,-0.5806,0.0)*yuv;
    // 输出像素颜色
    gl_FragColor = vec4(rgb,1.0);
}

);


// 顶点和片元初始化函数
static GLuint InitShader(const char* code,GLint type)
{
    // 创建shader
    GLuint sh = glCreateShader(type);
    if (sh == 0){
        XLOGD("glCreateShader %d failed",type);
        return 0;
    }

    // 加载shader
    glShaderSource(sh,
                   1,  // shader 数量
                   &code, // shader 代码
                   0  // 代码长度
    );

    // 编译shader
    glCompileShader(sh);
    // 获取编译情况
    GLint  status;
    glGetShaderiv(sh,GL_COMPILE_STATUS,&status);
    if (status == GL_FALSE)
    {
        XLOGD("glCompileShader failed");
        return 0;
    }

    XLOGD("glCompileShader success");

    return sh;
}


bool XShader::Init()
{
    // 顶点和片元 shader 初始化，
    vsh = InitShader(vertexShader,GL_VERTEX_SHADER); // 顶点

    if (vsh == 0)
    {
        XLOGE("InitShader GL_VERTEX_SHADER failed");
        return false;
    }
    XLOGE("InitShader GL_VERTEX_SHADER success");


    fsh = InitShader(fragYUV420P,GL_FRAGMENT_SHADER); // 片元yuv420p 初始化

    if (fsh == 0)
    {
        XLOGE("InitShader GL_FRAGMENT_SHADER failed");
        return false;
    }
    XLOGE("InitShader GL_FRAGMENT_SHADER success");


    // 创建渲染程序
    program = glCreateProgram();
    if (program == 0)
    {
        XLOGD("glCreateProgram failed");
        return false;
    }

    // 向渲染程序当中加入着色器
    glAttachShader(program,vsh);
    glAttachShader(program,fsh);

    // 开始进行连接程序

    glLinkProgram(program);
    GLint status = 0;
    glGetProgramiv(program,GL_LINK_STATUS,&status);

    if (status != GL_TRUE)
    {
        XLOGD("glLinkProgram failed");
        return false;
    }

    glUseProgram(program);


    // 加入顶点数据  两个三角形 组成正方形
    static  float vers[] = {
            1.0f,-1.0f,0.0f,
            -1.0f,-1.0f,0.0f,
            1.0f,1.0f,0.0f,
            -1.0f,1.0f,0.0f,
    };
    GLuint  apos =(GLuint) glGetAttribLocation(program,"aPosition");

    glEnableVertexAttribArray(apos);
    XLOGD("glEnableVertexAttribArray aps");
    // 传递顶点
    glVertexAttribPointer(apos,3,GL_FLOAT,GL_FALSE,12,vers);


    // 加入材质坐标数据
    static  float txts[] = {
            1.0f,0.0f,
            0.0f,0.0f,
            1.0f,1.0f,
            0.0,1.0
    };

    GLuint atex = (GLuint) glGetAttribLocation(program,"aTexCoord");
    glEnableVertexAttribArray(atex);

    XLOGD("glEnableVertexAttribArray atex");

    glVertexAttribPointer(atex,2,GL_FLOAT,GL_FALSE,8,txts);

    // 材质纹理初始化
    // 设置材质层
    glUniform1i( glGetUniformLocation(program,"yTexture"),0);
    glUniform1i( glGetUniformLocation(program,"uTexture"),1);
    glUniform1i( glGetUniformLocation(program,"vTexture"),2);

    XLOGD("初始化shader成功。");

    return true;
}


void XShader::Draw()
{
    if (!program) return;

    // 三维绘制
     glDrawArrays(GL_TRIANGLE_STRIP,0,4);
}

void XShader::GetTexture(unsigned int index,int width,int height, unsigned char * buf)
{
    if (texts[index] == 0)
    {
        // 材质初始化

        // 创建3个纹理
        glGenTextures(3,&texts[index]);

        // 设置纹理属性
        glBindTexture(GL_TEXTURE_2D,texts[index]);
        // 缩小的过滤器 ， 使用线性插值
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        // 设置纹理的格式和大小
        glTexImage2D(GL_TEXTURE_2D,
                     0,           // 细节基础，0 默认
                     GL_LUMINANCE,// 内部格式 ,亮度，灰度图
                     width,height,// 宽高 拉伸到全屏
                     0,           //边框
                     GL_LUMINANCE,// 数据的像素格式，亮度，灰度图，要与上面一致
                     GL_UNSIGNED_BYTE, // 像素的数据类型
                     NULL         //纹理的数据
        );
    }

    // 激活第一层纹理 , 绑定到创建的opengl纹理
    glActiveTexture(GL_TEXTURE0+index);
    glBindTexture(GL_TEXTURE_2D,texts[index]);
    // 替换纹理内容
    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,width,height,GL_LUMINANCE,GL_UNSIGNED_BYTE,buf);



}
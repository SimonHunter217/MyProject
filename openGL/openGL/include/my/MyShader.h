#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class MyShader
{
public:
    // ����ID
    unsigned int ID;

    // ��������ȡ��������ɫ��
	MyShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    // ʹ��/�������
    void use();
};

#endif
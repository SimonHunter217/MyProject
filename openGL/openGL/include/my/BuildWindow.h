#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//����һ������
GLFWwindow* createOpenGLWindow(bool useAntiAliasing = false, int samplesNum = 4);
//���ڹرյ�ʱ���������
void closeWindow();

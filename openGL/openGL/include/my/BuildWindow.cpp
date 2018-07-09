#include <my/BuildWindow.h>

#include <iostream>
#include <fstream>
#include <string>

void changeWindowSizeCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* createOpenGLWindow()
{
	//��ʼ��GLFW
	glfwInit();
	//�������汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//�����Ӱ汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//���ñ��ģʽΪ����ģʽ
	//���ܣ�https://learnopengl-cn.github.io/01%20Getting%20started/01%20OpenGL/
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//��������
	GLFWwindow *window = glfwCreateWindow(800, 600, "build_window", NULL, NULL);
	if (window == NULL)
	{
		//����ʧ��
		std::cout << "build failed" << std::endl;
		return 0;
	}
	//����������ڵ�������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);

	//��һ������Ҫ����ʼ��GLAD�������κ�OpenGL�ĺ���֮ǰ��Ҫ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}

	//������Ⱦ���ڵĴ�С
	//ǰ����������ʾ���½ǵ�����
	//�������������ֱ���ƿ�Ⱥ͸߶�
	//OpenGL����������Ⱦ���ڵĴ�С������ʵ�����꣬OpenGL�����괦�����(-1��1)֮��
	glViewport(0, 0, 800, 600);

	//ע��һ���¼��������ڳߴ�ı����Ҫ����������ͼ��С
	glfwSetFramebufferSizeCallback(window, changeWindowSizeCallBack);

	return window;
}

void closeWindow()
{
	glfwTerminate();
}

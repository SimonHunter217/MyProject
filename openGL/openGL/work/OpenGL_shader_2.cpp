#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

#include <my/BuildWindow.h>
#include <my/MyShader.h>

int main()
{
	GLFWwindow* window = createOpenGLWindow();

	float vertices[] = {
		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//������ɫ������location = 1�Ĳ���
	glEnableVertexAttribArray(1);

	//��ɫ��
	std::string vsPath = "./work/ShaderFile/ShaderLearn/changeColor_2/vertex.vs";
	std::string fsPath = "./work/ShaderFile/ShaderLearn/changeColor_2/fragment.fs";
	MyShader changeColorShader(vsPath.data(), fsPath.data());

	//ʹ����ɫ��
	changeColorShader.use();

	//��ȡuniform
	int locationNum = glGetUniformLocation(changeColorShader.ID, "addX");
	glUniform1f(locationNum, 0.1f);

	//ѭ������
	//���GLFW�Ƿ�Ҫ���˳�
	while (!glfwWindowShouldClose(window))
	{
		//���������Ļ��ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//������壬��ߵĻ��廹��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		//������ɫ����
		glfwSwapBuffers(window);
		//�����û�д����¼����������롢����ƶ���
		glfwPollEvents();
	}

	closeWindow();
	return 0;
}

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

#include <my/BuildWindow.h>
#include <my/MyShader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
	GLFWwindow* window = createOpenGLWindow();

	float quadVertices[] = {
		// λ��          // ��ɫ
		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		0.05f,  0.05f,  0.0f, 1.0f, 1.0f
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glBindVertexArray(0);

	glm::vec2 translations[100];
	int index = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (float)x / 10.0f + offset;
			translation.y = (float)y / 10.0f + offset;
			translations[index++] = translation;
		}
	}

	//��ɫ��
	std::string vsPath = "./work/ShaderFile/Instance/1/vertex.vs";
	std::string fsPath = "./work/ShaderFile/Instance/1/fragment.fs";
	MyShader instanceShader(vsPath.data(), fsPath.data());

	//ѭ������
	//���GLFW�Ƿ�Ҫ���˳�
	while (!glfwWindowShouldClose(window))
	{
		//���������Ļ��ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//������壬��ߵĻ��廹��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT
		glClear(GL_COLOR_BUFFER_BIT);

		instanceShader.use();
		for (unsigned int i = 0; i < 100; i++)
		{
			std::stringstream stream;
			stream << i;
			std::string index = stream.str();   //�˴�Ҳ������ stream>>string_temp  
			glUniform2f(glGetUniformLocation(instanceShader.ID, ("offsets[" + index + "]").c_str()),
				translations[i].x, translations[i].y);
		}
		glBindVertexArray(VAO);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);

		//������ɫ����
		glfwSwapBuffers(window);
		//�����û�д����¼����������롢����ƶ���
		glfwPollEvents();
	}

	closeWindow();
	return 0;
}

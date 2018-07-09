#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

#include <my/BuildWindow.h>
#include <my/MyShader.h>

int _draw_triangle_1_main()
{
	GLFWwindow* window = createOpenGLWindow();

	float vertices[] = {
		0.0, 0.0, 0.0,
		0.5, -0.5, 0.0,
		0.5, 0.5, 0.0,
		-0.5, 0.5, 0.0,
		-0.5, -0.5, 0.0
	};

	//����һ��VAO����
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//��VAO����
	glBindVertexArray(VAO);

	unsigned int VBO;
	//ͨ��һ������ID����һ��VBO����
	glGenBuffers(1, &VBO);
	//��VBO��ָ������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//д������
	//GL_STATIC_DRAW�����ݲ���򼸺�����ı䡣
	//GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
	//GL_STREAM_DRAW������ÿ�λ���ʱ����ı䡣
	//�ᾭ���ı�����ݽ�����ڸ���д����ڴ沿��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int elements[] = {
		0, 1, 2,
		0, 3, 4
	};

	//����EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	//��EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//���Ӷ�������
	//��һ����������Ӧ������ɫ���е�(location = 0)
	//�ڶ���������ָ�����ݵĴ�С����Ϊ�����õ���vec3�����������3
	//������������ָ���������ͣ�����õ���float
	//���ĸ���������ʾ�����Ƿ񱻱�׼�������������GL_TRUE����ô���ݻᱻӳ�䵽0-1֮��
	//�������������������ȡ�����ݵĳ���
	//������������������ʼλ�õ�ƫ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//������������
	glEnableVertexAttribArray(0);

	//��ɫ��
	std::string vsPath = "E:/MyCode/openGL/openGL/work/ShaderFile/DrawTriangle/vertex.vs";
	std::string fsPath = "E:/MyCode/openGL/openGL/work/ShaderFile/DrawTriangle/fragment.fs";
	MyShader orangeShader(vsPath.data(), fsPath.data());

	//ѭ������
	//���GLFW�Ƿ�Ҫ���˳�
	while (!glfwWindowShouldClose(window))
	{
		//���������Ļ��ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//������壬��ߵĻ��廹��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT
		glClear(GL_COLOR_BUFFER_BIT);

		//����
		orangeShader.use();
		glBindVertexArray(VAO);
		//�ڶ����������ӵڼ����ڵ㿪ʼ����
		//���������������Ƽ����ڵ�
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//�ڶ�����������Ҫ��������
		//�������������������ͣ������int
		//���ĸ�������������ƫ����
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//������ɫ����
		glfwSwapBuffers(window);
		//�����û�д����¼����������롢����ƶ���
		glfwPollEvents();
	}

	closeWindow();
	return 0;
}

#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <my/MyShader.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
	//λ��
	glm::vec3 Position;
	//����
	glm::vec3 Normal;
	//����λ��
	glm::vec2 TexCoords;
	//����
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	//���ǳ�tangant�ᣨT����bitangent�ᣨB����Normal�ᣨN������ɵ�����ϵ�������߿ռ䣨TBN����
	//���߿ռ��Ǹ������������
};

struct Texture {
	//����id
	unsigned int id;
	string type;
	//�洢����·�������ж��Ƿ���ع���
	string path;
};

class MyMesh {
public:
	//���㼯��
	vector<Vertex> vertices;
	//��������
	vector<unsigned int> indices;
	//������
	vector<Texture> textures;
	//�����������
	unsigned int VAO;
	//���캯��
	MyMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		setupMesh();
	}
	//���ƺ���
	//�淶������
	/*
		uniform sampler2D texture_diffuse_1;
		uniform sampler2D texture_diffuse_2;
		uniform sampler2D texture_diffuse_3;
		uniform sampler2D texture_specular_1;
		uniform sampler2D texture_specular_2;
	*/
	void Draw(MyShader shader)
	{
		//����
		unsigned int diffuseCount = 1;
		unsigned int specularCount = 1;
		unsigned int normalCount = 1;
		unsigned int heightCount = 1;
		//��������
		for (unsigned int i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);

			string number;
			string name = textures[i].type;
			if (name == "texture_diffuse") {
				number = std::to_string(diffuseCount++);
			}
			else if (name == "texture_specular") {
				number = std::to_string(specularCount++);
			}
			else if (name == "texture_normal") {
				number = std::to_string(normalCount++);
			}
			else if (name == "texture_height") {
				number = std::to_string(heightCount++);
			}

			glUniform1i(glGetUniformLocation(shader.ID, (name + "_" + number).c_str()), i);
		}
		//��ʼ����
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}
private:
	//��Ⱦ����
	unsigned int VBO, EBO;
	//ʹ�ó�ʼ��
	void setupMesh()
	{
		//��ʼ��
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		//��
		glBindVertexArray(VAO);

		//д������
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		//д������
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		//д�붥������
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		//����
		glEnableVertexAttribArray(1);
		//offsetof ������һ������Ϊ size_t �����ͳ���������һ���ṹ��Ա����ڽṹ��ͷ���ֽ�ƫ����
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		//��������
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		//��������
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

		//ȡ����
		glBindVertexArray(0);
	}
};

#endif
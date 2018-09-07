#ifndef TOOL_H
#define TOOL_H

#include <glad/glad.h> // holds all OpenGL type declarations

#define STB_IMAGE_IMPLEMENTATION
#include <img/stb_image.h>

unsigned int loadTexture(const char* path, GLint SWrap = GL_REPEAT, GLint TWrap = GL_REPEAT)
{
	unsigned int textureID;

	glGenTextures(1, &textureID);

	int width, height, colorChannelNum;
	unsigned char*  imageData = stbi_load(path, &width, &height, &colorChannelNum, 0);
	if (imageData)
	{
		GLenum format;
		if (colorChannelNum == 1)
		{
			format = GL_RED;
		}
		else if (colorChannelNum == 3)
		{
			format = GL_RGB;
		}
		else if (colorChannelNum == 4)
		{
			format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, SWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
	}
	stbi_image_free(imageData);
	glBindTexture(GL_TEXTURE0, textureID);
	return textureID;
}

//��ȡһ���յ���������
unsigned int getNullTexture(int width, int height)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return textureID;
}

#endif
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

Engine::Texture::Texture(std::string const& path, std::string const& type) :
	Resource(path), m_Type(type)
{
}

void Engine::Texture::Create()
{
	glGenTextures(1, &m_ID);

	int width;
	int height; 
	int components;
	unsigned char *data = stbi_load(m_Path.c_str(), &width, &height, &components, 0);

	GLenum format;
	if (components == 1)
	{
		format = GL_RED;
	}
	else if (components == 3)
	{
		format = GL_RGB;
	}
	else if (components == 4)
	{
		format = GL_RGBA;
	}

	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
}
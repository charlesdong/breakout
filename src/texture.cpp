#include "texture.h"
#include <lodepng.h>

Texture::Texture()
{
}

GLuint Texture::get() const
{
	return id;
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::create(const char * file)
{
	std::vector<unsigned char> image;
	unsigned width, height;

	glGenTextures(1, &id);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	lodepng::decode(image, width, height, file);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
	unbind();
}

void Texture::clear()
{
	glDeleteTextures(1, &id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
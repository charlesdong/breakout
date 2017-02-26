#pragma once

#include <glew.h>

class Texture
{
public:
	Texture();

	GLuint get() const;
	void bind() const;

	void create(const char * file);
	void clear();

	static void unbind();

private:
	GLuint id;
};
#pragma once

#include <glew.h>

class Texture
{
public:
	Texture(const char * file);

	GLuint get() const;
	void bind() const;

	void clear();

private:

	GLuint id;
};
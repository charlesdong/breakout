#pragma once

#include "shader.h"
#include <glew.h>
#include <glm/glm.hpp>
using glm::vec2;

class Renderer
{
public:
	Renderer();

	void init();
	void clear();

	void setSize(const vec2 & s);

	void render(const vec2 & pos);

private:
	GLuint vao;
	vec2 size;
	Shader * shader;
};
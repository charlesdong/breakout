#pragma once

#include "resource_manager.h"
#include <string>
#include <glew.h>
#include <glm/glm.hpp>
using std::string;
using glm::vec2;

class Renderer
{
public:
	Renderer();

	void init();
	void clear();

	void setSize(const vec2 & s);
	void setTexture(const string & tex);
	void render(const vec2 & pos);

private:
	GLuint vao;
	vec2 size;
	string texture;
	ResourceManager * resources;
};
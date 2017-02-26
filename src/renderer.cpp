#include "renderer.h"
#include "game.h"
#include <glew.h>
#include <glm/gtc/matrix_transform.hpp>
using glm::translate;
using glm::scale;
using glm::ortho;
using glm::vec3;
using glm::mat4;

Renderer::Renderer()
{
}

void Renderer::init()
{
	const GLfloat vertexes[] =
	{
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	resources = &Game::getApp().getResources();
	Shader & shader = resources->getShader("shader");
	shader.use();
	shader.set4x4f("projection", ortho(0.0f, 800.0f, 600.0f, 0.0f));
}

void Renderer::clear()
{
	glDeleteVertexArrays(1, &vao);
}

void Renderer::setSize(const vec2 & s)
{
	size = s;
}

void Renderer::setTexture(const string & tex)
{
	texture = tex;
}

void Renderer::render(const vec2 & pos)
{
	mat4 model;
	Shader & shader = resources->getShader("shader");
	Texture & tex = resources->getTexture(texture);

	model = translate(model, vec3(pos, 0.0f));
	model = scale(model, vec3(size, 1.0f));

	shader.use();
	shader.set4x4f("model", model);
	tex.bind();

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	tex.unbind();
}
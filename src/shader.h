#pragma once

#include <glew.h>
#include <glm/glm.hpp>
#include <string>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using std::string;

class Shader
{
public:
	Shader(const char * vFile, const char * fFile);
	~Shader();

	GLuint get() const;

	void use() const;

	void seti(const char * name, int v0) const;
	void setf(const char * name, float v0) const;
	void set2f(const char * name, float v0, float v1) const;
	void set2f(const char * name, const vec2 & v) const;
	void set3f(const char * name, float v0, float v1, float v2) const;
	void set3f(const char * name, const vec3 & v) const;
	void set4f(const char * name, float v0, float v1, float v2, float v3) const;
	void set4f(const char * name, const vec4 & v) const;
	void set4x4f(const char * name, const mat4 & m) const;

private:
	void loadCode(const char * vFile, const char * fFile, string & vCode, string & fCode) const;
	GLuint createShader(GLuint type, const char * code) const;
	GLuint createProgram(GLuint vShader, GLuint fShader) const;

	GLuint program;
};
#include "shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

using std::ifstream;
using std::ostringstream;
using std::cout;
using glm::value_ptr;

Shader::Shader()
{
}

GLuint Shader::get() const
{
	return program;
}

void Shader::use() const
{
	glUseProgram(program);
}

void Shader::create(const char * vFile, const char * fFile)
{
	string vCode, fCode;
	loadCode(vFile, fFile, vCode, fCode);

	GLuint vShader, fShader;
	vShader = createShader(GL_VERTEX_SHADER, vCode.c_str());
	fShader = createShader(GL_FRAGMENT_SHADER, fCode.c_str());

	program = createProgram(vShader, fShader);
}

void Shader::clear() const
{
	glDeleteProgram(program);
}

void Shader::loadCode(const char * vFile, const char * fFile, string & vCode, string & fCode) const
{
	ifstream fin;
	ostringstream ss;

	// vertex shader
	fin.open(vFile);
	if (!fin.is_open())
		cout << "Unable to open shader file " << vFile << " (maybe not found)\n";

	ss << fin.rdbuf();
	vCode = ss.str();

	fin.close();
	ss.str("");

	// fragment shader
	fin.open(fFile);
	if (!fin.is_open())
		cout << "Unable to open shader file " << fFile << " (maybe not found)\n";

	ss << fin.rdbuf();
	fCode = ss.str();

	fin.close();
}

GLuint Shader::createShader(GLuint type, const char * code) const
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		GLchar * infoLog = new GLchar[length + 1];
		glGetShaderInfoLog(shader, length + 1, nullptr, infoLog);
		cout << "--------------------------------------------------\n"
			<< "Shader compilation failed, type: " << type << ", info log:\n"
			<< infoLog << "\n";
		delete infoLog;
	}

	return shader;
}

GLuint Shader::createProgram(GLuint vShader, GLuint fShader) const
{
	GLuint prog = glCreateProgram();
	glAttachShader(prog, vShader);
	glAttachShader(prog, fShader);
	glLinkProgram(prog);

	GLint status;
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if (!status)
	{
		GLint length;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &length);
		GLchar * infoLog = new GLchar[length + 1];
		glGetProgramInfoLog(prog, length + 1, nullptr, infoLog);
		cout << "-------------------------------------------------\n"
			<< "Program linking failed, info log:\n"
			<< infoLog << "\n";
		delete infoLog;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return prog;
}

#define LOCATION glGetUniformLocation(program, name)
#define VEC_ADDR value_ptr(v)

void Shader::seti(const char * name, int v0) const
{
	glUniform1i(LOCATION, v0);
}

void Shader::setf(const char * name, float v0) const
{
	glUniform1f(LOCATION, v0);
}

void Shader::set2f(const char * name, float v0, float v1) const
{
	glUniform2f(LOCATION, v0, v1);
}

void Shader::set2f(const char * name, const vec2 & v) const
{
	glUniform2fv(LOCATION, 1, VEC_ADDR);
}

void Shader::set3f(const char * name, float v0, float v1, float v2) const
{
	glUniform3f(LOCATION, v0, v1, v2);
}

void Shader::set3f(const char * name, const vec3 & v) const
{
	glUniform3fv(LOCATION, 1, VEC_ADDR);
}

void Shader::set4f(const char * name, float v0, float v1, float v2, float v3) const
{
	glUniform4f(LOCATION, v0, v1, v2, v3);
}

void Shader::set4f(const char * name, const vec4 & v) const
{
	glUniform4fv(LOCATION, 1, VEC_ADDR);
}

void Shader::set4x4f(const char * name, const mat4 & m) const
{
	glUniformMatrix4fv(LOCATION, 1, GL_FALSE, value_ptr(m));
}
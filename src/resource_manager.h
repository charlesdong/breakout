#pragma once

#include "shader.h"
#include <map>
#include <string>
using std::map;
using std::string;

class ResourceManager
{
public:
	ResourceManager();
	ResourceManager(const ResourceManager &) = delete;
	~ResourceManager();

	void loadShader(const char * vFile, const char * fFile, const string & name);

	Shader & getShader(const string & name);

private:
	map<string, Shader> shaders;
};
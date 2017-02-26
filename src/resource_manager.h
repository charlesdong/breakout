#pragma once

#include "shader.h"
#include "texture.h"
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
	void loadTexture(const char * file, const string & name);

	Shader & getShader(const string & name);
	Texture & getTexture(const string & name);
private:
	map<string, Shader> shaders;
	map<string, Texture> textures;
};
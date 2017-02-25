#include "resource_manager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (auto iter : shaders)
		iter.second.clear();
}


void ResourceManager::loadShader(const char * vFile, const char * fFile, const string & name)
{
	Shader shader;
	shader.create(vFile, fFile);
	shaders[name] = shader;
}

Shader & ResourceManager::getShader(const string & name)
{
	return shaders[name];
}
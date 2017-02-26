#include "resource_manager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (auto iter : shaders)
		iter.second.clear();
	for (auto iter : textures)
		iter.second.clear();
}

void ResourceManager::loadShader(const char * vFile, const char * fFile, const string & name)
{
	Shader shader;
	shader.create(vFile, fFile);
	shaders[name] = shader;
}

void ResourceManager::loadTexture(const char * file, const string & name)
{
	Texture texture;
	texture.create(file);
	textures[name] = texture;
}

Shader & ResourceManager::getShader(const string & name)
{
	return shaders[name];
}

Texture & ResourceManager::getTexture(const string & name)
{
	return textures[name];
}
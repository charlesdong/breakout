#pragma once

#define GLFW_INCLUDE_NONE	// prevent GLFW from including gl.h
#include <glfw3.h>
#include "resource_manager.h"
#include "renderer.h"
#include "level.h"

class Game
{
public:
	Game();
	Game(const Game &) = delete;
	~Game();

	Game & operator=(const Game &) = delete;

	void init();
	void run();

	ResourceManager & getResources();
	Renderer & getRenderer();

	static Game & getApp();

private:
	void loadShaders();
	void loadTextures();
	void update();
	void render();
	void renderBackground();

	GLFWwindow * window;
	ResourceManager resources;
	Renderer renderer;
	Level level;

	static Game * game;
};
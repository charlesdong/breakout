#pragma once

#define GLFW_INCLUDE_NONE	// prevent GLFW from including gl.h
#include <glfw3.h>

#include "resource_manager.h"
#include "renderer.h"
#include "level.h"
#include "paddle.h"
#include "ball.h"

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
	int & getLives();

	static Game & getApp();

private:
	void loadShaders();
	void loadTextures();
	void processInput();
	void update();
	void render();
	void renderBackground();
	bool isKeyDown(int key) const;

	float deltaTime;
	GLFWwindow * window;
	ResourceManager resources;
	Renderer renderer;
	Level level;
	Paddle paddle;
	Ball ball;
	int lives;

	static Game * game;
};
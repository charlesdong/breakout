#pragma once

#define GLFW_INCLUDE_NONE
#include <glfw3.h>

class Game
{
public:
	Game();
	Game(const Game &) = delete;
	~Game();

	Game & operator=(const Game &) = delete;

	void init();
	void run();

private:
	void update();
	void render() const;

	GLFWwindow * window;
};
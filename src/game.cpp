#include "game.h"
#include <glew.h>
#include <iostream>		// TODO: logging
#include <cstdlib>		// for exit()

Game::Game() : window(nullptr)
{
}

Game::~Game()
{
	glfwTerminate();
}

void Game::init()
{
	using std::exit;

	if (!glfwInit())
	{
		std::cout << "Failed to init GLFW\n";
		exit(1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(800, 600, "Breakout", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create window using GLFW!\n";
		exit(1);
	}

	glewExperimental = GL_TRUE;
	if (glewInit())
	{
		std::cout << "Failed to init GLEW\n";
		exit(1);
	}

	glViewport(0, 0, 800, 600);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		update();

		render();

		glfwSwapBuffers(window);
	}
}

void Game::update()
{
}

void Game::render() const
{
}
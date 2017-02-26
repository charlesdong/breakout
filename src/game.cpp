#include "game.h"
#include <glew.h>
#include <iostream>		// TODO: logging
#include <cstdlib>		// for exit()

Game * Game::game;

Game::Game() : window(nullptr)
{
}

Game::~Game()
{
	glfwTerminate();
}

ResourceManager & Game::getResources()
{
	return resources;
}

Renderer & Game::getRenderer()
{
	return renderer;
}

void Game::init()
{
	using std::exit;
	game = this;

	// Init GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to init GLFW\n";
		exit(1);
	}

	// Window settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create window
	window = glfwCreateWindow(800, 600, "Breakout", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create window using GLFW!\n";
		exit(1);
	}
	glfwMakeContextCurrent(window);

	// Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit())
	{
		std::cout << "Failed to init GLEW\n";
		exit(1);
	}
	glGetError();	// After GLEW is initialized there's an underlying error, get rid of it

	// Init OpenGL settings
	glViewport(0, 0, 800, 600);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Init shaders and textures
	loadShaders();
	loadTextures();

	// Init game data
	renderer.init();
	level.init();
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

void Game::loadShaders()
{
	resources.loadShader("res/shaders/shader.vert", "res/shaders/shader.frag", "shader");
}

void Game::loadTextures()
{
	resources.loadTexture("res/textures/background.png", "background");
	resources.loadTexture("res/textures/brick_solid.png", "brick_solid");
	resources.loadTexture("res/textures/brick.png", "brick");
}

void Game::update()
{
	level.update();
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	renderBackground();
	level.render();
}

void Game::renderBackground()
{
	renderer.setSize(vec2(800.0f, 600.0f));
	renderer.setTexture("background");
	renderer.setColor(vec3(1.0f, 1.0f, 1.0f));
	renderer.render(vec2(0.0f, 0.0f));
}

Game & Game::getApp()
{
	return *game;
}
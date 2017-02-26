#include "game.h"
#include <glew.h>
#include <iostream>		// TODO: logging
#include <cstdlib>		// for exit()

void onKey(GLFWwindow * window, int key, int scancode, int action, int mods);

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

	// Set callbacks
	glfwSetKeyCallback(window, onKey);

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
	paddle.init();
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
	resources.loadTexture("res/textures/paddle.png", "paddle");
}

void Game::update()
{
	static float preTime = 0.0f;
	static float curTime = 0.0f;

	preTime = curTime;
	curTime = (float)glfwGetTime();
	float dt = curTime - preTime;

	level.update();

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		paddle.move(dt, -1);
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		paddle.move(dt, 1);
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	renderBackground();
	level.render();
	paddle.render();
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

void onKey(GLFWwindow * window, int key, int scancode, int action, int mods)
{
}
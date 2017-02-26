#pragma once

#include "renderer.h"
#include <glm/glm.hpp>
using glm::vec2;

class Paddle
{
public:
	Paddle();

	void init();
	void move(float dt, int direction);
	void render();

private:
	float posX;
	vec2 size;
	Renderer * renderer;
};
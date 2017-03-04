#pragma once

#include "renderer.h"
#include "level.h"
#include "paddle.h"
#include <glm/glm.hpp>
using glm::vec2;

class Ball
{
public:
	Ball();

	void init();
	void launch();
	void update(float dt, Level & level, const Paddle & paddle);
	void render();

	static const float RADIUS;
private:
	vec2 position;
	vec2 velocity;
	bool stuck;
	Renderer * renderer;

	static const vec2 INITIAL_VELOCITY;
};
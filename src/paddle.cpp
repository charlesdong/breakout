#include "paddle.h"
#include "game.h"

Paddle::Paddle()
{
	size = vec2(100.0f, 20.0f);
	posX = (800.0f - size.x) / 2.0f;
}

void Paddle::init()
{
	renderer = &Game::getApp().getRenderer();
}

void Paddle::move(float dt, int direction)
{
	const float velocity = 400.0f;
	float dx = dt * velocity * float(direction);
	posX += dx;
	// Does the paddle touched the right edge?
	if (posX + size.x > 800.0f)
		posX = 800.0f - size.x;
	// Does the paddle touched the left edge?
	if (posX < 0.0f)
		posX = 0.0f;
}

void Paddle::reset()
{
	size = vec2(100.0f, 20.0f);
	posX = (800.0f - size.x) / 2.0f;
}

void Paddle::render()
{
	renderer->setSize(size);
	renderer->setColor(vec3(1.0f, 1.0f, 1.0f));
	renderer->setTexture("paddle");
	renderer->render(vec2(posX, 600.0f - size.y));
}

float Paddle::getX() const
{
	return posX;
}

const vec2 & Paddle::getSize() const
{
	return size;
}
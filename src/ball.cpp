#include "ball.h"
#include "game.h"

const float Ball::RADIUS = 12.5f;
const vec2 Ball::INITIAL_VELOCITY = vec2(100.0f, -350.0f);

Ball::Ball()
{
	position = vec2((800.0f - RADIUS * 2.0f) / 2.0f, 580.0f - RADIUS * 2.0f);
	velocity = INITIAL_VELOCITY;
	stuck = true;
}

void Ball::init()
{
	renderer = &Game::getApp().getRenderer();
}

void Ball::launch()
{
	stuck = false;
}

void Ball::update(float dt, Level & level, const Paddle & paddle)
{
	if (stuck)
		position = vec2(paddle.getX() + (paddle.getSize().x - RADIUS * 2.0f) / 2.0f, 580.0f - RADIUS * 2.0f);
	else
	{
		position += velocity * dt;
		// Touches the left edge?
		if (position.x < 0.0f)
		{
			position.x = 0.0f;
			velocity.x *= -1.0f;
		}
		// Touches the right edge?
		if (position.x + RADIUS * 2.0f > 800.0f)
		{
			position.x = 800.0f - RADIUS * 2.0f;
			velocity.x *= -1.0f;
		}
		// Touches the top edge?
		if (position.y < 0.0f)
		{
			position.y = 0.0f;
			velocity.y *= -1.0f;
		}
		// Check collision with bricks
		level.checkCollision(position);
	}
}

void Ball::render()
{
	renderer->setSize(vec2(RADIUS * 2.0f));
	renderer->setTexture("ball");
	renderer->setColor(vec3(1.0f, 1.0f, 1.0f));
	renderer->render(position);
}
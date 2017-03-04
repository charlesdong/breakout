#include "ball.h"
#include "game.h"
#include "util.h"
#include <cmath>

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

void Ball::update(float dt, Level & level, Paddle & paddle)
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
		// Touches the paddle?
		if (intersect(position, vec2(RADIUS * 2.0f), vec2(paddle.getX(), 600.0f - paddle.getSize().y), paddle.getSize()))
		{
			float centerX = paddle.getX() + paddle.getSize().x / 2.0f;		// X coordinate of the paddle's center
			float distance = (position.x + RADIUS) - centerX;				// distance from the bottom-middle of the ball to the paddle's top-middle
			float ratio = distance / (paddle.getSize().x / 2.0f);			// X offset / half paddle length
			float length = glm::length(velocity);
			const float STRENGTH = 2.0f;

			velocity.x = INITIAL_VELOCITY.x * ratio * STRENGTH;
			velocity.y = -abs(velocity.y);
			velocity = glm::normalize(velocity) * length;

			Game::getApp().playSound("res/audio/paddle.wav");
		}
		// Drop out of the bottom edge?
		if (position.y > 600.0f)
		{
			int & lives = Game::getApp().getLives();
			paddle.reset();
			reset(paddle);
			lives--;
			if (lives <= 0)
			{
				lives = 3;
				level.reset();
			}
		}
		// Check collision with bricks
		Direction dir = level.checkCollision(position);
		if (dir == LEFT || dir == RIGHT)
			velocity.x *= -1.0f;
		else if (dir == UP || dir == DOWN)
			velocity.y *= -1.0f;
	}
}

void Ball::reset(const Paddle & paddle)
{
	position = vec2(paddle.getX() + (paddle.getSize().x - RADIUS * 2.0f) / 2.0f, 580.0f - RADIUS * 2.0f);
	velocity = INITIAL_VELOCITY;
	stuck = true;
}

void Ball::render()
{
	renderer->setSize(vec2(RADIUS * 2.0f));
	renderer->setTexture("ball");
	renderer->setColor(vec3(1.0f, 1.0f, 1.0f));
	renderer->render(position);
}
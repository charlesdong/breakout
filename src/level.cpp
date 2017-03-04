#include "level.h"
#include "ball.h"
#include "game.h"
#include <fstream>
#include <cmath>
using std::ifstream;
using std::floor;
using std::ceil;
using glm::dot;

Level::Level() : bricks(nullptr)
{
}

Level::~Level()
{
	delete[] bricks;
}

void Level::init()
{
	renderer = &Game::getApp().getRenderer();

	width = 15;
	height = 8;
	brickSize.x = 800.0f / width;
	brickSize.y = 300.0f / height;
	left = 0;

	ifstream fin("res/levels/1.txt");
	bricks = new brick_t[width * height];
	int temp;
	for (int i = 0; i < width * height; i++)
	{
		fin >> temp;
		bricks[i] = brick_t(temp);
		if (temp != 0 && temp != 1)
			left++;
	}

	fin.close();
}

void Level::update()
{
}

void Level::reset()
{
	delete[] bricks;

	width = 15;
	height = 8;
	brickSize.x = 800.0f / width;
	brickSize.y = 300.0f / height;
	left = 0;

	ifstream fin("res/levels/1.txt");
	bricks = new brick_t[width * height];
	int temp;
	for (int i = 0; i < width * height; i++)
	{
		fin >> temp;
		bricks[i] = brick_t(temp);
		if (temp != 0 && temp != 1)
			left++;
	}

	fin.close();
}

Direction Level::checkCollision(const vec2 & pos)
{
	// The brick coordinates (of the upper-left corner) of the upper-left and the lower-right brick.
	int ux, uy, dx, dy;
	vec2 center(pos.x + Ball::RADIUS, pos.y + Ball::RADIUS);
	Direction result = NULLDIR;

	// Remember to subtract 1 from dx and dy, 
	// or they'll represent the LOWER-RIGHT corner of the lower-right brick).
	ux = (int)floor(pos.x / brickSize.x);
	uy = (int)floor(pos.y / brickSize.y);
	dx = (int)ceil((pos.x + Ball::RADIUS * 2.0f) / brickSize.x) - 1;
	dy = (int)ceil((pos.y + Ball::RADIUS * 2.0f) / brickSize.y) - 1;

	// Check every brick in the range and destroy them (if the condition is satisfied).
	for (int x = ux; x <= dx; x++)
		for (int y = uy; y <= dy; y++)
			if (x >= 0 && x < width && y >= 0 && y < height && getBrick(x, y) != 0)
			{
				result = getDirection(center - vec2(brickSize.x * (x + 0.5f), brickSize.y * (y + 0.5f)));
				// Delete the brick.
				if (getBrick(x, y) != 1)
				{
					getBrick(x, y) = 0;
					left--;
				}
			}

	return result;
}

void Level::render() const
{
	int w, h;
	renderer->setSize(brickSize);
	for (h = 0; h < height; h++)
		for (w = 0; w < width; w++)
		{
			if (getBrick(w, h) == 0)
				continue;
			renderer->setTexture(getBrick(w, h) != 1 ? "brick" : "brick_solid");
			renderer->setColor(getColor(getBrick(w, h)));
			renderer->render(vec2(brickSize.x * w, brickSize.y * h));
		}
}

const vec3 & Level::getColor(brick_t id) const
{
	static const vec3 colors[6] =
	{
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.8f, 0.8f, 0.7f),
		vec3(0.2f, 0.6f, 1.0f),
		vec3(0.0f, 0.7f, 0.0f),
		vec3(0.8f, 0.8f, 0.4f),
		vec3(1.0f, 0.5f, 0.0f)
	};
	return colors[id];
}

brick_t & Level::getBrick(int w, int h) const
{
	return bricks[h * width + w];
}

Direction Level::getDirection(const vec2 & v)
{
	// Vectors pointing to the 4 directions
	static vec2 directions[5] =
	{
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.0f, 1.0f),
		vec2(-1.0f, 0.0f),
		vec2(0.0f, -1.0f)
	};
	Direction result;
	float max = 0.0f;
	float product;

	// Go through all directions and found the closest one
	for (int i = 1; i <= 4; i++)
	{
		product = dot(v, directions[i]);
		if (product > max)
		{
			max = product;
			result = (Direction)i;
		}
	}
	return result;
}
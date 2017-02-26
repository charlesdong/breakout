#include "level.h"
#include "game.h"
#include <fstream>
using std::ifstream;

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

	ifstream fin("res/levels/1.txt");
	bricks = new brick_t[width * height];
	int temp;
	for (int i = 0; i < width * height; i++)
	{
		fin >> temp;
		bricks[i] = brick_t(temp);
	}

	fin.close();
}

void Level::update()
{
}

void Level::render() const
{
	int w, h;
	for (h = 0; h < height; h++)
		for (w = 0; w < width; w++)
		{
			if (getBrick(w, h) == 0)
				continue;
			renderer->setSize(brickSize);
			renderer->setTexture(getBrick(w, h) != 1 ? "brick" : "brick_solid");
			renderer->setColor(getColor(getBrick(w, h)));
			renderer->render(vec2(brickSize.x * w, brickSize.y * h));
		}
}

const vec3 & Level::getColor(brick_t id) const
{
	static const vec3 colors[6] =
	{
		vec3(0.8f, 0.8f, 0.7f),
		vec3(1.0f, 1.0f, 1.0f),
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
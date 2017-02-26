#pragma once

#include "renderer.h"
#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;

// The brick ID type
typedef char brick_t;

class Level
{
public:
	Level();
	~Level();

	void init();

	void update();
	void render() const;

private:
	const vec3 & getColor(brick_t id) const;
	brick_t & getBrick(int w, int h) const;

	int width, height;
	vec2 brickSize;
	brick_t * bricks;
	Renderer * renderer;
};
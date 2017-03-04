#include "util.h"

bool intersectX(const vec2 & p1, const vec2 & s1, const vec2 & p2, const vec2 & s2)
{
	return p1.x + s1.x >= p2.x && p2.x + s2.x >= p1.x;
}

bool intersectY(const vec2 & p1, const vec2 & s1, const vec2 & p2, const vec2 & s2)
{
	return p1.y + s1.y >= p2.y && p2.y + s2.y >= p1.y;
}

bool intersect(const vec2 & p1, const vec2 & s1, const vec2 & p2, const vec2 & s2)
{
	return intersectX(p1, s1, p2, s2) && intersectY(p1, s1, p2, s2);
}
#pragma once

#include <glm/glm.hpp>
using glm::vec2;

bool intersectX(const vec2 & p1, const vec2 & s1, const vec2 & p2, const vec2 & s2);
bool intersectY(const vec2 & p1, const vec2 & s1, const vec2 & p2, const vec2 & s2);
bool intersect(const vec2 & p1, const vec2 & s1, const vec2 & p2, const vec2 & s2);
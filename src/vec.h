#pragma once

#include <cmath>
#include <limits>
using std::numeric_limits;
using std::sqrt;

#define REQUIRE_FLOAT() static_assert(numeric_limits<T>::is_iec559, "floating-point vectors required")

template <typename T>
class vec2_t
{
public:
	T x;
	T y;

	template <typename U>
	operator vec2_t<U>() const
	{
		return vec2_t<U>(U(x), U(y));
	}

	T length() const
	{
		REQUIRE_FLOAT();
		return sqrt(x * x + y * y);
	}

	vec2_t normalize() const
	{
		REQUIRE_FLOAT();
		T len = length();
		return vec2_t(x / len, y / len);
	}

	vec2_t operator+(const vec2_t & v) const
	{
		return vec2_t(x + v.x, y + v.y);
	}

	vec2_t operator-(const vec2_t & v) const
	{
		return vec2_t(x - v.x, y - v.y);
	}

	vec2_t operator*(T v) const
	{
		return vec2_t(x * v, y * v);
	}

	vec2_t operator/(T v) const
	{
		return vec2_t(x / v, y / v);
	}
};

template <typename T>
class vec3_t
{
public:
	T x;
	T y;
	T z;
};

template <typename T>
class vec4_t
{
public:
	T x;
	T y;
	T z;
	T w;
};

typedef vec2_t<int> Vec2i;
typedef vec2_t<float> Vec2;
typedef vec3_t<float> Vec3;
typedef vec4_t<float> Vec4;
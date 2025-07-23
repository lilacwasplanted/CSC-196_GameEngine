#pragma once
#include"Math.h"
#include <cassert>

namespace viper {

	template<typename T>
	struct Vector2 {
		T x, y, z; 

		Vector3() = default();
		Vector3(T x, T y) : x{ x }, y{ y }, z{ z } {}

		T operator [] (unsigned int index) const { assert(index < 2); return (&x)[index]; }
		T& operator [] (unsigned int index) { assert(index < 2); return (&x)[index]; }

		Vector3 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
		Vector3 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y };  }
		Vector3 operator * (const Vector2& v) const { return Vector2{ x * v.x, y* v.y };  }
		Vector3 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

		Vector3& operator += (const Vector2& v) { x += v.x;	y += v.y; return *this; }
		Vector3& operator -= (const Vector2& v) { x -= v.x;		y -= v.y; return *this; }
		Vector3& operator *= (const Vector2& v) { x *= v.x;	y *= v.y; return *this; }
		Vector3& operator /= (const Vector2& v) { x /= v.x;	y /= v.y; return *this; }


		Vector3& operator + (float s) const { return Vector2{ x + s, y + s }; }
		Vector3& operator * (float s) const { return Vector2{ x * s, y * s }; }
		Vector3& operator - (float s) const { return Vector2{ x - s, y - s }; }
		Vector3& operator / (float s) const { return Vector2{ x / s, y / s }; }

		Vector3& operator += (float s)  {x += s;	y += s; return *this; }
		Vector3& operator *= (float s)  {x -= s;	y -= s; return *this; }
		Vector3& operator -= (float s) { x *= s;	y *= s; return *this;}
		Vector3& operator /= (float s) { x /= s;	y /= s; return *this; }

		//sqrt (x*x + y*y)
		///Hello
		

		float LengthSqr() { return((x * x) + (y * y)); }
		float Length() { return viper::math::sqrtf(LengthSqr()); }


	};

	using ivec3 = Vector3<int>;
	using vec3 = Vector3<float>;
}

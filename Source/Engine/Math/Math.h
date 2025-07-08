#pragma once

#include<cmath>
#include<algorithm>
#include<SDL3/SDL.h>

namespace viper{
	namespace math{
		constexpr float pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089f;
		constexpr float twopi = 2 * pi;
		constexpr float halfpi = pi / 2;




		using std::min;
		using std::max;
		using std::clamp;
		using std::sqrt;
		using std::sqrtf;
		using std::sin;
		using std::sinf;
		using std::cos;
		using std::cosf;
	}
}
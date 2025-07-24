#pragma once
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"

#include <vector>

using namespace std;
namespace viper {
	class Model {
		public:

			Model() = default;
			Model(const vector<vec2> verts, const vec3& color) :
				_verts{ verts },
				_color{ color }
			{	}

			void Draw(class Renderer& renderer, const vec2& position, float rotation, float scale);
		
	private:
			vector<vec2> _verts;
			vec3 _color{ 255,255,255 };

	};
}
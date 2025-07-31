#pragma once
#include "Math/Transform.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"

namespace viper
{
	class Actor {
	public:
				Actor() = default;
				Actor(Transform& transform, Model* model) :
					_transform{ transform },
					_model{ model }
				{	}
				;

				virtual void Update(float dt);
				virtual void Draw(Renderer& renderer);

				Transform& GetTransform() { return _transform; }
	protected:
		Transform _transform;
		Model* _model;
	}; 
}
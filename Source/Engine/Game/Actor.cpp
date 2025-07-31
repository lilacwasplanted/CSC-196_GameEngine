#include "Actor.h"
#include "../Renderer/Model.h"

namespace viper {
	void viper::Actor::Update(float dt)
	{
		//
	}

	void viper::Actor::Draw(Renderer& renderer)
	{
		_model->Draw(renderer, _transform);
	}
};
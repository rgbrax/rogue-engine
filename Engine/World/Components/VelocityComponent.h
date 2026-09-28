#pragma once
#include "World/Component.h"
#include "Core/Vector2.h"

namespace rogue
{
	//Velocity defined as speed in position? or something else? TBD

	class VelocityComponent : public Component
	{
	public:
		Vector2 velocity = Vector2(0.0f, 0.0f);

		ComponentType GetType() override
		{
			return ComponentType::Velocity;
		}
	};
}
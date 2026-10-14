#pragma once
#include "World/Component.h"
#include "Core/Vector2.h"

namespace rogue
{
	struct VelocityComponent : public Component
	{
		static constexpr ComponentType Type = ComponentType::Velocity;

		VelocityComponent( )
			: Component( Type )
		{ }

		Vector2 velocity = Vector2(0.0f, 0.0f);
	};
}
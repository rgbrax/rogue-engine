#pragma once
#include "World/Component.h"
#include "Core/Vector2.h"

namespace rogue
{
	struct TransformComponent : public Component
	{
		static constexpr ComponentType Type = ComponentType::Transform;

		TransformComponent( )
			: Component( Type )
		{ }

		Vector2 pos = Vector2(0.0f, 0.0f);
	};
}
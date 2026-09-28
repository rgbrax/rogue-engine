#pragma once
#include "World/Component.h"
#include "Core/Vector2.h"

namespace rogue
{
	class TransformComponent : public Component
	{
	public:
		Vector2 pos = Vector2(0.0f, 0.0f);

		ComponentType GetType() override
		{
			return ComponentType::Transform;
		}
	};
}
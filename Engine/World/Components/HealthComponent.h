#pragma once
#include "World/Component.h"

namespace rogue
{
	class HealthComponent : public Component
	{
	public:
		uint32_t health = 0;
		uint32_t healthMax = 0;

		ComponentType GetType() override
		{
			return ComponentType::Health;
		}
	};
}
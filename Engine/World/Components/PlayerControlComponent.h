#pragma once
#include "World/Component.h"

namespace rogue
{
	class PlayerControlComponent : public Component
	{
	public:
		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;

		ComponentType GetType() override
		{
			return ComponentType::PlayerControl;
		}
	};
}
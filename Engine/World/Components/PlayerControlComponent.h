#pragma once
#include "World/Component.h"

namespace rogue
{
	struct PlayerControlComponent : public Component
	{
		static constexpr ComponentType Type = ComponentType::PlayerControl;

		PlayerControlComponent( )
			: Component( Type )
		{ }

		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;
	};
}
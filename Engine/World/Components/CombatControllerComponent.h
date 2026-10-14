#pragma once
#include "Core/Ids.h"
#include "World/Component.h"

namespace rogue
{
	//handles basic combat data for now

	struct CombatControllerComponent : public Component
	{
		static constexpr ComponentType Type = ComponentType::CombatController;

		CombatControllerComponent( )
			: Component( Type )
		{ }

		InstanceId target = InstanceId(0); //who the Actor is currently attacking; default 0 means nobody
	};
}
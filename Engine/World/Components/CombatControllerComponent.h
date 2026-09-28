#pragma once
#include "Core/Ids.h"
#include "World/Component.h"

namespace rogue
{
	//handles basic combat data for now

	class CombatControllerComponent : public Component
	{
	public:
		InstanceId target = InstanceId(0); //who the Actor is currently attacking; default 0 means nobody

		ComponentType GetType() override
		{
			return ComponentType::CombatController;
		}
	};
}
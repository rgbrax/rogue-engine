#pragma once
#include <cstdint>

namespace rogue
{
	//do we even need this anymore? TBD
	enum class ComponentType : uint8_t
	{
		None,
		CharacterAi,
		CombatController,
		Faction,
		Health,
		PlayerControl,
		Transform,
		Velocity,
		Count
	};

	class Component
	{
	public:
		virtual ComponentType GetType() = 0;
	};
}
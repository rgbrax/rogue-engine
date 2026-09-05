#pragma once

#include <cstdint>

namespace rogue
{
	//authorable def types / kinds the engine can construct 
	enum class DefType : uint16_t
	{
		Invalid = 0,
		Weapon,
		Armor,
		Consumable,
		MiscItem,
		Actor,
		Placeable,
		Cell,
		World,
		Stat,
		Ability,
		Faction,
		Class,
		Ruleset,
		Quest,
		Count
	};
}

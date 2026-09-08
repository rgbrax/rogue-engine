#pragma once

#include <cstdint>

namespace rogue
{
	//authored def types; not full parent-child hierarchy; i.e. you wouldn't create an ItemDef, you'd make a WeaponDef
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

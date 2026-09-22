#pragma once
#include <cstdint>

namespace rogue
{
	//authorable def types
	enum class DefType : uint8_t
	{
		Invalid,
		Actor,
		Armor,
		Consumable,
		Weapon,
		Count
	};
}

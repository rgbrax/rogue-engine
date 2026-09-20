#pragma once
#include <cstdint>

namespace rogue
{
	//authorable def types
	enum class DefType : uint8_t
	{
		Invalid = 0,
		Weapon,
		Armor,
		Consumable,
		Actor,		
		Count
	};
}

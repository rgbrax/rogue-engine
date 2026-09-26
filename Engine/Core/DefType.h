#pragma once
#include <cstdint>
#include <string>

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

	const std::string DefTypeValues[6] = { "Invalid", "Actor", "Armor", "Consumable", "Weapon", "Count" };
}

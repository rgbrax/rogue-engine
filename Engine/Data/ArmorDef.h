#pragma once
#include "Data/ItemDef.h"

namespace rogue
{
	class ArmorDef : public ItemDef
	{
	public:
		uint32_t armorRating = 0;

		ArmorDef( )
		{
			type = DefType::Armor;
		}
	};
}

#pragma once
#include "Data/ItemDef.h"

namespace rogue
{
	class WeaponDef : public ItemDef
	{
	public:
		uint32_t damage = 0;
		float range = 1.0f;

		WeaponDef()
		{
			type = DefType::Weapon;
		}
	};
}

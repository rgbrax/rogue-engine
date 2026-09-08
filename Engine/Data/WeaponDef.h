#pragma once

#include "Data/ItemDef.h"

namespace rogue
{
	//#tbd: move to separate file once more users of this struct exist
	//#tbd: add more damage types; implement w/ ruleset(?) i.e optional or build in/out
	enum class DamageType
	{
		Physical,
		Fire,
		Frost,
		Shock
	};

	inline constexpr EnumEntry DamageTypeNames[] =
	{
		{"Physical", DamageType::Physical},
		{"Fire", DamageType::Fire},
		{"Frost", DamageType::Frost},
		{"Shock", DamageType::Shock},
	};

	class WeaponDef : public ItemDef
	{
	public:
		float damage = 0.0f;
		float reach = 1.0f;
		DamageType damageType = DamageType::Physical;
		static const Schema& StaticSchema();
		const Schema& GetSchema() const override
		{
			return StaticSchema();
		}
	};
}

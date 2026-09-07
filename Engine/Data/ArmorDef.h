#pragma once
#include "Data/ItemDef.h"

namespace rogue
{
	enum class ArmorType
	{
		Clothes,
		LightArmor,
		HeavyArmor,
		Robes
	};

	class ArmorDef : public ItemDef
	{
	public:
		float armorRating = 0.0f;
		ArmorType armorType = ArmorType::Clothes;

		static const Schema& StaticSchema();
		const Schema& GetSchema() const override
		{
			return StaticSchema();
		}
	};
}

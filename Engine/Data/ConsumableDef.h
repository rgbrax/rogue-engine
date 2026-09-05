#pragma once
#include "Data/ItemDef.h"

namespace rogue
{
	enum class ConsumableType
	{
		Food,
		Potion,
		Poison
	};

	class ConsumableDef : public ItemDef
	{
	public:
		uint32_t effectAmount = 0; //unsigned, we use positive numbers only; food+potion is amt to heal; poison is amount to damage;
		float effectDuration = 0.0f; //duration in seconds; effect is divided by duratoin; 10 amount + 10 duration = 1 health per second;
		ConsumableType type = ConsumableType::Food;

		static const Schema& StaticSchema();
		const Schema& GetSchema() const override
		{
			return StaticSchema();
		}
	};
}

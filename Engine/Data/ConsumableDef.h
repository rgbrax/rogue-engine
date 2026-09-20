#pragma once
#include "Data/ItemDef.h"

namespace rogue
{
	class ConsumableDef : public ItemDef
	{
	public:
		uint32_t effectAmount = 0;
		float effectDuration = 0.0f;
	};
}

#pragma once

#include "Data/Def.h"

namespace rogue
{
	class ItemDef : public Def
	{
	public:
		std::string displayName = "";
		float weight = 0.0f;
		int32_t value = 0;

		static const Schema& StaticSchema();
	};
}

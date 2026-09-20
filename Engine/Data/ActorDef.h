#pragma once
#include "Data/ItemDef.h"

namespace rogue
{
	class ActorDef : public Def
	{
	public:
		std::string displayName = "";
		uint32_t health = 0;
		uint32_t level = 1;
		bool isUnique = false;
	};
}

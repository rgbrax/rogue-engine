#pragma once
#include "Data/Def.h"

namespace rogue
{
	class ItemDef : public Def
	{
	public:
		std::string displayName = "";
		float weight = 0.0f;
		uint32_t value = 0;
		bool isUnique = false;

		ItemDef( )
		{
			//non-authorable type, is a base class
			type = DefType::Invalid;
		}
	};
}

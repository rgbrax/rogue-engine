#pragma once
#include "Core/DefType.h"
#include "Core/Ids.h"

#include <string>

namespace rogue
{
	class Def
	{
	public:
		virtual ~Def() = default;
		DefId id;
		std::string editorId;
		DefType type = DefType::Invalid;
		ModuleId sourceModule;		
	};
}

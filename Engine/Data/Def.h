#pragma once
#include "Core/DefType.h"
#include "Core/Ids.h"
#include "Core/Schema.h"

#include <string>

namespace rogue
{
	//base definition
	class Def
	{
	public:
		virtual ~Def() = default;
		DefId id;
		std::string editorId; //in-editor name; i.e. "weapon_iron_sword"
		DefType type = DefType::Invalid;
		DefId archetype; //0 = none, inherit fields
		ModuleId sourceModule; //module file that created this definition
		virtual const Schema& GetSchema() const = 0;
	};
}

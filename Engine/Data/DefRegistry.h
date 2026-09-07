#pragma once
#include "Core/DefType.h"
#include "Data/Def.h"

#include <memory>
#include <span>
#include <string_view>

namespace rogue
{
	struct DefTypeInfo
	{
		DefType type;
		std::string_view name;
		std::unique_ptr<Def> (*Create)();
	};

	class DefRegistry
	{
	public:
		static std::unique_ptr<Def> Create(std::string_view name);
		static std::span<const DefTypeInfo> All();
	};
}

#pragma once
#include "Core/Ids.h"
#include "Data/Def.h"

#include <memory>
#include <string_view>
#include <vector>

namespace rogue
{
	//owns loaded definitions
	class DefTable
	{
	public:
		//takes ownership of an existing def, sets an id if none added, returns false if editorId is already taken or def is null
		bool Add(std::unique_ptr<Def> def);
		Def* Get(DefId id) const;
		Def* Find(std::string_view editorId) const;
		const std::vector<std::unique_ptr<Def>>& All() const;
		size_t Count() const;
		void Clear();

	private:
		std::vector<std::unique_ptr<Def>> m_defs; //#tbd: move away from std::vector / improve containers later
	};
}

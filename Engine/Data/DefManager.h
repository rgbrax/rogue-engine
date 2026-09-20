#pragma once
#include "Def.h"

#include <memory>
#include <vector>

namespace rogue
{
	class DefManager
	{
	public:
		const std::vector<std::shared_ptr<Def>>& GetDefs();
		Def* GetDefById(DefId id);
		Def* GetDefByEditorId(std::string_view editorId);
		bool SaveFiles();
		bool LoadFiles();
		bool AddDef(Def* def); //manually add def
	private:
		std::vector<std::shared_ptr<Def>> m_defs; //shared_ptr not efficient, but hard to mess up; improve memory later
	};
}

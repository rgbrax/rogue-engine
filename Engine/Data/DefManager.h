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
		bool SaveFiles(std::string_view filePath);
		bool LoadFiles(std::string_view filePath);
		bool AddDef(Def* def);
		bool RemoveDefById(DefId id);
		bool RemoveDefByEditorId(std::string_view editorId);
		bool RemoveDefByPtr(std::shared_ptr<Def> obj);
		bool ClearDefs();

	private:
		std::vector<std::shared_ptr<Def>> m_defs; //shared_ptr not efficient, but hard to mess up; improve memory later
	};
}

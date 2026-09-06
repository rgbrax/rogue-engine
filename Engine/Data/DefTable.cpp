#include "Data/DefTable.h"

namespace rogue
{
	bool DefTable::Add(std::unique_ptr<Def> def)
	{
		if (def == nullptr)
			return false;

		if (!def->editorId.empty() && Find(def->editorId) != nullptr)
			return false;

		if (!def->id.IsValid())
			def->id.value = m_defs.size() + 1; //#tbd: after IDs are created with module-tied name, we will set this elsewhere

		m_defs.push_back(std::move(def));
		return true;
	}

	Def* DefTable::Get(DefId id) const
	{
		for (const std::unique_ptr<Def>& def : m_defs)
		{
			if (def->id == id)
				return def.get();
		}

		return nullptr;
	}

	Def* DefTable::Find(std::string_view editorId) const
	{
		for (const std::unique_ptr<Def>& def : m_defs)
		{
			if (def->editorId == editorId)
				return def.get();
		}

		return nullptr;
	}

	const std::vector<std::unique_ptr<Def>>& DefTable::All() const
	{
		return m_defs;
	}

	size_t DefTable::Count() const
	{
		return m_defs.size();
	}

	void DefTable::Clear()
	{
		//destroys every Def, which is why callers hold a DefId and not a Def*
		m_defs.clear();
	}
}

#include "DefManager.h"

#include "ActorDef.h"
#include "ArmorDef.h"
#include "ConsumableDef.h"
#include "WeaponDef.h"

#include "../ThirdParty/json.hpp"
#include "../ThirdParty/rapidcsv.h"

namespace rogue
{
	const std::vector<std::shared_ptr<Def>>& DefManager::GetDefs()
	{
		return m_defs;
	}

	Def* DefManager::GetDefById(DefId id)
	{
		if (!id.IsValid() || !m_defs.size() || id.value > m_defs.size() + 1)
			return nullptr;

		for (int i = 0; i != m_defs.size(); i++)
		{
			if (m_defs[i]->id.value == id.value)
				return m_defs[i].get();
		}

		return nullptr;
	}

	Def* DefManager::GetDefByEditorId(std::string_view editorId)
	{
		if (editorId.empty() || !m_defs.size())
			return nullptr;

		for (int i = 0; i != m_defs.size(); i++)
		{
			if (m_defs[i]->editorId == editorId)
				return m_defs[i].get();
		}

		return nullptr;
	}

	bool DefManager::SaveFiles()
	{
		if (!m_defs.size())
			return false;

		return false;
	}

	bool DefManager::LoadFiles()
	{
		//load defs from csv using rapidcsv
		//this is static fields only, like our current defs; will be moved to dynamic fields and JSON instead

		rapidcsv::Document fileWeapons("weapons.csv");

		for ( int i = 0; i != fileWeapons.GetRowCount( ); i++ )
		{
			std::string editorId = fileWeapons.GetCell<std::string>("editorId", i);
			std::string displayName = fileWeapons.GetCell<std::string>("displayName", i);
			int value = fileWeapons.GetCell<int>("value", i);
			float weight = fileWeapons.GetCell<float>("weight", i);
			bool isUnique = "TRUE" == fileWeapons.GetCell<std::string>("isUnique", i);
			int damage = fileWeapons.GetCell<int>("damage", i);
			float range = fileWeapons.GetCell<float>("range", i);

			WeaponDef* weapon = new WeaponDef();
			weapon->id.value = m_defs.size() + 1;
			weapon->editorId = editorId;
			weapon->isUnique = isUnique;
			weapon->range = range;
			weapon->value = value;
			weapon->weight = weight;
			weapon->damage = damage;
			weapon->displayName = displayName;
			this->AddDef(weapon);
		}

		return true;
	}

	bool DefManager::AddDef(Def* def)
	{
		if (!def)
			return false;

		m_defs.push_back(std::unique_ptr<Def>(def));
		return true;
	}
}

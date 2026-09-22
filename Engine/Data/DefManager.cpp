#include "DefManager.h"

#include "ActorDef.h"
#include "ArmorDef.h"
#include "ConsumableDef.h"
#include "WeaponDef.h"

#include "../ThirdParty/json.hpp"
#include "../ThirdParty/rapidcsv.h"

using namespace nlohmann;

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
		if (m_defs.empty())
			return true;

		json j;
		j["moduleName"] = "core";

		//create json array for def list
		json jArray = json::array();

		for (const std::shared_ptr<Def>& def : m_defs)
		{
			json jDef;
			jDef["editorId"] = def->editorId;
			jDef["type"] = (int)def->type;

			switch (def->type)
			{
			case DefType::Actor:
			{
				ActorDef* actor = static_pointer_cast<ActorDef>(def).get();
				jDef["displayName"] = actor->displayName;
				jDef["health"] = actor->health;
				jDef["level"] = actor->level;
				jDef["isUnique"] = actor->isUnique;
			}
			break;
			case DefType::Armor:
			{
				ArmorDef* armor = std::static_pointer_cast<ArmorDef>(def).get();
				jDef["displayName"] = armor->displayName;
				jDef["value"] = armor->value;
				jDef["weight"] = armor->weight;
				jDef["isUnique"] = armor->isUnique;
				jDef["armorRating"] = armor->armorRating;
			}
			break;
			case DefType::Weapon:
			{
				WeaponDef* weapon = std::static_pointer_cast<WeaponDef>(def).get();
				jDef["displayName"] = weapon->displayName;
				jDef["value"] = weapon->value;
				jDef["weight"] = weapon->weight;
				jDef["isUnique"] = weapon->isUnique;
				jDef["damage"] = weapon->damage;
				jDef["range"] = weapon->range;
			}
			break;
			case DefType::Consumable:
			{
				ConsumableDef* consumable = std::static_pointer_cast<ConsumableDef>(def).get();
				jDef["displayName"] = consumable->displayName;
				jDef["value"] = consumable->value;
				jDef["weight"] = consumable->weight;
				jDef["isUnique"] = consumable->isUnique;
				jDef["effectAmount"] = consumable->effectAmount;
				jDef["effectDuration"] = consumable->effectDuration;
			}
			break;
			case DefType::Invalid:
			case DefType::Count:
			default:
				continue;
			}

			jArray.push_back(jDef);
		}

		j["definitions"] = jArray;

		std::ofstream file(m_defsFilePath);
		if ( !file.is_open( ) )
		{
			return false;
		}

		file << std::setw(4) << j; //4-ct spacing (tabs) formatting
		file.close();
		return true;
	}

	bool DefManager::LoadFiles()
	{
		if (!std::filesystem::exists(m_defsFilePath))
			return false;

		json j;

		std::ifstream file(m_defsFilePath);
		if (!file.is_open())
			return false;

		std::stringstream ss;
		ss << file.rdbuf();
		j = ss.str();

		std::string importModuleName = j["moduleName"];
		printf("Loading defs from:\n-> File: %s\n-> Module: %s\n", m_defsFilePath.c_str(), importModuleName.c_str());

		if ( !j["definitions"].is_array( ) )
		{
			printf("failed to get defs array");
			return false;
		}

		for ( const json& jDef : j["definitions"].array( ) )
		{
			std::string editorId = jDef["editorId"];
			DefType type = static_cast<DefType>(jDef["type"].get<int>());
			if ( type == DefType::Actor )
			{
				std::string displayName = jDef["displayName"];
				bool isUnique = jDef["isUnique"].get<bool>();
				uint32_t health = jDef["health"].get<uint32_t>();
				uint32_t level = jDef["level"].get<uint32_t>();
			}
			else if ( type == DefType::Armor )
			{
				std::string displayName = jDef["displayName"];
				bool isUnique = jDef["isUnique"].get<bool>();
				float weight = jDef["weight"].get<float>();
				uint32_t value = jDef["value"].get<uint32_t>();
				uint32_t armorRating = jDef["armorRating"].get<uint32_t>();
			}
			else if ( type == DefType::Consumable )
			{
				std::string displayName = jDef["displayName"];
				bool isUnique = jDef["isUnique"].get<bool>();
				float weight = jDef["weight"].get<float>();
				uint32_t value = jDef["value"].get<uint32_t>();
				uint32_t effectAmount = jDef["effectAmount"].get<uint32_t>();
				float effectDuration = jDef["effectDuration"].get<float>();
			}
			else if ( type == DefType::Weapon )
			{
				std::string displayName = jDef["displayName"];
				bool isUnique = jDef["isUnique"].get<bool>();
				float weight = jDef["weight"].get<float>();
				uint32_t value = jDef["value"].get<uint32_t>();
				uint32_t damage = jDef["damage"].get<uint32_t>();
				float reach = jDef["reach"].get<float>();
			}
			else
			{
				printf("failed to get valid type");
				continue;
			}
		}

		//printf("Loaded Data:\n%s\n", j.dump(4).c_str());
	}

	bool DefManager::AddDef(Def* def)
	{
		if (!def)
			return false;

		def->editorId = m_defs.size() + 1;
		m_defs.push_back(std::unique_ptr<Def>(def));
		return true;
	}
}

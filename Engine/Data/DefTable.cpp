#include "DefTable.h"
#include "ActorDef.h"
#include "ArmorDef.h"
#include "ConsumableDef.h"
#include "WeaponDef.h"

#include "ThirdParty/json.hpp"
#include "ThirdParty/rapidcsv.h"

using namespace nlohmann;

namespace rogue
{
	const std::vector<std::shared_ptr<Def>>& DefTable::GetDefs()
	{
		return m_defs;
	}

	Def* DefTable::GetDefById(DefId id)
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

	Def* DefTable::GetDefByEditorId(std::string_view editorId)
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

	bool DefTable::SaveFiles(std::string_view filePath)
	{
		if (m_defs.empty())
			return true;

		json j;
		j["moduleName"] = "core";
		json jArray = json::array();

		for (const std::shared_ptr<Def>& def : m_defs)
		{
			json jDef;
			jDef["editorId"] = def->editorId;
			jDef["type"] = (int)def->type;

			switch (def->type)
			{
			case DefType::Actor: {
				ActorDef* actor = static_pointer_cast<ActorDef>(def).get();
				jDef["displayName"] = actor->displayName;
				jDef["health"] = actor->health;
				jDef["level"] = actor->level;
				jDef["isUnique"] = actor->isUnique;
			}
			break;
			case DefType::Armor: {
				ArmorDef* armor = std::static_pointer_cast<ArmorDef>(def).get();
				jDef["displayName"] = armor->displayName;
				jDef["value"] = armor->value;
				jDef["weight"] = armor->weight;
				jDef["isUnique"] = armor->isUnique;
				jDef["armorRating"] = armor->armorRating;
			}
			break;
			case DefType::Weapon: {
				WeaponDef* weapon = std::static_pointer_cast<WeaponDef>(def).get();
				jDef["displayName"] = weapon->displayName;
				jDef["value"] = weapon->value;
				jDef["weight"] = weapon->weight;
				jDef["isUnique"] = weapon->isUnique;
				jDef["damage"] = weapon->damage;
				jDef["range"] = weapon->range;
			}
			break;
			case DefType::Consumable: {
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
				printf("[%s] error: invalid type\n", __FUNCTION__);
				continue;
			}

			jArray.push_back(jDef);
		}

		j["definitions"] = jArray;

		std::ofstream file(filePath.data());
		if (!file.is_open())
		{
			printf("[%s] error: unable to write filePath\n", __FUNCTION__);
			return false;
		}

		file << std::setw(4) << j;
		file.close();
		return true;
	}

	bool DefTable::LoadFiles(std::string_view filePath)
	{
		if (!std::filesystem::exists(filePath))
			return false;

		json j;

		std::ifstream file(filePath.data());
		if (!file.is_open())
		{
			printf("[%s] error: unable to open file\n", __FUNCTION__);
			return false;
		}

		std::stringstream ss;
		ss << file.rdbuf();
		j = json::parse(ss.str());

		std::string importModuleName = j["moduleName"];
		printf("Loading defs from:\n-> File: %s\n-> Module: %s\n", filePath.data(), importModuleName.c_str());

		if (!j["definitions"].is_array())
		{
			printf("failed to get defs array\n");
			return false;
		}

		for (const json& jDef : j["definitions"])
		{
			std::string editorId = jDef["editorId"];
			DefType type = static_cast<DefType>(jDef["type"].get<int>());

			if (type == DefType::Actor)
			{
				std::string displayName = jDef["displayName"];
				bool isUnique = jDef["isUnique"].get<bool>();
				uint32_t health = jDef["health"].get<uint32_t>();
				uint32_t level = jDef["level"].get<uint32_t>();

				ActorDef* actor = new ActorDef();
				actor->editorId = editorId;
				actor->type = type;
				actor->displayName = displayName;
				actor->isUnique = isUnique;
				actor->health = health;
				actor->level = level;

				AddDef(actor);
			}
			else if (type == DefType::Armor)
			{
				std::string displayName = jDef["displayName"];
				bool isUnique = jDef["isUnique"].get<bool>();
				float weight = jDef["weight"].get<float>();
				uint32_t value = jDef["value"].get<uint32_t>();
				uint32_t armorRating = jDef["armorRating"].get<uint32_t>();

				ArmorDef* armor = new ArmorDef();
				armor->editorId = editorId;
				armor->type = type;
				armor->displayName = displayName;
				armor->isUnique = isUnique;
				armor->weight = weight;
				armor->value = value;
				armor->armorRating = armorRating;

				AddDef(armor);
			}
			else if (type == DefType::Consumable)
			{
				std::string displayName = jDef["displayName"];
				bool isUnique = jDef["isUnique"].get<bool>();
				float weight = jDef["weight"].get<float>();
				uint32_t value = jDef["value"].get<uint32_t>();
				uint32_t effectAmount = jDef["effectAmount"].get<uint32_t>();
				float effectDuration = jDef["effectDuration"].get<float>();

				ConsumableDef* consumable = new ConsumableDef();
				consumable->editorId = editorId;
				consumable->type = type;
				consumable->displayName = displayName;
				consumable->isUnique = isUnique;
				consumable->weight = weight;
				consumable->value = value;
				consumable->effectAmount = effectAmount;
				consumable->effectDuration = effectDuration;

				AddDef(consumable);
			}
			else if (type == DefType::Weapon)
			{
				std::string displayName = jDef["displayName"];
				bool isUnique = jDef["isUnique"].get<bool>();
				float weight = jDef["weight"].get<float>();
				uint32_t value = jDef["value"].get<uint32_t>();
				uint32_t damage = jDef["damage"].get<uint32_t>();
				float range = jDef["range"].get<float>();

				WeaponDef* weapon = new WeaponDef();
				weapon->editorId = editorId;
				weapon->type = type;
				weapon->displayName = displayName;
				weapon->isUnique = isUnique;
				weapon->weight = weight;
				weapon->value = value;
				weapon->range = range;
				weapon->damage = damage;

				AddDef(weapon);
			}
			else
			{
				printf("failed to get valid type");
				continue;
			}
		}
	}

	bool DefTable::AddDef(Def* def)
	{
		if (!def)
			return false;

		def->id.value = m_defs.size() + 1;
		if (GetDefByEditorId(def->editorId) != nullptr)
		{
			printf("[%s] error: editorId already exists, skipping creation\n", __FUNCTION__);
			return false;
		}

		m_defs.push_back(std::unique_ptr<Def>(def));
		return true;
	}
	bool DefTable::RemoveDefById(DefId id)
	{
		m_defs.erase(m_defs.begin() + (id.value - 1));
		return true;
	}

	bool DefTable::RemoveDefByEditorId(std::string_view editorId)
	{
		size_t del = std::erase_if(m_defs, [editorId](const std::shared_ptr<Def>& def) {
			return def && def->editorId == editorId;
		});

		return del > 0;
	}

	bool DefTable::RemoveDefByPtr(std::shared_ptr<Def> obj)
	{
		return (std::erase(m_defs, obj));
	}

	bool DefTable::ClearDefs()
	{
		m_defs.clear();
		return (m_defs.size() == 0);
	}
}

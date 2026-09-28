#include "Game.h"
#include "Data/Defs/ActorDef.h"
#include "Data/Defs/ArmorDef.h"
#include "Data/Defs/ConsumableDef.h"
#include "Data/Defs/WeaponDef.h"

using namespace rogue;

namespace game
{
	namespace commands
	{
		void RunWindow(const std::vector<std::string>& params)
		{
			printf("Running test window\n");
			//ui::Run();
		}

		void RunRenderer(const std::vector<std::string>& params)
		{
			//run / start the Runtime engine; World + Renderer?

			printf("Running test renderer\n");
			//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)_RunRenderer, 0, 0, 0);
		}

		void WorldUpdate(const std::vector<std::string>& params)
		{
			printf("Ticking world : isInit: %i\n", (int)World->IsInit());
			World->Update(1.0f);
		}

		void WorldSpawn(const std::vector<std::string>& params)
		{
			printf("Adding def to world\n");

			InstanceId id = World->Spawn(DefId(std::stoi(params[0])));
			printf("Added new def, InstanceId: %i\n", (int)id.value);
		}

		void SaveDefs(const std::vector<std::string>& params)
		{
			bool success = DefTable->SaveFiles(params[0].c_str());
			printf("Saved: %i\n", (int)success);
		}

		void LoadDefs(const std::vector<std::string>& params)
		{
			bool success = DefTable->LoadFiles(params[0].c_str());
			printf("Loaded: %i\n", (int)success);
		}

		void PrintDefs(const std::vector<std::string>& params)
		{
			printf("Printing defs:\n");
			for (auto x : DefTable->GetDefs())
			{
				printf("EditorId : %s\n", x->editorId.c_str());
				printf("Type: %i\n", (int)x->type);

				if (x->type == DefType::Actor)
				{
					ActorDef* actor = static_pointer_cast<ActorDef>(x).get();
					printf("-->DisplayName: %s\n", actor->displayName.c_str());
					printf("-->Health: %i\n", (int)actor->health);
				}
				else if (x->type == DefType::Armor)
				{
					ArmorDef* armor = static_pointer_cast<ArmorDef>(x).get();
					printf("-->DisplayName: %s\n", armor->displayName.c_str());
					printf("-->ArmorRating: %i\n", (int)armor->armorRating);
				}
				else if (x->type == DefType::Consumable)
				{
					ConsumableDef* consumable = static_pointer_cast<ConsumableDef>(x).get();
					printf("-->DisplayName: %s\n", consumable->displayName.c_str());
					printf("-->EffectAmount: %i\n", (int)consumable->effectAmount);
				}
				else if (x->type == DefType::Weapon)
				{
					WeaponDef* weapon = static_pointer_cast<WeaponDef>(x).get();
					printf("-->DisplayName: %s\n", weapon->displayName.c_str());
					printf("-->Damage: %i\n", (int)weapon->damage);
				}
			}
		}

		void ClearDefs(const std::vector<std::string>& params)
		{
			DefTable->ClearDefs();
			printf("Cleared defs; Total: %i\n", (int)DefTable->GetDefs().size());
		}

		void CreateDefs(const std::vector<std::string>& params) //creates sample defs
		{
			{
				WeaponDef* wpn = new WeaponDef();
				wpn->editorId = "iron_sword";
				wpn->displayName = "Iron Sword";
				wpn->isUnique = false;
				wpn->range = 1.2f;
				wpn->value = 20;
				wpn->weight = 5.0f;
				wpn->damage = 5;
				DefTable->AddDef(wpn);
				printf("Side of weapon: %i\n", (int)sizeof(wpn));
			}
			{
				WeaponDef* wpn = new WeaponDef();
				wpn->editorId = "steel_sword";
				wpn->displayName = "Steel Sword";
				wpn->isUnique = false;
				wpn->range = 1.2f;
				wpn->value = 40;
				wpn->weight = 7.0f;
				wpn->damage = 7;
				DefTable->AddDef(wpn);
			}
			{
				ActorDef* actor = new ActorDef();
				actor->editorId = "npc_steven";
				actor->displayName = "Steven";
				actor->health = 100;
				actor->level = 1;
				actor->isUnique = true;
				DefTable->AddDef(actor);
			}
			{
				ActorDef* actor = new ActorDef();
				actor->editorId = "npc_ogre";
				actor->displayName = "Ogre Grunt";
				actor->health = 125;
				actor->level = 1;
				actor->isUnique = false;
				DefTable->AddDef(actor);
			}
			{
				ActorDef* actor = new ActorDef();
				actor->editorId = "npc_ogre_elite";
				actor->displayName = "Ogre Elite";
				actor->health = 300;
				actor->level = 5;
				actor->isUnique = false;
				DefTable->AddDef(actor);
			}
			{
				ActorDef* actor = new ActorDef();
				actor->editorId = "npc_ogre_captain_markkus";
				actor->displayName = "Captain Markkus";
				actor->health = 500;
				actor->level = 10;
				actor->isUnique = true;
				DefTable->AddDef(actor);
			}

			printf("Created defs; Total: %i\n", (int)DefTable->GetDefs().size());
		}

		void CreateWeaponDef(const std::vector<std::string>& params) //EditorId, DisplayName, IsUnique, Range, Value, Weight, Damage
		{
			std::string displayName = "";

			for (char c : params[1])
			{
				if (c == '_')
				{
					displayName += ' ';
				}
				else
				{
					displayName += c;
				}
			}

			WeaponDef* wpn = new WeaponDef();
			wpn->editorId = params[0];
			wpn->displayName = displayName;
			wpn->isUnique = (params[2] == "TRUE" || params[2] == "True" || params[2] == "true");
			wpn->range = std::stof(params[3]);
			wpn->value = (uint32_t)std::stoi(params[4]);
			wpn->weight = std::stof(params[5]);
			wpn->damage = (uint32_t)std::stoi(params[6]);
			DefTable->AddDef(wpn);
			printf("Created WeaponDef: %s\n", wpn->editorId.c_str());
		}

		void GetDef(const std::vector<std::string>& params)
		{
			Def* def = DefTable->GetDefByEditorId(params[0]);
			if (!def)
			{
				printf("Failed to GetDef result for EditorId: %s\n", params[0].c_str());
				return;
			}

			printf("Def obtained: %s; Type: %s\n", def->editorId.c_str(), DefTypeValues[(int)def->type].c_str());
		}

		void GetDefCount(const std::vector<std::string>& params)
		{
			printf("Count: %i\n", (int)DefTable->GetDefs().size());
		}

		void DeleteDefId(const std::vector<std::string>& params)
		{
			int id = std::stoi(params[0]);
			bool success = DefTable->RemoveDefById(DefId(id));
			printf("Deleted ID success: %i\n", (int)success);
		}

		void DeleteDefName(const std::vector<std::string>& params)
		{
			bool success = DefTable->RemoveDefByEditorId(params[0]);
			printf("Deleted ID success: %i\n", (int)success);
		}
	}
}
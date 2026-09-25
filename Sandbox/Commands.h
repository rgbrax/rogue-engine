#pragma once
#include "Console/Console.h"
#include "Data/ActorDef.h"
#include "Data/ArmorDef.h"
#include "Data/ConsumableDef.h"
#include "Data/DefTable.h"
#include "Data/WeaponDef.h"
#include "Platform/FileHandler.h"
#include "Platform/Window.h"

#include <Windows.h>

using namespace rogue;

namespace sandbox
{
	DefTable* defTable = new DefTable();
	Console* console = new Console();

	namespace ui
	{
		void Run();
	}

	namespace commands
	{
		//register commands for the console

		void Print(const std::vector<std::string>& params)
		{
			std::string output = "";
			for (std::string s : params)
			{
				output += (s + " ");
			}

			printf("print: %s\n", output.c_str());
		}

		void MsgBox(const std::vector<std::string>& params)
		{
			MessageBoxA(0, params[0].c_str(), params[1].c_str(), 0);
		}

		void RunWindow(const std::vector<std::string>& params)
		{
			printf("Running test window\n");
			ui::Run();
		}

		void SaveDefs(const std::vector<std::string>& params)
		{
			bool success = defTable->SaveFiles(params[0].c_str());
			printf("Saved: %i\n", (int)success);
		}

		void LoadDefs(const std::vector<std::string>& params)
		{
			bool success = defTable->LoadFiles(params[0].c_str());
			printf("Loaded: %i\n", (int)success);
		}

		void PrintDefs(const std::vector<std::string>& params)
		{
			printf("Printing defs:\n");
			for (auto x : defTable->GetDefs())
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
			defTable->ClearDefs();
			printf("Cleared defs; Total: %i\n", (int)defTable->GetDefs().size());
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
				defTable->AddDef(wpn);
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
				defTable->AddDef(wpn);
			}
			{
				ActorDef* actor = new ActorDef();
				actor->editorId = "npc_steven";
				actor->displayName = "Steven";
				actor->health = 100;
				actor->level = 1;
				actor->isUnique = true;
				defTable->AddDef(actor);
			}
			{
				ActorDef* actor = new ActorDef();
				actor->editorId = "npc_ogre";
				actor->displayName = "Ogre Grunt";
				actor->health = 125;
				actor->level = 1;
				actor->isUnique = false;
				defTable->AddDef(actor);
			}
			{
				ActorDef* actor = new ActorDef();
				actor->editorId = "npc_ogre_elite";
				actor->displayName = "Ogre Elite";
				actor->health = 300;
				actor->level = 5;
				actor->isUnique = false;
				defTable->AddDef(actor);
			}
			{
				ActorDef* actor = new ActorDef();
				actor->editorId = "npc_ogre_captain_markkus";
				actor->displayName = "Captain Markkus";
				actor->health = 500;
				actor->level = 10;
				actor->isUnique = true;
				defTable->AddDef(actor);
			}

			printf("Created defs; Total: %i\n", (int)defTable->GetDefs().size());
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
			defTable->AddDef(wpn);
			printf("Created WeaponDef: %s\n", wpn->editorId.c_str());
		}

		void GetDef(const std::vector<std::string>& params)
		{
			Def* def = defTable->GetDefByEditorId(params[0]);
			if (!def)
			{
				printf("Failed to GetDef result for EditorId: %s\n", params[0].c_str());
				return;
			}

			printf("Def obtained: %s; Type: %s\n", def->editorId.c_str(), DefTypeValues[(int)def->type].c_str());
		}

		void GetDefCount(const std::vector<std::string>& params)
		{
			printf("Count: %i\n", (int)defTable->GetDefs().size());
		}

		void DeleteDefId(const std::vector<std::string>& params)
		{
			int id = std::stoi(params[0]);
			bool success = defTable->RemoveDefById(DefId(id));
			printf("Deleted ID success: %i\n", (int)success);
		}

		void DeleteDefName(const std::vector<std::string>& params)
		{
			bool success = defTable->RemoveDefByEditorId(params[0]);
			printf("Deleted ID success: %i\n", (int)success);
		}
	}

	namespace ui
	{
		//would make its own file, but not really worth it at the moment

		namespace funcs
		{
			void CreateWeaponDef()
			{
				//this is obv not how we will be making our defs, but a fun test

				std::string wpnDefEditorId = window::GetControlText("wpnDefEditorId");
				std::string wpnDefDisplayName = window::GetControlText("wpnDefDisplayName");
				std::string wpnDefIsUnique = window::GetControlText("wpnDefIsUnique");
				std::string wpnDefRange = window::GetControlText("wpnDefRange");
				std::string wpnDefValue = window::GetControlText("wpnDefValue");
				std::string wpnDefWeight = window::GetControlText("wpnDefWeight");
				std::string wpnDefDamage = window::GetControlText("wpnDefDamage");

				std::vector<std::string> params{};
				params.push_back(wpnDefEditorId);
				params.push_back(wpnDefDisplayName);
				params.push_back(wpnDefIsUnique);
				params.push_back(wpnDefRange);
				params.push_back(wpnDefValue);
				params.push_back(wpnDefWeight);
				params.push_back(wpnDefDamage);

				commands::CreateWeaponDef(params);				
			}

			void PrintDefs( )
			{
				commands::PrintDefs(std::vector<std::string>());
			}

			void LoadDefs( )
			{
				//txtLoadDefsPath
				std::vector<std::string> params;
				params.push_back(window::GetControlText("txtLoadDefsPath"));
				commands::LoadDefs(params);
			}

			void SaveDefs( )
			{
				//txtSaveDefsPath
				std::vector<std::string> params;
				params.push_back(window::GetControlText("txtSaveDefsPath"));
				commands::SaveDefs(params);
			}

			void ClearDefs( )
			{
				commands::ClearDefs(std::vector<std::string>());
			}
		}

		void Run()
		{
			window::m_windowTitle = "REngine";
			window::m_windowClassName = "REngineClass";

			//general engine funcs column
			window::AddControl(window::ControlType::Label, "labelIntro", "Engine controls", 150, 25);
			window::AddControl(window::ControlType::Button, "btnPrintDefs", "Print Defs", 150, 25);
			window::AddControlFunction("btnPrintDefs", funcs::PrintDefs);
			window::AddControl(window::ControlType::Button, "btnClearDefs", "Clear Defs", 150, 25);
			window::AddControlFunction("btnClearDefs", funcs::ClearDefs);
			window::AddControl(window::ControlType::Edit, "txtLoadDefsPath", "load.json", 150, 25);
			window::AddControl(window::ControlType::Button, "btnLoadDefs", "Load Defs", 150, 25);
			window::AddControlFunction("btnLoadDefs", funcs::LoadDefs);
			window::AddControl(window::ControlType::Edit, "txtSaveDefsPath", "save.json", 150, 25);
			window::AddControl(window::ControlType::Button, "btnSaveDefs", "Save Defs", 150, 25);
			window::AddControlFunction("btnSaveDefs", funcs::SaveDefs);

			window::NextColumn();

			//CreateWeaponDef column
			window::AddControl(window::ControlType::Label, "wpnDefLabel", "Create WeaponDef:", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefEditorId", "EditorId", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefDisplayName", "DisplayName", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefIsUnique", "IsUnique", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefRange", "Range", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefValue", "Value", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefWeight", "Weight", 150, 25);
			window::AddControl(window::ControlType::Edit, "wpnDefDamage", "Damage", 150, 25);
			window::AddControl(window::ControlType::Button, "wpnDefCreateButton", "Create WeaponDef", 150, 25);
			window::AddControlFunction("wpnDefCreateButton", funcs::CreateWeaponDef);

			window::NextColumn();

			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)window::Setup, 0, 0, 0);
		}
	}
}

#include "Data/ActorDef.h"
#include "Data/ArmorDef.h"
#include "Data/ConsumableDef.h"
#include "Data/DefManager.h"
#include "Data/WeaponDef.h"

#include "Platform/WinAPI.h"
#include "Platform/Window.h"

#include "Console/Console.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace rogue;

DefManager* defMgr = new DefManager();
WinAPI* winapi = new WinAPI();
Console* console = new Console();

namespace sandbox
{
	namespace ui_funcs
	{
		void Login()
		{
			std::string user = window::GetControlText("txt_login_username");
			std::string pass = window::GetControlText("txt_login_password");

			if (user.empty() || pass.empty())
			{
				window::SetControlText("label_login_result_msg", "Login result: error");
				return;
			}

			if (user == "admin" && pass == "123")
			{
				window::SetControlText("label_login_result_msg", "Login result: success");
				return;
			}
			else
			{
				window::SetControlText("label_login_result_msg", "Login result: failure");
				return;
			}
		}
	}

	namespace console_funcs
	{
		void RunWindow(const std::vector<std::string>& params) //test window ui : runs in new thread
		{
			window::m_windowTitle = "REngine";
			window::m_windowClassName = "REngineClass";
			window::AddControl(window::ControlType::Label, "label_login_msg", "Login:", 150, 25);
			window::AddControl(window::ControlType::Edit, "txt_login_username", "user", 150, 25);
			window::AddControl(window::ControlType::Edit, "txt_login_password", "pass", 150, 25);
			window::AddControl(window::ControlType::Button, "btn_login_run", "Login", 150, 25);
			window::AddControl(window::ControlType::Label, "label_login_result_msg", "Login result: none", 150, 25);
			window::AddControlFunction("btn_login_run", ui_funcs::Login);
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)window::Setup, 0, 0, 0);
		}

		void SaveDefs(const std::vector<std::string>& params)
		{
			bool success = defMgr->SaveFiles(params[0].c_str());
			printf("Saved: %i\n", (int)success);
		}

		void LoadDefs(const std::vector<std::string>& params)
		{
			bool success = defMgr->LoadFiles(params[0].c_str());
			printf("Loaded: %i\n", (int)success);
		}

		void PrintDefs(const std::vector<std::string>& params)
		{
			printf("Printing defs:\n");
			for (auto x : defMgr->GetDefs())
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
			defMgr->ClearDefs();
			printf("Cleared defs; Total: %i\n", (int)defMgr->GetDefs().size());
		}

		void CreateDefs(const std::vector<std::string>& params) //creates sample defs
		{
			{
				WeaponDef* wpn = new WeaponDef();
				wpn->editorId = "iron_sword";
				wpn->displayName = "Iron Sword";
				wpn->isUnique = false;
				wpn->range = 1.2f;
				wpn->type = DefType::Weapon;
				wpn->value = 20;
				wpn->weight = 5.0f;
				wpn->damage = 5;
				defMgr->AddDef(wpn);
				printf("Side of weapon: %i\n", (int)sizeof(wpn));
			}
			{
				WeaponDef* wpn = new WeaponDef();
				wpn->editorId = "steel_sword";
				wpn->displayName = "Steel Sword";
				wpn->isUnique = false;
				wpn->range = 1.2f;
				wpn->type = DefType::Weapon;
				wpn->value = 40;
				wpn->weight = 7.0f;
				wpn->damage = 7;
				defMgr->AddDef(wpn);
			}
			{
				ActorDef* actor = new ActorDef();
				actor->editorId = "npc_steven";
				actor->displayName = "Steven";
				actor->health = 100;
				actor->level = 1;
				actor->isUnique = true;
				actor->type = DefType::Actor;
				defMgr->AddDef(actor);
			}
			{
				ActorDef* actor = new ActorDef();
				actor->editorId = "npc_ogre";
				actor->displayName = "Ogre Grunt";
				actor->health = 125;
				actor->level = 1;
				actor->isUnique = false;
				actor->type = DefType::Actor;
				defMgr->AddDef(actor);
			}
			{
				ActorDef* actor = new ActorDef();
				actor->editorId = "npc_ogre_elite";
				actor->displayName = "Ogre Elite";
				actor->health = 300;
				actor->level = 5;
				actor->isUnique = false;
				actor->type = DefType::Actor;
				defMgr->AddDef(actor);
			}
			{
				ActorDef* actor = new ActorDef();
				actor->editorId = "npc_ogre_captain_markkus";
				actor->displayName = "Captain Markkus";
				actor->health = 500;
				actor->level = 10;
				actor->isUnique = true;
				actor->type = DefType::Actor;
				defMgr->AddDef(actor);
			}

			printf("Created defs; Total: %i\n", (int)defMgr->GetDefs().size());
		}

		void GetDef(const std::vector<std::string>& params)
		{
		}

		void GetDefCount(const std::vector<std::string>& params)
		{
			printf("Count: %i\n", (int)defMgr->GetDefs().size());
		}

		void DeleteDefId(const std::vector<std::string>& params)
		{
			int id = std::stoi(params[0]);
			bool success = defMgr->RemoveDefById(DefId(id));
			printf("Deleted ID success: %i\n", (int)success);
		}

		void DeleteDefName(const std::vector<std::string>& params)
		{
			bool success = defMgr->RemoveDefByEditorId(params[0]);
			printf("Deleted ID success: %i\n", (int)success);
		}
	}

	void Run()
	{
		console->Setup();
		console->RegisterCommand(console_funcs::RunWindow, 0, "RunWindow");
		console->RegisterCommand(console_funcs::SaveDefs, 1, "SaveDefs");
		console->RegisterCommand(console_funcs::LoadDefs, 1, "LoadDefs");
		console->RegisterCommand(console_funcs::CreateDefs, 0, "CreateDefs");
		console->RegisterCommand(console_funcs::ClearDefs, 0, "ClearDefs");
		console->RegisterCommand(console_funcs::PrintDefs, 0, "PrintDefs");
		console->RegisterCommand(console_funcs::GetDefCount, 0, "GetDefCount");
		console->RegisterCommand(console_funcs::DeleteDefId, 1, "DeleteDefId");
		console->RegisterCommand(console_funcs::DeleteDefName, 1, "DeleteDefName");

		while (true)
		{
			std::string line;
			printf("Console> ");
			std::getline(std::cin, line);
			std::stringstream ss(line);

			std::string cmd;
			std::vector<std::string> params;

			std::string word;
			while (ss >> word)
			{
				if (cmd.empty())
					cmd = word;
				else
					params.push_back(word);
			}

			console->Run(cmd, params);
		}
	}
}

int main(int argc, const char* argv[])
{
	printf("START\n");
	sandbox::Run();
	printf("END");
	return 0;
}

#include "Data/ActorDef.h"
#include "Data/ArmorDef.h"
#include "Data/ConsumableDef.h"
#include "Data/DefManager.h"
#include "Data/WeaponDef.h"

#include "Platform/WinAPI.h"
#include "Platform/Window.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace rogue;

namespace test
{
	DefManager* defMgr = new DefManager();
	WinAPI* winapi = new WinAPI();

	namespace funcs
	{
		void MsgBox()
		{
			std::string title = "Notice";
			std::string msg = window::GetControlText("txt_msgbox_input");
			MessageBoxA(window::m_window, msg.c_str(), 0, 0);
		}

		void LogMsg()
		{
			std::string msg = window::GetControlText("txt_log_input");
			printf("[ui_log] : %s\n", msg.c_str());
		}

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

	void window()
	{
		window::m_windowTitle = "REngine";
		window::m_windowClassName = "REngineClass";
		window::AddControl(window::ControlType::Label, "label_intro", "REngine test window:", 150, 25);

		window::AddControl(window::ControlType::Edit, "txt_msgbox_input", "", 150, 25);
		window::AddControl(window::ControlType::Button, "btn_msgbox_run", "Submit Msg", 150, 25);
		window::AddControl(window::ControlType::Label, "label_filler_01", "", 150, 25);

		window::AddControl(window::ControlType::Edit, "txt_log_input", "", 150, 25);
		window::AddControl(window::ControlType::Button, "btn_log_run", "Submit Log", 150, 25);
		window::AddControl(window::ControlType::Label, "label_filler_02", "", 150, 25);

		window::AddControl(window::ControlType::Label, "label_login_msg", "Login:", 150, 25);
		window::AddControl(window::ControlType::Edit, "txt_login_username", "user", 150, 25);
		window::AddControl(window::ControlType::Edit, "txt_login_password", "pass", 150, 25);
		window::AddControl(window::ControlType::Button, "btn_login_run", "Login", 150, 25);
		window::AddControl(window::ControlType::Label, "label_login_result_msg", "Login result: none", 150, 25);

		window::AddControlFunction("btn_msgbox_run", funcs::MsgBox);
		window::AddControlFunction("btn_log_run", funcs::LogMsg);
		window::AddControlFunction("btn_login_run", funcs::Login);

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)window::Setup, 0, 0, 0);
	}

	void save()
	{
		bool success = defMgr->SaveFiles("test.json");
		printf("Saved: %i\n", (int)success);
	}

	void load()
	{
		bool success = defMgr->LoadFiles("test.json");
		printf("Loaded: %i\n", (int)success);
	}

	void create()
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

	void clear()
	{
		defMgr->ClearDefs();
		printf("Cleared defs; Total: %i\n", (int)defMgr->GetDefs().size());
	}

	void print()
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

	void count()
	{
		printf("Count: %i\n", (int)defMgr->GetDefs().size());
	}

	void del(int id)
	{
		bool success = defMgr->RemoveDefById(DefId(id));
		printf("Deleted ID success: %i\n", (int)success);
	}

	void run()
	{
		while (true)
		{
			std::string input = "";
			printf("command: ");
			std::cin >> input;

			if (input == "save")
			{
				save();
			}
			else if (input == "load")
			{
				load();
			}
			else if (input == "create")
			{
				create();
			}
			else if (input == "print")
			{
				print();
			}
			else if (input == "count")
			{
				count();
			}
			else if (input == "clear")
			{
				clear();
			}
			else if (input == "window")
			{
				window();
			}
			else if (input == "del_id")
			{
				int num;
				printf("number: ");
				std::cin >> num;
				del(num);
			}

			printf("\n\n");
		}
	}
}

int main(int argc, const char* argv[])
{
	printf("START\n");
	test::run();
	std::cin;
	printf("END");
	return 0;
}

#include "Data/ActorDef.h"
#include "Data/ArmorDef.h"
#include "Data/ConsumableDef.h"
#include "Data/WeaponDef.h"
#include "Data/DefManager.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace rogue;

bool ReadFile(const std::string& path, std::string& outText)
{
	std::ifstream in(path, std::ios::binary);
	if (!in)
		return false;

	std::ostringstream ss;
	ss << in.rdbuf();
	outText = ss.str();
	return true;
}

bool WriteFile(const std::string& path, const std::string& text)
{
	std::ofstream out(path, std::ios::binary);
	if (!out)
		return false;

	out << text;
	return static_cast<bool>(out);
}

void RunTest( )
{
	DefManager defMgr;
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
		defMgr.AddDef(wpn);
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
		defMgr.AddDef(wpn);
	}
	{
		ActorDef* actor = new ActorDef();
		actor->editorId = "npc_steven";
		actor->displayName = "Steven";
		actor->health = 100;
		actor->level = 1;
		actor->isUnique = true;
		actor->type = DefType::Actor;
		defMgr.AddDef(actor);
	}
	{
		ActorDef* actor = new ActorDef();
		actor->editorId = "npc_ogre";
		actor->displayName = "Ogre Grunt";
		actor->health = 125;
		actor->level = 1;
		actor->isUnique = false;
		actor->type = DefType::Actor;
		defMgr.AddDef(actor);

	}
	{
		ActorDef* actor = new ActorDef();
		actor->editorId = "npc_ogre_elite";
		actor->displayName = "Ogre Elite";
		actor->health = 300;
		actor->level = 5;
		actor->isUnique = false;
		actor->type = DefType::Actor;
		defMgr.AddDef(actor);

	}
	{
		ActorDef* actor = new ActorDef();
		actor->editorId = "npc_ogre_captain_markkus";
		actor->displayName = "Captain Markkus";
		actor->health = 500;
		actor->level = 10;
		actor->isUnique = true;
		actor->type = DefType::Actor;
		defMgr.AddDef(actor);
	}

	defMgr.SaveFiles();
	defMgr.LoadFiles();
}

int main(int argc, const char* argv[])
{
	printf("START\n");
	RunTest();
	std::cin;
	printf("END");
	return 0;
}

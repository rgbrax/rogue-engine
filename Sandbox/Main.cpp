#include "Data/ActorDef.h"
#include "Data/ArmorDef.h"
#include "Data/ConsumableDef.h"
#include "Data/DefRegistry.h"
#include "Data/DefTable.h"
#include "Data/TextSerializer.h"
#include "Data/WeaponDef.h"

#include <cstdio>
#include <fstream>
#include <sstream>

#include <Windows.h>

using namespace rogue;

static std::string ReadFile(const char* path)
{
	std::ifstream in(path, std::ios::binary);
	std::ostringstream ss;
	ss << in.rdbuf();
	return ss.str();
}

static void WriteFile(const char* path, const std::string& text)
{
	std::ofstream out(path, std::ios::binary);
	out << text;
}

void CreateSampleModule() //create sample defs
{
	DefTable table;

	//weapon
	auto iron = std::make_unique<WeaponDef>();
	iron->type = DefType::Weapon;
	iron->editorId = "weapon_iron_sword";
	iron->displayName = "Iron Sword";
	iron->weight = 5.0f;
	iron->value = 25;
	iron->damage = 10.0f;
	iron->reach = 1.2f;
	table.Add(std::move(iron));

	//armor
	auto helmet = std::make_unique<ArmorDef>();
	helmet->type = DefType::Armor;
	helmet->editorId = "armor_iron_helmet";
	helmet->displayName = "Iron Helmet";
	helmet->weight = 8.0f;
	helmet->value = 40;
	helmet->armorRating = 12.0f;
	helmet->armorType = ArmorType::HeavyArmor;
	table.Add(std::move(helmet));

	//consumable
	auto healthPotion = std::make_unique<ConsumableDef>();
	healthPotion->type = DefType::Consumable;
	healthPotion->editorId = "aid_health_potion";
	healthPotion->displayName = "Health Potion";
	healthPotion->consumableType = ConsumableType::Potion;
	healthPotion->effectAmount = 25;
	healthPotion->effectDuration = 0.0f;
	healthPotion->value = 10;
	healthPotion->weight = 0.1f;

	//actor
	auto goblin = std::make_unique<ActorDef>();
	goblin->type = DefType::Actor;
	goblin->editorId = "actor_goblin";
	goblin->displayName = "Goblin";
	goblin->level = 1;
	goblin->isUnique = false;

	std::string fileData = TextSerializer::WriteAll(table);
	WriteFile("base.roguemod", fileData);
}

void RunCreateSampleDefs()
{
	CreateSampleModule();
	printf("Sample file created!\n");
}

//temp location
DefTable defTable;

void RunLoadDefs( std::string filePath )
{
	int defCountOld = defTable.Count();
	int defCountNew = 0;

	std::string error;
	if (!TextSerializer::ReadAll(ReadFile(filePath.c_str()), defTable, &error))
	{
		std::printf("read failed: %s\n", error.c_str());
		return;
	}

	defCountNew = (int)defTable.Count();

	printf("File loaded!\n");
	printf("-> loaded %i defs (%i total)\n", (defCountNew-defCountOld), defCountNew);
}

void RunListDefinitions( )
{
	printf("DefRegistry: DefType Count: %i\n", (int)DefRegistry::All().size());
	for (const DefTypeInfo& info : DefRegistry::All())
		printf("->%s\n", info.name.data());

	printf("DefRegistry: DefTable Count: %i\n", (int)defTable.Count());

	//list each def
	for (const auto& x : defTable.All())
	{
		printf("DefId: %llu\n", x->id.value);
		printf("->Def EditorId: %s\n", x->editorId.c_str());

		if (x->type == DefType::Weapon)
		{
			printf("->DefType : Weapon");
			WeaponDef* weapon = static_cast<WeaponDef*>(x.get());
			printf("->->Damage: %f\n", weapon->damage);
			printf("->->Reach: %f\n", weapon->reach);
		}
	}
}

void RunListDefById(std::string editorId)
{
	//confirm objects
	if (const Def* def = defTable.Find(editorId))
		printf("\nloaded '%s' as a %s\n", def->editorId.c_str(), def->GetSchema().TypeName().c_str());
}

void RunLoadInstances( )
{

}

int main(int argc, const char* argv[])
{
	printf("param entered: %s\n", argv[1]);

	if (std::string(argv[1]) == "save") //save the current defs to the base file
	{
		RunCreateSampleDefs();
	}
	else if (std::string(argv[1]) == "load") //load a typed filename
	{
		RunLoadDefs(argv[2]);
	}
	else if ( std::string( argv[1] ) == "list" ) //list the current defs in the system
	{
		RunListDefinitions();
	}
	else if ( std::string( argv[1] ) == "getdef" )
	{
		RunListDefById(std::string(argv[2]));
	}
	else if ( std::string( argv[1] ) == "run" ) //run and compile the current defs into instances, then do something
	{
		RunLoadInstances();
	}
	else
	{
		printf("Error: invalid parameter;\nParameters:\n1) save | Save sample def types\n2) load | Load file defs\n3) help | this screen\n4) list | list all loaded defs\n5) getdef <EditorId> | list def by defid\n6) run | run the instances");
	}

	return 1;
}

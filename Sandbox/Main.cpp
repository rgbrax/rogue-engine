#include "Data/ArmorDef.h"
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

//test hardcoded content
static void BuildContent(DefTable& table)
{
	
}

void CreateSampleModule()
{
	DefTable table;

	//sample defs
	auto iron = std::make_unique<WeaponDef>();
	iron->editorId = "weapon_iron_sword";
	iron->type = DefType::Weapon;
	iron->displayName = "Iron Sword";
	iron->weight = 5.0f;
	iron->value = 25;
	iron->damage = 10.0f;
	iron->reach = 1.2f;
	table.Add(std::move(iron));

	auto helmet = std::make_unique<ArmorDef>();
	helmet->editorId = "armor_iron_helmet";
	helmet->Def::type = DefType::Armor;
	helmet->displayName = "Iron Helmet";
	helmet->weight = 8.0f;
	helmet->value = 40;
	helmet->armorRating = 12.0f;
	helmet->armorType = ArmorType::HeavyArmor;
	table.Add(std::move(helmet));

	std::string fileData = TextSerializer::WriteAll(table);
	WriteFile("base.roguemod", fileData);
}

int main()
{
	printf("==RogueEngine==\n");
	printf("DefRegistry: DefType Count: %i\n", (int)DefRegistry::All().size());
	for (const DefTypeInfo& info : DefRegistry::All())
		printf("->%s\n", info.name.data());

	//CreateSampleModule();
	//printf("Sample file created!\n");

	//read deftable
	DefTable loaded;
	std::string error;
	if (!TextSerializer::ReadAll(ReadFile("base.roguemod"), loaded, &error))
	{
		std::printf("read failed: %s\n", error.c_str());
		return 1;
	}

	printf("File loaded!\n");
	printf("-> loaded %i defs\n", (int)loaded.Count());

	//list each def
	for ( const auto &x : loaded.All( ) )
	{
		printf("DefId: %llu\n", x->id.value);
		printf("->Def EditorId: %s\n", x->editorId.c_str());

		if ( x->type == DefType::Weapon )
		{
			printf("->DefType : Weapon");
			WeaponDef* weapon = static_cast<WeaponDef*>(x.get());
			printf("->->Damage: %f\n", weapon->damage);
			printf("->->Reach: %f\n", weapon->reach);
		}
	}

	//confirm objects
	if (const Def* sword = loaded.Find("weapon_iron_sword"))
		printf("\nloaded '%s' as a %s\n",
			sword->editorId.c_str(), sword->GetSchema().TypeName().c_str());

	printf("END");
	while (true)
		Sleep(1000);

	return 0;
}

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
	printf("Starting file load\n");
	DefManager defmgr;
	defmgr.LoadFiles();
	printf("Loaded def count: %i\n", (int)defmgr.GetDefs().size());
	printf("Test print:\n");
	Def* def = defmgr.GetDefByEditorId("iron_sword");
	if ( def->type == DefType::Weapon )
	{
		WeaponDef* weapon = static_cast<WeaponDef*>(def);
		printf("Weapon display name: %s, weapon damage: %i\n", weapon->displayName.c_str(), weapon->damage);
	}
}

int main(int argc, const char* argv[])
{
	printf("START\n");
	RunTest();
	std::cin;
	printf("END");
	return 0;
}

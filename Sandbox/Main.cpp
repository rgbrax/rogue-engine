#include "Data/ActorDef.h"
#include "Data/ArmorDef.h"
#include "Data/ConsumableDef.h"
#include "Data/DefRegistry.h"
#include "Data/DefTable.h"
#include "Data/TextSerializer.h"
#include "Data/WeaponDef.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace rogue;
DefTable g_defTable;

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

std::string FieldValueToString(const FieldDesc& field, const Value& value)
{
	switch (field.type)
	{
	case FieldType::Bool:
		return std::get<bool>(value) ? "true" : "false";

	case FieldType::Int:
		return std::to_string(std::get<int64_t>(value));

	case FieldType::Float: {
		char buffer[32];
		std::snprintf(buffer, sizeof(buffer), "%g", std::get<double>(value));
		return buffer;
	}

	case FieldType::String:
		return "\"" + std::get<std::string>(value) + "\"";

	case FieldType::Ref:
		return "#" + std::to_string(std::get<DefId>(value).value);

	case FieldType::Enum: {
		const int64_t n = std::get<int64_t>(value);
		for (const EnumEntry& entry : field.enumValues)
		{
			if (entry.value == n)
				return std::string(entry.name);
		}
		return std::to_string(n);
	}

	default:
		return "?";
	}
}

void PrintDef(const Def& def)
{
	const Schema& schema = def.GetSchema();
	std::printf("%s %s (id %llu)\n", schema.TypeName().c_str(), def.editorId.c_str(),
				static_cast<unsigned long long>(def.id.value));

	std::vector<const FieldDesc*> fields;
	schema.CollectFields(fields);

	for (const FieldDesc* field : fields)
		std::printf("    %-16s %s\n", field->name.c_str(), FieldValueToString(*field, field->get(&def)).c_str());
}

void AddSampleDefs(DefTable& table)
{
	auto iron = std::make_unique<WeaponDef>();
	iron->type = DefType::Weapon;
	iron->editorId = "weapon_iron_sword";
	iron->displayName = "Iron Sword";
	iron->weight = 5.0f;
	iron->value = 25;
	iron->damage = 10.0f;
	iron->reach = 1.2f;
	table.Add(std::move(iron));

	auto helmet = std::make_unique<ArmorDef>();
	helmet->type = DefType::Armor;
	helmet->editorId = "armor_iron_helmet";
	helmet->displayName = "Iron Helmet";
	helmet->weight = 8.0f;
	helmet->value = 40;
	helmet->armorRating = 12.0f;
	helmet->armorType = ArmorType::HeavyArmor;
	table.Add(std::move(helmet));

	auto healthPotion = std::make_unique<ConsumableDef>();
	healthPotion->type = DefType::Consumable;
	healthPotion->editorId = "aid_health_potion";
	healthPotion->displayName = "Health Potion";
	healthPotion->consumableType = ConsumableType::Potion;
	healthPotion->effectAmount = 25;
	healthPotion->effectDuration = 0.0f;
	healthPotion->value = 10;
	healthPotion->weight = 0.1f;
	table.Add(std::move(healthPotion));

	auto goblin = std::make_unique<ActorDef>();
	goblin->type = DefType::Actor;
	goblin->editorId = "actor_goblin";
	goblin->displayName = "Goblin";
	goblin->health = 20;
	goblin->level = 1;
	goblin->isUnique = false;
	table.Add(std::move(goblin));
}

void PrintHelp()
{
	std::printf(
		"commands:\n"
		"  sample <file>    write a sample module (sword, helmet, potion, goblin)\n"
		"  load <file>      load defs from a module; repeat to load more files\n"
		"  save <file>      save every loaded def into one module\n"
		"  list             list every loaded def and its fields\n"
		"  get <editorId>   show one loaded def\n"
		"  types            list the def types the registry can create\n"
		"  clear            unload every def\n"
		"  help             show this list\n"
		"  quit             exit\n");
}

bool TakesArgument(const std::string& command)
{
	return command == "sample" || command == "load" || command == "save" || command == "get";
}

bool RunCommand(const std::string& command, const std::string& arg)
{
	if (TakesArgument(command) && arg.empty())
	{
		std::printf("usage: %s <%s>\n", command.c_str(), command == "get" ? "editorId" : "file");
		return true;
	}

	if (command == "sample")
	{
		DefTable sample;
		AddSampleDefs(sample);
		if (WriteFile(arg, TextSerializer::WriteAll(sample)))
			std::printf("wrote %zu sample defs to %s\n", sample.Count(), arg.c_str());
		else
			std::printf("could not write %s\n", arg.c_str());
	}
	else if (command == "load")
	{
		std::string text;
		if (!ReadFile(arg, text))
		{
			std::printf("could not open %s\n", arg.c_str());
			return true;
		}

		const size_t before = g_defTable.Count();
		std::string error;
		const bool ok = TextSerializer::ReadAll(text, g_defTable, &error);
		const size_t added = g_defTable.Count() - before;

		if (!ok)
			std::printf("stopped reading %s: %s\n", arg.c_str(), error.c_str());
		std::printf("loaded %zu new defs from %s (%zu total)\n", added, arg.c_str(), g_defTable.Count());
	}
	else if (command == "save")
	{
		if (WriteFile(arg, TextSerializer::WriteAll(g_defTable)))
			std::printf("saved %zu defs to %s\n", g_defTable.Count(), arg.c_str());
		else
			std::printf("could not write %s\n", arg.c_str());
	}
	else if (command == "list")
	{
		if (g_defTable.Count() == 0)
			std::printf("no defs loaded\n");
		for (const std::unique_ptr<Def>& def : g_defTable.All())
			PrintDef(*def);
	}
	else if (command == "get")
	{
		if (const Def* def = g_defTable.Find(arg))
			PrintDef(*def);
		else
			std::printf("'%s' is not loaded\n", arg.c_str());
	}
	else if (command == "types")
	{
		for (const DefTypeInfo& info : DefRegistry::All())
			std::printf("  %.*s\n", static_cast<int>(info.name.size()), info.name.data());
	}
	else if (command == "clear")
	{
		g_defTable.Clear();
		std::printf("unloaded every def\n");
	}
	else if (command == "help")
	{
		PrintHelp();
	}
	else if (command == "quit" || command == "exit")
	{
		return false;
	}
	else
	{
		std::printf("unknown command '%s'; type help\n", command.c_str());
	}

	return true;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			const std::string command = argv[i];
			std::string arg;
			if (TakesArgument(command) && i + 1 < argc)
				arg = argv[++i];

			if (!RunCommand(command, arg))
				break;
		}
		return 0;
	}

	PrintHelp();

	std::string line;
	while (true)
	{
		std::printf("> ");
		if (!std::getline(std::cin, line))
			break;

		size_t start = line.find_first_not_of(" \t\r");
		if (start == std::string::npos)
			continue;

		size_t end = line.find_first_of(" \t\r", start);
		std::string command = line.substr(start, end == std::string::npos ? std::string::npos : end - start);

		std::string arg;
		if (end != std::string::npos)
		{
			size_t argStart = line.find_first_not_of(" \t\r", end);
			if (argStart != std::string::npos)
				arg = line.substr(argStart, line.find_last_not_of(" \t\r") - argStart + 1);
		}

		if (!RunCommand(command, arg))
			break;
	}

	return 0;
}

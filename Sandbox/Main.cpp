#include "Data/ArmorDef.h"
#include "Data/DefTable.h"
#include "Data/WeaponDef.h"

#include <cstdio>
#include <memory>

using namespace rogue;

void PrintDef(const Def& def)
{
	std::vector<const FieldDesc*> fields;
	def.GetSchema().CollectFields(fields);

	printf("Definition #%llu) EditorId: %s, Type: %s\n", def.id.value, def.editorId.c_str(), def.GetSchema().TypeName().c_str());
	printf("Fields:\n");

	for (const FieldDesc* field : fields)
	{
		const Value v = field->get(&def);
		std::printf("\t%-14s = ", field->name.c_str());

		switch (field->type)
		{
		case FieldType::Bool:
			std::printf("%s", std::get<bool>(v) ? "true" : "false");
			break;
		case FieldType::Int:
		case FieldType::Enum:
			std::printf("%lld", (long long)std::get<int64_t>(v));
			break;
		case FieldType::Float:
			std::printf("%g", std::get<double>(v));
			break;
		case FieldType::String:
			std::printf("\"%s\"", std::get<std::string>(v).c_str());
			break;
		case FieldType::Ref:
			std::printf("DefId(%llu)", (unsigned long long)std::get<DefId>(v).value);
			break;
		}
		std::printf("\n");
	}
}

void LoadTestDefs(DefTable& table)
{
	auto iron = std::make_unique<WeaponDef>();
	iron->editorId = "weapon_iron_sword";
	iron->type = DefType::Weapon;
	iron->displayName = "Iron Sword";
	iron->weight = 5.0f;
	iron->value = 25;
	iron->damage = 7.0f;
	iron->reach = 1.2f;
	table.Add(std::move(iron));

	auto steel = std::make_unique<WeaponDef>();
	steel->editorId = "weapon_steel_sword";
	steel->type = DefType::Weapon;
	steel->displayName = "Steel Sword";
	steel->weight = 6.0f;
	steel->value = 60;
	steel->damage = 12.0f;
	steel->reach = 1.2f;
	table.Add(std::move(steel));

	auto helmet = std::make_unique<ArmorDef>();
	helmet->editorId = "armor_iron_helmet";
	helmet->Def::type = DefType::Armor;
	helmet->displayName = "Iron Helmet";
	helmet->weight = 8.0f;
	helmet->value = 40;
	helmet->armorRating = 12.0f;
	helmet->type = ArmorType::HeavyArmor;
	table.Add(std::move(helmet));
}

int main()
{
	DefTable table;
	LoadTestDefs(table);

	std::printf("loaded %i defs\n\n", (int)table.Count());

	for (const std::unique_ptr<Def>& def : table.All())
	{
		PrintDef(*def);
		std::printf("\n");
	}

	if (const Def* def = table.Find("weapon_steel_sword"))
		std::printf("found by name: %s\n", def->editorId.c_str());

	if (const Def* def = table.Get(DefId{1}))
		std::printf("found by id 1: %s\n", def->editorId.c_str());

	return 0;
}

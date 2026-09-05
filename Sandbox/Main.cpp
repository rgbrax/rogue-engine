#include "Data/DefRegistry.h"
#include "Data/DefTable.h"
#include "Data/WeaponDef.h"
#include "Core/Schema.h"

#include <cstdio>
#include <string>
#include <vector>

#include "Data/ArmorDef.h"
#include "Data/WeaponDef.h"

#include <cstdio>
#include <vector>

using namespace rogue;

//test - print constructed definition
void PrintDef(const Def& def)
{
	std::vector<const FieldDesc*> fields;
	def.GetSchema().CollectFields(fields);

	std::printf("%s : \"%s\"\n", def.GetSchema().TypeName().c_str(), def.editorId.c_str());

	for (const FieldDesc* field : fields)
	{
		const Value v = field->get(&def);
		std::printf("    %-14s = ", field->name.c_str());

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

void Run( )
{
	printf("APP_START");
	{
		rogue::WeaponDef ironSword;
		ironSword.id.value = 1;
		ironSword.editorId = "weapon_iron_sword";
		ironSword.type = rogue::DefType::Weapon;
		ironSword.displayName = "Iron Sword";
		ironSword.weight = 5.0f;
		ironSword.value = 25;
		ironSword.damage = 10.0f;
		ironSword.reach = 1.2f;
		ironSword.damageType = rogue::DamageType::Physical;

		PrintDef(ironSword);
	}
	printf("APP_END");
}

int main()
{
	Run();
	return 0;
}

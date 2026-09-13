#include "Data/DefRegistry.h"
#include "Data/ArmorDef.h"
#include "Data/ConsumableDef.h"
#include "Data/WeaponDef.h"

namespace rogue
{
	namespace
	{
		template <typename T>
		std::unique_ptr<Def> New()
		{
			return std::make_unique<T>();
		}

		const DefTypeInfo Table[] =
		{
			{DefType::Weapon, "WeaponDef", &New<WeaponDef>},
			{DefType::Armor, "ArmorDef", &New<ArmorDef>},
			{DefType::Consumable, "ConsumableDef", &New<ConsumableDef>},
			{DefType::Actor, "ActorDef", &New<ConsumableDef>},
		};
	}

	std::unique_ptr<Def> DefRegistry::Create(std::string_view name)
	{
		for (const DefTypeInfo& info : Table)
		{
			if (info.name != name)
				continue;

			std::unique_ptr<Def> def = info.Create();
			def->type = info.type;
			return def;
		}

		return nullptr;
	}

	std::span<const DefTypeInfo> DefRegistry::All()
	{
		return Table;
	}
}

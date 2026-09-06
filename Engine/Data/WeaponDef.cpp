#include "Data/WeaponDef.h"

namespace rogue
{
	const Schema& WeaponDef::StaticSchema()
	{
		//inherit parent schema; i.e. WeaponDef inherits fields from ItemDef; similar to a parent-child class
		static const Schema schema = SchemaBuilder<WeaponDef>("WeaponDef", &ItemDef::StaticSchema())
										 .Field("damage", &WeaponDef::damage)
										 .Field("reach", &WeaponDef::reach)
										 .Field("damageType", &WeaponDef::damageType)
										 .Build();

		return schema;
	}
}

#include "Data/ArmorDef.h"

namespace rogue
{
	const Schema& ArmorDef::StaticSchema()
	{
		static const Schema schema = SchemaBuilder<ArmorDef>("ArmorDef", &ItemDef::StaticSchema())
										 .Field("armorRating", &ArmorDef::armorRating)
										 .Field("armorType", &ArmorDef::armorType)
										 .Build();

		return schema;
	}
}

#include "Data/ArmorDef.h"

namespace rogue
{
	const Schema& ArmorDef::StaticSchema()
	{
		static const Schema schema = SchemaBuilder<ArmorDef>("ArmorDef", &ItemDef::StaticSchema())
										 .Field("armorRating", &ArmorDef::armorRating)
										 .EnumField("armorType", &ArmorDef::armorType, ArmorTypeNames)
										 .Build();

		return schema;
	}
}

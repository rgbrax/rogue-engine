#include "Data/ArmorDef.h"

namespace rogue
{
	const Schema& ArmorDef::StaticSchema( )
	{
		static const Schema schema = SchemaBuilder<ArmorDef>("ArmorDef", &ItemDef::StaticSchema())
			.Field("armorRating", &ArmorDef::armorRating)
			.Field("type", &ArmorDef::type)
			.Build();

		return schema;
	}
}

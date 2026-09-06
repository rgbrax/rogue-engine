#include "Data/ItemDef.h"

namespace rogue
{
	const Schema& ItemDef::StaticSchema()
	{
		static const Schema schema = SchemaBuilder<ItemDef>("ItemDef")
										 .Field("displayName", &ItemDef::displayName)
										 .Field("weight", &ItemDef::weight)
										 .Field("value", &ItemDef::value)
										 .Build();

		return schema;
	}
}

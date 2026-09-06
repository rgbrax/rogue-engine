#include "ConsumableDef.h"

namespace rogue
{
	const Schema& ConsumableDef::StaticSchema()
	{
		static const Schema schema = SchemaBuilder<ConsumableDef>("ConsumableDef", &ItemDef::StaticSchema())
										 .Field("effectAmount", &ConsumableDef::effectAmount)
										 .Field("effectDuration", &ConsumableDef::effectDuration)
										 .Field("type", &ConsumableDef::type)
										 .Build();

		return schema;
	}
}

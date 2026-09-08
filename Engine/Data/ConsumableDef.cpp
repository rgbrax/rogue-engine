#include "ConsumableDef.h"

namespace rogue
{
	const Schema& ConsumableDef::StaticSchema()
	{
		static const Schema schema = SchemaBuilder<ConsumableDef>("ConsumableDef", &ItemDef::StaticSchema())
										 .Field("effectAmount", &ConsumableDef::effectAmount)
										 .Field("effectDuration", &ConsumableDef::effectDuration)
										 .EnumField("consumableType", &ConsumableDef::consumableType, ConsumableTypeNames)
										 .Build();

		return schema;
	}
}

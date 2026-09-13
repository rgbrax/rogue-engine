#include "Data/ActorDef.h"

namespace rogue
{
	const Schema& ActorDef::StaticSchema()
	{
		static const Schema schema = SchemaBuilder<ActorDef>("ActorDef", &ActorDef::StaticSchema())
										 .Field("displayName", &ActorDef::displayName)
										 .Field("health", &ActorDef::health)
										 .Field("level", &ActorDef::level)
										 .Field("isUnique", &ActorDef::isUnique)
										 .Build();
		return schema;
	}
}

#pragma once
#include "Core/Ids.h"
#include "Data/Transform.h"

#include <string>
#include <vector>

namespace rogue
{
	struct Instance
	{
		InstanceId id;
		DefId def;
		Vector2 position;
		//field overrides
	};
}

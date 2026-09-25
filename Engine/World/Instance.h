#pragma once
#include "Core/Ids.h"
#include "Core/Vector2.h"

#include <string>
#include <vector>

namespace rogue
{
	struct Instance
	{
		InstanceId id;
		DefId def;
		Vector2 position;
	};
}

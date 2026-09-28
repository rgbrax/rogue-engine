#pragma once
#include "Core/Ids.h"
#include "Core/Vector2.h"
#include "World/Component.h"

#include <string>
#include <vector>

namespace rogue
{
	struct Instance
	{
		InstanceId id;
		DefId def;
		std::vector<std::shared_ptr<Component>> components{};
		std::shared_ptr<Component> GetComponentType(ComponentType type)
		{
			for (std::shared_ptr<Component> x : components)
			{
				if (x->GetType() == type)
				{
					return x;
				}
			}

			return nullptr;
		}
	};
}

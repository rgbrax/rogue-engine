#pragma once
#include "Core/Ids.h"
#include "World/Instance.h"

#include <memory>
#include <vector>

namespace rogue
{
	//World checks the Defs, and adds the Components
	//InstanceTable is a pure container, will not process any data

	class InstanceTable
	{
	public:
		InstanceTable();
		std::shared_ptr<Instance> Create(DefId id);
		std::shared_ptr<Instance> Find(InstanceId id) const;
		const std::vector<std::shared_ptr<Instance>>& GetAll();

	private:
		std::vector<std::shared_ptr<Instance>> m_instances;
		uint64_t m_nextId = 1;
	};
}

#include "InstanceTable.h"

namespace rogue
{
	InstanceTable::InstanceTable()
	{
	}

	std::shared_ptr<Instance> InstanceTable::Create(DefId id)
	{
		std::shared_ptr<Instance> instance = std::make_shared<Instance>();
		instance->id.value = m_nextId++;
		instance->def = id;
		m_instances.push_back(instance);
		return instance;
	}

	std::shared_ptr<Instance> InstanceTable::Find(InstanceId id) const
	{
		for (auto x : m_instances)
		{
			if (x->id == id)
				return x;
		}

		return nullptr;
	}

	const std::vector<std::shared_ptr<Instance>>& InstanceTable::GetAll()
	{
		return m_instances;
	}
}

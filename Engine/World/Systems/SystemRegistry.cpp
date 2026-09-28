#include "SystemRegistry.h"

namespace rogue
{
	void SystemRegistry::Add(std::string_view name, SystemFunction func)
	{
		SystemEntry entry{};
		entry.enabled = true;
		entry.name = name;
		entry.function = func;
		m_systems.push_back(entry);
		printf("[%s] Added system %s\n", __FUNCTION__, name.data());
	}

	void SystemRegistry::Replace(std::string_view name, SystemFunction func)
	{
		for (int i = 0; i != m_systems.size(); i++)
		{
			if( m_systems[i].name == name)
				m_systems[i].function = func;
		}
	}

	void SystemRegistry::SetEnabled(std::string_view name, bool enabled)
	{
		for (int i = 0; i != m_systems.size(); i++)
		{
			if (m_systems[i].name == name)
				m_systems[i].enabled = enabled;
		}
	}

	void SystemRegistry::RunAll(World& world, float deltaTime)
	{
		for (int i = 0; i != m_systems.size(); i++)
		{
			if (!m_systems[i].enabled)
				continue;

			m_systems[i].function(world, deltaTime);
		}
	}
}
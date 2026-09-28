#pragma once
#include "InstanceTable.h"
#include "Systems/SystemRegistry.h"
#include "Data/DefTable.h"

namespace rogue
{
	class World
	{
	public:
		World();
		World(std::shared_ptr<DefTable> defTable);
		~World();
		bool IsInit();
		InstanceId Spawn(DefId defId);
		void Update(float deltaTime);
	private:
		bool m_initialized = false;
		std::shared_ptr<InstanceTable> m_instanceTable = nullptr;
		std::shared_ptr<DefTable> m_defTable = nullptr;
		std::shared_ptr<SystemRegistry> m_systemRegistry = nullptr;
	};
}
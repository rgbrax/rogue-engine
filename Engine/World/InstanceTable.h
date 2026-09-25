#pragma once
#include "Data/DefTable.h"
#include "Instance.h"

#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace rogue
{
	//tbd: maybe rename Instance to GameObject, Object, Reference/Ref?

	class InstanceTable
	{
	public:
		InstanceTable();
		bool CreateInstanceFromDef(DefId id);
		bool CreateInstanceFromEditorId(std::string_view editorId);
		Instance* GetInstanceFromId(InstanceId id);
		const std::vector<std::shared_ptr<Instance>>& GetInstances();

	private:
		std::vector<std::shared_ptr<Instance>> m_instances;
	};
}

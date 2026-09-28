#include "InstanceTable.h"
#include "Data/DefTable.h"
#include "Data/Defs/ActorDef.h"
#include "Data/Defs/ArmorDef.h"
#include "Data/Defs/ConsumableDef.h"
#include "Data/Defs/ItemDef.h"
#include "Data/Defs/WeaponDef.h"

namespace rogue
{
	InstanceTable::InstanceTable()
	{
	}

	bool InstanceTable::AddInstance(Instance* instance)
	{
		if (!instance)
			return false;

		instance->id = InstanceId(m_instances.size() + 1);
		m_instances.push_back(std::unique_ptr<Instance>(instance));
	}

	bool InstanceTable::CreateInstanceFromDef(DefId id)
	{
		Instance* instance = new Instance();
		instance->def = id;
		return AddInstance(instance);
	}

	bool InstanceTable::CreateInstanceFromEditorId(std::string_view editorId)
	{
		/*Def* def = g_defTable.GetDefByEditorId(editorId);
		if (!def)
			return false;

		Instance* instance = new Instance();
		instance->def = def->id;
		return AddInstance(instance);*/
		return false;
	}

	std::shared_ptr<Instance> InstanceTable::GetInstanceFromId(InstanceId id)
	{
		for (std::shared_ptr<Instance> x : m_instances)
		{
			if (x->id == id)
				return x;
		}

		return std::shared_ptr<Instance>();
	}

	const std::vector<std::shared_ptr<Instance>>& InstanceTable::GetInstances()
	{
		return m_instances;
	}
}

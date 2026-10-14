#include "World.h"
#include "World/Component.h"
#include "World/Components/CombatControllerComponent.h"
#include "World/Components/HealthComponent.h"
#include "World/Components/PlayerControlComponent.h"
#include "World/Components/TransformComponent.h"
#include "World/Components/VelocityComponent.h"
#include "World/Systems/Systems.h"

namespace rogue
{
	World::World()
	{
		printf("__World null setup\n");
	}

	World::World(std::shared_ptr<DefTable> defTable)
		: m_defTable(defTable)
	{
		m_instanceTable = std::make_shared<InstanceTable>();
		m_systemRegistry = std::make_shared<SystemRegistry>();

		if (m_instanceTable != nullptr
			&& m_systemRegistry != nullptr
			&& m_defTable != nullptr)
		{
			m_initialized = true;
		}
		else
			return;

		printf("__World setup: tables created\n");

		m_systemRegistry->Add("PlayerControl", UpdatePlayerControl);
		m_systemRegistry->Add("Movement", UpdateMovement);
		m_systemRegistry->Add("Combat", UpdateCombat);
		printf("__World setup: systems registered\n");

		printf("__World setup: %i\n", (int)m_initialized);
	}

	World::~World()
	{
		printf("__World destroy\n");
	}

	bool World::IsInit()
	{
		if (!m_initialized
			|| !m_defTable
			|| !m_instanceTable)
			return false;

		return true;
	}

	InstanceId World::Spawn(DefId defId)
	{
		Def* def = m_defTable->GetDefById(defId);
		if (!def)
		{
			printf("World::Spawn: DefId not found!\n");
			return InstanceId();
		}

		std::shared_ptr<Instance> instance = m_instanceTable->Create( def->id );
		instance->Add<TransformComponent>( ).pos = Vector2( 0.0f, 0.0f );

		if(def->type == DefType::Actor)
		{
			instance->Add<CombatControllerComponent>( );
			instance->Add<HealthComponent>( );
			instance->Add<VelocityComponent>( );

			HealthComponent* health = instance->Get<HealthComponent>( );
			health->healthMax = actor

			//first instance should be the player
			if (instance->id.value == 1)
			{
				instance->Add<PlayerControlComponent>( );
			}
		}
		else if( def->type == DefType::Armor)
		{ 
		}
		else if (def->type == DefType::Consumable)
		{
		}
		else if (def->type == DefType::Weapon)
		{
		}

		if (def->type == DefType::Invalid || def->type == DefType::Count)
			return InstanceId();

		std::shared_ptr<Instance> instance = m_instanceTable->Create(def->id);
		instance->Add( TransformComponent );
		instance->components.push_back(std::make_shared<TransformComponent>());

		if (def->type == DefType::Actor)
		{
			instance->components.push_back(std::make_shared<CombatControllerComponent>());
			instance->components.push_back(std::make_shared<HealthComponent>());
			instance->components.push_back(std::make_shared<TransformComponent>());
			instance->components.push_back(std::make_shared<VelocityComponent>());

			//first instance should be the player
			if (instance->id.value == 1)
			{
				instance->components.push_back(std::make_shared<PlayerControlComponent>());
			}
		}
		else if( def->type == DefType::Armor)
		{ 
		}
		else if (def->type == DefType::Consumable)
		{

		}
		else if (def->type == DefType::Weapon)
		{

		}

		printf("World::Spawn InstanceId created: %i\n", (int)instance->id.value);
		return instance->id;
	}

	void World::Update(float deltaTime)
	{
		m_systemRegistry->RunAll(*this, deltaTime);
	}

	std::shared_ptr<InstanceTable> World::GetInstanceTable( ) const
	{
		return m_instanceTable;
	}

	std::shared_ptr<DefTable> World::GetDefTable( ) const
	{
		return m_defTable;
	}
}
#include "Systems.h"

//temp all
#include "World/Components/CombatControllerComponent.h"
#include "World/Components/HealthComponent.h"
#include "World/Components/TransformComponent.h"
#include "World/Components/VelocityComponent.h"
#include "World/Components/PlayerControlComponent.h"

namespace rogue
{
	void UpdateCombat(World& world, float deltaTime)
	{
		for ( std::shared_ptr<Instance> instance : world.GetInstanceTable( )->GetAll( ) )
		{
						
		}
	}
}
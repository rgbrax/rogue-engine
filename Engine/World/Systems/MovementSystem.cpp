#include "Systems.h"

//temp all
#include "World/Components/CombatControllerComponent.h"
#include "World/Components/HealthComponent.h"
#include "World/Components/TransformComponent.h"
#include "World/Components/VelocityComponent.h"
#include "World/Components/PlayerControlComponent.h"

namespace rogue
{
	void UpdateMovement(World& world, float deltaTime)
	{
		for ( std::shared_ptr<Instance> instance : world.GetInstanceTable( )->GetAll( ) )
		{
			TransformComponent* transform = nullptr;

			printf( "Instance: %i\n", ( int )instance->id.value );
			if ( instance->Has<TransformComponent>( ) )
			{
				printf( "--> Has Transform\n" );
				transform = instance->Get<TransformComponent>( );
				printf( "X: %f | Y: %f\n", transform->pos.x, transform->pos.y );
			}


			//movement
			if ( instance->Has<PlayerControlComponent>( ) )
			{
				if ( !transform )
					continue;

				PlayerControlComponent* playerControl = instance->Get<PlayerControlComponent>( );
				if ( playerControl->left )
					transform->pos.x -= 1.0f * deltaTime;
				if ( playerControl->right )
					transform->pos.x += 1.0f * deltaTime;
				if ( playerControl->up )
					transform->pos.y -= 1.0f * deltaTime;
				if ( playerControl->down )
					transform->pos.y += 1.0f * deltaTime;
			}
		}
	}
}
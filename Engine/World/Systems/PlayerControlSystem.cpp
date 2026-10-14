#include "Systems.h"
#include <cstdio>

#include <Windows.h>

//temp all
#include "World/Components/CombatControllerComponent.h"
#include "World/Components/HealthComponent.h"
#include "World/Components/TransformComponent.h"
#include "World/Components/VelocityComponent.h"
#include "World/Components/PlayerControlComponent.h"

namespace rogue
{
	void UpdatePlayerControl(World& world, float deltaTime)
	{
		for ( std::shared_ptr<Instance> instance : world.GetInstanceTable( )->GetAll( ) )
		{
			if ( instance->Has<PlayerControlComponent>() )
			{
				printf( "PlayerController found, instance id: %i\n", ( int )instance->id.value );
				PlayerControlComponent* playerControl = instance->Get<PlayerControlComponent>();
				playerControl->left = GetAsyncKeyState(VK_LEFT) != 0;
				playerControl->right = GetAsyncKeyState(VK_RIGHT) != 0;
				playerControl->up = GetAsyncKeyState(VK_UP) != 0;
				playerControl->down = GetAsyncKeyState(VK_DOWN) != 0;
			}
		}

		if ( GetAsyncKeyState( VK_LEFT ) )
		{
			
		}
	}
}
#pragma once
#include "World/Component.h"

namespace rogue
{
	struct HealthComponent : public Component
	{
		static constexpr ComponentType Type = ComponentType::Health;

		HealthComponent()
			: Component( Type )
		{ }

		int32_t health = 0;
		int32_t healthMax = 0;

		void Clamp( )
		{
			if ( health < 0 )
				health = 0;
			if ( health > healthMax )
				health = healthMax;
		}

		void Hurt( int32_t amount )
		{
			if ( amount >= health )
				health = 0;
			else
				health -= amount;
		}

		void Heal( int32_t amount )
		{
			if ( health + amount >= healthMax )
				health = healthMax;
			else
				health += amount;
		}

		bool IsDead( ) const
		{
			return health <= 0;
		}

		bool IsAlive( ) const
		{
			return health > 0;
		}

		bool IsFullHealth( ) const
		{
			return health == healthMax;
		}
	};
}
#pragma once
#include <cstdint>

namespace rogue
{
	//do we even need this anymore? TBD
	enum class ComponentType : uint8_t
	{
		None,
		CombatController,
		Health,
		PlayerControl,
		Transform,
		Velocity,
	};

	class Component
	{
	public:
		explicit Component( ComponentType type )
			: m_type( type )
		{ }

		virtual ~Component( ) = default;

		ComponentType GetType( ) const
		{
			return m_type;
		}

	private:
		ComponentType m_type = ComponentType::None;
	};
}
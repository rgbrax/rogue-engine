#pragma once
#include "Core/Ids.h"
#include "World/Component.h"

#include <vector>
#include <memory>

namespace rogue
{
	struct Instance
	{
		InstanceId id;
		DefId def;
		std::vector<std::unique_ptr<Component>> components;

		template <typename T>
		T* Get( )
		{
			for ( std::unique_ptr<Component>& component : components )
			{
				if ( component->GetType( ) == T::Type )
					return static_cast< T* >( component.get( ) );
			}

			return nullptr;
		}

		template <typename T>
		bool Has( )
		{
			return Get<T>( ) != nullptr;
		}

		template <typename T>
		T& Add( )
		{
			if ( T* existing = Get<T>( ) )
				return *existing;

			components.push_back( std::make_unique<T>( ) );
			return static_cast< T& >( *components.back( ) );
		}
	};
}

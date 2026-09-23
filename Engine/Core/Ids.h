#pragma once
#include <cstdint>
#include <compare>

namespace rogue
{
	struct DefId
	{
		uint64_t value = 0;
		constexpr bool IsValid() const
		{
			return value != 0;
		}
		constexpr auto operator<=>(const DefId&) const = default;
	};

	struct ModuleId
	{
		uint8_t value = 0;
		constexpr bool IsValid() const
		{
			return value != 0;
		}
		constexpr auto operator<=>(const ModuleId&) const = default;
	};

	struct InstanceId
	{
		uint64_t value = 0;
		constexpr bool IsValid() const
		{
			return value != 0;
		}
		constexpr auto operator<=>(const InstanceId&) const = default;
	};
}

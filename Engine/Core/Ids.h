#pragma once
#include <cstdint>
#include <functional>

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
		uint16_t value = 0;
		constexpr bool IsValid() const
		{
			return value != 0;
		}
		constexpr auto operator<=>(const ModuleId&) const = default;
	};
}

//hashing
template <>
struct std::hash<rogue::DefId>
{
	size_t operator()(const rogue::DefId& id) const noexcept
	{
		return std::hash<uint64_t>{}(id.value);
	}
};

template <>
struct std::hash<rogue::ModuleId>
{
	size_t operator()(const rogue::ModuleId& id) const noexcept
	{
		return std::hash<uint64_t>{}(id.value);
	}
};

#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace rogue
{
	class World;
	using SystemFunction = void (*)(World&, float);

	struct SystemEntry
	{
		std::string name;
		SystemFunction function = nullptr;
		bool enabled = true;
	};

	class SystemRegistry
	{
	public:
		void Add(std::string_view name, SystemFunction func);
		void Replace(std::string_view name, SystemFunction func);
		void SetEnabled(std::string_view name, bool enabled);
		void RunAll(World& world, float deltaTime);
	private:
		std::vector<SystemEntry> m_systems;
	};
}
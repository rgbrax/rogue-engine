#pragma once
#include <functional>
#include <string>

namespace rogue
{
	struct Command
	{
		std::string cmd = "";
		int argsMin = 0;
		std::function<void(const std::vector<std::string>&)> func{};
	};
}

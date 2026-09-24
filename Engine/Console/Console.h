#pragma once
#include "Command.h"

#include <unordered_map>

namespace rogue
{
	class Console
	{
	public:
		bool Run(std::string_view command, const std::vector<std::string>& params);
		bool Setup();
		void RegisterCommand(std::function<void(const std::vector<std::string>&)> func, int argsMin, std::string_view funcName);

	private:
		std::unordered_map<std::string, Command*> m_commands;
	};
}

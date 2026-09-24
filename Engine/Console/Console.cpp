#include "Console.h"
#include "Commands.h"

namespace rogue
{
	bool Console::Setup()
	{
		RegisterCommand(MsgBox, 2, "MsgBox");
		RegisterCommand(Print, 1, "Print");
		return true;
	}

	bool Console::Run(std::string_view commandName, const std::vector<std::string>& params)
	{
		auto it = m_commands.find(std::string(commandName));
		if (it == m_commands.end())
		{
			printf("Error: failed to get command : %s\n", commandName.data());
			return false;
		}

		Command* command = it->second;
		if (params.size() < command->argsMin)
		{
			if ((int)params.size() < command->argsMin)
			{
				printf("Error: %s needs at least %i args, got %zu\n", command->cmd.c_str(), command->argsMin, params.size());
				return false;
			}
		}

		command->func(params);
		return true;
	}

	void Console::RegisterCommand(std::function<void(const std::vector<std::string>&)> func, int argsMin, std::string_view funcName)
	{
		Command* command = new Command();
		command->argsMin = argsMin;
		command->func = func;
		command->cmd = funcName;
		m_commands[command->cmd] = command;
	}
}

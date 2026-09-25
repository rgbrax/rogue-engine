#include "Commands.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace sandbox
{
	void Run()
	{
		console->Setup();
		console->RegisterCommand(commands::RunWindow, 0, "RunWindow");
		console->RegisterCommand(commands::SaveDefs, 1, "SaveDefs");
		console->RegisterCommand(commands::LoadDefs, 1, "LoadDefs");
		console->RegisterCommand(commands::CreateDefs, 0, "CreateDefs");
		console->RegisterCommand(commands::ClearDefs, 0, "ClearDefs");
		console->RegisterCommand(commands::PrintDefs, 0, "PrintDefs");
		console->RegisterCommand(commands::GetDefCount, 0, "GetDefCount");
		console->RegisterCommand(commands::DeleteDefId, 1, "DeleteDefId");
		console->RegisterCommand(commands::DeleteDefName, 1, "DeleteDefName");
		console->RegisterCommand(commands::Print, 1, "Print");
		console->RegisterCommand(commands::MsgBox, 2, "MsgBox");
		console->RegisterCommand(commands::CreateWeaponDef, 7, "CreateWeaponDef");
		console->RegisterCommand(commands::GetDef, 1, "GetDef");

		while (true)
		{
			std::string line;
			printf("Console> ");
			std::getline(std::cin, line);
			std::stringstream ss(line);

			std::string cmd;
			std::vector<std::string> params;

			std::string word;
			while (ss >> word)
			{
				if (cmd.empty())
					cmd = word;
				else
					params.push_back(word);
			}

			console->Run(cmd, params);
		}
	}
}

int main(int argc, const char* argv[])
{
	printf("START\n");
	sandbox::Run();
	printf("END");
	return 0;
}

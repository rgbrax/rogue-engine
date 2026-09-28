#include "Game.h"

#include <cstdio>
#include <iostream>
#include <sstream>

namespace game
{
	void Setup()
	{
		World = std::make_shared<rogue::World>(game::DefTable);

		Console->Setup();
		Console->RegisterCommand(commands::RunWindow, 0, "RunWindow");
		Console->RegisterCommand(commands::RunRenderer, 0, "RunRenderer");
		Console->RegisterCommand(commands::SaveDefs, 1, "SaveDefs");
		Console->RegisterCommand(commands::LoadDefs, 1, "LoadDefs");
		Console->RegisterCommand(commands::CreateDefs, 0, "CreateDefs");
		Console->RegisterCommand(commands::ClearDefs, 0, "ClearDefs");
		Console->RegisterCommand(commands::PrintDefs, 0, "PrintDefs");
		Console->RegisterCommand(commands::GetDefCount, 0, "GetDefCount");
		Console->RegisterCommand(commands::DeleteDefId, 1, "DeleteDefId");
		Console->RegisterCommand(commands::DeleteDefName, 1, "DeleteDefName");
		Console->RegisterCommand(commands::CreateWeaponDef, 7, "CreateWeaponDef");
		Console->RegisterCommand(commands::GetDef, 1, "GetDef");
		Console->RegisterCommand(commands::WorldSpawn, 1, "WorldSpawn");
		Console->RegisterCommand(commands::WorldUpdate, 0, "WorldUpdate");
		printf("Setup: commands registered\n");
		printf("Setup: world.IsInit = %i\n", (int)World->IsInit());
		printf("Setup: completed\n");
	}

	void Run()
	{
		//run console for now
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

			Console->Run(cmd, params);
		}
	}
}
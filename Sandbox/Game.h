#pragma once
#include "Data/DefTable.h"
#include "World/World.h"
#include "Console/Console.h"

namespace game
{
	inline std::shared_ptr<rogue::Console> Console = std::make_shared<rogue::Console>();
	inline std::shared_ptr<rogue::DefTable> DefTable = std::make_shared<rogue::DefTable>();
	inline std::shared_ptr<rogue::World> World = std::make_shared<rogue::World>();

	namespace commands
	{
		//void Print(const std::vector<std::string>& params);
		void RunWindow(const std::vector<std::string>& params);
		void RunRenderer(const std::vector<std::string>& params);
		void WorldUpdate(const std::vector<std::string>& params);
		void WorldSpawn(const std::vector<std::string>& params);
		void SaveDefs(const std::vector<std::string>& params);
		void LoadDefs(const std::vector<std::string>& params);
		void PrintDefs(const std::vector<std::string>& params);
		void ClearDefs(const std::vector<std::string>& params);
		void CreateDefs(const std::vector<std::string>& params); //creates sample defs
		void CreateWeaponDef(const std::vector<std::string>& params); //EditorId, DisplayName, IsUnique, Range, Value, Weight, Damage
		void GetDef(const std::vector<std::string>& params);
		void GetDefCount(const std::vector<std::string>& params);
		void DeleteDefId(const std::vector<std::string>& params);
		void DeleteDefName(const std::vector<std::string>& params);
	}

	namespace windowui
	{
		void Run();
	}

	void Setup();
	void Run();
}
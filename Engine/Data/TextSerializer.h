#pragma once
#include "Data/Def.h"
#include "Data/DefTable.h"

#include <string>
#include <string_view>

namespace rogue
{
	class TextSerializer
	{
	public:
		static std::string Write(const Def& def); //write all fields
		static std::string WriteAll(const DefTable& table); //write all defs		
		static bool ReadAll(std::string_view text, DefTable& outTable, std::string* outError = nullptr); //constructed by DefRegistry, then fills fields by name
	};
}

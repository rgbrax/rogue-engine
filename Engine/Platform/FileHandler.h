#pragma once
#include <string>
#include <string_view>
#include <vector>

/*
/Platform/
->	Still determining what the folder structure should be
	but for now, this will go here.
*/

namespace rogue
{
	namespace files
	{
		//no members or oop, so changed this to a namespace
		//idk there's a StyleGuide laying around here somewhere; I swear I have standards

		std::string ReadFileText(std::string_view filePath);
		std::vector<std::string> ReadFileLines(std::string_view filePath);
		bool WriteFileText(std::string_view filePath, std::string_view fileData);
		bool WriteFileLines(std::string_view filePath, const std::vector<std::string>& fileLines);
	}
}

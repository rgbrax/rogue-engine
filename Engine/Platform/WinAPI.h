#pragma once
#include <string>
#include <vector>

/*
/Platform/
->	Still determining what the folder structure should be
	but for now, this will go here.

	This winapi wrapper will have funcs split up later.
*/

namespace rogue
{
	class WinAPI
	{
	public:
		std::string ReadFileText(std::string_view filePath);
		std::vector<std::string> ReadFileLines(std::string_view filePath);
		bool WriteFileText(std::string_view filePath, std::string_view fileData);
		bool WriteFileLines(std::string_view filePath, const std::vector<std::string>& fileLines);

	private:
	};
}

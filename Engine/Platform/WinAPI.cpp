#include "WinAPI.h"
#include <Windows.h>

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <memory>
#include <ostream>
#include <print>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace rogue
{
	std::string WinAPI::ReadFileText(std::string_view filePath)
	{
		if (filePath.empty())
			return std::string();

		std::ifstream file(filePath.data());
		std::stringstream ss;
		ss << file.rdbuf();
		return ss.str();
	}

	std::vector<std::string> WinAPI::ReadFileLines(std::string_view filePath)
	{
		if (filePath.empty())
			return std::vector<std::string>();

		std::ifstream file(filePath.data());
		std::vector<std::string> ret;
		std::string line;
		while (std::getline(file, line))
		{
			ret.push_back(line);
		}

		return ret;
	}

	bool WinAPI::WriteFileText(std::string_view filePath, std::string_view fileData)
	{
		if (filePath.empty() || fileData.empty())
			return false;

		std::ofstream file(filePath.data());
		file << fileData;

		return true;
	}

	bool WinAPI::WriteFileLines(std::string_view filePath, const std::vector<std::string>& fileLines)
	{
		if (filePath.empty() || fileLines.empty())
			return false;

		std::ofstream file(filePath.data());
		for (const std::string& s : fileLines)
		{
			file << s << "\n";
		}

		return true;
	}
}

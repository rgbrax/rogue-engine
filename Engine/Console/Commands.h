#pragma once
#include <Windows.h>

namespace rogue
{
	void Print(const std::vector<std::string>& params)
	{
		std::string output = "";
		for (std::string s : params)
		{
			output += (s + " ");
		}

		printf("print: %s\n", output.c_str());
	}

	void MsgBox(const std::vector<std::string>& params)
	{
		MessageBoxA(0, params[0].c_str(), params[1].c_str(), 0);
	}
}

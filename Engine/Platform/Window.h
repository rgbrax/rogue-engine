#pragma once
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

#include <Windows.h>

namespace rogue
{
	enum class ControlType : int
	{
		None,
		Label, //"TEXT"
		Edit, //"EDIT"
		Button, //"BUTTON"
		ListBox, //"LISTBOX"
		ComboBox, //"COMBOBOX"
		ScrollBar, //"SCROLLBAR"
		Count
	};

	const char* ControlList[7] = {"", "TEXT", "EDIT", "BUTTON", "LISTBOX", "COMBOBOX", "SCROLLBAR"};

	struct Control
	{
		HWND handle = nullptr;
		std::string txt = "";
		std::string title = "";
		int id = 0;
		ControlType type = ControlType::None;
		int posX = 0;
		int posY = 0;
		int sizeX = 0;
		int sizeY = 0;
	};

	class Window
	{
	public:
		Window();
		Window(std::string_view title, std::string_view className);
		void Run();
		bool Setup();
		bool AddControl(ControlType type, std::string_view name, std::string_view text, int sizeX, int sizeY);
		std::string GetControlText(std::string_view name);
		void SetControlText(std::string_view name);
		Control* GetControlByName(std::string_view name);

	private:
		HWND m_window = nullptr;
		std::string m_windowTitle = "";
		std::string m_windowClassName = "";
		RECT m_rect{};
		std::vector<Control*> m_controls{};
		static LRESULT CALLBACK WinProcThunk(HWND window, UINT msg, WPARAM wparam, LPARAM lparam);
	};
}

#pragma once
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <functional>
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
	namespace window
	{
		//WinAPI manual window and control creation
		//this is the beginning of a wrapper, it is not pretty right now
		//Will improve as it continues, but this certainly proves the concept

		enum class ControlType : int
		{
			None,
			Label, //"STATIC"
			Edit, //"EDIT"
			Button, //"BUTTON"
			ListBox, //"LISTBOX"
			ComboBox, //"COMBOBOX"
			ScrollBar, //"SCROLLBAR"
			Count
		};

		const char* ControlList[7] = {"", "STATIC", "EDIT", "BUTTON", "LISTBOX", "COMBOBOX", "SCROLLBAR"};

		struct Control
		{
			HWND handle = nullptr;
			std::string txt = "";
			std::string name = "";
			int id = 0;
			ControlType type = ControlType::None;
			int posX = 0;
			int posY = 0;
			int sizeX = 0;
			int sizeY = 0;
		};

		struct ControlFunction
		{
			std::string controlName = "";
			std::function<void()> func;
		};

		HWND m_window = nullptr;
		std::string m_windowTitle = "";
		std::string m_windowClassName = "";
		RECT m_rect{};
		std::vector<Control*> m_controls{};
		std::vector<ControlFunction*> m_controlFunctions{};

		void Run();
		bool Setup();
		bool AddControl(ControlType type, std::string_view name, std::string_view text, int sizeX, int sizeY);
		bool AddControlFunction(std::string_view controlName, std::function<void()> func);
		std::string GetControlText(std::string_view name);
		void SetControlText(std::string_view name);
		Control* GetControlByName(std::string_view name);
		Control* GetControlById(uint8_t id);
		void RunControlFunctions(std::string_view name);
		LRESULT CALLBACK WinProcThunk(HWND window, UINT msg, WPARAM wparam, LPARAM lparam);

		std::string GetTypeString(ControlType type)
		{
			int iPos = (int)type;
			return std::string(ControlList[iPos]);
		}

		void Run()
		{
			Setup();
		}

		bool Setup()
		{
			WNDCLASSEXA winClass{};
			winClass.cbSize = sizeof(WNDCLASSEXA);
			winClass.lpfnWndProc = &WinProcThunk;
			winClass.lpszClassName = m_windowClassName.c_str();
			winClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
			winClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);

			if (!RegisterClassExA(&winClass))
			{
				printf("[%s] error: failed to register class\n", __FUNCTION__);
				return false;
			}

			m_window = CreateWindowExA(0, m_windowClassName.c_str(), m_windowTitle.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, 0, 0, 0, 0);
			if (!m_window)
			{
				printf("[%s] error: failed to create window\n", __FUNCTION__);
				return false;
			}

			ShowWindow(m_window, SW_SHOW);
			UpdateWindow(m_window);

			MSG msg{};
			while (GetMessageA(&msg, nullptr, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}

			return true;
		}

		bool AddControl(ControlType type, std::string_view name, std::string_view text, int sizeX, int sizeY)
		{
			if (type == ControlType::None || type == ControlType::Count || name.empty())
				return false;

			static int currentX = 10;
			static int currentY = 10;
			static int idCounter = 101;

			Control* control = new Control();
			control->sizeX = sizeX;
			control->sizeY = sizeY;
			control->type = type;
			control->name = name;
			control->txt = text;
			control->id = idCounter;
			control->posX = currentX;
			control->posY = currentY;
			m_controls.push_back(control);

			currentY += control->sizeY + 5;
			idCounter++;
			return true;
		}

		bool AddControlFunction(std::string_view controlName, std::function<void()> funcPtr)
		{
			if (controlName.empty() || !funcPtr)
				return false;

			ControlFunction* func = new ControlFunction();
			func->controlName = controlName;
			func->func = funcPtr;
			m_controlFunctions.push_back(func);
		}

		std::string GetControlText(std::string_view name)
		{
			if (name.empty())
				return std::string();

			for (Control* control : m_controls)
			{
				if (control->name == name)
				{
					char msg[256] = "";
					GetWindowTextA(control->handle, msg, 256);
					return std::string(msg);
				}
			}

			return std::string();
		}

		void SetControlText(std::string_view name)
		{
			if (name.empty())
				return;

			for (Control* control : m_controls)
			{
				if (control->name == name)
				{
					SetWindowTextA(control->handle, name.data());
				}
			}
		}

		Control* GetControlByName(std::string_view name)
		{
			for (Control* control : m_controls)
			{
				if (control->name == name)
					return control;
			}

			return nullptr;
		}

		Control* GetControlById(uint8_t id)
		{
			for (Control* control : m_controls)
			{
				if (control->id == id)
					return control;
			}

			return nullptr;
		}

		void RunControlFunctions(std::string_view name)
		{
			for (ControlFunction* cFunc : m_controlFunctions)
			{
				if (cFunc->controlName == name)
					cFunc->func();
			}
		}

		LRESULT WinProcThunk(HWND window, UINT msg, WPARAM wparam, LPARAM lparam)
		{
			if (msg == WM_CREATE)
			{
				for (Control* control : m_controls)
				{
					if (!control->id || control->name.empty() || control->type == ControlType::None || control->type == ControlType::Count)
						continue;

					std::string typeStr = GetTypeString(control->type);
					if (typeStr.empty())
						continue;

					if (control->type == ControlType::Button)
					{
						control->handle = CreateWindowA(typeStr.c_str(), control->txt.c_str(), WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, control->posX, control->posY, control->sizeX, control->sizeY, window, reinterpret_cast<HMENU>(control->id), 0, 0);
					}
					else if (control->type == ControlType::ComboBox)
					{
					}
					else if (control->type == ControlType::Edit)
					{
						control->handle = CreateWindowA(typeStr.c_str(), control->txt.c_str(), WS_VISIBLE | WS_CHILD | WS_BORDER | CBS_AUTOHSCROLL, control->posX, control->posY, control->sizeX, control->sizeY, window, reinterpret_cast<HMENU>(control->id), 0, 0);
					}
					else if (control->type == ControlType::Label)
					{
						control->handle = CreateWindowA(typeStr.c_str(), control->txt.c_str(), WS_VISIBLE | WS_CHILD, control->posX, control->posY, control->sizeX, control->sizeY, window, reinterpret_cast<HMENU>(control->id), 0, 0);
					}
					else if (control->type == ControlType::ListBox)
					{
					}
					else if (control->type == ControlType::ScrollBar)
					{
					}
					else
					{
						continue;
					}
				}
			}
			else if (msg == WM_PAINT)
			{
			}
			else if (msg == WM_DESTROY)
			{
			}
			else if (msg == WM_COMMAND)
			{
				Control* control = GetControlById(LOWORD(wparam));

				if (control != nullptr && control->type == ControlType::Button && HIWORD(wparam) == BN_CLICKED)
					RunControlFunctions(control->name);
			}
			else
			{
				//unhandled
			}

			return DefWindowProcA(window, msg, wparam, lparam);
		}
	}
}

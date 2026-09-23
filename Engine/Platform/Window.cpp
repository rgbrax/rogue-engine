#include "Window.h"

namespace rogue
{
	Window::Window()
	{
	}

	Window::Window(std::string_view title, std::string_view className)
	{
	}

	void Window::Run()
	{
	}

	bool Window::Setup()
	{
		WNDCLASSEXA winClass{};
		winClass.cbSize = sizeof(WNDCLASSEXA);
		winClass.lpfnWndProc = (LRESULT)WinProc;
		winClass.lpszClassName = m_windowClassName.c_str();
		winClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		winClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);

		if (!RegisterClassExA(&winClass))
		{
			printf("[%s] error: failed to register class\n", __FUNCTION__);
			return false;
		}

		HWND winHandle = CreateWindowExA(0, m_windowClassName.c_str(), m_windowTitle.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, 0, 0, 0, 0);
		if (!winHandle)
		{
			printf("[%s] error: failed to create window\n", __FUNCTION__);
			return false;
		}

		ShowWindow(winHandle, SW_SHOW);
		UpdateWindow(winHandle);

		MSG msg{};
		while (GetMessageA(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}

		return true;
	}

	bool Window::AddControl(ControlType type, std::string_view name, std::string_view text, int sizeX, int sizeY)
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
		control->title = name;
		control->txt = text;
		control->id = idCounter;

		//calc size
		currentX += control->sizeX + 5;
		//currentY += control->sizeY + 5;

		control->posX = currentX;
		control->posY = currentY;

		m_controls.push_back(control);
		idCounter++;

		return true;
	}

	std::string Window::GetControlText(std::string_view name)
	{
		if (name.empty())
			return std::string();

		for (Control* control : m_controls)
		{
			if (control->title == name)
			{
				char msg[256] = "";
				GetWindowTextA(control->handle, msg, 256);
				return std::string(msg);
			}
		}

		return std::string();
	}

	void Window::SetControlText(std::string_view name)
	{
		if (name.empty())
			return;

		for (Control* control : m_controls)
		{
			if (control->title == name)
			{
				SetWindowTextA(control->handle, name.data());
			}
		}
	}

	Control* Window::GetControlByName(std::string_view name)
	{
		for (Control* control : m_controls)
		{
			if (control->title == name)
				return control;
		}

		return nullptr;
	}

	std::string GetTypeString(ControlType type)
	{
		int iPos = (int)type;
		return std::string(ControlList[iPos]);
	}

	LRESULT Window::WinProc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_CREATE)
		{
			for (Control* control : m_controls)
			{
				if (!control->id || control->title.empty() || control->type == ControlType::None || control->type == ControlType::Count)
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
			for (Control* control : m_controls)
			{
				if (control->type == ControlType::Button)
				{
					if (LOWORD(wparam) == control->id && HIWORD(wparam) == BN_CLICKED)
					{
						if (control->title == "btn_msg")
						{
							MessageBoxA(m_window, "TEST", "NOTICE", 0);
						}
						else if (control->title == "btn_log")
						{
							std::string input = this->GetControlText("txt_input_log");
							printf("Log input: %s\n", input.c_str());
						}
					}
				}
			}
		}
		else
		{
			//unhandled
		}

		return DefWindowProcA(window, msg, wparam, lparam);
	}
}

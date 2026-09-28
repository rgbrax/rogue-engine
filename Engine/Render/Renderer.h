#pragma once
#include <SDL3/SDL.h>

#include <memory>
#include <string>

namespace rogue
{
	class Renderer
	{
	public:
		bool SetupWindow();

	private:
		std::string m_windowTitle = "REngine";
		std::string m_windowClassName = "REngineClass";
		int m_sizeX = 600;
		int m_sizeY = 400;
		std::shared_ptr<SDL_Renderer> m_renderer = nullptr;
		std::shared_ptr<SDL_Window> m_window = nullptr;
	};
}
#include "Engine.h"
#include <SDL3/SDL.h>
#include <cstdio>

int main()
{
	std::printf("rogue engine %s\n", rogue::GetVersion());

	const int sdl = SDL_GetVersion();
	std::printf("SDL %d.%d.%d\n", SDL_VERSIONNUM_MAJOR(sdl), SDL_VERSIONNUM_MINOR(sdl), SDL_VERSIONNUM_MICRO(sdl));
	return 0;
}

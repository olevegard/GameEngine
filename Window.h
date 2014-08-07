#pragma once

#include "Rect.h"

class Window
{
	public:
	bool InitSDL()
	{
		if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
		{
			std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	}
	bool CreateWindow( Rect windowRect )
	{
		InitSDL();

		window = SDL_CreateWindow( "Server", windowRect.x, windowRect.y, windowRect.w, windowRect.h, 0 );

		if ( window == nullptr )
		{
			std::cout << "Failed to create window : " << SDL_GetError();
			return false;
		}

		return true;
	}
	private:
	Rect windowRect;
		SDL_Window* window;
};

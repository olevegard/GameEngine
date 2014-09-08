#pragma once

#include "Rect.h"
#include <iostream>

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
	bool CreateWindow( SDL_Point pos, SDL_Point size )
	{
		InitSDL();

		windowPos = pos;
		windowSize = size;

		window = SDL_CreateWindow( "Server", pos.x, pos.y, size.x, size.y, 0 );

		if ( window == nullptr )
		{
			std::cout << "Failed to create window : " << SDL_GetError();
			return false;
		}

		return true;
	}
	SDL_Window* GetWindow() const
	{
		return window;
	}
	SDL_Point GetSize() const
	{
		return windowSize;
	}
	private:
	SDL_Point windowPos;
	SDL_Point windowSize;
	SDL_Window* window;
};

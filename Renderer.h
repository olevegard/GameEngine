// Renderer.h - headerphole.blogspot.no
// A wrapper around SDL_Renderer
// Handles initialization, rendering, setting of properties etc
#pragma once

#include <SDL2/SDL.h>

#include "Window.h"

class Renderer
{
	public:
	Renderer()
	{
	}

	bool Init( const Window &window )
	{
		renderer = SDL_CreateRenderer( window.GetWindow(), -1, SDL_RENDERER_ACCELERATED );

		if ( renderer == nullptr )
		{
			std::cout << "Failed to create renderer : " << SDL_GetError();
			return false;
		}

		SetLogicalSize( window.GetSize() );
		return true;
	}

	void RenderRotation( SDL_Texture* texture, SDL_Rect rect, double angle, SDL_Point center )
	{
		SDL_RenderCopyEx( renderer, texture, nullptr, &rect,  angle, &center, SDL_FLIP_NONE );
	}

	// Renders entire texture
	void RenderWhole( SDL_Texture* texture, SDL_Rect rect )
	{
		SDL_RenderCopy( renderer, texture, nullptr, &rect );
	}

	// Renders part of a texture to a destination
	// Source rect = the part of the rect you want to render
	// Target rect = the rect you want to render it to
	void RenderPart( SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect targetRect )
	{
		SDL_RenderCopy( renderer, texture, sourceRect, &targetRect );
	}
	// Renders entire image to the entire screen ( ie background image )
	void RenderBackground( SDL_Texture* texture )
	{
		SDL_RenderCopy( renderer, texture, nullptr, nullptr );
	}
	void SetLogicalSize( SDL_Point pt )
	{
		SDL_RenderSetLogicalSize( renderer, pt.x, pt.y );
	}
	void SetDrawColor( const SDL_Color &clr )
	{
		SDL_SetRenderDrawColor( renderer, 255, clr.r, clr.g, clr.b );
	}

	//private:
	SDL_Renderer* renderer;
};

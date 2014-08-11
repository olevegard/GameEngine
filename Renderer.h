// Renderer.h - headerphole.blogspot.no
// A wrapper around SDL_Renderer
// Handles initialization, rendering, setting of properties etc
#pragma once

#include <SDL2/SDL.h>

#include "Window.h"
#include "Texture.h"
#include "Font.h"

class Renderer
{
	public:
	Renderer();

	bool Init( const Window &window );

	// Called before rendering a new frame ( will clear any previous information )
	void RenderClear();

	// Called after rendering a frame to switch back and front buffer
	// Basically it renders everything out to the screen
	void RenderPresent();

	// Renders with rotation
	void RenderRotation( SDL_Texture* texture, SDL_Rect rect, double angle, SDL_Point center );

	// Renders entire texture
	void RenderWhole( SDL_Texture* texture, SDL_Rect rect );

	// Renders part of a texture to a destination
	// Source rect = the part of the rect you want to render
	// Target rect = the rect you want to render it to
	void RenderPart( SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect targetRect );

	// Renders entire image to the entire screen ( ie background image )
	void RenderBackground( SDL_Texture* texture );

	// Renders a Texture object
	void RenderTexture( const Texture &texture );

	Font CreateFont( const std::string &str, int32_t size );

	void SetLogicalSize( SDL_Point pt );
	void SetDrawColor( const SDL_Color &clr );

	//private:
	SDL_Renderer* renderer;
};

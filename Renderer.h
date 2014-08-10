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

	void RenderRotation( SDL_Texture* texture, SDL_Rect rect, double angle, SDL_Point center );

	// Renders entire texture
	void RenderWhole( SDL_Texture* texture, SDL_Rect rect );

	// Renders part of a texture to a destination
	// Source rect = the part of the rect you want to render
	// Target rect = the rect you want to render it to
	void RenderPart( SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect targetRect );

	// Renders entire image to the entire screen ( ie background image )
	void RenderBackground( SDL_Texture* texture );
	void RenderTexture( const Texture &texture );
	void SetLogicalSize( SDL_Point pt );
	void SetDrawColor( const SDL_Color &clr );
	Font CreateFont( const std::string &str, int32_t size );

	//private:
	SDL_Renderer* renderer;
};

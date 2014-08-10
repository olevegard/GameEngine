#include "Renderer.h"

#include <iostream>

Renderer::Renderer()
{
}
bool Renderer::Init( const Window &window )
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
void Renderer::RenderRotation( SDL_Texture* texture, SDL_Rect rect, double angle, SDL_Point center )
{
	SDL_RenderCopyEx( renderer, texture, nullptr, &rect,  angle, &center, SDL_FLIP_NONE );
}
// Renders entire texture
void Renderer::RenderWhole( SDL_Texture* texture, SDL_Rect rect )
{
	SDL_RenderCopy( renderer, texture, nullptr, &rect );
}
// Renders part of a texture to a destination
// Source rect = the part of the rect you want to render
// Target rect = the rect you want to render it to
void Renderer::RenderPart( SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect targetRect )
{
	SDL_RenderCopy( renderer, texture, &sourceRect, &targetRect );
}
// Renders entire image to the entire screen ( ie background image )
void Renderer::RenderBackground( SDL_Texture* texture )
{
	SDL_RenderCopy( renderer, texture, nullptr, nullptr );
}
void Renderer::RenderTexture( const Texture &texture )
{
	SDL_RenderCopy( renderer, texture.GetTexture(), nullptr, texture.GetRectPtr() );
}
void Renderer::SetLogicalSize( SDL_Point pt )
{
	SDL_RenderSetLogicalSize( renderer, pt.x, pt.y );
}
void Renderer::SetDrawColor( const SDL_Color &clr )
{
	SDL_SetRenderDrawColor( renderer, 255, clr.r, clr.g, clr.b );
}
Font Renderer::CreateFont( const std::string &str, int32_t size )
{
	Font font;
	font.Init( renderer, str, size );
	return font;
}

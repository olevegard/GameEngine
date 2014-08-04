#include "Texture.h"

#include <SDL2/SDL_image.h>

#include <iostream>
#include <sstream>

#include "Rect.h"

Texture::Texture()
	:	x( 0.0 )
	,	y( 0.0 )
	,	rect( { 0, 0, 0, 0 } )
	,	angle( 0.0 )
	,	deltaMultiplier( 100 )
{
}
Texture::~Texture()
{
	//SDL_DestroyTexture( texture );
}
// Initializes a texture, including size and position
void Texture::LoadTexture( SDL_Renderer *renderer, const std::string &str )
{
	texture = IMG_LoadTexture( renderer, str.c_str() );

	CalculateSize( );
}
void Texture::Render( SDL_Renderer* renderer )
{
	SDL_RenderCopyEx( renderer, texture, nullptr, &rect,  angle, &center, SDL_FLIP_NONE );
}
void Texture::Update( double delta )
{
	x += speed.x * delta * deltaMultiplier;
	y += speed.y * delta * deltaMultiplier;

	rect.SetPos( x, y );
}
Rect Texture::GetRect() const
{
	return rect;
}
Speed Texture::GetSpeed( ) const
{
	return speed;
}
void Texture::SetRect( Rect r )
{
	x = r.x;
	y = r.y;

	rect.Set( r );
}
void Texture::SetPos( SDL_Point p )
{
	rect.SetPos( p );

	x = p.x;
	y = p.y;
}
void Texture::SetSpeed( Speed s )
{
	speed.x = s.x;
	speed.y = s.y;
}
void Texture::SetTexture( SDL_Texture *text )
{
	SDL_DestroyTexture( texture );

	texture = text;
	CalculateSize( );
}
void Texture::SetTexture( SDL_Renderer* renderer, SDL_Surface* surface )
{
	ConvertSuface( renderer, surface );
}
void Texture::CenterAtPoint( const SDL_Point &p )
{
	rect.CenterAtPoint( p );
}
bool Texture::CheckCollision( const Texture &other ) const
{
	return CheckCollision( other.GetRect() );
}
bool Texture::CheckCollision( const Rect &other ) const
{
	return rect.CheckCollision( other );
}
bool Texture::IsOutOfBounds( const Rect &windowSize ) const
{
	if ( rect.x > windowSize.w )
		return true;

	if ( ( rect.x + rect.w ) < 0 )
		return true;

	if (  rect.y > windowSize.h )
		return true;

	if ( ( rect.y + rect.h ) < 0 )
		return true;

	// Not out fo bounds
	return false;
}
void Texture::MoveLeft( int32_t amount )
{
	rect.MoveLeft( amount );
}
void Texture::MoveRight( int32_t amount )
{
	rect.MoveRight( amount );
}
void Texture::MoveUp( int32_t amount )
{
	rect.MoveUp( amount );
}
void Texture::MoveDown( int32_t amount )
{
	rect.MoveDown( amount );
}
void Texture::CalculateSize( )
{
	rect.SetSizeFromTexture( texture );

	CalculateCenter( );
}
void Texture::CalculateCenter( )
{
	center = rect.CalculateCenter();
}
void Texture::ConvertSuface( SDL_Renderer* renderer, SDL_Surface* surface )
{
	if ( surface == nullptr )
	{
		std::cout << "Texture creation from surface failed|\n";
		std::cout << "\tERROR: " << SDL_GetError() << std::endl;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );

	SetTexture( texture );
	SDL_FreeSurface( surface );
}

#pragma once

#include <SDL2/SDL.h>

struct Rect : public SDL_Rect
{
	Rect();
	Rect( SDL_Rect r );

	void CenterAtPoint( const SDL_Point &p );

	void SetPos( SDL_Point p );
	void SetPos( double x_, double y_ );
	void Set( const Rect &rect );
	void SetSizeFromTexture( SDL_Texture* texture );

	bool CheckCollision( const Rect &other ) const;
	bool IsOutOfBounds( const Rect &windowSize ) const;
	SDL_Point CalculateCenter( ) const;

	void MoveLeft( int32_t amount );
	void MoveRight( int32_t amount );
	void MoveUp( int32_t amount );
	void MoveDown( int32_t amount );
};

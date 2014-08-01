// Texture.h - headerphile.blogspot.no
// A bare-bones texture class.
// Contains texture, rect for texture, angle of rotation and center of rotation

#pragma once

#include <SDL2/SDL.h>

#include <string>

struct Speed
{
	double x;
	double y;
};

struct Texture
{
	Texture();
	~Texture();

	// Initializes a texture, including size and position
	void LoadTexture( SDL_Renderer *renderer, const std::string &str );

	void Render( SDL_Renderer* renderer );
	void Update( double delta );

	// Collision detection
	bool CheckCollision( const Texture &other ) const;
	bool CheckCollision( const SDL_Rect &other ) const;
	bool IsOutOfBounds( const SDL_Rect &windowSize ) const;

	// Setters
	void SetRect( SDL_Rect r );
	void SetPos( SDL_Point p );
	void SetSpeed( Speed s );

	void MoveLeft( int32_t amount );
	void MoveRight( int32_t amount );
	void MoveUp( int32_t amount );
	void MoveDown( int32_t amount );

	void CenterAtPoint( const SDL_Point &p );

	SDL_Rect GetRect() const;
	Speed GetSpeed( ) const;
	private:

	void CalculateSize( );
	void CalculateCenter( );

	void ConvertSuface( SDL_Renderer* renderer, SDL_Surface* surface );

	// Converts surface to SDL_Texture* and call SetTextre() with that SDL_Texture*
	void SetTexture( SDL_Renderer* renderer, SDL_Surface* surface );

	// Frees previous and sets texture to text
	void SetTexture( SDL_Texture *text );

	// Position
	double x;
	double y;
	SDL_Rect rect;

	SDL_Texture* texture;

	// Movement
	Speed speed;
	double deltaMultiplier;

	// Rotation
	double angle;
	SDL_Point center;
};
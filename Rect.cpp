#include "Rect.h"

Rect::Rect()
	{
		x = 100;
		y = 100;
		w = 100;
		h = 100;
	}
	Rect::Rect( SDL_Rect r )
	{
		x = r.x;
		y = r.y;
		w = r.w;
		h = r.h;
	}
	void Rect::CenterAtPoint( const SDL_Point &p )
	{
		x = p.x - ( w * 0.5 );
		y = p.y - ( h * 0.5 );
	}
	void Rect::SetPos( SDL_Point p )
	{
		x = p.x;
		y = p.y;
	}
	void Rect::SetPos( double x_, double y_ )
	{
		x = x_;
		y = y_;
	}
	void Rect::Set( const Rect &rect )
	{
		x = rect.x;
		y = rect.y;

		w = rect.w;
		h = rect.h;
	}
	bool Rect::CheckCollision( const Rect &other ) const
	{
		// Find edges of rect1
		int left1 = x;
		int right1 = x + w;
		int top1 = y;
		int bottom1 = y + h;

		// Find edges of rect2
		int left2 = other.x;
		int right2 = other.x + other.w;
		int top2 = other.y;
		int bottom2 = other.y + other.h;

		// Check edges
		if ( left1 > right2 )// Left 1 is right of right 2
			return false; // No collision

		if ( right1 < left2 ) // Right 1 is left of left 2
			return false; // No collision

		if ( top1 > bottom2 ) // Top 1 is below bottom 2
			return false; // No collision

		if ( bottom1 < top2 ) // Bottom 1 is above top 2
			return false; // No collision

		return true;
	}
	bool Rect::IsOutOfBounds( const Rect &windowSize ) const
	{
		if ( x > ( windowSize.x + windowSize.w ) )
			return true;

		if ( ( x + w ) < windowSize.x )
			return true;

		if (  y > ( windowSize.y + windowSize.h ) )
			return true;

		if ( ( y + h ) < ( windowSize.y ) )
			return true;

		// Not out fo bounds
		return false;
	}
	void Rect::MoveLeft( int32_t amount )
	{
		x -= amount;
	}
	void Rect::MoveRight( int32_t amount )
	{
		x += amount;
	}
	void Rect::MoveUp( int32_t amount )
	{
		y -= amount;
	}
	void Rect::MoveDown( int32_t amount )
	{
		y += amount;
	}
	SDL_Point Rect::CalculateCenter( ) const
	{
		SDL_Point center;
		center.x = x + ( w * 0.5 );
		center.y = y + ( h * 0.5 );

		return center;
	}
	void Rect::SetSizeFromTexture( SDL_Texture* texture )
	{
		SDL_QueryTexture( texture, nullptr, nullptr, &w, &h );
	}

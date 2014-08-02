#pragma once

struct Rect : public SDL_Rect
{
	Rect()
	{
		x = 100;
		y = 100;
		w = 100;
		h = 100;
	}
};

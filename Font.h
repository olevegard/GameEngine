#pragma once

#include <string>

#include <SDL2/SDL_ttf.h>

enum class FontStyle
{
	Normal,
	Bold,
	Italic,
	Underline,
	Strikethrough
};
class Font
{
	public:
		Font();

		bool Init( SDL_Renderer* renderer_, const std::string &fontName, int32_t fontSize );

		void AddFontStyle( FontStyle style );
		void RemFontStyle( FontStyle style );
		void SetFontStyle( FontStyle style );

		bool ChkFontStyle( FontStyle style );

		void SetFontStyleMask( int32_t newMask );

		void ApplyFontStyle();

		TTF_Font* GetFont() const;
	private:
		TTF_Font* font;

		int32_t prevMask;
		int32_t mask;
};

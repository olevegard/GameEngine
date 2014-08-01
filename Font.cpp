#include "Font.h"

#include <iostream>

Font::Font()
	:	mask( 0 )
{
}
bool Font::Init( const std::string &fontName, int32_t fontSize )
{
	if ( TTF_WasInit() == 0 )
	{
		if ( TTF_Init() == -1 )
		{
			std::cout << "Failed to init TTF! " << TTF_GetError() << std::endl;
			return false;
		}

	}
	font = TTF_OpenFont( fontName.c_str(), fontSize );

	if ( font == nullptr )
	{
		std::cout << "Failed to load font";
		return false;
	}

	return true;
}
void Font::AddFontStyle( FontStyle style )
{
	switch ( style )
	{
		case FontStyle::Normal:
			return;
		case FontStyle::Bold:
			mask |= TTF_STYLE_BOLD;
			break;
		case FontStyle::Italic:
			mask |= TTF_STYLE_ITALIC;
			break;
		case FontStyle::Underline:
			mask |= TTF_STYLE_UNDERLINE;
			break;
		case FontStyle::Strikethrough:
			mask |= TTF_STYLE_STRIKETHROUGH;
			break;
		default :
			break;
	}
	TTF_SetFontStyle( font, mask );

	ApplyFontStyle();
}
void Font::RemFontStyle( FontStyle style )
{
	switch ( style )
	{
		case FontStyle::Normal:
			break;
		case FontStyle::Bold:
			mask &= ~TTF_STYLE_BOLD;
			break;
		case FontStyle::Italic:
			mask &= ~TTF_STYLE_ITALIC;
			break;
		case FontStyle::Underline:
			mask &= ~TTF_STYLE_UNDERLINE;
			break;
		case FontStyle::Strikethrough:
			mask &= ~TTF_STYLE_STRIKETHROUGH;
			break;
		default :
			break;
	}

	ApplyFontStyle();
}
void Font::SetFontStyle( FontStyle style )
{
	switch ( style )
	{
		case FontStyle::Normal:
			mask = TTF_STYLE_NORMAL;
			break;
		case FontStyle::Bold:
			mask = TTF_STYLE_BOLD;
			break;
		case FontStyle::Italic:
			mask = TTF_STYLE_ITALIC;
			break;
		case FontStyle::Underline:
			mask = TTF_STYLE_UNDERLINE;
			break;
		case FontStyle::Strikethrough:
			mask = TTF_STYLE_STRIKETHROUGH;
			break;
		default :
			break;
	}

	ApplyFontStyle();
}
bool Font::ChkFontStyle( FontStyle style )
{
	switch ( style )
	{
		case FontStyle::Normal:
			return ( mask & TTF_STYLE_NORMAL );
		case FontStyle::Bold:
			return ( mask & TTF_STYLE_BOLD );
		case FontStyle::Italic:
			return ( mask & TTF_STYLE_ITALIC );
		case FontStyle::Underline:
			return ( mask & TTF_STYLE_UNDERLINE );
		case FontStyle::Strikethrough:
			return ( mask & TTF_STYLE_STRIKETHROUGH );
		default :
			return false;
	}

	ApplyFontStyle();
}
void Font::SetFontStyleMask( int32_t newMask )
{
	mask = newMask;
}
void Font::ApplyFontStyle()
{
	if ( prevMask == mask )
		return;

	TTF_SetFontStyle( font, mask );

	prevMask = mask;
}
TTF_Font* Font::GetFont() const
{
	return font;
}


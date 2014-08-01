#pragma once

class Font
{
	public:
		void Init( const std::string &fontName, int32_t fontSize )
		{
			if ( TTF_WasInit() == 0 )
				TTF_Init();

			font = TTF_OpenFont( fontName.c_str(), fontSize );
		}
	
	private:
		TTF_Font* font;
};

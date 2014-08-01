#pragma once

class Font
{
	public:
		Font()
			:	mask( 0 )
		{
		}
		bool Init( const std::string &fontName, int32_t fontSize )
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
		}

	
	private:
		TTF_Font* font;

		int32_t mask;
};

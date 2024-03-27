#ifndef FONT_MANAGER
#define FONT_MANAGER

#include "./game.h"

namespace Radix
{
	class FontManager
	{
		public:
			static TTF_Font* LoadFont(const char*, int);
			static void DrawFont(SDL_Texture*, SDL_Rect);
	};
}

#endif
#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include "./game.h"

namespace Radix
{
	class TextureManager
	{
		public:
			static SDL_Texture* LoadTexture(const char* file_name);
			static void Draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination, SDL_RendererFlip flip);
	};
}

#endif
#include "./font_manager.h"

namespace Radix
{
	TTF_Font* FontManager::LoadFont(const char* file_name, int font_size)
	{
		return TTF_OpenFont(file_name, font_size);
	}

	void FontManager::DrawFont(SDL_Texture* texture, SDL_Rect position)
	{
		SDL_RenderCopy(Game::renderer, texture, nullptr, &position);
	}
}
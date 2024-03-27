#include "./asset_manager.h"

namespace Radix
{
	AssetManager::AssetManager(EntityManager* entity_manager)
	{}

	AssetManager::~AssetManager()
	{}

	void AssetManager::Clear()
	{
		fonts.clear();
		textures.clear();
	}

	SDL_Texture* AssetManager::GetTexture(std::string texture_id)
	{
		return textures[texture_id];
	}

	void AssetManager::AddTexture(std::string texture_id, const char* file_path)
	{
		textures.emplace(texture_id, TextureManager::LoadTexture(file_path));
	}

	TTF_Font* AssetManager::GetFont(std::string font_id)
	{
		return fonts[font_id];
	}

	void AssetManager::AddFont(std::string font_id, const char* file_path, int font_size)
	{
		fonts.emplace(font_id, FontManager::LoadFont(file_path, font_size));
	}
}
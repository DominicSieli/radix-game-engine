#include "./asset_manager.h"

namespace Radix
{
	AssetManager::AssetManager(EntityManager* entityManager)
	{}

	AssetManager::~AssetManager()
	{}

	void AssetManager::Clear()
	{
		fonts.clear();
		textures.clear();
	}

	SDL_Texture* AssetManager::GetTexture(std::string textureId)
	{
		return textures[textureId];
	}

	void AssetManager::AddTexture(std::string textureId, const char* filePath)
	{
		textures.emplace(textureId, TextureManager::LoadTexture(filePath));
	}

	TTF_Font* AssetManager::GetFont(std::string fontId)
	{
		return fonts[fontId];
	}

	void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize)
	{
		fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
	}
}
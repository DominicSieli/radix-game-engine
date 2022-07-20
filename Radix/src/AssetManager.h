#pragma once

#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>

#include "./Game.h"
#include "./FontManager.h"
#include "./EntityManager.h"
#include "./TextureManager.h"

namespace Radix
{
	class AssetManager
	{
	private:
		EntityManager* entityManager;
		std::map<std::string, TTF_Font*> fonts;
		std::map<std::string, SDL_Texture*> textures;
	public:
		AssetManager(EntityManager* entityManager);
		~AssetManager();
		void Clear();
		SDL_Texture* GetTexture(std::string textureId);
		void AddTexture(std::string textureId, const char* filePath);
		TTF_Font* GetFont(std::string fontId);
		void AddFont(std::string fontId, const char* filePath, int fontSize);
	};
}
#ifndef ASSET_MANAGER
#define ASSET_MANAGER

#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>

#include "./game.h"
#include "./font_manager.h"
#include "./entity_manager.h"
#include "./texture_manager.h"

namespace Radix
{
	class AssetManager
	{
		private:
			EntityManager* entity_manager;
			std::map<std::string, TTF_Font*> fonts;
			std::map<std::string, SDL_Texture*> textures;
		public:
			AssetManager(EntityManager* entity_manager);
			~AssetManager();
			void Clear();
			SDL_Texture* GetTexture(std::string texture_id);
			void AddTexture(std::string texture_id, const char* file_path);
			TTF_Font* GetFont(std::string font_id);
			void AddFont(std::string font_id, const char* file_path, int font_size);
	};
}

#endif
#ifndef TILE_COMPONENT
#define TILE_COMPONENT

#include <SDL2/SDL.h>
#include "./entity_manager.h"
#include "./asset_manager.h"
#include "../lib/glm/glm.hpp"

namespace Radix
{
	class TileComponent: public Component
	{
		public:
			SDL_Texture* texture;
			SDL_Rect source_rectangle;
			SDL_Rect destination_rectangle;
			glm::vec2 position;

			TileComponent(int source_rectangle_x, int source_rectangle_y, int x, int y, int tile_size, int tile_scale, std::string asset_texture_id)
			{
				texture = Game::asset_manager->GetTexture(asset_texture_id);

				source_rectangle.x = source_rectangle_x;
				source_rectangle.y = source_rectangle_y;
				source_rectangle.w = tile_size;
				source_rectangle.h = tile_size;

				destination_rectangle.x = x;
				destination_rectangle.y = y;
				destination_rectangle.w = tile_size * tile_scale;
				destination_rectangle.h = tile_size * tile_scale;

				position.x = x;
				position.y = y;
			}

			~TileComponent()
			{
				SDL_DestroyTexture(texture);
			}

			void Update(float delta_time) override
			{
				destination_rectangle.x = position.x - Game::camera.x;
				destination_rectangle.y = position.y - Game::camera.y;
			}

			void Render() override
			{
				TextureManager::Draw(texture, source_rectangle, destination_rectangle, SDL_FLIP_NONE);
			}
	};
}

#endif
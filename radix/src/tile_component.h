#pragma once

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
		SDL_Rect sourceRectangle;
		SDL_Rect destinationRectangle;
		glm::vec2 position;

		TileComponent(int sourceRectangleX, int sourceRectangleY, int x, int y, int tileSize, int tileScale, std::string assetTextureId)
		{
			texture = Game::assetManager->GetTexture(assetTextureId);

			sourceRectangle.x = sourceRectangleX;
			sourceRectangle.y = sourceRectangleY;
			sourceRectangle.w = tileSize;
			sourceRectangle.h = tileSize;

			destinationRectangle.x = x;
			destinationRectangle.y = y;
			destinationRectangle.w = tileSize * tileScale;
			destinationRectangle.h = tileSize * tileScale;

			position.x = x;
			position.y = y;
		}

		~TileComponent()
		{
			SDL_DestroyTexture(texture);
		}

		void Update(float deltaTime) override
		{
			destinationRectangle.x = position.x - Game::camera.x;
			destinationRectangle.y = position.y - Game::camera.y;
		}

		void Render() override
		{
			TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
		}
	};
}
#include "tile_component.h"

namespace Radix
{
	TileComponent::TileComponent(int source_rectangle_x, int source_rectangle_y, int x, int y, int tile_size, int tile_scale, std::string asset_texture_id)
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

	TileComponent::~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void TileComponent::Update(float delta_time)
	{
		destination_rectangle.x = position.x - Game::camera.x;
		destination_rectangle.y = position.y - Game::camera.y;
	}

	void TileComponent::Render()
	{
		TextureManager::Draw(texture, source_rectangle, destination_rectangle, SDL_FLIP_NONE);
	}
}
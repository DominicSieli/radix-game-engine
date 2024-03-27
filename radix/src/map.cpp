#include <fstream>
#include "./map.h"
#include "./game.h"
#include "./entity_manager.h"
#include "./tile_component.h"

namespace Radix
{
	extern EntityManager entity_manager;

	Map::Map(std::string texture_id, int scale, int tile_size)
	{
		this->texture_id = texture_id;
		this->scale = scale;
		this->tile_size = tile_size;
	}

	Map::~Map()
	{}

	void Map::LoadMap(std::string file_path, int map_size_x, int map_size_y)
	{
		std::fstream map_file;
		map_file.open(file_path);

		for(int y = 0; y < map_size_y; y++)
		{
			for(int x = 0; x < map_size_x; x++)
			{
				char character;
				map_file.get(character);
				int source_rectangle_y = atoi(&character) * tile_size;
				map_file.get(character);
				int source_rectangle_x = atoi(&character) * tile_size;
				AddTile(source_rectangle_x, source_rectangle_y, x * (scale * tile_size), y * (scale * tile_size));
				map_file.ignore();
			}
		}

		map_file.close();
	}

	void Map::AddTile(int source_rectangle_x, int source_rectangle_y, int x, int y)
	{
		Entity& new_tile(entity_manager.AddEntity("Tile", TILEMAP));
		new_tile.AddComponent<TileComponent>(source_rectangle_x, source_rectangle_y, x, y, tile_size, scale, texture_id);
	}
}
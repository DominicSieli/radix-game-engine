#include <fstream>
#include "./Map.h"
#include "./Game.h"
#include "./EntityManager.h"
#include "./TileComponent.h"

namespace Radix
{
	extern EntityManager entityManager;

	Map::Map(std::string textureId, int scale, int tileSize)
	{
		this->textureId = textureId;
		this->scale = scale;
		this->tileSize = tileSize;
	}

	Map::~Map()
	{}

	void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY)
	{
		std::fstream mapFile;
		mapFile.open(filePath);

		for(int y = 0; y < mapSizeY; y++)
		{
			for(int x = 0; x < mapSizeX; x++)
			{
				char chr;
				mapFile.get(chr);
				int sourceRectangleY = atoi(&chr) * tileSize;
				mapFile.get(chr);
				int sourceRectangleX = atoi(&chr) * tileSize;
				AddTile(sourceRectangleX, sourceRectangleY, x * (scale * tileSize), y * (scale * tileSize));
				mapFile.ignore();
			}
		}

		mapFile.close();
	}

	void Map::AddTile(int sourceRectangleX, int sourceRectangleY, int x, int y)
	{
		Entity& newTile(entityManager.AddEntity("Tile", TILEMAP));
		newTile.AddComponent<TileComponent>(sourceRectangleX, sourceRectangleY, x, y, tileSize, scale, textureId);
	}
}
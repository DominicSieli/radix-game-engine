#pragma once

#include <vector>

#include "./Entity.h"
#include "./Component.h"

class EntityManager
{
private:
	std::vector<Entity*> entities;
public:
	void Clear();
	void Update(float deltaTime);
	void Render();
	bool IsEmpty() const;
	void ListEntities() const;
	Entity& AddEntity(std::string name, LayerType layer);
	std::vector<Entity*> GetEntities() const;
	std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
	CollisionType CheckCollisions() const;
	void DestroyInactiveEntities();
	unsigned int EntityCount();
};
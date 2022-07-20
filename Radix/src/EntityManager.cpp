#include <iostream>
#include "./Collision.h"
#include "./EntityManager.h"
#include "./ColliderComponent.h"

namespace Radix
{
	void EntityManager::Clear()
	{
		for(auto& entity : entities)
		{
			entity->Destroy();
		}
	}

	void EntityManager::Update(float deltaTime)
	{
		for(auto& entity : entities)
		{
			entity->Update(deltaTime);
		}

		DestroyInactiveEntities();
	}

	void EntityManager::DestroyInactiveEntities()
	{
		for(int i = 0; i < entities.size(); i++)
		{
			if(entities[i]->Active() == false)
			{
				entities.erase(entities.begin() + i);
			}
		}
	}

	void EntityManager::Render()
	{
		for(int layerNumber = 0; layerNumber < LAYER_COUNT; layerNumber++)
		{
			for(auto& entity: GetEntitiesByLayer(static_cast<LayerType>(layerNumber)))
			{
				entity->Render();
			}
		}
	}

	bool EntityManager::IsEmpty() const
	{
		return entities.size() == 0;
	}

	void EntityManager::ListEntities() const
	{
		for(unsigned int i = 0; i < entities.size(); i++)
		{
			std::cout << "Entity[" << i << "]: " << entities[i]->name << "\n";
			entities[i]->ListComponents();
		}
	}

	Entity& EntityManager::AddEntity(std::string name, LayerType layer)
	{
		Entity* entity = new Entity(*this, name, layer);
		entities.emplace_back(entity);
		return *entity;
	}

	std::vector<Entity*> EntityManager::GetEntities() const
	{
		return entities;
	}

	std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const
	{
		std::vector<Entity*> selectedEntities;

		for(auto& entity: entities)
		{
			if(entity->layer == layer) selectedEntities.emplace_back(entity);
		}

		return selectedEntities;
	}

	CollisionType EntityManager::CheckCollisions() const
	{
		for(int i = 0; i < entities.size() - 1; i++)
		{
			auto& thisEntity = entities[i];

			if(thisEntity->HasComponent<ColliderComponent>() == true)
			{
				ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();

				for(int j = i + 1; j < entities.size(); j++)
				{
					auto& thatEntity = entities[j];

					if(thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>() == true)
					{
						ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();

						if(Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider) == true)
						{
							if(thisCollider->tag.compare("PLAYER") == 0 && thatCollider->tag.compare("ENEMY") == 0)
							{
								return PLAYER_ENEMY_COLLISION;
							}

							if(thisCollider->tag.compare("PLAYER") == 0 && thatCollider->tag.compare("PROJECTILE") == 0)
							{
								return PLAYER_PROJECTILE_COLLISION;
							}

							if(thisCollider->tag.compare("ENEMY") == 0 && thatCollider->tag.compare("PLAYER_PROJECTILE") == 0)
							{
								return ENEMY_PROJECTILE_COLLISION;
							}

							if(thisCollider->tag.compare("PLAYER") == 0 && thatCollider->tag.compare("LEVEL_COMPLETE") == 0)
							{
								return PLAYER_LEVEL_COMPLETE_COLLISION;
							}
						}
					}
				}
			}
		}

		return NO_COLLISION;
	}

	unsigned int EntityManager::EntityCount()
	{
		return entities.size();
	}
}
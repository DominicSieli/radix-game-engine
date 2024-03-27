#include <iostream>
#include "./collision.h"
#include "./entity_manager.h"
#include "./collider_component.h"

namespace Radix
{
	void EntityManager::Clear()
	{
		for(auto& entity : entities)
		{
			entity->Destroy();
		}
	}

	void EntityManager::Update(float delta_time)
	{
		for(auto& entity : entities)
		{
			entity->Update(delta_time);
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
		for(int layer_number = 0; layer_number < LAYER_COUNT; layer_number++)
		{
			for(auto& entity: GetEntitiesByLayer(static_cast<LayerType>(layer_number)))
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
		std::vector<Entity*> selected_entities;

		for(auto& entity: entities)
		{
			if(entity->layer == layer) selected_entities.emplace_back(entity);
		}

		return selected_entities;
	}

	CollisionType EntityManager::CheckCollisions() const
	{
		for(int i = 0; i < entities.size() - 1; i++)
		{
			auto& this_entity = entities[i];

			if(this_entity->HasComponent<ColliderComponent>() == true)
			{
				ColliderComponent* this_collider = this_entity->GetComponent<ColliderComponent>();

				for(int j = i + 1; j < entities.size(); j++)
				{
					auto& that_entity = entities[j];

					if(this_entity->name.compare(that_entity->name) != 0 && that_entity->HasComponent<ColliderComponent>() == true)
					{
						ColliderComponent* that_collider = that_entity->GetComponent<ColliderComponent>();

						if(Collision::CheckRectangleCollision(this_collider->collider, that_collider->collider) == true)
						{
							if(this_collider->tag.compare("PLAYER") == 0 && that_collider->tag.compare("ENEMY") == 0)
							{
								return PLAYER_ENEMY_COLLISION;
							}

							if(this_collider->tag.compare("PLAYER") == 0 && that_collider->tag.compare("PROJECTILE") == 0)
							{
								return PLAYER_PROJECTILE_COLLISION;
							}

							if(this_collider->tag.compare("ENEMY") == 0 && that_collider->tag.compare("PLAYER_PROJECTILE") == 0)
							{
								return ENEMY_PROJECTILE_COLLISION;
							}

							if(this_collider->tag.compare("PLAYER") == 0 && that_collider->tag.compare("LEVEL_COMPLETE") == 0)
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
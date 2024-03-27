#ifndef COLLIDER_COMPONENT
#define COLLIDER_COMPONENT

#include <SDL2/SDL.h>
#include "./game.h"
#include "./entity_manager.h"
#include "./transform_component.h"

namespace Radix
{
	class ColliderComponent: public Component
	{
		public:
			std::string tag;
			SDL_Rect collider;
			SDL_Rect source_rectangle;
			SDL_Rect destination_rectangle;
			TransformComponent* transform_component;

			ColliderComponent(std::string tag, int x, int y, int width, int height)
			{
				this->tag = tag;
				this->collider = {x, y, width, height};
			}

			void Initialize() override
			{
				if(entity->HasComponent<TransformComponent>())
				{
					transform_component = entity->GetComponent<TransformComponent>();
					source_rectangle = {0, 0, (int)transform_component->dimension.x, (int)transform_component->dimension.y};
					destination_rectangle = {collider.x, collider.y, collider.w, collider.h};
				}
			}

			void Update(float delta_time) override
			{
				collider.x = static_cast<int>(transform_component->position.x);
				collider.y = static_cast<int>(transform_component->position.y);
				collider.w = transform_component->dimension.x * transform_component->scale;
				collider.h = transform_component->dimension.y * transform_component->scale;
				destination_rectangle.x = collider.x - Game::camera.x;
				destination_rectangle.y = collider.y - Game::camera.y;
			}
	};
}

#endif
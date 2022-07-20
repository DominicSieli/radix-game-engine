#pragma once

#include <SDL2/SDL.h>
#include "./Game.h"
#include "./EntityManager.h"
#include "./TransformComponent.h"

namespace Radix
{
	class ColliderComponent: public Component
	{
	public:
		std::string tag;
		SDL_Rect collider;
		SDL_Rect sourceRect;
		SDL_Rect destinationRect;
		TransformComponent* transformComponent;

		ColliderComponent(std::string tag, int x, int y, int width, int height)
		{
			this->tag = tag;
			this->collider = {x, y, width, height};
		}

		void Initialize() override
		{
			if(entity->HasComponent<TransformComponent>())
			{
				transformComponent = entity->GetComponent<TransformComponent>();
				sourceRect = {0, 0, transformComponent->dimension.x, transformComponent->dimension.y};
				destinationRect = {collider.x, collider.y, collider.w, collider.h};
			}
		}

		void Update(float deltaTime) override
		{
			collider.x = static_cast<int>(transformComponent->position.x);
			collider.y = static_cast<int>(transformComponent->position.y);
			collider.w = transformComponent->dimension.x * transformComponent->scale;
			collider.h = transformComponent->dimension.y * transformComponent->scale;
			destinationRect.x = collider.x - Game::camera.x;
			destinationRect.y = collider.y - Game::camera.y;
		}
	};
}
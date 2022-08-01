#pragma once

#include <SDL2/SDL.h>

#include "./Game.h"
#include "./EntityManager.h"
#include "../lib/glm/glm.hpp"

namespace Radix
{
	class TransformComponent: public Component
	{
	public:
		int scale;
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec2 dimension;

		TransformComponent(int positionX, int positionY, int velocityX, int velocityY, int dimensionX, int dimensionY, int scale)
		{
			this->scale = scale;
			this->position = glm::vec2(positionX, positionY);
			this->velocity = glm::vec2(velocityX, velocityY);
			this->dimension = glm::vec2(dimensionX, dimensionY);
		}

		void Initialize() override
		{}

		void Update(float deltaTime) override
		{
			position.x += velocity.x * deltaTime;
			position.y += velocity.y * deltaTime;
		}

		void Render() override
		{}
	};
}
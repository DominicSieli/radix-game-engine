#ifndef TRANSFORM_COMPONENT
#define TRANSFORM_COMPONENT

#include <SDL2/SDL.h>

#include "./game.h"
#include "./entity_manager.h"
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

			TransformComponent(int position_x, int position_y, int velocity_x, int velocity_y, int dimension_x, int dimension_y, int scale)
			{
				this->scale = scale;
				this->position = glm::vec2(position_x, position_y);
				this->velocity = glm::vec2(velocity_x, velocity_y);
				this->dimension = glm::vec2(dimension_x, dimension_y);
			}

			void Initialize() override
			{}

			void Update(float delta_time) override
			{
				position.x += velocity.x * delta_time;
				position.y += velocity.y * delta_time;
			}

			void Render() override
			{}
	};
}

#endif
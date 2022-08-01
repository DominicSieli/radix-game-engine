#pragma once

#include "EntityManager.h"
#include "TransformComponent.h"
#include "../lib/glm/glm.hpp"

namespace Radix
{
	class ProjectileEmitterComponent: public Component
	{
	private:
		TransformComponent* transformComponent;
		glm::vec2 origin;
		int speed;
		int range;
		float angleRadian;
		bool loop;
	public:
		ProjectileEmitterComponent(int speed, int angleDegree, int range, bool loop)
		{
			this->speed = speed;
			this->angleRadian = glm::radians(static_cast<float>(angleDegree));
			this->range = range;
			this->loop = loop;
		}

		void Initialize() override
		{
			transformComponent = entity->GetComponent<TransformComponent>();
			origin = glm::vec2(transformComponent->position.x, transformComponent->position.y);
			transformComponent->velocity = glm::vec2(glm::cos(angleRadian) * speed, glm::sin(angleRadian) * speed);
		}

		void Update(float deltaTime) override
		{
			if(glm::distance(transformComponent->position, origin) > range)
			{
				if(loop == true)
				{
					transformComponent->position.x = origin.x;
					transformComponent->position.y = origin.y;
				}
				else
				{
					entity->Destroy();
				}
			}
		}
	};
}
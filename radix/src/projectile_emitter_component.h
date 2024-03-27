#ifndef PROJECTILE_EMITTER_COMPONENT
#define PROJECTILE_EMITTER_COMPONENT

#include "entity_manager.h"
#include "transform_component.h"
#include "../lib/glm/glm.hpp"

namespace Radix
{
	class ProjectileEmitterComponent: public Component
	{
		private:
			TransformComponent* transform_component;
			glm::vec2 origin;
			int speed;
			int range;
			float radian;
			bool loop;
		public:
			ProjectileEmitterComponent(int speed, int degree, int range, bool loop)
			{
				this->speed = speed;
				this->radian = glm::radians(static_cast<float>(degree));
				this->range = range;
				this->loop = loop;
			}

			void Initialize() override
			{
				transform_component = entity->GetComponent<TransformComponent>();
				origin = glm::vec2(transform_component->position.x, transform_component->position.y);
				transform_component->velocity = glm::vec2(glm::cos(radian) * speed, glm::sin(radian) * speed);
			}

			void Update(float delta_time) override
			{
				if(glm::distance(transform_component->position, origin) > range)
				{
					if(loop == true)
					{
						transform_component->position.x = origin.x;
						transform_component->position.y = origin.y;
					}
					else
					{
						entity->Destroy();
					}
				}
			}
	};
}

#endif
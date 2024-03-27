#include <iostream>
#include "./entity.h"

namespace Radix
{
	Entity::Entity(EntityManager& entity_manager): entity_manager{entity_manager}
	{
		this->active = true;
	}

	Entity::Entity(EntityManager& entity_manager, std::string name, LayerType layer): entity_manager{entity_manager}, name{name}, layer{layer}
	{
		this->active = true;
	}

	void Entity::Update(float delta_time)
	{
		for(auto& component : components)
		{
			component->Update(delta_time);
		}
	}

	void Entity::Render()
	{
		for(auto& component : components)
		{
			component->Render();
		}
	}

	void Entity::Destroy()
	{
		this->active = false;
	}

	bool Entity::Active() const
	{
		return this->active;
	}

	void Entity::ListComponents() const
	{
		for(auto component: component_type_map)
		{
			std::cout << "Component<" << component.first->name() << ">" << "\n";
		}
	}
}
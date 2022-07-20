#include <iostream>
#include "./Entity.h"

Entity::Entity(EntityManager& entityManager): entityManager{entityManager}
{
	this->active = true;
}

Entity::Entity(EntityManager& entityManager, std::string name, LayerType layer): entityManager{entityManager}, name{name}, layer{layer}
{
	this->active = true;
}

void Entity::Update(float deltaTime)
{
	for(auto& component : components)
	{
		component->Update(deltaTime);
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
	for(auto component: componentTypeMap)
	{
		std::cout << "Component<" << component.first->name() << ">" << "\n";
	}
}
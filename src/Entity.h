#pragma once

#include <map>
#include <vector>
#include <string>
#include <typeinfo>

#include "./Constants.h"
#include "./Component.h"
#include "./EntityManager.h"

class EntityManager;

class Entity
{
private:
	bool active;
	EntityManager& entityManager;
	std::vector<Component*> components;
	std::map<const std::type_info*, Component*> componentTypeMap;
public:
	std::string name;
	LayerType layer;
	Entity(EntityManager& entityManager);
	Entity(EntityManager& entityManager, std::string name, LayerType layer);
	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool Active() const;
	void ListComponents() const;

	template<typename T, typename... T_ARGS>
	T& AddComponent(T_ARGS&&... args)
	{
		T* component(new T(std::forward<T_ARGS>(args)...));
		component->entity = this;
		components.emplace_back(component);
		componentTypeMap[&typeid(*component)] = component;
		component->Initialize();
		return *component;
	}

	template<typename T>
	T* GetComponent()
	{
		return static_cast<T*>(componentTypeMap[&typeid(T)]);
	}

	template<typename T>
	bool HasComponent() const
	{
		return componentTypeMap.count(&typeid(T));
	}
};
#pragma once

#include "./Entity.h"

namespace Radix
{
	class Entity;

	class Component
	{
	public:
		Entity* entity;
		virtual ~Component() {}
		virtual void Initialize() {}
		virtual void Update(float deltaTime) {}
		virtual void Render() {}
	};
}
#pragma once

#include <SDL2/SDL.h>

namespace Radix
{
	class Collision
	{
	public:
		static bool CheckRectangleCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
	};
}
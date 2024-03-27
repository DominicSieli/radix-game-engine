#include "./collision.h"

namespace Radix
{
	bool Collision::CheckRectangleCollision(const SDL_Rect& rectangle_1, const SDL_Rect& rectangle_2)
	{
		return (rectangle_1.x + rectangle_1.w >= rectangle_2.x && rectangle_2.x + rectangle_2.w >= rectangle_1.x && rectangle_1.y + rectangle_1.h >= rectangle_2.y && rectangle_2.y + rectangle_2.h >= rectangle_1.y);
	}
}
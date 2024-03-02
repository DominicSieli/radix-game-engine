#pragma once

namespace Radix
{
	class Animation
	{
	public:
		unsigned int index;
		unsigned int frames;
		unsigned int speed;

		Animation();
		Animation(unsigned int index, unsigned int frames, unsigned int speed);
	};
}
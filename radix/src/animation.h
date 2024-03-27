#ifndef ANIMATION
#define ANIMATION

namespace Radix
{
	class Animation
	{
		public:
			unsigned int index;
			unsigned int frames;
			unsigned int speed;

			Animation();
			Animation(unsigned int, unsigned int, unsigned int);
	};
}

#endif
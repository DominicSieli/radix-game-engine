#include "./Animation.h"

Animation::Animation()
{}

Animation::Animation(unsigned int index, unsigned int frames, unsigned int speed)
{
	this->index = index;
	this->frames = frames;
	this->speed = speed;
}
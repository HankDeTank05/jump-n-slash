#include "Animation.h"

Animation::Animation(float _fps, bool _loop)
	: frames(),
	fps(_fps),
	spf(1.f / fps),
	loop(_loop)
{
	// do nothing
}

Animation::~Animation()
{
	frames.clear();
}

Animation::Iterator Animation::GetFirstFrame()
{
	return frames.begin();
}

Animation::Iterator Animation::GetNextFrame(Iterator it)
{
	it++;
	if (it == frames.end() && loop == true)
	{
		if (loop)
		{
			it = frames.begin();
		}
		else
		{
			it--;
		}
	}
	return it;
}

void Animation::AddFrame(sf::Sprite* pNextFrame)
{
	frames.push_back(pNextFrame);
}

float Animation::GetFPS()
{
	return fps;
}

float Animation::GetSPF()
{
	return spf;
}

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

bool Animation::IsLastFrame(Iterator it)
{
	Iterator tempIt = ++it;
	it--;
	return tempIt == frames.end();
}

void Animation::AddFrame(sf::Sprite* pNextFrame)
{
	frames.push_back(pNextFrame);
}

void Animation::SetLoop(bool newLoop)
{
	loop = newLoop;
}

bool Animation::IsLooping()
{
	return loop;
}

float Animation::GetFPS()
{
	return fps;
}

float Animation::GetSPF()
{
	return spf;
}

#ifndef ANIMATION_H
#define ANIMATION_H

#include <list>

#include <SFML/Graphics/Sprite.hpp>

class Animation
{
public:
	Animation() = delete;
	Animation(float fps, bool loop = true);
	Animation(const Animation& a) = delete;
	Animation& operator=(const Animation& a) = delete;
	virtual ~Animation();

	using Iterator = std::list<sf::Sprite*>::iterator;

	Iterator GetFirstFrame(); // TODO: docs for Animation::GetFirstFrame
	Iterator GetNextFrame(Iterator it); // TODO: docs for Animation::GetNextFrame

	void AddFrame(sf::Sprite* pNextFrame); // TODO: docs for Animation::AddFrame

	float GetFPS(); // TODO: docs for Animation::GetFPS
	float GetSPF(); // TODO: docs for Animation::GetSPF

private:
	std::list<sf::Sprite*> frames;
	float fps; // frames per second
	float spf; // seconds per frame
	bool loop;
};

#endif
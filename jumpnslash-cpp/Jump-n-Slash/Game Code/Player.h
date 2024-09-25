#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "../Engine Code/UpdatableObject.h"
#include "../Engine Code/DrawableObject.h"
#include "../Engine Code/InputObject.h"

class Player : public UpdatableObject, public DrawableObject, public InputObject
{
public:
	Player();
	Player(const Player& p) = delete;
	Player& operator=(const Player& p) = delete;
	virtual ~Player();

	virtual void Update() override;
	virtual void Draw() override;
	
private:
	sf::CircleShape circle;
	int currentFrames;
	int maxFrames;
};

#endif
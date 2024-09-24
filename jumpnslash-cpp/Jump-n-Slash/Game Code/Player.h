#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "../Engine Code/DrawableObject.h"

class Player : public DrawableObject
{
public:
	Player();
	Player(const Player& p) = delete;
	Player& operator=(const Player& p) = delete;
	virtual ~Player();

	virtual void Draw() override;
	
private:
	sf::CircleShape circle;
};

#endif
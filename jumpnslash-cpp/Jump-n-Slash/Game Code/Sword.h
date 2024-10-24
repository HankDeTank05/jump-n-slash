#ifndef SWORD_H
#define SWORD_H

#include "../Engine Code/UpdateObject.h"
#include "../Engine Code/DrawObject.h"
#include "../Engine Code/CollisionObject.h"

// forward declarations
class Player;
class SwordState;
class AnimationComponent;

class Sword : public UpdateObject, public DrawObject, public CollisionObject
{
public:
	Sword() = delete;
	Sword(Player* pPlayer);
	Sword(const Sword& s) = delete;
	Sword& operator=(const Sword& s) = delete;
	virtual ~Sword() = default;

private:
	Player* pPlayer;
	sf::Vector2f pos;
	const SwordState* pCurrentState;
	const SwordState* pPrevState;
	sf::Sprite* pSprite;
	AnimationComponent* pAnimComp;
};

#endif
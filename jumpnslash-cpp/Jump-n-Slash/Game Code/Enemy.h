#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/System/Vector2.hpp>

#include "../Engine Code/UpdateObject.h"
#include "../Engine Code/DrawObject.h"
#include "../Engine Code/CollisionObject.h"
#include "../Engine Code/AnimationComponent.h"

class Enemy : public UpdateObject, public DrawObject, public CollisionObject
{
public:
	Enemy();
	Enemy(const Enemy& e) = delete;
	Enemy& operator=(const Enemy& e) = delete;
	virtual ~Enemy();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	sf::Vector2f pos;
	sf::Vector2f posDelta;
	sf::Sprite* pSprite;
	AnimationComponent animComp;
};

#endif
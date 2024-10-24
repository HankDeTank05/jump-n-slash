#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/System/Vector2.hpp>

#include "../Engine Code/UpdateObject.h"
#include "../Engine Code/DrawObject.h"
#include "../Engine Code/CollisionObject.h"
#include "../Engine Code/AnimationComponent.h"

// forward declarations
class Player;

class Enemy : public UpdateObject,
	public DrawObject,
	public CollisionObject
{
public:
	Enemy();
	Enemy(const Enemy& e) = delete;
	Enemy& operator=(const Enemy& e) = delete;
	virtual ~Enemy();

	// update stuff
	virtual void Update(float deltaTime) override;

	// draw stuff
	virtual void Draw() override;

	// collision stuff
	virtual void OnCollisionEnter(CollisionObject* pOther) override;
	virtual void OnCollisionDuring(CollisionObject* pOther) override;
	virtual void OnCollisionExit(CollisionObject* pOther) override;

private:
	sf::Vector2f pos;
	sf::Vector2f posDelta;
	sf::Sprite* pSprite;
	AnimationComponent animComp;
};

#endif
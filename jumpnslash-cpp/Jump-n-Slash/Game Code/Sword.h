#ifndef SWORD_H
#define SWORD_H

// engine includes
#include "../Engine Code/UpdateObject.h"
#include "../Engine Code/DrawObject.h"
#include "../Engine Code/CollisionObject.h"

// forward declarations
class Player;
class SwordState;
class AnimationComponent;
class Sprite;

class Sword : public UpdateObject, public DrawObject, public CollisionObject
{
public:
	Sword() = delete;
	Sword(Player* pPlayer);
	Sword(const Sword& s) = delete;
	Sword& operator=(const Sword& s) = delete;
	virtual ~Sword();

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;

	virtual void OnCollisionEnter(CollisionObject* pOther) override;
	virtual void OnCollisionDuring(CollisionObject* pOther) override;
	virtual void OnCollisionExit(CollisionObject* pOther) override;

	void Attack();

private: // accessors (accessible thru attorney)
	friend class SwordAttorney;
	bool IsAttacking();

private: // mutators (accessible thru attorney)
	void SetAnimationIdle();
	void SetAnimationSwing();

private:
	Player* pPlayer;
	const sf::Vector2f playerPosOffset;
	sf::Vector2f pos;
	const SwordState* pCurrentState;
	const SwordState* pPrevState;
	Sprite* pSprite;
	AnimationComponent* pAnimComp;
	bool attack;
};

#endif
#ifndef SWORD_STATE_H
#define SWORD_STATE_H

// forward declarations
class Sword;

class SwordState
{
public:
	SwordState() = default;
	SwordState(const SwordState& ss) = delete;
	SwordState& operator=(const SwordState& ss) = delete;
	virtual ~SwordState() = default;

	virtual void Enter(Sword* pSword) const = 0;
	virtual void Update(Sword* pSword, float deltaTime) const = 0;
	virtual const SwordState* GetNextState(Sword* pSword) const = 0;
};

#endif
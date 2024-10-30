#ifndef SWORD_STATE_SWING_H
#define SWORD_STATE_SWING_H

#include "SwordState.h"

class SwordStateSwing : public SwordState
{
public:
	SwordStateSwing() = default;
	SwordStateSwing(const SwordStateSwing& sss) = delete;
	SwordStateSwing& operator=(const SwordStateSwing& sss) = delete;
	virtual ~SwordStateSwing() = default;

	virtual void Enter(Sword* pSword) const override;
	virtual void Update(Sword* pSword, float deltaTime) const override;
	virtual const SwordState* GetNextState(Sword* pSword) const override;
};

#endif
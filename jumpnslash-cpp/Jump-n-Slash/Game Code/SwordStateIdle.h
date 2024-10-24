#ifndef SWORD_STATE_IDLE_H
#define SWORD_STATE_IDLE_H

#include "SwordState.h"

class SwordStateIdle : public SwordState
{
public:
	SwordStateIdle() = default;
	SwordStateIdle(const SwordStateIdle& ssi) = delete;
	SwordStateIdle& operator=(const SwordStateIdle& ssi) = delete;
	virtual ~SwordStateIdle() = default;

	virtual void Enter(Sword* pSword) const override;
	virtual void Update(Sword* pSword, float deltaTime) const override;
	virtual const SwordState* GetNextState(Sword* pSword) const override;
};

#endif
#ifndef PLAYER_CONTROL_STRATEGY_H
#define PLAYER_CONTROL_STRATEGY_H

#include "../Engine Code/InputObject.h"

#include "ControlScheme.h"

class PlayerControlStrategy : public InputObject
{
public:
	PlayerControlStrategy() = delete;
	PlayerControlStrategy(ControlScheme scheme);
	PlayerControlStrategy(const PlayerControlStrategy& pcs) = delete;
	PlayerControlStrategy& operator=(const PlayerControlStrategy& pcs) = delete;
	virtual ~PlayerControlStrategy() = default;

	virtual void SendInputs() = 0;

protected:
	bool jump;
	float walk;
	bool slashAtk;
	bool dreamAtk;
	bool dash;
};

#endif
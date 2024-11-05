#ifndef PLAYER_CONTROL_STRATEGY_H
#define PLAYER_CONTROL_STRATEGY_H

#include "../Engine Code/InputObject.h"

#include "ControlScheme.h"

// forward declarations
class Player;

class PlayerControlStrategy : public InputObject
{
public:
	PlayerControlStrategy() = delete;
	PlayerControlStrategy(Player* pPlayer, ControlScheme ctrl);
	PlayerControlStrategy(const PlayerControlStrategy& pcs) = delete;
	PlayerControlStrategy& operator=(const PlayerControlStrategy& pcs) = delete;
	virtual ~PlayerControlStrategy() = default;

	void GetInputs();

protected:
	Player* pPlayer;
	bool jump;
	float walk;
	bool slashAtk;
	bool dreamAtk;
	bool dash;
};

#endif
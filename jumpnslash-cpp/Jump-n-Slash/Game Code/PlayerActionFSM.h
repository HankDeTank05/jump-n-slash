#ifndef PLAYER_ACTION_FSM_H
#define PLAYER_ACTION_FSM_H

// game includes
#include "PlayerActionStateNone.h"
#include "PlayerActionStateSlashAtk.h"
#include "PlayerActionStateDreamAtk.h"

class PlayerActionFSM
{
public:
	static const PlayerActionStateNone none;
	static const PlayerActionStateSlashAtk slashAtk;
	static const PlayerActionStateDreamAtk dreamAtk;
};

#endif
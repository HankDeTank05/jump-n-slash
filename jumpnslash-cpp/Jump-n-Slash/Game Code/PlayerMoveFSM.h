#ifndef PLAYER_MOVE_FSM_H
#define PLAYER_MOVE_FSM_H

// game includes
#include "PlayerMoveState.h"
#include "PlayerMoveStateIdle.h"
#include "PlayerMoveStateWalking.h"
#include "PlayerMoveStateJumping.h"
#include "PlayerMoveStateFalling.h"
#include "PlayerMoveStateDashing.h"
#include "PlayerMoveStateSlashAtk.h"
#include "PlayerMoveStateDreamAtk.h"

class PlayerMoveFSM
{
public:
	static const PlayerMoveStateIdle idle;
	static const PlayerMoveStateWalking walking;
	static const PlayerMoveStateJumping jumping;
	static const PlayerMoveStateFalling falling;
	static const PlayerMoveStateDashing dashing;
	static const PlayerMoveStateSlashAtk slashAtk;
	static const PlayerMoveStateDreamAtk dreamAtk;
};

#endif
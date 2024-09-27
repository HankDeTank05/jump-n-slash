#ifndef PLAYER_FSM_H
#define PLAYER_FSM_H

#include "PlayerMoveState.h"
#include "PlayerStateIdle.h"
#include "PlayerStateWalking.h"
#include "PlayerStateJumping.h"
#include "PlayerStateFalling.h"

class PlayerFSM
{
public:
	static const PlayerStateIdle idle;
	static const PlayerStateWalking walking;
	static const PlayerStateJumping jumping;
	static const PlayerStateFalling falling;
};

#endif
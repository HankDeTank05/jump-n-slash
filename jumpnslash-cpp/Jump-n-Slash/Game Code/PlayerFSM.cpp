#include "PlayerFSM.h"

const PlayerStateIdle PlayerFSM::idle = PlayerStateIdle();
const PlayerStateWalking PlayerFSM::walking = PlayerStateWalking();
const PlayerStateJumping PlayerFSM::jumping = PlayerStateJumping();
const PlayerStateFalling PlayerFSM::falling = PlayerStateFalling();
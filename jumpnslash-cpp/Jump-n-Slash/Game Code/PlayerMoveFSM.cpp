#include "PlayerMoveFSM.h"

const PlayerMoveStateIdle PlayerMoveFSM::idle;
const PlayerMoveStateWalking PlayerMoveFSM::walking;
const PlayerMoveStateJumping PlayerMoveFSM::jumping;
const PlayerMoveStateFalling PlayerMoveFSM::falling;
const PlayerMoveStateDashing PlayerMoveFSM::dashing;
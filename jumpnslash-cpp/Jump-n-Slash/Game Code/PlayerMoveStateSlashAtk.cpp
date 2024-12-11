#include "PlayerMoveStateSlashAtk.h"

// language includes
#include <iostream>

// game includes
#include "GameDebugFlags.h"
#include "PlayerAttorney.h"
#include "PlayerMoveFSM.h"

void PlayerMoveStateSlashAtk::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_ACTION_STATE) std::cout << "Entered PlayerMoveStateSlashAtk" << std::endl;

	PlayerAttorney::StateAccess::SetAnimationAttack(pPlayer);
	PlayerAttorney::StateAccess::BeginSlashAtk(pPlayer);
}

void PlayerMoveStateSlashAtk::Update(Player* pPlayer, float deltaTime) const
{
	//assert(false); // TODO: implement update behavior
}

const PlayerMoveState* PlayerMoveStateSlashAtk::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	if (PlayerAttorney::StateAccess::IsAttacking(pPlayer) == false)
	{
		if (PlayerAttorney::StateAccess::IsGrounded(pPlayer) == true)
		{
			if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x == 0)
			{
				pNextState = &PlayerMoveFSM::idle;
			}
			else
			{
				pNextState = &PlayerMoveFSM::walking;
			}
		}
		else
		{
			if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).y < 0)
			{
				pNextState = &PlayerMoveFSM::falling;
			}
			else if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).y > 0)
			{
				pNextState = &PlayerMoveFSM::jumping;
			}
			else
			{
				assert(false); // congrats. your attack ended exactly at the apex of the jump...
			}
		}
	}

	return pNextState;
}

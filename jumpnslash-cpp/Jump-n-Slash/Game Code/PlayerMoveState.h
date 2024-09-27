#ifndef PLAYER_MOVE_STATE_H
#define PLAYER_MOVE_STATE_H

// forward declarations
class Player;

class PlayerMoveState
{
public:
	PlayerMoveState();
	PlayerMoveState(const PlayerMoveState& pms) = delete;
	PlayerMoveState& operator=(const PlayerMoveState& pms) = delete;
	virtual ~PlayerMoveState();

	virtual void Enter(Player* pPlayer) const = 0;
	//virtual const void HandleInput(Player* pPlayer) const = 0;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const = 0;
	//virtual void SetAnimation(Player* pPlayer) const = 0;

private:
};

#endif
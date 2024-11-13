#ifndef PLAYER_ACTION_STATE_H
#define PLAYER_ACTION_STATE_H

// forward declarations
class Player;

class PlayerActionState
{
public:
	PlayerActionState() = default;
	PlayerActionState(const PlayerActionState& pas) = delete;
	PlayerActionState& operator=(const PlayerActionState& pas) = delete;
	virtual ~PlayerActionState() = default;

	virtual void Enter(Player* pPlayer) const = 0;
	virtual void Update(Player* pPlayer, float deltaTime) const = 0;
	virtual const PlayerActionState* GetNextState(Player* pPlayer) const = 0;
};

#endif
#ifndef PLAYER_ANIM_STATE_H
#define PLAYER_ANIM_STATE_h

// forward declarations
class Player;

class PlayerAnimState
{
public:
	PlayerAnimState() = default;
	PlayerAnimState(const PlayerAnimState& pas) = delete;
	PlayerAnimState& operator=(const PlayerAnimState& pas) = delete;
	virtual ~PlayerAnimState() = default;

	virtual void Enter(Player* pPlayer) const = 0;
	virtual void Update(Player* pPlayer, float deltaTime) const = 0;
	virtual const PlayerAnimState* GetNextState(Player* pPlayer) const = 0;
};

#endif

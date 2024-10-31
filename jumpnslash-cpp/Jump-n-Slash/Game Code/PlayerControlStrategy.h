#ifndef PLAYER_CONTROL_STRATEGY_H
#define PLAYER_CONTROL_STRATEGY_H

class PlayerControlStrategy
{
public:
	PlayerControlStrategy() = default;
	PlayerControlStrategy(const PlayerControlStrategy& pcs) = delete;
	PlayerControlStrategy& operator=(const PlayerControlStrategy& pcs) = delete;
	virtual ~PlayerControlStrategy() = default;
};

#endif
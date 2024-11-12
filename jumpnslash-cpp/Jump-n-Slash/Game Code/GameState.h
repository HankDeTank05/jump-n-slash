#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState
{
public:
	GameState() = default;
	GameState(const GameState& gs) = delete;
	GameState& operator=(const GameState& gs) = delete;
	virtual ~GameState() = default;

	virtual const GameState* GetNextState() const = 0;
};

#endif
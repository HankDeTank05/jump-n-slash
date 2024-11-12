#ifndef GAME_STATE_PLAYING_H
#define GAME_STATE_PLAYING_H

// game includes
#include "GameState.h"

class GameStatePlaying : public GameState
{
public:
	GameStatePlaying() = default;
	GameStatePlaying(const GameStatePlaying& gsp) = delete;
	GameStatePlaying& operator=(const GameStatePlaying& gsp) = delete;
	virtual ~GameStatePlaying() = default;

	virtual const GameState* GetNextState() const override;
};

#endif
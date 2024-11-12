#ifndef GAME_STATE_MENU_H
#define GAME_STATE_MENU_H

// game includes
#include "GameState.h"

class GameStateMenu : public GameState
{
public:
	GameStateMenu() = default;
	GameStateMenu(const GameStateMenu& gsm) = delete;
	GameStateMenu& operator=(const GameStateMenu& gsm) = delete;
	virtual ~GameStateMenu() = default;

	virtual const GameState* GetNextState() const override;
};

#endif
#ifndef GAME_FSM_H
#define GAME_FSM_H

// game includes
#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateMenu.h"

class GameFSM
{
public:
	static const GameStatePlaying playing;
	static const GameStateMenu menu;
};

#endif
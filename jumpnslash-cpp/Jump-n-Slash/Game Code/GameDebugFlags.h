#ifndef GAME_DEBUG_FLAGS_H
#define GAME_DEBUG_FLAGS_H

#include "../Engine Code/EngineDebugFlags.h"

// input debug flags

const bool DEBUG_CONTROLLER_INPUT = false;

// player debug flags

const bool DEBUG_PLAYER_POSITION = true; // visualizes player pos and posDelta
const bool DEBUG_PLAYER_MAP_COLLISION = false; // visualizes raycasting
const bool DEBUG_PLAYER_MOVE_STATE = true; // visualizes player move state
const bool DEBUG_PLAYER_ACTION_STATE = true; // visualizes player action state

// sword debug flags

const bool DEBUG_SWORD_POSITION = true;
const bool DEBUG_SWORD_STATE = true;

// LevelMap debug flags

const bool DEBUG_LEVEL_SCROLL_BOUNDS = false;

// tool debug flags

const bool DEBUG_ASSET_LOAD_AUTOMATION = false;

#endif
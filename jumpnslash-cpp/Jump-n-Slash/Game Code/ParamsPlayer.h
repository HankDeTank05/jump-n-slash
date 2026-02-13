#ifndef PARAMS_PLAYER_H
#define PARAMS_PLAYER_H

namespace Movement
{
	const float GROUNDED_HORIZONTAL_MOVE_SPEED = 100.0f; // TODO: make sure this parameter has asserts in LoadResources.cpp
	const float	AERIAL_HORIZONTAL_MOVE_SPEED = 100.f; // not currently in use
	const float GROUNDED_ACCELERATION = 0.f; // not currently in use
	const float GROUNDED_DECELERATION = 0.f; // not currently in use
	const float AERIAL_HORIZONTAL_ACCELERATION = 0.f; // not currently in use
	const float AERIAL_HORIZONTAL_DECELERATION = 0.f; // not currently in use

	const float MAX_JUMP_HEIGHT = 150.f; // TODO: make sure this parameter has asserts in LoadResources.cpp
	const float JUMP_RISING_SPEED = 400.f; // TODO: make sure this parameter has asserts in LoadResources.cpp
	
	const float PLAYER_GRAVITY = 10.f; // TODO: make sure this parameter has asserts in LoadResources.cpp
}

namespace Dash
{
	const float DASH_DISTANCE = 50.f; // not currently in use
	const float DASH_SPEED = 10.f; // not currently in use
	const float DASH_INVINCIBILITY_TIME = 1.f; // not currently in use
}

namespace SlashAtk
{
	const float SLASH_WINDUP_TIME = 0.f; // not currently in use
	const float SLASH_ACTIVE_TIME = 1.f; // TODO: make sure this parameter has asserts in LoadResources.cpp
	const float SLASH_RECOVERY_TIME = 0.f; // not currently in use
	const bool AERIAL_SLASH_ALLOWED = false; // not currently in use
	const float SLASH_GROUND_MOVE_DISTANCE = 0.f; // not currently in use
}

const float ANIMATION_FRAMERATE = 7.f; // TODO: remove this parameter

//const float MAX_JUMP_HOLD_TIME = 0.0f;

#endif
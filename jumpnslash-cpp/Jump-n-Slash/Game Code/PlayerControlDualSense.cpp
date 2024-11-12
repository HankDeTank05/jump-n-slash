#include "PlayerControlDualSense.h"

#include "../Engine Code/ControllerInputs.h"

#include "DesignerControls.h"

PlayerControlDualSense::PlayerControlDualSense(Player* pPlayer)
	: PlayerControlStrategy(pPlayer, ControlScheme::DualSense)
{
	// do nothing
}

void PlayerControlDualSense::GamepadBtnPressed(int gamepadIndex, int btnNum)
{
	DualSenseButton btn = static_cast<DualSenseButton>(btnNum);
	switch (btn)
	{
	case DS_GAME_JUMP:
		jump = true;
		break;
	case DS_GAME_SLASH_ATK:
		slashAtk = true;
		break;
	case DS_GAME_DREAM_ATK:
		dreamAtk = true;
		break;
	case DS_GAME_DASH:
		dash = true;
		break;
	case DS_GAME_PAUSE:
		assert(false);
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

void PlayerControlDualSense::GamepadBtnReleased(int gamepadIndex, int btnNum)
{
	DualSenseButton btn = static_cast<DualSenseButton>(btnNum);
	switch (btn)
	{
	case DS_GAME_JUMP:
		jump = false;
		break;
	case DS_GAME_SLASH_ATK:
		slashAtk = false;
		break;
	case DS_GAME_DREAM_ATK:
		dreamAtk = false;
		break;
	case DS_GAME_DASH:
		dash = false;
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

void PlayerControlDualSense::GamepadAxisMoved(int gamepadIndex, sf::Joystick::Axis axis, float axisState, float axisStateDelta)
{
	DualSenseAxis spAxis = static_cast<DualSenseAxis>(axis);
	switch (spAxis)
	{
	case DS_GAME_WALK:
	case DS_GAME_WALK_ALT:
		walk = axisState;
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

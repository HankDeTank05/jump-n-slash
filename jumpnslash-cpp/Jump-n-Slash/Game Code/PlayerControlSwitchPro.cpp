#include "PlayerControlSwitchPro.h"

#include "../Engine Code/ControllerInputs.h"

#include "DesignerControls.h"

PlayerControlSwitchPro::PlayerControlSwitchPro(Player* pPlayer)
	: PlayerControlStrategy(pPlayer, ControlScheme::SwitchPro)
{
	// do nothing
}

void PlayerControlSwitchPro::GamepadBtnPressed(int gamepadIndex, int btnNum)
{
	SwitchProButton btn = static_cast<SwitchProButton>(btnNum);
	switch (btn)
	{
	case SP_GAME_JUMP:
		jump = true;
		break;
	case SP_GAME_SLASH_ATK:
		slashAtk = true;
		break;
	case SP_GAME_DREAM_ATK:
		dreamAtk = true;
		break;
	case SP_GAME_DASH:
		dash = true;
		break;
	case SP_GAME_PAUSE:
		assert(false);
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

void PlayerControlSwitchPro::GamepadBtnReleased(int gamepadIndex, int btnNum)
{
	SwitchProButton btn = static_cast<SwitchProButton>(btnNum);
	switch (btn)
	{
	case SP_GAME_JUMP:
		jump = false;
		break;
	case SP_GAME_SLASH_ATK:
		slashAtk = false;
		break;
	case SP_GAME_DREAM_ATK:
		dreamAtk = false;
		break;
	case SP_GAME_DASH:
		dash = false;
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

void PlayerControlSwitchPro::GamepadAxisMoved(int gamepadIndex, sf::Joystick::Axis axis, float axisState, float axisStateDelta)
{
	SwitchProAxis spAxis = static_cast<SwitchProAxis>(axis);
	switch (spAxis)
	{
	case SP_GAME_WALK:
	case SP_GAME_WALK_ALT:
		walk = axisState;
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

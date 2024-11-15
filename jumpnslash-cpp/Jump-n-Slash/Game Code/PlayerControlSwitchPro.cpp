#include "PlayerControlSwitchPro.h"

#include "../Engine Code/ControllerInputs.h"

#include "ControlMapping.h"

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
	case SwitchPro::Game::JUMP:
		jump = true;
		break;
	case SwitchPro::Game::SLASH_ATK:
		slashAtk = true;
		break;
	case SwitchPro::Game::DREAM_ATK:
		dreamAtk = true;
		break;
	case SwitchPro::Game::DASH:
		dash = true;
		break;
	case SwitchPro::Game::PAUSE:
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
	case SwitchPro::Game::JUMP:
		jump = false;
		break;
	case SwitchPro::Game::SLASH_ATK:
		slashAtk = false;
		break;
	case SwitchPro::Game::DREAM_ATK:
		dreamAtk = false;
		break;
	case SwitchPro::Game::DASH:
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
	case SwitchPro::Game::WALK:
	case SwitchPro::Game::WALK_ALT:
		walk = axisState;
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

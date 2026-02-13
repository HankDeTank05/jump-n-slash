#include "PlayerControlDualSense.h"

#include "../Engine Code/ControllerInputs.h"

#include "ControlMapping.h"

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
	case DualSense::Game::JUMP:
		jump = true;
		break;
	case DualSense::Game::SLASH_ATK:
		slashAtk = true;
		break;
	case DualSense::Game::DREAM_ATK:
		dreamAtk = true;
		break;
	case DualSense::Game::DASH:
		dash = true;
		break;
	case DualSense::Game::PAUSE:
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
	case DualSense::Game::JUMP:
		jump = false;
		break;
	case DualSense::Game::SLASH_ATK:
		slashAtk = false;
		break;
	case DualSense::Game::DREAM_ATK:
		dreamAtk = false;
		break;
	case DualSense::Game::DASH:
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
	case DualSense::Game::WALK:
	case DualSense::Game::WALK_ALT:
		walk = axisState;
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

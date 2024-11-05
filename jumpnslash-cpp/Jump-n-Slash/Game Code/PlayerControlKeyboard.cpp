#include "PlayerControlKeyboard.h"

#include "DesignerControls.h"

PlayerControlKeyboard::PlayerControlKeyboard(Player* pPlayer)
	: PlayerControlStrategy(pPlayer, ControlScheme::Keyboard)
{
	// do nothing
}

void PlayerControlKeyboard::KeyPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
	case KB_JUMP:
		jump = true;
		break;
	case KB_WALK_LEFT:
		walk -= 1.f;
		if (walk < -1.f) walk = -1.f;
		break;
	case KB_WALK_RIGHT:
		walk += 1.f;
		if (walk > 1.f) walk = 1.f;
		break;
	case KB_SLASH_ATK:
		slashAtk = true;
		break;
	case KB_DREAM_ATK:
		dreamAtk = true;
		break;
	case KB_DASH:
		dash = true;
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

void PlayerControlKeyboard::KeyReleased(sf::Keyboard::Key key)
{
	switch (key)
	{
	case KB_JUMP:
		jump = false;
		break;
	case KB_WALK_LEFT:
		if (walk < 0.f) walk = 0.f;
		break;
	case KB_WALK_RIGHT:
		if (walk > 0.f) walk = 0.f;
		break;
	case KB_SLASH_ATK:
		slashAtk = false;
		break;
	case KB_DREAM_ATK:
		dreamAtk = false;
		break;
	case KB_DASH:
		dash = false;
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

#include "PlayerControlKeyboard.h"

// engine includes
//#include "../Engine Code/SceneManager.h"

// game includes
#include "DesignerControls.h"
#include "ControlSelection.h"
#include "GameManager.h"

PlayerControlKeyboard::PlayerControlKeyboard(Player* pPlayer)
	: PlayerControlStrategy(pPlayer, ControlScheme::Keyboard)
{
	// do nothing
}

void PlayerControlKeyboard::KeyPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
	case KB_GAME_JUMP:
		jump = true;
		break;
	case KB_GAME_WALK_LEFT:
		walk -= 1.f;
		if (walk < -1.f) walk = -1.f;
		break;
	case KB_GAME_WALK_RIGHT:
		walk += 1.f;
		if (walk > 1.f) walk = 1.f;
		break;
	case KB_GAME_SLASH_ATK:
		slashAtk = true;
		break;
	case KB_GAME_DREAM_ATK:
		dreamAtk = true;
		break;
	case KB_GAME_DASH:
		dash = true;
		break;
	case KB_GAME_PAUSE:
		//assert(false);
		GameManager::PauseGame();
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

void PlayerControlKeyboard::KeyReleased(sf::Keyboard::Key key)
{
	switch (key)
	{
	case KB_GAME_JUMP:
		jump = false;
		break;
	case KB_GAME_WALK_LEFT:
		if (walk < 0.f) walk = 0.f;
		break;
	case KB_GAME_WALK_RIGHT:
		if (walk > 0.f) walk = 0.f;
		break;
	case KB_GAME_SLASH_ATK:
		slashAtk = false;
		break;
	case KB_GAME_DREAM_ATK:
		dreamAtk = false;
		break;
	case KB_GAME_DASH:
		dash = false;
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

#include "PlayerControlKeyboard.h"

// engine includes
//#include "../Engine Code/SceneManager.h"

// game includes
#include "ControlMapping.h"
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
	case Keyboard::Game::JUMP:
		jump = true;
		break;
	case Keyboard::Game::WALK_LEFT:
		walk -= 1.f;
		if (walk < -1.f) walk = -1.f;
		break;
	case Keyboard::Game::WALK_RIGHT:
		walk += 1.f;
		if (walk > 1.f) walk = 1.f;
		break;
	case Keyboard::Game::SLASH_ATK:
		slashAtk = true;
		break;
	case Keyboard::Game::DREAM_ATK:
		dreamAtk = true;
		break;
	case Keyboard::Game::DASH:
		dash = true;
		break;
	case Keyboard::Game::PAUSE:
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
	case Keyboard::Game::JUMP:
		jump = false;
		break;
	case Keyboard::Game::WALK_LEFT:
		walk += 1.f;
		break;
	case Keyboard::Game::WALK_RIGHT:
		walk -= 1.f;
		break;
	case Keyboard::Game::SLASH_ATK:
		slashAtk = false;
		break;
	case Keyboard::Game::DREAM_ATK:
		dreamAtk = false;
		break;
	case Keyboard::Game::DASH:
		dash = false;
		break;
	default:
		assert(false); // crash if we don't recognize the input being received
	}
}

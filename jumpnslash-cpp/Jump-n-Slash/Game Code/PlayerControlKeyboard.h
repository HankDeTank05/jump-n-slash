#ifndef PLAYER_CONTROL_KEYBOARD_H
#define PLAYER_CONTROL_KEYBOARD_H

#include "PlayerControlStrategy.h"

// forward declarations
class Player;

class PlayerControlKeyboard : public PlayerControlStrategy
{
public:
	PlayerControlKeyboard() = delete;
	PlayerControlKeyboard(Player* pPlayer);
	PlayerControlKeyboard(const PlayerControlKeyboard& pck) = delete;
	PlayerControlKeyboard& operator=(const PlayerControlKeyboard& pck) = delete;
	virtual ~PlayerControlKeyboard() = default;

	virtual void KeyPressed(sf::Keyboard::Key key) override;
	virtual void KeyReleased(sf::Keyboard::Key key) override;
};

#endif
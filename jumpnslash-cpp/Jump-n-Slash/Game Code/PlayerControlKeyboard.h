#ifndef PLAYER_CONTROL_KEYBOARD_H
#define PLAYER_CONTROL_KEYBOARD_H

#include "PlayerControlStrategy.h"

class PlayerControlKeyboard : public PlayerControlStrategy
{
public:
	PlayerControlKeyboard();
	PlayerControlKeyboard(const PlayerControlKeyboard& pck) = delete;
	PlayerControlKeyboard& operator=(const PlayerControlKeyboard& pck) = delete;
	virtual ~PlayerControlKeyboard() = default;

	virtual void SendInputs() override;

	virtual void KeyPressed(sf::Keyboard::Key key) override;
	virtual void KeyReleased(sf::Keyboard::Key key) override;
};

#endif
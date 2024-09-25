#ifndef KEY_REGISTRATION_COMMAND_H
#define KEY_REGISTRATION_COMMAND_H

#include <SFML/Window/Keyboard.hpp>

#include "Command.h"
#include "InputEvent.h"

// forward declarations
class InputObject;

class KeyRegistrationCommand : public Command
{
public:
	KeyRegistrationCommand() = delete;
	KeyRegistrationCommand(InputObject* pInputable, sf::Keyboard::Key key, KeyEvent eventToReg);
	KeyRegistrationCommand(const KeyRegistrationCommand& krc);
	KeyRegistrationCommand& operator=(const KeyRegistrationCommand& krc);
	virtual ~KeyRegistrationCommand() = default;

	virtual void Execute() override;

private:
	InputObject* pInputable;
	sf::Keyboard::Key key;
	KeyEvent eventToReg;
};

#endif
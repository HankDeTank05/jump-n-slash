#ifndef KEY_DEREGISTRATION_COMMAND_H
#define KEY_DEREGISTRATION_COMMAND_H

#include <SFML/Window/Keyboard.hpp>

#include "Command.h"
#include "InputEvent.h"

// forward declarations
class InputObject;

class KeyDeregistrationCommand : public Command
{
public:
	KeyDeregistrationCommand() = delete;
	KeyDeregistrationCommand(InputObject* pInputable, sf::Keyboard::Key key, KeyEvent eventToDereg);
	KeyDeregistrationCommand(const KeyDeregistrationCommand& krc);
	KeyDeregistrationCommand& operator=(const KeyDeregistrationCommand& krc);
	virtual ~KeyDeregistrationCommand() = default;

	virtual void Execute() override;

private:
	InputObject* pInputable;
	sf::Keyboard::Key key;
	KeyEvent eventToDereg;
};

#endif
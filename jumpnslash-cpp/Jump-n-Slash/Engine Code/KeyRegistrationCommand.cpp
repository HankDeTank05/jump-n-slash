#include "KeyRegistrationCommand.h"

#include "InputObjectAttorney.h"

KeyRegistrationCommand::KeyRegistrationCommand(InputObject* _pInputable, sf::Keyboard::Key _key, KeyEvent _eventToReg)
	: pInputable(_pInputable),
	key(_key),
	eventToReg(_eventToReg)
{
	// do nothing
}

KeyRegistrationCommand::KeyRegistrationCommand(const KeyRegistrationCommand& krc)
	: pInputable(krc.pInputable),
	key(krc.key),
	eventToReg(krc.eventToReg)
{
	// do nothing
}

KeyRegistrationCommand& KeyRegistrationCommand::operator=(const KeyRegistrationCommand& krc)
{
	pInputable = krc.pInputable;
	key = krc.key;
	eventToReg = krc.eventToReg;

	return *this;
}

void KeyRegistrationCommand::Execute()
{
	InputObjectAttorney::Registration::RegisterKey(pInputable, key, eventToReg);
}

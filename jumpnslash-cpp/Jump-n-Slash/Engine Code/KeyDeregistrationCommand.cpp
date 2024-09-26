#include "KeyDeregistrationCommand.h"

#include "InputObjectAttorney.h"

KeyDeregistrationCommand::KeyDeregistrationCommand(InputObject* _pInputable, sf::Keyboard::Key _key, KeyEvent _eventToDereg)
	: pInputable(_pInputable),
	key(_key),
	eventToDereg(_eventToDereg)
{
	// do nothing
}

KeyDeregistrationCommand::KeyDeregistrationCommand(const KeyDeregistrationCommand& krc)
	: pInputable(krc.pInputable),
	key(krc.key),
	eventToDereg(krc.eventToDereg)
{
	// do nothing
}

KeyDeregistrationCommand& KeyDeregistrationCommand::operator=(const KeyDeregistrationCommand& krc)
{
	pInputable = krc.pInputable;
	key = krc.key;
	eventToDereg = krc.eventToDereg;

	return *this;
}

void KeyDeregistrationCommand::Execute()
{
	InputObjectAttorney::Registration::DeregisterKey(pInputable, key, eventToDereg);
}

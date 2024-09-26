#include "MouseBtnDeregistrationCommand.h"

#include "InputObjectAttorney.h"

MouseBtnDeregistrationCommand::MouseBtnDeregistrationCommand(InputObject* _pInputable, sf::Mouse::Button _btn, MouseEvent _eventToDereg)
	: pInputable(_pInputable),
	btn(_btn),
	eventToDereg(_eventToDereg)
{
	// do nothing
}

MouseBtnDeregistrationCommand::MouseBtnDeregistrationCommand(const MouseBtnDeregistrationCommand& mbdc)
	: pInputable(mbdc.pInputable),
	btn(mbdc.btn),
	eventToDereg(mbdc.eventToDereg)
{
	// do nothing
}

MouseBtnDeregistrationCommand& MouseBtnDeregistrationCommand::operator=(const MouseBtnDeregistrationCommand& mbdc)
{
	pInputable = mbdc.pInputable;
	btn = mbdc.btn;
	eventToDereg = mbdc.eventToDereg;

	return *this;
}

void MouseBtnDeregistrationCommand::Execute()
{
	InputObjectAttorney::Registration::DeregisterMouseBtn(pInputable, btn, eventToDereg);
}

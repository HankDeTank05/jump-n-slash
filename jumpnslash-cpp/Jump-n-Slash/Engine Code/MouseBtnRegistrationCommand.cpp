#include "MouseBtnRegistrationCommand.h"

#include "InputObjectAttorney.h"

MouseBtnRegistrationCommand::MouseBtnRegistrationCommand(InputObject* _pInputable, sf::Mouse::Button _btn, MouseEvent _eventToReg)
	: pInputable(_pInputable),
	btn(_btn),
	eventToReg(_eventToReg)
{
	// do nothing
}

MouseBtnRegistrationCommand::MouseBtnRegistrationCommand(const MouseBtnRegistrationCommand& mbrc)
	: pInputable(mbrc.pInputable),
	btn(mbrc.btn),
	eventToReg(mbrc.eventToReg)
{
	// do nothing
}

MouseBtnRegistrationCommand& MouseBtnRegistrationCommand::operator=(const MouseBtnRegistrationCommand& mbrc)
{
	pInputable = mbrc.pInputable;
	btn = mbrc.btn;
	eventToReg = mbrc.eventToReg;

	return *this;
}

void MouseBtnRegistrationCommand::Execute()
{
	InputObjectAttorney::Registration::RegisterMouseBtn(pInputable, btn, eventToReg);
}

#include "MouseBtnListener.h"

#include "InputObjectAttorney.h"

MouseBtnListener::MouseBtnListener(sf::Mouse::Button _btn)
	: btn(_btn),
	prevState(false),
	notifyOnPress(),
	notifyOnRelease()
{
	// do nothing
}

void MouseBtnListener::ProcessMouseBtnEvent()
{
	bool currState = sf::Mouse::isButtonPressed(btn);

	if (currState != prevState)
	{
		if (prevState == false && currState == true)
		{
			for (NotifyList::iterator it = notifyOnPress.begin(); it != notifyOnPress.end(); it++)
			{
				InputObjectAttorney::MouseEvents::MouseBtnPressed(*it, btn);
			}
		}
		else if (prevState == true && currState == false)
		{
			for (NotifyList::iterator it = notifyOnRelease.begin(); it != notifyOnRelease.end(); it++)
			{
				InputObjectAttorney::MouseEvents::MouseBtnReleased(*it, btn);
			}
		}
	}

	prevState = currState;
}

void MouseBtnListener::Register(InputObject* pInputable, MouseEvent eventToReg)
{
	switch (eventToReg)
	{
	case MouseEvent::BtnPress:
		notifyOnPress.push_back(pInputable);
		break;
	case MouseEvent::BtnRelease:
		notifyOnRelease.push_back(pInputable);
		break;
	default:
		assert(false); // crash if we don't know what the event is
	}
}

void MouseBtnListener::Deregister(InputObject* pInputable, MouseEvent eventToDereg)
{
	switch (eventToDereg)
	{
	case MouseEvent::BtnPress:
		notifyOnPress.remove(pInputable);
		break;
	case MouseEvent::BtnRelease:
		notifyOnRelease.remove(pInputable);
		break;
	default:
		assert(false); // crash if we don't know what the event is
	}
}

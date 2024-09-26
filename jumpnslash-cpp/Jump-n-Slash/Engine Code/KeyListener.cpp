#include "KeyListener.h"

#include "InputObjectAttorney.h"

KeyListener::KeyListener(sf::Keyboard::Key _key)
	: key(_key),
	prevState(false),
	notifyOnPress(),
	notifyOnRelease()
{
	// do nothing
}

void KeyListener::ProcessKeyEvent()
{
	bool currState = sf::Keyboard::isKeyPressed(key);

	if (prevState == false && currState == true)
	{
		// key press
		for (NotifyList::iterator it = notifyOnPress.begin(); it != notifyOnPress.end(); it++)
		{
			InputObjectAttorney::KeyEvents::KeyPressed(*it, key);
		}
	}
	else if (prevState == true && currState == false)
	{
		// key release
		for (NotifyList::iterator it = notifyOnRelease.begin(); it != notifyOnRelease.end(); it++)
		{
			InputObjectAttorney::KeyEvents::KeyReleased(*it, key);
		}
	}

	prevState = currState;
}

void KeyListener::Register(InputObject* pInputable, KeyEvent eventToReg)
{

	switch (eventToReg)
	{
	case KeyEvent::KeyPress:
		notifyOnPress.push_back(pInputable);
		break;
	case KeyEvent::KeyRelease:
		notifyOnRelease.push_back(pInputable);
		break;
	default:
		assert(false); // crash if we don't know what the event is
	}
}

void KeyListener::Deregister(InputObject* pInputable, KeyEvent eventToDereg)
{
	switch (eventToDereg)
	{
	case KeyEvent::KeyPress:
		notifyOnPress.remove(pInputable);
		break;
	case KeyEvent::KeyRelease:
		notifyOnRelease.remove(pInputable);
		break;
	default:
		assert(false); // crash if we don't know what the event is
	}
}

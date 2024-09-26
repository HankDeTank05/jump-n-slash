#include "InputManager.h"

#include "KeyListener.h"

InputManager::InputManager()
	: keyTracker(),
	mouseBtnTracker()
{
	// do nothing
}

InputManager::~InputManager()
{
	for (KeyTracker::iterator it = keyTracker.begin(); it != keyTracker.end(); it++)
	{
		delete it->second;
	}

	for (MouseBtnTracker::iterator it = mouseBtnTracker.begin(); it != mouseBtnTracker.end(); it++)
	{
		delete it->second;
	}
}

void InputManager::RegisterKey(sf::Keyboard::Key key, InputObject* pInputable, KeyEvent eventToReg)
{
	if (keyTracker.count(key) == 0)
	{
		// make new KeyListener
		keyTracker.emplace(key, new KeyListener(key));
	}

	keyTracker.at(key)->Register(pInputable, eventToReg);
}

void InputManager::DeregisterKey(sf::Keyboard::Key key, InputObject* pInputable, KeyEvent eventToDereg)
{
	assert(false);
}

void InputManager::RegisterMouseBtn(sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToReg)
{
	assert(false);
}

void InputManager::DeregisterMouseBtn(sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToDereg)
{
	assert(false);
}

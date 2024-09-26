#include "InputManager.h"

#include "KeyListener.h"
#include "MouseBtnListener.h"

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

void InputManager::ProcessKeyboardEvents()
{
	for (KeyTracker::iterator it = keyTracker.begin(); it != keyTracker.end(); it++)
	{
		it->second->ProcessKeyEvent();
	}
}

void InputManager::ProcessMouseEvents()
{
	for (MouseBtnTracker::iterator it = mouseBtnTracker.begin(); it != mouseBtnTracker.end(); it++)
	{
		it->second->ProcessMouseBtnEvent();
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
	assert(keyTracker.count(key) > 0); // crash if you try to deregister something that isn't registered

	keyTracker.at(key)->Deregister(pInputable, eventToDereg);
}

void InputManager::RegisterMouseBtn(sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToReg)
{
	if (mouseBtnTracker.count(btn) == 0)
	{
		// make new MouseBtnListener
		mouseBtnTracker.emplace(btn, new MouseBtnListener(btn));
	}

	mouseBtnTracker.at(btn)->Register(pInputable, eventToReg);
}

void InputManager::DeregisterMouseBtn(sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToDereg)
{
	assert(mouseBtnTracker.count(btn) > 0); // crash if you try to deregister something that isn't registered

	mouseBtnTracker.at(btn)->Deregister(pInputable, eventToDereg);
}

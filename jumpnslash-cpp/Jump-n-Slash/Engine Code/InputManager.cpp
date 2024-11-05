#include "InputManager.h"

#include "KeyListener.h"
#include "MouseBtnListener.h"
#include "MouseCursorListener.h"
#include "GamepadBtnListener.h"
#include "GamepadAxisListener.h"

InputManager::InputManager()
	: keyTracker(),
	mouseBtnTracker(),
	pCursorListener(new MouseCursorListener())
{
	// do nothing
}

InputManager::~InputManager()
{
	delete pCursorListener;

	for (GamepadAxisTracker::iterator it = gpAxisTracker.begin(); it != gpAxisTracker.end(); it++)
	{
		for (std::map<sf::Joystick::Axis, GamepadAxisListener*>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			delete it2->second;
		}
	}

	for (GamepadBtnTracker::iterator it = gpBtnTracker.begin(); it != gpBtnTracker.end(); it++)
	{
		for (std::map<int, GamepadBtnListener*>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			delete it2->second;
		}
	}

	for (MouseBtnTracker::iterator it = mouseBtnTracker.begin(); it != mouseBtnTracker.end(); it++)
	{
		delete it->second;
	}

	for (KeyTracker::iterator it = keyTracker.begin(); it != keyTracker.end(); it++)
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
	pCursorListener->ProcessCursorEvent();
	for (MouseBtnTracker::iterator it = mouseBtnTracker.begin(); it != mouseBtnTracker.end(); it++)
	{
		it->second->ProcessMouseBtnEvent();
	}
}

void InputManager::ProcessGamepadEvents()
{
	for (GamepadBtnTracker::iterator it = gpBtnTracker.begin(); it != gpBtnTracker.end(); it++)
	{
		int gamepadIndex = it->first;
		std::map<int, GamepadBtnListener*>& listenerMap = gpBtnTracker.at(gamepadIndex);
		for (std::map<int, GamepadBtnListener*>::iterator it2 = listenerMap.begin(); it2 != listenerMap.end(); it2++)
		{
			it2->second->ProcessGamepadBtnEvent();
		}
	}
	for (GamepadAxisTracker::iterator it = gpAxisTracker.begin(); it != gpAxisTracker.end(); it++)
	{
		int gamepadIndex = it->first;
		std::map<sf::Joystick::Axis, GamepadAxisListener*>& listenerMap = gpAxisTracker.at(gamepadIndex);
		for (std::map<sf::Joystick::Axis, GamepadAxisListener*>::iterator it2 = listenerMap.begin(); it2 != listenerMap.end(); it2++)
		{
			it2->second->ProcessGamepadAxisEvent();
		}
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

void InputManager::RegisterMouseCursor(InputObject* pInputable)
{
	pCursorListener->Register(pInputable);
}

void InputManager::DeregisterMouseCursor(InputObject* pInputable)
{
	pCursorListener->Deregister(pInputable);
}

void InputManager::RegisterGamepadBtn(int gamepadIndex, int btnNum, InputObject* pInputable, GamepadBtnEvent eventToReg)
{
	if (gpBtnTracker.count(gamepadIndex) == 0)
	{
		// make new submap
		gpBtnTracker.emplace(gamepadIndex, std::map<int, GamepadBtnListener*>());
	}

	if (gpBtnTracker.count(gamepadIndex) > 0 && gpBtnTracker.at(gamepadIndex).count(btnNum) == 0)
	{
		// make new GamepadBtnListener
		gpBtnTracker.at(gamepadIndex).emplace(btnNum, new GamepadBtnListener(gamepadIndex, btnNum));
	}

	gpBtnTracker.at(gamepadIndex).at(btnNum)->Register(pInputable, eventToReg);
}

void InputManager::DeregisterGamepadBtn(int gamepadIndex, int btnNum, InputObject* pInputable, GamepadBtnEvent eventToDereg)
{
	assert(gpBtnTracker.count(gamepadIndex) > 0); // gamepadIndex not found
	assert(gpBtnTracker.at(gamepadIndex).count(btnNum) > 0); // btnNum not found

	gpBtnTracker.at(gamepadIndex).at(btnNum)->Deregister(pInputable, eventToDereg);
}

void InputManager::RegisterGamepadAxis(int gamepadIndex, sf::Joystick::Axis axis, InputObject* pInputable, GamepadAxisEvent eventToReg)
{
	if (gpAxisTracker.count(gamepadIndex) == 0)
	{
		// make new submap
		gpAxisTracker.emplace(gamepadIndex, std::map<sf::Joystick::Axis, GamepadAxisListener*>());
	}

	if (gpAxisTracker.count(gamepadIndex) > 0 && gpAxisTracker.at(gamepadIndex).count(axis) == 0)
	{
		// make new GamepadAxisListener
		gpAxisTracker.at(gamepadIndex).emplace(axis, new GamepadAxisListener(gamepadIndex, axis));
	}

	gpAxisTracker.at(gamepadIndex).at(axis)->Register(pInputable, eventToReg);
}

void InputManager::DeregisterGamepadAxis(int gamepadIndex, sf::Joystick::Axis axis, InputObject* pInputable, GamepadAxisEvent eventToDereg)
{
	assert(gpAxisTracker.count(gamepadIndex) > 0); // gamepadIndex not found
	assert(gpAxisTracker.at(gamepadIndex).count(axis) > 0); // axis not found

	gpAxisTracker.at(gamepadIndex).at(axis)->Deregister(pInputable, eventToDereg);
}

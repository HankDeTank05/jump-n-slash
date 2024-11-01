#ifndef GAMEPAD_BTN_LISTENER_H
#define GAMEPAD_BTN_LISTENER_H

#include <list>

#include <SFML/Window/Joystick.hpp>

#include "InputEvent.h"

// forward declarations
class InputObject;

class GamepadBtnListener
{
public:
	GamepadBtnListener() = delete;
	GamepadBtnListener(int gamepadIndex, int btnNum);
	GamepadBtnListener(const GamepadBtnListener& gbl) = delete;
	GamepadBtnListener& operator=(const GamepadBtnListener& gbl) = delete;
	virtual ~GamepadBtnListener() = default;

	void ProcessGamepadBtnEvent();

	using NotifyList = std::list<InputObject*>;

	void Register(InputObject* pInputable, GamepadBtnEvent eventToReg);
	void Deregister(InputObject* pInputable, GamepadBtnEvent eventToDereg);

private:
	int gamepadIndex;
	int btnNum;
	bool prevState;
	NotifyList notifyOnPress;
	NotifyList notifyOnRelease;
};

#endif
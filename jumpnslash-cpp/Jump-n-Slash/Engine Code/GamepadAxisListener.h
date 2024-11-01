#ifndef GAMEPAD_AXIS_LISTENER_H
#define GAMEPAD_AXIS_LISTENER_H

#include <list>

#include <SFML/Window/Joystick.hpp>

#include "InputEvent.h"

// forward declarations
class InputObject;

class GamepadAxisListener
{
public:
	GamepadAxisListener() = delete;
	GamepadAxisListener(int gamepadIndex, sf::Joystick::Axis axis);
	GamepadAxisListener(const GamepadAxisListener& gal) = delete;
	GamepadAxisListener& operator=(const GamepadAxisListener& gal) = delete;
	virtual ~GamepadAxisListener() = default;

	void ProcessGamepadAxisEvent();

	using NotifyList = std::list<InputObject*>;

	void Register(InputObject* pInputable, GamepadAxisEvent eventToReg);
	void Deregister(InputObject* pInputable, GamepadAxisEvent eventToDereg);

private:
	int gamepadIndex;
	sf::Joystick::Axis axis;
	float prevState;
	NotifyList notifyOnPositive;
	NotifyList notifyOnNegative;
};

#endif
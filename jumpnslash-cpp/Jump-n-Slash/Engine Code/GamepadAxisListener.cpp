#include "GamepadAxisListener.h"

#include "InputObjectAttorney.h"

GamepadAxisListener::GamepadAxisListener(int _gamepadIndex, sf::Joystick::Axis _axis)
	: gamepadIndex(_gamepadIndex),
	axis(_axis),
	prevState(0.f),
	notifyOnPositive(),
	notifyOnNegative()
{
	// do nothing
}

void GamepadAxisListener::ProcessGamepadAxisEvent()
{
	assert(sf::Joystick::isConnected(0));

	float currState = sf::Joystick::getAxisPosition(gamepadIndex, axis) * 0.01f; // divide by 100 so that inputs are in the range [-1, 1]

	if (currState != prevState)
	{
		if (currState > prevState)
		{
			for (NotifyList::iterator it = notifyOnPositive.begin(); it != notifyOnPositive.end(); it++)
			{
				InputObjectAttorney::GamepadEvents::GamepadAxisMoved(*it, gamepadIndex, axis, currState, currState - prevState);
			}
		}
		else if (currState < prevState)
		{
			for (NotifyList::iterator it = notifyOnNegative.begin(); it != notifyOnNegative.end(); it++)
			{
				InputObjectAttorney::GamepadEvents::GamepadAxisMoved(*it, gamepadIndex, axis, currState, currState - prevState);
			}
		}
		else
		{
			assert(false); // how tf...?
		}
	}

	prevState = currState;
}

void GamepadAxisListener::Register(InputObject* pInputable, GamepadAxisEvent eventToReg)
{
	switch (eventToReg)
	{
	case GamepadAxisEvent::AxisInputAny:
	case GamepadAxisEvent::AxisInputPositive:
		notifyOnPositive.push_back(pInputable);
		if (eventToReg == GamepadAxisEvent::AxisInputPositive) break;
	case GamepadAxisEvent::AxisInputNegative:
		notifyOnNegative.push_back(pInputable);
		break;
	default:
		assert(false); // crash if we don't know what the event is
	}
}

void GamepadAxisListener::Deregister(InputObject* pInputable, GamepadAxisEvent eventToDereg)
{
	switch (eventToDereg)
	{
	case GamepadAxisEvent::AxisInputAny:
	case GamepadAxisEvent::AxisInputPositive:
		notifyOnPositive.remove(pInputable);
		if (eventToDereg == GamepadAxisEvent::AxisInputPositive) break;
	case GamepadAxisEvent::AxisInputNegative:
		notifyOnNegative.remove(pInputable);
		break;
	default:
		assert(false);
	}
}

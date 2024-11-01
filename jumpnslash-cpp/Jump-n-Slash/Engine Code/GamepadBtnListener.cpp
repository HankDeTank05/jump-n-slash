#include "GamepadBtnListener.h"

#include "InputObjectAttorney.h"

GamepadBtnListener::GamepadBtnListener(int _gamepadIndex, int _btnNum)
	: gamepadIndex(_gamepadIndex),
	btnNum(_btnNum),
	prevState(false),
	notifyOnPress(),
	notifyOnRelease()
{
	// do nothing
}

void GamepadBtnListener::ProcessGamepadBtnEvent()
{
	bool currState = sf::Joystick::isButtonPressed(gamepadIndex, btnNum);

	if (currState != prevState)
	{
		if (prevState == false && currState == true)
		{
			// btn press
			for (NotifyList::iterator it = notifyOnPress.begin(); it != notifyOnPress.end(); it++)
			{
				InputObjectAttorney::GamepadEvents::GamepadBtnPressed(*it, gamepadIndex, btnNum);
			}
		}
		else if (prevState == true && currState == false)
		{
			// btn release
			for (NotifyList::iterator it = notifyOnRelease.begin(); it != notifyOnRelease.end(); it++)
			{
				InputObjectAttorney::GamepadEvents::GamepadBtnReleased(*it, gamepadIndex, btnNum);
			}
		}
		else
		{
			assert(false); // how tf...?
		}
	}

	prevState = currState;
}

void GamepadBtnListener::Register(InputObject* pInputable, GamepadBtnEvent eventToReg)
{
	switch (eventToReg)
	{
	case GamepadBtnEvent::BtnPress:
		notifyOnPress.push_back(pInputable);
		break;
	case GamepadBtnEvent::BtnRelease:
		notifyOnRelease.push_back(pInputable);
		break;
	default:
		assert(false); // crash if we don't know what the event is
	}
}

void GamepadBtnListener::Deregister(InputObject* pInputable, GamepadBtnEvent eventToDereg)
{
	switch (eventToDereg)
	{
	case GamepadBtnEvent::BtnPress:
		notifyOnPress.remove(pInputable);
		break;
	case GamepadBtnEvent::BtnRelease:
		notifyOnRelease.remove(pInputable);
		break;
	default:
		assert(false); // crash if we don't know what the event is
	}
}

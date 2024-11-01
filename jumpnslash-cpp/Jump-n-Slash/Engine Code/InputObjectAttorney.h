#ifndef INPUT_OBJECT_ATTORNEY_H
#define INPUT_OBJECT_ATTORNEY_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>

#include "InputEvent.h"

// forward declarations
class InputObject;

class InputObjectAttorney
{
public:
	class Registration
	{
	private:
		friend class KeyRegistrationCommand;
		friend class KeyDeregistrationCommand;
		static void RegisterKey(InputObject* pInputable, sf::Keyboard::Key key, KeyEvent eventToReg);
		static void DeregisterKey(InputObject* pInputable, sf::Keyboard::Key key, KeyEvent eventToDereg);

		friend class MouseBtnRegistrationCommand;
		friend class MouseBtnDeregistrationCommand;
		static void RegisterMouseBtn(InputObject* pInputable, sf::Mouse::Button btn, MouseEvent eventToReg);
		static void DeregisterMouseBtn(InputObject* pInputable, sf::Mouse::Button btn, MouseEvent eventToDereg);

		friend class MouseCursorRegistrationCommand;
		friend class MouseCursorDeregistrationCommand;
		static void RegisterMouseCursor(InputObject* pInputable);
		static void DeregisterMouseCursor(InputObject* pInputable);

		friend class GamepadBtnRegistrationCommand;
		friend class GamepadBtnDeregistrationCommand;
		static void RegisterGamepadBtn(InputObject* pInputable, int gamepadIndex, int btnNum, GamepadBtnEvent eventToReg);
		static void DeregisterGamepadBtn(InputObject* pInputable, int gamepadIndex, int btnNum, GamepadBtnEvent eventToDereg);

		friend class GamepadAxisRegistrationCommand;
		friend class GamepadAxisDeregistrationCommand;
		static void RegisterGamepadAxis(InputObject* pInputable, int gamepadIndex, sf::Joystick::Axis axis, GamepadAxisEvent eventToReg);
		static void DeregisterGamepadAxis(InputObject* pInputable, int gamepadIndex, sf::Joystick::Axis axis, GamepadAxisEvent eventToDereg);
	};

	class KeyEvents
	{
	private:
		friend class KeyListener;
		static void KeyPressed(InputObject* pInputable, sf::Keyboard::Key key);
		static void KeyReleased(InputObject* pInputable, sf::Keyboard::Key key);
	};

	class MouseEvents
	{
	private:
		friend class MouseBtnListener;
		friend class MouseCursorListener;
		static void MouseBtnPressed(InputObject* pInputable, sf::Mouse::Button btn);
		static void MouseBtnReleased(InputObject* pInputable, sf::Mouse::Button btn);
		static void MouseCursorMoved(InputObject* pInputable, sf::Vector2i pos, sf::Vector2i delta);
	};

	class GamepadEvents
	{
	private:
		friend class GamepadBtnListener;
		friend class GamepadAxisListener;
		static void GamepadBtnPressed(InputObject* pInputable, int gamepadIndex, int btnNum);
		static void GamepadBtnReleased(InputObject* pInputable, int gamepadIndex, int btnNum);
		static void GamepadAxisMoved(InputObject* pInputable, int gamepadIndex, sf::Joystick::Axis axis, float axisState, float axisStateDelta);
	};
};

#endif
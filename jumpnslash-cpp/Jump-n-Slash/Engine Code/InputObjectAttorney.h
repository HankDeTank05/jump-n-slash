#ifndef INPUT_OBJECT_ATTORNEY_H
#define INPUT_OBJECT_ATTORNEY_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

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
};

#endif
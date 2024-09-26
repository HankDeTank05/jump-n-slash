#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <map>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>

#include "InputEvent.h"

// forward declarations
class InputObject;
class KeyListener;
class MouseBtnListener;

class InputManager
{
public:
	InputManager();
	InputManager(const InputManager& im) = delete;
	InputManager& operator=(const InputManager& im) = delete;
	virtual ~InputManager();

	void ProcessKeyboardEvents();
	void ProcessMouseEvents();
	//void ProcessGamepadEvents();

	using KeyTracker = std::map<sf::Keyboard::Key, KeyListener*>;
	void RegisterKey(sf::Keyboard::Key key, InputObject* pInputable, KeyEvent eventToReg);
	void DeregisterKey(sf::Keyboard::Key key, InputObject* pInputable, KeyEvent eventToDereg);

	using MouseBtnTracker = std::map<sf::Mouse::Button, MouseBtnListener*>;
	void RegisterMouseBtn(sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToReg);
	void DeregisterMouseBtn(sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToDereg);

private:
	KeyTracker keyTracker;
	MouseBtnTracker mouseBtnTracker;
};

#endif
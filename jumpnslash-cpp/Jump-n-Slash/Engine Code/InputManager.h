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
class MouseCursorListener;
class GamepadBtnListener;
class GamepadAxisListener;

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

	void RegisterMouseCursor(InputObject* pInputable);
	void DeregisterMouseCursor(InputObject* pInputable);

	using GamepadBtnTracker = std::map<int, std::map<int, GamepadBtnListener*>>;
	void RegisterGamepadBtn(int gamepadIndex, int btnNum, InputObject* pInputable, GamepadBtnEvent eventToReg);
	void DeregisterGamepadBtn(int gamepadIndex, int btnNum, InputObject* pInputable, GamepadBtnEvent eventToDereg);

	using GamepadAxisTracker = std::map<int, std::map<sf::Joystick::Axis, GamepadAxisListener*>>;
	void RegisterGamepadAxis(int gamepadIndex, sf::Joystick::Axis axis, InputObject* pInputable, GamepadAxisEvent eventToReg);
	void DeregisterGamepadAxis(int gamepadIndex, sf::Joystick::Axis axis, InputObject* pInputable, GamepadAxisEvent eventToDereg);

private:
	KeyTracker keyTracker;
	MouseBtnTracker mouseBtnTracker;
	MouseCursorListener* pCursorListener;
	GamepadBtnTracker gpBtnTracker;
	GamepadAxisTracker gpAxisTracker;
};

#endif
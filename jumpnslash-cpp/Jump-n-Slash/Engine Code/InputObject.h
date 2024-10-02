#ifndef INPUT_OBJECT_H
#define INPUT_OBJECT_H

#include <map>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>

#include "InputEvent.h"
#include "RegistrationState.h"

// forward declarations
class KeyRegistrationCommand;
class KeyDeregistrationCommand;
class MouseBtnRegistrationCommand;
class MouseBtnDeregistrationCommand;
class MouseCursorRegistrationCommand;
class MouseCursorDeregistrationCommand;

class InputObject
{
public:
	InputObject();
	InputObject(const InputObject& io) = delete;
	InputObject& operator=(const InputObject& io) = delete;
	virtual ~InputObject();

protected:
	friend class InputObjectAttorney;

	virtual void KeyPressed(sf::Keyboard::Key key); // TODO: documentation for InputObject::KeyPressed
	virtual void KeyReleased(sf::Keyboard::Key key); // TODO: documentation for InputObject::KeyReleased

	virtual void MouseBtnPressed(sf::Mouse::Button btn); // TODO: documentation for InputObject::MouseButtonPressed
	virtual void MouseBtnReleased(sf::Mouse::Button btn); // TODO: documentation for InputObject::MouseButtonReleased
	virtual void MouseCursorMoved(sf::Vector2i pos, sf::Vector2i delta); // TODO: documentation for InputObject::MouseCursorMoved
	// TODO: figure out mouse wheel inputs

	// TODO: figure out gamepad button inputs
	// TODO: figure out gamepad stick inputs

	void RequestKeyRegistration(sf::Keyboard::Key key, KeyEvent eventToReg); // TODO: documentation for InputObject::RequestKeyRegistration
	void RequestKeyDeregistration(sf::Keyboard::Key key, KeyEvent eventToDereg); // TODO: documentation for InputObject::RequestKeyDeregistration

	void RequestMouseBtnRegistration(sf::Mouse::Button btn, MouseEvent eventToReg); // TODO: documentation for InputObject::RequestMouseBtnRegistration
	void RequestMouseBtnDeregistration(sf::Mouse::Button btn, MouseEvent eventToDereg); // TODO: documentation for InputObject::RequestMouseBtnDeregistration
	void RequestMouseCursorRegistration(); // TODO: documentation for InputObject::RequestMouseCursorRegistration
	void RequestMouseCursorDeregistration(); // TODO: documentation for InputObject::RequestMouseCursorDeregistration

private:
	void RegisterKey(sf::Keyboard::Key key, KeyEvent eventToReg);
	void DeregisterKey(sf::Keyboard::Key key, KeyEvent eventToDereg);

	void RegisterMouseBtn(sf::Mouse::Button btn, MouseEvent eventToReg);
	void DeregisterMouseBtn(sf::Mouse::Button btn, MouseEvent eventToDereg);
	void RegisterMouseCursor();
	void DeregisterMouseCursor();

	struct KeyRegistrationData
	{
		RegistrationState regState;
		KeyRegistrationCommand* pRegCmd;
		KeyDeregistrationCommand* pDeregCmd;
	};

	using KeyTrackerID = std::pair<sf::Keyboard::Key, KeyEvent>;
	using KeyRegTracker = std::map<KeyTrackerID, KeyRegistrationData>;

	struct MouseBtnRegistrationData
	{
		RegistrationState regState;
		MouseBtnRegistrationCommand* pRegCmd;
		MouseBtnDeregistrationCommand* pDeregCmd;
	};

	using MouseBtnTrackerID = std::pair<sf::Mouse::Button, MouseEvent>;
	using MouseBtnRegTracker = std::map<MouseBtnTrackerID, MouseBtnRegistrationData>;

	struct MouseCursorRegistrationData
	{
		RegistrationState regState;
		MouseCursorRegistrationCommand* pRegCmd;
		MouseCursorDeregistrationCommand* pDeregCmd;
	};

private:
	KeyRegTracker keyTracker;
	MouseBtnRegTracker mouseBtnTracker;
	MouseCursorRegistrationData mouseCursorRegData;
};

#endif
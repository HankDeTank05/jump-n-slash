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

class InputObject
{
public:
	InputObject() = default;
	InputObject(const InputObject& io) = delete;
	InputObject& operator=(const InputObject& io) = delete;
	virtual ~InputObject();

protected:
	friend class InputObjectAttorney;

	virtual void KeyPressed(sf::Keyboard::Key key); // TODO: documentation for InputObject::KeyPressed
	virtual void KeyReleased(sf::Keyboard::Key key); // TODO: documentation for InputObject::KeyReleased

	virtual void MouseBtnPressed(sf::Mouse::Button btn); // TODO: documentation for InputObject::MouseButtonPressed
	virtual void MouseBtnReleased(sf::Mouse::Button btn); // TODO: documentation for InputObject::MouseButtonReleased

	// TODO: figure out mouse position inputs
	// TODO: figure out mouse wheel inputs

	// TODO: figure out joystick button inputs
	// TODO: figure out joystick stick inputs

	void EnqueueForKeyRegistration(sf::Keyboard::Key key, KeyEvent eventToReg);
	void EnqueueForKeyDeregistration(sf::Keyboard::Key key, KeyEvent eventToDereg);

	void EnqueueForMouseBtnRegistration(sf::Mouse::Button btn, MouseEvent eventToReg);
	void EnqueueForMouseBtnDeregistration(sf::Mouse::Button btn, MouseEvent eventToDereg);

private:
	void RegisterKey(sf::Keyboard::Key key, KeyEvent eventToReg);
	void DeregisterKey(sf::Keyboard::Key key, KeyEvent eventToDereg);

	void RegisterMouseBtn(sf::Mouse::Button btn, MouseEvent eventToReg);
	void DeregisterMouseBtn(sf::Mouse::Button btn, MouseEvent eventToDereg);

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
	using MouseRegTracker = std::map<MouseBtnTrackerID, MouseBtnRegistrationData>;

private:
	KeyRegTracker keyTracker;
	MouseRegTracker mouseBtnTracker;
};

#endif
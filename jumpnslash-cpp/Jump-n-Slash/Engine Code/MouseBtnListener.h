#ifndef MOUSE_BTN_LISTENER_H
#define MOUSE_BTN_LISTENER_H

#include <list>

#include <SFML/Window/Mouse.hpp>

#include "InputEvent.h"

// forward declarations
class InputObject;

class MouseBtnListener
{
public:
	MouseBtnListener() = delete;
	MouseBtnListener(sf::Mouse::Button btn);
	MouseBtnListener(const MouseBtnListener& mbl) = delete;
	MouseBtnListener& operator=(const MouseBtnListener& mbl) = delete;
	virtual ~MouseBtnListener() = default;

	void ProcessMouseBtnEvent();

	using NotifyList = std::list<InputObject*>;

	void Register(InputObject* pInputable, MouseEvent eventToReg);
	void Deregister(InputObject* pInputable, MouseEvent eventToDereg);

private:
	sf::Mouse::Button btn;
	bool prevState;
	NotifyList notifyOnPress;
	NotifyList notifyOnRelease;
};

#endif
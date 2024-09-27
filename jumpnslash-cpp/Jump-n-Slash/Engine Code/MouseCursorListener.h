#ifndef MOUSE_CURSOR_LISTENER_H
#define MOUSE_CURSOR_LISTENER_H

#include <list>

#include <SFML/Window/Mouse.hpp>

// forward declarations
class InputObject;

class MouseCursorListener
{
public:
	MouseCursorListener();
	MouseCursorListener(const MouseCursorListener& mcl) = delete;
	MouseCursorListener& operator=(const MouseCursorListener& mcl) = delete;
	virtual ~MouseCursorListener();

	void ProcessCursorEvent();

	using NotifyList = std::list<InputObject*>;

	void Register(InputObject* pInputable);
	void Deregister(InputObject* pInputable);

private:
	sf::Vector2i prevPos;
	NotifyList notifyOnMove;
};

#endif
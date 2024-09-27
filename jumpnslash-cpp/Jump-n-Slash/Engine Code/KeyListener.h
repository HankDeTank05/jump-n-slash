#ifndef KEY_LISTENER_H
#define KEY_LISTENER_H

#include <list>

#include <SFML/Window/Keyboard.hpp>

#include "InputEvent.h"

// forward declarations
class InputObject;

class KeyListener
{
public:
	KeyListener() = delete;
	KeyListener(sf::Keyboard::Key key);
	KeyListener(const KeyListener& kl) = delete;
	KeyListener& operator=(const KeyListener& kl) = delete;
	virtual ~KeyListener() = default;

	void ProcessKeyEvent();

	using NotifyList = std::list<InputObject*>;

	void Register(InputObject* pInputable, KeyEvent eventToReg);
	void Deregister(InputObject* pInputable, KeyEvent eventToDereg);

private:
	sf::Keyboard::Key key;
	bool prevState;
	NotifyList notifyOnPress;
	NotifyList notifyOnRelease;
};

#endif
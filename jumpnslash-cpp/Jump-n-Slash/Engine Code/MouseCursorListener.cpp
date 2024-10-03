#include "MouseCursorListener.h"

#include "InputObjectAttorney.h"
#include "EngineAttorney.h"

MouseCursorListener::MouseCursorListener()
	: prevPos(sf::Mouse::getPosition()),
	notifyOnMove()
{
	// do nothing
}

MouseCursorListener::~MouseCursorListener()
{
	// do nothing??
}

void MouseCursorListener::ProcessCursorEvent()
{
	sf::Vector2i currPos = sf::Mouse::getPosition(EngineAttorney::GameWindow::GetWindow());

	if (currPos != prevPos)
	{
		for (NotifyList::iterator it = notifyOnMove.begin(); it != notifyOnMove.end(); it++)
		{
			InputObjectAttorney::MouseEvents::MouseCursorMoved(*it, currPos, currPos - prevPos);
		}
	}

	prevPos = currPos;
}

void MouseCursorListener::Register(InputObject* pInputable)
{
	notifyOnMove.push_back(pInputable);
}

void MouseCursorListener::Deregister(InputObject* pInputable)
{
	notifyOnMove.remove(pInputable);
}

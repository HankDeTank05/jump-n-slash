#include "Subject.h"

#include "Observer.h"

Subject::ObserverListRef Subject::AddObserver(Observer* pObserver)
{
	return observers.insert(observers.end(), pObserver);
}

void Subject::RemoveObserver(ObserverListRef listRef)
{
	observers.erase(listRef);
}

void Subject::Notify(ObserverEvent event)
{
	for (ObserverList::iterator it = observers.begin(); it != observers.end(); it++)
	{
		(*it)->OnNotify(event);
	}
}

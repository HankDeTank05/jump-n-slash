#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>

#include "ObserverEvent.h"

// forward declarations
class Observer;

class Subject
{
public:
	Subject() = default;
	Subject(const Subject& s) = delete;
	Subject& operator=(const Subject& s) = delete;
	virtual ~Subject() = default;

	using ObserverList = std::list<Observer*>;
	using ObserverListRef = ObserverList::iterator;

	ObserverListRef AddObserver(Observer* pObserver);
	void RemoveObserver(ObserverListRef listRef);

protected:
	void Notify(ObserverEvent event);

private:
	ObserverList observers;
};

#endif
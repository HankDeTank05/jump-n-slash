#ifndef OBSERVER_H
#define OBSERVER_H

#include "ObserverEvent.h"

class Observer
{
public:
	Observer() = default;
	Observer(const Observer& o) = delete;
	Observer& operator=(const Observer& o) = delete;
	virtual ~Observer() = default;

	virtual void OnNotify(ObserverEvent event) = 0;
};

#endif
#ifndef ACTIVATOR_H
#define ACTIVATOR_H

// forward declarations
class Activatable;

class Activator
{
public:
	Activator() = delete;
	Activator(Activatable* pThingToActivate);
	Activator(const Activator& a) = delete;
	Activator& operator=(const Activator& a) = delete;
	virtual ~Activator() = default;

	void Trigger();

private:
	Activatable* pThingToActivate;
	bool isTriggered;
};

#endif
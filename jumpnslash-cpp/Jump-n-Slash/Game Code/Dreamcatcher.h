#ifndef DREAMCATCHER_H
#define DREAMCATCHER_H

class Dreamcatcher
{
public:
	Dreamcatcher() = default;
	Dreamcatcher(const Dreamcatcher& d) = delete;
	Dreamcatcher& operator=(const Dreamcatcher& d) = delete;
	virtual ~Dreamcatcher() = default;

	virtual void SlashAtkBehavior() = 0;
	virtual void DreamAtkBehavior() = 0;
	virtual void JumpBehavior() = 0;
	virtual void DashBehavior() = 0;
};

#endif
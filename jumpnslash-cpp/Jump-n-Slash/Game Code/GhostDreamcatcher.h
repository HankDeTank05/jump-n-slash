#ifndef GHOST_DREAMCATCHER_H
#define GHOST_DREAMCATCHER_H

// game includes
#include "Dreamcatcher.h"

class GhostDreamcatcher : public Dreamcatcher
{
public:
	GhostDreamcatcher() = default;
	GhostDreamcatcher(const GhostDreamcatcher& gd) = delete;
	GhostDreamcatcher& operator=(const GhostDreamcatcher& gd) = delete;
	virtual ~GhostDreamcatcher() = default;

	virtual void SlashAtkBehavior() override;
	virtual void DreamAtkBehavior() override;
	virtual void JumpBehavior() override;
	virtual void DashBehavior() override;
};

#endif
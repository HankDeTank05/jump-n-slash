#ifndef SWORD_FSM_H
#define SWORD_FSM_H

#include "SwordStateIdle.h"
#include "SwordStateSwing.h"

class SwordFSM
{
public:
	static const SwordStateIdle idle;
	static const SwordStateSwing swing;
};

#endif
#ifndef COLLISION_TEST_COMMAND_H
#define COLLISION_TEST_COMMAND_H

#include "Command.h"

class CollisionTestCommand : public Command
{
public:
	CollisionTestCommand();
	CollisionTestCommand(const CollisionTestCommand& ctc) = delete;
	CollisionTestCommand& operator=(const CollisionTestCommand& ctc) = delete;
	virtual ~CollisionTestCommand();

	virtual void Execute() = 0;
};

#endif
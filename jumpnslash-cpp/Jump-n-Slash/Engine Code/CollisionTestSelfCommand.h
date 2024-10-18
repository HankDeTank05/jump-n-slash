#ifndef COLLISION_TEST_SELF_COMMAND_H
#define COLLISION_TEST_SELF_COMMAND_H

#include "CollisionTestCommand.h"

// forward declarations
class CollisionGroup;
class CollisionDispatchBase;

class CollisionTestSelfCommand : public CollisionTestCommand
{
public:
	CollisionTestSelfCommand() = delete;
	CollisionTestSelfCommand(CollisionGroup* pGroup, CollisionDispatchBase* pDispatch);
	CollisionTestSelfCommand(const CollisionTestSelfCommand& ctsc) = delete;
	CollisionTestSelfCommand& operator=(const CollisionTestSelfCommand& ctsc) = delete;
	virtual ~CollisionTestSelfCommand();

	virtual void Execute() override;

private:
	CollisionGroup* pGroup;
	CollisionDispatchBase* pDispatch;
};

#endif
#ifndef COLLISION_TEST_SELF_COMMAND_H
#define COLLISION_TEST_SELF_COMMAND_H

#include "CollisionTestCommand.h"

// forward declarations
class CollisionObjectGroup;
class CollisionDispatchBase;

class CollisionTestSelfCommand : public CollisionTestCommand
{
public:
	CollisionTestSelfCommand() = delete;
	CollisionTestSelfCommand(CollisionObjectGroup* pGroup, CollisionDispatchBase* pColDispatch, CollisionDispatchBase* pNoColDispatch);
	CollisionTestSelfCommand(const CollisionTestSelfCommand& ctsc) = delete;
	CollisionTestSelfCommand& operator=(const CollisionTestSelfCommand& ctsc) = delete;
	virtual ~CollisionTestSelfCommand();

	virtual void Execute() override;

private:
	CollisionObjectGroup* pGroup;
	CollisionDispatchBase* pColDispatch;
	CollisionDispatchBase* pNoColDispatch;
};

#endif
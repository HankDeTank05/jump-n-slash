#ifndef COLLISION_TEST_PAIR_COMMAND_H
#define COLLISION_TEST_PAIR_COMMAND_H

#include "CollisionTestCommand.h"

// forward declarations
class CollisionObjectGroup;
class CollisionDispatchBase;

class CollisionTestPairCommand : public CollisionTestCommand
{
public:
	CollisionTestPairCommand() = delete;
	CollisionTestPairCommand(CollisionObjectGroup* pGroup1, CollisionObjectGroup* pGroup2, CollisionDispatchBase* pDispatch);
	CollisionTestPairCommand(const CollisionTestPairCommand& ctpc) = delete;
	CollisionTestPairCommand& operator=(const CollisionTestPairCommand& ctpc) = delete;
	virtual ~CollisionTestPairCommand() = default;

	virtual void Execute() override;

private:
	static const bool VISUALIZE = true;

private:
	CollisionObjectGroup* pGroup1;
	CollisionObjectGroup* pGroup2;
	CollisionDispatchBase* pDispatch;
};

#endif
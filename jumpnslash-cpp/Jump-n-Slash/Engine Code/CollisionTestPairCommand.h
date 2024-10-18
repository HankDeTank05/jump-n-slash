#ifndef COLLISION_TEST_PAIR_COMMAND_H
#define COLLISION_TEST_PAIR_COMMAND_H

#include "CollisionTestCommand.h"

// forward declarations
class CollisionGroup;
class CollisionDispatchBase;

class CollisionTestPairCommand : public CollisionTestCommand
{
public:
	CollisionTestPairCommand() = delete;
	CollisionTestPairCommand(CollisionGroup* pGroup1, CollisionGroup* pGroup2, CollisionDispatchBase* pDispatch);
	CollisionTestPairCommand(const CollisionTestPairCommand& ctpc) = delete;
	CollisionTestPairCommand& operator=(const CollisionTestPairCommand& ctpc) = delete;
	virtual ~CollisionTestPairCommand();

	virtual void Execute() override;

private:
	static const bool VISUALIZE = true;

private:
	CollisionGroup* pGroup1;
	CollisionGroup* pGroup2;
	CollisionDispatchBase* pDispatch;
};

#endif
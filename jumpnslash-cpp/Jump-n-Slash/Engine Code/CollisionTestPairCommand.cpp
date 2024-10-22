#include "CollisionTestPairCommand.h"

CollisionTestPairCommand::CollisionTestPairCommand(CollisionObjectGroup* _pGroup1,
	CollisionObjectGroup* _pGroup2, CollisionDispatchBase* _pDispatch)
	: pGroup1(_pGroup1),
	pGroup2(_pGroup2),
	pDispatch(_pDispatch)
{
	// do nothing?
}

void CollisionTestPairCommand::Execute()
{
	// TODO: actual collision testing occurs here
	assert(false);
}

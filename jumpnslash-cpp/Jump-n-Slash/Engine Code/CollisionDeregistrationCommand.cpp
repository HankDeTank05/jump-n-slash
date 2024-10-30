#include "CollisionDeregistrationCommand.h"

#include "CollisionObjectAttorney.h"

CollisionDeregistrationCommand::CollisionDeregistrationCommand(CollisionObject* _pCollidable)
	: pCollidable(_pCollidable)
{
	// do nothing
}

void CollisionDeregistrationCommand::Execute()
{
	CollisionObjectAttorney::Registration::Deregister(pCollidable);
}

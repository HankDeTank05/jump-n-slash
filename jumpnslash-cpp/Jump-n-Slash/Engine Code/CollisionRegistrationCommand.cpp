#include "CollisionRegistrationCommand.h"

#include "CollisionObjectAttorney.h"

CollisionRegistrationCommand::CollisionRegistrationCommand(CollisionObject* _pCollidable)
	: pCollidable(_pCollidable)
{
	// do nothing
}

void CollisionRegistrationCommand::Execute()
{
	CollisionObjectAttorney::Registration::Register(pCollidable);
}

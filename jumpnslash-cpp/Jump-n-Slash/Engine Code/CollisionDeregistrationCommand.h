#ifndef COLLISION_DEREGISTRATION_COMMAND_H
#define COLLISION_DEREGISTRATION_COMMAND_H

#include "Command.h"

// forward declarations
class CollisionObject;

class CollisionDeregistrationCommand : public Command
{
public:
	CollisionDeregistrationCommand() = delete;
	CollisionDeregistrationCommand(CollisionObject* pCollidable);
	CollisionDeregistrationCommand(const CollisionDeregistrationCommand& cdc) = delete;
	CollisionDeregistrationCommand& operator=(const CollisionDeregistrationCommand& cdc) = delete;
	virtual ~CollisionDeregistrationCommand() = default;

	virtual void Execute() override;

private:
	CollisionObject* pCollidable;
};

#endif
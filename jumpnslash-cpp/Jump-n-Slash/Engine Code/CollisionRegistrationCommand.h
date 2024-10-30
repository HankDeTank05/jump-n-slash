#ifndef COLLISION_REGISTRATION_COMMAND_H
#define COLLISION_REGISTRATION_COMMAND_H

#include "Command.h"

// forward declarations
class CollisionObject;

class CollisionRegistrationCommand : public Command
{
public:
	CollisionRegistrationCommand() = delete;
	CollisionRegistrationCommand(CollisionObject* pCollidable);
	CollisionRegistrationCommand(const CollisionRegistrationCommand& crc) = delete;
	CollisionRegistrationCommand& operator=(const CollisionRegistrationCommand& crc) = delete;
	virtual ~CollisionRegistrationCommand() = default;

	virtual void Execute() override;

private:
	CollisionObject* pCollidable;
};

#endif
#ifndef GAME_OBJECT_REGISTRATION_COMMAND_H
#define GAME_OBJECT_REGISTRATION_COMMAND_H

// engine includes
#include "Command.h"

// forward declarations
class GameObject;

class GameObjectRegistrationCommand : public Command
{
public:
	GameObjectRegistrationCommand() = delete;
	GameObjectRegistrationCommand(GameObject* pGameObject);
	GameObjectRegistrationCommand(const GameObjectRegistrationCommand& gorc) = delete;
	GameObjectRegistrationCommand& operator=(const GameObjectRegistrationCommand& gorc) = delete;
	virtual ~GameObjectRegistrationCommand() = default;

	virtual void Execute() override;

private:
	GameObject* pGameObject;
};

#endif
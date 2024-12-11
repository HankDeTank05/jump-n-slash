#ifndef GAME_OBJECT_DEREGISTRATION_COMMAND_H
#define GAME_OBJECT_DEREGISTRATION_COMMAND_H

// engine includes
#include "Command.h"

// forward declarations
class GameObject;

class GameObjectDeregistrationCommand : public Command
{
public:
	GameObjectDeregistrationCommand() = delete;
	GameObjectDeregistrationCommand(GameObject* pGameObject);
	GameObjectDeregistrationCommand(const GameObjectDeregistrationCommand& gorc) = delete;
	GameObjectDeregistrationCommand& operator=(const GameObjectDeregistrationCommand& gorc) = delete;
	virtual ~GameObjectDeregistrationCommand() = default;

	virtual void Execute() override;

private:
	GameObject* pGameObject;
};

#endif
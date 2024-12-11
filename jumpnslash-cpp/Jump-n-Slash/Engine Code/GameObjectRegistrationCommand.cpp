#include "GameObjectRegistrationCommand.h"

// engine includes
#include "GameObjectAttorney.h"

GameObjectRegistrationCommand::GameObjectRegistrationCommand(GameObject* _pGameObject)
	: pGameObject(_pGameObject)
{
	// do nothing
}

void GameObjectRegistrationCommand::Execute()
{
	GameObjectAttorney::CommandAccess::EnterScene(pGameObject);
}

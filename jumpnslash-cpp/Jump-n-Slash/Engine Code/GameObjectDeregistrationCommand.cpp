#include "GameObjectDeregistrationCommand.h"

// engine includes
#include "GameObjectAttorney.h"

GameObjectDeregistrationCommand::GameObjectDeregistrationCommand(GameObject* _pGameObject)
	: pGameObject(_pGameObject)
{
	// do nothing
}

void GameObjectDeregistrationCommand::Execute()
{
	GameObjectAttorney::CommandAccess::ExitScene(pGameObject);
}

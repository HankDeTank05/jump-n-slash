#include "GameObjectAttorney.h"

#include "GameObject.h"

void GameObjectAttorney::CommandAccess::EnterScene(GameObject* pGameObject)
{
	pGameObject->EnterScene();
}

void GameObjectAttorney::CommandAccess::ExitScene(GameObject* pGameObject)
{
	pGameObject->ExitScene();
}

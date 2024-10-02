#include "UpdateManager.h"

#include "UpdateObjectAttorney.h"

UpdateManager::~UpdateManager()
{
	updateList.clear();
}

UpdateManager::UpdateListRef UpdateManager::Register(UpdateObject* pUpdatable)
{
	return updateList.insert(updateList.end(), pUpdatable);
}

void UpdateManager::Deregister(UpdateListRef updateListRef)
{
	updateList.erase(updateListRef);
}

void UpdateManager::Update(float deltaTime)
{
	for (UpdateList::iterator it = updateList.begin(); it != updateList.end(); it++)
	{
		UpdateObjectAttorney::GameLoop::Update(*it, deltaTime);
	}
}

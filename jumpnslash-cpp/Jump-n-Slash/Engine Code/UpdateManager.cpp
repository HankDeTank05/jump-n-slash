#include "UpdateManager.h"

#include "UpdatableObjectAttorney.h"

UpdateManager::~UpdateManager()
{
	updateList.clear();
}

UpdateManager::UpdateListRef UpdateManager::Register(UpdatableObject* pUpdatable)
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
		UpdatableObjectAttorney::GameLoop::Update(*it, deltaTime);
	}
}

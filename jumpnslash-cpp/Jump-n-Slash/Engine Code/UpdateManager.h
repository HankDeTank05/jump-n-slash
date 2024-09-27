#ifndef UPDATE_MANAGER_H
#define UPDATE_MANAGER_H

#include <list>

// forward declarations
class UpdatableObject;

class UpdateManager
{
public:
	UpdateManager() = default;
	UpdateManager(const UpdateManager& um) = delete;
	UpdateManager& operator=(const UpdateManager& um) = delete;
	virtual ~UpdateManager();

private:
	using UpdateList = std::list<UpdatableObject*>;
public:
	using UpdateListRef = UpdateList::iterator;

	UpdateListRef Register(UpdatableObject* pUpdatable); // TODO: documentation for UpdateManager::Register
	void Deregister(UpdateListRef updateListRef); // TODO: documentation for UpdateManager::Deregister

	void Update(float deltaTime);

private:
	UpdateList updateList;
};

#endif
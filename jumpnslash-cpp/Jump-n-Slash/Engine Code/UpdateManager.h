#ifndef UPDATE_MANAGER_H
#define UPDATE_MANAGER_H

#include <list>

// forward declarations
class UpdateObject;

class UpdateManager
{
public:
	UpdateManager() = default;
	UpdateManager(const UpdateManager& um) = delete;
	UpdateManager& operator=(const UpdateManager& um) = delete;
	virtual ~UpdateManager();

private:
	using UpdateList = std::list<UpdateObject*>;
public:
	using UpdateListRef = UpdateList::iterator;

	// TODO: docs for UpdateManager::Register
	UpdateListRef Register(UpdateObject* pUpdatable);
	// TODO: docs for UpdateManager::Deregister
	void Deregister(UpdateListRef updateListRef); 

	void Update(float deltaTime);

private:
	UpdateList updateList;
};

#endif
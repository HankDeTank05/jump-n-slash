#ifndef UPDATE_OBJECT_H
#define UPDATE_OBJECT_H

#include "RegistrationState.h"
#include "UpdateManager.h"

// forward declarations
class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

class UpdateObject
{
public:
	UpdateObject();
	UpdateObject(const UpdateObject& uo) = delete;
	UpdateObject& operator=(const UpdateObject& uo) = delete;
	virtual ~UpdateObject();

protected:
	virtual void Update(float deltaTime); // TODO: documentation for UpdateObject::Update

	void RequestUpdateRegistration(); // TODO: documentation for UpdateObject::RequestUpdateRegistration
	void RequestUpdateDeregistration(); // TODO: documentation for UpdateObject::RequestUpdateDeregistration

private:
	friend class UpdateObjectAttorney;
	void Register();
	void Deregister();

private:
	RegistrationState regState;
	UpdateRegistrationCommand* pRegCmd;
	UpdateDeregistrationCommand* pDeregCmd;
	UpdateManager::UpdateListRef deleteRef;
};

#endif
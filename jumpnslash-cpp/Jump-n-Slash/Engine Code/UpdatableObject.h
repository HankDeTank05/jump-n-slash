#ifndef UPDATABLE_OBJECT_H
#define UPDATABLE_OBJECT_H

#include "RegistrationState.h"
#include "UpdateManager.h"

// forward declarations
class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

class UpdatableObject
{
public:
	UpdatableObject();
	UpdatableObject(const UpdatableObject& uo) = delete;
	UpdatableObject& operator=(const UpdatableObject& uo) = delete;
	virtual ~UpdatableObject();

protected:
	virtual void Update(float deltaTime); // TODO: documentation for UpdatableObject::Update

	void EnqueueForUpdateRegistration(); // TODO: documentation for UpdatableObject::EnqueueForUpdateRegistration
	void EnqueueForUpdateDeregistration(); // TODO: documentation for UpdatableObject::EnqueueForUpdateDeregistration

private:
	friend class UpdatableObjectAttorney;
	void Register();
	void Deregister();

private:
	RegistrationState regState;
	UpdateRegistrationCommand* pRegCmd;
	UpdateDeregistrationCommand* pDeregCmd;
	UpdateManager::UpdateListRef deleteRef;
};

#endif
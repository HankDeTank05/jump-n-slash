#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include "RegistrationState.h"
#include "DrawManager.h"

// forward declarations
class DrawRegistrationCommand;
class DrawDeregistrationCommand;

class DrawableObject
{
public:
	DrawableObject();
	DrawableObject(const DrawableObject& dob) = delete;
	DrawableObject& operator=(const DrawableObject& dob) = delete;
	virtual ~DrawableObject();

protected:
	virtual void Draw(); // TODO: documentation for DrawableObject::Draw

	void EnqueueForDrawRegistration(); // TODO: documentation for DrawableObject::EnqueueForDrawRegistration
	void EnqueueForDrawDeregistration(); // TODO: documentation for DrawableObject::EnqueueForDrawDeregistration

private:
	friend class DrawableObjectAttorney;
	void Register();
	void Deregister();

private:
	RegistrationState regState;
	DrawRegistrationCommand* pRegCmd;
	DrawDeregistrationCommand* pDeregCmd;
	DrawManager::DrawListRef deleteRef;
};

#endif
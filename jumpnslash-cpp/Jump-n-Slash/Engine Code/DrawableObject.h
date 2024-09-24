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

	// TODO: documentation for DrawableObject::Draw()
	virtual void Draw();

	// TODO: documentation for DrawableObject::EnqueueForDrawRegistration()
	void EnqueueForDrawRegistration();
	// TODO: documentation for DrawableObject::EnqueueForDrawDeregistration()
	void EnqueueForDrawDeregistration();

private:
	friend class DrawableObjectAttorney;
	void Register(); // TODO: rename this function to "DrawableObject::SceneRegister" once scene system is created
	void Deregister(); // TODO: rename this function to "DrawableObject::SceneDeregister" once scene system is created

private:
	RegistrationState regState;
	DrawRegistrationCommand* pRegCmd;
	DrawDeregistrationCommand* pDeregCmd;
	DrawManager::DrawListRef deleteRef;
};

#endif
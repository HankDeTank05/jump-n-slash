#ifndef DRAW_OBJECT_H
#define DRAW_OBJECT_H

#include "RegistrationState.h"
#include "DrawManager.h"

// forward declarations
class DrawRegistrationCommand;
class DrawDeregistrationCommand;

class DrawObject
{
public:
	DrawObject();
	DrawObject(const DrawObject& dob) = delete;
	DrawObject& operator=(const DrawObject& dob) = delete;
	virtual ~DrawObject();

protected:
	virtual void Draw(); // TODO: documentation for DrawObject::Draw

	void RequestDrawRegistration(); // TODO: documentation for DrawObject::RequestDrawRegistration
	void RequestDrawDeregistration(); // TODO: documentation for DrawObject::RequestDrawDeregistration

private:
	friend class DrawObjectAttorney;
	void Register();
	void Deregister();

private:
	RegistrationState regState;
	DrawRegistrationCommand* pRegCmd;
	DrawDeregistrationCommand* pDeregCmd;
	DrawManager::DrawListRef deleteRef;
};

#endif
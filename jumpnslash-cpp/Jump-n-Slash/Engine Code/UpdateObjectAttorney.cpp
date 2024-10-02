#include "UpdateObjectAttorney.h"

#include "UpdateObject.h"

void UpdateObjectAttorney::GameLoop::Update(UpdateObject* pUpdatable, float deltaTime)
{
	pUpdatable->Update(deltaTime);
}

void UpdateObjectAttorney::Registration::Register(UpdateObject* pUpdatable)
{
	pUpdatable->Register();
}

void UpdateObjectAttorney::Registration::Deregister(UpdateObject* pUpdatable)
{
	pUpdatable->Deregister();
}

#include "UpdatableObjectAttorney.h"

#include "UpdatableObject.h"

void UpdatableObjectAttorney::GameLoop::Update(UpdatableObject* pUpdatable)
{
	pUpdatable->Update();
}

void UpdatableObjectAttorney::Registration::Register(UpdatableObject* pUpdatable)
{
	pUpdatable->Register();
}

void UpdatableObjectAttorney::Registration::Deregister(UpdatableObject* pUpdatable)
{
	pUpdatable->Deregister();
}

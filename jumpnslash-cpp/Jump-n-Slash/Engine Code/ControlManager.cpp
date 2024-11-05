#include "ControlManager.h"

ControlManager* ControlManager::pInstance = nullptr;

ControlManager::ControlManager()
	: ctrl(ControlScheme::Keyboard)
{
	// TODO: read modified mapping from text file
}

ControlManager& ControlManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new ControlManager();
	}
	return *pInstance;
}

void ControlManager::SetControlScheme(ControlScheme ctrl)
{
	Instance().privSetControlScheme(ctrl);
}

ControlScheme ControlManager::GetControlScheme()
{
	return Instance().privGetControlScheme();
}

void ControlManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void ControlManager::privSetControlScheme(ControlScheme _ctrl)
{
	if (_ctrl != ctrl)
	{

	}

	ctrl = _ctrl;
}

ControlScheme ControlManager::privGetControlScheme()
{
	return ctrl;
}

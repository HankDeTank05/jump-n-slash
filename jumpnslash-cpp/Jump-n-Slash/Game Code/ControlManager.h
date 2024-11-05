#ifndef CONTROL_MANAGER_H
#define CONTROL_MANAGER_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

#include "../Engine Code/ControllerInputs.h"

#include "ControlScheme.h"

class ControlManager // this class is written as a singleton
{
private:
	static ControlManager* pInstance;

	ControlManager();
	ControlManager(const ControlManager& cm) = delete;
	ControlManager& operator=(const ControlManager& cm) = delete;
	virtual ~ControlManager() = default;

	static ControlManager& Instance();

public: // api functions
	// TODO: docs for ControlManager::SetControlScheme
	static void SetControlScheme(ControlScheme ctrl);
	// TODO: docs for ControlManager::GetControlScheme
	static ControlScheme GetControlScheme();
	

private: // internal-only API functions
	friend class ControlManagerAttorney;
	static void Terminate();

private: // API backend functions
	void privSetControlScheme(ControlScheme ctrl);
	ControlScheme privGetControlScheme();

private: // member variables
	ControlScheme ctrl;
};

#endif
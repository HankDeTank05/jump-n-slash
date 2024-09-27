#include "InputObject.h"

#include "KeyRegistrationCommand.h"
#include "KeyDeregistrationCommand.h"
#include "MouseBtnRegistrationCommand.h"
#include "MouseBtnDeregistrationCommand.h"
#include "MouseCursorRegistrationCommand.h"
#include "MouseCursorDeregistrationCommand.h"
#include "SceneAttorney.h"
#include "JumpSlashEngine.h"

InputObject::InputObject()
	: keyTracker(),
	mouseBtnTracker(),
	mouseCursorRegData()
{
	mouseCursorRegData.regState = RegistrationState::CURRENTLY_DEREGISTERED;
	mouseCursorRegData.pRegCmd = new MouseCursorRegistrationCommand(this);
	mouseCursorRegData.pDeregCmd = new MouseCursorDeregistrationCommand(this);
}

InputObject::~InputObject()
{
	delete mouseCursorRegData.pDeregCmd;
	delete mouseCursorRegData.pRegCmd;

	for (MouseBtnRegTracker::iterator it = mouseBtnTracker.begin(); it != mouseBtnTracker.end(); it++)
	{
		delete it->second.pDeregCmd;
		delete it->second.pRegCmd;
	}

	for (KeyRegTracker::iterator it = keyTracker.begin(); it != keyTracker.end(); it++)
	{
		delete it->second.pDeregCmd;
		delete it->second.pRegCmd;
	}
}

void InputObject::EnqueueForKeyRegistration(sf::Keyboard::Key key, KeyEvent eventToReg)
{
	KeyTrackerID keyID(key, eventToReg);
	if (keyTracker.count(keyID) == 0)
	{
		// create registration data
		KeyRegistrationData keyRegData;
		keyRegData.regState = RegistrationState::CURRENTLY_DEREGISTERED;
		keyRegData.pRegCmd = new KeyRegistrationCommand(this, key, eventToReg);
		keyRegData.pDeregCmd = new KeyDeregistrationCommand(this, key, eventToReg);
		keyTracker.emplace(keyID, keyRegData);
	}
	else
	{
		// use existing registration data
		assert(keyTracker.at(keyID).regState == RegistrationState::CURRENTLY_DEREGISTERED);
	}

	SceneAttorney::Commands::AddCommand(JumpSlashEngine::GetCurrentScene(), keyTracker.at(keyID).pRegCmd);

	keyTracker.at(keyID).regState = RegistrationState::PENDING_REGISTRATION;
}

void InputObject::EnqueueForKeyDeregistration(sf::Keyboard::Key key, KeyEvent eventToDereg)
{
	KeyTrackerID keyID(key, eventToDereg);
	assert(keyTracker.count(keyID) > 0); // Invalid KeyID: keyID does not exist!
	assert(keyTracker.at(keyID).regState == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorney::Commands::AddCommand(JumpSlashEngine::GetCurrentScene(), keyTracker.at(keyID).pDeregCmd);

	keyTracker.at(keyID).regState = RegistrationState::PENDING_DEREGISTRATION;
}

void InputObject::EnqueueForMouseBtnRegistration(sf::Mouse::Button btn, MouseEvent eventToReg)
{
	MouseBtnTrackerID btnID(btn, eventToReg);
	if (mouseBtnTracker.count(btnID) == 0)
	{
		// create registration data
		MouseBtnRegistrationData mouseBtnRegData;
		mouseBtnRegData.regState = RegistrationState::CURRENTLY_DEREGISTERED;
		mouseBtnRegData.pRegCmd = new MouseBtnRegistrationCommand(this, btn, eventToReg);
		mouseBtnRegData.pDeregCmd = new MouseBtnDeregistrationCommand(this, btn, eventToReg);
		mouseBtnTracker.emplace(btnID, mouseBtnRegData);
	}
	else
	{
		// use existing registration data
		assert(mouseBtnTracker.at(btnID).regState == RegistrationState::CURRENTLY_DEREGISTERED);
	}

	SceneAttorney::Commands::AddCommand(JumpSlashEngine::GetCurrentScene(), mouseBtnTracker.at(btnID).pRegCmd);

	mouseBtnTracker.at(btnID).regState = RegistrationState::PENDING_REGISTRATION;
}

void InputObject::EnqueueForMouseBtnDeregistration(sf::Mouse::Button btn, MouseEvent eventToDereg)
{
	MouseBtnTrackerID btnID(btn, eventToDereg);
	assert(mouseBtnTracker.count(btnID) > 0); // Invalid BtnID: btnID does not exist!
	assert(mouseBtnTracker.at(btnID).regState == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorney::Commands::AddCommand(JumpSlashEngine::GetCurrentScene(), mouseBtnTracker.at(btnID).pDeregCmd);

	mouseBtnTracker.at(btnID).regState = RegistrationState::PENDING_DEREGISTRATION;
}

void InputObject::EnqueueForMouseCursorRegistration()
{
	assert(mouseCursorRegData.regState == RegistrationState::CURRENTLY_DEREGISTERED);

	SceneAttorney::Commands::AddCommand(JumpSlashEngine::GetCurrentScene(), mouseCursorRegData.pRegCmd);

	mouseCursorRegData.regState = RegistrationState::PENDING_REGISTRATION;
}

void InputObject::EnqueueForMouseCursorDeregistration()
{
	assert(mouseCursorRegData.regState == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorney::Commands::AddCommand(JumpSlashEngine::GetCurrentScene(), mouseCursorRegData.pDeregCmd);

	mouseCursorRegData.regState = RegistrationState::PENDING_DEREGISTRATION;
}

void InputObject::RegisterKey(sf::Keyboard::Key key, KeyEvent eventToReg)
{
	KeyTrackerID keyID(key, eventToReg);
	assert(keyTracker.count(keyID) > 0); // Invalid KeyID: keyID does not exist!
	assert(keyTracker.at(keyID).regState == RegistrationState::PENDING_REGISTRATION);

	SceneAttorney::Input::RegisterKey(JumpSlashEngine::GetCurrentScene(), key, this, eventToReg);

	keyTracker.at(keyID).regState = RegistrationState::CURRENTLY_REGISTERED;
}

void InputObject::DeregisterKey(sf::Keyboard::Key key, KeyEvent eventToDereg)
{
	KeyTrackerID keyID(key, eventToDereg);
	assert(keyTracker.count(keyID) > 0); // Invalid KeyID: keyID does not exist!
	assert(keyTracker.at(keyID).regState == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorney::Input::DeregisterKey(JumpSlashEngine::GetCurrentScene(), key, this, eventToDereg);

	keyTracker.at(keyID).regState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void InputObject::RegisterMouseBtn(sf::Mouse::Button btn, MouseEvent eventToReg)
{
	MouseBtnTrackerID btnID(btn, eventToReg);
	assert(mouseBtnTracker.count(btnID) > 0); // Invalid BtnID: btnID does not exist!
	assert(mouseBtnTracker.at(btnID).regState == RegistrationState::PENDING_REGISTRATION);

	SceneAttorney::Input::RegisterMouseBtn(JumpSlashEngine::GetCurrentScene(), btn, this, eventToReg);

	mouseBtnTracker.at(btnID).regState = RegistrationState::CURRENTLY_REGISTERED;
}

void InputObject::DeregisterMouseBtn(sf::Mouse::Button btn, MouseEvent eventToDereg)
{
	MouseBtnTrackerID btnID(btn, eventToDereg);
	assert(mouseBtnTracker.count(btnID) > 0); // Invalid BtnID: btnID does not exist!
	assert(mouseBtnTracker.at(btnID).regState == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorney::Input::DeregisterMouseBtn(JumpSlashEngine::GetCurrentScene(), btn, this, eventToDereg);

	mouseBtnTracker.at(btnID).regState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void InputObject::RegisterMouseCursor()
{
	assert(mouseCursorRegData.regState == RegistrationState::PENDING_REGISTRATION);

	SceneAttorney::Input::RegisterMouseCursor(JumpSlashEngine::GetCurrentScene(), this);

	mouseCursorRegData.regState = RegistrationState::CURRENTLY_REGISTERED;
}

void InputObject::DeregisterMouseCursor()
{
	assert(mouseCursorRegData.regState == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorney::Input::DeregisterMouseCursor(JumpSlashEngine::GetCurrentScene(), this);

	mouseCursorRegData.regState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void InputObject::KeyPressed(sf::Keyboard::Key key)
{
	// do nothing. override to make it do something
}

void InputObject::KeyReleased(sf::Keyboard::Key key)
{
	// do nothing. override to make it do something
}

void InputObject::MouseBtnPressed(sf::Mouse::Button btn)
{
	// do nothing. override to make it do something
}

void InputObject::MouseBtnReleased(sf::Mouse::Button btn)
{
	// do nothing. override to make it do something
}

void InputObject::MouseCursorMoved(sf::Vector2i pos, sf::Vector2i delta)
{
	// do nothing. override to make it do something
}

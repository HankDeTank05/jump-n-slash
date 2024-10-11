#include "DrawObject.h"

#include <cassert>

#include "EngineAttorney.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"
#include "SceneAttorney.h"
#include "SceneManager.h"

DrawObject::DrawObject()
	: regState(RegistrationState::CURRENTLY_DEREGISTERED),
	pRegCmd(new DrawRegistrationCommand(this)),
	pDeregCmd(new DrawDeregistrationCommand(this)),
	deleteRef()
{
	// do nothing
}

DrawObject::~DrawObject()
{
	delete pDeregCmd;
	delete pRegCmd;
}

void DrawObject::Draw()
{
	// do nothing. override to make it do something
}

void DrawObject::Render(sf::Drawable& drawable)
{
	EngineAttorney::GameWindow::GetWindow().draw(drawable);
}

void DrawObject::Render(sf::Vertex* array, int vtexCount)
{
	EngineAttorney::GameWindow::GetWindow().draw(array, vtexCount, sf::Lines);
}

void DrawObject::RequestDrawRegistration()
{
	assert(regState == RegistrationState::CURRENTLY_DEREGISTERED);

	SceneAttorney::Commands::AddCommand(SceneManager::GetCurrentScene(), pRegCmd);

	regState = RegistrationState::PENDING_REGISTRATION;
}

void DrawObject::RequestDrawDeregistration()
{
	assert(regState == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorney::Commands::AddCommand(SceneManager::GetCurrentScene(), pDeregCmd);

	regState = RegistrationState::PENDING_DEREGISTRATION;
}

void DrawObject::Register()
{
	assert(regState == RegistrationState::PENDING_REGISTRATION);

	deleteRef = SceneAttorney::Draw::Register(SceneManager::GetCurrentScene(), this);

	regState = RegistrationState::CURRENTLY_REGISTERED;
}

void DrawObject::Deregister()
{
	assert(regState == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorney::Draw::Deregister(SceneManager::GetCurrentScene(), deleteRef);

	regState = RegistrationState::CURRENTLY_DEREGISTERED;
}

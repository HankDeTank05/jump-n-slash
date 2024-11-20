#include "GameObject.h"

// engine includes
#include "SceneAttorney.h"
#include "SceneManager.h"
#include "GameObjectRegistrationCommand.h"
#include "GameObjectDeregistrationCommand.h"
#include "AnimationComponent.h"

GameObject::GameObject()
	: regState(RegistrationState::CURRENTLY_DEREGISTERED),
	pRegCmd(new GameObjectRegistrationCommand(this)),
	pDeregCmd(new GameObjectDeregistrationCommand(this)),
	pos(),
	width(),
	height(),
	pSprite(nullptr),
	pAnimComp(new AnimationComponent())
{
	// do nothing
}

GameObject::~GameObject()
{
	delete pDeregCmd;
	delete pRegCmd;
}

void GameObject::MarkForDestroy()
{
	RequestSceneExit();
}

void GameObject::Draw()
{
	Render(pSprite);
}

void GameObject::RequestSceneEntry()
{
	assert(regState == RegistrationState::CURRENTLY_DEREGISTERED);

	SceneAttorney::Commands::AddCommand(SceneManager::GetCurrentScene(), pRegCmd);

	regState = RegistrationState::PENDING_REGISTRATION;
}

void GameObject::RequestSceneExit()
{
	assert(regState == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorney::Commands::AddCommand(SceneManager::GetCurrentScene(), pDeregCmd);
}

void GameObject::OnSceneEntry()
{
	// do nothing. override to make it do something
}

void GameObject::OnSceneExit()
{
	// do nothing. override to make it do something
}

void GameObject::EnterScene()
{
	assert(regState == RegistrationState::PENDING_REGISTRATION);

	RequestUpdateRegistration();
	RequestDrawRegistration();

	OnSceneEntry();

	regState = RegistrationState::CURRENTLY_REGISTERED;
}

void GameObject::ExitScene()
{
	assert(regState == RegistrationState::PENDING_DEREGISTRATION);

	RequestUpdateDeregistration();
	RequestDrawDeregistration();

	OnSceneExit();

	regState = RegistrationState::CURRENTLY_DEREGISTERED;
}

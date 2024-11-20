#include "GameObject.h"

// engine includes
#include "SceneAttorney.h"
#include "SceneManager.h"
#include "GameObjectRegistrationCommand.h"
#include "GameObjectDeregistrationCommand.h"
#include "AnimationComponent.h"
#include "Sprite.h"

GameObject::GameObject()
	: regState(RegistrationState::CURRENTLY_DEREGISTERED),
	pRegCmd(new GameObjectRegistrationCommand(this)),
	pDeregCmd(new GameObjectDeregistrationCommand(this)),
	pos(),
	posDelta(0.f, 0.f),
	width(0.f),
	height(0.f),
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

sf::Vector2f GameObject::GetPos() const
{
	return pos;
}

sf::Vector2f GameObject::GetPosDelta() const
{
	return posDelta;
}

float GameObject::GetWidth() const
{
	return width;
}

float GameObject::GetHeight() const
{
	return height;
}

void GameObject::UpdateSprite()
{
	assert(pSprite != nullptr);
	pSprite = pAnimComp->GetCurrentFrame();
	SetWidth();
	SetHeight();
}

void GameObject::SetWidth()
{
	width = abs(pSprite->GetTextureRect().getSize().x * pSprite->GetScale().x);
}

void GameObject::SetHeight()
{
	height = abs(pSprite->GetTextureRect().getSize().y * pSprite->GetScale().y);
}

void GameObject::SetPosition(const sf::Vector2f& newPos)
{
	pos = newPos;
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

#include "Player.h"

#include "../Engine Code/JumpSlashEngine.h"

Player::Player()
	: circle(64.0f),
	currentFrames(0),
	maxFrames(100)
{
	circle.setFillColor(sf::Color::Green);

	EnqueueForUpdateRegistration();
	EnqueueForDrawRegistration();
}

Player::~Player()
{
	// do destructor stuff here
}

void Player::Update()
{
	currentFrames++;
	if (currentFrames >= maxFrames)
	{
		EnqueueForUpdateDeregistration();
		EnqueueForDrawDeregistration();
	}
}

void Player::Draw()
{
	JumpSlashEngine::GetWindow().draw(circle);
}

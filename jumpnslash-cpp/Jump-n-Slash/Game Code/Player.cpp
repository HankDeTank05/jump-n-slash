#include "Player.h"

#include "../Engine Code/JumpSlashEngine.h"

Player::Player()
	: circle(64.0f)
{
	circle.setFillColor(sf::Color::Green);
	EnqueueForDrawRegistration();
}

Player::~Player()
{
	// do destructor stuff here
}

void Player::Draw()
{
	JumpSlashEngine::GetWindow().draw(circle);
}

#include "Player.h"

#include "../Engine Code/JumpSlashEngine.h"

Player::Player()
	: circle(64.0f),
	currentFrames(0),
	maxFrames(100)
{
	circle.setFillColor(sf::Color::White);

	EnqueueForUpdateRegistration();
	EnqueueForDrawRegistration();
	EnqueueForKeyRegistration(sf::Keyboard::R, KeyEvent::KeyPress);
	EnqueueForKeyRegistration(sf::Keyboard::G, KeyEvent::KeyPress);
	EnqueueForKeyRegistration(sf::Keyboard::B, KeyEvent::KeyPress);
}

Player::~Player()
{
	// do destructor stuff here
}

void Player::Update()
{
	//currentFrames++;
	//if (currentFrames >= maxFrames)
	//{
	//	EnqueueForUpdateDeregistration();
	//	EnqueueForDrawDeregistration();
	//}
}

void Player::Draw()
{
	JumpSlashEngine::GetWindow().draw(circle);
}

void Player::KeyPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::R:
		circle.setFillColor(sf::Color::Red);
		break;
	case sf::Keyboard::G:
		circle.setFillColor(sf::Color::Green);
		break;
	case sf::Keyboard::B:
		circle.setFillColor(sf::Color::Blue);
		break;
	}
}

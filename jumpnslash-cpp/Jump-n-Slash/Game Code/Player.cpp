#include "Player.h"

#include "../Engine Code/SpriteManager.h"
#include "../Engine Code/Visualizer.h"

#include "Constants.h"
#include "DesignerControls.h"
#include "PlayerMoveState.h"
#include "PlayerFSM.h"
#include "LevelMap.h"

Player::Player(LevelMap* _pLevel)
	: pos(_pLevel->GetStartingSpawnPoint()),
	posDelta(0.0f, 0.0f),
	speed(PLAYER_WALK_SPEED),
	pSprite(SpriteManager::GetSprite("player idle 1")),
	pCurrentState(&PlayerFSM::idle),
	respawnPoint(_pLevel->GetStartingSpawnPoint()),
	pLevel(_pLevel)
{
	RequestUpdateRegistration();
	RequestDrawRegistration();
	RequestKeyRegistration(JUMP_KEY, KeyEvent::KeyPress);
	RequestKeyRegistration(JUMP_KEY, KeyEvent::KeyRelease);
	RequestKeyRegistration(WALK_LEFT_KEY, KeyEvent::KeyPress);
	RequestKeyRegistration(WALK_LEFT_KEY, KeyEvent::KeyRelease);
	RequestKeyRegistration(WALK_RIGHT_KEY, KeyEvent::KeyPress);
	RequestKeyRegistration(WALK_RIGHT_KEY, KeyEvent::KeyRelease);
	
	assert(pCurrentState != nullptr);
}

Player::~Player()
{
	// do nothing
}

void Player::Update(float deltaTime)
{
	/*
	pos += posDelta * deltaTime;
	pSprite->setPosition(pos);

	// map collision
	Visualizer::VisualizePoint(pos + sf::Vector2f(0.f, TILE_SIZE_F), sf::Color::Green);
	Visualizer::VisualizePoint(pos + sf::Vector2f(TILE_SIZE_F, TILE_SIZE_F), sf::Color::Green);
	Visualizer::VisualizeSegment(pos + sf::Vector2f(0.f, TILE_SIZE_F), pos + sf::Vector2f(0.f, TILE_SIZE_F * 4), sf::Color::Yellow);
	//Visualizer::VisualizePoint(pos);
	//Visualizer::VisualizePoint(pos + sf::Vector2f(TILE_SIZE_F, 0.f));
	//*/
	pCurrentState->Update(this, deltaTime);

	pSprite->setPosition(pos);

	const PlayerMoveState* pPrevState = pCurrentState;
	pCurrentState = pCurrentState->GetNextState(this);
	if (pCurrentState != pPrevState)
	{
		pCurrentState->Enter(this);
	}
}

void Player::Draw()
{
	Render(*pSprite);
}

void Player::KeyPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
	case WALK_LEFT_KEY:
		posDelta.x = -speed;
		break;
	case WALK_RIGHT_KEY:
		posDelta.x = speed;
		break;
	}
}

void Player::KeyReleased(sf::Keyboard::Key key)
{
	switch (key)
	{
	case WALK_LEFT_KEY:
	case WALK_RIGHT_KEY:
		posDelta.x = 0.f;
		break;
	}
}

sf::Vector2f Player::GetPos()
{
	return pos;
}

sf::Vector2f Player::GetPosDelta()
{
	return posDelta;
}

LevelMap* Player::GetLevel()
{
	return pLevel;
}

void Player::SetPosX(float newX)
{
	pos.x = newX;
}

void Player::SetPosY(float newY)
{
	pos.y = newY;
}

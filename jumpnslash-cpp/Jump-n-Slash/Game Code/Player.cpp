#include "Player.h"

#include "../Engine Code/JumpSlashEngine.h"
#include "../Engine Code/SpriteManager.h"

#include "Constants.h"
#include "DesignerControls.h"
#include "PlayerMoveState.h"
#include "PlayerFSM.h"

Player::Player(sf::Vector2f spawnPoint)
	: pos(0.0f, 0.0f),
	posDelta(0.0f, 0.0f),
	speed(PLAYER_WALK_SPEED),
	pSprite(SpriteManager::GetSprite("player idle 1")),
	pCurrentState(&PlayerFSM::idle),
	respawnPoint(spawnPoint)
{
	EnqueueForUpdateRegistration();
	EnqueueForDrawRegistration();
	EnqueueForKeyRegistration(JUMP_BTN, KeyEvent::KeyPress);
	EnqueueForKeyRegistration(JUMP_BTN, KeyEvent::KeyRelease);
	EnqueueForKeyRegistration(WALK_LEFT_BTN, KeyEvent::KeyPress);
	EnqueueForKeyRegistration(WALK_LEFT_BTN, KeyEvent::KeyRelease);
	EnqueueForKeyRegistration(WALK_RIGHT_BTN, KeyEvent::KeyPress);
	EnqueueForKeyRegistration(WALK_RIGHT_BTN, KeyEvent::KeyRelease);
	
	assert(pCurrentState != nullptr);
}

Player::~Player()
{
	// do nothing
}

void Player::Update(float deltaTime)
{
	pos += posDelta * deltaTime;
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
	JumpSlashEngine::GetWindow().draw(*pSprite);
}

void Player::KeyPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
	case WALK_LEFT_BTN:
		posDelta.x = -speed;
		break;
	case WALK_RIGHT_BTN:
		posDelta.x = speed;
		break;
	}
}

void Player::KeyReleased(sf::Keyboard::Key key)
{
	switch (key)
	{
	case WALK_LEFT_BTN:
	case WALK_RIGHT_BTN:
		posDelta.x = 0.0f;
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

void Player::SetSpawnPoint(sf::Vector2f spawnPoint)
{
	respawnPoint = spawnPoint;
}

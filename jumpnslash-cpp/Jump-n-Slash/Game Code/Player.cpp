#include "Player.h"

#include "../Engine Code/SpriteManager.h"
#include "../Engine Code/AnimationManager.h"
#include "../Engine Code/Visualizer.h"
#include "../Engine Code/Math.h"
#include "../Engine Code/SceneManager.h"
#include "../Engine Code/Camera.h"
#include "../Engine Code/AnimationSet.h"
#include "../Engine Code/Animation.h"
#include "../Engine Code/Math.h"
#include "../Engine Code/ConvenienceFunctions.h"

#include "Constants.h"
#include "DebugFlags.h"
#include "DesignerControls.h"
#include "PlayerMoveState.h"
#include "PlayerFSM.h"
#include "LevelMap.h"
#include "LevelTile.h"
#include "RoomData.h"
#include <iostream>

Player::Player(LevelMap* pLevel)
	: Actor(PLAYER_WALK_SPEED, pLevel),
	pCurrentState(&PlayerFSM::idle),
	pPrevState(nullptr),
	respawnPoint(),
	walkLeftKeyDown(false),
	walkRightKeyDown(false),
	jumpKeyDown(false),
	applyGravity(true)
{	
	assert(pCurrentState != nullptr);

	// connect to map
	pLevel->LinkToPlayer(this);

	// do animation stuff
	AnimationSet* pAnimSet = new AnimationSet();
	
	pAnimSet->AddAnimation("idle", AnimationManager::GetAnimation("player idle"));
	pAnimSet->AddAnimation("walk", AnimationManager::GetAnimation("player walk"));
	pAnimSet->AddAnimation("jump", AnimationManager::GetAnimation("player jump"));
	pAnimSet->AddAnimation("fall", AnimationManager::GetAnimation("player fall"));
	

	pAnimComp->DefineAnimationSet(pAnimSet);
	pAnimComp->SetAnimation("idle");

	pSprite = pAnimComp->GetCurrentFrame();

	// register with the engine
	RequestUpdateRegistration();
	RequestDrawRegistration();
	RequestKeyRegistration(JUMP_KEY, KeyEvent::KeyPress);
	RequestKeyRegistration(JUMP_KEY, KeyEvent::KeyRelease);
	RequestKeyRegistration(WALK_LEFT_KEY, KeyEvent::KeyPress);
	RequestKeyRegistration(WALK_LEFT_KEY, KeyEvent::KeyRelease);
	RequestKeyRegistration(WALK_RIGHT_KEY, KeyEvent::KeyPress);
	RequestKeyRegistration(WALK_RIGHT_KEY, KeyEvent::KeyRelease);
}

Player::~Player()
{
	// do nothing
}

void Player::Update(float deltaTime)
{
	assert(pLevel != nullptr);
	assert(pCurrentRoom != nullptr);

	// update the move state
	pCurrentState = pCurrentState->GetNextState(this);
	if (pCurrentState != pPrevState)
	{
		pCurrentState->Enter(this);
	}

	// update player based on the current move state
	pCurrentState->Update(this, deltaTime);

	// check if we're still inside the room
	sf::Vector2f roomMin = pCurrentRoom->GetRoomMinBounds();
	sf::Vector2f roomMax = pCurrentRoom->GetRoomMaxBounds();
	if (pos.x < roomMin.x || roomMin.x <= pos.x || pos.y < roomMin.y || roomMin.y < pos.y)
	{
		Notify(ObserverEvent::PlayerOutsideCurrentRoom);
	}

	// update the camera
	sf::Vector2f newCamCenter = Math::ClampPoint(pos, pCurrentRoom->GetScrollMinBounds(), pCurrentRoom->GetScrollMaxBounds());
	SceneManager::GetCurrentCamera()->SetCenter(newCamCenter);

	// reset the player's y-velocity if they're grounded (so we don't continuously accelerate downwards)
	if (isGrounded && !jumpKeyDown)
	{
		posDelta.y = 0.f;
	}

	// TEMPORARY CODE, to make sure jump force is only applied for the first frame the jump key is pressed
	if (jumpKeyDown)
	{
		jumpKeyDown = false;
	}

	// update the previous state for the next frame
	pPrevState = pCurrentState;

	// debug visualizations
	if (DEBUG_PLAYER_POSITION)
	{

		// Visualize player coordinates in world space

		sf::Color posColor = sf::Color::Yellow;
		//std::string posStr = "(" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")";
		sf::Vector2f textPos = Math::ConvertScreenToWorldSpace(sf::Vector2i(0, 0));
		sf::Vector2f lineStart(static_cast<float>(textPos.x), static_cast<float>(textPos.y));
		lineStart.y += VIZ_DEFAULT_TEXT_SIZE;
		Visualizer::VisualizeText(Convenience::ConvertToString(pos), textPos, posColor);
		Visualizer::VisualizeSegment(lineStart, pos, posColor);

		// Visualize posDelta

		sf::Color posDeltaColor = sf::Color::Magenta;
		sf::Vector2f halfTileDelta(TILE_SIZE_F / 2.f, TILE_SIZE_F / 2.f);
		//std::string posDeltaStr = "(" + std::to_string(posDelta.x) + ", " + std::to_string(posDelta.y) + ")";
		textPos.y += VIZ_DEFAULT_TEXT_SIZE;
		sf::Vector2f tempPosDelta = posDelta / deltaTime;
		Visualizer::VisualizeText(Convenience::ConvertToString(tempPosDelta), textPos, posDeltaColor);
		Visualizer::VisualizeSegment(pos + halfTileDelta, pos + halfTileDelta + tempPosDelta, posDeltaColor);
	}
	if (DEBUG_PLAYER_STATE)
	{
		std::string stateStr;
		if (pCurrentState == &PlayerFSM::falling) stateStr = "fall";
		else if (pCurrentState == &PlayerFSM::idle) stateStr = "idle";
		else if (pCurrentState == &PlayerFSM::jumping) stateStr = "jump";
		else if (pCurrentState == &PlayerFSM::walking) stateStr = "walk";
		else assert(false); // just in case we add any states and forget to update the debug code, this'll crash to remind us
		sf::Vector2f textPos = Math::ConvertScreenToWorldSpace(sf::Vector2i(0, VIZ_DEFAULT_TEXT_SIZE * 2));
		Visualizer::VisualizeText(stateStr, textPos, sf::Color::Cyan);
	}
	if (DEBUG_LEVEL_SCROLL_BOUNDS)
	{
		pLevel->DebugLevelScrollBounds(pCurrentRoom);
	}
}

void Player::Alarm0()
{
	applyGravity = true;
}

void Player::KeyPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
	case WALK_LEFT_KEY:
		walkLeftKeyDown = true;
		facing = -1;
		break;
	case WALK_RIGHT_KEY:
		walkRightKeyDown = true;
		facing = 1;
		break;
	case JUMP_KEY:
		jumpKeyDown = true;
		break;
	}
}

void Player::KeyReleased(sf::Keyboard::Key key)
{
	switch (key)
	{
	case WALK_LEFT_KEY:
		walkLeftKeyDown = false;
		break;
	case WALK_RIGHT_KEY:
		walkRightKeyDown = false;
		break;
	case JUMP_KEY:
		break;
	}
}

bool Player::IsApplyGravity()
{
	return applyGravity;
}

void Player::ProcessInputs(float deltaTime)
{
	posDelta.x = 0.f;

	if (walkLeftKeyDown)
	{
		posDelta.x -= speed * deltaTime;
		//posDelta.x -= speed;
	}
	if (walkRightKeyDown)
	{
		posDelta.x += speed * deltaTime;
		//posDelta.x += speed;
	}
	if (isGrounded && jumpKeyDown)
	{
		posDelta.y = JUMP_FORCE * deltaTime;
		applyGravity = false; // temporarily stop applying gravity to allow variable height jumping
		RequestAlarmRegistration(AlarmID::Alarm0, MAX_JUMP_HOLD_TIME);
	}
}

void Player::SetCurrentRoom(RoomData* _pCurrentRoom)
{
	pCurrentRoom = _pCurrentRoom;
	if (pCurrentRoom->HasPlayerSpawn())
	{
		respawnPoint = *(pCurrentRoom->GetPlayerSpawnPoint());
	}
}

void Player::SetAnimationIdle()
{
	pAnimComp->SetAnimation("idle");
}

void Player::SetAnimationWalk()
{
	pAnimComp->SetAnimation("walk");
}

void Player::SetAnimationJump()
{
	pAnimComp->SetAnimation("jump");
}

void Player::SetAnimationFall()
{
	pAnimComp->SetAnimation("fall");
}

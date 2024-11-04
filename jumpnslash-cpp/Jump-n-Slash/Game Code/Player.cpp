#include "Player.h"

#include <iostream>

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
#include "PlayerControlKeyboard.h"

Player::Player(LevelMap* pLevel, ControlScheme scheme)
	: Actor(PLAYER_WALK_SPEED, pLevel),
	pCtrlStrat(nullptr),
	pCurrentState(&PlayerFSM::idle),
	pPrevState(nullptr),
	respawnPoint(),
	//inputReceivedWalkLeft(false),
	//inputReceivedWalkRight(false),
	inputWalkDir(0.f),
	inputReceivedJump(false),
	applyGravity(true)
{	
	assert(pCurrentState != nullptr);

	switch (scheme)
	{
	case ControlScheme::Keyboard:
		pCtrlStrat = new PlayerControlKeyboard();
		break;
	case ControlScheme::SwitchPro:
		assert(false);
		break;
	case ControlScheme::DualSense:
		assert(false);
		break;
	default:
		assert(false);
	}

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
	SetWidth();
	SetHeight();

	// register with the engine
	RequestUpdateRegistration();
	RequestDrawRegistration();
	RequestKeyRegistration(KB_JUMP, KeyEvent::KeyPress);
	RequestKeyRegistration(KB_JUMP, KeyEvent::KeyRelease);
	RequestKeyRegistration(KB_WALK_LEFT, KeyEvent::KeyPress);
	RequestKeyRegistration(KB_WALK_LEFT, KeyEvent::KeyRelease);
	RequestKeyRegistration(KB_WALK_RIGHT, KeyEvent::KeyPress);
	RequestKeyRegistration(KB_WALK_RIGHT, KeyEvent::KeyRelease);

	SetCollisionSprite(pSprite, VolumeType::BSphere);
}

Player::~Player()
{
	delete pCtrlStrat;
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
	if (pos.x < roomMin.x || roomMax.x <= pos.x || pos.y < roomMin.y || roomMax.y < pos.y)
	{
		Notify(ObserverEvent::PlayerOutsideCurrentRoom);
	}

	// update the camera
	sf::Vector2f newCamCenter = Math::ClampPoint(pos, pCurrentRoom->GetScrollMinBounds(), pCurrentRoom->GetScrollMaxBounds());
	SceneManager::GetCurrentCamera()->SetCenter(newCamCenter);

	// reset the player's y-velocity if they're grounded (so we don't continuously accelerate downwards)
	if ((grounded && !inputReceivedJump) || headBonked)
	{
		posDelta.y = 0.f;
		if (headBonked == true)
		{
			headBonked = false;
		}
	}

	// update the sprite
	assert(pSprite != nullptr);
	pSprite = pAnimComp->GetCurrentFrame();
	SetWidth();
	SetHeight();

	if (facing == 1)
	{
		pSprite->setOrigin(0.f, 0.f);
	}
	else if (facing == -1)
	{
		pSprite->setOrigin(TILE_SIZE_F, 0.f);
	}
	else
	{
		assert(false);
	}
	pSprite->setScale(sf::Vector2f(static_cast<float>(facing), 1.f));
	pSprite->setPosition(pos);
	UpdateCollisionData(pSprite);

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
	case KB_WALK_LEFT:
		//inputReceivedWalkLeft = true;
		inputWalkDir -= 1.f;
		if (inputWalkDir < -1.f) inputWalkDir = -1.f;
		facing = -1;
		break;
	case KB_WALK_RIGHT:
		//inputReceivedWalkRight = true;
		inputWalkDir += 1.f;
		if (inputWalkDir > 1.f) inputWalkDir = 1.f;
		facing = 1;
		break;
	case KB_JUMP:
		inputReceivedJump = true;
		break;
	}
}

void Player::KeyReleased(sf::Keyboard::Key key)
{
	switch (key)
	{
	case KB_WALK_LEFT:
		//inputReceivedWalkLeft = false;
		inputWalkDir += 1.f;
		if (inputWalkDir < 0.f) inputWalkDir = 0.f;
		break;
	case KB_WALK_RIGHT:
		//inputReceivedWalkRight = false;
		inputWalkDir -= 1.f;
		if (inputWalkDir > 0.f) inputWalkDir = 0.f;
		break;
	case KB_JUMP:
		inputReceivedJump = false;
		break;
	}
}

bool Player::IsApplyGravity()
{
	return applyGravity;
}

void Player::OnCollisionEnter(CollisionObject* pOther)
{
	if (DEBUG_COLLISION) std::cout << "Player has entered collision" << std::endl;
}

void Player::OnCollisionDuring(CollisionObject* pOther)
{
	// do nothing
}

void Player::OnCollisionExit(CollisionObject* pOther)
{
	if (DEBUG_COLLISION) std::cout << "Player has exited collision" << std::endl;
}

void Player::ProcessInputs(float deltaTime)
{
	posDelta.x = speed * inputWalkDir * deltaTime;

	if (grounded && inputReceivedJump)
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

#include "Player.h"

// language includes
#include <iostream>

// engine includes
#include "../Engine Code/SpriteManager.h"
#include "../Engine Code/AnimationManager.h"
#include "../Engine Code/Visualizer.h"
#include "../Engine Code/Math.h"
#include "../Engine Code/SceneManager.h"
#include "../Engine Code/Camera.h"
#include "../Engine Code/AnimationSet.h"
#include "../Engine Code/Animation.h"
#include "../Engine Code/ConvenienceFunctions.h"
#include "../Engine Code/ControlManager.h"

// game includes
#include "Constants.h"
#include "GameDebugFlags.h"
#include "ParamsPlayer.h"
#include "PlayerMoveState.h"
#include "PlayerMoveFSM.h"
#include "LevelMap.h"
#include "LevelTile.h"
#include "RoomData.h"
#include "PlayerControlKeyboard.h"
#include "PlayerControlSwitchPro.h"
#include "PlayerControlDualSense.h"
#include "ControllerDebugger.h"
#include "Sword.h"
#include "SwordAttorney.h"

Player::Player(LevelMap* pLevel)
	: Actor(Movement::GROUNDED_HORIZONTAL_MOVE_SPEED, pLevel),
	pCtrlStrat(nullptr),
	pCurrentState(&PlayerMoveFSM::idle),
	pPrevState(nullptr),
	pSword(new Sword(this)),
	respawnPoint(),
	inputWalkDir(0.f),
	inputReceivedJump(false),
	inputReceivedSlashAtk(false),
	applyGravity(true),
	attacking(false),
	heightBeforeJump(0.f),
	peakJumpHeight(heightBeforeJump)
{	
	assert(pCurrentState != nullptr);

	RequestSceneEntry();
}

Player::~Player()
{
	delete pCtrlStrat;
	delete pSword;
}

void Player::Update(float deltaTime)
{
	assert(pLevel != nullptr);
	assert(pCurrentRoom != nullptr);

	// update the inputs
	pCtrlStrat->GetInputs();

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
	UpdateSprite();

	FaceSprite();
	pSprite->SetPosition(pos);
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
	if (DEBUG_PLAYER_MOVE_STATE)
	{
		std::string stateStr;
		if (pCurrentState == &PlayerMoveFSM::falling) stateStr = "fall";
		else if (pCurrentState == &PlayerMoveFSM::idle) stateStr = "idle";
		else if (pCurrentState == &PlayerMoveFSM::jumping) stateStr = "jump";
		else if (pCurrentState == &PlayerMoveFSM::walking) stateStr = "walk";
		else if (pCurrentState == &PlayerMoveFSM::slashAtk) stateStr = "slashAtk";
		else assert(false); // just in case we add any states and forget to update the debug code, this'll crash to remind us
		sf::Vector2f textPos = Math::ConvertScreenToWorldSpace(sf::Vector2i(0, VIZ_DEFAULT_TEXT_SIZE * 2));
		Visualizer::VisualizeText(stateStr, textPos, sf::Color::Cyan);
	}
	if (DEBUG_LEVEL_SCROLL_BOUNDS)
	{
		pLevel->DebugLevelScrollBounds(pCurrentRoom);
	}
	if (DEBUG_CONTROLLER_INPUT)
	{
		ControllerDebugger::DisplayDebugInfo();
	}
	if (DEBUG_CONNECTORS) pSprite->DebugConnectors();
}

void Player::Alarm0()
{
	assert(false);
	applyGravity = true;
}

void Player::Alarm1()
{
	assert(pCurrentState == &PlayerMoveFSM::slashAtk);
	attacking = false;
}

bool Player::IsApplyGravity()
{
	return applyGravity;
}

bool Player::IsReceivingSlashInput()
{
	return inputReceivedSlashAtk;
}

bool Player::IsAttacking()
{
	return attacking;
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

void Player::OnSceneEntry()
{
	SetControls(ControlManager::GetControlScheme());

	// connect to map
	pLevel->LinkToPlayer(this);

	// do animation stuff
	pAnimComp->DefineAnimation("idle", AnimationManager::GetAnimation("player idle"));
	pAnimComp->DefineAnimation("walk", AnimationManager::GetAnimation("player walk"));
	pAnimComp->DefineAnimation("jump", AnimationManager::GetAnimation("player jump"));
	pAnimComp->DefineAnimation("fall", AnimationManager::GetAnimation("player fall"));
	pAnimComp->DefineAnimation("attack", AnimationManager::GetAnimation("player attack"));

	pAnimComp->SetAnimation("idle");

	pSprite = pAnimComp->GetCurrentFrame();
	SetWidth();
	SetHeight();

	SetCollisionObjectGroup<Player>();
	SetCollisionSprite(pSprite, VolumeType::BSphere);
	RequestCollisionRegistration();
}

void Player::OnSceneExit()
{
	RequestCollisionDeregistration();
}

void Player::ProcessInputs(float deltaTime)
{
	posDelta.x = speed * inputWalkDir * deltaTime;

	if (inputReceivedJump == true && heightBeforeJump - peakJumpHeight <= Movement::MAX_JUMP_HEIGHT)
	{
		if (grounded)
		{
			posDelta.y = -Movement::JUMP_RISING_SPEED * deltaTime;
			applyGravity = false; // temporarily stop applying gravity to allow variable height jumping
			heightBeforeJump = pos.y;
		}
		else if(pos.y < peakJumpHeight)
		{
			peakJumpHeight = pos.y;
			//std::cout << peakJumpHeight << std::endl;
		}
	}
	else if(inputReceivedJump == false || heightBeforeJump - peakJumpHeight > Movement::MAX_JUMP_HEIGHT)
	{
		// the following if block is what makes the player begin descending the moment they release the jump button
		if (applyGravity == false)
		{
			posDelta.y = 0.f;
		}

		applyGravity = true;
		
		if (grounded)
		{
			heightBeforeJump = pos.y;
			peakJumpHeight = heightBeforeJump;
		}
	}
}

void Player::SetControls(ControlScheme ctrl)
{
	// TODO: consider factory/obj pool pattern for changing control schemes
	
	if (pCtrlStrat != nullptr)
	{
		delete pCtrlStrat;
	}

	switch (ctrl)
	{
	case ControlScheme::Keyboard:
		pCtrlStrat = new PlayerControlKeyboard(this);
		break;
	case ControlScheme::SwitchPro:
		pCtrlStrat = new PlayerControlSwitchPro(this);
		break;
	case ControlScheme::DualSense:
		pCtrlStrat = new PlayerControlDualSense(this);
		break;
	default:
		assert(false);
	}
}

void Player::ApplyGravity(float deltaTime)
{
	posDelta.y += Movement::PLAYER_GRAVITY * deltaTime;
}

void Player::SetWalk(float direction)
{
	assert(-1.f <= direction);
	assert(direction <= 1.f);

	inputWalkDir = direction;
	if (inputWalkDir < 0 && facing > 0)
	{
		facing = -1;
	}
	else if (inputWalkDir > 0 && facing < 0)
	{
		facing = 1;
	}
}

void Player::SetJump(bool enabled)
{
	inputReceivedJump = enabled;
}

void Player::SetSlash(bool enabled)
{
	inputReceivedSlashAtk = enabled;
}

void Player::SetCurrentRoom(RoomData* _pCurrentRoom)
{
	pCurrentRoom = _pCurrentRoom;
	if (pCurrentRoom->HasPlayerSpawn())
	{
		respawnPoint = *(pCurrentRoom->GetPlayerSpawnPoint());
	}
}

void Player::BeginSlashAtk()
{
	if (attacking == false) // only allow attacks if you're not currently attacking
	{
		SwordAttorney::PlayerAccess::Attack(pSword);
		RequestAlarmRegistration(AlarmID::Alarm1, SlashAtk::SLASH_ACTIVE_TIME);
		attacking = true;
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

void Player::SetAnimationAttack()
{
	pAnimComp->SetAnimation("attack");
}

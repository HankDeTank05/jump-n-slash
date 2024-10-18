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

Player::Player()
	: pos(),
	posDelta(0.f, 0.f),
	speed(PLAYER_WALK_SPEED),
	animComp(),
	pSprite(nullptr),
	pCurrentState(&PlayerFSM::idle),
	pPrevState(nullptr),
	respawnPoint(),
	pLevel(nullptr),
	pCurrentRoom(nullptr),
	walkLeftKeyDown(false),
	walkRightKeyDown(false),
	jumpKeyDown(false),
	isGrounded(false),
	facing(1)
{	
	assert(pCurrentState != nullptr);

	/*
	Animation* pIdle = new Animation(ANIMATION_FRAMERATE);
	pIdle->AddFrame(SpriteManager::GetSprite("player idle 1"));
	pIdle->AddFrame(SpriteManager::GetSprite("player idle 2"));
	pIdle->AddFrame(SpriteManager::GetSprite("player idle 3"));
	pIdle->AddFrame(SpriteManager::GetSprite("player idle 4"));

	Animation* pWalk = new Animation(ANIMATION_FRAMERATE);
	pWalk->AddFrame(SpriteManager::GetSprite("player walk 1"));
	pWalk->AddFrame(SpriteManager::GetSprite("player walk 2"));
	pWalk->AddFrame(SpriteManager::GetSprite("player walk 3"));
	pWalk->AddFrame(SpriteManager::GetSprite("player walk 4"));

	Animation* pJump = new Animation(ANIMATION_FRAMERATE);
	pJump->AddFrame(SpriteManager::GetSprite("player jump 1"));
	pJump->AddFrame(SpriteManager::GetSprite("player jump 2"));
	pJump->AddFrame(SpriteManager::GetSprite("player jump 3"));
	pJump->AddFrame(SpriteManager::GetSprite("player jump 4"));

	Animation* pFall = new Animation(ANIMATION_FRAMERATE);
	pFall->AddFrame(SpriteManager::GetSprite("player fall 1"));
	pFall->AddFrame(SpriteManager::GetSprite("player fall 2"));
	pFall->AddFrame(SpriteManager::GetSprite("player fall 3"));
	pFall->AddFrame(SpriteManager::GetSprite("player fall 4"));
	//*/

	AnimationSet* pAnimSet = new AnimationSet();
	/*
	pAnimSet->AddAnimation("idle", pIdle);
	pAnimSet->AddAnimation("walk", pWalk);
	pAnimSet->AddAnimation("jump", pJump);
	pAnimSet->AddAnimation("fall", pFall);
	//*/
	//*
	pAnimSet->AddAnimation("idle", AnimationManager::GetAnimation("player idle"));
	pAnimSet->AddAnimation("walk", AnimationManager::GetAnimation("player walk"));
	pAnimSet->AddAnimation("jump", AnimationManager::GetAnimation("player jump"));
	pAnimSet->AddAnimation("fall", AnimationManager::GetAnimation("player fall"));
	//*/

	animComp.DefineAnimationSet(pAnimSet);
	animComp.SetAnimation("idle");
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

	// set the sprite position for drawing
	pSprite = animComp.GetCurrentFrame();
	if (facing == 1)
	{
		pSprite->setOrigin(0.f, 0.f);
	}
	else if (facing == -1)
	{
		pSprite->setOrigin(32.f, 0.f);
	}
	pSprite->setScale(static_cast<float>(facing), 1.f);
	pSprite->setPosition(pos);

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

void Player::Draw()
{
	assert(pSprite != nullptr);
	Render(*pSprite);
}

void Player::Alarm0()
{
	assert(false);
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

void Player::LinkToMap(LevelMap* _pLevel)
{
	pLevel = _pLevel;
	pLevel->LinkToPlayer(this);
	RequestUpdateRegistration();
	RequestDrawRegistration();
	RequestKeyRegistration(JUMP_KEY, KeyEvent::KeyPress);
	RequestKeyRegistration(JUMP_KEY, KeyEvent::KeyRelease);
	RequestKeyRegistration(WALK_LEFT_KEY, KeyEvent::KeyPress);
	RequestKeyRegistration(WALK_LEFT_KEY, KeyEvent::KeyRelease);
	RequestKeyRegistration(WALK_RIGHT_KEY, KeyEvent::KeyPress);
	RequestKeyRegistration(WALK_RIGHT_KEY, KeyEvent::KeyRelease);
}

sf::Vector2f Player::GetPos() const
{
	return pos;
}

sf::Vector2f Player::GetPosDelta() const
{
	return posDelta;
}

LevelMap* Player::GetLevel() const
{
	return pLevel;
}

bool Player::IsGrounded() const
{
	return isGrounded;
}

void Player::RaycastRight(float deltaTime)
{
	const int RAY_COUNT = 2;
	std::array<sf::Vector2f, RAY_COUNT> startPos;
	std::array<sf::Vector2f, RAY_COUNT> endPos;

	// cast a ray from the top (index=0) and the bottom (index=1) of the sprite
	startPos[0] = pos + sf::Vector2f(TILE_SIZE_F, 0.f);
	startPos[1] = pos + sf::Vector2f(TILE_SIZE_F, TILE_SIZE_F - 0.001f); // subtract a little just in case we reach into the next tile (this only happens when pos.y is a whole number)

	float minX = MAX_LEVEL_SIZE * TILE_SIZE_F;

	for (int i = 0; i < RAY_COUNT; i++)
	{
		sf::Vector2f currPos = startPos[i];

		// Edge case: the player is partially inside a tile that's solid on the left
		LevelTile* pTile = pLevel->GetTileAtPos(currPos); // The tile in which the raycast begins

		if (pTile != nullptr && // Is this tile empty
			pTile->IsSolidOnSides() && // Is this tile solid on the sides
			pos.x + TILE_SIZE_F > pTile->GetPos().x) // Is the right edge of the player to the right of the left edge of this tile
		{
			// Visuals for debugging ONLY
			if (DEBUG_PLAYER_MAP_COLLISION)
			{
				Visualizer::VisualizePoint(currPos, sf::Color::Green);
			}

			currPos.x += TILE_SIZE_F;
		}

		// While the current position is empty or NOT solid on the sides, and within the bounds of the map
		while ((pLevel->GetTileAtPos(currPos) == nullptr || pLevel->GetTileAtPos(currPos)->IsSolidOnSides() == false) &&
			currPos.x < MAX_LEVEL_SIZE * TILE_SIZE_F)
		{
			// Visuals for debugging ONLY
			if (DEBUG_PLAYER_MAP_COLLISION)
			{
				Visualizer::VisualizePoint(currPos, sf::Color::Green);
			}

			// For iterations through the while loop after the first
			if (std::floorf(currPos.x) == currPos.x)
			{
				// increment by tile size, since we only want to check every tile space
				currPos.x += TILE_SIZE_F;
			}
			else // we may be in the middle of a tile space, so we want to increment to the edge of the next tile space
			{
				// if we divide by tile size, and cast to an int (remove the fractional part), we get the x-index of the tile
				int tileIndex = static_cast<int>(currPos.x / TILE_SIZE_F);

				// re-multiply by tile size to get the edge of the next tile space
				currPos.x = static_cast<float>(tileIndex) * TILE_SIZE_F;

				// increment by tile size, since the above math gets a point that is behind the starting pos
				currPos.x += TILE_SIZE_F;
			}
		}

		endPos[i] = currPos;
		if (endPos[i].x < minX)
		{
			minX = endPos[i].x;
		}
		if (DEBUG_PLAYER_MAP_COLLISION)
		{
			Visualizer::VisualizeSegment(startPos[i], endPos[i]);
			Visualizer::VisualizePoint(endPos[i], sf::Color::Red);
			Visualizer::VisualizeText(std::to_string(endPos[i].x), endPos[i], sf::Color::Red);
		}
	}

	sf::Vector2f mayMoveTo = pos + posDelta + sf::Vector2f(TILE_SIZE_F, 0.f); // The position the player wants to move to

	if (mayMoveTo.x < minX)
	{
		minX = mayMoveTo.x;
	}
	pos.x = minX - TILE_SIZE_F;
}

void Player::RaycastLeft(float deltaTime)
{
	const int RAY_COUNT = 2;
	std::array<sf::Vector2f, RAY_COUNT> startPos;
	std::array<sf::Vector2f, RAY_COUNT> endPos;

	// cast a ray from the top (index=0) and the bottom (index=1) of the sprite
	startPos[0] = pos;
	startPos[1] = pos + sf::Vector2f(0.f, TILE_SIZE_F - 0.001f); // subtract a little just in case we reach into the next tile (this only happens when pos.y is a whole number)

	float maxX = 0;

	for (int i = 0; i < RAY_COUNT; i++)
	{
		sf::Vector2f currPos = startPos[i];

		while ((pLevel->GetTileAtPos(currPos) == nullptr || pLevel->GetTileAtPos(currPos)->IsSolidOnSides() == false) &&
			currPos.x >= 0.f)
		{
			// only visualize stuff if we're debugging
			if (DEBUG_PLAYER_MAP_COLLISION) Visualizer::VisualizePoint(currPos, sf::Color::Green);

			if (currPos != startPos[i])
			{
				// decrement by tile size, since we only want to check every tile space
				currPos.x -= TILE_SIZE_F;
			}
			else // we may be in the middle of a tile space, so we want to decrement to the edge of the next tile space
			{
				// if we divide by tile size, and cast to an int (remove the fractional part), we get the x-index of the tile
				int tileIndex = static_cast<int>(currPos.x / TILE_SIZE_F);

				// re-multiply by tile size to get the edge of the next tile space
				currPos.x = static_cast<float>(tileIndex) * TILE_SIZE_F;

				// Edge case: the player's x-position is a whole number (the player is already on the edge of a tile)
				if (currPos == startPos[i])
				{
					currPos.x -= TILE_SIZE_F;
				}
			}
		}

		// Account for the while loop going one tile further than we want it to
		currPos.x += TILE_SIZE_F;

		endPos[i] = currPos;
		if (endPos[i].x > maxX)
		{
			maxX = endPos[i].x;
		}

		// only visualize stuff if we're debugging
		if (DEBUG_PLAYER_MAP_COLLISION)
		{
			Visualizer::VisualizeSegment(startPos[i], endPos[i]);
			Visualizer::VisualizePoint(endPos[i], sf::Color::Red);
			Visualizer::VisualizeText(std::to_string(endPos[i].x), endPos[i], sf::Color::Red);
		}
	}

	//sf::Vector2f mayMoveTo = pos + posDelta * deltaTime;
	sf::Vector2f mayMoveTo = pos + posDelta;

	if (mayMoveTo.x > maxX)
	{
		maxX = mayMoveTo.x;
	}
	pos.x = maxX;
}

void Player::RaycastUp(float deltaTime)
{
	const int RAY_COUNT = 2;
	std::array<sf::Vector2f, RAY_COUNT> startPos;
	std::array<sf::Vector2f, RAY_COUNT> endPos;

	// Cast a ray from the left (index=0) and right (index=1) of the sprite
	startPos[0] = pos;
	startPos[1] = pos + sf::Vector2f(TILE_SIZE_F - 0.001f, 0.f); // subtract a little just in case we reach into the next tile (this only happens when pos.x is a whole number)

	// The highest point the player can move to without being inside of a wall
	float maxY = 0;

	for (int i = 0; i < RAY_COUNT; i++) {
		sf::Vector2f currPos = startPos[i];

		// While the current position is empty or NOT solid underneath, and within the bounds of the map
		while ((pLevel->GetTileAtPos(currPos) == nullptr || !pLevel->GetTileAtPos(currPos)->IsSolidOnBottom()) && currPos.y >= 0.0f) {
			// Visuals for debugging ONLY
			if (DEBUG_PLAYER_MAP_COLLISION) {
				Visualizer::VisualizePoint(currPos, sf::Color::Green);
			}

			// For iterations through the while loop after the first
			if (currPos != startPos[i]) {
				// We only need to check every tile space, so decrement by tile size
				currPos.y -= TILE_SIZE_F;
			}
			else { // First iteration through the while loop; we may be in the middle of a tile, so decrement to the edge of the nearest tile space
				// We can get the y-index of a tile by dividing the y position by tile size and casting to an int to remove the decimal
				int tileIndex = static_cast<int>(currPos.y / TILE_SIZE_F);

				// Multiplying by tile size again gets the position of the edge of the current tile
				currPos.y = static_cast<float>(tileIndex) * TILE_SIZE_F;

				// Edge case: the player's y-position is a whole number (the player is already on the edge of a tile)
				if (currPos == startPos[i])
				{
					currPos.y -= TILE_SIZE_F;
				}
			}
		}

		// Account for the while loop going one tile further than we want it to
		currPos.y += TILE_SIZE_F;

		endPos[i] = currPos;
		if (endPos[i].y > maxY) {
			maxY = endPos[i].y;
		}

		// Visuals for debugging ONLY
		if (DEBUG_PLAYER_MAP_COLLISION) {
			Visualizer::VisualizeSegment(startPos[i], endPos[i]);
			Visualizer::VisualizePoint(endPos[i], sf::Color::Red);
			if (i == 0) Visualizer::VisualizeText(std::to_string(endPos[i].y), endPos[i] + sf::Vector2f(0.f, -VIZ_DEFAULT_TEXT_SIZE), sf::Color::Red);
			else Visualizer::VisualizeText(std::to_string(endPos[i].y), endPos[i], sf::Color::Red);
		}
	}

	//sf::Vector2f mayMoveTo = pos + posDelta * deltaTime; // The position the player wants to move to
	sf::Vector2f mayMoveTo = pos + posDelta;

	// If the player's projected movement is in an invalid location, then move them the maximum distance allowed
	if (mayMoveTo.y > maxY) {
		maxY = mayMoveTo.y;
	}

	isGrounded = pos.y == maxY;

	pos.y = maxY;
}

void Player::RaycastDown(float deltaTime)
{
	const int RAY_COUNT = 2;
	std::array<sf::Vector2f, RAY_COUNT> startPos;
	std::array<sf::Vector2f, RAY_COUNT> endPos;

	// Cast a ray downwards from the left (index=0) and right (index=1) edges of the sprite; we add tile size to the y-value to begin our raycast at the bottom of the player's sprite
	startPos[0] = pos + sf::Vector2f(0.f, TILE_SIZE_F);
	startPos[1] = pos + sf::Vector2f(TILE_SIZE_F - 0.001f, TILE_SIZE_F); // subtract a little just in case we reach into the next tile (this only happens when pos.x is a whole number)

	// The lowest point the player can move to without being inside of a wall
	float minY = MAX_LEVEL_SIZE * TILE_SIZE_F;

	for (int i = 0; i < RAY_COUNT; i++)
	{
		sf::Vector2f currPos = startPos[i];

		// Edge case: the player is partially inside a tile that's solid on top
		LevelTile* pTile = pLevel->GetTileAtPos(currPos); // The tile in which the raycast begins

		if (pTile != nullptr && // Is this tile empty
			pTile->IsSolidOnTop() && // Is this tile solid on top
			pos.y + TILE_SIZE_F > pTile->GetPos().y) // Is the bottom edge of the player below the top edge of this tile
		{
			// Visuals for debugging ONLY
			if (DEBUG_PLAYER_MAP_COLLISION)
			{
				Visualizer::VisualizePoint(currPos, sf::Color::Green);
			}

			currPos.y += TILE_SIZE_F;
		}

		// While the current position is empty or NOT solid on top, and within the bounds of the map
		while ((pLevel->GetTileAtPos(currPos) == nullptr || pLevel->GetTileAtPos(currPos)->IsSolidOnTop() == false) &&
			currPos.y <= MAX_LEVEL_SIZE * TILE_SIZE_F)
		{

			// Visuals for debugging ONLY
			if (DEBUG_PLAYER_MAP_COLLISION)
			{
				Visualizer::VisualizePoint(currPos, sf::Color::Green);
			}

			// For iterations through the while loop after the first
			if (std::floorf(currPos.y) == currPos.y)
			{
				currPos.y += TILE_SIZE_F;
			}
			else // First iteration through the while loop; we may be in the middle of a tile, so increment to the top edge of the next tile below
			{
				// We can get the y-index of a tile by dividing the y position by tile size and casting to an int to remove the decimal
				int tileIndex = static_cast<int>(currPos.y / TILE_SIZE_F);

				// Multiplying by tile size again gets the position of the edge of the current tile
				currPos.y = static_cast<float>(tileIndex) * TILE_SIZE_F;

				// Increment by tile size because currPos is above startPos[i]
				currPos.y += TILE_SIZE_F;
			}
		}

		endPos[i] = currPos;
		if (endPos[i].y < minY)
		{
			minY = endPos[i].y;
		}

		// Visuals for debugging ONLY
		if (DEBUG_PLAYER_MAP_COLLISION)
		{
			Visualizer::VisualizeSegment(startPos[i], endPos[i]);
			Visualizer::VisualizePoint(endPos[i], sf::Color::Red);
			if (i == 0) Visualizer::VisualizeText(std::to_string(endPos[i].y), endPos[i] + sf::Vector2f(0, -VIZ_DEFAULT_TEXT_SIZE), sf::Color::Red);
			else Visualizer::VisualizeText(std::to_string(endPos[i].y), endPos[i], sf::Color::Red);
		}
	}

	sf::Vector2f mayMoveTo = pos + posDelta + sf::Vector2f(0.f, TILE_SIZE_F); // The position the player wants to move to
	
	// If the player's projected movement is in an invalid location, then move them the maximum distance allowed
	if (mayMoveTo.y < minY)
	{
		minY = mayMoveTo.y;
	}
	
	// Determine if we is grounded or not
	minY -= TILE_SIZE_F;
	isGrounded = pos.y == minY;

	pos.y = minY;
}

void Player::SetPos(sf::Vector2f newPos)
{
	pos = newPos;
}

void Player::ApplyGravity(float deltaTime)
{
	posDelta.y += GRAVITY_WEIGHT * deltaTime;
	//posDelta.y += GRAVITY_WEIGHT;
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
		//posDelta.y = JUMP_FORCE;
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
	animComp.SetAnimation("idle");
}

void Player::SetAnimationWalk()
{
	animComp.SetAnimation("walk");
}

void Player::SetAnimationJump()
{
	animComp.SetAnimation("jump");
}

void Player::SetAnimationFall()
{
	animComp.SetAnimation("fall");
}

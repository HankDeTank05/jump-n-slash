#include "Player.h"

#include "../Engine Code/SpriteManager.h"
#include "../Engine Code/Visualizer.h"

#include "Constants.h"
#include "DebugFlags.h"
#include "DesignerControls.h"
#include "PlayerMoveState.h"
#include "PlayerFSM.h"
#include "LevelMap.h"
#include "LevelTile.h"

Player::Player(LevelMap* _pLevel)
	: pos(_pLevel->GetStartingSpawnPoint()),
	posDelta(0.f, 0.f),
	speed(PLAYER_WALK_SPEED),
	pSprite(SpriteManager::GetSprite("player idle 1")),
	pCurrentState(&PlayerFSM::idle),
	pPrevState(pCurrentState),
	respawnPoint(_pLevel->GetStartingSpawnPoint()),
	pLevel(_pLevel),
	walkLeftKeyDown(false),
	walkRightKeyDown(false),
	jumpKeyDown(false),
	isGrounded(false)
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
	// update the move state
	pCurrentState = pCurrentState->GetNextState(this);
	if (pCurrentState != pPrevState)
	{
		pCurrentState->Enter(this);
	}

	Move(deltaTime);

	// update based on the current move state
	pCurrentState->Update(this, deltaTime);

	// reset the player's y-velocity if they're grounded (so we don't continuously accelerate downwards)
	if (isGrounded && !jumpKeyDown)
	{
		posDelta.y = 0.f;
	}
	if (jumpKeyDown)
	{
		jumpKeyDown = false;
	}

	// set the sprite position for drawing
	pSprite->setPosition(pos);
	if (DEBUG_PLAYER_POSITION)
	{
		// Visualize player coordinates in world space
		sf::Color posColor = sf::Color::Yellow;
		Visualizer::VisualizePoint(pos, posColor);
		std::string posStr = "(" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")";
		Visualizer::VisualizeText(posStr, sf::Vector2f(0.f, 0.f), posColor);
		Visualizer::VisualizeSegment(sf::Vector2f(0.f, VIZ_DEFAULT_TEXT_SIZE), pos, posColor);

		// Visualize posDelta
		sf::Color posDeltaColor = sf::Color::Magenta;
		sf::Vector2f halfTileDelta(TILE_SIZE_F / 2.f, TILE_SIZE_F / 2.f);
		Visualizer::VisualizeSegment(pos + halfTileDelta, pos + halfTileDelta + posDelta, posDeltaColor);
	}
	if (DEBUG_PLAYER_STATE)
	{
		std::string stateStr;
		if (pCurrentState == &PlayerFSM::falling) stateStr = "falling";
		else if (pCurrentState == &PlayerFSM::idle) stateStr = "idle";
		else if (pCurrentState == &PlayerFSM::jumping) stateStr = "jumping";
		else if (pCurrentState == &PlayerFSM::walking) stateStr = "walking";
		else assert(false); // just in case we add any states and forget to update the debug code, this'll crash to remind us
		Visualizer::VisualizeText(stateStr, sf::Vector2f(0.f, VIZ_DEFAULT_TEXT_SIZE * 1), sf::Color::Cyan);
	}
	pPrevState = pCurrentState;
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
		walkLeftKeyDown = true;
		break;
	case WALK_RIGHT_KEY:
		walkRightKeyDown = true;
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
	}
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
	startPos[0] = pos;
	startPos[1] = pos + sf::Vector2f(0.f, TILE_SIZE_F - 0.001f); // subtract a little just in case we reach into the next tile (this only happens when pos.y is a whole number)

	float minX = MAX_LEVEL_SIZE * TILE_SIZE_F;

	for (int i = 0; i < RAY_COUNT; i++)
	{
		sf::Vector2f currPos = startPos[i];

		while ((pLevel->GetTileAtPos(currPos) == nullptr || pLevel->GetTileAtPos(currPos)->IsSolidOnSides() == false) &&
			currPos.x < MAX_LEVEL_SIZE * TILE_SIZE_F)
		{
			if (DEBUG_PLAYER_MAP_COLLISION) Visualizer::VisualizePoint(currPos, sf::Color::Green);
			if (currPos != startPos[i])
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
		currPos.x -= TILE_SIZE_F; // decrement by one tile size because everything is relative to the top left corner

		endPos[i] = currPos;
		if (endPos[i].x < minX)
		{
			minX = endPos[i].x;
		}
		if (DEBUG_PLAYER_MAP_COLLISION)
		{
			Visualizer::VisualizeSegment(startPos[i], endPos[i]);
			Visualizer::VisualizePoint(endPos[i], sf::Color::Red);
			Visualizer::VisualizeText(endPos[i].x, endPos[i], sf::Color::Red);
		}
	}

	sf::Vector2f mayMoveTo = pos + posDelta * deltaTime;

	if (mayMoveTo.x < minX)
	{
		minX = mayMoveTo.x;
	}
	pos.x = minX;
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
			Visualizer::VisualizeText(endPos[i].x, endPos[i], sf::Color::Red);
		}
	}

	sf::Vector2f mayMoveTo = pos + posDelta * deltaTime;
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
			if (i == 0) Visualizer::VisualizeText(endPos[i].y, endPos[i] + sf::Vector2f(0.f, -VIZ_DEFAULT_TEXT_SIZE), sf::Color::Red);
			else Visualizer::VisualizeText(endPos[i].y, endPos[i], sf::Color::Red);
		}
	}

	// The position the player wants to move to
	sf::Vector2f mayMoveTo = pos + posDelta * deltaTime;
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

	// Cast a ray from the left (index=0) and right (index=1) of the sprite
	startPos[0] = pos;
	startPos[1] = pos + sf::Vector2f(TILE_SIZE_F - 0.001f, 0.f); // subtract a little just in case we reach into the next tile (this only happens when pos.x is a whole number)

	// The lowest point the player can move to without being inside of a wall
	float minY = MAX_LEVEL_SIZE * TILE_SIZE_F;

	for (int i = 0; i < RAY_COUNT; i++)
	{
		sf::Vector2f currPos = startPos[i];

		// While the current position is empty or NOT solid on top, and within the bounds of the map
		while ((pLevel->GetTileAtPos(currPos) == nullptr || !pLevel->GetTileAtPos(currPos)->IsSolidOnTop()) && currPos.y <= MAX_LEVEL_SIZE * TILE_SIZE_F)
		{
			// Visuals for debugging ONLY
			if (DEBUG_PLAYER_MAP_COLLISION)
			{
				Visualizer::VisualizePoint(currPos, sf::Color::Green);
			}

			// For iterations through the while loop after the first
			if (currPos != startPos[i])
			{
				currPos.y += TILE_SIZE_F;
			}
			else // First iteration through the while loop; we may be in the middle of a tile, so increment to the edge of the nearest tile space
			{
				// We can get the y-index of a tile by dividing the y position by tile size and casting to an int to remove the decimal
				int tileIndex = static_cast<int>(currPos.y / TILE_SIZE_F);

				// Multiplying by tile size again gets the position of the edge of the current tile
				currPos.y = static_cast<float>(tileIndex) * TILE_SIZE_F;

				// Increment by tile size because currPos is above of startPos[i]
				currPos.y += TILE_SIZE_F;
			}
		}

		// Decrement by tile size because position is relative to the top left corner of the player
		currPos.y -= TILE_SIZE_F;

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
			if (i == 0) Visualizer::VisualizeText(endPos[i].y, endPos[i] + sf::Vector2f(0, -VIZ_DEFAULT_TEXT_SIZE), sf::Color::Red);
			else Visualizer::VisualizeText(endPos[i].y, endPos[i], sf::Color::Red);
		}
	}

	// The position the player wants to move to
	sf::Vector2f mayMoveTo = pos + posDelta * deltaTime;
	// If the player's projected movement is in an invalid location, then move them the maximum distance allowed
	if (mayMoveTo.y < minY)
	{
		minY = mayMoveTo.y;
	}
	
	// Determine if we is grounded or not
	isGrounded = pos.y == minY;

	pos.y = minY;
}

void Player::ApplyGravity(float deltaTime)
{
	posDelta.y += GRAVITY_WEIGHT * deltaTime;
}

void Player::Move(float deltaTime)
{
	posDelta.x = 0.f;

	if (walkLeftKeyDown)
	{
		posDelta.x -= speed;
	}
	if (walkRightKeyDown)
	{
		posDelta.x += speed;
	}
	if (isGrounded && jumpKeyDown)
	{
		posDelta.y = JUMP_FORCE;
	}
}

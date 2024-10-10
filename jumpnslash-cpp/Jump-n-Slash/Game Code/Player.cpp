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
	walkLeftHeld(false),
	walkRightHeld(false)
{
	RequestUpdateRegistration();
	RequestDrawRegistration();
	//RequestKeyRegistration(JUMP_KEY, KeyEvent::KeyPress);
	//RequestKeyRegistration(JUMP_KEY, KeyEvent::KeyRelease);
	RequestKeyRegistration(WALK_LEFT_KEY, KeyEvent::KeyPress);
	RequestKeyRegistration(WALK_LEFT_KEY, KeyEvent::KeyRelease);
	RequestKeyRegistration(WALK_RIGHT_KEY, KeyEvent::KeyPress);
	RequestKeyRegistration(WALK_RIGHT_KEY, KeyEvent::KeyRelease);
	RequestKeyRegistration(sf::Keyboard::Up, KeyEvent::KeyPress);
	RequestKeyRegistration(sf::Keyboard::Up, KeyEvent::KeyRelease);
	RequestKeyRegistration(sf::Keyboard::Down, KeyEvent::KeyPress);
	RequestKeyRegistration(sf::Keyboard::Down, KeyEvent::KeyRelease);
	
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

	// update based on the current move state
	pCurrentState->Update(this, deltaTime);

	// set the sprite position for drawing
	pSprite->setPosition(pos);
	if (DEBUG_PLAYER_POSITION)
	{
		Visualizer::VisualizePoint(pos, sf::Color::Yellow);
		std::string posStr = "(" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")";
		Visualizer::VisualizeText(posStr, sf::Vector2f(0.f, 0.f), sf::Color::Yellow);
		Visualizer::VisualizeSegment(sf::Vector2f(0.f, VIZ_DEFAULT_TEXT_SIZE), pos, sf::Color::Yellow);
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
		posDelta.x = -speed;
		break;
	case WALK_RIGHT_KEY:
		posDelta.x = speed;
		break;
	case sf::Keyboard::Up:
		posDelta.y = -speed;
		break;
	case sf::Keyboard::Down:
		posDelta.y = speed;
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

void Player::RaycastRight(float deltaTime)
{
	const int RAY_COUNT = 2;
	std::array<sf::Vector2f, RAY_COUNT> startPos;
	std::array<sf::Vector2f, RAY_COUNT> endPos;

	// cast a ray from the top (index=0) and the bottom (index=1) of the sprite
	startPos[0] = pos;
	startPos[1] = pos + sf::Vector2f(0.f, TILE_SIZE_F);

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
			Visualizer::VisualizeText(endPos[i].x, endPos[i]);
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
	startPos[1] = pos + sf::Vector2f(0.f, TILE_SIZE_F);

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

				currPos.x -= 0.001f;
			}
		}

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
			Visualizer::VisualizeText(endPos[i].x, endPos[i]);
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
	startPos[1] = pos + sf::Vector2f(TILE_SIZE_F, 0.0f);

	// The highest point the play can move to without being inside of a wall
	float maxY = 0;

	for (int i = 0; i < RAY_COUNT; i++) {
		sf::Vector2f curPos = startPos[i];

		// While the current position is empty or NOT solid underneath, and within the bounds of the map
		while ((pLevel->GetTileAtPos(curPos) == nullptr || !pLevel->GetTileAtPos(curPos)->IsSolidOnBottom()) && curPos.y >= 0.0f) {
			// Visuals for debugging ONLY
			if (DEBUG_PLAYER_MAP_COLLISION) {
				Visualizer::VisualizePoint(curPos, sf::Color::Green);
			}

			// For iterations through the while loop after the first
			if (curPos != startPos[i]) {
				// We only need to check every tile space, so decrement by tile size
				curPos.y -= TILE_SIZE_F;
			}
			else { // First iteration through the while loop; we may be in the middle of a tile, so decrement to the edge of the nearest tile space
				// We can get the y-index of a tile by dividing the y position by tile size and casting to an int to remove the decimal
				int tileIndex = static_cast<int>(curPos.y / TILE_SIZE_F);

				// Multiplying by tile size again gets the position of the edge of the current tile
				curPos.y = static_cast<float>(tileIndex) * TILE_SIZE_F;
			}
		}

		endPos[i] = curPos;
		if (endPos[i].y > maxY) {
			maxY = endPos[i].y;
		}

		// Visuals for debugging ONLY
		if (DEBUG_PLAYER_MAP_COLLISION) {
			Visualizer::VisualizeSegment(startPos[i], endPos[i]);
			Visualizer::VisualizePoint(endPos[i], sf::Color::Red);
			Visualizer::VisualizeText(endPos[i].y, endPos[i]);
		}
	}

	// The position the player wants to move to
	sf::Vector2f mayMoveTo = pos + posDelta * deltaTime;
	// If the player's projected movement is in an invalid location, move them the maximum distance allowed
	if (mayMoveTo.y > maxY) {
		maxY = mayMoveTo.y;
	}
	pos.y = maxY;
}

void Player::RaycastDown(float deltaTime)
{
	assert(false);
}

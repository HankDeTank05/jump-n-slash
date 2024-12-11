#include "Actor.h"

// engine includes
#include "../Engine Code/Visualizer.h"
#include "../Engine Code/AnimationComponent.h"
#include "../Engine Code/AnimationSet.h"

// game includes
#include "Constants.h"
#include "GameDebugFlags.h"
#include "ParamsPlayer.h"
#include "LevelTile.h"
#include "LevelMap.h"
#include "GameManagerAttorney.h"

Actor::Actor(float _speed)
	: pos(),
	posDelta(0.f, 0.f),
	width(0.f),
	height(0.f),
	speed(_speed),
	pAnimComp(new AnimationComponent()),
	pSprite(nullptr),
	pCurrentRoom(nullptr),
	grounded(false),
	headBonked(false),
	facing(1)
{
	// do nothing
}

Actor::~Actor()
{
	delete pAnimComp;
}

void Actor::Draw()
{
	assert(pCurrentRoom != nullptr); // TODO: this is bad and stupid but Henry told me to do it (bitch)

	Render(pSprite);
}

sf::Vector2f Actor::GetPos() const
{
	return pos;
}

sf::Vector2f Actor::GetPosDelta() const
{
	return posDelta;
}

float Actor::GetWidth() const
{
	return width;
}

float Actor::GetHeight() const
{
	return height;
}

float Actor::GetHeight() const
{
	return height;
}

bool Actor::IsGrounded() const
{
	return grounded;
}

bool Actor::IsHeadBonked() const
{
	return headBonked;
}

int Actor::GetFacing() const
{
	assert(facing == 1 || facing == -1);
	return facing;
}

void Actor::RaycastRight()
{
	LevelMap* pMap = GameManagerAttorney::PlayerAccess::GetMap();

	const int RAY_COUNT = 2;
	std::array<sf::Vector2f, RAY_COUNT> startPos;
	std::array<sf::Vector2f, RAY_COUNT> endPos;

	// cast a ray from the top (index=0) and the bottom (index=1) of the sprite
	startPos[0] = pos + sf::Vector2f(width, 0.f);
	startPos[1] = pos + sf::Vector2f(width, height - 0.001f); // subtract a little just in case we reach into the next tile (this only happens when pos.y is a whole number)

	float minX = MAX_LEVEL_SIZE * TILE_SIZE_F;

	for (int i = 0; i < RAY_COUNT; i++)
	{
		sf::Vector2f currPos = startPos[i];

		// Edge case: the player is partially inside a tile that's solid on the left
		LevelTile* pTile = pMap->GetTileAtPos(currPos); // The tile in which the raycast begins

		if (pTile != nullptr && // Is this tile empty
			pTile->IsSolidOnSides() && // Is this tile solid on the sides
			pos.x + width > pTile->GetPos().x) // Is the right edge of the player to the right of the left edge of this tile
		{
			// Visuals for debugging ONLY
			if (DEBUG_PLAYER_MAP_COLLISION)
			{
				Visualizer::VisualizePoint(currPos, sf::Color::Green);
			}

			currPos.x += width;
		}

		// While the current position is empty or NOT solid on the sides, and within the bounds of the map
		while ((pMap->GetTileAtPos(currPos) == nullptr || pMap->GetTileAtPos(currPos)->IsSolidOnSides() == false) &&
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

	sf::Vector2f mayMoveTo = pos + posDelta + sf::Vector2f(width, 0.f); // The position the player wants to move to

	if (mayMoveTo.x < minX)
	{
		minX = mayMoveTo.x;
	}
	pos.x = minX - width;
}

void Actor::RaycastLeft()
{
	LevelMap* pMap = GameManagerAttorney::PlayerAccess::GetMap();

	const int RAY_COUNT = 2;
	std::array<sf::Vector2f, RAY_COUNT> startPos;
	std::array<sf::Vector2f, RAY_COUNT> endPos;

	// cast a ray from the top (index=0) and the bottom (index=1) of the sprite
	startPos[0] = pos;
	startPos[1] = pos + sf::Vector2f(0.f, height - 0.001f); // subtract a little just in case we reach into the next tile (this only happens when pos.y is a whole number)

	float maxX = 0;

	for (int i = 0; i < RAY_COUNT; i++)
	{
		sf::Vector2f currPos = startPos[i];

		while ((pMap->GetTileAtPos(currPos) == nullptr || pMap->GetTileAtPos(currPos)->IsSolidOnSides() == false) &&
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

void Actor::RaycastUp()
{
	LevelMap* pMap = GameManagerAttorney::PlayerAccess::GetMap();

	const int RAY_COUNT = 2;
	std::array<sf::Vector2f, RAY_COUNT> startPos;
	std::array<sf::Vector2f, RAY_COUNT> endPos;

	// Cast a ray from the left (index=0) and right (index=1) of the sprite
	startPos[0] = pos;
	startPos[1] = pos + sf::Vector2f(width - 0.001f, 0.f); // subtract a little just in case we reach into the next tile (this only happens when pos.x is a whole number)

	// The highest point the player can move to without being inside of a wall
	float maxY = 0;

	for (int i = 0; i < RAY_COUNT; i++) {
		sf::Vector2f currPos = startPos[i];

		// While the current position is empty or NOT solid underneath, and within the bounds of the map
		while ((pMap->GetTileAtPos(currPos) == nullptr || !pMap->GetTileAtPos(currPos)->IsSolidOnBottom()) && currPos.y >= 0.0f) {
			// Visuals for debugging ONLY
			if (DEBUG_PLAYER_MAP_COLLISION) {
				Visualizer::VisualizePoint(currPos, sf::Color::Green);
			}

			// For iterations through the while loop after the first
			if (currPos != startPos[i]) {
				// We only need to check every tile space, so decrement by tile size
				currPos.y -= TILE_SIZE_F;
			}
			else {
				// First iteration through the while loop; we may be in the middle of a tile, so decrement to the edge of the nearest tile space
				
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

	headBonked = pos.y == maxY;

	pos.y = maxY;
}

void Actor::RaycastDown()
{
	LevelMap* pMap = GameManagerAttorney::PlayerAccess::GetMap();

	const int RAY_COUNT = 2;
	std::array<sf::Vector2f, RAY_COUNT> startPos;
	std::array<sf::Vector2f, RAY_COUNT> endPos;

	// Cast a ray downwards from the left (index=0) and right (index=1) edges of the sprite; we add tile size to the y-value to begin our raycast at the bottom of the player's sprite
	startPos[0] = pos + sf::Vector2f(0.f, height);
	startPos[1] = pos + sf::Vector2f(width - 0.001f, height); // subtract a little just in case we reach into the next tile (this only happens when pos.x is a whole number)

	// The lowest point the player can move to without being inside of a wall
	float minY = MAX_LEVEL_SIZE * TILE_SIZE_F;

	for (int i = 0; i < RAY_COUNT; i++)
	{
		sf::Vector2f currPos = startPos[i];

		// Edge case: the player is partially inside a tile that's solid on top
		LevelTile* pTile = pMap->GetTileAtPos(currPos); // The tile in which the raycast begins

		if (pTile != nullptr && // Is this tile empty
			pTile->IsSolidOnTop() && // Is this tile solid on top
			pos.y + height > pTile->GetPos().y) // Is the bottom edge of the player below the top edge of this tile
		{
			// Visuals for debugging ONLY
			if (DEBUG_PLAYER_MAP_COLLISION)
			{
				Visualizer::VisualizePoint(currPos, sf::Color::Green);
			}

			currPos.y += height;
		}

		// While the current position is empty or NOT solid on top, and within the bounds of the map
		while ((pMap->GetTileAtPos(currPos) == nullptr || pMap->GetTileAtPos(currPos)->IsSolidOnTop() == false) &&
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
			else 
			{
				// First iteration through the while loop; we may be in the middle of a tile, so increment to the top edge of the next tile below
				
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

	sf::Vector2f mayMoveTo = pos + posDelta + sf::Vector2f(0.f, height); // The position the player wants to move to

	// If the player's projected movement is in an invalid location, then move them the maximum distance allowed
	if (mayMoveTo.y < minY)
	{
		minY = mayMoveTo.y;
	}

	// Determine if we is grounded or not
	minY -= height;
	grounded = pos.y == minY;

	pos.y = minY;
}

void Actor::FaceSprite()
{
	if (facing == 1)
	{
		pSprite->SetOrigin(sf::Vector2f(0.f, 0.f));
	}
	else if (facing == -1)
	{
		pSprite->SetOrigin(sf::Vector2f(width, 0.f));
	}
	else
	{
		assert(false);
	}
	pSprite->SetScale(sf::Vector2f(static_cast<float>(facing), 1.f));
}

sf::Vector2f Actor::GetConnector(const std::string& name)
{
	return pSprite->GetConnector(name);
}

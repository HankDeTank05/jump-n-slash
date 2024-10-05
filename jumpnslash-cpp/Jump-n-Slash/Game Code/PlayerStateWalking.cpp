#include "PlayerStateWalking.h"

#include <array>

#include "../Engine Code/Visualizer.h"

#include "PlayerAttorney.h"
#include "Constants.h"
#include "LevelMap.h"
#include "LevelTile.h"

PlayerStateWalking::PlayerStateWalking()
{
	// do nothing
}

PlayerStateWalking::PlayerStateWalking(const PlayerStateWalking& psw)
{
	// do nothing
}

PlayerStateWalking& PlayerStateWalking::operator=(const PlayerStateWalking& psw)
{
	return *this;
}

PlayerStateWalking::~PlayerStateWalking()
{
	// do nothing
}

void PlayerStateWalking::Enter(Player* pPlayer) const
{
	// code goes here
}

void PlayerStateWalking::Update(Player* pPlayer, float deltaTime) const
{
	LevelMap* pLevel = PlayerAttorney::State::GetLevel(pPlayer);

	const int RAY_COUNT = 2;
	std::array<sf::Vector2f, RAY_COUNT> startPos;
	std::array<sf::Vector2f, RAY_COUNT> endPos;

	if (PlayerAttorney::State::GetPosDelta(pPlayer).x > 0) // check for map collision moving right
	{
		// cast a ray from the top (index=0) and the bottom (index=1) of the sprite
		startPos[0] = PlayerAttorney::State::GetPos(pPlayer) + sf::Vector2f(TILE_SIZE_F, 0.f);
		startPos[1] = PlayerAttorney::State::GetPos(pPlayer) + sf::Vector2f(TILE_SIZE_F, TILE_SIZE_F);

		float minX = MAX_LEVEL_SIZE * TILE_SIZE_F;

		for (int i = 0; i < RAY_COUNT; i++)
		{
			sf::Vector2f currPos = startPos[i];

			while ((pLevel->GetTileAtPos(currPos) == nullptr || pLevel->GetTileAtPos(currPos)->IsSolidOnSides() == false) &&
				currPos.x < MAX_LEVEL_SIZE * TILE_SIZE_F)
			{
				Visualizer::VisualizePoint(currPos, sf::Color::Green);
				if (currPos != startPos[i])
				{
					// increment by tile size, since we only want to check every tile space
					currPos.x += TILE_SIZE_F;
				}
				else // we may be in the middle of a tile space, so we want to increment to the edge of the next tile space
				{
					// if we divide by tile size, and cast to an int (remove the fractional part), we get the x-index 
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
			Visualizer::VisualizeSegment(startPos[i], endPos[i]);
			Visualizer::VisualizePoint(endPos[i], sf::Color::Red);
		}

		// compare minx with pos.x + posDelta.x
		// set pos.x to minx
	}
	else if (PlayerAttorney::State::GetPosDelta(pPlayer).x < 0) // check for map collision moving left
	{
		// cast a ray from the top (index=0) and the bottom (index=1) of the sprite
		startPos[0] = PlayerAttorney::State::GetPos(pPlayer);
		startPos[1] = PlayerAttorney::State::GetPos(pPlayer) + sf::Vector2f(0.f, TILE_SIZE_F);

		for (int i = 0; i < RAY_COUNT; i++)
		{
			sf::Vector2f currPos = startPos[i];

			while ((pLevel->GetTileAtPos(currPos) == nullptr || pLevel->GetTileAtPos(currPos)->IsSolidOnSides() == false) &&
				currPos.x >= 0.f)
			{
				Visualizer::VisualizePoint(currPos, sf::Color::Green);
				if (currPos != startPos[i])
				{
					// decrement by tile size, since we only want to check every tile space
					currPos.x -= TILE_SIZE_F;
				}
				else // we may be in the middle of a tile space, so we want to decrement to the edge of the next tile space
				{
					// if we divide by tile size, and cast to an int (remove the fractional part), we get the x-index 
					int tileIndex = static_cast<int>(currPos.x / TILE_SIZE_F);

					// re-multiply by tile size to get the edge of the next tile space
					currPos.x = static_cast<float>(tileIndex) * TILE_SIZE_F;

					currPos.x -= 0.001f;
				}
			}

			endPos[i] = currPos;
			Visualizer::VisualizeSegment(startPos[i], endPos[i]);
			Visualizer::VisualizePoint(endPos[i], sf::Color::Red);
		}
	}
}

const PlayerMoveState* PlayerStateWalking::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	// logic goes here

	return pNextState;
}

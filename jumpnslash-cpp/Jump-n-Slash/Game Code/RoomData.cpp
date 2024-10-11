#include "RoomData.h"

RoomData::RoomData(sf::Vector2f _origin, sf::Vector2f _size, bool _isStartRoom, bool _hasPlayerSpawn, sf::Vector2f* _pPlayerSpawn,
	std::list<sf::Vector2f> _enemyLeftSpawns, std::list<sf::Vector2f> _enemyRightSpawns,
	float _scrollBoundsLeftX, float _scrollBoundsRightX, float _scrollBoundsTopY, float _scrollBoundsBottomY)
	: origin(_origin),
	size(_size),
	isStartRoom(_isStartRoom),
	hasPlayerSpawn(_hasPlayerSpawn),
	pPlayerSpawn(_pPlayerSpawn),
	enemyLeftSpawns(_enemyLeftSpawns),
	enemyRightSpawns(_enemyRightSpawns),
	scrollBoundsLeftX(_scrollBoundsLeftX),
	scrollBoundsRightX(_scrollBoundsRightX),
	scrollBoundsTopY(_scrollBoundsTopY),
	scrollBoundsBottomY(_scrollBoundsBottomY)
{
	if (hasPlayerSpawn)
	{
		assert(pPlayerSpawn != nullptr);
	}
	else
	{
		assert(pPlayerSpawn == nullptr);
	}
}

RoomData::~RoomData()
{
	delete pPlayerSpawn;
}

float RoomData::GetScrollBoundsLeftX()
{
	return scrollBoundsLeftX;
}

float RoomData::GetScrollBoundsRightX()
{
	return scrollBoundsRightX;
}

float RoomData::GetScrollBoundsTopY()
{
	return scrollBoundsTopY;
}

float RoomData::GetScrollBoundsBottomY()
{
	return scrollBoundsBottomY;
}

sf::Vector2f RoomData::GetScrollMinBounds()
{
	return sf::Vector2f(scrollBoundsLeftX, scrollBoundsTopY);
}

sf::Vector2f RoomData::GetScrollMaxBounds()
{
	return sf::Vector2f(scrollBoundsRightX, scrollBoundsBottomY);
}

sf::Vector2f RoomData::GetOrigin()
{
	return origin;
}

sf::Vector2f RoomData::GetSize()
{
	return size;
}

bool RoomData::IsStartRoom()
{
	return isStartRoom;
}

bool RoomData::HasPlayerSpawn()
{
	return hasPlayerSpawn;
}

sf::Vector2f* RoomData::GetPlayerSpawnPoint()
{
	return pPlayerSpawn;
}

std::list<sf::Vector2f> RoomData::GetEnemyLeftSpawns()
{
	return enemyLeftSpawns;
}

std::list<sf::Vector2f> RoomData::GetEnemyRightSpawns()
{
	return enemyRightSpawns;
}

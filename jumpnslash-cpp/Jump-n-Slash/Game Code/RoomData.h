#ifndef ROOM_DATA_H
#define ROOM_DATA_H

#include <list>

#include <SFML/System/Vector2.hpp>

class RoomData
{
public:
	RoomData() = delete;
	RoomData(sf::Vector2f origin, sf::Vector2f size, bool isStartRoom, bool hasPlayerSpawn, sf::Vector2f* playerSpawn,
		std::list<sf::Vector2f> enemyLeftSpawns, std::list<sf::Vector2f> enemyRightSpawns,
		float scrollBoundsLeftX, float scrollBoundsRightX, float scrollBoundsTopY, float scrollBoundsBottomY);
	RoomData(const RoomData& rd) = delete;
	RoomData& operator=(const RoomData& rd) = delete;
	virtual ~RoomData();

	// accessors

	sf::Vector2f GetOrigin();
	sf::Vector2f GetSize();
	bool IsStartRoom();
	bool HasPlayerSpawn();
	sf::Vector2f* GetPlayerSpawnPoint();
	std::list<sf::Vector2f> GetEnemyLeftSpawns();
	std::list<sf::Vector2f> GetEnemyRightSpawns();
	float GetScrollBoundsLeftX();
	float GetScrollBoundsRightX();
	float GetScrollBoundsTopY();
	float GetScrollBoundsBottomY();
	sf::Vector2f GetScrollMinBounds();
	sf::Vector2f GetScrollMaxBounds();
	sf::Vector2f GetRoomMinBounds();
	sf::Vector2f GetRoomMaxBounds();

private:
	sf::Vector2f origin; // in world space!!
	sf::Vector2f size; // in world space!!
	bool isStartRoom;
	bool hasPlayerSpawn;
	sf::Vector2f* pPlayerSpawn; // if hasPlayerSpawn == false, this is nullptr
	std::list<sf::Vector2f> enemyLeftSpawns;
	std::list<sf::Vector2f> enemyRightSpawns;
	float scrollBoundsLeftX;
	float scrollBoundsRightX;
	float scrollBoundsTopY;
	float scrollBoundsBottomY;
};

#endif
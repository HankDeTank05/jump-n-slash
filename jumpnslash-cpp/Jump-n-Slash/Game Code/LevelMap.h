#ifndef LEVEL_MAP_H
#define LEVEL_MAP_H

#include <array>
#include <list>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Constants.h"

// forward declarations
class LevelTile;

class LevelMap
{
public:
	LevelMap() = delete;
	LevelMap(std::vector<std::vector<std::string>>* grid);
	LevelMap(const LevelMap& lm) = delete;
	LevelMap& operator=(const LevelMap& lm) = delete;
	virtual ~LevelMap();

private:
	struct RoomData
	{
		sf::Vector2f origin; // in world space!!
		sf::Vector2f size; // in world space!!
		bool isStartingRoom;
		bool hasPlayerSpawn;
		sf::Vector2f* playerSpawnPoint; // if hasPlayerSpawn == false, this is nullptr
		std::list<sf::Vector2f> enemyLeftSpawns;
		std::list<sf::Vector2f> enemyRightSpawns;
		float scrollLeftBoundsX;
		float scrollRightBoundsX;
		float scrollTopBoundsY;
		float scrollBottomBoundsY;
	};

public:
	using RoomList = std::list<RoomData*>;
	using RoomListRef = RoomList::iterator;

	sf::Vector2f GetStartingSpawnPoint(); // TODO: docs for LevelMap::GetStartingSpawnPoint
	RoomListRef GetStartingRoomRef(); // TODO: docs for LevelMap::GetStartingRoomRef
	RoomListRef GetRoomAtPos(sf::Vector2f worldPos); // TODO: docs for LevelMap::GetRoomAtPos

	/*!
	* \brief	Get the tile at a given world-space position.
	* 
	* Returns a pointer to the \c LevelTile at the given world-space position. If there is no tile at the given position, \c nullptr will
	* be returned.
	* 
	* \param[in]	worldPos	The world-space position at which you would like to check for a tile.
	* 
	* \return	A \c LevelTile pointer. Will be \c nullptr if no tile exists at the given coordinates.
	* 
	* \note If you pass invalid coordinates to this function, it will crash the game. Valid coordinates are in the following range:
	* - \c 0.0f \c <= \c x \c < \c MAX_LEVEL_SIZE \c * \c TILE_SIZE_F
	* - \c 0.0f \c <= \c y \c < \c MAX_LEVEL_SIZE \c * \c TILE_SIZE_F
	* \c MAX_LEVEL_SIZE and \c TILE_SIZE_F are defined in the Constants.h file.
	* 
	* \see LevelTile
	*/
	LevelTile* GetTileAtPos(sf::Vector2f worldPos); // TODO: docs for LevelMap::GetTileAtPos needs example code

	void DebugLevelScrollBounds(RoomListRef roomListRef);

private:
	std::array<std::array<LevelTile*, MAX_LEVEL_SIZE>, MAX_LEVEL_SIZE> map;
	sf::Vector2i usedSize;
	RoomList rooms;
};

#endif
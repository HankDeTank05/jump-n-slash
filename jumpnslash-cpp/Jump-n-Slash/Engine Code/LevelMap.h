#ifndef LEVEL_MAP_H
#define LEVEL_MAP_H

#include <vector>

// forward declarations
class MapTile;

class LevelMap
{
public:
	LevelMap() = delete;
	LevelMap(std::string filename);
	LevelMap(const LevelMap& lm) = delete;
	LevelMap& operator=(const LevelMap& lm) = delete;
	virtual ~LevelMap();

private:
	std::vector<std::vector<MapTile*>> grid;
};

#endif
#ifndef MAP_H
#define MAP_H

#include <array>

class Map
{
public:
	Map();
	Map(const Map& m) = delete;
	Map& operator=(const Map& m) = delete;
	virtual ~Map();

	using Grid = std::array<std::array<int, 256>, 256>;

private:
	Grid grid;
};

#endif
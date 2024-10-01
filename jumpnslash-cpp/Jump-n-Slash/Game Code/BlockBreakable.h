#ifndef BLOCK_BREAKABLE_H
#define BLOCK_BREAKABLE_H

#include "LevelTile.h"

class BlockBreakable : public LevelTile
{
public:
	BlockBreakable(sf::Vector2f pos);
	BlockBreakable(const BlockBreakable& bb) = delete;
	BlockBreakable& operator=(const BlockBreakable& bb) = delete;
	virtual ~BlockBreakable();

	void Break();
};

#endif
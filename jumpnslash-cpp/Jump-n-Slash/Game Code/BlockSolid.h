#ifndef BLOCK_SOLID_H
#define BLOCK_SOLID_H

#include "LevelTile.h"

class BlockSolid : public LevelTile
{
public:
	BlockSolid() = delete;
	BlockSolid(sf::Vector2f pos);
	BlockSolid(const BlockSolid& bs) = delete;
	BlockSolid& operator=(const BlockSolid& bs) = delete;
	virtual ~BlockSolid();
};

#endif
#ifndef BLOCK_HAZARD_H
#define BLOCK_HAZARD_H

#include "LevelTile.h"

class BlockHazard : public LevelTile
{
public:
	BlockHazard() = delete;
	BlockHazard(sf::Vector2f pos);
	BlockHazard(const BlockHazard& bh) = delete;
	BlockHazard& operator=(const BlockHazard& bh) = delete;
	virtual ~BlockHazard();
};

#endif
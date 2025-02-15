#ifndef BLOCK_SOLID_H
#define BLOCK_SOLID_H

// game includes
#include "MapTile.h"

class BlockSolid : public MapTile
{
public:
	BlockSolid();
	BlockSolid(const BlockSolid& bs) = delete;
	BlockSolid& operator=(const BlockSolid& bs) = delete;
	virtual ~BlockSolid() = default;
};

#endif
#ifndef BLOCK_HAZARD_H
#define BLOCK_HAZARD_H

class BlockHazard
{
public:
	BlockHazard();
	BlockHazard(const BlockHazard& bh) = delete;
	BlockHazard& operator=(const BlockHazard& bh) = delete;
	virtual ~BlockHazard() = default;
};

#endif
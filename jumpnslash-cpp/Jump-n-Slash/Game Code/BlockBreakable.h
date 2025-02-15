#ifndef BLOCK_BREAKABLE_H
#define BLOCK_BREAKABLE_H

class BlockBreakable
{
public:
	BlockBreakable();
	BlockBreakable(const BlockBreakable& bb) = delete;
	BlockBreakable& operator=(const BlockBreakable& bb) = delete;
	virtual ~BlockBreakable() = default;
};

#endif
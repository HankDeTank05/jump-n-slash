#ifndef VIZ_CMD_SEG_POOL_H
#define VIZ_CMD_SEG_POOL_H

#include <stack>

// forward declarations
class VisualizerCommandSegment;

class VizCmdSegPool
{
public:
	VizCmdSegPool();
	VizCmdSegPool(const VizCmdSegPool& vcsp) = delete;
	VizCmdSegPool& operator=(const VizCmdSegPool& vcsp) = delete;
	virtual ~VizCmdSegPool();

	using SegCmdPool = std::stack<VisualizerCommandSegment*>;

	VisualizerCommandSegment* GetCommand();
	void RecycleCommand(VisualizerCommandSegment* pCmd);

private:
	SegCmdPool pool;
};

#endif
#ifndef VIZ_CMD_POINT_POOL_H
#define VIZ_CMD_POINT_POOL_H

#include <stack>

// forward declarations
class VisualizerCommandPoint;

class VizCmdPointPool
{
public:
	VizCmdPointPool();
	VizCmdPointPool(const VizCmdPointPool& vcpp) = delete;
	VizCmdPointPool& operator=(const VizCmdPointPool& vcpp) = delete;
	virtual ~VizCmdPointPool();

	using PointCmdPool = std::stack<VisualizerCommandPoint*>;

	VisualizerCommandPoint* GetCommand();
	void RecycleCommand(VisualizerCommandPoint* pCmd);

private:
	PointCmdPool pool;
};

#endif
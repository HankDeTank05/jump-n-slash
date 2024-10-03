#ifndef VIZ_CMD_CIRCLE_POOL_H
#define VIZ_CMD_CIRCLE_POOL_H

#include <stack>

// forward declarations
class VisualizerCommandCircle;

class VizCmdCirclePool
{
public:
	VizCmdCirclePool();
	VizCmdCirclePool(const VizCmdCirclePool& vccp) = delete;
	VizCmdCirclePool& operator=(const VizCmdCirclePool& vccp) = delete;
	virtual ~VizCmdCirclePool();

	using CircleCmdPool = std::stack<VisualizerCommandCircle*>;

	VisualizerCommandCircle* GetCommand();
	void RecycleCommand(VisualizerCommandCircle* pCmd);

private:
	CircleCmdPool pool;
};

#endif
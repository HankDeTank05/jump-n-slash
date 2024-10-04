#ifndef VIZ_CMD_RECT_POOL_H
#define VIZ_CMD_RECT_POOL_H

#include <stack>

// forward declarations
class VisualizerCommandRect;

class VizCmdRectPool
{
public:
	VizCmdRectPool();
	VizCmdRectPool(const VizCmdRectPool& vcrp) = delete;
	VizCmdRectPool& operator=(const VizCmdRectPool& vcrp) = delete;
	virtual ~VizCmdRectPool();

	using RectCmdPool = std::stack<VisualizerCommandRect*>;

	VisualizerCommandRect* GetCommand();
	void RecycleCommand(VisualizerCommandRect* pCmd);

private:
	RectCmdPool pool;
};

#endif
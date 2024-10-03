#include "VizCmdCirclePool.h"

#include "VisualizerCommandCircle.h"

VizCmdCirclePool::VizCmdCirclePool()
	: pool()
{
	// do nothing
}

VizCmdCirclePool::~VizCmdCirclePool()
{
	while (pool.empty() == false)
	{
		delete pool.top();
		pool.pop();
	}
}

VisualizerCommandCircle* VizCmdCirclePool::GetCommand()
{
	VisualizerCommandCircle* pVizCmdCircle;
	if (pool.empty() == false)
	{
		pVizCmdCircle = pool.top();
		pool.pop();
	}
	else
	{
		pVizCmdCircle = new VisualizerCommandCircle();
	}
	return pVizCmdCircle;
}

void VizCmdCirclePool::RecycleCommand(VisualizerCommandCircle* pCmd)
{
	pool.push(pCmd);
}

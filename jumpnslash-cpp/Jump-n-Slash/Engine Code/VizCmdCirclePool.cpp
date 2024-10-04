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
	VisualizerCommandCircle* pCmd;
	if (pool.empty() == false)
	{
		pCmd = pool.top();
		pool.pop();
	}
	else
	{
		pCmd = new VisualizerCommandCircle();
	}
	return pCmd;
}

void VizCmdCirclePool::RecycleCommand(VisualizerCommandCircle* pCmd)
{
	pool.push(pCmd);
}

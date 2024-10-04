#include "VizCmdRectPool.h"

#include "VisualizerCommandRect.h"

VizCmdRectPool::VizCmdRectPool()
	: pool()
{
	// do nothing
}

VizCmdRectPool::~VizCmdRectPool()
{
	while (pool.empty() == false)
	{
		delete pool.top();
		pool.pop();
	}
}

VisualizerCommandRect* VizCmdRectPool::GetCommand()
{
	VisualizerCommandRect* pCmd;
	if (pool.empty() == false)
	{
		pCmd = pool.top();
		pool.pop();
	}
	else
	{
		pCmd = new VisualizerCommandRect();
	}
	return pCmd;
}

void VizCmdRectPool::RecycleCommand(VisualizerCommandRect* pCmd)
{
	pool.push(pCmd);
}

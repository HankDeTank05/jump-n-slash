#include "VizCmdSegPool.h"

#include "VisualizerCommandSegment.h"

VizCmdSegPool::VizCmdSegPool()
	: pool()
{
	// do nothing
}

VizCmdSegPool::~VizCmdSegPool()
{
	while (pool.empty() == false)
	{
		delete pool.top();
		pool.pop();
	}
}

VisualizerCommandSegment* VizCmdSegPool::GetCommand()
{
	VisualizerCommandSegment* pCmd;
	if (pool.empty() == false)
	{
		pCmd = pool.top();
		pool.pop();
	}
	else
	{
		pCmd = new VisualizerCommandSegment();
	}
	return pCmd;
}

void VizCmdSegPool::RecycleCommand(VisualizerCommandSegment* pCmd)
{
	pool.push(pCmd);
}

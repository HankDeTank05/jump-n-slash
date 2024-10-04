#include "VizCmdPointPool.h"

#include "VisualizerCommandPoint.h"

VizCmdPointPool::VizCmdPointPool()
	: pool()
{
	// do nothing
}

VizCmdPointPool::~VizCmdPointPool()
{
	while (pool.empty() == false)
	{
		delete pool.top();
		pool.pop();
	}
}

VisualizerCommandPoint* VizCmdPointPool::GetCommand()
{
	VisualizerCommandPoint* pCmd;
	if (pool.empty() == false)
	{
		pCmd = pool.top();
		pool.pop();
	}
	else
	{
		pCmd = new VisualizerCommandPoint();
	}
	return pCmd;
}

void VizCmdPointPool::RecycleCommand(VisualizerCommandPoint* pCmd)
{
	pool.push(pCmd);
}

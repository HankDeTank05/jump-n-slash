#include "VizCmdTextPool.h"

#include "VisualizerCommandText.h"

VizCmdTextPool::VizCmdTextPool()
	: pool()
{
	// do nothing
}

VizCmdTextPool::~VizCmdTextPool()
{
	while (pool.empty() == false)
	{
		delete pool.top();
		pool.pop();
	}
}

VisualizerCommandText* VizCmdTextPool::GetCommand()
{
	VisualizerCommandText* pCmd;
	if (pool.empty() == false)
	{
		pCmd = pool.top();
		pool.pop();
	}
	else
	{
		pCmd = new VisualizerCommandText();
	}
	return pCmd;
}

void VizCmdTextPool::RecycleCommand(VisualizerCommandText* pCmd)
{
	pool.push(pCmd);
}

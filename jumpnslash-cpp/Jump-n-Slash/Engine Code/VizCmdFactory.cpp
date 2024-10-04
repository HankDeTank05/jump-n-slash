#include "VizCmdFactory.h"

#include "VizCmdPointPool.h"
#include "VizCmdCirclePool.h"
#include "VizCmdRectPool.h"
#include "VizCmdSegPool.h"
#include "VisualizerCommandPoint.h"
#include "VisualizerCommandCircle.h"
#include "VisualizerCommandRect.h"
#include "VisualizerCommandSegment.h"

VizCmdFactory* VizCmdFactory::pInstance = nullptr;

VizCmdFactory::VizCmdFactory()
	: pPointPool(new VizCmdPointPool()),
	pCirclePool(new VizCmdCirclePool()),
	pRectPool(new VizCmdRectPool()),
	pSegPool(new VizCmdSegPool())
{
	// do nothing
}

VizCmdFactory::~VizCmdFactory()
{
	delete pSegPool;
	delete pRectPool;
	delete pCirclePool;
	delete pPointPool;
}

VizCmdFactory& VizCmdFactory::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new VizCmdFactory();
	}
	return *pInstance;
}

VisualizerCommandPoint* VizCmdFactory::GetPointCommand(sf::Vector2f pos, sf::Color color)
{
	return Instance().privGetPointCommand(pos, color);
}

VisualizerCommandCircle* VizCmdFactory::GetCircleCommand(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	return Instance().privGetCircleCommand(pos, radius, color, showCenter);
}

VisualizerCommandRect* VizCmdFactory::GetRectCommand(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	return Instance().privGetRectCommand(pos, size, color);
}

VisualizerCommandSegment* VizCmdFactory::GetSegmentCommand(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color)
{
	return Instance().privGetSegmentCommand(pos0, pos1, color);
}

void VizCmdFactory::RecyclePointCommand(VisualizerCommandPoint* pCmd)
{
	Instance().privRecyclePointCommand(pCmd);
}

void VizCmdFactory::RecycleCircleCommand(VisualizerCommandCircle* pCmd)
{
	Instance().privRecycleCircleCommand(pCmd);
}

void VizCmdFactory::RecycleRectCommand(VisualizerCommandRect* pCmd)
{
	Instance().privRecycleRectCommand(pCmd);
}

void VizCmdFactory::RecycleSegmentCommand(VisualizerCommandSegment* pCmd)
{
	Instance().privRecycleSegmentCommand(pCmd);
}

void VizCmdFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

VisualizerCommandPoint* VizCmdFactory::privGetPointCommand(sf::Vector2f pos, sf::Color color)
{
	VisualizerCommandPoint* pCmd = pPointPool->GetCommand();

	pCmd->Init(pos, color);

	return pCmd;
}

VisualizerCommandCircle* VizCmdFactory::privGetCircleCommand(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	VisualizerCommandCircle* pCmd = pCirclePool->GetCommand();

	pCmd->Init(pos, radius, color, showCenter);

	return pCmd;
}

VisualizerCommandRect* VizCmdFactory::privGetRectCommand(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	VisualizerCommandRect* pCmd = pRectPool->GetCommand();

	pCmd->Init(pos, size, color);

	return pCmd;
}

VisualizerCommandSegment* VizCmdFactory::privGetSegmentCommand(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color)
{
	VisualizerCommandSegment* pCmd = pSegPool->GetCommand();

	pCmd->Init(pos0, pos1, color);

	return pCmd;
}

void VizCmdFactory::privRecyclePointCommand(VisualizerCommandPoint* pCmd)
{
	pPointPool->RecycleCommand(pCmd);
}

void VizCmdFactory::privRecycleCircleCommand(VisualizerCommandCircle* pCmd)
{
	pCirclePool->RecycleCommand(pCmd);
}

void VizCmdFactory::privRecycleRectCommand(VisualizerCommandRect* pCmd)
{
	pRectPool->RecycleCommand(pCmd);
}

void VizCmdFactory::privRecycleSegmentCommand(VisualizerCommandSegment* pCmd)
{
	pSegPool->RecycleCommand(pCmd);
}

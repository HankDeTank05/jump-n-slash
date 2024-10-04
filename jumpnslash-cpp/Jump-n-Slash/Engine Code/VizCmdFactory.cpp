#include "VizCmdFactory.h"

#include "VizCmdPointPool.h"
#include "VizCmdCirclePool.h"
#include "VizCmdRectPool.h"
#include "VisualizerCommandPoint.h"
#include "VisualizerCommandCircle.h"
#include "VisualizerCommandRect.h"

VizCmdFactory* VizCmdFactory::pInstance = nullptr;

VizCmdFactory::VizCmdFactory()
	: pPointPool(new VizCmdPointPool()),
	pCirclePool(new VizCmdCirclePool()),
	pRectPool(new VizCmdRectPool())
{
	// do nothing
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

#include "VizCmdFactory.h"

#include "VizCmdCirclePool.h"
#include "VisualizerCommandCircle.h"

VizCmdFactory* VizCmdFactory::pInstance = nullptr;

VizCmdFactory::VizCmdFactory()
	: pCirclePool(new VizCmdCirclePool())
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

VisualizerCommandCircle* VizCmdFactory::GetCircleCommand(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	return Instance().privGetCircleCommand(pos, radius, color, showCenter);
}

VisualizerCommandRect* VizCmdFactory::GetRectCommand(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	return Instance().privGetRectCommand(pos, size, color);
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

VisualizerCommandCircle* VizCmdFactory::privGetCircleCommand(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	VisualizerCommandCircle* pCmd = pCirclePool->GetCommand();

	pCmd->Init(pos, radius, color, showCenter);

	return pCmd;
}

VisualizerCommandRect* VizCmdFactory::privGetRectCommand(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	assert(false); // TODO: empty function VizCmdFactory:privGetRectCommand
	return nullptr;
}

void VizCmdFactory::privRecycleCircleCommand(VisualizerCommandCircle* pCmd)
{
	pCirclePool->RecycleCommand(pCmd);
}

void VizCmdFactory::privRecycleRectCommand(VisualizerCommandRect* pCmd)
{
	assert(false); // TODO: empty function VizCmdFactory::privRecycleRectCommand
}

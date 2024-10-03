#ifndef VIZ_CMD_FACTORY_H
#define VIZ_CMD_FACTORY_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

// forward declarations
class VisualizerCommandCircle;
class VisualizerCommandRect;
class VizCmdCirclePool;

class VizCmdFactory // this class is written as a singleton
{
private:
	static VizCmdFactory* pInstance;

	VizCmdFactory();
	VizCmdFactory(const VizCmdFactory& vcf) = delete;
	VizCmdFactory& operator=(const VizCmdFactory& vcf) = delete;
	virtual ~VizCmdFactory() = default;

	static VizCmdFactory& Instance();

public: // public api functions
	static VisualizerCommandCircle* GetCircleCommand(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	static VisualizerCommandRect* GetRectCommand(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	static void RecycleCircleCommand(VisualizerCommandCircle* pCmd);
	static void RecycleRectCommand(VisualizerCommandRect* pCmd);

private: // engine-only api functions
	friend class VizCmdAttorney;
	static void Terminate();

private: // private api backend functions
	VisualizerCommandCircle* privGetCircleCommand(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	VisualizerCommandRect* privGetRectCommand(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	void privRecycleCircleCommand(VisualizerCommandCircle* pCmd);
	void privRecycleRectCommand(VisualizerCommandRect* pCmd);

private: // member variables
	VizCmdCirclePool* pCirclePool;
};

#endif
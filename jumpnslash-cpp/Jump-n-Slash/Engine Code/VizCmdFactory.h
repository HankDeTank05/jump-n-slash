#ifndef VIZ_CMD_FACTORY_H
#define VIZ_CMD_FACTORY_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

// forward declarations
class VisualizerCommandPoint;
class VisualizerCommandCircle;
class VisualizerCommandRect;
class VisualizerCommandSegment;
class VizCmdPointPool;
class VizCmdCirclePool;
class VizCmdRectPool;
class VizCmdSegPool;

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
	static VisualizerCommandPoint* GetPointCommand(sf::Vector2f pos, sf::Color color);
	static VisualizerCommandCircle* GetCircleCommand(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	static VisualizerCommandRect* GetRectCommand(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	static VisualizerCommandSegment* GetSegmentCommand(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color);
	static void RecyclePointCommand(VisualizerCommandPoint* pCmd);
	static void RecycleCircleCommand(VisualizerCommandCircle* pCmd);
	static void RecycleRectCommand(VisualizerCommandRect* pCmd);

private: // engine-only api functions
	friend class VizCmdAttorney;
	static void Terminate();

private: // private api backend functions
	VisualizerCommandPoint* privGetPointCommand(sf::Vector2f pos, sf::Color color);
	VisualizerCommandCircle* privGetCircleCommand(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	VisualizerCommandRect* privGetRectCommand(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	void privRecyclePointCommand(VisualizerCommandPoint* pCmd);
	void privRecycleCircleCommand(VisualizerCommandCircle* pCmd);
	void privRecycleRectCommand(VisualizerCommandRect* pCmd);

private: // member variables
	VizCmdPointPool* pPointPool;
	VizCmdCirclePool* pCirclePool;
	VizCmdRectPool* pRectPool;
};

#endif
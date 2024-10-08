#ifndef VIZ_CMD_FACTORY_H
#define VIZ_CMD_FACTORY_H

#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Color.hpp>

// forward declarations
class VisualizerCommandPoint;
class VisualizerCommandCircle;
class VisualizerCommandRect;
class VisualizerCommandSegment;
class VisualizerCommandText;
class VizCmdPointPool;
class VizCmdCirclePool;
class VizCmdRectPool;
class VizCmdSegPool;
class VizCmdTextPool;

class VizCmdFactory // this class is written as a singleton
{
private:
	static VizCmdFactory* pInstance;

	VizCmdFactory();
	VizCmdFactory(const VizCmdFactory& vcf) = delete;
	VizCmdFactory& operator=(const VizCmdFactory& vcf) = delete;
	virtual ~VizCmdFactory();

	static VizCmdFactory& Instance();

public: // public api functions
	static VisualizerCommandPoint* GetPointCommand(sf::Vector2f pos, sf::Color color);
	static VisualizerCommandCircle* GetCircleCommand(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	static VisualizerCommandRect* GetRectCommand(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	static VisualizerCommandSegment* GetSegmentCommand(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color);
	static VisualizerCommandText* GetTextCommand(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix);
	static void RecyclePointCommand(VisualizerCommandPoint* pCmd);
	static void RecycleCircleCommand(VisualizerCommandCircle* pCmd);
	static void RecycleRectCommand(VisualizerCommandRect* pCmd);
	static void RecycleSegmentCommand(VisualizerCommandSegment* pCmd);
	static void RecycleTextCommand(VisualizerCommandText* pCmd);

private: // engine-only api functions
	friend class VizCmdFactoryAttorney;
	static void Terminate();

private: // private api backend functions
	VisualizerCommandPoint* privGetPointCommand(sf::Vector2f pos, sf::Color color);
	VisualizerCommandCircle* privGetCircleCommand(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	VisualizerCommandRect* privGetRectCommand(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	VisualizerCommandSegment* privGetSegmentCommand(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color);
	VisualizerCommandText* privGetTextCommand(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix);
	void privRecyclePointCommand(VisualizerCommandPoint* pCmd);
	void privRecycleCircleCommand(VisualizerCommandCircle* pCmd);
	void privRecycleRectCommand(VisualizerCommandRect* pCmd);
	void privRecycleSegmentCommand(VisualizerCommandSegment* pCmd);
	void privRecycleTextCommand(VisualizerCommandText* pCmd);

private: // member variables
	VizCmdPointPool* pPointPool;
	VizCmdCirclePool* pCirclePool;
	VizCmdRectPool* pRectPool;
	VizCmdSegPool* pSegPool;
	VizCmdTextPool* pTextPool;
};

#endif
#ifndef VISUALIZER_COMMAND_POINT_H
#define VISUALIZER_COMMAND_POINT_H

#include "SFML/System/Vector2.hpp"

#include "VisualizerCommand.h"

class VisualizerCommandPoint : public VisualizerCommand
{
public:
	VisualizerCommandPoint();
	VisualizerCommandPoint(const VisualizerCommandPoint& vcp) = delete;
	VisualizerCommandPoint& operator=(const VisualizerCommandPoint& vcp) = delete;
	virtual ~VisualizerCommandPoint();

	void Init(sf::Vector2f pos, sf::Color color);

	virtual void Execute() override;
	virtual void Recycle() override;

private:
	sf::Vector2f pos;
};

#endif
#ifndef VISUALIZER_COMMAND_CIRCLE_H
#define VISUALIZER_COMMAND_CIRCLE_H

#include <SFML/System/Vector2.hpp>

#include "VisualizerCommand.h"

class VisualizerCommandCircle : public VisualizerCommand
{
public:
	VisualizerCommandCircle();
	VisualizerCommandCircle(const VisualizerCommandCircle& vcc) = delete;
	VisualizerCommandCircle& operator=(const VisualizerCommandCircle& vcc) = delete;
	virtual ~VisualizerCommandCircle();

	void Init(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);

	virtual void Execute() override;
	virtual void Recycle() override;

private:
	sf::Vector2f pos;
	float radius;
	bool showCenter;
};

#endif
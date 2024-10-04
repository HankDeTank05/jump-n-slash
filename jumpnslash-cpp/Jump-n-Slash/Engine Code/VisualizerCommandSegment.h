#ifndef VISUALIZER_COMMAND_SEGMENT_H
#define VISUALIZER_COMMAND_SEGMENT_H

#include <SFML/System/Vector2.hpp>

#include "VisualizerCommand.h"

class VisualizerCommandSegment : public VisualizerCommand
{
public:
	VisualizerCommandSegment();
	VisualizerCommandSegment(const VisualizerCommandSegment& vcs) = delete;
	VisualizerCommandSegment& operator=(const VisualizerCommandSegment& vcs) = delete;
	virtual ~VisualizerCommandSegment();

	void Init(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color);

	virtual void Execute() override;
	virtual void Recycle() override;

private:
	sf::Vector2f pos0;
	sf::Vector2f pos1;
};

#endif
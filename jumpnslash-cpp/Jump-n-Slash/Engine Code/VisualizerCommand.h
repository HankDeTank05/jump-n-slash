#ifndef VISUALIZER_COMMAND_H
#define VISUALIZER_COMMAND_H

#include <SFML/Graphics.hpp>

#include "Command.h"

class VisualizerCommand : public Command
{
public:
	VisualizerCommand();
	VisualizerCommand(const VisualizerCommand& vc) = delete;
	VisualizerCommand& operator=(const VisualizerCommand& vc) = delete;
	virtual ~VisualizerCommand();

	virtual void Execute() = 0;
	virtual void Recycle() = 0;

protected:
	sf::Color color;
};

#endif
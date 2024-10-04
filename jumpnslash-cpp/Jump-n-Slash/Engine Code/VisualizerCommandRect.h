#ifndef VISUALIZER_COMMAND_RECT_H
#define VISUALIZER_COMMAND_RECT_H

#include <SFML/System/Vector2.hpp>

#include "VisualizerCommand.h"

class VisualizerCommandRect : public VisualizerCommand
{
public:
	VisualizerCommandRect();
	VisualizerCommandRect(const VisualizerCommandRect& vcr) = delete;
	VisualizerCommandRect& operator=(const VisualizerCommandRect& vcr) = delete;
	virtual ~VisualizerCommandRect();

	void Init(sf::Vector2f pos, sf::Vector2f size, sf::Color color);

	virtual void Execute() override;
	virtual void Recycle() override;

private:
	sf::Vector2f pos;
	sf::Vector2f size;
};

#endif
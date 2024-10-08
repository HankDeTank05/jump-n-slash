#ifndef VISUALIZER_COMMAND_TEXT_H
#define VISUALIZER_COMMAND_TEXT_H

#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

#include "VisualizerCommand.h"

class VisualizerCommandText : public VisualizerCommand
{
public:
	VisualizerCommandText() = default;
	VisualizerCommandText(const VisualizerCommandText& vct) = delete;
	VisualizerCommandText& operator=(const VisualizerCommandText& vct) = delete;
	virtual ~VisualizerCommandText() = default;

	void Init(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix);

	virtual void Execute() override;
	virtual void Recycle() override;

private:
	sf::String str;
	sf::Vector2f pos;
	int sizeInPix;
};

#endif
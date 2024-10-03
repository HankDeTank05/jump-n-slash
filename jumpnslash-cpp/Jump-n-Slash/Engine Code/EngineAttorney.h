#ifndef ENGINE_ATTORNEY_H
#define ENGINE_ATTORNEY_H

#include <SFML/Graphics.hpp>

class EngineAttorney
{
public:
	class GameWindow
	{
	private:
		friend class DrawObject;
		friend class MouseCursorListener;
		static sf::RenderWindow& GetWindow();
	};
};

#endif
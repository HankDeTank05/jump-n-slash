#ifndef ENGINE_ATTORNEY_H
#define ENGINE_ATTORNEY_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

class EngineAttorney
{
public:
	class GameWindow
	{
	private:
		friend class DrawObject;
		friend class MouseCursorListener;
		friend class CameraManager;
		friend class Camera;
		friend class Math;
		static sf::RenderWindow& GetWindow();
		static void SetView(sf::View view);
	};
};

#endif
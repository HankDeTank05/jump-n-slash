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
	class QuitGameAccess
	{
	private:
		friend class QuitGameCommand;
		friend class GameManager;
		static void RequestQuitGame();
	};
	class CommandAccess
	{
	private:
		friend class EngineQuitCommand;
		friend class EngineDontQuitCommand;
		static void QuitGame();
	};
};

#endif
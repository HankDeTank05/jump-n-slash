#include "EngineAttorney.h"

#include "JumpSlashEngine.h"

sf::RenderWindow& EngineAttorney::GameWindow::GetWindow()
{
	return JumpSlashEngine::GetWindow();
}

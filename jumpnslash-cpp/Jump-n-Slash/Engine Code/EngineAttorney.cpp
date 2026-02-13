#include "EngineAttorney.h"

#include "JumpSlashEngine.h"

sf::RenderWindow& EngineAttorney::GameWindow::GetWindow()
{
	return JumpSlashEngine::GetWindow();
}

void EngineAttorney::GameWindow::SetView(sf::View view)
{
	JumpSlashEngine::SetView(view);
}

void EngineAttorney::QuitGameAccess::RequestQuitGame()
{
	JumpSlashEngine::RequestQuitGame();
}

void EngineAttorney::CommandAccess::QuitGame()
{
	JumpSlashEngine::QuitGame();
}

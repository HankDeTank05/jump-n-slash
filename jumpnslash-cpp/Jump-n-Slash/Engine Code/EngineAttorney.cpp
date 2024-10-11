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

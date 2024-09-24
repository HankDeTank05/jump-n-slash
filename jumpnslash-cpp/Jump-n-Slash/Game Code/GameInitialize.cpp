#include "../Engine Code/JumpSlashEngine.h"

#include "Constants.h"

void JumpSlashEngine::GameInitialize()
{
	// the body of this function should set the window name and size
	SetWindowName(WINDOW_NAME);
	SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}
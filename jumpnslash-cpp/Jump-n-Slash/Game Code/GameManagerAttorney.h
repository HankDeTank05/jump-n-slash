#ifndef GAME_MANAGER_ATTORNEY_H
#define GAME_MANAGER_ATTORNEY_H

class GameManagerAttorney
{
public:
	class EngineAccess
	{
	private:
		friend class JumpSlashEngine;
		static void Terminate();
	};

	class QuitGameAccess
	{
	private:
		friend class QuitGameCommand;
		static void QuitGame();
	};
};

#endif
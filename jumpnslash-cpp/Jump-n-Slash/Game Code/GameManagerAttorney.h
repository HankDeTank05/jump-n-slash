#ifndef GAME_MANAGER_ATTORNEY_H
#define GAME_MANAGER_ATTORNEY_H

// forward declarations
class Player;
class LevelMap;

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

	class SceneAccess
	{
		friend class Level0;
		static void SetPlayer(Player* pPlayer);
		static void SetLevel(LevelMap* pLevel);
	};

	class PlayerAccess
	{
		friend class Player;
		friend class Actor;
		static LevelMap* GetMap();
	};

	class LevelAccess
	{
		friend class LevelMap;
		static Player* GetPlayer();
	};
};

#endif
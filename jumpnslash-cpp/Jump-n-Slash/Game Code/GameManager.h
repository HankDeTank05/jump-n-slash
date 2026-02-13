#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

// forward declarations
class GameState;
class Player;
class LevelMap;

class GameManager // this class is written as a singleton
{
private:
	static GameManager* pInstance;

	GameManager();
	GameManager(const GameManager& gm) = delete;
	GameManager& operator=(const GameManager& gm) = delete;
	virtual ~GameManager() = default;

	static GameManager& Instance();

public: // API functions
	static void StartGame();
	static void PauseGame();
	static void ResumeFromPause();

private: // selective access API functions
	friend class GameManagerAttorney;
	static void Terminate();

	static void QuitGame();

	static void SetPlayer(Player* pPlayer);
	static void SetLevel(LevelMap* pLevel);
	static Player* GetPlayer();
	static LevelMap* GetMap();

private: // API backend functions
	void privStartGame();
	void privPauseGame();
	void privResumeFromPause();

	void privQuitGame();

	void privSetPlayer(Player* pPlayer);
	void privSetLevel(LevelMap* pLevel);
	Player* privGetPlayer();
	LevelMap* privGetLevel();

private: // member variables
	const GameState* pCurrentState;
	Player* pPlayer;
	LevelMap* pLevel;

};

#endif
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

// forward declarations
class GameState;

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

private: // internal-only API functions
	friend class GameManagerAttorney;
	static void Terminate();

	static void QuitGame();

private: // API backend functions
	void privStartGame();
	void privPauseGame();
	void privResumeFromPause();

	void privQuitGame();

private: // member variables
	const GameState* pCurrentState;

};

#endif
#ifndef JUMP_SLASH_ENGINE_H
#define JUMP_SLASH_ENGINE_H

#include <SFML/Graphics.hpp>

// this class is written as a singleton

class JumpSlashEngine
{
private:

	static JumpSlashEngine* pInstance;

	JumpSlashEngine();
	JumpSlashEngine(const JumpSlashEngine& jse) = delete;
	JumpSlashEngine& operator=(const JumpSlashEngine& jse) = delete;
	~JumpSlashEngine() = default;

	static JumpSlashEngine& Instance();

public: // public api functions
	static void Run();
	static void Terminate();

private: // private functions
	void privRun();

	void Initialize();
	void LoadContent();
	void Update(float deltaTime);
	void Draw();
	void UnloadContent();

	void LoadResources();
	void GameEnd();

private: // member variables
	sf::RenderWindow window;
	sf::Clock clock;
};

#endif
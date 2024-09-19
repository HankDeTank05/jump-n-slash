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
	// TODO: add static function for setting window name
	// TODO: add static function for setting window size
	// TODO: add static function for setting the fullscreen mode
	
	// TODO: should these be public?
	static void Run(); // TODO: docs
	static void Terminate(); // TODO: docs

private: // private functions
	void privRun();

	void Initialize();
	void LoadContent();
	void Update(float deltaTime);
	void Draw();
	void UnloadContent();

	/*!
	* \brief	Initialize the game window.
	* 
	* This function is called by the engine but defined by the user. In it, you can specify things about the window such as title, size, and fullscreen mode.
	* 
	* \return	Does not return anything.
	* 
	* \see	JumpSlashEngine::LoadResources
	* \see	JumpSlashEngine::GameEnd
	*/
	void GameInitialize(); 
	/*!
	* \brief	Load assets into the engine.
	* 
	* This function is called by the engine but defined by the user. In it, you can load assets into the engine by calling the load functions of the asset managers.
	* 
	* \return	Does not return anything.
	* 
	* \see	JumpSlashEngine::GameInitialize
	* \see	JumpSlashengine::GameEnd
	* 
	* \see	TextureManager::LoadTexture
	* TODO: add more "see also" references for asset manager load functions as they're created
	*/
	void LoadResources(); // TODO: LoadResources function body
	/*!
	* \brief	Do things when the game ends.
	* 
	* This function is called by the engine but defined by the user. In it, you can do things when the game ends.
	* 
	* \return	Does not return anything.
	* 
	* \see	JumpSlashEngine::GameInitialize
	* \see	JumpSlashEngine::LoadResources
	* TODO: figure out what the purpose of this function is
	*/
	void GameEnd(); // TODO: GameEnd function body

private: // member variables
	sf::RenderWindow window;
	sf::Clock clock;
};

#endif
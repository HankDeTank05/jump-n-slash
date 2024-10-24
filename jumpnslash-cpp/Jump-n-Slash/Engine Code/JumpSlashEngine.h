#ifndef JUMP_SLASH_ENGINE_H
#define JUMP_SLASH_ENGINE_H

#include <SFML/Graphics.hpp>

// forward declarations
class Scene;

class JumpSlashEngine // this class is written as a singleton
{
private:

	static JumpSlashEngine* pInstance;

	JumpSlashEngine() = default;
	JumpSlashEngine(const JumpSlashEngine& jse) = delete;
	JumpSlashEngine& operator=(const JumpSlashEngine& jse) = delete;
	virtual ~JumpSlashEngine();

	static JumpSlashEngine& Instance();

public: // public api functions
	/*!
	* \brief Set the name of the window.
	* 
	* TODO: docs for JumpSlashEngine::SetWindowName is incomplete
	*/
	static void SetWindowName(sf::String winName);
	/*!
	* \brief Set the size of the window.
	* 
	* TODO: docs for JumpSlashEngine::SetWindowSize is incomplete
	*/
	static void SetWindowSize(int winWidth, int winHeight);
	// TODO: create function JumpSlashEngine::SetFullscreenMode
	
	// TODO: should these be public?
	static void Run(); // TODO: docs for JumpSlashEngine::Run
	static void Terminate(); // TODO: docs for JumpSlashEngine::Terminate

private: // engine-only api functions
	friend class EngineAttorney;
	static sf::RenderWindow& GetWindow();
	static void SetView(sf::View view);

private: // private api backend functions
	void privSetWindowName(sf::String winName);
	void privSetWindowSize(int winWidth, int winHeight);

	void privRun();

	sf::RenderWindow& privGetWindow();
	void privSetView(sf::View view);

private:
	void Initialize();
	void LoadContent();
	void Update();
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
	* \see	SpriteManager::LoadSprite
	* TODO: add more "see also" references for asset manager load functions as they're created
	*/
	void LoadResources();
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
	void GameEnd(); // TODO: function not defined JumpSlashEngine::GameEnd

private: // member variables
	sf::RenderWindow window;
	sf::String winName;
	int winWidth;
	int winHeight;
	
};

#endif
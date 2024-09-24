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
	virtual ~JumpSlashEngine() = default;

	static JumpSlashEngine& Instance();

public: // public api functions
	static void SetWindowName(sf::String winName); // TODO: documentation for JumpSlashEngine::SetWindowName
	static void SetWindowSize(int winWidth, int winHeight); // TODO: documentation for JumpSlashEngine::SetWindowSize
	// TODO: create function JumpSlashEngine::SetFullscreenMode

	static void SetStartScene(Scene* pStartScene);
	static Scene* GetCurrentScene();
	
	// TODO: should these be public?
	static void Run(); // TODO: documentation for JumpSlashEngine::Run
	static void Terminate(); // TODO: documentation for JumpSlashEngine::Terminate

	static sf::RenderWindow& GetWindow(); // TODO: I don't like this...

private: // private functions
	void privSetWindowName(sf::String winName);
	void privSetWindowSize(int winWidth, int winHeight);

	void privSetStartScene(Scene* pStartScene);
	Scene* privGetCurrentScene();

	void privRun();

	sf::RenderWindow& privGetWindow();

private:
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
	sf::Clock clock;

	Scene* pCurrentScene;
	
};

#endif
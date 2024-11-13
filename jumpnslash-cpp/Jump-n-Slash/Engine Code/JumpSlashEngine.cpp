#include "JumpSlashEngine.h"

// language includes
#include <cassert>

// engine includes
#include "TextureManagerAttorney.h"
#include "SpriteManagerAttorney.h"
#include "GridManagerAttorney.h"
#include "AnimationManagerAttorney.h"
#include "VisualizerAttorney.h"
#include "FontManagerAttorney.h"
#include "VizCmdFactoryAttorney.h"
#include "SceneManagerAttorney.h"
#include "TimeManagerAttorney.h"
#include "TimeManager.h"
#include "ControlManagerAttorney.h"
#include "EngineQuitCommandBase.h"
#include "EngineQuitCommand.h"
#include "EngineDontQuitCommand.h"

// game includes
#include "../Game Code/Constants.h" // TODO: this is awful form. make a separate one for the engine!

JumpSlashEngine* JumpSlashEngine::pInstance = nullptr;

JumpSlashEngine::JumpSlashEngine()
	: window(),
	winName(),
	winWidth(),
	winHeight(),
	pQuitCmd(new EngineQuitCommand()),
	pDontQuitCmd(new EngineDontQuitCommand()),
	pCmdToExe(pDontQuitCmd)
{
	// do nothing
}

JumpSlashEngine::~JumpSlashEngine()
{
	delete pDontQuitCmd;
	delete pQuitCmd;
}

JumpSlashEngine& JumpSlashEngine::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new JumpSlashEngine();
	}
	return *pInstance;
}

void JumpSlashEngine::SetWindowName(sf::String winName)
{
	Instance().privSetWindowName(winName);
}

void JumpSlashEngine::SetWindowSize(int winWidth, int winHeight)
{
	Instance().privSetWindowSize(winWidth, winHeight);
}

void JumpSlashEngine::Run()
{
	Instance().privRun();
}

void JumpSlashEngine::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void JumpSlashEngine::privSetWindowName(sf::String _winName)
{
	winName = _winName;
}

void JumpSlashEngine::privSetWindowSize(int _winWidth, int _winHeight)
{
	winWidth = _winWidth;
	winHeight = _winHeight;
}

void JumpSlashEngine::privRun()
{
	Initialize();
	window.create(sf::VideoMode(winWidth, winHeight), winName);
	window.setFramerateLimit(MAX_FRAMERATE);
	LoadContent();
	TimeManagerAttorney::Time::Start();
	while (window.isOpen())
	{
		Update();
		Draw();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// quit if the window is closed thru the OS
				QuitGame();
				break;
			case sf::Event::KeyPressed:
				// quit if the escape key was pressed
				if (event.key.code == sf::Keyboard::Escape) QuitGame();
				break;
			default:
				break;
			}
		}
		// quit if the game or engine requested it
		pCmdToExe->Execute();
	}
	UnloadContent();
}

void JumpSlashEngine::Initialize()
{
	// Use this area for one-time non-graphic creation
	
	GameInitialize();
}

void JumpSlashEngine::LoadContent()
{
	LoadResources();

	SceneManagerAttorney::Initialization::InitStartScene();
}

void JumpSlashEngine::Update()
{
	TimeManagerAttorney::Time::ProcessTime();

	float deltaTime = TimeManager::GetFrameTime();
	
	SceneManagerAttorney::GameLoop::UpdateCurrentScene(deltaTime);
}

void JumpSlashEngine::Draw()
{
	window.clear();

	SceneManagerAttorney::GameLoop::DrawCurrentScene();

	window.display();
}

void JumpSlashEngine::UnloadContent()
{
	GameEnd();

	// asset managers
	TextureManagerAttorney::Termination::Terminate();
	SpriteManagerAttorney::Termination::Terminate();
	GridManagerAttorney::Termination::Terminate();
	FontManagerAttorney::Termination::Terminate();
	AnimationManagerAttorney::Termination::Terminate();

	// debug tools
	VisualizerAttorney::Termination::Terminate();
	VizCmdFactoryAttorney::Termination::Terminate();

	// main systems
	SceneManagerAttorney::Termination::Terminate();
	TimeManagerAttorney::Termination::Terminate();

	// other
	ControlManagerAttorney::Termination::Terminate();
}

sf::RenderWindow& JumpSlashEngine::GetWindow()
{
	return Instance().privGetWindow();
}

void JumpSlashEngine::SetView(sf::View view)
{
	Instance().privSetView(view);
}

void JumpSlashEngine::RequestQuitGame()
{
	Instance().privRequestQuitGame();
}

void JumpSlashEngine::QuitGame()
{
	Instance().privQuitGame();
}

sf::RenderWindow& JumpSlashEngine::privGetWindow()
{
	return window;
}

void JumpSlashEngine::privSetView(sf::View view)
{
	window.setView(view);
}

void JumpSlashEngine::privRequestQuitGame()
{
	pCmdToExe = pQuitCmd;
}

void JumpSlashEngine::privQuitGame()
{
	// TODO: potentially put an autosave function here
	window.close();
}
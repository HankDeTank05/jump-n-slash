#include "JumpSlashEngine.h"

#include <cassert>
#include "TextureManagerAttorney.h"
#include "SpriteManagerAttorney.h"
#include "GridManagerAttorney.h"
#include "VisualizerAttorney.h"
#include "FontManagerAttorney.h"
#include "VizCmdFactoryAttorney.h"
#include "SceneAttorney.h" // TODO: remove this when SceneManager is created
#include "Scene.h" // TODO: remove this when SceneManager is created

JumpSlashEngine* JumpSlashEngine::pInstance = nullptr;

JumpSlashEngine::~JumpSlashEngine()
{
	pCurrentScene->End();
	delete pCurrentScene;
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

void JumpSlashEngine::SetStartScene(Scene* pStartScene)
{
	Instance().privSetStartScene(pStartScene);
}

Scene* JumpSlashEngine::GetCurrentScene()
{
	return Instance().privGetCurrentScene();
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

void JumpSlashEngine::privSetStartScene(Scene* _pStartScene)
{
	pCurrentScene = _pStartScene;
}

Scene* JumpSlashEngine::privGetCurrentScene()
{
	assert(pCurrentScene != nullptr);
	return pCurrentScene;
}

void JumpSlashEngine::privRun()
{
	Initialize();
	LoadContent();
	window.create(sf::VideoMode(winWidth, winHeight), winName);
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();

		Update(deltaTime.asSeconds());
		Draw();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
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

	assert(pCurrentScene != nullptr); // You forgot to call SetStartScene at the end of LoadContent!
	pCurrentScene->Init();
}

void JumpSlashEngine::Update(float deltaTime)
{
	SceneAttorney::GameLoop::Update(pCurrentScene, deltaTime);
}

void JumpSlashEngine::Draw()
{
	window.clear();

	SceneAttorney::GameLoop::Draw(pCurrentScene);

	window.display();
}

void JumpSlashEngine::UnloadContent()
{
	TextureManagerAttorney::Termination::Terminate();
	SpriteManagerAttorney::Termination::Terminate();
	GridManagerAttorney::Termination::Terminate();
	FontManagerAttorney::Termination::Terminate();
	VisualizerAttorney::Termination::Terminate();
	VizCmdFactoryAttorney::Termination::Terminate();
}

sf::RenderWindow& JumpSlashEngine::GetWindow()
{
	return Instance().privGetWindow();
}

sf::RenderWindow& JumpSlashEngine::privGetWindow()
{
	return window;
}

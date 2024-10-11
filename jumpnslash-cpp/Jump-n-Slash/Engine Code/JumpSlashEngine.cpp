#include "JumpSlashEngine.h"

#include <cassert>
#include "TextureManagerAttorney.h"
#include "SpriteManagerAttorney.h"
#include "GridManagerAttorney.h"
#include "VisualizerAttorney.h"
#include "FontManagerAttorney.h"
#include "VizCmdFactoryAttorney.h"
#include "SceneManagerAttorney.h"

JumpSlashEngine* JumpSlashEngine::pInstance = nullptr;

JumpSlashEngine::~JumpSlashEngine()
{
	// do nothing?
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
	LoadContent();
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

	SceneManagerAttorney::Initialization::InitStartScene();
}

void JumpSlashEngine::Update(float deltaTime)
{
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
	// asset managers
	TextureManagerAttorney::Termination::Terminate();
	SpriteManagerAttorney::Termination::Terminate();
	GridManagerAttorney::Termination::Terminate();
	FontManagerAttorney::Termination::Terminate();

	// debug tools
	VisualizerAttorney::Termination::Terminate();
	VizCmdFactoryAttorney::Termination::Terminate();

	// main systems
	SceneManagerAttorney::Termination::Terminate();
}

sf::RenderWindow& JumpSlashEngine::GetWindow()
{
	return Instance().privGetWindow();
}

void JumpSlashEngine::SetView(sf::View view)
{
	Instance().privSetView(view);
}

sf::RenderWindow& JumpSlashEngine::privGetWindow()
{
	return window;
}

void JumpSlashEngine::privSetView(sf::View view)
{
	window.setView(view);
}

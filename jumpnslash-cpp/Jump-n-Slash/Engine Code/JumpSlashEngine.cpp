#include "JumpSlashEngine.h"

#include "../Game Code/Constants.h"

JumpSlashEngine* JumpSlashEngine::pInstance = nullptr;

JumpSlashEngine::JumpSlashEngine()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME),
	clock()
{
	// do nothing
}

JumpSlashEngine& JumpSlashEngine::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new JumpSlashEngine();
	}
	return *pInstance;
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

void JumpSlashEngine::privRun()
{
	this->Initialize();
	this->LoadContent();
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();

		this->Update(deltaTime.asSeconds());
		this->Draw();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}
	this->UnloadContent();
}

void JumpSlashEngine::Initialize()
{
	// Use this area for one-time non-graphic creation
	
	GameInitialize();
}

void JumpSlashEngine::LoadContent()
{
	LoadResources();
}

void JumpSlashEngine::Update(float deltaTime)
{
	// TODO: engine update system
}

void JumpSlashEngine::Draw()
{
	window.clear();

	// TODO: engine draw system

	// the following will be replaced with the engine draw system
	sf::CircleShape shape(64.0f);
	shape.setFillColor(sf::Color::Green);
	window.draw(shape);
	// the preceding will be replaced with the engine draw system

	window.display();
}

void JumpSlashEngine::UnloadContent()
{
	// TODO: engine unloadcontent function body
}

#include "CompSprTest.h"

// engine includes
#include "../Engine Code/SpriteManager.h"
#include "../Engine Code/SpriteTreeNode.h"
#include "../Engine Code/Sprite.h"

// game includes
#include "GameDebugFlags.h"

CompSprTest::CompSprTest()
	: marioParts(),
	pRoot(nullptr)
{
	RequestSceneEntry();
}

CompSprTest::~CompSprTest()
{
	if (pRoot != nullptr)
	{
		delete pRoot;
	}
}

void CompSprTest::Update(float deltaTime)
{
	if (DEBUG_CONNECTORS)
	{
		for (std::map<std::string, Sprite*>::iterator it = marioParts.begin(); it != marioParts.end(); it++)
		{
			(*it).second->DebugConnectors();
		}
	}

	//SpriteTreeNode::NodeList list = pRoot->Traverse(TreeTraversal::Levelorder);
	pRoot->UpdatePositions();
}

void CompSprTest::Draw()
{
	//Render(marioParts.at("arm back"));
	//Render(marioParts.at("body"));
	//Render(marioParts.at("arm front"));
	//Render(marioParts.at("hand front"));
	SpriteTreeNode::NodeList list = pRoot->Traverse(TreeTraversal::Inorder);
	for (SpriteTreeNode::NodeList::iterator it = list.begin(); it != list.end(); it++)
	{
		Render((*it)->GetSprite());
	}
}

void CompSprTest::OnSceneEntry()
{
	marioParts.emplace("body", SpriteManager::GetSprite("paper mario body"));
	marioParts.at("body")->SetPosition(sf::Vector2f(100.f, 100.f));
	//marioParts.at("body")->AddConnector("body to arm front", sf::Vector2f(107.f, 27.f), 0.f);
	//marioParts.at("body")->AddConnector("body to arm back", sf::Vector2f(48.f, 30.f), 0.f);

	marioParts.emplace("arm front", SpriteManager::GetSprite("paper mario arm front"));
	//marioParts.at("arm front")->AddConnector("body to arm front", sf::Vector2f(30.f, 16.f), 0.f);
	//marioParts.at("arm front")->SetPositionByConnector("body to arm front", marioParts.at("body")->GetPosition() + marioParts.at("body")->GetConnector("body to arm front").first);
	//marioParts.at("arm front")->AddConnector("arm front to hand front", sf::Vector2f(47.f, 91.f), 0.f);

	marioParts.emplace("arm back", SpriteManager::GetSprite("paper mario arm back"));
	//marioParts.at("arm back")->AddConnector("body to arm back", sf::Vector2f(67.f, 16.f), 0.f);
	//marioParts.at("arm back")->SetPositionByConnector("body to arm back", marioParts.at("body")->GetPosition() + marioParts.at("body")->GetConnector("body to arm back").first);

	marioParts.emplace("hand front", SpriteManager::GetSprite("paper mario hand front"));
	//marioParts.at("hand front")->AddConnector("arm front to hand front", sf::Vector2f(70.f, 23.f), 0.f);
	//marioParts.at("hand front")->SetPositionByConnector("arm front to hand front", marioParts.at("arm front")->GetPosition() + marioParts.at("arm front")->GetConnector("arm front to hand front").first);

	pRoot = new SpriteTreeNode(SpriteManager::GetSprite("paper mario body"));
	pRoot->AddChild(true, "body to arm front", sf::Vector2f(107.f, 27.f), sf::Vector2f(30.f, 16.f), SpriteManager::GetSprite("paper mario arm front"));
	pRoot->AddChild(false, "body to arm back", sf::Vector2f(48.f, 30.f), sf::Vector2f(76.f, 16.f), SpriteManager::GetSprite("paper mario arm back"));
}

void CompSprTest::OnSceneExit()
{
	delete pRoot;
	pRoot = nullptr;
}

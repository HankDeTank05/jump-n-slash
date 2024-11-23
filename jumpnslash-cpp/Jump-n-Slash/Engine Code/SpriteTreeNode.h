#ifndef SPRITE_TREE_NODE_H
#define SPRITE_TREE_NODE_H

// language includes
#include <map>
#include <string>
#include <list>

// library includes
#include <SFML/System/Vector2.hpp>

// engine includes
#include "TreeTraversal.h"

// forward declarations
class Sprite;

class SpriteTreeNode
{
public:
	SpriteTreeNode() = delete;
	SpriteTreeNode(Sprite* pSprite);
private:
	SpriteTreeNode(Sprite* pSprite, SpriteTreeNode* pParent, const std::string& nameOfParentConn);
public:
	SpriteTreeNode(const SpriteTreeNode& mstn) = delete;
	SpriteTreeNode& operator=(const SpriteTreeNode& mstn) = delete;
	virtual ~SpriteTreeNode();

	using MapKey = std::pair<bool, std::string>;
	using NodeList = std::list<SpriteTreeNode*>;
	using Subtree = std::map<MapKey, NodeList>;

	void AddChild(bool inFront, const std::string& connName, const sf::Vector2f& connPosOnParent, const sf::Vector2f& connPosOnChild, Sprite* pChildSprite);
	NodeList GetChildren(bool inFront, const std::string& connName);
	NodeList Traverse(TreeTraversal traversalMethod);

	Sprite* GetSprite() const;

	void UpdatePositions();

private:
	void AddChild(bool inFront, const std::string& connName, const sf::Vector2f& connPosOnParent, const sf::Vector2f& connPosOnChild, SpriteTreeNode* pChild);
	NodeList TraversePreorder();
	NodeList TraverseInorder();
	NodeList TraversePostorder();
	NodeList TraverseLevelorder();
	Subtree GetChildren();

private:
	Sprite* pSprite;
	SpriteTreeNode* pParent;
	const std::string nameOfParentConn;
	Subtree children;
};

#endif
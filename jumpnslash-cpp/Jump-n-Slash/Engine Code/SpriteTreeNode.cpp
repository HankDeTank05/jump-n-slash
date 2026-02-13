#include "SpriteTreeNode.h"

// language includes
#include <queue>

// engine includes
#include "Sprite.h"

SpriteTreeNode::SpriteTreeNode(Sprite* _pSprite)
	: pSprite(_pSprite),
	pParent(nullptr),
	nameOfParentConn(),
	children()
{
	// do nothing
}

SpriteTreeNode::SpriteTreeNode(Sprite* _pSprite, SpriteTreeNode* _pParent, const std::string& _nameOfParentConn)
	: pSprite(_pSprite),
	pParent(_pParent),
	nameOfParentConn(_nameOfParentConn),
	children()
{
	// do nothing
}

SpriteTreeNode::~SpriteTreeNode()
{
	assert(false);
}

void SpriteTreeNode::AddChild(bool inFront, const std::string& connName, const sf::Vector2f& connPosOnParent, const sf::Vector2f& connPosOnChild, SpriteTreeNode* pChild)
{
	// create a connector on this sprite if it doesn't already exist
	if (pSprite->HasConnector(connName) == false)
	{
		pSprite->AddConnector(connName, connPosOnParent);
	}

	MapKey key(inFront, connName);

	// create a map entry for this connector name if it doesn't already exist
	if (children.count(key) == 0)
	{
		children.emplace(key, std::list<SpriteTreeNode*>());
	}

	// add the child node to the map entry for this connector name
	children.at(key).push_back(pChild);

	pChild->pSprite->AddConnector(connName, connPosOnChild);
}

SpriteTreeNode::NodeList SpriteTreeNode::TraversePreorder()
{
	NodeList order;

	order.push_back(this);

	// get the sprites behind (left subtree)
	for (Subtree::iterator it = children.begin(); it != children.end(); it++)
	{
		if ((*it).first.first == false)
		{
			for (NodeList::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
			{
				order.splice(order.end(), (*it2)->TraversePreorder());
			}
		}
	}

	// get the sprites in front (right subtree)
	for (Subtree::iterator it = children.begin(); it != children.end(); it++)
	{
		if ((*it).first.first == true)
		{
			for (NodeList::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
			{
				order.splice(order.end(), (*it2)->TraversePreorder());
			}
		}
	}

	return order;
}

SpriteTreeNode::NodeList SpriteTreeNode::TraverseInorder()
{
	NodeList order;

	// get the sprites behind (left subtree)
	for (Subtree::iterator it = children.begin(); it != children.end(); it++)
	{
		if ((*it).first.first == false)
		{
			for (NodeList::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
			{
				order.splice(order.end(), (*it2)->TraverseInorder());
			}
		}
	}

	order.push_back(this);

	// get the sprites in front (right subtree)
	for (Subtree::iterator it = children.begin(); it != children.end(); it++)
	{
		if ((*it).first.first == true)
		{
			for (NodeList::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
			{
				order.splice(order.end(), (*it2)->TraverseInorder());
			}
		}
	}

	return order;
}

SpriteTreeNode::NodeList SpriteTreeNode::TraversePostorder()
{
	NodeList order;

	// get the sprites behind (left subtree)
	for (Subtree::iterator it = children.begin(); it != children.end(); it++)
	{
		if ((*it).first.first == false)
		{
			for (NodeList::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
			{
				order.splice(order.end(), (*it2)->TraversePostorder());
			}
		}
	}

	// get the sprites in front (right subtree)
	for (Subtree::iterator it = children.begin(); it != children.end(); it++)
	{
		if ((*it).first.first == true)
		{
			for (NodeList::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
			{
				order.splice(order.end(), (*it2)->TraversePostorder());
			}
		}
	}

	order.push_back(this);

	return order;
}

SpriteTreeNode::NodeList SpriteTreeNode::TraverseLevelorder()
{
	NodeList order;
	std::queue<SpriteTreeNode*> queue;

	queue.push(this);
	while (queue.empty() == false)
	{
		SpriteTreeNode* pNode = queue.front();
		queue.pop();
		order.push_back(pNode);
		Subtree currentChildren = pNode->GetChildren();

		// get the sprites behind (left subtree)
		for (Subtree::iterator it = currentChildren.begin(); it != currentChildren.end(); it++)
		{
			if ((*it).first.first == false)
			{
				for (NodeList::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
				{
					queue.push(*it2);
				}
			}
		}
		
		// get the sprites in front (right subtree)
		for (Subtree::iterator it = currentChildren.begin(); it != currentChildren.end(); it++)
		{
			if ((*it).first.first == true)
			{
				for (NodeList::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
				{
					queue.push(*it2);
				}
			}
		}
	}

	return order;
}

SpriteTreeNode::Subtree SpriteTreeNode::GetChildren()
{
	return children;
}

void SpriteTreeNode::AddChild(bool inFront, const std::string& connName, const sf::Vector2f& connPosOnParent, const sf::Vector2f& connPosOnChild, Sprite* pChildSprite)
{
	AddChild(inFront, connName, connPosOnParent, connPosOnChild, new SpriteTreeNode(pChildSprite, this, connName));
}

SpriteTreeNode::NodeList SpriteTreeNode::GetChildren(bool inFront, const std::string& connName)
{
	MapKey key(inFront, connName);
	assert(children.count(key) > 0); // no children with this connector name were found!
	return children.at(key);
}

Sprite* SpriteTreeNode::GetSprite() const
{
	return pSprite;
}

void SpriteTreeNode::UpdatePositions()
{
	NodeList list = TraverseLevelorder();

	for (NodeList::iterator it = list.begin(); it != list.end(); it++)
	{
		if (*it != this)
		{
			assert((*it)->pParent != nullptr);

			(*it)->GetSprite()->SetPositionByConnector((*it)->nameOfParentConn, (*it)->pParent->GetSprite()->GetConnector((*it)->nameOfParentConn));

			(*it)->UpdatePositions();
		}
	}
}

SpriteTreeNode::NodeList SpriteTreeNode::Traverse(TreeTraversal traversalMethod)
{
	switch (traversalMethod)
	{
	case TreeTraversal::Preorder:
		return TraversePreorder();
	case TreeTraversal::Inorder:
		return TraverseInorder();
	case TreeTraversal::Postorder:
		return TraversePostorder();
	case TreeTraversal::Levelorder:
		return TraverseLevelorder();
	default:
		assert(false);
	}
}

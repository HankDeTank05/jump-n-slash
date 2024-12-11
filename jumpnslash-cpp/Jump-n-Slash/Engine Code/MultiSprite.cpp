#include "MultiSprite.h"

// engine includes
#include "SpriteTreeNode.h"

MultiSprite::MultiSprite(Sprite* pSprite)
	: pRoot(new SpriteTreeNode(pSprite))
{
	// do nothing
}

MultiSprite::~MultiSprite()
{
	// post-order traversal to delete the tree
	// left, right, root
	delete pRoot;
}

SpriteTreeNode* MultiSprite::GetRoot()
{
	return pRoot;
}

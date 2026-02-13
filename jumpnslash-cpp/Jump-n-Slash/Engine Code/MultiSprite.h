#ifndef MULTI_SPRITE_H
#define MULTI_SPRITE_H

// language includes
#include <list>

// forward declarations
class Sprite;
class SpriteTreeNode;

class MultiSprite
{
public:
	MultiSprite() = delete;
	MultiSprite(Sprite* pSprite);
	MultiSprite(const MultiSprite& ms) = delete;
	MultiSprite& operator=(const MultiSprite& ms) = delete;
	virtual ~MultiSprite();

	SpriteTreeNode* GetRoot();

	std::list<Sprite*> GetDrawOrderList();

private:
	SpriteTreeNode* pRoot;
};

#endif
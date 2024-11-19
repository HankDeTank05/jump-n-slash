#ifndef SPRITE_ATTORNEY_H
#define SPRITE_ATTORNEY_H

// library includes
#include <SFML/Graphics/Sprite.hpp>

// forward declarations
class Sprite;

class SpriteAttorney
{
public:
	class GameObjectAccess
	{
	private:
		friend class DrawObject;
		friend class CollisionObject;
		static sf::Sprite* GetSprite(Sprite* pSprite);
	};
};

#endif
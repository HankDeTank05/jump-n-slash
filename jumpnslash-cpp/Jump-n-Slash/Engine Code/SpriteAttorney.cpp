#include "SpriteAttorney.h"

// engine includes
#include "Sprite.h"

sf::Sprite* SpriteAttorney::GameObjectAccess::GetSprite(Sprite* pSprite)
{
    return pSprite->GetSprite();
}

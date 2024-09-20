#include "SpriteManager.h"

#include <cassert>
#include "TextureManager.h"

SpriteManager* SpriteManager::pInstance = nullptr;

SpriteManager& SpriteManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new SpriteManager();
	}
	return *pInstance;
}

void SpriteManager::LoadSprite(std::string key, sf::Texture* pTex)
{
	Instance().privLoadSprite(key, pTex);
}

void SpriteManager::LoadSprite(std::string key, sf::Texture* pTex, sf::IntRect spriteRect)
{
	Instance().privLoadSprite(key, pTex, spriteRect);
}

void SpriteManager::LoadSprite(std::string key, std::string texKey)
{
	Instance().privLoadSprite(key, texKey);
}

void SpriteManager::LoadSprite(std::string key, std::string texKey, sf::IntRect spriteRect)
{
	Instance().privLoadSprite(key, texKey, spriteRect);
}

sf::Sprite* SpriteManager::GetSprite(std::string key)
{
	return Instance().privGetSprite(key);
}

void SpriteManager::privLoadSprite(std::string key, sf::Texture* pTex)
{

	assert(sprites.count(key) == 0); // Invalid Key: sprite key already exists!
	assert(pTex != nullptr);
	
	sf::Sprite* pSpr = new sf::Sprite();
	pSpr->setTexture(*pTex);

	sprites.emplace(key, pSpr);
}

void SpriteManager::privLoadSprite(std::string key, sf::Texture* pTex, sf::IntRect spriteRect)
{

	assert(sprites.count(key) == 0); // Invalid Key: sprite key already exists!
	assert(pTex != nullptr);

	sf::Sprite* pSpr = new sf::Sprite();
	pSpr->setTexture(*pTex);
	pSpr->setTextureRect(spriteRect);

	sprites.emplace(key, pSpr);
}

void SpriteManager::privLoadSprite(std::string key, std::string texKey)
{

	assert(sprites.count(key) == 0); // Invalid Key: sprite key already exists!

	sf::Sprite* pSpr = new sf::Sprite();
	pSpr->setTexture(*TextureManager::GetTexture(texKey));

	sprites.emplace(key, pSpr);
}

void SpriteManager::privLoadSprite(std::string key, std::string texKey, sf::IntRect spriteRect)
{

	assert(sprites.count(key) == 0); // Invalid Key: sprite key already exists!

	sf::Sprite* pSpr = new sf::Sprite();
	pSpr->setTexture(*TextureManager::GetTexture(texKey));
	pSpr->setTextureRect(spriteRect);

	sprites.emplace(key, pSpr);
}

sf::Sprite* SpriteManager::privGetSprite(std::string key)
{
	assert(sprites.count(key) > 0); // Invalid Key: sprite key not found!

	return sprites.at(key);
}

void SpriteManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

#include "SpriteManager.h"

// language includes
#include <cassert>

// engine includes
#include "TextureManager.h"
#include "Sprite.h"

SpriteManager* SpriteManager::pInstance = nullptr;

SpriteManager::~SpriteManager()
{
	for (std::map<std::string, Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++)
	{
		delete it->second;
	}
}

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

Sprite* SpriteManager::GetSprite(std::string key)
{
	return Instance().privGetSprite(key);
}

void SpriteManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void SpriteManager::privLoadSprite(std::string key, sf::Texture* pTex)
{

	assert(sprites.count(key) == 0); // Invalid Key: sprite key already exists!
	assert(pTex != nullptr);
	
	Sprite* pSpr = new Sprite();
	pSpr->SetTexture(*pTex);

	sprites.emplace(key, pSpr);
}

void SpriteManager::privLoadSprite(std::string key, sf::Texture* pTex, sf::IntRect spriteRect)
{

	assert(sprites.count(key) == 0); // Invalid Key: sprite key already exists!
	assert(pTex != nullptr);

	Sprite* pSpr = new Sprite();
	pSpr->SetTexture(*pTex);
	pSpr->SetTextureRect(spriteRect);

	sprites.emplace(key, pSpr);
}

void SpriteManager::privLoadSprite(std::string key, std::string texKey)
{

	assert(sprites.count(key) == 0); // Invalid Key: sprite key already exists!

	Sprite* pSpr = new Sprite();
	pSpr->SetTexture(*TextureManager::GetTexture(texKey));

	sprites.emplace(key, pSpr);
}

void SpriteManager::privLoadSprite(std::string key, std::string texKey, sf::IntRect spriteRect)
{

	assert(sprites.count(key) == 0); // Invalid Key: sprite key already exists!

	Sprite* pSpr = new Sprite();
	pSpr->SetTexture(*TextureManager::GetTexture(texKey));
	pSpr->SetTextureRect(spriteRect);

	sprites.emplace(key, pSpr);
}

Sprite* SpriteManager::privGetSprite(std::string key)
{
	assert(sprites.count(key) > 0); // Invalid Key: sprite key not found!

	return sprites.at(key);
}

#include "TextureManager.h"

#include <cassert>

TextureManager* TextureManager::pInstance = nullptr;

TextureManager& TextureManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new TextureManager();
	}
	return *pInstance;
}

void TextureManager::LoadTexture(std::string key, std::string filename)
{
	Instance().privLoadTexture(key, filename);
}

sf::Texture* TextureManager::GetTexture(std::string key)
{
	return Instance().privGetTexture(key);
}

void TextureManager::privLoadTexture(std::string key, std::string filename)
{
	assert(textures.count(key) == 0); // Invalid Key: Key already exists!

	std::string relativePath = FOLDER_NAME + filename;

	sf::Texture* pTex = new sf::Texture();
	assert(pTex->loadFromFile(relativePath));
	
	textures.emplace(key, pTex);
}

sf::Texture* TextureManager::privGetTexture(std::string key)
{
	assert(textures.count(key) > 0); // Invalid Key: Key not found!

	return textures.at(key);
}

void TextureManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

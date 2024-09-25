#include "TextureManager.h"

#include <cassert>

TextureManager* TextureManager::pInstance = nullptr;

TextureManager::~TextureManager()
{
	for (std::map<std::string, sf::Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
	{
		delete it->second;
	}
}

TextureManager& TextureManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new TextureManager();
	}
	return *pInstance;
}

void TextureManager::LoadTexture(std::string key, std::string filename, bool smooth)
{
	Instance().privLoadTexture(key, filename, smooth);
}

sf::Texture* TextureManager::GetTexture(std::string key)
{
	return Instance().privGetTexture(key);
}

void TextureManager::privLoadTexture(std::string key, std::string filename, bool smooth)
{
	assert(textures.count(key) == 0); // Invalid Key: texture key already exists!

	std::string relativePath = FOLDER_NAME + filename;

	sf::Texture* pTex = new sf::Texture();
	//pTex->loadFromFile(relativePath) // uncomment this to see the error message if the assert gets triggered
	assert(pTex->loadFromFile(relativePath)); // File not found, probably.
	pTex->setSmooth(smooth);
	
	textures.emplace(key, pTex);
}

sf::Texture* TextureManager::privGetTexture(std::string key)
{
	assert(textures.count(key) > 0); // Invalid Key: texture key not found!

	return textures.at(key);
}

void TextureManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

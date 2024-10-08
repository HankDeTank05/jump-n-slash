#include "FontManager.h"

FontManager* FontManager::pInstance = nullptr;

FontManager::~FontManager()
{
	for (std::map<std::string, sf::Font*>::iterator it = fonts.begin(); it != fonts.end(); it++)
	{
		delete it->second;
	}
}

FontManager& FontManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new FontManager();
	}
	return *pInstance;
}

void FontManager::LoadFont(std::string key, std::string filename)
{
	Instance().privLoadFont(key, filename);
}

sf::Font* FontManager::GetFont(std::string key)
{
	return Instance().privGetFont(key);
}

void FontManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void FontManager::privLoadFont(std::string key, std::string filename)
{
	assert(fonts.count(key) == 0); // if you triggered this assert, the key you tried to use already exists

	std::string relativePath = FOLDER_NAME + filename;

	sf::Font* pFont = new sf::Font();
	//pFont->loadFromFile(relativePath); // uncomment this to see the error message if the assert gets triggered
	assert(pFont->loadFromFile(relativePath)); // file not found, probably

	fonts.emplace(key, pFont);
}

sf::Font* FontManager::privGetFont(std::string key)
{
	assert(fonts.count(key) > 0); // if you triggered this assert, the key you tried to use does not exist

	return fonts.at(key);
}

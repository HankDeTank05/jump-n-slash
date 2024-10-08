#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <SFML/Graphics/Font.hpp>

#include <map>
#include <string>

class FontManager // this class is written as a singleton
{
private:
	static FontManager* pInstance;

	FontManager() = default;
	FontManager(const FontManager& fm) = delete;
	FontManager& operator=(const FontManager& fm) = delete;
	virtual ~FontManager();

	static FontManager& Instance();

public: // public api functions
	static void LoadFont(std::string key, std::string filename); // TODO: docs for FontManager::LoadFont
	static sf::Font* GetFont(std::string key); // TODO: docs for FontManager::GetFont

private: // engine-only api functions
	friend class FontManagerAttorney;
	static void Terminate();

private: // private api backend functions
	void privLoadFont(std::string key, std::string filename);
	sf::Font* privGetFont(std::string key);

private: // member variables
	std::map<std::string, sf::Font*> fonts; // the map containing every font loaded into the engine
	const std::string FOLDER_NAME = "assets/fonts/"; // the name of the folder that font files will be loaded from

};

#endif
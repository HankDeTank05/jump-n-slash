#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

// forward declarations
class TextureManagerAttorney;

class TextureManager // this class is written as a singleton
{
private:
	static TextureManager* pInstance;

	TextureManager() = default;
	TextureManager(const TextureManager& tm) = delete;
	TextureManager& operator=(const TextureManager& tm) = delete;
	~TextureManager() = default;

	static TextureManager& Instance();

public: // api functions
	static void LoadTexture(std::string key, std::string filename);
	static sf::Texture* GetTexture(std::string key);

private: // private functions
	void privLoadTexture(std::string key, std::string filename);
	sf::Texture* privGetTexture(std::string key);

private: // member variables
	std::map<std::string, sf::Texture*> textures;
	const std::string FOLDER_NAME = "Textures\\";

private: // engine-only api functions
	friend class TextureManagerAttorney;
	static void Terminate();
};

#endif
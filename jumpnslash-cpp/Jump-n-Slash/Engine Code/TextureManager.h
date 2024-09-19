#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

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
	/*!
	* \brief	Load a texture into the engine.
	* 
	* Load a texture into the engine. You must specify a key with which to identify the texture, and the name of the file to load.
	* 
	* \param[in]	key			The key used to identify the texture. (Duplicate keys are not allowed!)
	* \param[in]	filename	The name of the file to load. The file must be in TODO(insert folder here).
	* 
	* \return	Does not return anything.
	* 
	* \see	TextureManager::GetTexture
	* 
	* \see	SpriteManager::LoadSprite
	* \see	SpriteManager::GetSprite
	*/
	static void LoadTexture(std::string key, std::string filename); // TODO: add example code to this function's documentation
	/*!
	* \brief	Get a texture which has already been loaded into the engine.
	* 
	* Get a texture from the engine. In order to get a texture from the engine, it must already be loaded it into the engine.
	* 
	* \param[in]	key		The key used to identify the texture. This is the same key used when loading the texture.
	* 
	* \return	Returns a pointer to an SFML texture.
	* 
	* \see	TextureManager::LoadTexture
	* 
	* \see	SpriteManager::LoadSprite
	* \see	SpriteManager::GetSprite
	*/
	static sf::Texture* GetTexture(std::string key); // TODO: add example code to this function's documentation

private: // private functions
	void privLoadTexture(std::string key, std::string filename);
	sf::Texture* privGetTexture(std::string key);

private: // member variables
	std::map<std::string, sf::Texture*> textures; /*!< The map containing every texture loaded into the engine. */
	const std::string FOLDER_NAME = "Assets/Textures/"; /*!< The name of the folder that texture files will be loaded from. */

private: // engine-only api functions
	static void Terminate();
};

#endif
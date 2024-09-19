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
	/*!
	* \brief Load a texture into the engine.
	* 
	* Load a texture into the engine. You must specify the name of the file to load, and a key with which to identify the texture.
	* 
	* \param[in]	key			The key to use to identify the texture. (Duplicate keys are not allowed!)
	* \param[in]	filename	The name of the file to load. The file must be in TODO(insert folder here).
	* 
	* \return	Does not return anything.
	* 
	* \see	TextureManager::GetTexture
	*/
	static void LoadTexture(std::string key, std::string filename);
	/*!
	* \brief Get a texture from the engine which has already been loaded.
	* 
	* Get a texture from the engine. In order to get a texture from the engine, you must have already loaded it into the engine.
	* 
	* \param[in]	key		The key used to identify the texture. This is the same key used when loading the texture.
	* 
	* \return	Returns a pointer to an SFML texture.
	* 
	* \see	TextureManager::LoadTexture
	*/
	static sf::Texture* GetTexture(std::string key);

private: // private functions
	void privLoadTexture(std::string key, std::string filename);
	sf::Texture* privGetTexture(std::string key);

private: // member variables
	std::map<std::string, sf::Texture*> textures; /*!< The map containing every texture loaded into the engine. */
	const std::string FOLDER_NAME = "Textures\\"; /*!< The name of the folder that texture files will be loaded from. */

private: // engine-only api functions
	friend class TextureManagerAttorney;
	static void Terminate();
};

#endif
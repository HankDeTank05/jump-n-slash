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
	virtual ~TextureManager();

	static TextureManager& Instance();

public: // api functions
	/*!
	* \brief	Load a texture into the engine.
	* 
	* Load a texture into the engine. You must specify a key with which to identify the texture, and the name of the file to load.
	* 
	* \param[in]	key			The key used to identify the texture. (Duplicate keys are not allowed!)
	* \param[in]	filename	The name of the file to load. The file must be in \c Assets/Textures/ or a subfolder within it.
	* \param[in]	smooth		Whether or not a texture should be smoothed. If omitted, this argument is \c true by default.
	* 
	* \note		The \c filename argument can include subfolders within the Textures folder. See examples below.
	* 
	* \return	Does not return anything.
	* 
	* \section example1 Example 1
	* \code
	* // LoadResources.cpp
	* #include "../Engine Code/JumpSlashEngine.h"
	* #include "../Engine Code/TextureManager.h"
	* 
	* void JumpSlashEngine::LoadResources()
	* {
	*	// load textures for Fruit Ninja
	*	TextureManager::LoadTexture("apple surface", "apple_surface.png");
	*	TextureManager::LoadTexture("apple inside", "apple_inside.png");
	*	TextureManager::LoadTexture("orange surface", "orange_surface.png");
	*	TextureManager::LoadTexture("orange inside", "orange_inside.png");
	*	TextureManager::LoadTexture("banana surface", "banana_surface.png");
	*	TextureManager::LoadTexture("banana inside", "banana_inside.png");
	*	TextureManager::LoadTexture("pineapple surface", "pineapple_surface.png");
	*	TextureManager::LoadTexture("pineapple inside", "pineapple_inside.png");
	*	TextureManager::LoadTexture("watermelon surface", "watermelon_surface.png");
	*	TextureManager::LoadTexture("watermelon inside", "watermelon_inside.png");
	* }
	* \endcode
	* 
	* \section example2 Example 2
	* \code
	* // LoadResources.cpp
	* #include "../Engine Code/JumpSlashEngine.h"
	* #include "../Engine Code/TextureManager.h"
	* 
	* void JumpSlashEngine::LoadResources()
	* {
	*	// load textures for Super Mario Bros.
	*	// these textures are pixel art, so we don't want them smoothed
	*	TextureManager::LoadTexture("question block", "blocks/question_block.png", false);
	*	TextureManager::LoadTexture("brick block", "blocks/brick_block.png", false);
	*	TextureManager::LoadTexture("mario spritesheet", "characters/mario_spritesheet.png", false);
	*	TextureManager::LoadTexture("clouds", "backgrounds/cloud_tiles.png", false);
	* }
	* \endcode
	* 
	* \see	TextureManager::GetTexture
	* 
	* \see	SpriteManager::LoadSprite
	* \see	SpriteManager::GetSprite
	*/
	static void LoadTexture(std::string key, std::string filename, bool smooth = true);
	/*!
	* \brief	Get a texture which has already been loaded into the engine.
	* 
	* Get a texture from the engine. In order to get a texture from the engine, it must already be loaded it into the engine.
	* 
	* \param[in]	key		The key used to identify the texture. This is the same key used when loading the texture.
	* 
	* \return	Returns a pointer to an SFML texture.
	* 
	* \b Example
	* \code
	* // LoadResources.cpp
	* #include "../Engine Code/JumpSlashEngine.h"
	* #include "../Engine Code/TextureManager.h"
	* 
	* void JumpSlashEngine::LoadResources()
	* {
	*	// make sure the pixelated textures for Super Mario Bros. are not smoothed
	*	assert(TextureManager::GetTexture("question block").isSmooth() == false);
	*	assert(TextureManager::GetTexture("brick block").isSmooth() == false);
	*	assert(TextureManager::GetTexture("mario spritesheet").isSmooth() == false);
	*	assert(TextureManager::GetTexture("clouds").isSmooth() == false);
	* }
	* \endcode
	* 
	* \see	TextureManager::LoadTexture
	* \see	SpriteManager::LoadSprite
	* \see	SpriteManager::GetSprite
	*/
	static sf::Texture* GetTexture(std::string key);

private: // engine-only api functions
	friend class TextureManagerAttorney;
	static void Terminate();

private: // private api backend functions
	void privLoadTexture(std::string key, std::string filename, bool smooth);
	sf::Texture* privGetTexture(std::string key);

private: // member variables
	std::map<std::string, sf::Texture*> textures; /*!< The map containing every texture loaded into the engine. */
	const std::string FOLDER_NAME = "assets/textures/"; /*!< The name of the folder that texture files will be loaded from. */
};

#endif
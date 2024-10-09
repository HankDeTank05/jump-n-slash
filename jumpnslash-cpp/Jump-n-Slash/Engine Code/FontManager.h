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
	/*!
	* \brief	Load a font into the engine.
	* 
	* Load a font into the engine. You must specify a key with which to identify the font, and the name of the file to load.
	* 
	* \param[in]	key			The key used to identify the font. (Duplicate keys are not allowed!)
	* \param[in]	filename	The name of the file to load. The file must be in \c assets/fonts/ or a subfolder within it.
	* 
	* \note		The \c filename argument can include subfolders within the \c fonts folder. See examples below.
	* 
	* \return	Does not return anything.
	* 
	* \section example1 Example 1
	* The following example demonstrates how to load a font located in the \c fonts folder.
	* \code
	* // LoadResources.cpp
	* #include "../Engine Code/JumpSlashEngine.h"
	* #include "../Engine Code/FontManager.h"
	* 
	* void JumpSlashEngine::LoadResources()
	* {
	*	// load fonts
	*	FontManager::LoadFont("arial", "arial.ttf");
	*	FontManager::LoadFont("consolas", "consola.tff");
	*	FontManager::LoadFont("delfino", "Delfino.ttf");
	* }
	* \endcode
	* \section example2 Example 2
	* The following example demonstrates how to load fonts located a subfolder within the \c fonts folder.
	* \code
	* // LoadResources.cpp
	* #include "../Engine Code/JumpSlashEngine.h"
	* #include "../Engine Code/FontManager.h"
	* 
	* void JumpSlashEngine::LoadResources()
	* {
	*	// load fonts
	*	FontManager::LoadFont("arial", "standard/arial.ttf");
	*	FontManager::LoadFont("consolas", "monospaced/consola.tff");
	*	FontManager::LoadFont("delfino", "standard/Delfino.ttf");
	* }
	* \endcode
	* 
	* \see	TextureManager
	* \see	SpriteManager
	* \see	GridManager
	*/
	static void LoadFont(std::string key, std::string filename);
	/*!
	* \brief	Get a font which has already been loaded into the engine.
	* 
	* Get a font from the engine. In order to get a font from the engine, it must already be loaded into the engine.
	* 
	* \param[in]	key		The key used to identify the font. This is the same key used when loading the font.
	* 
	* \return	Returns a pointer to an SFML font.
	* 
	* \see	TextureManager
	* \see	SpriteManager
	* \see	GridManager
	*/
	static sf::Font* GetFont(std::string key); // TODO: docs for FontManager::GetFont needs example code

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
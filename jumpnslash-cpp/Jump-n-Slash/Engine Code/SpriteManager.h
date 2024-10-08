#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class SpriteManager // this class is written as a singleton
{
private:
	static SpriteManager* pInstance;

	SpriteManager() = default;
	SpriteManager(const SpriteManager& sm) = delete;
	SpriteManager& operator=(const SpriteManager& sm) = delete;
	virtual ~SpriteManager();

	static SpriteManager& Instance();

public: // api functions
	/*!
	* \brief	Load a sprite into the engine with a texture pointer, using the whole texture.
	* 
	* Load a sprite into the engine. You must specify a key with which to identify the sprite, and provide a pointer to an existing texture.
	* 
	* \param[in]	key		The key used to identify the sprite. (Duplicate keys are not allowed!)
	* \param[in]	pTex	A pointer to the texture with which to create the sprite. The entire texture will be used.
	* 
	* \return	Does not return anything.
	* 
	* \see	SpriteManager::LoadSprite(std::string key, sf::Texture* pTex, sf::IntRect spriteRect)
	* \see	SpriteManager::LoadSprite(std::string key, std::string texKey)
	* \see	SpriteManager::LoadSprite(std::string key, std::string texKey, sf::IntRect spriteRect)
	* \see	SpriteManager::GetSprite
	* 
	* \see	TextureManager::LoadTexture
	* \see	TextureManager::GetTexture
	*/
	static void LoadSprite(std::string key, sf::Texture* pTex); // TODO: docs for SpriteManager::LoadSprite(key, pTex) needs example code
	/*!
	* \brief	Load a sprite into the engine with a texture pointer, using a part of the texture.
	* 
	* Load a sprite into the engine. You must specify a key with which to identify the sprite, provide a pointer to an existing texture, and provide an sf::IntRect specifying the area of the texture to be used in the sprite.
	* 
	* \param[in]	key			The key used to identify the sprite. (Duplicate keys are not allowed!)
	* \param[in]	pTex		A pointer to the texture with which to create the sprite. Only the portion of the texture specified by the spriteRect will be used.
	* \param[in]	spriteRect	The rectangle defining the area of the texture to be used in the sprite. This area can be smaller than the texture, or larger than it.
	* 
	* \return	Does not return anything.
	* 
	* \see	SpriteManager::LoadSprite(std::string key, sf::Texture* pTex)
	* \see	SpriteManager::LoadSprite(std::string key, std::string texKey)
	* \see	SpriteManager::LoadSprite(std::string key, std::string texKey, sf::IntRect spriteRect)
	* \see	SpriteManager::GetSprite
	* 
	* \see	TextureManager::LoadTexture
	* \see	TextureManager::GetTexture
	*/
	static void LoadSprite(std::string key, sf::Texture* pTex, sf::IntRect spriteRect); // TODO: docs for SpriteManager::LoadSprite(key, pTex, spriteRect) need example code
	/*!
	* \brief	Load a sprite into the engine with a texture key, using the whole texture.
	* 
	* Load a sprite into the engine. You must specify a key with which to identify the sprite, and provide the key of a texture loaded into the engine.
	* 
	* \param[in]	key		The key used to identify the sprite. (Duplicate keys are not allowed!)
	* \param[in]	texKey	The key of the texture with which to create the sprite. The entire texture will be used. (The texture must already be loaded into the engine when this function is called.)
	* 
	* \return	Does not return anything.
	* 
	* \see	SpriteManager::LoadSprite(std::string key, sf::Texture* pTex)
	* \see	SpriteManager::LoadSprite(std::string key, sf::Texture* pTex, sf::IntRect spriteRect)
	* \see	SpriteManager::LoadSprite(std::string key, std::string texKey, sf::IntRect spriteRect)
	* \see	SpriteManager::GetSprite
	* 
	* \see	TextureManager::LoadTexture
	* \see	TextureManager::GetTexture
	*/
	static void LoadSprite(std::string key, std::string texKey); // TODO: docs for SpriteManager::LoadSprite(key, texKey) needs example code
	/*!
	* \brief	Load a sprite into the engine with a texture key, using a part of the texture
	* 
	* Load a sprite into the engine. You must specify a key with which to identify the sprite, provide the key of a texture loaded into the engine, and provide an sf::IntRect specifying the area of the texture to be used in the sprite.
	* 
	* \param[in]	key			The key used to identify the sprite. (Duplicate keys are not allowed!)
	* \param[in]	texKey		The key of the texture with which to create the sprite. Only the portion of the texture specified by the spriteRect will be used. (The texture must already be loaded into the engine when this function is called.)
	* \param[in]	spriteRect	The rectangle defining the area of the texture to be used in the sprite. This area can be smaller than the texture, or larger than it.
	* 
	* \return	Does not return anything.
	* 
	* \see	SpriteManager::LoadSprite(std::string key, sf::Texture* pTex)
	* \see	SpriteManager::LoadSprite(std::string key, sf::Texture* pTex, sf::IntRect spriteRect)
	* \see	SpriteManager::LoadSprite(std::string key, std::string texKey)
	* \see	SpriteManager::GetSprite
	* 
	* \see	TextureManager::LoadTexture
	* \see	TextureManager::GetTexture
	*/
	static void LoadSprite(std::string key, std::string texKey, sf::IntRect spriteRect); // TODO: docs for SpriteManager::LoadSprite(key, texKey, spriteRect) needs example code
	/*!
	* \brief	Get a sprite which has already been loaded into the engine.
	* 
	* Get a sprite from the engine. In order to get a sprite from the engine, it must already be loaded into the engine.
	* 
	* \param[in]	key		The key used to identify the sprite. This is the same key used when loading the texture.
	* 
	* \return	Returns a pointer to an SFML sprite.
	* 
	* \see	SpriteManager::LoadSprite(std::string key, sf::Texture* pTex)
	* \see	SpriteManager::LoadSprite(std::string key, sf::Texture* pTex, sf::IntRect spriteRect)
	* \see	SpriteManager::LoadSprite(std::string key, std::string texKey)
	* \see	SpriteManager::LoadSprite(std::string key, std::string texKey, sf::IntRect spriteRect)
	* 
	* \see	TextureManager::LoadTexture
	* \see	TextureManager::GetTexture
	*/
	static sf::Sprite* GetSprite(std::string key); // TODO: docs for SpriteManager::GetSprite(key) needs example code

private: // engine-only api functions
	friend class SpriteManagerAttorney;
	static void Terminate();

private: // private api backend functions
	void privLoadSprite(std::string key, sf::Texture* pTex);
	void privLoadSprite(std::string key, sf::Texture* pTex, sf::IntRect spriteRect);
	void privLoadSprite(std::string key, std::string texKey);
	void privLoadSprite(std::string key, std::string texKey, sf::IntRect spriteRect);
	sf::Sprite* privGetSprite(std::string key);

private: // member variables
	std::map<std::string, sf::Sprite*> sprites; /*!< The map containing every sprite loaded into the engine. */
};

#endif
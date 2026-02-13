#ifndef SPRITE_H
#define SPRITE_H

// language includes
#include <map>
#include <string>
#include <queue>

// library includes
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

// forward declarations
class SpriteCommand;

class Sprite
{
public:
	Sprite();
	Sprite(const sf::Texture& texture); // specialized constructor from sf::Sprite
	Sprite(const sf::Texture& texture, const sf::IntRect& rectangle); // specialized constructor from sf::Sprite
	Sprite(const Sprite& s) = delete;
	Sprite& operator=(const Sprite& s) = delete;
	virtual ~Sprite();

	// stuff specific to this class

	using Connector = sf::Vector2f; // landmark points on the sprite
	using ConnectorMap = std::map<std::string, Connector>; // multiple connection points are allowed, and each one has a name

	/*!
	* \brief	Add a connector to this sprite.
	* 
	* Add a connector to this sprite with the given name.
	* Connectors allow you to positionally and rotationally link two sprites together at fixed points on each sprite.
	* 
	* \note	If a connector with the given name already exists, the game will crash forcing you to fix the error.
	* 
	* \param[in]	name	The name of the connector you're creating. This will be used when accessing or modifying this connector in the future.
	* \param[in]	pos		The position of the connector, relative to the top-left corner of the sprite
	* \param[in]	rot		The rotation of the connector, which will be applied to connected sprites.
	* 
	* TODO: docs for Sprite::AddConnector needs example code
	* 
	* \return	Does not return anything.
	* 
	* TODO: docs for Sprite::AddConnector needs example code
	* 
	* \see	Sprite::ModifyConnector
	* \see	Sprite::GetConnector
	*/
	void AddConnector(const std::string& name, const sf::Vector2f& pos);
	/*!
	* \brief	Modify an existing connector on this sprite.
	* 
	* Modify an existing connector on this sprite with the given name. This will overwrite the existing position and rotation for that connector.
	* 
	* \note	If no connector with the given name is found, the game will crash forcing you to fix the error.
	* 
	* \param[in]	name	The name of the connector you would like to modify.
	* \param[in]	pos		The new position of the connector, relative to the top-left corner of the sprite.
	* \param[in]	rot		The new rotation of the connector, which will be applied to connected sprites.
	* 
	* TODO: docs for Sprite::GetConnector needs example code
	* 
	* \see	Sprite::AddConnector
	* \see	Sprite::GetConnector
	*/
	void ModifyConnector(const std::string& name, const sf::Vector2f& pos);
	/*!
	* \brief	Get a connector from this sprite.
	* 
	* Get a connector from this sprite with the given name.
	* 
	* \note	If no connector with the given name is found, the game will crash forcing you to fix the error.
	* 
	* \param[in]	name	The name of the connector you would like to get
	* 
	* \return	A \c Sprite::Connector
	* 
	* \note	\c Sprite::Connector is a \c using definition for \c std::pair<sf::Vector2f, float> where the \c sf::Vector2f is the position of the connector relative to the
	* origin of the sprite, and \c float is the rotation to be applied to the connected sprite.
	* 
	* TODO: docs for Sprite::GetConnector needs example code
	* 
	* \see	Sprite::AddConnector
	* \see	Sprite::ModifyConnector
	*/
	sf::Vector2f GetConnector(const std::string& name);
	// TODO: docs for Sprite::HasConnector
	bool HasConnector(const std::string& name);

	void DebugConnectors();

	void SetPositionByConnector(const std::string& name, const sf::Vector2f& pos);

	// texture stuff (from sf::Sprite)

	void SetTexture(const sf::Texture& texture, bool resetRect = false);
	void SetTextureRect(const sf::IntRect& rectangle);
	const sf::Texture* GetTexture() const;
	const sf::IntRect& GetTextureRect() const;

	// color stuff (from sf::Sprite)

	void SetColor(const sf::Color& newColor);
	const sf::Color& GetColor() const;

	// collision stuff (from sf::Sprite)

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;

	// transform stuff (from sf::Sprite)

	void SetPosition(const sf::Vector2f& newPos);
	void Move(const sf::Vector2f& posDelta);
	const sf::Vector2f& GetPosition() const;
	
	void SetRotation(float newDeg);
	void Rotate(float degDelta);
	float GetRotation() const;
	
	void SetScale(const sf::Vector2f& newScale);
	void Scale(const sf::Vector2f& scaleRelative);
	const sf::Vector2f& GetScale() const;

	void SetOrigin(const sf::Vector2f& newOrigin);
	const sf::Vector2f& GetOrigin() const;

	const sf::Transform& GetTransform() const;
	const sf::Transform& GetInverseTransform() const;

private: // engine-only functions (accessible through attorney)
	friend class SpriteAttorney;
	sf::Sprite* GetSprite();

private:
	sf::Sprite* pSprite; // the sf::Sprite to be manipulated/drawn
	ConnectorMap connMap; // a map of the original connector data
	ConnectorMap connMods; // a map of the modified connector data based on transformations
	std::queue<SpriteCommand*> tformOps; // a queue of transform operations (commands) for processing at time of drawing
};

#endif
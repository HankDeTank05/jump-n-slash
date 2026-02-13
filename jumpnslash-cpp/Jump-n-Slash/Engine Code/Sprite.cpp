#include "Sprite.h"

// engine includes
#include "Visualizer.h"

Sprite::Sprite()
	: pSprite(new sf::Sprite()),
	connMap(),
	connMods(),
	tformOps() // TODO: this is currently not being used
{
	// do nothing
}

Sprite::Sprite(const sf::Texture& texture)
	: pSprite(new sf::Sprite(texture)),
	connMap()
{
	// do nothing
}

Sprite::Sprite(const sf::Texture& texture, const sf::IntRect& rectangle)
	: pSprite(new sf::Sprite(texture, rectangle)),
	connMap()
{
	// do nothing
}

Sprite::~Sprite()
{
	connMap.clear();

	delete pSprite;
}

void Sprite::AddConnector(const std::string& name, const sf::Vector2f& pos)
{
	assert(connMap.count(name) == 0); // no duplicate names allowed!
	assert(connMods.count(name) == 0);

	connMap.emplace(name, Connector(pos));
	connMods.emplace(name, connMap.at(name));
}

void Sprite::ModifyConnector(const std::string& name, const sf::Vector2f& pos)
{
	assert(connMap.count(name) > 0); // a connector with that name doesn't exist!
	assert(connMods.count(name) > 0);

	connMap.at(name) = Connector(pos);
	connMods.emplace(name, connMap.at(name));
}

sf::Vector2f Sprite::GetConnector(const std::string& name)
{
	assert(connMap.count(name) > 0); // a connector with that name doesn't exist!
	assert(connMods.count(name) > 0);

	return /*pSprite->getPosition() +*/ connMods.at(name);
}

bool Sprite::HasConnector(const std::string& name)
{
	assert(connMap.count(name) == connMods.count(name));
	return connMap.count(name) > 0;
}

void Sprite::DebugConnectors()
{
	for (ConnectorMap::iterator it = connMods.begin(); it != connMods.end(); it++)
	{
		std::string name = (*it).first;
		sf::Vector2f pos = pSprite->getPosition() + pSprite->getOrigin() + (*it).second;

		sf::Color color = sf::Color::White;

		// draw the point
		Visualizer::VisualizePoint(pos, color);

		// draw the name
		Visualizer::VisualizeText(name, pos, color);
	}
}

void Sprite::SetPositionByConnector(const std::string& name, const sf::Vector2f& pos)
{
	Connector conn = GetConnector(name);
	SetPosition(pos - conn);
}

void Sprite::SetTexture(const sf::Texture& texture, bool resetRect)
{
	pSprite->setTexture(texture, resetRect);
}

void Sprite::SetTextureRect(const sf::IntRect& rectangle)
{
	pSprite->setTextureRect(rectangle);
}

const sf::Texture* Sprite::GetTexture() const
{
	return pSprite->getTexture();
}

const sf::IntRect& Sprite::GetTextureRect() const
{
	return pSprite->getTextureRect();
}

void Sprite::SetOrigin(const sf::Vector2f& newOrigin)
{
	for (ConnectorMap::iterator it = connMap.begin(); it != connMap.end(); it++)
	{
		std::string name = (*it).first;
		sf::Vector2f pos = (*it).second;

		Connector connModded(pos - newOrigin);
		connMods.at(name) = connModded;
	}

	pSprite->setOrigin(newOrigin);
}

const sf::Vector2f& Sprite::GetOrigin() const
{
	return pSprite->getOrigin();
}

const sf::Transform& Sprite::GetTransform() const
{
	return pSprite->getTransform();
}

const sf::Transform& Sprite::GetInverseTransform() const
{
	return pSprite->getInverseTransform();
}

sf::Sprite* Sprite::GetSprite()
{
	return pSprite;
}

void Sprite::SetColor(const sf::Color& newColor)
{
	pSprite->setColor(newColor);
}

const sf::Color& Sprite::GetColor() const
{
	return pSprite->getColor();
}

sf::FloatRect Sprite::GetLocalBounds() const
{
	return pSprite->getLocalBounds();
}

sf::FloatRect Sprite::GetGlobalBounds() const
{
	return pSprite->getGlobalBounds();
}

void Sprite::SetPosition(const sf::Vector2f& newPos)
{
	pSprite->setPosition(newPos);
}

void Sprite::Move(const sf::Vector2f& posDelta)
{
	pSprite->move(posDelta);
}

const sf::Vector2f& Sprite::GetPosition() const
{
	return pSprite->getPosition();
}

void Sprite::SetRotation(float newDeg)
{
	pSprite->setRotation(newDeg);
}

void Sprite::Rotate(float degDelta)
{
	pSprite->rotate(degDelta);
}

float Sprite::GetRotation() const
{
	return pSprite->getRotation();
}

void Sprite::SetScale(const sf::Vector2f& newScale)
{
	for (ConnectorMap::iterator it = connMap.begin(); it != connMap.end(); it++)
	{
		std::string name = (*it).first;
		sf::Vector2f pos = (*it).second;

		Connector connModded(sf::Vector2f(pos.x * newScale.x, pos.y * newScale.y));
		connMods.at(name) = connModded;
	}

	pSprite->setScale(newScale);
}

void Sprite::Scale(const sf::Vector2f& scaleRelative)
{
	// TODO: test that this actually works
	for (ConnectorMap::iterator it = connMods.begin(); it != connMods.end(); it++)
	{
		std::string name = (*it).first;
		sf::Vector2f pos = (*it).second;

		connMods.at(name) = Connector(sf::Vector2f(pos.x * scaleRelative.x, pos.y * scaleRelative.y));
	}

	pSprite->scale(scaleRelative);
}

const sf::Vector2f& Sprite::GetScale() const
{
	return pSprite->getScale();
}

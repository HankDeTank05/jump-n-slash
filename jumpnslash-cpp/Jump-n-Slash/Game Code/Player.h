#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "../Engine Code/UpdatableObject.h"
#include "../Engine Code/DrawableObject.h"
#include "../Engine Code/InputObject.h"

// forward declarations
class PlayerMoveState;

class Player : public UpdatableObject, public DrawableObject, public InputObject
{
public:
	Player() = delete;
	Player(sf::Vector2f spawnPoint);
	Player(const Player& p) = delete;
	Player& operator=(const Player& p) = delete;
	virtual ~Player();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	virtual void KeyPressed(sf::Keyboard::Key key) override;
	virtual void KeyReleased(sf::Keyboard::Key key) override;

private: // player accessors. for selective access only (thru attorney)
	friend class PlayerAttorney;
	sf::Vector2f GetPos();
	sf::Vector2f GetPosDelta();

private: // player mutators. for selective access only (thru attorney)
	void SetSpawnPoint(sf::Vector2f spawnPoint);

private:
	sf::Vector2f pos;
	sf::Vector2f posDelta;
	float speed;
	sf::Sprite* pSprite;
	const PlayerMoveState* pCurrentState;
	sf::Vector2f respawnPoint;
};

#endif
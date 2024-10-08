#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "../Engine Code/UpdateObject.h"
#include "../Engine Code/DrawObject.h"
#include "../Engine Code/InputObject.h"

// forward declarations
class PlayerMoveState;
class LevelMap;

class Player : public UpdateObject, public DrawObject, public InputObject
{
public:
	Player() = delete;
	Player(LevelMap* pLevel);
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
	LevelMap* GetLevel();

private: // player mutators. for selective access only (thru attorney)
	void SetPosX(float newX);
	void SetPosY(float newY);
	void RaycastRight(float deltaTime);
	void RaycastLeft(float deltaTime);
	void RaycastUp(float deltaTime);
	void RaycastDown(float deltaTime);

private:
	sf::Vector2f pos;
	sf::Vector2f posDelta;
	float speed;
	sf::Sprite* pSprite;
	const PlayerMoveState* pCurrentState;
	sf::Vector2f respawnPoint;
	LevelMap* pLevel;
};

#endif
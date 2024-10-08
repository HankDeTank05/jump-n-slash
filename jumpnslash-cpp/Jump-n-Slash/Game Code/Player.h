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
	void RaycastRight(float deltaTime);
	void RaycastLeft(float deltaTime);
	void RaycastUp(float deltaTime);
	void RaycastDown(float deltaTime);

private:
	sf::Vector2f pos; // current world-space position
	sf::Vector2f posDelta; // player movement for the current frame (aka, the change from previous frame)
	float speed; // horizontal movement speed
	sf::Sprite* pSprite; // the sprite to be drawn
	const PlayerMoveState* pCurrentState; // the current movement state
	sf::Vector2f respawnPoint; // where the player will respawn after dying
	LevelMap* pLevel; // pointer to the current level (for map collision)
	bool walkLeftHeld; // flag indicating if the walk left key is currently pressed
	bool walkRightHeld; // flag indicating if the walk right key is currently pressed
};

#endif
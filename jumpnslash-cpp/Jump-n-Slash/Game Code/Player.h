#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player();
	Player(const Player& p) = delete;
	Player& operator=(const Player& p) = delete;
	~Player();
};

#endif
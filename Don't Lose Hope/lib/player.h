#ifndef PLAYER_H
#define PLAYER_H
#ifndef PLAYER_MAX_LIFES
#define PLAYER_MAX_LIFES 3

class Player
{
public:
	Player() {
		current_lifes = PLAYER_MAX_LIFES;
	}
	~Player();

	void setLifes(unsigned int lifeQtt) { current_lifes = lifeQtt; }
	unsigned int getLifes() { return current_lifes; }

private:
	unsigned int current_lifes;
};

#endif
#endif

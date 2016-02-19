#ifndef PLAYER_H
#define PLAYER_H

#ifndef PLAYER_MAX_LIFES
#define PLAYER_MAX_LIFES 3
#endif

#ifndef MOVE_SPEED
#define MOVE_SPEED 100.0
#endif

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>


enum MOVEMENT {STOPPED, UP, RIGHT, DOWN, LEFT};

class Player
{
public:
	Player();
	~Player();

	// NOT IMPLEMENTED YET
	//void setLifes(unsigned int lifeQtt);
	//unsigned int getLifes();

	//sf::Vector2f getPosition();
	//void setPosition();

	void move(int moveDirection);
	void stop();

	int getDirection();
	void setDirection(int newDirection);

	void loadTextures();
	void loadShape(int size);

	void setLevel(int i){level = i;}

	sf::Vector2f getNextPosition();

	std::vector<std::vector<sf::Texture>> textures = std::vector<std::vector<sf::Texture>>(5,std::vector<sf::Texture>(4));
	
	sf::RectangleShape shape; // Player shape

	sf::Vector2f position; // Player position on screen

	bool changeSide = false; // ???????
protected:

private:
	//unsigned int current_lifes;
	int direction;
	int movecounter = 0;

	int shapeSize = 0;

	sf::Clock ClockAnimation;
	sf::Clock ClockSpeed;
	int level;

	
};


#endif

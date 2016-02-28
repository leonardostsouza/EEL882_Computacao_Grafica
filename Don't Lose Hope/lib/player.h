/********************************************************
* UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
* COMPUTAÇÃO GRÁFICA (EEL882) - PROF. CLÁUDIO ESPERANÇA
*
* TRABALHO 3
*
* ALUNOS:
* LEONARDO SOUZA - 112086681
* RAPHAEL SATHLER - 111344078
********************************************************/

#ifndef PLAYER_H
#define PLAYER_H

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

	/*******************************************************
	*  void move(int moveDirection)
	*  moves player continuouslly in a given direction 
	*  movedirection -  direction to which player will move 
	*					treated values are listed in enum MOVEMENT
	********************************************************/	
	void move(int moveDirection);
	void stop();

	int getDirection();	
	void setDirection(int newDirection); // changes direction player is oriented

	void loadTextures(); // loads player textures (human and splash)

	/*******************************************************
	*  void loadShape(int size)
	*  loads and sets parameters for player shape
	*  int size - dimentions the shape will take (size x size)
	********************************************************/
	void loadShape(int size);

	int splash(); // triggers water splash animation. Called when player steps on water

	/*******************************************************
	*  sf::Vector2f getNextPosition()
	*  returns the position on screen which will be occupied by the player
	*  if it continues in the same trajectory
	********************************************************/
	sf::Vector2f getNextPosition();
	
	sf::RectangleShape shape; // Player shape
	sf::Vector2f position; // Player position on screen
protected:

private:
	// control variables
	int direction;
	int movecounter = 0;
	int splashCounter = 0;
	int shapeSize = 0;
	sf::Clock ClockAnimation;
	sf::Clock ClockSpeed;

	// textures
	std::vector<std::vector<sf::Texture>> textures = std::vector<std::vector<sf::Texture>>(5,std::vector<sf::Texture>(4));
	std::vector<sf::Texture> splashTextures = std::vector<sf::Texture>(9);
};


#endif

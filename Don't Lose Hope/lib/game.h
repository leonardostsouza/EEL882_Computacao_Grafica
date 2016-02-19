#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include "utilities.h"
#include "player.h"
#include "screen.h"

class Game
{
public:
	Game(bool fs = false, sf::RenderWindow* wd = NULL, sf::VideoMode vm = {0,0,0}, std::vector<std::string> maps = {""});
//	Game(bool fs = false, sf::RenderWindow* wd = NULL, sf::VideoMode vm = {0,0,0});
	~Game();
	GAMESTATE eventHandler(bool isFullscren, bool isSoundEnabled, int level);

protected:
	void createBackground();
	void createMusic();
	bool isFullscreen();
	void setFullscreen(bool fs);
	void createGrid();
	void loadTextures();
	void mapParser(std::string mapFile);
	void movePlayer();
	sf::Vector2f getGridPos(sf::Vector2f objPosition); // return grid position from screen position

private:
	const float Speed = 100.f;
	bool fullscreen;
	bool enableDrawing;
	bool changeSide = false;
	std::vector<std::string> levels;
	
	bool left = true;
	int movecounter = 0;
	//sf::Clock ClockAnimation;
	//sf::Clock ClockSpeed;
	//sf::Vector2f playerPos;
	sf::VideoMode vmode;
	sf::RenderWindow* App;
	sf::Sprite background;
	sf::Font font;
	sf::SoundBuffer buffer;
	sf::Sound bgMusic;		
	sf::Texture texture;
	std::vector<sf::Vector2f> obstaclesPos = std::vector<sf::Vector2f>(5);
	std::vector<sf::Text> menu;
	std::vector<sf::Texture> obstacles = std::vector<sf::Texture>(5);
	//std::vector<std::vector<sf::Texture>> player = std::vector<std::vector<sf::Texture>>(5,std::vector<sf::Texture>(4));
	std::vector<sf::Texture> house = std::vector<sf::Texture>(2);
	sf::Vector2f housePos;
	//sf::RectangleShape playerShape;
	std::vector<std::vector<sf::RectangleShape>> grid = std::vector<std::vector<sf::RectangleShape>>(6,std::vector<sf::RectangleShape>(7));

	enum DIRECTION {STOPPED, UP, RIGHT, DOWN, LEFT};
	int moving;

	Player* playerObj;
};

#endif
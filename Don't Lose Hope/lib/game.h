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

class Game
{
public:
	Game(bool fs = false, sf::RenderWindow* wd = NULL, sf::VideoMode vm = {0,0,0}, std::vector<std::string> maps = {""});
//	Game(bool fs = false, sf::RenderWindow* wd = NULL, sf::VideoMode vm = {0,0,0});
	~Game();
	GAMESTATE eventHandler(bool isFullscren, bool isSoundEnabled, int level);
	GAMESTATE loadGame();

protected:
	void showText(int op);
	void createBackground();
	void createMusic();
	bool isFullscreen();
	void setFullscreen(bool fs);
	void createGrid();
	void loadTextures();
	void mapParser(std::string mapFile);
	void movePlayer();
	bool saveGame();
	sf::Vector2f getGridPos(sf::Vector2f objPosition); // return grid position from screen position

private:
	bool fullscreen;
	bool enableDrawing;
	std::vector<std::string> levels;
	sf::Text gametext;
	
	bool left = true;
	int counterTime=0;
	int movecounter = 0;
	sf::VideoMode vmode;
	sf::RenderWindow* App;
	sf::Sprite background;
	sf::Font font;
	sf::SoundBuffer buffer;
	sf::Sound bgMusic;		
	sf::Texture texture;
	std::vector<sf::Vector2f> obstaclesPos = std::vector<sf::Vector2f>(5);
//	std::vector<sf::Texture> obstacles = std::vector<sf::Texture>(5);
	sf::Texture obstacle;
	//std::vector<std::vector<sf::Texture>> player = std::vector<std::vector<sf::Texture>>(5,std::vector<sf::Texture>(4));
	std::vector<sf::Texture> house = std::vector<sf::Texture>(2);
	sf::Vector2f housePos;
	//sf::RectangleShape playerShape;
	std::vector<std::vector<sf::RectangleShape>> grid = std::vector<std::vector<sf::RectangleShape>>(6,std::vector<sf::RectangleShape>(7));

	enum TYPETEXT {LOSE,WIN,SAVED};

	enum DIRECTION {STOPPED, UP, RIGHT, DOWN, LEFT};
	int moving;

	Player* playerObj;
};

#endif
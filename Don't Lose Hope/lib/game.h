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
	~Game();
	
	GAMESTATE eventHandler(bool isFullscren, bool isSoundEnabled, int level);
	bool loadGame(std::string mapName);

protected:
	
	void createBackground();
	void createMusic();
	bool isFullscreen();
	void setFullscreen(bool fs);
	void createGrid();
	void loadTextures();
	void loadMessages();

	/*******************************************************
	*  void playEffect(int sound, bool loop)
	*  plays selected sound effect
	*  int sound - sound to be played. Accepted values are listed in enum SOUNDS
	*  bool loop - 	false = sound is played only once
	* 				true = sound played until a buffer::stop() is called
	********************************************************/
	void playEffect(int sound, bool loop = false);

	void changeBG(); // changes background image to create animates background

	/*******************************************************
	*  sf::Vector2i getGridPos(sf::Vector2i objPosition)
	*  returns object grid position
	*  sf::Vector2i objPosition - object screen position
	********************************************************/
	sf::Vector2f getGridPos(sf::Vector2f objPosition);
	
	/*******************************************************
	*  void showMessage(std::string msg)
	*  shows message on screen
	*  std::string msg - message to be shown
	********************************************************/
	void showMessage(std::string str);

	void showText(int op); // shows endgame text when player WINS or LOSES
	void retryGame(); // restarts current level with initial values

	bool mapParser(std::string mapFile); // parse map file and set variables accordingly
	bool saveGame(); // save current game

	

private:
	bool fullscreen;
	bool enableDrawing;
	int bgCounter = 0;
	std::vector<std::string> levels;
	sf::Text gametext;
	int state;
	bool left = true;
	int movecounter = 0;
	sf::VideoMode vmode;
	sf::RenderWindow* App;
	sf::Sprite background;
	sf::Font font;
	sf::Font messageFont;
	std::vector<sf::SoundBuffer> bsoundEffects = std::vector<sf::SoundBuffer>(5);
	sf::Sound soundEffects;
	sf::SoundBuffer buffer;
	sf::Sound bgMusic;		
	std::vector<sf::Texture> bgTextures = std::vector<sf::Texture>(4);
	std::vector<sf::Vector2f> obstaclesPos = std::vector<sf::Vector2f>(MAX_OBSTACLES, sf::Vector2f({-1,-1}));
	sf::Texture obstacle;
	std::vector<sf::Texture> house = std::vector<sf::Texture>(2);
	sf::Vector2f housePos;
	std::vector<std::vector<sf::RectangleShape>> grid = std::vector<std::vector<sf::RectangleShape>>(6,std::vector<sf::RectangleShape>(7));

	sf::Clock ClockSpeed;
	sf::Clock BgSpeed;
	sf::Text message;
	sf::RectangleShape messageBox;

	enum TYPETEXT {IN_GAME,LOSE,WIN,SAVED};

	enum SOUNDS {WATER_SPLASH, HIT_OBSTACLES, SKYING, VADER, YODA};

	enum DIRECTION {STOPPED, UP, RIGHT, DOWN, LEFT};
	int moving;

	Player* playerObj;
};

#endif
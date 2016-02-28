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
	Game(sf::RenderWindow* wd = NULL, sf::VideoMode vm = {0,0,0}, std::vector<std::string> maps = {""});
	~Game();
	
	GAMESTATE eventHandler(bool isSoundEnabled, int level);

	/*******************************************************
	*  bool loadGame(std::string mapName);
	*  Loads a previously saved game
	*  string mapName - Filename to be loaded. Actually, there's only one save in the game.
	********************************************************/
	bool loadGame(std::string mapName);

protected:
	
	void createBackground(); // creates a set of background images to animate the game background

	/*******************************************************
	*  bool createMusic();
	*  Loads a set of sounds, music and sound effects. 
	*  The background music is loaded into an exclusive buffer while the sounds effects swaps the buffer.
	********************************************************/
	void createMusic(); 

	void createGrid(); // Create the grid so the player can orientate himself
	void loadTextures(); //Load all the textures necessaries to the game
	void loadMessages(); //Load the 

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
	//Control Variables
	bool enableDrawing;
	bool left = true;
	int state;
	int moving;
	int movecounter = 0;
	int bgCounter = 0;

	// Text-related variables
	sf::Text message;
	sf::Text gametext;
	sf::Font font;
	sf::Font messageFont;
	sf::RectangleShape messageBox;
	sf::Clock ClockSpeed;
	
	// Clock for Background (so it can change)
	sf::Clock BgSpeed;
	
	// Window variables
	sf::VideoMode vmode;
	sf::RenderWindow* App;
	sf::Sprite background;

	// Sound variables
	sf::Sound soundEffects;
	sf::SoundBuffer buffer;
	sf::Sound bgMusic;		
	std::vector<sf::SoundBuffer> bsoundEffects = std::vector<sf::SoundBuffer>(5);

	// Textures variables
	sf::Texture obstacle;
	std::vector<sf::Texture> bgTextures = std::vector<sf::Texture>(4);
	std::vector<sf::Texture> house = std::vector<sf::Texture>(2);

	// In-game objects variables
	sf::Vector2f housePos;
	std::vector<sf::Vector2f> obstaclesPos = std::vector<sf::Vector2f>(MAX_OBSTACLES, sf::Vector2f({-1,-1}));

	// Grid variables (grid is a joint of rectangles)
	std::vector<std::vector<sf::RectangleShape>> grid = std::vector<std::vector<sf::RectangleShape>>(6,std::vector<sf::RectangleShape>(7));

	// Levels availables
	std::vector<std::string> levels;

	enum TYPETEXT {IN_GAME,LOSE,WIN,SAVED};

	enum SOUNDS {WATER_SPLASH, HIT_OBSTACLES, SKYING, VADER, YODA};

	enum DIRECTION {STOPPED, UP, RIGHT, DOWN, LEFT};
	
	Player* playerObj;
};

#endif
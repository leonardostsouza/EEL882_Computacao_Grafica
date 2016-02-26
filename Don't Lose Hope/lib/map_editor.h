#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include "utilities.h"

class MapEditor
{
public:
	MapEditor(bool fs = false, sf::RenderWindow* wd = NULL, sf::VideoMode vm = {0,0,0});
	~MapEditor();

	GAMESTATE eventHandler(sf::Event event,bool isFullscren, bool isSoundEnabled);

protected:
	void createBackground(); // sets up game background
	void createMusic();	// set um music tracks for map editor
	void createGrid(); // sets up grid to be drawn on screen
	void loadTextures(); // sets up textures
	bool mapWriter(); // saves created map as a file

	bool isFullscreen();
	void setFullscreen(bool fs);
	
	/*******************************************************
	*  void changeMouseBox(int type, sf::Texture* txt)
	*  changes texture in mouse box
	*  int type - type backgorund for mousebox (WHITE or TRANSPARENT)
	*  sf::Texture* txt - texture to be put on mousebox
	********************************************************/
	void changeMouseBox(int type = 0, sf::Texture* txt = NULL);

	/*******************************************************
	*  void delFromGrid()
	*  deletes texture from mouse position on grid
	********************************************************/
	void delFromGrid();

	/*******************************************************
	*  void showMessage(std::string msg, float pos)
	*  shows message on screen
	*  std::string msg - message to be shown
	*  float pos - y position on screen for message to be shown
	********************************************************/
	void showMessage(std::string, float pos);

	void setText(); // load fonts and set properties of text shown on screen

	/*******************************************************
	*  sf::Vector2i getGridPos(sf::Vector2i objPosition)
	*  returns object grid position
	*  sf::Vector2i objPosition - object screen position
	********************************************************/
	sf::Vector2i getGridPos(sf::Vector2i objPosition);

private:
	// control variales
	sf::Clock ClockSpeed;
	bool savestate = false;
	bool fullscreen;
	bool clickEnable;
	bool keyPressEnable;
	int typeChosen=NONE;
	int qttObstacles=0;

	// window properties variables
	sf::VideoMode vmode;
	sf::RenderWindow* App;
	sf::Sprite background;
	sf::SoundBuffer buffer;
	sf::Sound bgMusic;		
	sf::Texture texture;
	sf::Text message;
	sf::Font font;

	// game objects variables
	std::vector<sf::Vector2i> objPosition = std::vector<sf::Vector2i>(MAX_OBSTACLES + 2,sf::Vector2i({-1,-1}));
	std::vector<sf::Texture> sprites = std::vector<sf::Texture>(3);
	std::vector<std::vector<sf::RectangleShape>> grid = std::vector<std::vector<sf::RectangleShape>>(6,std::vector<sf::RectangleShape>(7));
	sf::RectangleShape toolBox;
	sf::RectangleShape* mouseBox; // grid box that follows mouse. Textured with selected object
	std::vector<sf::RectangleShape> tools = std::vector<sf::RectangleShape>(3);
	sf::Vector2i mousePos;
	sf::Vector2i clickCoord;

	std::string savename; //saved map name

	enum SPRITETYPE {NONE, PLAYER, HOUSE, OBSTACLE};
	enum SETCOLOR {TRANSPARENT, WHITE};
};

#endif
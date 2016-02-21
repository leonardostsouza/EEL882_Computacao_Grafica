#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/Event.hpp>
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
	void createBackground();
	void createMusic();
	bool isFullscreen();
	void setFullscreen(bool fs);
	void createGrid();
	void loadTextures();
	bool mapWriter();
	void changeMouseBox(int type = 0, sf::Texture* txt = NULL);
	void delFromGrid();
	void showMessage(std::string, float pos);
	void setText();
	sf::Vector2i getGridPos(sf::Vector2i objPosition); // return grid position from screen position

private:
	sf::Clock ClockSpeed;
	bool savestate = false;
	bool fullscreen;
	bool clickEnable;
	bool keyPressEnable;
	int typeChosen=NONE;
	int qttObstacles=0;
	std::string savename;
	sf::VideoMode vmode;
	sf::RenderWindow* App;
	sf::Sprite background;
	sf::SoundBuffer buffer;
	sf::Sound bgMusic;		
	sf::Texture texture;
	sf::Text message;
	sf::Font font;
	std::vector<sf::Vector2i> objPosition = std::vector<sf::Vector2i>(MAX_OBSTACLES + 2,sf::Vector2i({-1,-1}));
	std::vector<sf::Texture> sprites = std::vector<sf::Texture>(3);
	std::vector<std::vector<sf::RectangleShape>> grid = std::vector<std::vector<sf::RectangleShape>>(6,std::vector<sf::RectangleShape>(7));
	sf::RectangleShape toolBox;
	sf::RectangleShape* mouseBox;
	sf::Vector2i mousePos;
	sf::Vector2i clickCoord;
	std::vector<sf::RectangleShape> tools = std::vector<sf::RectangleShape>(3);

	enum SPRITETYPE {NONE, PLAYER, HOUSE, OBSTACLE};
	enum SETCOLOR {TRANSPARENT, WHITE};
};

#endif
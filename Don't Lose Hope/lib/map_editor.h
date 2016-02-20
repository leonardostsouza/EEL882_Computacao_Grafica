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
	GAMESTATE eventHandler(bool isFullscren, bool isSoundEnabled);

protected:
	void createBackground();
	void createMusic();
	bool isFullscreen();
	void setFullscreen(bool fs);
	void createGrid();
	void loadTextures();
	void mapWriter();
	//sf::Vector2f getGridPos(sf::Vector2f objPosition); // return grid position from screen position

private:
	bool fullscreen;
	sf::VideoMode vmode;
	sf::RenderWindow* App;
	sf::Sprite background;
	sf::SoundBuffer buffer;
	sf::Sound bgMusic;		
	sf::Texture texture;
	std::vector<sf::Vector2f> obstaclesPos = std::vector<sf::Vector2f>(5);
	std::vector<sf::Texture> obstacles = std::vector<sf::Texture>(5);
	std::vector<sf::Texture> house = std::vector<sf::Texture>(2);
	sf::Vector2f housePos;
	std::vector<std::vector<sf::RectangleShape>> grid = std::vector<std::vector<sf::RectangleShape>>(6,std::vector<sf::RectangleShape>(7));
};

#endif
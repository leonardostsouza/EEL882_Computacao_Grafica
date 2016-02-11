#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "utilities.h"

class Game
{
public:
	Game(bool fs = false, sf::RenderWindow* wd = NULL, sf::VideoMode vm = {0,0,0});
	~Game();
	GAMESTATE eventHandler(sf::Event event, bool isFullscren, bool isSoundEnabled);

protected:
	void createBackground();
	void createMusic();
	bool isFullscreen();
	void setFullscreen(bool fs);
	void createGrid();
	void loadTextures();
	void mapParser(std::string mapFile);

private:
	bool fullscreen;
	bool enableDrawing;
	sf::VideoMode vmode;
	sf::RenderWindow* window;
	sf::Sprite background;
	sf::Font font;
	sf::SoundBuffer buffer;
	sf::Sound bgMusic;
	sf::Texture texture;
	std::vector<sf::Text> menu;
	std::vector<sf::Texture> obstacles = std::vector<sf::Texture>(5);
	std::vector<sf::Texture> player = std::vector<sf::Texture>(8);
	sf::Texture house;
	std::vector<std::vector<sf::RectangleShape>> grid = std::vector<std::vector<sf::RectangleShape>>(6,std::vector<sf::RectangleShape>(7));
};

#endif
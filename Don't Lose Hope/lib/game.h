#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include "utilities.h"

class Game
{
public:
	Game(bool fs = false, sf::RenderWindow* wd = NULL, sf::VideoMode vm = {0,0,0});
	~Game();
	GAMESTATE eventHandler(GAMESTATE localstate);

protected:
	void createBackground();
	void createMusic();
	bool isFullscreen();
	void setFullscreen(bool fs);

private:
	bool fullscreen;
	sf::VideoMode vmode;
	sf::RenderWindow* window;
	sf::Sprite background;
	//sf::Text menu[4];
	sf::Font font;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Texture texture;
	std::vector<sf::Text> menu;
};

#endif
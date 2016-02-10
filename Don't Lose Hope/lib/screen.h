#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include "utilities.h"

//using namespace std;

class Screen
{
public:
	Screen(bool fs = false, sf::RenderWindow* wd = NULL, sf::VideoMode vm = {0,0,0});
	~Screen();
	GAMESTATE eventHandler(GAMESTATE localstate);

protected:
	void createBackground();
	void createMenu(GAMESTATE which);
	void createMusic();
	void changeMenuColor(int menuop);
	bool isFullscreen();
	void setFullscreen(bool fs);
	//void play();

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

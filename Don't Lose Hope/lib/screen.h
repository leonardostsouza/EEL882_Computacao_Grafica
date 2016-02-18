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

	bool isFullscreen();
	bool isSoundEnabled();	

protected:
	void createBackground();
	void createMenu(GAMESTATE which);
	void createMusic();
	void changeMenuColor(int menuop);

	void setSoundEnabled(bool se);
	void setFullscreen(bool fs);

private:
	bool fullscreen;
	bool soundEnabled;
	sf::VideoMode vmode;
	sf::RenderWindow* App;
	sf::Sprite background;
	//sf::Text menu[4];
	sf::Font font;
	sf::SoundBuffer buffer;
	sf::Sound bgMusic;
	sf::Texture texture;
	std::vector<sf::Text> menu;
	bool clickEnable;
};

#endif

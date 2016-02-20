#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
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
	int getChosenLevel(){return chosenlevel;}
	std::vector<std::string> passLevels(){return levels;}

protected:
	void createBackground();
	void createMenu(GAMESTATE which, bool change);
	void createMusic();
	void changeMenuColor(int menuop, GAMESTATE localstate);
	void loadLevels();
	void setSoundEnabled(bool se);
	void setFullscreen(bool fs);

private:
	bool fullscreen;
	bool soundEnabled;
	int page=0;
	bool change=true;
	sf::VideoMode vmode;
	sf::RenderWindow* App;
	sf::Sprite background;
	//sf::Text menu[4];
	sf::Font font;
	sf::SoundBuffer buffer;
	sf::Sound bgMusic;
	sf::Texture texture;
	std::vector<sf::Text> menu;
	std::vector<std::string> levels;
	bool clickEnable;
	int chosenlevel = 0;
	sf::Vector2i mousePos;
};

#endif

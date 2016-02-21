#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
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
	void showMessage(std::string str);//, float position);
	std::vector<std::string> passLevels(){return levels;}

protected:
	void createBackground();
	void createMenu(GAMESTATE which, bool change);
	void createMusic();
	void changeMenuColor(int menuop, GAMESTATE localstate);
	void loadLevels();
	void loadFonts();
	void setSoundEnabled(bool se);
	void setFullscreen(bool fs);

private:
	bool levelsloaded = false;
	bool fullscreen;
	bool soundEnabled;
	int page=0;
	bool change=true;
	sf::VideoMode vmode;
	sf::RenderWindow* App;
	sf::Sprite background;
	//sf::Text menu[4];
	sf::Font font[2];
	sf::SoundBuffer buffer;
	sf::Sound bgMusic;
	sf::Texture texture;

	sf::Text message;
	sf::RectangleShape messageBox;

	std::vector<sf::Text> menu;
	std::vector<std::string> levels;
	bool clickEnable;
	int chosenlevel = 0;
	sf::Vector2i mousePos;

	sf::Clock ClockSpeed;
};

#endif

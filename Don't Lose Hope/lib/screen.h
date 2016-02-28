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
	Screen(sf::RenderWindow* wd = NULL, sf::VideoMode vm = {0,0,0});
	~Screen();

	GAMESTATE eventHandler(GAMESTATE localstate);

	bool isSoundEnabled();	

	int getChosenLevel(){return chosenlevel;}	// returns level chosen by player
	void showMessage(std::string str);	// shows message on screen

	std::vector<std::string> passLevels(){return levels;} // returns a vector with the names of maps available for playing

protected:
	void createBackground(); // sets background image for main menu
	
	/*******************************************************
	*  void createMenu(GAMESTATE which, bool change)
	*  sets menu options to be shown in screen
	*  GAMESTATE which - What kind of menu needs to be shown (MAIN, LEVEL SELECTION, OPTIONS, etc)
	*  bool change - true = changes the menu already being displayed, loading new options
	*			false = maintain same menu being displayed
	********************************************************/
	void createMenu(GAMESTATE which, bool change);

	void createMusic();	// sets music played on main menu

	/*******************************************************
	*  void changeMenuColor(int menuop, GAMESTATE localstate)
	*  changes the color of selected menu option. Called on mouse hover
	*  GAMESTATE localstae - current state of menu screen (MAIN MENU, OPTIONS MENU or MAP SELECTION)
	*  int menuop - which menu option to change color
	********************************************************/
	void changeMenuColor(int menuop, GAMESTATE localstate); 

	void loadLevels(); // loads the names of the levels available for playing
	void loadFonts();	// loads fonts used in menus

	void setSoundEnabled(bool se);

private:
	// window variables
	bool levelsloaded = false;
	bool soundEnabled;

	sf::VideoMode vmode;
	sf::RenderWindow* App;
	sf::Sprite background;
	sf::Font font[2];
	sf::SoundBuffer buffer;
	sf::Sound bgMusic;
	sf::Texture texture;
	sf::Text message;
	sf::RectangleShape messageBox;
	std::vector<sf::Text> menu;
	std::vector<std::string> levels;

	// control variables
	bool clickEnable;
	int page = 0; // current page in level selection menu
	bool change = true;
	int chosenlevel = 0;
	sf::Vector2i mousePos;
	sf::Clock ClockSpeed;
};

#endif

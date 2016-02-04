#ifndef SCREEN_H
#define SCREEN_H
#ifndef DEFAULT_WINDOW_WIDTH
#define DEFAULT_WINDOW_WIDTH 640
#ifndef DEFAULT_WINDOW_HEIGHT
#define DEFAULT_WINDOW_HEIGHT 480

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

//using namespace std;

class Screen
{
public:
	Screen(bool fs = false);
	~Screen();
	void play();

protected:
	void createBackground();
	void createMenu();
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
#endif
#endif

#include "lib/game.h"

Game::Game(bool fs, sf::RenderWindow* wd, sf::VideoMode vm) : window (wd), fullscreen (fs) , vmode (vm) 
{

	// Create the background
	createBackground();


	// Creating the music
	createMusic();

	//play();
}


Game::~Game()
{
}

void Game::createBackground() {
	std::string fileName;
	fileName = "resources/images/game_background.png";

	if (!texture.loadFromFile(fileName)) {
		std::cerr << "Error loading background" << std::endl;
	}
	else {
		texture.setSmooth(true);
		background.setTexture(texture);
		background.scale((float)vmode.width / (float)texture.getSize().x, (float)vmode.height / (float)texture.getSize().y);
	}
}

void Game::createMusic() {

	if (!buffer.loadFromFile("resources/sounds/game.ogg")){
		std::cerr << "Error loading sound" << std::endl;
	}
	else {
		sound.setBuffer(buffer);
		sound.setLoop(true);
		sound.setVolume(70);
		sound.play();
	}
}

bool Game::isFullscreen()
{
	return this->fullscreen;
}

void Game::setFullscreen(bool fs)
{
	this->fullscreen = fs;
}

GAMESTATE Game::eventHandler(GAMESTATE localstate) {
	/*while ((*window).isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while ((*window).pollEvent(event))
		{
			// close window event
			if (event.type == sf::Event::Closed)
				(*window).close();
		}*/

		
	(*window).clear();
	(*window).draw(background);
	GAMESTATE nextState = PLAYING;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		nextState = MAINMENU;
	}
	

	(*window).display();

	return nextState;
}
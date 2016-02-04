#include "lib/Screen.h"

Screen::Screen(bool fs)
{
	//set VideoMode
	this->setFullscreen(fs);
	if (!isFullscreen())
	{
		vmode.width = DEFAULT_WINDOW_WIDTH;
		vmode.height = DEFAULT_WINDOW_HEIGHT;
		vmode.bitsPerPixel = sf::VideoMode::getDesktopMode().bitsPerPixel;
	}
	else
	{
		vmode = sf::VideoMode::getFullscreenModes()[0];
	}

	// Create the main window
	window = new sf::RenderWindow(sf::VideoMode(vmode.width, vmode.height, vmode.bitsPerPixel), "Don't Lose Hope");

	// Create the background
	createBackground();

	// Drawing the menu
	createMenu();

	// Creating the music
	createMusic();

	play();
}


Screen::~Screen()
{
}

void Screen::play() {
	
	while ((*window).isOpen())
	{

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while ((*window).pollEvent(event))
		{
			// close window event
			if (event.type == sf::Event::Closed)
				(*window).close();
		}

		(*window).clear();
		(*window).draw(background);
		// O compilador tava reclamando desse for. op tem que ser do tipo drawable, não text
		/*for (vector<sf::Text>::iterator op = menu.begin(); op != menu.end(); ++op) {
			(*window).draw(op);
		}*/
		(*window).display();

	}


}

void Screen::createBackground() {
	std::string fileName;
	if (this->isFullscreen())
	{
		fileName = "resources/images/menu_background_fullscreen.png";
	}
	else
	{
		fileName = "resources/images/menu_background_window.png";
	}

	if (!texture.loadFromFile(fileName)) {
		std::cerr << "Error loading background" << std::endl;
	}
	else {
		texture.setSmooth(true);
		background.setTexture(texture);
		background.scale((float)vmode.width / (float)texture.getSize().x, (float)vmode.height / (float)texture.getSize().y);
	}
}

void Screen :: createMenu() {
	//set menu size
	menu.resize(4);

	if (!font.loadFromFile("resources/fonts/default_font.ttf")) {
		std::cerr << "Error loading fonts" << std::endl;
	}
	else {
		menu[0].setCharacterSize(40);
		menu[0].setString("New Game");
		menu[0].setPosition({ (float)((vmode.width / 3) + 20),(float)(vmode.height / 3 + 30) });
		menu[0].setFont(font);
		menu[0].setColor(sf::Color(0, 0, 0));
		menu[1].setCharacterSize(40);
		menu[1].setString("Continue");
		menu[1].setPosition({ (float)((vmode.width / 3) + 20),(float)(vmode.height / 3 + 80) });
		menu[1].setFont(font);
		menu[1].setColor(sf::Color(0, 0, 0));
		menu[2].setCharacterSize(40);
		menu[2].setString("Options");
		menu[2].setPosition({ (float)((vmode.width / 3) + 20),(float)(vmode.height / 3 + 130) });
		menu[2].setFont(font);
		menu[2].setColor(sf::Color(0, 0, 0));
		menu[3].setCharacterSize(40);
		menu[3].setString("Exit");
		menu[3].setPosition({ (float)((vmode.width / 3) + 20),(float)(vmode.height / 3 + 180) });
		menu[3].setFont(font);
		menu[3].setColor(sf::Color(0, 0, 0));
	}
}

void Screen::createMusic() {

	if (!buffer.loadFromFile("resources/sounds/main_menu.wav")){
		std::cerr << "Error loading sound" << std::endl;
	}
	else {
		sound.setBuffer(buffer);
		sound.setLoop(true);
		sound.setVolume(70);
		sound.play();
	}
}

bool Screen::isFullscreen()
{
	return this->fullscreen;
}

void Screen::setFullscreen(bool fs)
{
	this->fullscreen = fs;
}
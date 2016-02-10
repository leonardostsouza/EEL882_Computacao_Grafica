#include "lib/screen.h"

Screen::Screen(bool fs, sf::RenderWindow* wd, sf::VideoMode vm) : window (wd), fullscreen (fs) , vmode (vm) 
{

	// Create the background
	createBackground();

	// Drawing the menu
	//createMenu(MAINMENU);

	// Creating the music
	createMusic();

	//play();
}


Screen::~Screen()
{
}

void Screen::changeMenuColor(int op){
	for (int i = 0; i < menu.size(); i++) {
		if (op == i){
			menu[i].setColor(sf::Color(255, 255, 0));
		}else{
			menu[i].setColor(sf::Color(0, 0, 0));
		}
	}
}

GAMESTATE Screen::eventHandler(GAMESTATE localstate) {
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
		createMenu(localstate);
		GAMESTATE nextState;

		//check mouse position on main screen
		sf::Vector2i mousePos=sf::Mouse::getPosition(*window);
		sf::RectangleShape highlight;
		highlight.setSize(sf::Vector2f((vmode.width / 3), (vmode.height / 12)));
		highlight.setFillColor(sf::Color(0, 102, 204, 60));

		if (localstate == MAINMENU){
			nextState = MAINMENU;
			// Highlight menu options
			
			if((mousePos.x >= (vmode.width / 3)) && (mousePos.x <= 2*(vmode.width / 3)))
			{
				// NEW GAME
				if ((mousePos.y >= ((float)((vmode.height / 3) + (vmode.height / 12))))
					&& (mousePos.y <= ((float)((vmode.height / 3) + (2*vmode.height / 12)))))
				{
					changeMenuColor(0);
					highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (vmode.height / 12) + (vmode.height / 64)));
					window->draw(highlight);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						nextState = PLAYING;
					}
				}			
				// CONTINUE
				else if ((mousePos.y >= ((float)((vmode.height / 3) + (2*vmode.height / 12))))
					&& (mousePos.y <= ((float)((vmode.height / 3) + (3*vmode.height / 12)))))
				{
					changeMenuColor(1);
					highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (2*vmode.height / 12) + (vmode.height / 64)));
					window->draw(highlight);
				}
				// OPTIONS
				else if ((mousePos.y >= ((float)((vmode.height / 3) + (3*vmode.height / 12))))
					&& (mousePos.y <= ((float)((vmode.height / 3) + (4*vmode.height / 12)))))
				{
					changeMenuColor(2);
					highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (3*vmode.height / 12) + (vmode.height / 64)));
					window->draw(highlight);
					
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						nextState = OPTIONSMENU;
					}
				}
				// EXIT
				else if ((mousePos.y >= ((float)((vmode.height / 3) + (4*vmode.height / 12))))
					&& (mousePos.y <= ((float)((vmode.height / 3) + (5*vmode.height / 12)))))
				{
					changeMenuColor(3);
					highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (4*vmode.height / 12) + (vmode.height / 64)));
					window->draw(highlight);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						nextState = CLOSE;
					}
				}else{
					changeMenuColor(-1);
				}
			}else{
				changeMenuColor(-1);
			}

			///Add a mouseclick handler. Whenever he changes the screen, changes the state to the desired one :D
		
		}else{
			nextState = OPTIONSMENU;
			if((mousePos.x >= (vmode.width / 3)) && (mousePos.x <= 2*(vmode.width / 3)))
			{
				// SOUND
				if ((mousePos.y >= ((float)((vmode.height / 3) + (vmode.height / 12))))
					&& (mousePos.y <= ((float)((vmode.height / 3) + (2*vmode.height / 12)))))
				{
					changeMenuColor(0);
					highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (vmode.height / 12) + (vmode.height / 64)));
					window->draw(highlight);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						std::cout << sound.getStatus() << std::endl;
						if (sound.getStatus() == sf::Sound::Playing){
							sound.stop();
						}else{
							sound.play();
						}
					}
				}

				// GO BACK
				if ((mousePos.y >= ((float)((vmode.height / 3) + (2*vmode.height / 12))))
					&& (mousePos.y <= ((float)((vmode.height / 3) + (3*vmode.height / 12)))))
				{
					changeMenuColor(1);
					highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (2*vmode.height / 12) + (vmode.height / 64)));
					window->draw(highlight);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						nextState = MAINMENU;
					}
				}
			}			
		}

		for (std::vector<sf::Text>::iterator op = menu.begin(); op != menu.end(); op++) {
				(*window).draw(*op);
			}
		(*window).display();

		return nextState;
	}


void Screen::createBackground() {
	std::string fileName;

	if (fullscreen){
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

void Screen::createMenu(GAMESTATE which) {

	if (!font.loadFromFile("resources/fonts/default_font.ttf")) {
		std::cerr << "Error loading fonts" << std::endl;
		return;
	}
	if (which == MAINMENU){
		//set menu size
		menu.clear();
		menu.resize(4);

		menu[0].setCharacterSize(vmode.height / 12);
		menu[0].setString("New Game");
		menu[0].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)((vmode.height / 3) + (vmode.height / 12)) });
		menu[0].setFont(font);
		menu[0].setColor(sf::Color(0, 0, 0));
		menu[1].setCharacterSize(vmode.height / 12);
		menu[1].setString("Continue");
		menu[1].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)(vmode.height / 3 + 2*(vmode.height / 12)) });
		menu[1].setFont(font);
		menu[1].setColor(sf::Color(0, 0, 0));
		menu[2].setCharacterSize(vmode.height / 12);
		menu[2].setString("Options");
		menu[2].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)(vmode.height / 3 + 3*(vmode.height / 12)) });
		menu[2].setFont(font);
		menu[2].setColor(sf::Color(0, 0, 0));
		menu[3].setCharacterSize(vmode.height / 12);
		menu[3].setString("Exit");
		menu[3].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)(vmode.height / 3 + 4*(vmode.height / 12)) });
		menu[3].setFont(font);
		menu[3].setColor(sf::Color(0, 0, 0));
	}else{
		//set menu size
		menu.clear();
		menu.resize(2);	
		menu[0].setCharacterSize(vmode.height / 12);
		if (sound.getStatus() == sf::Sound::Playing){
			menu[0].setString("Sound: Yes");	
		}else{
			menu[0].setString("Sound: No");	
		}
		menu[0].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)((vmode.height / 3) + (vmode.height / 12)) });
		menu[0].setFont(font);
		menu[0].setColor(sf::Color(0, 0, 0));
		menu[1].setCharacterSize(vmode.height / 12);
		menu[1].setString("Go Back");
		menu[1].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)(vmode.height / 3 + 2*(vmode.height / 12)) });
		menu[1].setFont(font);
		menu[1].setColor(sf::Color(0, 0, 0));
	}
}

void Screen::createMusic() {

	if (!buffer.loadFromFile("resources/sounds/main_menu.ogg")){
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
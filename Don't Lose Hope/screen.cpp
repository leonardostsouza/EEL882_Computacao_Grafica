#include "lib/screen.h"

Screen::Screen(bool fs, sf::RenderWindow* wd, sf::VideoMode vm) : App (wd), fullscreen (fs) , vmode (vm) 
{

// Create the background
	createBackground();

// Loading levels
	loadLevels();

// Creating background music
	createMusic();

//play();
}


Screen::~Screen()
{
}

void Screen::changeMenuColor(int op, GAMESTATE localstate){
	for (int i = 0; i < menu.size(); i++) {
		if (op == i){
			menu[i].setColor(sf::Color(255, 0, 0));
		}
		else
		{
			menu[i].setColor(sf::Color(0, 0, 0));
		}
	}
	if (localstate == CHOOSING){
		//BACK
		if (page == 0){
			menu[4].setColor(sf::Color(0, 0, 0,100));
		}
		//NEXT
		if (levels.size() < (page+1)*4){
			menu[5].setColor(sf::Color(0, 0, 0,100));	
		}
	}
}

void Screen::loadLevels(){
	levels.clear();
	levels.resize(20);
	struct dirent *de;
	DIR *dir = opendir("resources/maps");
	if (!dir){
		std::cout << "Unable to open resources/map. Was it deleted?" << std::endl;
		return;
	}
	int i=0;
	while(de = readdir(dir)){
		if (strcmp(de->d_name,".") and strcmp(de->d_name,"..") and (std::string(de->d_name).find("~",5)==std::string::npos)){
			levels[i] = de->d_name;
			i++;
		}
	}
	levels.resize(i);
	levels.shrink_to_fit();
	std::sort(levels.begin(),levels.end());
	closedir(dir);
	levelsloaded = true;
}

GAMESTATE Screen::eventHandler(GAMESTATE localstate) {
	App->clear();
	App->draw(background);
	createMenu(localstate,change);
	change = false;
	GAMESTATE nextState;

	if (isSoundEnabled()){
		if (bgMusic.getStatus() != sf::SoundSource::Status::Playing)
		{
			bgMusic.play();
		}	
	}

	//check mouse position on main screen
	mousePos=sf::Mouse::getPosition(*App);
	sf::RectangleShape highlight;
	highlight.setSize(sf::Vector2f((vmode.width / 3.1), (vmode.height / 12)));
	highlight.setFillColor(sf::Color(0, 102, 204, 90));

	// MAIN MENU SCREEN
	if (localstate == MAINMENU)
	{
		nextState = MAINMENU;

		// Menu Options mousover and clicking Handling
		//std::cout << "X: " << vmode.width << " |Y: " << vmode.height << std::endl;
		if((mousePos.x >= (vmode.width / 3)) && (mousePos.x <= 2*(vmode.width / 3)))
		{
			// NEW GAME
			if ((mousePos.y >= ((float)((vmode.height / 3) + (vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (2*vmode.height / 12)))))
			{
				changeMenuColor(0,localstate);
				highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (vmode.height / 12) + (vmode.height / 64)));
				App->draw(highlight);

				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
				}

				if (clickEnable)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						change = true;
						clickEnable = false;
						nextState = CHOOSING;
						levelsloaded = false;
						#ifdef DEBUG	                  
						std::cout << "DEBUG === GAMESTATE = \"CHOOSING\"" << std::endl;            
	                    #endif
					}						
				}

			}			
			// CONTINUE
			else if ((mousePos.y >= ((float)((vmode.height / 3) + (2*vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (3*vmode.height / 12)))))
			{
				changeMenuColor(1,localstate);
				highlight.setSize(sf::Vector2f((vmode.width / 3.5), (vmode.height / 12)));
				highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (2*vmode.height / 12) + (vmode.height / 64)));
				App->draw(highlight);

				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
				}

				if (clickEnable)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						change = true;
						clickEnable = false;
						nextState = CONTINUE;
						#ifdef DEBUG	                  
						std::cout << "DEBUG === GAMESTATE = \"CONTINUE\"" << std::endl;            
	                    #endif
					}						
				}
			}
			// MAP EDITOR
			else if ((mousePos.y >= ((float)((vmode.height / 3) + (3*vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (4*vmode.height / 12)))))
			{
				changeMenuColor(2,localstate);
				highlight.setSize(sf::Vector2f((vmode.width / 2.1), (vmode.height / 12)));
				highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (3*vmode.height / 12) + (vmode.height / 64)));
				App->draw(highlight);

				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
				}

				if (clickEnable){
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						clickEnable = false;
						nextState = CREATING;
						#ifdef DEBUG	                  
						std::cout << "DEBUG === GAMESTATE = \"CHOOSING\"" << std::endl;                   
	                    #endif 
					}
				}
			}
			// OPTIONS
			else if ((mousePos.y >= ((float)((vmode.height / 3) + (4*vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (5*vmode.height / 12)))))
			{
				changeMenuColor(3,localstate);
				highlight.setSize(sf::Vector2f((vmode.width / 3.8), (vmode.height / 12)));
				highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (4*vmode.height / 12) + (vmode.height / 64)));
				App->draw(highlight);

				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
				}

				if (clickEnable){
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						clickEnable = false;
						nextState = OPTIONSMENU;
						change = true;
						#ifdef DEBUG	                  
						std::cout << "DEBUG === GAMESTATE = \"OPTIONSMENU\"" << std::endl;                   
	                    #endif 
					}
				}
			}
			// EXIT
			else if ((mousePos.y >= ((float)((vmode.height / 3) + (5*vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (6*vmode.height / 12)))))
			{
				changeMenuColor(4,localstate);
				highlight.setSize(sf::Vector2f((vmode.width / 5.8), (vmode.height / 12)));
				highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (5*vmode.height / 12) + (vmode.height / 64)));
				App->draw(highlight);

				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
				}

				if (clickEnable)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						clickEnable = false;
						nextState = CLOSE;
						#ifdef DEBUG	                  
						std::cout << "DEBUG === GAMESTATE = \"CLOSE\"" << std::endl;            
	                    #endif 
					}
				}
			}
			else
			{
				changeMenuColor(-1,localstate);
				clickEnable = false;
			}
		}else{
			changeMenuColor(-1,localstate);
			clickEnable = false;
		}
		///Add a mouseclick handler. Whenever he changes the screen, changes the state to the desired one :D
	}
	else if (localstate == CHOOSING){
		nextState = CHOOSING;
		if (!levelsloaded){
			loadLevels();
		}
		// Menu Options mousover and clicking Handling
		//std::cout << "X: " << vmode.width << " |Y: " << vmode.height << std::endl;
		if((mousePos.x >= (vmode.width / 3)) && (mousePos.x <= 2*(vmode.width / 3)))
		{
			// FIRST PHASE
			if ((mousePos.y >= ((float)((vmode.height / 3) + (vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (2*vmode.height / 12)))))
			{
				if (page*4 < levels.size()){
					changeMenuColor(0,localstate);
					highlight.setSize(sf::Vector2f((vmode.width / 4.5), (vmode.height / 12)));
					highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (vmode.height / 12) + (vmode.height / 64)));
					App->draw(highlight);

					if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						clickEnable = true;
					}

					if (clickEnable)
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							chosenlevel = page*4;
							clickEnable = false;
							change = true;
							nextState = PLAYING;
						#ifdef DEBUG	                  
							std::cout << "DEBUG === GAMESTATE = \"CHOOSING\"" << std::endl;            
	                    #endif
						}						
					}
				}else{
					changeMenuColor(-1,localstate);
					if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						clickEnable = true;
					}
				}

			}			
			// Second phase
			else if ((mousePos.y >= ((float)((vmode.height / 3) + (2*vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (3*vmode.height / 12)))))
			{
				if (((page*4)+1) < levels.size()){
					changeMenuColor(1,localstate);
					highlight.setSize(sf::Vector2f((vmode.width / 4.5), (vmode.height / 12)));
					highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (2*vmode.height / 12) + (vmode.height / 64)));
					App->draw(highlight);

					if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						clickEnable = true;
					}

					if (clickEnable)
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							chosenlevel = (page*4) + 1;
							clickEnable = false;
							change = true;
							nextState = PLAYING;
						#ifdef DEBUG	                  
							std::cout << "DEBUG === GAMESTATE = \"PLAYING\"" << std::endl;            
	                    #endif
						}						
					}
				}else{
					changeMenuColor(-1,localstate);
					if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						clickEnable = true;
					}
				}
			}
			// Third Phase
			else if ((mousePos.y >= ((float)((vmode.height / 3) + (3*vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (4*vmode.height / 12)))))
			{
				if (((page*4)+2) < levels.size()){
					changeMenuColor(2,localstate);
					highlight.setSize(sf::Vector2f((vmode.width / 4.5), (vmode.height / 12)));
					highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (3*vmode.height / 12) + (vmode.height / 64)));
					App->draw(highlight);

					if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						clickEnable = true;
					}

					if (clickEnable){
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							chosenlevel = (page*4) + 2;
							clickEnable = false;
							change = true;
							nextState = PLAYING;
						#ifdef DEBUG	                  
							std::cout << "DEBUG === GAMESTATE = \"CHOOSING\"" << std::endl;                   
	                    #endif 
						}
					}
				}else{
					changeMenuColor(-1,localstate);
					if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						clickEnable = true;
					}
				}
			}
			// Forth Phase
			else if ((mousePos.y >= ((float)((vmode.height / 3) + (4*vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (5*vmode.height / 12)))))
			{
				if (((page*4)+3) < levels.size()){
					changeMenuColor(3,localstate);
					highlight.setSize(sf::Vector2f((vmode.width / 4.5), (vmode.height / 12)));
					highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (4*vmode.height / 12) + (vmode.height / 64)));
					App->draw(highlight);

					if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						clickEnable = true;
					}

					if (clickEnable){
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							chosenlevel = (page*4) + 3;
							clickEnable = false;
							change = true;
							nextState = PLAYING;
						#ifdef DEBUG	                  
							std::cout << "DEBUG === GAMESTATE = \"PLAYING\"" << std::endl;                   
	                    #endif 
						}
					}
				}else{
					changeMenuColor(-1,localstate);
					if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						clickEnable = true;
					}
				}
			}
			// NEXT
			else if ((mousePos.y >= ((float)((vmode.height / 3) + (5*vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (6*vmode.height / 12)))))
			{
				if ((mousePos.x >= (float)((vmode.width / 3) + (vmode.width / 5))) && (mousePos.x >= (float)((vmode.width / 3) + (vmode.width / 32)))){
					if (levels.size() > (page+1)*4){
						changeMenuColor(5,localstate);
						highlight.setSize(sf::Vector2f((vmode.width / 6), (vmode.height / 12)));
						highlight.setPosition((vmode.width / 3) + (vmode.width / 5.5), ((vmode.height / 3) + (5*vmode.height / 12) + (vmode.height / 64)));
						App->draw(highlight);

						if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
							clickEnable = true;
						}

						if (clickEnable){
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							{
								clickEnable = false;
								change = true;
								page++;
						#ifdef DEBUG	                  
								std::cout << "DEBUG === GAMESTATE = \"CHOOSING\"" << std::endl;                   
	                    #endif 
							}
						}
					}else{
						changeMenuColor(-1,localstate);
						if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
							clickEnable = true;
						}
					}
				}
			// BACK
				else if ((mousePos.x >= (float)((vmode.width / 3) + (vmode.width / 32))) && (mousePos.x >= (float)((vmode.width / 3) + (vmode.width / 48))))
				{
					if (page > 0){
						changeMenuColor(4,localstate);
						highlight.setSize(sf::Vector2f((vmode.width / 5.5), (vmode.height / 12)));
						highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (5*vmode.height / 12) + (vmode.height / 64)));
						App->draw(highlight);

						if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
							clickEnable = true;
						}

						if (clickEnable){
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
							{
								clickEnable = false;
								change = true;
								page--;
						#ifdef DEBUG	                  
								std::cout << "DEBUG === GAMESTATE = \"CHOOSING\"" << std::endl;                   
	                    #endif 
							}
						}
					}else{
						changeMenuColor(-1,localstate);
						if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
							clickEnable = true;
						}
					}
				}
			}
			// MAINMENU BUTTON
			else if ((mousePos.y >= ((float)((vmode.height / 3) + (6*vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (7*vmode.height / 12)))))
			{
				changeMenuColor(6,localstate);
				highlight.setSize(sf::Vector2f((vmode.width / 2.9), (vmode.height / 12)));
				highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (6*vmode.height / 12) + (vmode.height / 64)));
				App->draw(highlight);

				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
				}

				if (clickEnable)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						clickEnable = false;
						change = true;
						nextState = MAINMENU;
						#ifdef DEBUG	                  
						std::cout << "DEBUG === GAMESTATE = \"MAINMENU\"" << std::endl;            
	                    #endif 
					}
				}
			}
			else
			{
				changeMenuColor(-1,localstate);
				clickEnable = false;
			}
		}else{
			changeMenuColor(-1,localstate);
			clickEnable = false;
		}
	}
	//OPTIONS MENU SCREEN
	else if (localstate == OPTIONSMENU)
	{
		nextState = OPTIONSMENU;
		if((mousePos.x >= (vmode.width / 3)) && (mousePos.x <= 2*(vmode.width / 3)))
		{
			// SOUND
			if ((mousePos.y >= ((float)((vmode.height / 3) + (vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (2*vmode.height / 12)))))
			{
				changeMenuColor(0,localstate);
				highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (vmode.height / 12) + (vmode.height / 64)));
				App->draw(highlight);

				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
				}

				if (clickEnable)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						clickEnable = false;		
						change = true;				
						if (bgMusic.getStatus() == sf::SoundSource::Status::Playing)
						{			
							setSoundEnabled(false);			
							bgMusic.stop();

							#ifdef DEBUG
							std::cout << "DEBUG === SOUND OFF " << std::endl;
                    		#endif
						}
						else
						{
							setSoundEnabled(true);	
							bgMusic.play();

							#ifdef DEBUG
							std::cout << "DEBUG === SOUND ON " << std::endl;
                    		#endif
						}
					}
				}
			}
			// GO BACK TO MAIN MENU
			else if ((mousePos.y >= ((float)((vmode.height / 3) + (2*vmode.height / 12))))
				&& (mousePos.y <= ((float)((vmode.height / 3) + (3*vmode.height / 12)))))
			{
				changeMenuColor(1,localstate);
				highlight.setPosition((vmode.width / 3), ((vmode.height / 3) + (2*vmode.height / 12) + (vmode.height / 64)));
				App->draw(highlight);

				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
				}

				if (clickEnable)
				{											
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						clickEnable = false;
						change = true;
						nextState = MAINMENU;
						#ifdef DEBUG	                  
						std::cout << "DEBUG === GAMESTATE = \"MAINMENU\"" << std::endl;            
	                    #endif 
					}
				}
			}
			else
			{
				clickEnable = false;
			}
		}
		else{			
			clickEnable = false;
		}			
	}

//		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
//			nextState = CLOSE;
//		}

	for (std::vector<sf::Text>::iterator op = menu.begin(); op != menu.end(); op++) {
		App->draw(*op);
	}
	App->display();

	if (nextState == CREATING || nextState == PLAYING){
		bgMusic.stop();
	}

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

void Screen::createMenu(GAMESTATE which, bool change) {

	if (change == true){
		if (!font.loadFromFile("resources/fonts/default_font.ttf")) {
			std::cerr << "Error loading fonts" << std::endl;
			return;
		}
		if (which == MAINMENU){
	//set menu size
			menu.clear();
			menu.resize(5);

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
			menu[2].setString("Map Editor");
			menu[2].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)(vmode.height / 3 + 3*(vmode.height / 12)) });
			menu[2].setFont(font);
			menu[2].setColor(sf::Color(0, 0, 0));
			menu[3].setCharacterSize(vmode.height / 12);
			menu[3].setString("Options");
			menu[3].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)(vmode.height / 3 + 4*(vmode.height / 12)) });
			menu[3].setFont(font);
			menu[3].setColor(sf::Color(0, 0, 0));
			menu[4].setCharacterSize(vmode.height / 12);
			menu[4].setString("Exit");
			menu[4].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)(vmode.height / 3 + 5*(vmode.height / 12)) });
			menu[4].setFont(font);
			menu[4].setColor(sf::Color(0, 0, 0));
		}else if (which == CHOOSING) {
			menu.clear();
			menu.resize(7);
			int index;
			int range = page*4;
			if(levels.size() > range+4){
				for(int i=range;i<range+4;i++){
					index = i%4;
					menu[index].setCharacterSize(vmode.height / 12);
					menu[index].setString(levels[i]);
					menu[index].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)((vmode.height / 3) + (index+1)*(vmode.height / 12)) });
					menu[index].setFont(font);
					menu[index].setColor(sf::Color(0, 0, 0));
				}
			}else{
				for(int i=range;i<levels.size();i++){
					index = i%4;
					menu[index].setCharacterSize(vmode.height / 12);
					menu[index].setString(levels[i]);
					menu[index].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)((vmode.height / 3) + (index+1)*(vmode.height / 12)) });
					menu[index].setFont(font);
					menu[index].setColor(sf::Color(0, 0, 0));
				}
			}
			menu[4].setCharacterSize(vmode.height / 12);
			menu[4].setString("Back");
			menu[4].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)(vmode.height / 3 + 5*(vmode.height / 12)) });
			menu[4].setFont(font);
			if (page > 0){
				menu[4].setColor(sf::Color(0, 0, 0));	
			}else{
				menu[4].setColor(sf::Color(255, 0, 0, 100));
			}

			menu[5].setCharacterSize(vmode.height / 12);
			menu[5].setString("Next");
			menu[5].setPosition({ (float)((vmode.width / 3) + (vmode.width / 5)),(float)(vmode.height / 3 + 5*(vmode.height / 12)) });
			menu[5].setFont(font);
			if (levels.size() > (page+1)*4){
				menu[5].setColor(sf::Color(0, 0, 0));
			}else{
				menu[5].setColor(sf::Color(0, 0, 0, 100));		
			}
			menu[6].setCharacterSize(vmode.height / 12);
			menu[6].setString("Main Menu");
			menu[6].setPosition({ (float)((vmode.width / 3) + (vmode.width / 32)),(float)(vmode.height / 3 + 6*(vmode.height / 12)) });
			menu[6].setFont(font);
			menu[6].setColor(sf::Color(0, 0, 0));
	//menu.resize();
		}else if (which == OPTIONSMENU){
	//set menu size
			menu.clear();
			menu.resize(2);	
			menu[0].setCharacterSize(vmode.height / 12);
			if (bgMusic.getStatus() == sf::SoundSource::Status::Playing)
			{
				menu[0].setString("Sound: Yes");	
			}
			else
			{
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
}

void Screen::createMusic() {
	if (!buffer.loadFromFile("resources/sounds/main_menu.ogg"))
	{
		std::cerr << "Error loading background music" << std::endl;
	}
	else 
	{
		bgMusic.setBuffer(buffer);
		bgMusic.setLoop(true);
		bgMusic.setVolume(70);
		bgMusic.play();
	}
}

bool Screen::isFullscreen()
{
	return fullscreen;
}

void Screen::setFullscreen(bool fs)
{
	fullscreen = fs;
}

bool Screen::isSoundEnabled()
{
	return soundEnabled;
}

void Screen::setSoundEnabled(bool se)
{
	soundEnabled = se;
}
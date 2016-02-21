#include "lib/game.h"

Game::Game(bool fs, sf::RenderWindow* wd, sf::VideoMode vm, std::vector<std::string> maps) : App (wd), fullscreen (fs) , vmode (vm) , levels(maps)
//Game::Game(bool fs, sf::RenderWindow* wd, sf::VideoMode vm) : App (wd), fullscreen (fs) , vmode (vm) 
{
	//create player
	playerObj = new Player();

	// Create the background
	createBackground();

	//Create the grid
	createGrid();

	//Load the player
	loadTextures();

	// Creating the music
	createMusic();	
}


Game::~Game()
{
}

bool Game::saveGame(){
	std::ofstream map("resources/saves/savegame");
	if(map.is_open()){
		sf::Vector2i obPos;
		sf::Vector2i playerPos = (sf::Vector2i)getGridPos(playerObj->position);
		sf::Vector2i houseP = (sf::Vector2i)getGridPos(housePos);
		map << "#Map Created by Don't Lose Hope Editor" << std::endl;
		map << "#|PLAYER_POSITION|HOUSE_POSITION|OBSTACLE1|OBSTACLE2|OBSTACLE3|OBSTACLE4|OBSTACLE5|" << std::endl;
		map << "|" << playerPos.x << "," << playerPos.y;
		map << "|" << houseP.x << "," << houseP.y;
		for (int i = 0; i < obstaclesPos.size(); i++){
			obPos = (sf::Vector2i)getGridPos(obstaclesPos[i]);
			map << "|" << obPos.x << "," << obPos.y;
		}
		map << "|" << std::endl;
	map.close();
	return true;
	}else{
		return false;
	}
}

bool Game::loadGame(std::string mapName = "resources/saves/savegame"){
	enableDrawing = false;
	return mapParser(mapName);
}

void Game::loadTextures()
{
	// Obstacles textures
	if(!obstacle.loadFromFile("resources/images/sprites.png", sf::IntRect(531,545,33,34)))
		std::cerr << "Error loading sprites" << std::endl;

	// House Textures
	if(!house[0].loadFromFile("resources/images/sprites.png", sf::IntRect(152,24,78,67)))
		std::cerr << "Error loading sprites" << std::endl;

	if(!house[1].loadFromFile("resources/images/sprites.png", sf::IntRect(258,26,78,67)))
		std::cerr << "Error loading sprites" << std::endl;

	//Player Textures
	playerObj->loadTextures();
	enableDrawing = true;
}

void Game::createBackground() 
{
	std::string fileName;
	fileName = "resources/images/game_background.png";

	if (!texture.loadFromFile(fileName)) {
		std::cerr << "Error loading background" << std::endl;
	}
	else {
		texture.setSmooth(true);
		background.setTexture(texture);
		background.scale(((float)vmode.width*1.2) / (float)texture.getSize().x, (float)vmode.height / (float)texture.getSize().y);
		background.setPosition(-(float)vmode.width*1/8,0);
	}
}

void Game::createMusic() 
{

	if (!buffer.loadFromFile("resources/sounds/game.ogg")){
		std::cerr << "Error loading sound" << std::endl;
	}
	else {
		bgMusic.setBuffer(buffer);
		bgMusic.setLoop(true);
		bgMusic.setVolume(70);
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


sf::Vector2f Game::getGridPos(sf::Vector2f objPosition){
	sf::Vector2f pos;
	pos.x = (int)round((objPosition.x - ((float)vmode.width*X_RATIO)) / ((float)vmode.height*MULTIPLIER_RATIO));
	pos.y = (int)round((objPosition.y - ((float)vmode.width*Y_RATIO)) / ((float)vmode.height*MULTIPLIER_RATIO));
	return pos;
}

void Game::createGrid()
{
	for (int i = 0; i < grid.size(); i++){
		for (int j = 0; j < grid[i].size(); j++){
			grid[i][j].setSize(sf::Vector2f(((float)vmode.height*MULTIPLIER_RATIO),((float)vmode.height*MULTIPLIER_RATIO)));
			grid[i][j].setFillColor(sf::Color::Transparent);
			grid[i][j].setOutlineColor(sf::Color(200,200,200,100));
			grid[i][j].setOutlineThickness(1);
			grid[i][j].setPosition(((float)vmode.width*X_RATIO)+(((float)vmode.height*MULTIPLIER_RATIO)*i),((float)vmode.width*Y_RATIO)+(j*((float)vmode.height*MULTIPLIER_RATIO)));
		}
	}
}

bool Game::mapParser(std::string mapName)
{
	std::ifstream map(mapName);

	int spriteX, spriteY;
	int obs = 0;

	enum SPRITETYPE {PLAYER, HOUSE, OBST};

	SPRITETYPE spriteType = PLAYER;

	//clear map textures
	for (int iterator1 = 0; iterator1 < grid.size(); iterator1++)
	{
		for (int iterator2 = 0; iterator2 < grid[iterator1].size(); iterator2++)
		{
			grid[iterator1][iterator2].setTexture(NULL);
			grid[iterator1][iterator2].setFillColor(sf::Color::Transparent);
		}
	}
	if (map.is_open())
	{	
		std::string line;
		while ( getline(map,line) )
		{
			if (line[0] == '|')
			{
				std::string value;
				value.clear();

				for(unsigned int iterator = 1; iterator < line.size(); iterator++)
				{

					// receive coordinates values
					if (line[iterator] == ',')
					{
	      			// Receive x value
						spriteX = std::stoi(value);
						value.clear();
					}
					else if (line[iterator] == '|')
					{
	      			// receive y value
						spriteY = std::stoi(value);
						value.clear();

	      			// draw sprite
						if (spriteX >= 0 && spriteX < grid.size() && spriteY >= 0 && spriteY < grid[0].size()){
							grid[spriteX][spriteY].setFillColor(sf::Color::White);

							if (spriteType == HOUSE)
							{
								housePos = grid[spriteX][spriteY].getPosition();
							}
							else if (spriteType == OBST)
							{
								obstaclesPos[obs] = grid[spriteX][spriteY].getPosition();
								obs++;
							} 

							switch (spriteType)
							{
								case OBST:
									grid[spriteX][spriteY].setTexture(&obstacle);
									break;

								case HOUSE:
									grid[spriteX][spriteY].setTexture(&house[0]);
									spriteType = OBST;
									break;

								case PLAYER:								
									//Setting player shape
									playerObj->loadShape(((float)vmode.height*MULTIPLIER_RATIO));			
									playerObj->shape.setPosition(grid[spriteX][spriteY].getPosition());
									playerObj->position.x = playerObj->shape.getPosition().x;
									playerObj->position.y = playerObj->shape.getPosition().y;
									grid[spriteX][spriteY].setFillColor(sf::Color::Transparent);
									spriteType = HOUSE;
									break;
								default:
									break;
							}
						}
					}
					else
					{
						value = value + line[iterator];
					}
				}
			}
		}
		map.close();
		return true;
	}
	else
	{
		std::cerr << "Map File missing" << std::endl;
		return false;
	}
}

GAMESTATE Game::eventHandler(bool isFullscreen, bool isSoundEnabled, int level) 
{
	// Play background music
	if (isSoundEnabled)
	{
		if (bgMusic.getStatus() != sf::SoundSource::Status::Playing)
		{
			bgMusic.play();
		}	
	}
	

	App->clear();
	App->draw(background);

	if (enableDrawing)
	{
		loadGame("resources/maps/" + levels[level]);
	}

	GAMESTATE nextState = PLAYING;

	for (int i = 0; i < grid.size(); i++)
		for (int j = 0; j < grid[i].size(); j++)
			App->draw(grid[i][j]);

		if (playerObj->getDirection() == STOPPED){
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				if (playerObj->getDirection() != UP){
					playerObj->setDirection(UP);
				}	
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				if (playerObj->getDirection() != RIGHT){
					playerObj->setDirection(RIGHT);
				}
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				if (playerObj->getDirection() != DOWN){					
					playerObj->setDirection(DOWN);				
				}
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				if (playerObj->getDirection() != LEFT){
					playerObj->setDirection(LEFT);
				}
			}else if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				if (saveGame()){
					showText(SAVED);
				}
			}				
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			playerObj->stop();
			nextState = MAINMENU;
		}

		// check for player collisions with obstacles
		for (int i = 0; i < obstaclesPos.size(); i++)
		{
			if( getGridPos(obstaclesPos[i]).x == getGridPos(playerObj->getNextPosition()).x &&
				getGridPos(obstaclesPos[i]).y == getGridPos(playerObj->getNextPosition()).y)
			{
				playerObj->stop();
			}
		}

		// check if player is outside the grid
		if( getGridPos(playerObj->position).x < -1 || getGridPos(playerObj->position).x > 6 ||
			getGridPos(playerObj->position).y < -1 || getGridPos(playerObj->position).y > 7)
		{
			playerObj->stop();
			if (playerObj->splash() == 9){
				if (state != LOSE) {
					state = LOSE;
					showText(LOSE);
				}
			}
		}

		// check for player "collision" with house
		if( getGridPos(housePos).x == getGridPos(playerObj->position).x &&
			getGridPos(housePos).y == getGridPos(playerObj->position).y)
		{
			grid[getGridPos(housePos).x ][getGridPos(housePos).y].setTexture(&house[1]);
			playerObj->stop();
			playerObj->shape.setFillColor(sf::Color(0,0,0,0));
			if (state != WIN) {
				state = WIN;
				showText(WIN);
			}
		}

		// move player
		playerObj->move(playerObj->getDirection());
		App->draw(playerObj->shape);

		if (ClockSpeed.getElapsedTime().asSeconds() < 5){
			App->draw(gametext);
		}

		App->display();

		// Stop music if exiting PLAYING state
		if (nextState != PLAYING){
			enableDrawing = true;
			bgMusic.stop();
		}

		return nextState;
	}

void Game::showText(int op){
		if (!font.loadFromFile("resources/fonts/ingame_font.ttf")) {
			std::cerr << "Error loading fonts" << std::endl;
			return;
		}
		gametext.setCharacterSize(vmode.height / 10);
		gametext.setFont(font);
		gametext.setColor(sf::Color(255, 0, 0));
		switch (op){
			case LOSE:
				gametext.setPosition({ (float)(vmode.width / 5),(float)((vmode.height/2) - (vmode.height / 5))});
				gametext.setString("I find your lack of\n\t\t\tHOPE \n\t\tdisturbing");
				break;

			case WIN:
				gametext.setPosition({ (float)(vmode.width / 5),(float)((vmode.height / 2) - (vmode.height / 20))});
				gametext.setString("HOPE, YOU HAVE FOUND");
				break;

			case SAVED:
				std::cout << __LINE__ << std::endl;
				gametext.setCharacterSize(vmode.height/26);
				gametext.setPosition(vmode.width/10,vmode.height-vmode.height/10);
				//gametext.setPosition({ (float)(vmode.width / 5),(float)((vmode.height/2) - (vmode.height / 5))});
				gametext.setString("Saved");
				std::cout << __LINE__ << std::endl;
				break;

			default:
				break;
		}
		ClockSpeed.restart();
}
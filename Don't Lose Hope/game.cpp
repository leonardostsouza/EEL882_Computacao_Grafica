#include "lib/game.h"

Game::Game(bool fs, sf::RenderWindow* wd, sf::VideoMode vm) : window (wd), fullscreen (fs) , vmode (vm) 
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

	//Setting the playershape
	(*playerObj).loadShape(((float)vmode.height*0.11));
}


Game::~Game()
{
}

void Game::loadTextures()
{
	// Obstacles textures
	if(!obstacles[0].loadFromFile("resources/images/sprites.png", sf::IntRect(531,545,33,34)))
		std::cerr << "Error loading sprites" << std::endl;

	if(!obstacles[1].loadFromFile("resources/images/sprites.png", sf::IntRect(2,180,44,42)))
		std::cerr << "Error loading sprites" << std::endl;

	if(!obstacles[2].loadFromFile("resources/images/sprites.png", sf::IntRect(84,130,42,40)))
		std::cerr << "Error loading sprites" << std::endl;

	if(!obstacles[3].loadFromFile("resources/images/sprites.png", sf::IntRect(0,320,47,44)))
		std::cerr << "Error loading sprites" << std::endl;

	if(!obstacles[4].loadFromFile("resources/images/sprites.png", sf::IntRect(6,487,47,40)))
		std::cerr << "Error loading sprites" << std::endl;

	// House Texture
	if(!house.loadFromFile("resources/images/sprites.png", sf::IntRect(152,26,78,67)))
		std::cerr << "Error loading sprites" << std::endl;

	//Player Textures
	(*playerObj).loadTextures();

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
	pos.x = (int)round((objPosition.x - ((float)vmode.width*1/4)) / ((float)vmode.height*0.11));
	pos.y = (int)round((objPosition.y - ((float)vmode.width*1/8)) / ((float)vmode.height*0.11));
	return pos;
}

void Game::createGrid()
{
	for (int i = 0; i < grid.size(); i++){
		for (int j = 0; j < grid[i].size(); j++){
			grid[i][j].setSize(sf::Vector2f(((float)vmode.height*0.11),((float)vmode.height*0.11)));
			grid[i][j].setFillColor(sf::Color::Transparent);
			grid[i][j].setOutlineColor(sf::Color::Black);
			grid[i][j].setOutlineThickness(1);
			grid[i][j].setPosition(((float)vmode.width*1/4)+(((float)vmode.height*0.11)*i),((float)vmode.width*1/8)+(j*((float)vmode.height*0.11)));
		}
	}
}

/*
void Game::movePlayer(){
	float ElapsedTime = ClockSpeed.getElapsedTime().asSeconds();
	ClockSpeed.restart();
	switch(moving){
		case STOPPED:
		break;
		case UP:
		playerPos.y -= Speed * ElapsedTime;
		break;
		case DOWN:
		playerPos.y += Speed * ElapsedTime;
		break;
		case LEFT:
		playerPos.x -= Speed * ElapsedTime;
		break;
		case RIGHT:
		playerPos.x += Speed * ElapsedTime;
		break;		
		default:
		std::cout << "Something's wrong!" << std::endl;
	}

	if (moving != STOPPED){
		if (ClockAnimation.getElapsedTime().asSeconds() >= 0.2f || changeSide == true){
			changeSide = false;
			if (movecounter > 3) movecounter = 0;
			(*playerObj).shape.setTexture(&(*playerObj).textures[moving][movecounter]);
			movecounter++;
			ClockAnimation.restart();
		}
	}

	if (moving == 3){
		for (int i = 0; i < obstaclesPos.size(); i++){
			if (((playerPos.x >= obstaclesPos[i].x) && (playerPos.x <= (obstaclesPos[i].x + 51))) && ((playerPos.y >= obstaclesPos[i].y) && (playerPos.y <= (obstaclesPos[i].y + 51)))){
				moving = 0;
				movecounter = 0;
				(*playerObj).shape.setTexture(&(*playerObj).textures[moving][movecounter]);
				playerPos.x = obstaclesPos[i].x;
				playerPos.y = obstaclesPos[i].y - 51;
			}
		}
	}
	(*playerObj).shape.setPosition(playerPos);
}*/

void Game::mapParser(std::string mapName)
{
	std::ifstream map(mapName);
	int spriteX, spriteY;
	int obs = 0;

	enum SPRITETYPE {PLAYER, HOUSE, O1, O2, O3, O4};

	SPRITETYPE spriteType = PLAYER;

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

							if (spriteType != HOUSE && spriteType != PLAYER){
								obstaclesPos[obs] = grid[spriteX][spriteY].getPosition();
								obs++;
							} 

							switch (spriteType)
							{
								case O1:
									grid[spriteX][spriteY].setTexture(&obstacles[0]);
									break;
								case O2:
									grid[spriteX][spriteY].setTexture(&obstacles[1]);
									break;
								case O3:
									grid[spriteX][spriteY].setTexture(&obstacles[2]);
									break;
								case O4:
									grid[spriteX][spriteY].setTexture(&obstacles[3]);
									break;
								case HOUSE:
									grid[spriteX][spriteY].setTexture(&house);
									spriteType = O1;
									break;
								case PLAYER:								
									(*playerObj).shape.setPosition(grid[spriteX][spriteY].getPosition());
									(*playerObj).position.x = (*playerObj).shape.getPosition().x;
									(*playerObj).position.y = (*playerObj).shape.getPosition().y;
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
	}
	else
	{
		std::cerr << "Map File missing" << std::endl;
	}
}



GAMESTATE Game::eventHandler(sf::Event event, bool isFullscreen, bool isSoundEnabled) 
{
	// Play background music
	if (isSoundEnabled)
	{
		if (bgMusic.getStatus() != sf::SoundSource::Status::Playing)
		{
			bgMusic.play();
		}	
	}
	

	(*window).clear();
	(*window).draw(background);

	if (enableDrawing)
	{
		mapParser("resources/maps/phase1");
		enableDrawing = false;
	}

	GAMESTATE nextState = PLAYING;

	for (int i = 0; i < grid.size(); i++)
		for (int j = 0; j < grid[i].size(); j++)
			(*window).draw(grid[i][j]);

		if ((*playerObj).getDirection() == STOPPED){
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				if ((*playerObj).getDirection() != UP){
					(*playerObj).setDirection(UP);
					(*playerObj).changeSide = true;
				}	
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				if (moving != RIGHT){
					(*playerObj).setDirection(RIGHT);
					(*playerObj).changeSide = true;
				}
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				if (moving != DOWN){					
					(*playerObj).setDirection(DOWN);				
					(*playerObj).changeSide = true;
				}
			}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				if (moving != LEFT){
					(*playerObj).setDirection(LEFT);
					(*playerObj).changeSide = true;
				}
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			(*playerObj).stop();
			movecounter = 0;
			nextState = MAINMENU;
		}

		// check for player collisions with obstacles
		for (int i = 0; i < obstaclesPos.size(); i++)
		{
			if( getGridPos(obstaclesPos[i]).x == getGridPos((*playerObj).getNextPosition()).x &&
				getGridPos(obstaclesPos[i]).y == getGridPos((*playerObj).getNextPosition()).y)
			{
				(*playerObj).setDirection(STOPPED);
			}
		}

		// move player
		(*playerObj).move((*playerObj).getDirection());
		(*window).draw((*playerObj).shape);
		(*window).display();

		// Stop music if exiting PLAYING state
		if (nextState != PLAYING){
			enableDrawing = true;
			bgMusic.stop();
		}

		return nextState;
	}
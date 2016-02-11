#include "lib/game.h"

Game::Game(bool fs, sf::RenderWindow* wd, sf::VideoMode vm) : window (wd), fullscreen (fs) , vmode (vm) 
{

	// Create the background
	createBackground();

	//Create the grid
	createGrid();

	//Load the textures
	loadTextures();

	// Creating the music
	createMusic();

	//play();
}


Game::~Game()
{
}

void Game::loadTextures()
{
		// Obstacles textures
		if(!obstacles[0].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
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
		if(!house.loadFromFile("resources/images/sprites.png", sf::IntRect(683,560,80,80)))
			std::cerr << "Error loading sprites" << std::endl;

		//Player Textures
		if(!player[0].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
			std::cerr << "Error loading sprites" << std::endl;

		if(!player[1].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
			std::cerr << "Error loading sprites" << std::endl;

		if(!player[2].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
			std::cerr << "Error loading sprites" << std::endl;

		if(!player[3].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
			std::cerr << "Error loading sprites" << std::endl;

		if(!player[4].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
			std::cerr << "Error loading sprites" << std::endl;

		if(!player[5].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
			std::cerr << "Error loading sprites" << std::endl;

		if(!player[6].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
			std::cerr << "Error loading sprites" << std::endl;

		if(!player[7].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
			std::cerr << "Error loading sprites" << std::endl;

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

void Game::createGrid()
{
	for (int i = 0; i < grid.size(); i++){
		for (int j = 0; j < grid[i].size(); j++){
			grid[i][j].setSize(sf::Vector2f(50,50));
			grid[i][j].setFillColor(sf::Color::Transparent);
			grid[i][j].setOutlineColor(sf::Color::Black);
			grid[i][j].setOutlineThickness(1);
			grid[i][j].setPosition(160+(51*j),60+(i*51));
		}
	}
}

void Game::mapParser(std::string mapName)
{
	std::ifstream map(mapName);
	int spriteX, spriteY;

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

	      			//std::cout << iterator << " " << spriteType << " " << spriteX << " " << spriteY << std::endl;

	      			// draw sprite
	      			if (spriteX >= 0 && spriteX < grid.size() && spriteY >= 0 && spriteY < grid[0].size()){
		      			grid[spriteX][spriteY].setFillColor(sf::Color::White);

		      			std::cout << iterator << " " << spriteType << " " << spriteX << " " << spriteY << std::endl;

		      			switch (spriteType)
		      			{
		      				case O1:		      				
								grid[spriteX][spriteY].setTexture(&obstacles[1]);
								break;
							case O2:
								grid[spriteX][spriteY].setTexture(&obstacles[2]);
								break;
							case O3:
								grid[spriteX][spriteY].setTexture(&obstacles[3]);
								break;
							case O4:
								grid[spriteX][spriteY].setTexture(&obstacles[4]);
								break;
							case HOUSE:
								grid[spriteX][spriteY].setTexture(&house);
								spriteType = O1;
								break;
							default:
								grid[spriteX][spriteY].setTexture(&player[0]);
								spriteType = HOUSE;
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

	/*grid[0][0].setFillColor(sf::Color::White);
	grid[0][0].setTexture(&obstacles[0]);
	grid[0][1].setFillColor(sf::Color::White);
	grid[0][1].setTexture(&obstacles[1]);
	grid[0][2].setFillColor(sf::Color::White);
	grid[0][2].setTexture(&obstacles[2]);
	grid[0][3].setFillColor(sf::Color::White);
	grid[0][3].setTexture(&obstacles[3]);
	grid[0][4].setFillColor(sf::Color::White);
	grid[0][4].setTexture(&obstacles[4]);
	grid[0][5].setFillColor(sf::Color::White);
	grid[0][5].setTexture(&house);*/

	//Draws the grid
	//for (std::vector<sf::RectangleShape>::iterator elem = grid.begin(); elem != grid.end(); elem++) {
	//	for (std::vector<sf::RectangleShape>::iterator op = elem.begin(); op != elem.end(); op++) {
//			(*window).draw(*op);
	for (int i = 0; i < grid.size(); i++)
		for (int j = 0; j < grid[i].size(); j++)
			(*window).draw(grid[i][j]);

	
	

	

	//std::cout << "W: " << (float)vmode.width << " | H: " << (float)vmode.height << std::endl;

	
	
	
	

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		nextState = MAINMENU;
	}
	

	(*window).display();

	// Stop music if exiting PLAYING state
	if (nextState != PLAYING){
		enableDrawing = true;
		bgMusic.stop();
	}

	return nextState;
}
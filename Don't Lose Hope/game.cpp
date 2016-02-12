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

		//Setting the playershape
		playerShape.setSize(sf::Vector2f(50,50));
		playerShape.setFillColor(sf::Color::White);
		playerShape.setTexture(&player[0][0]);
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
			if(!house.loadFromFile("resources/images/sprites.png", sf::IntRect(683,560,80,80)))
				std::cerr << "Error loading sprites" << std::endl;

			//Player Textures
			if(!player[0][0].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
				std::cerr << "Error loading sprites" << std::endl;

			if(!player[1][0].loadFromFile("resources/images/sprites.png", sf::IntRect(34,82,39,41)))
				std::cerr << "Error loading sprites" << std::endl;

			if(!player[1][1].loadFromFile("resources/images/sprites.png", sf::IntRect(68,82,39,41)))
				std::cerr << "Error loading sprites" << std::endl;

			if(!player[1][2].loadFromFile("resources/images/sprites.png", sf::IntRect(34,82,39,41)))
				std::cerr << "Error loading sprites" << std::endl;

			if(!player[2][0].loadFromFile("resources/images/sprites.png", sf::IntRect(170,82,39,41)))
				std::cerr << "Error loading sprites" << std::endl;

			if(!player[2][1].loadFromFile("resources/images/sprites.png", sf::IntRect(204,82,39,41)))
				std::cerr << "Error loading sprites" << std::endl;

			if(!player[2][2].loadFromFile("resources/images/sprites.png", sf::IntRect(170,82,39,41)))
				std::cerr << "Error loading sprites" << std::endl;			

			if(!player[3][0].loadFromFile("resources/images/sprites.png", sf::IntRect(0,0,39,41)))
				std::cerr << "Error loading sprites" << std::endl;

			if(!player[3][1].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
				std::cerr << "Error loading sprites" << std::endl;

			if(!player[3][2].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
				std::cerr << "Error loading sprites" << std::endl;

			if(!player[4][0].loadFromFile("resources/images/sprites.png", sf::IntRect(170,0,39,41)))
				std::cerr << "Error loading sprites" << std::endl;
			
			if(!player[4][1].loadFromFile("resources/images/sprites.png", sf::IntRect(238,0,39,41)))
				std::cerr << "Error loading sprites" << std::endl;

			if(!player[4][2].loadFromFile("resources/images/sprites.png", sf::IntRect(170,0,39,41)))
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
				grid[i][j].setPosition(160+(51*i),60+(j*51));
			}
		}
	}

	void Game::movePlayer(){
		//0 CIMA
		//1 DIREITA
		//2 BAIXO
		//3 ESQUERDA
		float ElapsedTime = ClockSpeed.getElapsedTime().asSeconds();
		ClockSpeed.restart();
		switch(moving){
			case 0:
				break;
			case 1:
				playerPos.y -= Speed * ElapsedTime;
				break;
			case 2:
				playerPos.x += Speed * ElapsedTime;
				break;
			case 3:
				playerPos.y += Speed * ElapsedTime;
				break;
			case 4:
				playerPos.x -= Speed * ElapsedTime;
				break;
			default:
				std::cout << "Something's wrong!" << std::endl;
		}

		if (moving != 0){
			if (ClockAnimation.getElapsedTime().asSeconds() >= 0.5f){
				if (movecounter > 2) movecounter = 0;
				playerShape.setTexture(&player[moving][movecounter]);
				movecounter++;
				ClockAnimation.restart();
			}
		}
		playerShape.setPosition(playerPos);
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

		      			// draw sprite
		      			if (spriteX >= 0 && spriteX < grid.size() && spriteY >= 0 && spriteY < grid[0].size()){
			      			grid[spriteX][spriteY].setFillColor(sf::Color::White);

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
								default:
									playerShape.setPosition(grid[spriteX][spriteY].getPosition());
									playerPos.x = playerShape.getPosition().x;
									playerPos.y = playerShape.getPosition().y;
									grid[spriteX][spriteY].setFillColor(sf::Color::Transparent);
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

		for (int i = 0; i < grid.size(); i++)
			for (int j = 0; j < grid[i].size(); j++)
				(*window).draw(grid[i][j]);

		

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			moving = 1;
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			moving = 2;
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			moving = 3;
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			moving = 4;
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			nextState = MAINMENU;
		}

		movePlayer();	
		(*window).draw(playerShape);
		(*window).display();

		// Stop music if exiting PLAYING state
		if (nextState != PLAYING){
			enableDrawing = true;
			bgMusic.stop();
		}

		return nextState;
	}
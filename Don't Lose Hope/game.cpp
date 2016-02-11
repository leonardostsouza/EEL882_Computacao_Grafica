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

void Game::loadTextures(){
		if(!obstacles[0].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
			std::cerr << "Error loading background" << std::endl;

		if(!obstacles[1].loadFromFile("resources/images/sprites.png", sf::IntRect(2,180,44,42)))
			std::cerr << "Error loading background" << std::endl;

		if(!obstacles[2].loadFromFile("resources/images/sprites.png", sf::IntRect(84,130,42,40)))
			std::cerr << "Error loading background" << std::endl;

		if(!obstacles[3].loadFromFile("resources/images/sprites.png", sf::IntRect(0,320,47,44)))
			std::cerr << "Error loading background" << std::endl;

		if(!obstacles[4].loadFromFile("resources/images/sprites.png", sf::IntRect(6,487,47,40)))
			std::cerr << "Error loading background" << std::endl;

		if(!house.loadFromFile("resources/images/sprites.png", sf::IntRect(683,560,80,80)))
			std::cerr << "Error loading background" << std::endl;
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
		background.scale(((float)vmode.width*1.2) / (float)texture.getSize().x, (float)vmode.height / (float)texture.getSize().y);
		background.setPosition(-(float)vmode.width*1/8,0);
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

void Game::createGrid(){
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
GAMESTATE Game::eventHandler(GAMESTATE localstate) {
	(*window).clear();
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
	(*window).draw(background);

	grid[0][0].setFillColor(sf::Color::White);
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
	grid[0][5].setTexture(&house);

	//Draws the grid
	//for (std::vector<sf::RectangleShape>::iterator elem = grid.begin(); elem != grid.end(); elem++) {
	//	for (std::vector<sf::RectangleShape>::iterator op = elem.begin(); op != elem.end(); op++) {
//			(*window).draw(*op);
		for (int i = 0; i < grid.size(); i++)
			for (int j = 0; j < grid[i].size(); j++)
				(*window).draw(grid[i][j]);

	
	

	

	//std::cout << "W: " << (float)vmode.width << " | H: " << (float)vmode.height << std::endl;

	
	
	
	GAMESTATE nextState = PLAYING;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		nextState = MAINMENU;
	}
	

	(*window).display();

	return nextState;
}
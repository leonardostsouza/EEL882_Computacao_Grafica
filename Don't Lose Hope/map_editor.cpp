#include "lib/map_editor.h"

MapEditor::MapEditor(bool fs, sf::RenderWindow* wd, sf::VideoMode vm) : App (wd), fullscreen (fs) , vmode (vm)
{
	// Create the background
	createBackground();

	//Create the grid
	createGrid();

	//Load the player
	loadTextures();

	// Creating the music
	createMusic();	
}


MapEditor::~MapEditor()
{
}

void MapEditor::loadTextures()
{
	// Obstacles textures
	if(!obstacle.loadFromFile("resources/images/sprites.png", sf::IntRect(531,545,33,34)))
		std::cerr << "Error loading sprites" << std::endl;

	// House Textures
	if(!house[0].loadFromFile("resources/images/sprites.png", sf::IntRect(152,26,78,67)))
		std::cerr << "Error loading sprites" << std::endl;

	if(!house[1].loadFromFile("resources/images/sprites.png", sf::IntRect(258,26,78,67)))
		std::cerr << "Error loading sprites" << std::endl;

}

void MapEditor::createBackground() 
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

	toolBox.setSize(sf::Vector2f((vmode.width / 5), (vmode.height / 2)));
	toolBox.setPosition(0, 0);
	toolBox.setFillColor(sf::Color(0, 102, 204, 90));
}

void MapEditor::createMusic() 
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

bool MapEditor::isFullscreen()
{
	return this->fullscreen;
}

void MapEditor::setFullscreen(bool fs)
{
	this->fullscreen = fs;
}

void MapEditor::createGrid()
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



GAMESTATE MapEditor::eventHandler(bool isFullscreen, bool isSoundEnabled) 
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
	App->draw(toolBox);

	GAMESTATE nextState = CREATING;

	for (int i = 0; i < grid.size(); i++)
		for (int j = 0; j < grid[i].size(); j++)
			App->draw(grid[i][j]);

	
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			nextState = MAINMENU;
		}

		App->display();

		// Stop music if exiting PLAYING state
		if (nextState != CREATING){
			bgMusic.stop();
		}


		return nextState;
	}
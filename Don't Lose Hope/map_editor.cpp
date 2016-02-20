#include "lib/map_editor.h"

MapEditor::MapEditor(bool fs, sf::RenderWindow* wd, sf::VideoMode vm) : App (wd), fullscreen (fs) , vmode (vm)
{
//Load the player
	loadTextures();

// Create the background
	createBackground();

//Create the grid
	createGrid();

// Creating the music
	createMusic();	
}


MapEditor::~MapEditor()
{
}

void MapEditor::loadTextures()
{
// Obstacles textures
	if(!sprites[2].loadFromFile("resources/images/sprites.png", sf::IntRect(531,545,33,34)))
		std::cerr << "Error loading sprites" << std::endl;

// House Textures
	if(!sprites[1].loadFromFile("resources/images/sprites.png", sf::IntRect(152,26,78,67)))
		std::cerr << "Error loading sprites" << std::endl;

// Player Textures
	if(!sprites[0].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
		std::cerr << "Error loading player textures" << std::endl;

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

	toolBox.setSize(sf::Vector2f((vmode.width / 9), (vmode.height / 2.2)));
	toolBox.setPosition(20, vmode.height/3.4);
	toolBox.setFillColor(sf::Color(0, 102, 204, 90));

	mouseBox = new sf::RectangleShape;
	mouseBox->setSize(sf::Vector2f(((float)vmode.height*MULTIPLIER_RATIO),((float)vmode.height*MULTIPLIER_RATIO)));
	mouseBox->setFillColor(sf::Color::Transparent);

	for (int i = 0; i<tools.size(); i++){
		tools[i].setSize(sf::Vector2f(((float)vmode.height*MULTIPLIER_RATIO),((float)vmode.height*MULTIPLIER_RATIO)));
		tools[i].setFillColor(sf::Color::White);
		tools[i].setPosition(20+toolBox.getSize().x/7,(vmode.height/3.1)+i*20+i*((float)vmode.height*MULTIPLIER_RATIO));
		tools[i].setOutlineColor(sf::Color(0,0,0,150));
		tools[i].setOutlineThickness(1);
	}

	tools[0].setTexture(&sprites[0]);
	tools[1].setTexture(&sprites[1]);
	tools[2].setTexture(&sprites[2]);
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

void MapEditor::changeMouseBox(int type, sf::Texture* txt){
	delete mouseBox;
	mouseBox = new sf::RectangleShape;
	mouseBox->setSize(sf::Vector2f(((float)vmode.height*MULTIPLIER_RATIO),((float)vmode.height*MULTIPLIER_RATIO)));
	if (type == WHITE){
		mouseBox->setFillColor(sf::Color::White);
		mouseBox->setTexture(txt);
	}else{
		mouseBox->setFillColor(sf::Color::Transparent);
	}
	
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

sf::Vector2i MapEditor::getGridPos(sf::Vector2i objPosition){
	sf::Vector2i pos;
	pos.x = (int)round((objPosition.x - ((float)vmode.width*X_RATIO)) / ((float)vmode.height*MULTIPLIER_RATIO));
	pos.y = (int)round((objPosition.y - ((float)vmode.width*Y_RATIO)) / ((float)vmode.height*MULTIPLIER_RATIO));
	return pos;
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
	for (int i = 0; i<tools.size(); i++){
		App->draw(tools[i]);
	}
	
	mousePos=sf::Mouse::getPosition(*App);
	
	GAMESTATE nextState = CREATING;
	if ((mousePos.x >= 20+toolBox.getSize().x/7) && (mousePos.x <= (20+toolBox.getSize().x/7 + ((float)vmode.height*MULTIPLIER_RATIO)))){
		if ((mousePos.y >= (vmode.height/3.1)) && (mousePos.y <= (vmode.height/3.1)+((float)vmode.height*MULTIPLIER_RATIO))){
				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
				}

				if (clickEnable)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{	
						changeMouseBox(WHITE,&sprites[0]);
						typeChosen = PLAYER;
						clickEnable = false;
					}						
				}
		}
		else if ((mousePos.y >= (vmode.height/3.1)+20+((float)vmode.height*MULTIPLIER_RATIO)) && (mousePos.y <= (vmode.height/3.1)+20+2*((float)vmode.height*MULTIPLIER_RATIO))) {
				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
				}

				if (clickEnable)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						changeMouseBox(WHITE,&sprites[1]);
						typeChosen = HOUSE;
						clickEnable = false;
					}						
				}
		}
		else if ((mousePos.y >= (vmode.height/3.1)+40+2*((float)vmode.height*MULTIPLIER_RATIO)) && (mousePos.y <= (vmode.height/3.1)+40+3*((float)vmode.height*MULTIPLIER_RATIO))) {
				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
				}

				if (clickEnable)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						changeMouseBox(WHITE,&sprites[2]);
						typeChosen = OBSTACLE;
						clickEnable = false;
					}						
				}
		}
	}else{
		if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
		}
		if (clickEnable){
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				clickCoord = getGridPos(mousePos);
				if((clickCoord.x >= 0 && clickCoord.x < 7) && (clickCoord.y >= 0 && clickCoord.y < 7)){
					grid[clickCoord.x][clickCoord.y].setFillColor(sf::Color::White);
					if (typeChosen != NONE){
						grid[clickCoord.x][clickCoord.y].setTexture(&sprites[typeChosen-1]);
					}
				} 
			}
		}
	}
	
	mouseBox->setPosition((mousePos.x-(((float)vmode.height*MULTIPLIER_RATIO)/2)), (mousePos.y - (((float)vmode.height*MULTIPLIER_RATIO)/2)));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)){
		typeChosen = NONE;
		changeMouseBox(TRANSPARENT);
	}
	App->draw((*mouseBox));


	

	for (int i = 0; i < grid.size(); i++){
		for (int j = 0; j < grid[i].size(); j++){
			App->draw(grid[i][j]);
		}
	}


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
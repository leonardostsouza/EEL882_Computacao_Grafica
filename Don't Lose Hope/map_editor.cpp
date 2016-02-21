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

// Creating the text
	setText();
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

void MapEditor::setText(){
	if (!font.loadFromFile("resources/fonts/message_font.ttf")) {
		std::cerr << "Error loading fonts" << std::endl;
		return;
	}
	message.setCharacterSize(vmode.height/26);
	message.setPosition(vmode.width/10,vmode.height-vmode.height/10);
	message.setFont(font);
	message.setColor(sf::Color(255, 0, 0));
	message.setString("Doubts? Any doubts? Questions? Press CTRL + H for Help");
}

void MapEditor::showMessage(std::string txt, float pos){
	message.setPosition(vmode.width/10,pos);
	message.setString(txt);
	ClockSpeed.restart();
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

bool MapEditor::mapWriter(){
	if (objPosition[0] != sf::Vector2i({-1,-1}) && objPosition[1] != sf::Vector2i({-1,-1})){
	std::ofstream map("resources/maps/" + savename);
	if(map.is_open()){
		map << "#Map Created with Don't Lose Hope Editor" << std::endl;
		map << "#|PLAYER_POSITION|HOUSE_POSITION|OBSTACLE1|OBSTACLE2|OBSTACLE3|..." << std::endl;
		for (int i = 0; i< objPosition.size(); i++){
			map << "|" << objPosition[i].x << "," << objPosition[i].y;
		}
		map << "|" << std::endl;
	}
	map.close();
	return true;
	}else{
		return false;
	}
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

void MapEditor::delFromGrid(){
	clickCoord = getGridPos(mousePos);
	for (int i = 0; i< objPosition.size(); i++){
		if ((objPosition[i].x == clickCoord.x) && (objPosition[i].y == clickCoord.y)){
			objPosition[i] = sf::Vector2i({-1,-1});
			if (i >= 2){
				objPosition[i] = sf::Vector2i({-1,-1});
				for (int j = i; j < objPosition.size()-1; j++){
					objPosition[j] = objPosition[j+1];
				}
				qttObstacles--;
			}
			grid[clickCoord.x][clickCoord.y].setTexture(NULL);
			grid[clickCoord.x][clickCoord.y].setFillColor(sf::Color::Transparent);
		}
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
	pos.x = (int)round((-(((float)vmode.height*MULTIPLIER_RATIO)/2) + objPosition.x - ((float)vmode.width*X_RATIO)) / ((float)vmode.height*MULTIPLIER_RATIO));
	pos.y = (int)round((-(((float)vmode.height*MULTIPLIER_RATIO)/2) + objPosition.y - ((float)vmode.width*Y_RATIO)) / ((float)vmode.height*MULTIPLIER_RATIO));
	return pos;
}

GAMESTATE MapEditor::eventHandler(sf::Event event, bool isFullscreen, bool isSoundEnabled) 
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

	// Shade player tool button if player already on map
	if (objPosition[0] != sf::Vector2i({-1,-1}))
	{
		sf::RectangleShape mask;
		mask.setFillColor(sf::Color(255, 255, 255, 150));
		mask.setPosition(tools[0].getPosition().x, tools[0].getPosition().y);
		mask.setSize(tools[0].getSize());

		App->draw(mask);
	}

	// Shade house tool button if house already on map
	if (objPosition[1] != sf::Vector2i({-1,-1}))
	{
		sf::RectangleShape mask;
		mask.setFillColor(sf::Color(255, 255, 255, 150));
		mask.setPosition(tools[1].getPosition().x, tools[1].getPosition().y);
		mask.setSize(tools[1].getSize());

		App->draw(mask);
	}

	// Shade obstacle tool button if max obstacle quantity reached
	if (qttObstacles >= MAX_OBSTACLES)
	{
		sf::RectangleShape mask;
		mask.setFillColor(sf::Color(255, 255, 255, 150));
		mask.setPosition(tools[2].getPosition().x, tools[2].getPosition().y);
		mask.setSize(tools[2].getSize());

		App->draw(mask);
	}
	

	GAMESTATE nextState = CREATING;

	if (!savestate){
		mousePos=sf::Mouse::getPosition(*App);


		if ((mousePos.x >= 20+toolBox.getSize().x/7) && (mousePos.x <= (20+toolBox.getSize().x/7 + ((float)vmode.height*MULTIPLIER_RATIO)))){
			if ((mousePos.y >= (vmode.height/3.1)) && (mousePos.y <= (vmode.height/3.1)+((float)vmode.height*MULTIPLIER_RATIO))){
				if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = true;
				}

				if (clickEnable)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{	
						if (objPosition[0] == sf::Vector2i({-1,-1})){
							changeMouseBox(WHITE,&sprites[0]);
							typeChosen = PLAYER;
							clickEnable = false;
						}
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
						if (objPosition[1] == sf::Vector2i({-1,-1})){
							changeMouseBox(WHITE,&sprites[1]);
							typeChosen = HOUSE;
							clickEnable = false;
						}
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
						if (objPosition[qttObstacles+2] == sf::Vector2i({-1,-1}) && qttObstacles < MAX_OBSTACLES){
							changeMouseBox(WHITE,&sprites[2]);
							typeChosen = OBSTACLE;
							clickEnable = false;
						}						
					}
				}
			}
		}else{
			if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				clickEnable = true;
			}
			if (clickEnable){
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					clickEnable = false;

					if (typeChosen != NONE){
						clickCoord = getGridPos(mousePos);

						if((clickCoord.x >= 0 && clickCoord.x < 7) && (clickCoord.y >= 0 && clickCoord.y < 7)){
							if (grid[clickCoord.x][clickCoord.y].getTexture() == NULL){
								grid[clickCoord.x][clickCoord.y].setFillColor(sf::Color::White);
								grid[clickCoord.x][clickCoord.y].setTexture(&sprites[typeChosen-1]);

								switch(typeChosen){

									case PLAYER:
									objPosition[0] = sf::Vector2i({clickCoord.x,clickCoord.y});
									break;

									case HOUSE:
									objPosition[1] = sf::Vector2i({clickCoord.x,clickCoord.y});
									break;

									case OBSTACLE:
									objPosition[qttObstacles+2] = sf::Vector2i({clickCoord.x,clickCoord.y});
									qttObstacles++;
									break;

									default:
									break;
								}

								if ((typeChosen != NONE))// || (typeChosen == OBSTACLE && qttObstacles >= MAX_OBSTACLES)){
								{
									typeChosen = NONE;
									changeMouseBox(TRANSPARENT);
								}
							}
						}
					} 
				}
			}
		}

		mouseBox->setPosition((mousePos.x-(((float)vmode.height*MULTIPLIER_RATIO)/2)), (mousePos.y - (((float)vmode.height*MULTIPLIER_RATIO)/2)));
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			keyPressEnable = true;
		}


		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) && keyPressEnable == true){
			keyPressEnable = false;
			delFromGrid();
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && keyPressEnable == true){
			keyPressEnable = false;
			if (typeChosen == NONE){
				nextState = MAINMENU;
			}else{
				typeChosen = NONE;
				changeMouseBox(TRANSPARENT);
			}
		}else if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && sf::Keyboard::isKeyPressed(sf::Keyboard::S) && keyPressEnable == true){
			keyPressEnable = false;
			savestate = true;
			showMessage("File Name: ",vmode.height-vmode.height/10);
		}else if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && sf::Keyboard::isKeyPressed(sf::Keyboard::H) && keyPressEnable == true){
			showMessage("Select a cartoon and put it over the grid\nPress Control + S to save. Press ESC to cancel or quit\nPress Delete with the mouse over a cartoon to delete",vmode.height-vmode.height/4);
		}

		if (ClockSpeed.getElapsedTime().asSeconds() < 5) {
			App->draw(message);
		}
		App->draw((*mouseBox));

	}else{
		//showMessage("Name:",vmode.height-vmode.height/10);
		if (event.type == sf::Event::TextEntered && keyPressEnable){
			keyPressEnable = false;
			if(event.text.unicode == 8){
				if (savename.size()>0){
					savename.resize(savename.size()-1);
					showMessage("File Name: " + savename,vmode.height-vmode.height/10);
				}
			}else if(event.text.unicode == 13){
				showMessage("",vmode.height-vmode.height/10);
				if(!mapWriter()){
					showMessage("At least a player and a house are needed",vmode.height-vmode.height/10);
					savename = "";
				}else{
					showMessage("Saved",vmode.height-vmode.height/10);
				}
				savestate = false;
			}else if ((event.text.unicode > 47 && event.text.unicode < 58) || (event.text.unicode > 96 && event.text.unicode < 123) || (event.text.unicode > 64 && event.text.unicode < 91)){
					savename+= static_cast<char>(event.text.unicode);
					showMessage("File Name: " + savename,vmode.height-vmode.height/10);
			}
		}else if(event.type == sf::Event::KeyReleased){
			keyPressEnable = true;
		}
		//mapWriter();
		App->draw(message);
	}


	for (int i = 0; i < grid.size(); i++){
		for (int j = 0; j < grid[i].size(); j++){
			App->draw(grid[i][j]);
		}
	}

	App->display();

	// Stop music if exiting PLAYING state
	if (nextState != CREATING){
		bgMusic.stop();
	}

	return nextState;
}
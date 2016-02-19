#include "lib/player.h"

Player::Player()
{
	//current_lifes = PLAYER_MAX_LIFES;
	direction = STOPPED;
	movecounter = 0;
	splashCounter = 0;
	shapeSize = 0;
	textures = std::vector<std::vector<sf::Texture>>(5,std::vector<sf::Texture>(4));
	splashTextures = std::vector<sf::Texture>(9);
}

Player::~Player(){}

/*Player::setLifes(unsigned int lifeQtt)
{
	current_lifes = lifeQtt;
}

Player::getLifes()
{
	return current_lifes;
}*/

/*sf::Vector2f Player::getPosition()
{
	return playerPosition;
}*/

int Player::getDirection()
{
	return direction;
}

void Player::setDirection(int newDirection)
{
	direction = newDirection;
}

void Player::loadTextures()
{
	#ifdef DEBUG
	std::cout << "DEBUG === Loading player textures" << std::endl;
	#endif

	if(!textures[0][0].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[0][1].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[0][2].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[0][3].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[1][0].loadFromFile("resources/images/sprites.png", sf::IntRect(0,40,38,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[1][1].loadFromFile("resources/images/sprites.png", sf::IntRect(70,40,39,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[1][2].loadFromFile("resources/images/sprites.png", sf::IntRect(35,40,38,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[1][3].loadFromFile("resources/images/sprites.png", sf::IntRect(70,40,39,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[2][0].loadFromFile("resources/images/sprites.png", sf::IntRect(0,125,38,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[2][1].loadFromFile("resources/images/sprites.png", sf::IntRect(35,125,39,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[2][2].loadFromFile("resources/images/sprites.png", sf::IntRect(70,125,38,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[2][3].loadFromFile("resources/images/sprites.png", sf::IntRect(35,125,39,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[3][0].loadFromFile("resources/images/sprites.png", sf::IntRect(0,0,37,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[3][1].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[3][2].loadFromFile("resources/images/sprites.png", sf::IntRect(71,0,38,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[3][3].loadFromFile("resources/images/sprites.png", sf::IntRect(34,0,39,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[4][0].loadFromFile("resources/images/sprites.png", sf::IntRect(0,82,38,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[4][1].loadFromFile("resources/images/sprites.png", sf::IntRect(35,82,39,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[4][2].loadFromFile("resources/images/sprites.png", sf::IntRect(70,82,38,41)))
	std::cerr << "Error loading player textures" << std::endl;

	if(!textures[4][3].loadFromFile("resources/images/sprites.png", sf::IntRect(35,82,39,41)))
	std::cerr << "Error loading player textures" << std::endl;

	// splash textures
	if(!splashTextures[0].loadFromFile("resources/images/sprites.png", sf::IntRect(345,316,50,50)))
	std::cerr << "Error loading player splash textures" << std::endl;

	if(!splashTextures[1].loadFromFile("resources/images/sprites.png", sf::IntRect(395,316,50,50)))
		std::cerr << "Error loading player splash textures" << std::endl;

	if(!splashTextures[2].loadFromFile("resources/images/sprites.png", sf::IntRect(445,316,50,50)))
		std::cerr << "Error loading player splash textures" << std::endl;

	if(!splashTextures[3].loadFromFile("resources/images/sprites.png", sf::IntRect(495,316,50,50)))
		std::cerr << "Error loading player splash textures" << std::endl;

	if(!splashTextures[4].loadFromFile("resources/images/sprites.png", sf::IntRect(545,316,50,50)))
		std::cerr << "Error loading player splash textures" << std::endl;

	if(!splashTextures[5].loadFromFile("resources/images/sprites.png", sf::IntRect(595,316,60,50)))
		std::cerr << "Error loading player splash textures" << std::endl;

	if(!splashTextures[6].loadFromFile("resources/images/sprites.png", sf::IntRect(645,316,50,50)))
		std::cerr << "Error loading player splash textures" << std::endl;

	if(!splashTextures[7].loadFromFile("resources/images/sprites.png", sf::IntRect(695,316,50,50)))
		std::cerr << "Error loading player splash textures" << std::endl;

	if(!splashTextures[8].loadFromFile("resources/images/sprites.png", sf::IntRect(745,316,50,50)))
	std::cerr << "Error loading player splash textures" << std::endl;


	#ifdef DEBUG
	std::cout << "DEBUG === Finished loading player textures" << std::endl;
	#endif
}

void Player::loadShape(int size)
{
	shapeSize = size;
	shape.setSize(sf::Vector2f(size,size));
	shape.setFillColor(sf::Color::White);
	shape.setTexture(&textures[0][0]);

	movecounter = 0;
	splashCounter = 0;
}

void Player::move(int moveDirection)
{
	float ElapsedTime = ClockSpeed.getElapsedTime().asSeconds();
	ClockSpeed.restart();
	switch(moveDirection){
		case STOPPED:
		direction = STOPPED;
		break;
		case UP:
		direction = UP;
		position.y -= MOVE_SPEED * ElapsedTime;
		break;
		case DOWN:
		direction = DOWN;
		position.y += MOVE_SPEED * ElapsedTime;
		break;
		case LEFT:
		direction = LEFT;
		position.x -= MOVE_SPEED * ElapsedTime;
		break;
		case RIGHT:
		direction = RIGHT;
		position.x += MOVE_SPEED * ElapsedTime;
		break;		
		default:
		std::cout << "Invalid move direction!" << std::endl;
	}

	if (direction != STOPPED){
		if (ClockAnimation.getElapsedTime().asSeconds() >= 0.2f || changeSide == true){
			changeSide = false;
			if (movecounter > 3) movecounter = 0;
			shape.setTexture(&textures[moveDirection][movecounter]);
			movecounter++;
			ClockAnimation.restart();
		}
	}

	shape.setPosition(position);
}

sf::Vector2f Player::getNextPosition()
{
	sf::Vector2f nextPosition = position;

	switch(direction)
	{
		case STOPPED:
		break;
		case UP:
		nextPosition.y -= shapeSize/2;
		break;
		case DOWN:
		nextPosition.y += shapeSize/2;
		break;
		case LEFT:
		nextPosition.x -= shapeSize/2;
		break;
		case RIGHT:
		nextPosition.x += shapeSize/2;
		break;		
		default:
		std::cout << "Invalid move direction!" << std::endl;
	}

	return nextPosition;
}

void Player::stop()
{
	this->move(STOPPED);
}

void Player::splash()
{ 
	if (splashCounter < 9)
	{
		if (ClockAnimation.getElapsedTime().asSeconds() >= 0.2f)
		{
			shape.setTexture(&splashTextures[splashCounter]);
			splashCounter++;
			ClockAnimation.restart();
		}
	}
	
}
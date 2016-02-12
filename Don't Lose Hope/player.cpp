#include "lib/player.h"

Player::Player()
{
		//current_lifes = PLAYER_MAX_LIFES;
		direction = STOPPED;
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

	#ifdef DEBUG
	std::cout << "DEBUG === Finished loading player textures" << std::endl;
	#endif
}

void Player::loadShape(int size)
{
	shape.setSize(sf::Vector2f(size,size));
	shape.setFillColor(sf::Color::White);
	shape.setTexture(&textures[0][0]);
}

void Player::move(int moveDirection)
{
	float ElapsedTime = ClockSpeed.getElapsedTime().asSeconds();
	ClockSpeed.restart();
	switch(moveDirection){
		case STOPPED:
		direction = STOPPED;
		movecounter = 0;
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
		std::cout << "Invalid moveDirection!" << std::endl;
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

/*
	if (direction == DOWN){
		for (int i = 0; i < obstaclesPos.size(); i++){
			if (((playerPosition.x >= obstaclesPos[i].x) && (playerPosition.x <= (obstaclesPos[i].x + 51))) && ((playerPos.y >= obstaclesPos[i].y) && (playerPos.y <= (obstaclesPos[i].y + 51)))){
				moveDirection = 0;
				movecounter = 0;
				shape.setTexture(&textures[moveDirection][movecounter]);
				playerPosition.x = obstaclesPos[i].x;
				playerPosition.y = obstaclesPos[i].y - 51;
			}
		}
	}
	*/
	
	shape.setPosition(position);
}

void Player::stop()
{
	this->move(STOPPED);
}
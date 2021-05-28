#include "Header.h"
#include "Enemy.h"

/*Initializers*/
void Enemy::initVariables(std::vector<sf::Vector2f> enemy_spawn_positions)
{
	/*Random Number Generator Seed*/
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);

	/*Movement Variables*/
	this->enemyDetails.velocity = sf::Vector2f(0.f, 0.f); 
	this->enemyDetails.maxVelocity = 3.f; 
	this->enemyDetails.acceleration = 0.2f; 
	this->enemyDetails.deceleration = 0.15f; 

	/*Spawn Position Vector*/
	std::cout << "Random Number: " << this->getRandomInt(0, enemy_spawn_positions.size()) << '\n';

	this->enemyDetails.enemySpawnPosition = enemy_spawn_positions[this->getRandomInt(0, enemy_spawn_positions.size())];

	/*Randomization Variables*/
	this->directionCounter = 0;
	this->randomDirectionNumber = this->getRandomInt(0, 4);

	/*Collision Variables*/
	this->playerCollisionBool = false;
	this->wallCollision = false;
}
void Enemy::initSpriteRect()
{
	this->spriteRect.setSize(sf::Vector2f(26.f, 32.f));
	this->spriteRect.setOutlineThickness(1.f);
	this->spriteRect.setOutlineColor(sf::Color::Red);
	this->spriteRect.setFillColor(sf::Color::Transparent);
	this->spriteRect.setOrigin(this->spriteRect.getGlobalBounds().width / 2.f, this->spriteRect.getGlobalBounds().height / 2.f);
}
void Enemy::initSprite()
{
	this->spriteIntRect = sf::IntRect(32, 0, 32, 32);
	this->setRandomEnemy();
	this->sprite.setTextureRect(this->spriteIntRect);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x - 2.f, this->spriteRect.getPosition().y - 1.f));
}

/*Constructor & Destructor*/
Enemy::Enemy(std::vector<sf::Vector2f> enemy_spawn_positions)
{
	this->initVariables(enemy_spawn_positions);
	this->initSpriteRect();
	this->initSprite();
}
Enemy::~Enemy()
{
}

/*Setters*/
void Enemy::setEnemyPosition()
{
	this->spriteRect.setPosition(this->enemyDetails.enemySpawnPosition);
}
void Enemy::setRandomEnemy()
{
	int randomNumber = this->getRandomInt(1, 28);

	switch (randomNumber)
	{
	case 1: 
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/1.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/1.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 1.f; 
		break;
	case 2:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/2.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/2.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 2.f;
		break;
	case 3:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/3.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/3.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 3.f;
		break;
	case 4:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/4.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/4.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 4.f;
		break;
	case 5:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/5.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/5.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 5.f;
		break;
	case 6:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/6.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/6.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 6.f;
		break;
	case 7:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/7.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/7.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 7.f;
		break;
	case 8:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/8.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/8.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 8.f;
		break;
	case 9:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/9.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/9.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 9.f;
		break;
	case 10:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/10.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/10.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 10.f;
		break;
	case 11:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/11.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/11.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 11.f;
		break;
	case 12:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/12.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/12.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 12.f;
		break;
	case 13:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/13.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/13.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 13.f;
		break;
	case 14:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/14.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/14.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 14.f;
		break;
	case 15:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/15.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/15.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 15.f;
		break;
	case 16:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/16.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/16.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 16.f;
		break;
	case 17:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/17.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/17.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 17.f;
		break;
	case 18:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/18.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/18.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 18.f;
		break;
	case 19:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/19.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/19.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 19.f;
		break;
	case 20:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/20.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/20.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 20.f;
		break;
	case 21:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/21.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/21.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 21.f;
		break;
	case 22:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/22.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/22.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 22.f;
		break;
	case 23:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/23.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/23.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 23.f;
		break;
	case 24:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/24.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/24.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 24.f;
		break;
	case 25:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/25.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/25.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 25.f;
		break;
	case 26:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/26.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/26.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 26.f;
		break;
	case 27:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/27.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/27.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 27.f;
		break;
	case 28:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/28.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/28.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 28.f;
		break;
	default:
		std::cout << "ERROR::ENEMY::void Enemy::setRandomEnemy()::Invalid Switch Entry!\n";
	}
}

/*Getters*/
int Enemy::getRandomInt(int min, int max)
{
	return rand() % max + min;
}
sf::RectangleShape Enemy::getSpriteRect()
{
	return this->spriteRect;
}
std::tuple<sf::RectangleShape, float> Enemy::getEnemyDamageAndRect()
{
	return std::make_tuple(this->spriteRect, this->enemyDetails.damage);
}

/*Tile Collisions Functions*/
void Enemy::tileCollision(std::tuple<bool, unsigned short> collision_tuple)
{
	if (std::get<0>(collision_tuple) == true && std::get<1>(collision_tuple) == TILEMAP::TileType::Wall)
	{
		this->wallCollision = true;
		std::cout << "Enemy/Wall Collision!" << '\n';
		this->randomDirectionNumber = 0;
	}
	else
		this->wallCollision = false;

	if (this->wallCollision == true)
	{
		sf::Vector2f position = this->spriteRect.getPosition();

		if (this->enemyDetails.velocity.x != 0.f)
		{
			position.x = this->oldPosition.x;
			this->enemyDetails.velocity.x = 0.f;
		}

		if (this->enemyDetails.velocity.y != 0.f)
		{
			position.y = this->oldPosition.y;
			this->enemyDetails.velocity.y = 0.f;
		}

		this->spriteRect.setPosition(position);
	}
}
void Enemy::playerCollision(sf::RectangleShape player_rect)
{
	if (this->spriteRect.getGlobalBounds().intersects(player_rect.getGlobalBounds()))
	{
		this->playerCollisionBool = true;
	}
	else
		this->playerCollisionBool = false; 

	if (this->playerCollisionBool == true)
	{
		sf::Vector2f position = this->spriteRect.getPosition();

		if (this->enemyDetails.velocity.x != 0.f)
		{
			this->enemyDetails.velocity.x = 0.f;
			position.x = this->oldPosition.x;
		}

		if (this->enemyDetails.velocity.y != 0.f)
		{
			this->enemyDetails.velocity.y = 0.f;
			position.y = this->oldPosition.y;
		}

		this->spriteRect.setPosition(position);
	}
}

/*Update Functions*/
void Enemy::updateRandomDirection(const float& dt)
{
		if (this->randomDirectionNumber == 0)
		{
			this->enemyDetails.currentDirection = EnemyDirection::Idle;
			this->updateVelocity(0.f, 0.f, dt);
		}
		else if (this->randomDirectionNumber == 1)
		{
			this->enemyDetails.currentDirection = EnemyDirection::Up;
			this->enemyDetails.oldDirection = EnemyDirection::Up;
			this->updateVelocity(0.f, -1.f, dt);
		}
		else if (this->randomDirectionNumber == 2)
		{
			this->enemyDetails.currentDirection = EnemyDirection::Down;
			this->enemyDetails.oldDirection = EnemyDirection::Down;
			this->updateVelocity(0.f, 1.f, dt);
		}
		else if (this->randomDirectionNumber == 3)
		{
			this->enemyDetails.currentDirection = EnemyDirection::Left;
			this->enemyDetails.oldDirection = EnemyDirection::Left;
			this->updateVelocity(-1.f, 0.f, dt);
		}
		else if (this->randomDirectionNumber == 4)
		{
			this->enemyDetails.currentDirection = EnemyDirection::Right;
			this->enemyDetails.oldDirection = EnemyDirection::Right;
			this->updateVelocity(1.f, 0.f, dt);
		}

		this->directionCounter++;

		if (this->directionCounter > 200)
		{
			this->randomDirectionNumber = this->getRandomInt(0, 4);

			this->directionCounter = 0;
		}
}
void Enemy::updateVelocity(float dir_x, float dir_y, const float& dt)
{
	this->enemyDetails.velocity.x += this->enemyDetails.acceleration * dir_x;
	this->enemyDetails.velocity.y += this->enemyDetails.acceleration * dir_y;

	this->updateMovement(dt);
}
void Enemy::updateMovement(const float& dt)
{
	/*Up*/
	if (this->enemyDetails.velocity.y < 0.f)
	{
		if (this->enemyDetails.velocity.y < -this->enemyDetails.maxVelocity)
			this->enemyDetails.velocity.y = -this->enemyDetails.maxVelocity;

		this->enemyDetails.velocity.y += this->enemyDetails.deceleration;

		if (this->enemyDetails.velocity.y > 0.f)
			this->enemyDetails.velocity.y = 0.f;
	}
	/*Down*/
	else if (this->enemyDetails.velocity.y > 0.f)
	{
		if (this->enemyDetails.velocity.y > this->enemyDetails.maxVelocity)
			this->enemyDetails.velocity.y = this->enemyDetails.maxVelocity;

		this->enemyDetails.velocity.y -= this->enemyDetails.deceleration;

		if (this->enemyDetails.velocity.y < 0.f)
			this->enemyDetails.velocity.y = 0.f;
	}

	/*Left*/
	if (this->enemyDetails.velocity.x < 0.f)
	{
		if (this->enemyDetails.velocity.x < -this->enemyDetails.maxVelocity)
			this->enemyDetails.velocity.x = -this->enemyDetails.maxVelocity;

		this->enemyDetails.velocity.x += this->enemyDetails.deceleration;

		if (this->enemyDetails.velocity.x > 0.f)
			this->enemyDetails.velocity.x = 0.f;
	}
	/*Right*/
	else if (this->enemyDetails.velocity.x > 0.f)
	{
		if (this->enemyDetails.velocity.x > this->enemyDetails.maxVelocity)
			this->enemyDetails.velocity.x = this->enemyDetails.maxVelocity;

		this->enemyDetails.velocity.x -= this->enemyDetails.deceleration;

		if (this->enemyDetails.velocity.x < 0.f)
			this->enemyDetails.velocity.x = 0.f;
	}

	this->oldPosition = this->spriteRect.getPosition();
	this->spriteRect.move(sf::Vector2f(this->enemyDetails.velocity.x, this->enemyDetails.velocity.y) * dt * (1.f / dt));
	this->updateAnimation();
}
void Enemy::updateAnimation()
{
	/*IntRect Variables*/
	int intRect_Left = 32;
	int intRect_Top = 32;
	int intRect_Width = 32;
	int intRect_Height = 32;


	int intRectTop_Up = 96;
	int intRectTop_Down = 0;
	int intRectTop_Left = 32;
	int intRectTop_Right = 64;

	int intRectLeft_Start = 0;
	int intRectLeft_End = 64;

	int intRectLeft_FrameSize = 32;

	sf::IntRect idleUp = sf::IntRect(intRect_Left, intRect_Top * 3, intRect_Width, intRect_Height);
	sf::IntRect idleDown = sf::IntRect(intRect_Left, intRect_Top * 0, intRect_Width, intRect_Height);
	sf::IntRect idleLeft = sf::IntRect(intRect_Left, intRect_Top, intRect_Width, intRect_Height);
	sf::IntRect idleRight = sf::IntRect(intRect_Left, intRect_Top * 2, intRect_Width, intRect_Height);


	/*Animation Switch Time Variables*/
	float deltaTime = this->animationClock.getElapsedTime().asSeconds();
	float switchTime = .1f;

	/*Movement "If" Statement*/
	if (deltaTime > switchTime)
	{
		if (this->enemyDetails.currentDirection == EnemyDirection::Up)
		{
			this->spriteIntRect.top = intRectTop_Up;

			if (this->spriteIntRect.left == intRectLeft_End)
				this->spriteIntRect.left = intRectLeft_Start;
			else
			{
				this->spriteIntRect.left += intRectLeft_FrameSize;
				this->sprite.setTextureRect(this->spriteIntRect);
				this->animationClock.restart();
			}
		}
		else if (this->enemyDetails.currentDirection == EnemyDirection::Down)
		{
			this->spriteIntRect.top = intRectTop_Down;

			if (this->spriteIntRect.left == intRectLeft_End)
				this->spriteIntRect.left = intRectLeft_Start;
			else
			{
				this->spriteIntRect.left += intRectLeft_FrameSize;
				this->sprite.setTextureRect(this->spriteIntRect);
				this->animationClock.restart();
			}
		}
		else if (this->enemyDetails.currentDirection == EnemyDirection::Left)
		{
			this->spriteIntRect.top = intRectTop_Left;

			if (this->spriteIntRect.left == intRectLeft_End)
				this->spriteIntRect.left = intRectLeft_Start;
			else
			{
				this->spriteIntRect.left += intRectLeft_FrameSize;
				this->sprite.setTextureRect(this->spriteIntRect);
				this->animationClock.restart();
			}
		}
		else if (this->enemyDetails.currentDirection == EnemyDirection::Right)
		{
			this->spriteIntRect.top = intRectTop_Right;

			if (this->spriteIntRect.left == intRectLeft_End)
				this->spriteIntRect.left = intRectLeft_Start;
			else
			{
				this->spriteIntRect.left += intRectLeft_FrameSize;
				this->sprite.setTextureRect(this->spriteIntRect);
				this->animationClock.restart();
			}
		}
		else if (this->enemyDetails.currentDirection == EnemyDirection::Idle)
		{
			if (this->enemyDetails.oldDirection == EnemyDirection::Up)
			{
				this->spriteIntRect = idleUp;
				this->sprite.setTextureRect(this->spriteIntRect);
			}
			else if (this->enemyDetails.oldDirection == EnemyDirection::Down)
			{
				this->spriteIntRect = idleDown;
				this->sprite.setTextureRect(this->spriteIntRect);
			}
			else if (this->enemyDetails.oldDirection == EnemyDirection::Left)
			{
				this->spriteIntRect = idleLeft;
				this->sprite.setTextureRect(this->spriteIntRect);
			}
			else if (this->enemyDetails.oldDirection == EnemyDirection::Right)
			{
				this->spriteIntRect = idleRight;
				this->sprite.setTextureRect(this->spriteIntRect);
			}
		}
	}
}
void Enemy::update(const float& dt)
{
	
	this->updateRandomDirection(dt);


	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x - 2.f, this->spriteRect.getPosition().y - 1.f));
}

/*Render Functions*/
void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

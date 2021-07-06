#include "Header.h"
#include "Enemy.h"

/*Initializers*/
void Enemy::initVariables(std::vector<sf::Vector2f> enemy_spawn_positions, std::vector<sf::Vector2f> path_finder_markings)
{
	/*Random Number Generator Seed*/
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);

	/*Emote State*/
	this->enemyDetails.emoteState = EmoteStates::Default;

	/*Movement Variables*/
	this->enemyDetails.velocity = sf::Vector2f(0.f, 0.f); 
	this->enemyDetails.maxVelocity = 384.f; 
	this->enemyDetails.acceleration = 26.f; 
	this->enemyDetails.deceleration = 19.f; 

	/*Spawn Random Position Vector*/
	this->enemyDetails.enemySpawnPosition = enemy_spawn_positions[this->getRandomInt(0, enemy_spawn_positions.size())];
	//std::cout << "Random Number: " << this->getRandomInt(0, enemy_spawn_positions.size()) << '\n';

	/*Path Finder Markings*/
	this->enemyDetails.pathFinderMarkings = path_finder_markings;

	/*Randomization Variables*/
	this->randomDirectionCounter = 0;
	this->randomDirectionNumber = this->getRandomInt(0, 5);

	/*Audio*/
	this->playEmoteSFX = false;

	/*Collision Variables*/
	this->projectileCollisionBool = false;
	this->playerCollisionBool = false;
	this->alertCircleCollisionBool = false;
	this->playerCollisionBool = false;
	this->wallCollision = false;

	/*Destroy Variables*/
	this->destroy = false;

	/*AI Variables*/
	this->goingAroundWall = false;
	this->attackPlayer = false;
	this->directionNumber = 0;

	/*Emote Variables*/
	this->emoteCounter = 0;
}
void Enemy::initSpriteRect()
{
	/*Enemy Sprite Rect*/
	this->spriteRect.setSize(sf::Vector2f(26.f, 32.f));
	this->spriteRect.setOutlineThickness(1.f);
	this->spriteRect.setOutlineColor(sf::Color::Red);
	this->spriteRect.setFillColor(sf::Color::Transparent);
	this->spriteRect.setOrigin(this->spriteRect.getGlobalBounds().width / 2.f, this->spriteRect.getGlobalBounds().height / 2.f);

	/*Alert Circle*/
	this->alertCircle = sf::CircleShape(200);
	this->alertCircle.setOutlineThickness(1.f);
	this->alertCircle.setOutlineColor(sf::Color::Transparent);
	this->alertCircle.setFillColor(sf::Color::Transparent);
	this->alertCircle.setOrigin(this->alertCircle.getGlobalBounds().width / 2.f, this->alertCircle.getGlobalBounds().height / 2.f);
	this->alertCircle.setPosition(this->spriteRect.getPosition());
}
void Enemy::initSprite()
{
	/*Enemy Sprite*/
	this->spriteIntRect = sf::IntRect(32, 0, 32, 32);
	this->setRandomEnemy();
	this->sprite.setTextureRect(this->spriteIntRect);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x - 2.f, this->spriteRect.getPosition().y - 1.f));

	/*Emote Sprite*/
	this->emoteIntRect = sf::IntRect(0, 0, 32, 32);
	this->emoteSprite.setTextureRect(this->emoteIntRect);
	this->emoteSprite.setOrigin(this->emoteSprite.getGlobalBounds().width / 2.f, this->emoteSprite.getGlobalBounds().height / 2.f);
	this->emoteSprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y - 50.f));
}

/*Constructor & Destructor*/
Enemy::Enemy(std::vector<sf::Vector2f> enemy_spawn_positions, std::vector<sf::Vector2f> path_finder_markings, std::map<std::string, std::unique_ptr<Audio>>& audio_map)
	:Entity(audio_map)
{
	this->initVariables(enemy_spawn_positions, path_finder_markings);
	this->initSpriteRect();
	this->initSprite();
}
Enemy::~Enemy()
{
}

/*Setters*/
void Enemy::setDestroy(bool destroy)
{
	this->destroy = destroy;
}
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
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 1.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 2:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/2.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/2.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 2.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 3:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/3.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/3.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 3.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 4:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/4.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/4.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 4.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 5:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/5.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/5.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 5.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 6:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/6.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/6.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 6.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 7:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/7.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/7.png");
		sprite.setTexture(this->texture);
		this->enemyDetails.damage = 7.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 8:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/8.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/8.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 8.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 9:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/9.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/9.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 9.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 10:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/10.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/10.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 10.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 11:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/11.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/11.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 11.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 12:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/12.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/12.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 12.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 13:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/13.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/13.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 13.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 14:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/14.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/14.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 14.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 15:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/15.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/15.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 15.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 16:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/16.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/16.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 16.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 17:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/17.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/17.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 17.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 18:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/18.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/18.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 18.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 19:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/19.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/19.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 19.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 20:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/20.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/20.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 20.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 21:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/21.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/21.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 21.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 22:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/22.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/22.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 22.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 23:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/23.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/23.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 23.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 24:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/24.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/24.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 24.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 25:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/25.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/25.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 25.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 26:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/26.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/26.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 26.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 27:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/27.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/27.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 27.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	case 28:
		if (!this->texture.loadFromFile("Resources/Images/Characters/Soldier/28.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::Soldier/28.png");
		this->sprite.setTexture(this->texture);
		this->enemyDetails.damage = 28.f;
		this->enemyDetails.maxHP = this->getRandomInt(50, 100);
		this->enemyDetails.currentHP = this->enemyDetails.maxHP;
		break;
	default:
		std::cout << "ERROR::ENEMY::void Enemy::setRandomEnemy()::Invalid Switch Entry!\n";
	}
}
void Enemy::setEmoteState(EmoteStates emote_state)
{
	switch (emote_state)
	{
	case EmoteStates::Default:
		break;
	case EmoteStates::Alert_1:
		if (!this->emoteTexture.loadFromFile("Resources/Images/Emotes/alert.png"))
			throw("ERROR::ENEMY::FAILED_TO_LOAD::alert.png");
		this->emoteSprite.setTexture(this->emoteTexture);
		break;
	default:
		throw("ERROR::ENEMY::void Enemy::setEmoteState(EmoteStates emote_state)::INVALID_ENTRY");
	}
}

/*Getters*/
bool Enemy::getDestroy()
{
	return this->destroy;
}
int Enemy::getRandomInt(int min, int max)
{
	return rand() % max + min;
}
sf::RectangleShape Enemy::getSpriteRect()
{
	return this->spriteRect;
}
std::tuple<sf::RectangleShape, float, bool> Enemy::getSpriteRectDamageAttackPlayerBool()
{
	return std::make_tuple(this->spriteRect, this->enemyDetails.damage, this->attackPlayer);
}

/*Collisions Functions*/
void Enemy::projectileCollision(std::tuple<sf::RectangleShape, int> collision_tuple)
{
	if (std::get<0>(collision_tuple).getGlobalBounds().intersects(this->spriteRect.getGlobalBounds()))
	{
		this->projectileCollisionBool = true;
		std::cout << "Enemy/Wall Collison (from ENEMY!)\n";
	}
	else
		this->projectileCollisionBool = false; 

	if (this->projectileCollisionBool)
	{
		this->enemyDetails.currentHP -= std::get<1>(collision_tuple);

		if (this->enemyDetails.currentHP < 0)
			this->enemyDetails.currentHP = 0;

		std::cout << "Enemy HP: " << this->enemyDetails.currentHP << '\n';
	}

	if (this->enemyDetails.currentHP == 0)
		this->destroy = true; 
}
void Enemy::tileCollision(std::tuple<bool, unsigned short, std::string_view> collision_tuple)
{
	if (std::get<1>(collision_tuple) == TILEMAP::TileType::Wall || std::get<1>(collision_tuple) == TILEMAP::TileType::Invisible_Wall)
	{
		this->wallCollision = true;
		std::cout << "Enemy/Wall Collision!" << '\n';
		this->randomDirectionNumber = 0;
	}
	else
		this->wallCollision = false;

	if (this->wallCollision && this->attackPlayer)
	{
		this->goingAroundWall = true;
		this->lastDirection = enemyDetails.currentDirection;
	}

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
void Enemy::alertCircleCollision(sf::RectangleShape player_rect)
{
	if (this->alertCircle.getGlobalBounds().intersects(player_rect.getGlobalBounds()))
	{
		this->alertCircleCollisionBool = true;
		this->attackPlayer = true;
		this->playEmoteSFX = true;
		//std::cout << "Alert Circle Player Collision Bool: " << this->alertCircleCollisionBool << '\n';
	}
	else if (!this->alertCircle.getGlobalBounds().intersects(player_rect.getGlobalBounds()))
	{
		this->alertCircleCollisionBool = false;
		this->playEmoteSFX = false;
		//std::cout << "Alert Circle Player Collision Bool: " << this->alertCircleCollisionBool << '\n';
	}

	if (this->alertCircleCollisionBool)
	{
		this->enemyDetails.emoteState = EmoteStates::Alert_1;
		this->setEmoteState(this->enemyDetails.emoteState);
	}
	else if (!this->alertCircleCollisionBool)
	{
		this->enemyDetails.emoteState = EmoteStates::Default;
		this->setEmoteState(this->enemyDetails.emoteState);
	}
}

/*Update Functions*/
void Enemy::updatePath(sf::RectangleShape player_rect, const float& dt)
{
	std::vector<sf::Vector2f> closestX;
	bool swappedClosestX = false;
	do {
		swappedClosestX = false;
		for (unsigned int i = 0; i < this->enemyDetails.pathFinderMarkings.size(); i++)
		{
			for (auto itj = this->enemyDetails.pathFinderMarkings.begin(); itj != this->enemyDetails.pathFinderMarkings.end() - 1; itj = std::next(itj))
			{
				if (std::abs(player_rect.getPosition().x - (*itj).x) > std::abs(player_rect.getPosition().x - (*std::next(itj)).x))
				{
					std::swap(*itj, *std::next(itj));
					swappedClosestX = true;
				}
			}
		}
	} while (swappedClosestX);

	closestX = this->enemyDetails.pathFinderMarkings;

	std::vector<sf::Vector2f> closestY;
	bool swappedClosestY = false;
	do {
		swappedClosestY = false;
		for (unsigned int i = 0; i < this->enemyDetails.pathFinderMarkings.size(); i++)
		{
			for (auto itj = this->enemyDetails.pathFinderMarkings.begin(); itj != this->enemyDetails.pathFinderMarkings.end() - 1; itj = std::next(itj))
			{
				if (std::abs(player_rect.getPosition().y - (*itj).y) > std::abs(player_rect.getPosition().y - (*std::next(itj)).y))
				{
					std::swap(*itj, *std::next(itj));
					swappedClosestY = true;
				}
			}
		}
	} while (swappedClosestY);

	closestY = this->enemyDetails.pathFinderMarkings;

	sf::Vector2f enemyPosition;

	enemyPosition = this->spriteRect.getPosition();

	float remainderX_X = std::abs(enemyPosition.x - closestX[0].x);
	float remainderY_Y = std::abs(enemyPosition.y - closestY[0].y);

	
	if (this->lastDirection == EnemyDirection::Left || this->lastDirection == EnemyDirection::Right)
	{
		if (remainderY_Y > 10.f)
		{
			if (enemyPosition.y > closestY[0].y)
			{
				this->directionNumber = 1;
				this->updateAIAttackMovement(dt);
			}
			else if (enemyPosition.y < closestY[0].y)
			{
				this->directionNumber = 2;
				this->updateAIAttackMovement(dt);
			}
		}
		else if (remainderY_Y < 10.f)
		{
			if (enemyPosition.x > closestY[0].x)
			{
				this->directionNumber = 3;
				this->updateAIAttackMovement(dt);
			}
			else if (enemyPosition.x < closestY[0].x)
			{
				this->directionNumber = 4;
				this->updateAIAttackMovement(dt);
			}
		}
		if (std::abs(enemyPosition.x - closestY[0].x) < 10.f && std::abs(enemyPosition.y - closestY[0].y) < 10.f)
			this->goingAroundWall = false;
	}
		
	if (this->lastDirection == EnemyDirection::Up || this->lastDirection == EnemyDirection::Down)
	{
		if (remainderX_X > 10.f)
		{
			if (enemyPosition.x > closestX[0].x)
			{
				this->directionNumber = 3;
				this->updateAIAttackMovement(dt);
			}
			else if (enemyPosition.x < closestX[0].x)
			{
				this->directionNumber = 4;
				this->updateAIAttackMovement(dt);
			}
		}
		else if (remainderX_X < 10.f)
		{
			if (enemyPosition.y > closestX[0].y)
			{
				this->directionNumber = 1;
				this->updateAIAttackMovement(dt);
			}
			else if (enemyPosition.y < closestX[0].y)
			{
				this->directionNumber = 2;
				this->updateAIAttackMovement(dt);   
			}
		}	
		if(std::abs(enemyPosition.x - closestX[0].x) < 10.f && std::abs(enemyPosition.y - closestX[0].y) < 10.f)
			this->goingAroundWall = false;
	}
}
void Enemy::updateAIDirection(sf::RectangleShape player_rect, const float& dt)
{
	sf::Vector2f playerPosition; 

	playerPosition = player_rect.getPosition();

	sf::Vector2f enemyPosition;

	enemyPosition = this->spriteRect.getPosition(); 

	float remainderX = std::abs(playerPosition.x - enemyPosition.x); 

	if (this->goingAroundWall)
	{
		this->updatePath(player_rect, dt);
		
	}
	else if (!this->goingAroundWall)
	{
		if (remainderX > 20.f)
		{
			if (playerPosition.x > enemyPosition.x)
			{
				this->directionNumber = 4;
				this->updateAIAttackMovement(dt);
			}
			else if (playerPosition.x < enemyPosition.x)
			{
				this->directionNumber = 3;
				this->updateAIAttackMovement(dt);
			}
		}
		else if (remainderX < 20.f)
		{
			if (playerPosition.y > enemyPosition.y)
			{
				this->directionNumber = 2;
				this->updateAIAttackMovement(dt);
			}
			else if (playerPosition.y < enemyPosition.y)
			{
				this->directionNumber = 1;
				this->updateAIAttackMovement(dt);
			}
		}
	}
}
void Enemy::updateAIAttackMovement(const float& dt)
{
	if (this->directionNumber == 1)
		{
		this->enemyDetails.currentDirection = EnemyDirection::Up;
		this->enemyDetails.oldDirection = EnemyDirection::Up;
		this->updateVelocity(0.f, -1.f, dt);
		}
	else if (this->directionNumber == 2)
		{
		this->enemyDetails.currentDirection = EnemyDirection::Down;
		this->enemyDetails.oldDirection = EnemyDirection::Down;
		this->updateVelocity(0.f, 1.f, dt);
		}
	else if (this->directionNumber == 3)
		{
		this->enemyDetails.currentDirection = EnemyDirection::Left;
		this->enemyDetails.oldDirection = EnemyDirection::Left;
		this->updateVelocity(-1.f, 0.f, dt);
		}
	else if (this->directionNumber == 4)
		{
		this->enemyDetails.currentDirection = EnemyDirection::Right;
		this->enemyDetails.oldDirection = EnemyDirection::Right;
		this->updateVelocity(1.f, 0.f, dt);
		}
}
void Enemy::updateEmoteAnimation()
{
	int intRectLeft_Start = 0;
	int intRectLeft_Middle = 32;
	int intRectLeft_End = 64;

	int intRectLeft_FrameSize = 32;

	float deltaTime = this->emoteAnimationClock.getElapsedTime().asSeconds();
	float switchTime = 0.1f;

	int counter = 0;

	if (deltaTime > switchTime)
	{
		if (this->enemyDetails.emoteState == EmoteStates::Alert_1)
		{
			if (this->emoteIntRect.left == intRectLeft_Start)
			{
				counter = 1;
				this->emoteCounter += 1;
				this->emoteIntRect.left += intRectLeft_FrameSize;
				this->emoteSprite.setTextureRect(this->emoteIntRect);
				this->emoteAnimationClock.restart();
			}
			else if (this->emoteIntRect.left == intRectLeft_Middle & counter == 1)
			{
				this->emoteIntRect.left += intRectLeft_FrameSize;
				this->emoteSprite.setTextureRect(this->emoteIntRect);
				this->emoteAnimationClock.restart();
			}
			else if (this->emoteIntRect.left == intRectLeft_Middle & counter == 0)
			{
				this->emoteIntRect.left -= intRectLeft_FrameSize;
				this->emoteSprite.setTextureRect(this->emoteIntRect);
				this->emoteAnimationClock.restart();
			}
			else if (this->emoteIntRect.left == intRectLeft_End)
			{
				counter = 0;
				this->emoteIntRect.left -= intRectLeft_FrameSize;
				this->emoteSprite.setTextureRect(this->emoteIntRect);
				this->emoteAnimationClock.restart();
			}
		}
	}
}
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

		this->randomDirectionCounter++;

		if (this->randomDirectionCounter > 200)
		{
			this->randomDirectionNumber = this->getRandomInt(0, 5);

			this->randomDirectionCounter = 0;
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
	this->spriteRect.move(sf::Vector2f(this->enemyDetails.velocity.x * dt, this->enemyDetails.velocity.y * dt));
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
void Enemy::updateAudio()
{
	int deltaTime = this->emoteSFXClock.getElapsedTime().asSeconds();
	int switchTime = 0.1f;

	if (this->playEmoteSFX && this->emoteCounter < 5)
	{
		if (deltaTime > switchTime)
		{
			this->audioMap["ENEMY_ALERT_1"]->play();
			this->emoteSFXClock.restart();
		}
	}
}
void Enemy::update(sf::RectangleShape player_rect, const float& dt)
{
	/*Attack Player or Random Direction*/
	if (this->attackPlayer)
		this->updateAIDirection(player_rect, dt);
	else if (!this->attackPlayer)
		this->updateRandomDirection(dt);

	/*Audio*/
	this->updateAudio();

	/*Emotes*/
	this->updateEmoteAnimation();
	this->emoteSprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y - 50.f));

	/*Update Sprite & Shape Positions*/
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x - 2.f, this->spriteRect.getPosition().y - 1.f));
	this->alertCircle.setPosition(this->spriteRect.getPosition());
}

/*Render Functions*/
void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	target.draw(this->alertCircle);

	if (this->alertCircleCollisionBool && this->emoteCounter < 5)
		target.draw(this->emoteSprite);
}

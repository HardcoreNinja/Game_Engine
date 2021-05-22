#include "Header.h"
#include "Projectile.h"
#include "TileMap.h"

/*Initializers*/
void Projectile::initVariables()
{
	this->maxvelocity = 10.f;
	this->destroy = false;
	this->lifeTimeCounter = 0;
	this->maxLifeTimeCounter = 50;
	this->wallCollision = false;
}
void Projectile::initSpriteRect()
{
	this->spriteRect.setSize(sf::Vector2f(111.f, 137.f));
	this->spriteRect.setOutlineThickness(1.f);
	this->spriteRect.setOutlineColor(sf::Color::Red);
	this->spriteRect.setFillColor(sf::Color::Transparent);
	this->spriteRect.setOrigin(this->spriteRect.getGlobalBounds().width / 2.f, this->spriteRect.getGlobalBounds().height / 2.f);
	this->spriteRect.scale(sf::Vector2f(.5, .5));
}
void Projectile::initSprite()
{
	this->spriteIntRect = sf::IntRect(0, 0, 192, 192);
	if(!this->texture.loadFromFile("Resources/Images/Energy_Tornados/black.png"))
		throw("ERROR::PROJECTILE::FAILED_TO_LOAD::black.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->spriteIntRect);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
	this->sprite.scale(sf::Vector2f(.5, .5));
}

/*Constructor & Destructor*/
Projectile::Projectile()
{
	this->initVariables();
	this->initSpriteRect();
	this->initSprite();
}
Projectile::~Projectile()
{
}

/*Getters*/
bool Projectile::getDestroy()
{
		return this->destroy;
}
sf::RectangleShape Projectile::getSpriteRect()
{
	return this->spriteRect;
}

/*Setters*/
void Projectile::setProjectileType(ProjectileTypes projectile_type)
{
	this->projectileType  = projectile_type;

	switch (this->projectileType)
	{
	case ProjectileTypes::Black_Tornado_0:
		if (!this->texture.loadFromFile("Resources/Images/Energy_Tornados/black.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::black.png");
		break;
	case ProjectileTypes::Blue_Tornado_1:
		if (!this->texture.loadFromFile("Resources/Images/Energy_Tornados/blue.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::blue.png");
		break;
	case ProjectileTypes::Brown_Tornado_2:
		if (!this->texture.loadFromFile("Resources/Images/Energy_Tornados/brown.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::brown.png");
		break;
	case ProjectileTypes::Green_Tornado_3:
		if (!this->texture.loadFromFile("Resources/Images/Energy_Tornados/green.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::green.png");
		break;
	case ProjectileTypes::Red_Tornado_4:
		if (!this->texture.loadFromFile("Resources/Images/Energy_Tornados/red.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::red.png");
		break;
	}
}
void Projectile::setProjectileDirection(int player_direction)
{
	switch (player_direction)
	{
		case 0:
			this->projectileDirection = ProjectileDirection::Idle;
			break;
		case 1:
			this->projectileDirection = ProjectileDirection::Up;
			break;
		case 2:
			this->projectileDirection = ProjectileDirection::Down;
			break;
		case 3:
			this->projectileDirection = ProjectileDirection::Left;
			break;
		case 4: 
			this->projectileDirection = ProjectileDirection::Right;
			break;
	    default:
			std::cout << "PROJECTILE:: void getPlayerDirection():: INVALID ENTRY...\n";
			break;
	}
}
void Projectile::setProjectilePosition(sf::RectangleShape player)
{
	this->spriteRect.setPosition(player.getPosition());
}

/*Tile Collision Functions*/
void Projectile::tileCollision(std::tuple<bool, unsigned short> collision_tuple)
{
	if (std::get<0>(collision_tuple) == true && std::get<1>(collision_tuple) == TILEMAP::TileType::Wall)
	{
		this->wallCollision = true;
		std::cout << "Projectile/Wall Collision: " << this->wallCollision << '\n';
	}
	else
		this->wallCollision = false;

	if (this->wallCollision)
		this->destroy = true;
	else
		this->destroy = false;
}

/*Update Functions*/
void Projectile::updateMovement(const float& dt)
{
	if (this->projectileDirection == ProjectileDirection::Up)
	{
		this->spriteRect.move(0.f, -this->maxvelocity * dt * (1.f / dt));
	}
	else if (this->projectileDirection == ProjectileDirection::Down)
	{
		this->spriteRect.move(0.f, this->maxvelocity * dt * (1.f / dt));
	}
	else if (this->projectileDirection == ProjectileDirection::Left)
	{
		this->spriteRect.move(-this->maxvelocity * dt * (1.f / dt), 0.f);
	}
	else if (this->projectileDirection == ProjectileDirection::Right)
	{
		this->spriteRect.move(this->maxvelocity * dt * (1.f / dt), 0.f);
	}
}
void Projectile::updateLifeTimeCounter()
{
	++this->lifeTimeCounter;

	if (this->lifeTimeCounter > this->maxLifeTimeCounter)
	{
		this->destroy = true;
		this->lifeTimeCounter = 0;
	}
	else 
		this->destroy = false;
	


}
void Projectile::updateAnimation()
{
	/*IntRect Variables*/
	int intRectLeft_Start = 0;
	int intRectLeft_End = 768;

	int intRectTop_Start = 0;
	int intRectTop_End = 576;

	int intRect_FrameSize = 192;

	/*Animation Switch Time Variables*/
	float deltaTime = this->animationClock.getElapsedTime().asSeconds();
	float switchTime = 0.01;

	if (deltaTime > switchTime)
	{
		if (this->spriteIntRect.left == intRectLeft_End)
		{
			this->spriteIntRect.left = intRectLeft_Start;
			this->spriteIntRect.top += intRect_FrameSize;

			if (this->spriteIntRect.top == intRectTop_End)
				this->spriteIntRect.top = intRectTop_Start;
		}
		else
		{
			this->spriteIntRect.left += intRect_FrameSize;
			this->sprite.setTextureRect(this->spriteIntRect);
			this->animationClock.restart();
		}
	}
}
void Projectile::update(const float& dt)
{
	this->updateMovement(dt);
	this->updateLifeTimeCounter();
	this->updateAnimation();
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y));
}

/*Render Functions*/
void Projectile::render(sf::RenderTarget& target)
{
	target.draw(this->spriteRect);
	target.draw(this->sprite);
}

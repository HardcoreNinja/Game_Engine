#include "Header.h"
#include "Projectile.h"
#include "TileMap.h"

/*Initializers*/
void Projectile::initVariables()
{
	this->maxvelocity = 5.f;
	this->stop = false;
	this->destroy = false;
	this->lifeTimeCounter = 0;
	this->maxLifeTimeCounter = 50;
	this->explode = false;
	this->wallCollision = false;
}
void Projectile::initSpriteRect()
{
	this->spriteRect.setSize(sf::Vector2f(111.f, 137.f));
	this->spriteRect.setOutlineThickness(1.f);
	this->spriteRect.setOutlineColor(sf::Color::Transparent);
	this->spriteRect.setFillColor(sf::Color::Transparent);
	this->spriteRect.setOrigin(this->spriteRect.getGlobalBounds().width / 2.f, this->spriteRect.getGlobalBounds().height / 2.f);
	this->spriteRect.scale(sf::Vector2f(.35, .35));
}
void Projectile::initSprite()
{
	/*Projectile*/
	this->spriteIntRect = sf::IntRect(0, 0, 192, 192);
	if(!this->texture.loadFromFile("Resources/Images/Energy_Tornados/black.png"))
		throw("ERROR::PROJECTILE::FAILED_TO_LOAD::black.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->spriteIntRect);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
	this->sprite.scale(sf::Vector2f(.35, .35));

	/*Explosion*/
	this->explosionIntRect = sf::IntRect(0, 0, 100, 100);
	if (!this->explosionTexture.loadFromFile("Resources/Images/Explosions/blue.png"))
		throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/blue.png");
	this->explosionTexture.setSmooth(true);
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
	if(this->projectileDirection == ProjectileDirection::Up)
	this->spriteRect.setPosition(player.getPosition().x, player.getPosition().y - 25.f);
	if (this->projectileDirection == ProjectileDirection::Down)
		this->spriteRect.setPosition(player.getPosition().x, player.getPosition().y + 25.f);
	if (this->projectileDirection == ProjectileDirection::Left)
		this->spriteRect.setPosition(player.getPosition().x - 25.f, player.getPosition().y);
	if (this->projectileDirection == ProjectileDirection::Right)
		this->spriteRect.setPosition(player.getPosition().x + 25.f, player.getPosition().y);
}
void Projectile::setExplosionTexture()
{
	this->sprite.scale(sf::Vector2f(1.025, 1.025));
	this->sprite.setTextureRect(this->explosionIntRect);
	this->sprite.setTexture(this->explosionTexture);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
	this->stop = true;
	this->explode = true;
}

/*Tile Collision Functions*/
void Projectile::tileCollision(std::tuple<bool, unsigned short> collision_tuple)
{
	if (std::get<0>(collision_tuple) == true && std::get<1>(collision_tuple) == TILEMAP::TileType::Wall)
	{
		std::cout << "Projectile/Wall Collision: " << this->wallCollision << '\n';
		this->wallCollision = true;
		this->setExplosionTexture();
	}
	else
		this->wallCollision = false;
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
		this->setExplosionTexture();
}
void Projectile::updateProjectileAnimation()
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
void Projectile::updateExplosionAnimation()
{
	/*IntRect Variables*/
	int intRectLeft_Start = 0;
	int intRectLeft_End = 1300;

	int intRectTop_Start = 0;
	int intRectTop_End = 300;

	int intRect_FrameSize = 100;

	/*Animation Switch Time Variables*/
	float deltaTime = this->explosionAnimationClock.getElapsedTime().asSeconds();
	float switchTime = 0.001;

	if (deltaTime > switchTime)
	{
		if (this->explosionIntRect.left == intRectLeft_End && this->explosionIntRect.top == intRectTop_End)
			this->destroy = true;

		if (this->explosionIntRect.left == intRectLeft_End)
		{
			this->explosionIntRect.left = intRectLeft_Start;
			this->explosionIntRect.top += intRect_FrameSize;
		}
		else
		{
			this->explosionIntRect.left += intRect_FrameSize;
			this->sprite.setTextureRect(this->explosionIntRect);
			this->explosionAnimationClock.restart();
		}
	}
}
void Projectile::update(const float& dt)
{
	if(!this->stop)
	this->updateMovement(dt);

	this->updateLifeTimeCounter();
	this->updateProjectileAnimation();
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y));

	if (this->explode)
		this->updateExplosionAnimation();
}

/*Render Functions*/
void Projectile::render(sf::RenderTarget& target)
{
	target.draw(this->spriteRect);
	target.draw(this->sprite);
}

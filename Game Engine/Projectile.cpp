#include "Header.h"
#include "Projectile.h"

/*Initializers*/
void Projectile::initVariables()
{
	/*Movement Variables*/
	this->projectileDetails.velocity = sf::Vector2f(0.f, 0.f);
	this->projectileDetails.maxVelocity = 8.f;
	this->projectileDetails.acceleration = 1.f;
	this->projectileDetails.deceleration = 0.1f;
	this->stop = false;

	/*Destroy Variables*/
	this->destroy = false;
	this->projectileDetails.lifeTimeCounter = 0;
	this->projectileDetails.maxLifeTimeCounter = 100;

	/*Explosion Variables*/
	this->explode = false;

	/*Collision Variables*/
	this->wallCollision = false;
}
void Projectile::initSpriteRect()
{
	this->spriteRect.setSize(sf::Vector2f(111.f, 137.f));
	this->spriteRect.setOutlineThickness(1.f);
	this->spriteRect.setOutlineColor(sf::Color::Transparent);
	this->spriteRect.setFillColor(sf::Color::Transparent);
	this->spriteRect.setOrigin(this->spriteRect.getGlobalBounds().width / 2.f, this->spriteRect.getGlobalBounds().height / 2.f);
	this->spriteRect.setScale(sf::Vector2f(.35, .35));
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
	this->sprite.setScale(sf::Vector2f(.35, .35));

	/*Explosion*/
	this->projectileDetails.explosionIntRect = sf::IntRect(0, 0, 100, 100);
	if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/blue.png"))
		throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/blue.png");
	this->projectileDetails.explosionTexture.setSmooth(true);
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
	this->projectileDetails.projectileType  = projectile_type;

	switch (this->projectileDetails.projectileType)
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
void Projectile::setProjectileDirection(PlayerDirection player_direction)
{
	switch (player_direction)
	{
		case PlayerDirection::Idle:
			this->projectileDetails.projectileDirection = ProjectileDirection::Idle;
			break;
		case PlayerDirection::Up:
			this->projectileDetails.projectileDirection = ProjectileDirection::Up;
			break;
		case PlayerDirection::Down:
			this->projectileDetails.projectileDirection = ProjectileDirection::Down;
			break;
		case PlayerDirection::Left:
			this->projectileDetails.projectileDirection = ProjectileDirection::Left;
			break;
		case PlayerDirection::Right:
			this->projectileDetails.projectileDirection = ProjectileDirection::Right;
			break;
	    default:
			std::cout << "PROJECTILE:: void getPlayerDirection():: INVALID ENTRY...\n";
			break;
	}
}
void Projectile::setProjectilePosition(sf::RectangleShape player)
{
	if(this->projectileDetails.projectileDirection == ProjectileDirection::Up)
	this->spriteRect.setPosition(player.getPosition().x, player.getPosition().y - 50.f);
	if (this->projectileDetails.projectileDirection == ProjectileDirection::Down)
		this->spriteRect.setPosition(player.getPosition().x, player.getPosition().y + 50.f);
	if (this->projectileDetails.projectileDirection == ProjectileDirection::Left)
		this->spriteRect.setPosition(player.getPosition().x - 50.f, player.getPosition().y);
	if (this->projectileDetails.projectileDirection == ProjectileDirection::Right)
		this->spriteRect.setPosition(player.getPosition().x + 50.f, player.getPosition().y);
}
void Projectile::setExplosionTexture()
{
	this->sprite.setTextureRect(this->projectileDetails.explosionIntRect);
	this->sprite.setTexture(this->projectileDetails.explosionTexture);
	this->sprite.setScale(sf::Vector2f(1.f, 1.f));
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
	this->stop = true;
	this->explode = true;
}

/*Tile Collision Functions*/
void Projectile::tileCollision(std::tuple<bool, unsigned short> collision_tuple)
{
	if (std::get<0>(collision_tuple) == true && std::get<1>(collision_tuple) == TILEMAP::TileType::Wall)
	{
		this->wallCollision = true;
		std::cout << "Projectile/Wall Collision: " << this->wallCollision << '\n';
		this->setExplosionTexture();
	}
	else
		this->wallCollision = false;

	if (this->wallCollision == true)
	{
		sf::Vector2f position = this->spriteRect.getPosition();

		if (this->projectileDetails.velocity.x != 0.f)
		{
			position.x = this->oldPosition.x;
			this->projectileDetails.velocity.x = 0.f;
		}

		if (this->projectileDetails.velocity.y != 0.f)
		{
			position.y = this->oldPosition.y;
			this->projectileDetails.velocity.y = 0.f;
		}

		this->spriteRect.setPosition(position);
	}
}

/*Update Functions*/
void Projectile::updateDirection(const float& dt)
{
	if (this->projectileDetails.projectileDirection == ProjectileDirection::Up)
	{
		this->updateVelocity(0.f, -1.f, dt);
	}
	else if (this->projectileDetails.projectileDirection == ProjectileDirection::Down)
	{
		this->updateVelocity(0.f, 1.f, dt);
	}
	else if (this->projectileDetails.projectileDirection == ProjectileDirection::Left)
	{
		this->updateVelocity(-1.f, 0.f, dt);
	}
	else if (this->projectileDetails.projectileDirection == ProjectileDirection::Right)
	{
		this->updateVelocity(1.f, 0.f, dt);
	}
}
void Projectile::updateVelocity(float dir_x, float dir_y, const float& dt)
{
	this->projectileDetails.velocity.x += this->projectileDetails.acceleration * dir_x;
	this->projectileDetails.velocity.y += this->projectileDetails.acceleration * dir_y;

	this->updateMovement(dt);
}
void Projectile::updateMovement(const float& dt)
{
	/*Up*/
	if (this->projectileDetails.velocity.y < 0.f)
	{
		if (this->projectileDetails.velocity.y < -this->projectileDetails.maxVelocity)
			this->projectileDetails.velocity.y = -this->projectileDetails.maxVelocity;

		this->projectileDetails.velocity.y += this->projectileDetails.deceleration;

		if (this->projectileDetails.velocity.y > 0.f)
			this->projectileDetails.velocity.y = 0.f;
	}
	/*Down*/
	else if (this->projectileDetails.velocity.y > 0.f)
	{
		if (this->projectileDetails.velocity.y > this->projectileDetails.maxVelocity)
			this->projectileDetails.velocity.y = this->projectileDetails.maxVelocity;

		this->projectileDetails.velocity.y -= this->projectileDetails.deceleration;

		if (this->projectileDetails.velocity.y < 0.f)
			this->projectileDetails.velocity.y = 0.f;
	}

	/*Left*/
	if (this->projectileDetails.velocity.x < 0.f)
	{
		if (this->projectileDetails.velocity.x < -this->projectileDetails.maxVelocity)
			this->projectileDetails.velocity.x = -this->projectileDetails.maxVelocity;

		this->projectileDetails.velocity.x += this->projectileDetails.deceleration;

		if (this->projectileDetails.velocity.x > 0.f)
			this->projectileDetails.velocity.x = 0.f;
	}
	/*Right*/
	else if (this->projectileDetails.velocity.x > 0.f)
	{
		if (this->projectileDetails.velocity.x > this->projectileDetails.maxVelocity)
			this->projectileDetails.velocity.x = this->projectileDetails.maxVelocity;

		this->projectileDetails.velocity.x -= this->projectileDetails.deceleration;

		if (this->projectileDetails.velocity.x < 0.f)
			this->projectileDetails.velocity.x = 0.f;
	}

	this->oldPosition = this->spriteRect.getPosition();

	if (!this->stop)
	this->spriteRect.move(sf::Vector2f(this->projectileDetails.velocity.x, this->projectileDetails.velocity.y) * dt * (1.f / dt));

	this->updateProjectileAnimation();
}
void Projectile::updateLifeTimeCounter()
{
	++this->projectileDetails.lifeTimeCounter;

	if (this->projectileDetails.lifeTimeCounter > this->projectileDetails.maxLifeTimeCounter)
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
		if (this->projectileDetails.explosionIntRect.left == intRectLeft_End && this->projectileDetails.explosionIntRect.top == intRectTop_End)
		{
			this->projectileDetails.explosionIntRect.left = intRectLeft_Start;
			this->projectileDetails.explosionIntRect.top = intRectTop_Start;
			this->destroy = true;
		}

		if (this->projectileDetails.explosionIntRect.left == intRectLeft_End)
		{
			this->projectileDetails.explosionIntRect.left = intRectLeft_Start;
			this->projectileDetails.explosionIntRect.top += intRect_FrameSize;
		}
		else
		{
			this->projectileDetails.explosionIntRect.left += intRect_FrameSize;
			this->sprite.setTextureRect(this->projectileDetails.explosionIntRect);
			this->explosionAnimationClock.restart();
		}	
	}
}
void Projectile::update(const float& dt)
{
	this->updateDirection(dt);
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y));

	this->updateLifeTimeCounter();
	
	if (this->explode)
		this->updateExplosionAnimation();
}

/*Render Functions*/
void Projectile::render(sf::RenderTarget& target)
{
	target.draw(this->spriteRect);
	target.draw(this->sprite);
}

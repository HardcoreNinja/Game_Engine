#include "Header.h"
#include "Projectile.h"

/*Initializers*/
void Projectile::initVariables(ProjectileDetails projectile_details)
{
	/*Projectile Details*/
	this->projectileDetails = projectile_details;

	/*Movement Variables*/
	this->stop = false;

	/*Destroy Variables*/
	this->destroy = false;
	
	/*Explosion Variables*/
	this->explode = false;

	/*Collision Variables*/
	this->enemyCollisionBool = false;
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
	this->setProjectileType(this->projectileDetails.projectileType);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->spriteIntRect);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
	this->sprite.setScale(sf::Vector2f(.35, .35));

	/*Explosion*/
	this->projectileDetails.explosionIntRect = sf::IntRect(0, 0, 100, 100);
	this->projectileDetails.explosionTexture.setSmooth(true);
}
void Projectile::initAudio()
{
	switch (this->projectileDetails.projectileType)
	{
	case ProjectileTypes::Black_Tornado:
		this->audioMap["PROJECTILE_ENERGY_TORNADO"]->play();
		break;
	case ProjectileTypes::Blue_Tornado:
		this->audioMap["PROJECTILE_ENERGY_TORNADO"]->play();
		break;
	case ProjectileTypes::Brown_Tornado:
		this->audioMap["PROJECTILE_ENERGY_TORNADO"]->play();
		this->projectileDetails.damage = 50;
		break;
	case ProjectileTypes::Cyan_Ball_1:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Cyan_Ball_2:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Cyan_Ball_3:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Cyan_Ball_4:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Cyan_Ball_5:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Green_Tornado:
		this->audioMap["PROJECTILE_ENERGY_TORNADO"]->play();
		break;
	case ProjectileTypes::Pink_Ball_1:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Pink_Ball_2:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Pink_Ball_3:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Pink_Ball_4:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Pink_Ball_5:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Red_Tornado:
		this->audioMap["PROJECTILE_ENERGY_TORNADO"]->play();
		break;
	case ProjectileTypes::Yellow_Ball_1:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Yellow_Ball_2:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Yellow_Ball_3:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Yellow_Ball_4:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	case ProjectileTypes::Yellow_Ball_5:
		this->audioMap["PROJECTILE_ENERGY_BALL"]->play();
		break;
	default:
		std::cout << "ERROR::PROJECITLE::void Projectile::setProjectileType(ProjectileTypes projectile_type))::Invalid Switch Entry!\n";
	}
}

/*Constructor & Destructor*/
Projectile::Projectile(ProjectileDetails projectile_details, std::map<std::string, std::unique_ptr<Audio>>& audio_map)
	:Entity(audio_map)
{
	this->initVariables(projectile_details);
	this->initSpriteRect();
	this->initSprite();
	this->initAudio();
}
Projectile::~Projectile()
{
}

/*Getters*/
std::tuple<sf::RectangleShape, int> Projectile::getProjectileSpriteRectAndInt()
{
	return std::make_tuple(this->spriteRect, this->projectileDetails.damage);
}
bool Projectile::getDestroy()
{
	return this->destroy;
}
sf::RectangleShape Projectile::getSpriteRect()
{
	return this->spriteRect;
}
float Projectile::getManaDrainFactor()
{
	return this->projectileDetails.manaDrainFactor;
}
ProjectileDetails Projectile::getProjectileDetails()
{
	return this->projectileDetails;
}

/*Setters*/
void Projectile::setProjectileType(ProjectileTypes projectile_type)
{
	this->projectileDetails.projectileType  = projectile_type;

	switch (this->projectileDetails.projectileType)
	{
	case ProjectileTypes::Black_Tornado:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/black_tornado.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::black_tornado.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/gray.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/gray.png");
		this->projectileDetails.manaDrainFactor = 5.f;
		this->projectileDetails.damage = 50;
		break;
	case ProjectileTypes::Blue_Tornado:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/blue_tornado.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::blue_tornado.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/blue.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/blue.png");
		this->projectileDetails.manaDrainFactor = 5.f;
		this->projectileDetails.damage = 50;
		break;
	case ProjectileTypes::Brown_Tornado:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/brown_tornado.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::brown_tornado.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/orange.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/orange.png");
		this->projectileDetails.manaDrainFactor = 5.f;
		this->projectileDetails.damage = 50;
		break;
	case ProjectileTypes::Cyan_Ball_1:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/cyan_ball_1.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::cyan_ball_1.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/cyan.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/cyan.png");
		this->projectileDetails.manaDrainFactor = 3.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Cyan_Ball_2:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/cyan_ball_2.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::cyan_ball_2.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/cyan.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/cyan.png");
		this->projectileDetails.manaDrainFactor = 3.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Cyan_Ball_3:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/cyan_ball_3.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::cyan_ball_3.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/cyan.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/cyan.png");
		this->projectileDetails.manaDrainFactor = 3.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Cyan_Ball_4:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/cyan_ball_4.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::cyan_ball_4.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/cyan.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/cyan.png");
		this->projectileDetails.manaDrainFactor = 3.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Cyan_Ball_5:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/cyan_ball_5.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::cyan_ball_5.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/cyan.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/cyan.png");
		this->projectileDetails.manaDrainFactor = 3.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Green_Tornado:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/green_tornado.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::green_tornado.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/green.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/green.png");
		this->projectileDetails.manaDrainFactor = 5.f;
		this->projectileDetails.damage = 50;
		break;
	case ProjectileTypes::Pink_Ball_1:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/pink_ball_1.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::pink_ball_1.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/pink.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/pink.png");
		this->projectileDetails.manaDrainFactor = 4.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Pink_Ball_2:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/pink_ball_2.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::pink_ball_2.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/pink.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/pink.png");
		this->projectileDetails.manaDrainFactor = 4.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Pink_Ball_3:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/pink_ball_3.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::pink_ball_3.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/pink.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/pink.png");
		this->projectileDetails.manaDrainFactor = 4.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Pink_Ball_4:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/pink_ball_4.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::pink_ball_4.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/pink.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/pink.png");
		this->projectileDetails.manaDrainFactor = 4.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Pink_Ball_5:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/pink_ball_5.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::pink_ball_5.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/pink.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/pink.png");
		this->projectileDetails.manaDrainFactor = 4.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Red_Tornado:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/red_tornado.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::red_tornado.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/red.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/red.png");
		this->projectileDetails.manaDrainFactor = 5.f;
		this->projectileDetails.damage = 50;
		break;
	case ProjectileTypes::Yellow_Ball_1:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/yellow_ball_1.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::yellow_ball_1.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/yellow.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/yellow.png");
		this->projectileDetails.manaDrainFactor = 6.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Yellow_Ball_2:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/yellow_ball_2.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::yellow_ball_2.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/yellow.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/yellow.png");
		this->projectileDetails.manaDrainFactor = 6.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Yellow_Ball_3:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/yellow_ball_3.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::yellow_ball_3.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/yellow.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/yellow.png");
		this->projectileDetails.manaDrainFactor = 6.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Yellow_Ball_4:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/yellow_ball_4.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::yellow_ball_4.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/yellow.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/yellow.png");
		this->projectileDetails.manaDrainFactor = 6.f;
		this->projectileDetails.damage = 25;
		break;
	case ProjectileTypes::Yellow_Ball_5:
		if (!this->texture.loadFromFile("Resources/Images/Projectiles/yellow_ball_5.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::yellow_ball_5.png");
		if (!this->projectileDetails.explosionTexture.loadFromFile("Resources/Images/Explosions/yellow.png"))
			throw("ERROR::PROJECTILE::FAILED_TO_LOAD::Explosions/yellow.png");
		this->projectileDetails.manaDrainFactor = 6.f;
		this->projectileDetails.damage = 25;
		break;
	default:
		std::cout << "ERROR::PROJECITLE::void Projectile::setProjectileType(ProjectileTypes projectile_type))::Invalid Switch Entry!\n";
	}
}
void Projectile::setDirection(Direction player_direction)
{
	switch (player_direction)
	{
		case Direction::Idle:
			this->projectileDetails.direction = Direction::Idle;
			break;
		case Direction::Up:
			this->projectileDetails.direction = Direction::Up;
			break;
		case Direction::Down:
			this->projectileDetails.direction = Direction::Down;
			break;
		case Direction::Left:
			this->projectileDetails.direction = Direction::Left;
			break;
		case Direction::Right:
			this->projectileDetails.direction = Direction::Right;
			break;
	    default:
			std::cout << "PROJECTILE:: void getDirection():: INVALID ENTRY...\n";
			break;
	}
}
void Projectile::setProjectilePosition(sf::RectangleShape player)
{
	if(this->projectileDetails.direction == Direction::Up)
	this->spriteRect.setPosition(player.getPosition().x, player.getPosition().y - 50.f);
	if (this->projectileDetails.direction == Direction::Down)
		this->spriteRect.setPosition(player.getPosition().x, player.getPosition().y + 50.f);
	if (this->projectileDetails.direction == Direction::Left)
		this->spriteRect.setPosition(player.getPosition().x - 50.f, player.getPosition().y);
	if (this->projectileDetails.direction == Direction::Right)
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

/*Collision Functions*/
void Projectile::enemyCollision(sf::RectangleShape enemy_rect)
{
	if (enemy_rect.getGlobalBounds().intersects(this->spriteRect.getGlobalBounds()))
	{
		this->enemyCollisionBool = true;
		std::cout << "Enemy/Projectile Collision (from Projectile!)\n";
		this->setExplosionTexture();
	}
	else
		this->enemyCollisionBool = false; 

	if (this->enemyCollisionBool)
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
void Projectile::tileCollision(std::tuple<bool, unsigned short, std::string_view> collision_tuple)
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
void Projectile::updateAudio()
{
	if (this->wallCollision || this->enemyCollisionBool || this->projectileDetails.lifeTimeCounter == this->projectileDetails.maxLifeTimeCounter)
		this->audioMap["PROJECTILE_EXPLOSION"]->play();
}
void Projectile::updateDirection(const float& dt)
{
	if (this->projectileDetails.direction == Direction::Up)
	{
		this->updateVelocity(0.f, -1.f, dt);
	}
	else if (this->projectileDetails.direction == Direction::Down)
	{
		this->updateVelocity(0.f, 1.f, dt);
	}
	else if (this->projectileDetails.direction == Direction::Left)
	{
		this->updateVelocity(-1.f, 0.f, dt);
	}
	else if (this->projectileDetails.direction == Direction::Right)
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
	this->spriteRect.move(sf::Vector2f(this->projectileDetails.velocity.x * dt, this->projectileDetails.velocity.y * dt));

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
	int intRectLeft_End = 0;

	int intRectTop_Start = 0;
	int intRectTop_End = 0;

	int intRect_FrameSize = 0;

	switch (this->projectileDetails.projectileType)
	{
	case ProjectileTypes::Black_Tornado:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 576;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Blue_Tornado:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 576;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Brown_Tornado:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 576;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Cyan_Ball_1:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Cyan_Ball_2:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Cyan_Ball_3:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Cyan_Ball_4:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Cyan_Ball_5:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Green_Tornado:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 576;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Pink_Ball_1:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Pink_Ball_2:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Pink_Ball_3:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Pink_Ball_4:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Pink_Ball_5:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Red_Tornado:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 576;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Yellow_Ball_1:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Yellow_Ball_2:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Yellow_Ball_3:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Yellow_Ball_4:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	case ProjectileTypes::Yellow_Ball_5:
		intRectLeft_Start = 0;
		intRectLeft_End = 768;

		intRectTop_Start = 0;
		intRectTop_End = 960;

		intRect_FrameSize = 192;
		break;
	default:
		std::cout << "ERROR::PROJECITLE::void Projectile::updateProjectileAnimation()::Invalid Switch Entry!\n";
	}

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
	int intRectLeft_End = 5500;

	int intRectTop_Start = 0;

	int intRect_FrameSize = 100;

	/*Animation Switch Time Variables*/
	float deltaTime = this->explosionAnimationClock.getElapsedTime().asSeconds();
	float switchTime = 0.001;

	if (deltaTime > switchTime)
	{
		if (this->projectileDetails.explosionIntRect.left == intRectLeft_End)
		{
			//this->projectileDetails.explosionIntRect.left = intRectLeft_Start;
			this->destroy = true;
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
	
	/*Audio*/
	this->updateAudio();

	if (this->explode)
		this->updateExplosionAnimation();
}

/*Save & Load Functions*/
void Projectile::saveToFile()
{
	std::ofstream ofs("Config/projectile_details.ini");

	if (ofs.is_open())
	{
		/*Projectile Type*/
		ofs << static_cast<int>(this->projectileDetails.projectileType) << '\n';

		/*Movement Variables*/
		ofs << this->projectileDetails.velocity.x << " " << this->projectileDetails.velocity.y << '\n';
		ofs << this->projectileDetails.maxVelocity << '\n';
		ofs << this->projectileDetails.acceleration << '\n';
		ofs << this->projectileDetails.deceleration << '\n';

		/*Mana*/
		ofs << this->projectileDetails.manaDrainFactor << '\n';

		/*Destroy Variables*/
		ofs << this->projectileDetails.lifeTimeCounter << '\n';
		ofs << this->projectileDetails.maxLifeTimeCounter << '\n';
	}
	ofs.close();

	std::cout << "Saved Projectile Details!\n";
}

/*Render Functions*/
void Projectile::render(sf::RenderTarget& target, sf::Vector2f player_center, sf::Shader* shader)
{
	target.draw(this->spriteRect);

	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPosition", player_center);
		target.draw(this->sprite, shader);
	}
	else if (!shader)
		target.draw(this->sprite);
}

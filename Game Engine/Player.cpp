#include "Header.h"
#include "Player.h"
#include "TileMap.h"

/*Initializers*/
void Player::initVariables()
{
	this->velocity = sf::Vector2f(0.f, 0.f);
	this->maxVelocity = 10.f;
	this->acceleration = 0.2f;
	this->deceleration = 0.15f;
	this->wallCollision = false;
}
void Player::initKeybinds()
{
	std::ifstream ifs("Config/player_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string keyboardKey = "";

		while (ifs >> key >> keyboardKey)

			this->keybinds[key] = this->supportedKeys->at(keyboardKey);
	}
	ifs.close();

	//Debug Tester
	for (auto i : this->keybinds)
	{
		std::cout << i.first << " " << i.second << '\n';
	}
}
void Player::initIntRectVector()
{
	int intRectLeftX = 48;
	int intRectTopY = 256; 

	int intRectWidth = 48;
	int intRectHeight = 64;

	/*Actors 0-3*/
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 1, intRectTopY * 0, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 4, intRectTopY * 0, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 7, intRectTopY * 0, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 10, intRectTopY * 0, intRectWidth, intRectHeight));

	/*Actors 4-7*/
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 1, intRectTopY * 1, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 4, intRectTopY * 1, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 7, intRectTopY * 1, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 10, intRectTopY * 1, intRectWidth, intRectHeight));

	/*Actors 8-11*/
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 1, intRectTopY * 2, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 4, intRectTopY * 2, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 7, intRectTopY * 2, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 10, intRectTopY * 2, intRectWidth, intRectHeight));

	/*Actors 12-15*/
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 1, intRectTopY * 3, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 4, intRectTopY * 3, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 7, intRectTopY * 3, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 10, intRectTopY * 3, intRectWidth, intRectHeight));

	/*Actors 16-19*/
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 0, intRectTopY * 4, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 4, intRectTopY * 4, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 7, intRectTopY * 4, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 10, intRectTopY * 4, intRectWidth, intRectHeight));

	/*Actors 20-23*/
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 1, intRectTopY * 5, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 4, intRectTopY * 5, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 7, intRectTopY * 5, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 10, intRectTopY * 5, intRectWidth, intRectHeight));
}
void Player::initSpriteRect()
{
	this->spriteRect.setSize(sf::Vector2f(26, 42.f));
	this->spriteRect.setOutlineThickness(1.f);
	this->spriteRect.setOutlineColor(sf::Color::Red);
	this->spriteRect.setFillColor(sf::Color::Transparent);
	this->spriteRect.setOrigin(this->spriteRect.getGlobalBounds().width / 2.f, this->spriteRect.getGlobalBounds().height / 2.f);
	this->spriteRect.setPosition(207, 176);
}
void Player::initSprite(Actors actor)
{
	this->actor = actor;
	this->spriteIntRect = this->intRectVector[static_cast<int>(this->actor)];
	if(!this->texture.loadFromFile("Resources/Images/Characters/MasterHeroSheet.png"))
		throw("ERROR::PLAYER::FAILED_TO_LOAD::MasterHeroSheet.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->spriteIntRect);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2.f, this->sprite.getGlobalBounds().height/2.f);
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y-10));
}

/*Constuctor & Destructor*/
Player::Player(Actors actor, std::map<std::string, int>* supported_keys)
{
	this->supportedKeys = supported_keys;
	this->initVariables();
	this->initKeybinds();
	this->initIntRectVector();
	this->initSpriteRect();
	this->initSprite(actor);
}
Player::~Player()
{
}

/*Getters*/
sf::RectangleShape Player::getSpriteRect()
{
	return this->spriteRect;
}

/*Tile Collision Functions*/
void Player::tileCollision(std::tuple<bool, unsigned short> collision_tuple)
{
	if (std::get<0>(collision_tuple) == true && std::get<1>(collision_tuple) == TILEMAP::TileType::Wall)
	{
		this->wallCollision = true;
		std::cout << "Wall Collision: " << this->wallCollision << '\n';
	}
	else
		this->wallCollision = false;

	if (this->wallCollision == true)
	{
		sf::Vector2f position = this->spriteRect.getPosition();

		if (this->velocity.x != 0.f)
		{
			position.x = this->oldPosition.x;
			this->velocity.x = 0.f;
		}

		if (this->velocity.y != 0.f)
		{
			position.y = this->oldPosition.y;
			this->velocity.y = 0.f;
		}

		this->spriteRect.setPosition(position);
	}
}

/*Update Functions*/
void Player::updateUserInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("UP"))))
	{
		this->playerDirection = PlayerDirection::Up;
		this->updateVelocity(0.f, -1.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DOWN"))))
	{
		this->playerDirection = PlayerDirection::Down;
		this->updateVelocity(0.f, 1.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT"))))
	{
		this->playerDirection = PlayerDirection::Left;
		this->updateVelocity(-1.f, 0.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("RIGHT"))))
	{
		this->playerDirection = PlayerDirection::Right;
		this->updateVelocity(1.f, 0.f, dt);
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("UP")))
		|| !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DOWN")))
		|| !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT")))
		|| !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("RIGHT"))))
	{
		this->playerDirection = PlayerDirection::Idle;
		this->updateVelocity(0.f, 0.f, dt);
	}
}
void Player::updateVelocity(float dir_x, float dir_y, const float& dt)
{
	this->velocity.x += this->acceleration * dir_x;
	this->velocity.y += this->acceleration * dir_y;

	this->updateMovement(dt);
}
void Player::updateMovement(const float& dt)
{
	/*Up*/
	if (this->velocity.y < 0.f)
	{
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		this->velocity.y += this->deceleration;

		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}
	/*Down*/
	else if (this->velocity.y > 0.f)
	{
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		this->velocity.y -= this->deceleration;

		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}

	/*Left*/
	if (this->velocity.x < 0.f)
	{
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		this->velocity.x += this->deceleration;

		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}
	/*Right*/
	else if (this->velocity.x > 0.f)
	{
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		this->velocity.x -= this->deceleration;

		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}

	this->oldPosition = this->spriteRect.getPosition();
	this->spriteRect.move(sf::Vector2f(this->velocity.x, this->velocity.y) * dt * (1.f / dt));
	this->updateAnimation();
}
void Player::updateAnimation()
{
	/*IntRect Variables*/
	int intRectTop_Up = 0;
	int intRectTop_Down = 0;
	int intRectTop_Left = 0;
	int intRectTop_Right = 0;

	int intRectLeft_Start = 0;
	int intRectLeft_End = 0;

	int intRectLeft_FrameSize = 48;

	int intRectWidth = 48;
	int intRectHeight = 64;

	sf::IntRect idleUp;
	sf::IntRect idleDown;
	sf::IntRect idleLeft;
	sf::IntRect idleRight;

	/*Actor IntRect Switch*/
	switch (this->actor)
	{
	case Actors::Actor_0:
		intRectTop_Up = 192;
		intRectTop_Down = 0;
		intRectTop_Left = 64;
		intRectTop_Right = 128;

		intRectLeft_Start = 0;
		intRectLeft_End = 96;

		idleUp = sf::IntRect(intRectWidth * 1, intRectTop_Up, intRectWidth, intRectHeight);
		idleDown = sf::IntRect(intRectWidth * 1, intRectTop_Down, intRectWidth, intRectHeight);
		idleLeft = sf::IntRect(intRectWidth * 1, intRectTop_Left, intRectWidth, intRectHeight);
		idleRight = sf::IntRect(intRectWidth * 1, intRectTop_Right, intRectWidth, intRectHeight);
		break;
	}

	/*Animation Switch Time Variables*/
	float deltaTime = this->animationClock.getElapsedTime().asSeconds();
	float switchTime = .1f;

	/*Movement "If" Statement*/
	if (deltaTime > switchTime)
	{
			if (this->playerDirection == PlayerDirection::Up)
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
			else if (this->playerDirection == PlayerDirection::Down)
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
			else if (this->playerDirection == PlayerDirection::Left)
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
			else if (this->playerDirection == PlayerDirection::Right)
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
		else if (this->velocity.x == 0.f && this->velocity.y == 0.f)
		{
			if (this->playerDirection == PlayerDirection::Up)
			{
				this->spriteIntRect = idleUp;
				this->sprite.setTextureRect(this->spriteIntRect);
			}
			else if (this->playerDirection == PlayerDirection::Down)
			{
				this->spriteIntRect = idleDown;
				this->sprite.setTextureRect(this->spriteIntRect);
			}
			else if (this->playerDirection == PlayerDirection::Left)
			{
				this->spriteIntRect = idleLeft;
				this->sprite.setTextureRect(this->spriteIntRect);
			}
			else if (this->playerDirection == PlayerDirection::Right)
			{
				this->spriteIntRect = idleRight;
				this->sprite.setTextureRect(this->spriteIntRect);
			}
		}
	}
}
void Player::update(const float& dt)
{
	this->updateUserInput(dt);
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y - 10));
}

/*Render Functions*/
void Player::render(sf::RenderTarget& target)
{
	target.draw(this->spriteRect);
	target.draw(this->sprite);
}

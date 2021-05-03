#include "Header.h"
#include "Player.h"

/*Initializers*/
void Player::initVariables()
{
	this->movementSpeed = 10.f;
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

/*Movement Functions*/
void Player::movement(const float& dt)
{
	/*IntRect Variables*/
	int intRectTop_Up;
	int intRectTop_Down;
	int intRectTop_Left;
	int intRectTop_Right;

	int intRectLeft_Start;
	int intRectLeft_End;

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

	float deltaTime = this->animationClock.getElapsedTime().asSeconds();
	float switchTime = .1f;

	if (deltaTime > switchTime)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("UP"))))
		{
			this->playerDirection = PlayerDirection::Up;
			if (!this->wallCollision && this->playerDirection == PlayerDirection::Up)
			{
				this->spriteRect.move(0, -this->movementSpeed * dt * (1.f / dt));

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
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DOWN"))))
		{
			this->playerDirection = PlayerDirection::Down;
			if (!this->wallCollision && this->playerDirection == PlayerDirection::Down)
			{
				this->spriteRect.move(0, this->movementSpeed * dt * (1.f / dt));

				this->spriteIntRect.top = intRectTop_Down;

				if (this->spriteIntRect.left == intRectLeft_End)
				{
					this->spriteIntRect.left = intRectLeft_Start;
				}
				else
				{
					this->spriteIntRect.left += intRectLeft_FrameSize;
					this->sprite.setTextureRect(this->spriteIntRect);
					this->animationClock.restart();
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT"))))
		{
			this->playerDirection = PlayerDirection::Left;
			if (!this->wallCollision && this->playerDirection == PlayerDirection::Left)
			{
				this->spriteRect.move(-this->movementSpeed * dt * (1.f / dt), 0);

				this->spriteIntRect.top = intRectTop_Left;

				if (this->spriteIntRect.left == intRectLeft_End)
				{
					this->spriteIntRect.left = intRectLeft_Start;
				}
				else
				{
					this->spriteIntRect.left += intRectLeft_FrameSize;
					this->sprite.setTextureRect(this->spriteIntRect);
					this->animationClock.restart();
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("RIGHT"))))
		{
			this->playerDirection = PlayerDirection::Right;
			if (!this->wallCollision && this->spriteIntRect.top == intRectTop_Right)
			{
				this->spriteRect.move(this->movementSpeed * dt * (1.f / dt), 0);

				this->spriteIntRect.top = intRectTop_Right;

				if (this->spriteIntRect.left == intRectLeft_End)
				{
					this->spriteIntRect.left = intRectLeft_Start;
				}
				else
				{
					this->spriteIntRect.left += intRectLeft_FrameSize;
					this->sprite.setTextureRect(this->spriteIntRect);
					this->animationClock.restart();
				}
			}
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("UP"))) 
			|| !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DOWN")))
			|| !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT")))
			|| !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("RIGHT"))))
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

/*Tile Collisions Functions*/
void Player::tileCollision(std::tuple<bool, unsigned short> collision_tuple)
{
	if (std::get<0>(collision_tuple) == true && std::get<1>(collision_tuple) == 3)
	{
		this->wallCollision = true;
		std::cout << "Wall Collision: " << this->wallCollision << '\n';
	}
	else
		this->wallCollision = false;

	if (this->wallCollision == true && this->playerDirection == PlayerDirection::Left)
		this->spriteRect.move(10, 0);
	else if (this->wallCollision == true && this->playerDirection == PlayerDirection::Right)
		this->spriteRect.move(-10, 0);
	else if (this->wallCollision == true && this->playerDirection == PlayerDirection::Up)
		this->spriteRect.move(0, 10);
	else if (this->wallCollision == true && this->playerDirection == PlayerDirection::Down)
		this->spriteRect.move(0, -10);
}

/*Update Functions*/
void Player::update(const float& dt)
{
	this->movement(dt);
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y - 10));
}

/*Render Functions*/
void Player::render(sf::RenderTarget& target)
{
	target.draw(this->spriteRect);
	target.draw(this->sprite);
}

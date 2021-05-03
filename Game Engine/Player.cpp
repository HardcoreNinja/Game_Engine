#include "Header.h"
#include "Player.h"
/*Initializers*/
void Player::initIntRectVector()
{
	int intRectLeftX = 48;
	int intRectTopY = 256; 

	int intRectWidth = 48;
	int intRectHeight = 64;

	/*Actors 0-3*/
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 0, intRectTopY * 0, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 4, intRectTopY * 0, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 7, intRectTopY * 0, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 10, intRectTopY * 0, intRectWidth, intRectHeight));

	/*Actors 4-7*/
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 0, intRectTopY * 1, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 4, intRectTopY * 1, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 7, intRectTopY * 1, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 10, intRectTopY * 1, intRectWidth, intRectHeight));

	/*Actors 8-11*/
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 0, intRectTopY * 2, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 4, intRectTopY * 2, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 7, intRectTopY * 2, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 10, intRectTopY * 2, intRectWidth, intRectHeight));

	/*Actors 12-15*/
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 0, intRectTopY * 3, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 4, intRectTopY * 3, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 7, intRectTopY * 3, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 10, intRectTopY * 3, intRectWidth, intRectHeight));

	/*Actors 16-19*/
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 0, intRectTopY * 4, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 4, intRectTopY * 4, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 7, intRectTopY * 4, intRectWidth, intRectHeight));
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 10, intRectTopY * 4, intRectWidth, intRectHeight));

	/*Actors 20-23*/
	this->intRectVector.push_back(sf::IntRect(intRectLeftX * 0, intRectTopY * 5, intRectWidth, intRectHeight));
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
Player::Player(Actors actor)
{
	this->initIntRectVector();
	this->initSpriteRect();
	this->initSprite(actor);
}
Player::~Player()
{
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->spriteRect);
	target.draw(this->sprite);
}

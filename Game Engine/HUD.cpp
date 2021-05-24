#include "Header.h"
#include "HUD.h"

/*Initializers*/
void HUD::initSprites()
{
	/*HUD System*/
	if (!this->textureHUDSystem.loadFromFile("Resources/Images/HUD/hud_system.png"))
		throw("ERROR::HUD::FAILED_TO_LOAD::HUD/hud_system.png");
	this->intRectHUDSystem = sf::IntRect(0, 0, 302.f, 136.f);
	this->spriteHUDSystem.setTexture(this->textureHUDSystem);
	this->spriteHUDSystem.setTextureRect(this->intRectHUDSystem);
	this->spriteHUDSystem.setPosition(25.f, 25.f);

	/*Red Bar*/
	if (!this->textureRedBar.loadFromFile("Resources/Images/HUD/red_bar.png"))
		throw("ERROR::HUD::FAILED_TO_LOAD::HUD/red_bar.png");
	this->intRectRedBar = sf::IntRect(0, 0, 157.f, 13.f);
	this->spriteRedBar.setTexture(this->textureRedBar);
	this->spriteRedBar.setTextureRect(this->intRectRedBar);
	this->spriteRedBar.setPosition(148.f, 37.f);

	/*Yellow Bar*/
	if (!this->textureYellowBar.loadFromFile("Resources/Images/HUD/yellow_bar.png"))
		throw("ERROR::HUD::FAILED_TO_LOAD::HUD/yellow_bar.png");
	this->intRectYellowBar = sf::IntRect(0, 0, 157.f, 14.f);
	this->spriteYellowBar.setTexture(this->textureYellowBar);
	this->spriteYellowBar.setTextureRect(this->intRectYellowBar);
	this->spriteYellowBar.setPosition(165.f, 82.f);

	/*Blue Bar*/
	if (!this->textureBlueBar.loadFromFile("Resources/Images/HUD/blue_bar.png"))
		throw("ERROR::HUD::FAILED_TO_LOAD::HUD/blue_bar.png");
	this->intRectBlueBar = sf::IntRect(0, 0, 157.f, 13.f);
	this->spriteBlueBar.setTexture(this->textureBlueBar);
	this->spriteBlueBar.setTextureRect(this->intRectBlueBar);
	this->spriteBlueBar.setPosition(148.f, 126.f);
}

/*Constructor & Destructor*/
HUD::HUD(PlayerDetails player_details)
{
	this->initSprites();
}
HUD::~HUD()
{
}

/*Update Functions*/
void HUD::update(const float& dt)
{
}

/*Render Functions*/
void HUD::render(sf::RenderTarget& target)
{
	target.draw(this->spriteBlueBar);
	target.draw(this->spriteYellowBar);
	target.draw(this->spriteRedBar);
	target.draw(this->spriteHUDSystem);
}

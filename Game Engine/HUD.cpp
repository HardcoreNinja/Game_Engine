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
void HUD::initText()
{
	if (!this->font.loadFromFile("Resources/Fonts/BreatheFire.ttf"))
		throw ("ERROR::HUD::FAILED_TO_LOAD:BreatheFire.ttf");

	this->playerLevel.setFont(font);
	this->playerLevel.setFillColor(sf::Color::White);
	this->playerLevel.setCharacterSize(30);
	this->playerLevel.setPosition(65.f, 65.f);

	this->staminaText.setFont(font);
	this->staminaText.setFillColor(sf::Color::Black);
	this->staminaText.setCharacterSize(15);
	this->staminaText.setPosition(170.f, 79.f);

	this->manaText.setFont(font);
	this->manaText.setFillColor(sf::Color::Black);
	this->manaText.setCharacterSize(15);
	this->manaText.setPosition(170.f, 123.f);
}

/*Constructor & Destructor*/
HUD::HUD()
{
	this->initSprites();
	this->initText();
}
HUD::~HUD()
{
}

/*Update Functions*/
void HUD::updateMana(float current_mana, float max_mana)
{
	int intRectLeft = 157.f;

	float percentageChange = current_mana / max_mana;

	std::cout << "PercentageChange: " << percentageChange << '\n';

	this->intRectBlueBar.width = intRectLeft * percentageChange;
	this->spriteBlueBar.setTextureRect(this->intRectBlueBar);
}
void HUD::updateManaText(float current_mana, float max_mana)
{
	std::stringstream ss;

	ss << "Mana: " << static_cast<int>(current_mana) << " / " << max_mana;

	this->manaText.setString(ss.str());
}
void HUD::updatePlayerLevelText(PlayerDetails player_details)
{
	std::stringstream ss;

	ss << "Lv: " << player_details.level;

	this->playerLevel.setString(ss.str());
}
void HUD::updateStamina(PlayerDetails player_details)
{
	int intRectLeft = 157.f;

	float percentageChange = player_details.currentStamina / player_details.maxStamina; 

	std::cout << "PercentageChange: " << percentageChange << '\n';

	this->intRectYellowBar.width = intRectLeft * percentageChange;
	this->spriteYellowBar.setTextureRect(this->intRectYellowBar);
}
void HUD::updateStaminaText(PlayerDetails player_details)
{
	std::stringstream ss; 

	ss << "Stamina: " << std::floor(player_details.currentStamina * 100.f)/ 100.f << " / " << player_details.maxStamina;

	this->staminaText.setString(ss.str());
}
void HUD::update(PlayerDetails player_details, float current_mana, float max_mana)
{
	this->updateMana(current_mana, max_mana);
	this->updateManaText(current_mana, max_mana);
	this->updatePlayerLevelText(player_details);
	this->updateStamina(player_details);
	this->updateStaminaText(player_details);
}

/*Render Functions*/
void HUD::render(sf::RenderTarget& target)
{
	target.draw(this->spriteBlueBar);
	target.draw(this->spriteYellowBar);
	target.draw(this->spriteRedBar);
	target.draw(this->spriteHUDSystem);
	target.draw(this->staminaText);
	target.draw(this->playerLevel);
	target.draw(this->manaText);
}

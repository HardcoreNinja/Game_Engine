#include "Header.h"
#include "Player.h"

/*Initializers*/
void Player::initVariables(PlayerDetails player_details)
{
	/*Player Details*/
	this->playerDetails = player_details;
	
	/*std::cout << "Player Name: " << this->playerDetails.name << '\n' <<
		" | " << "Texture Counter:" << this->playerDetails.textureSwitchCounter << '\n' <<
		" | " << "Gender Bool: " << this->playerDetails.male1Female0 << '\n' <<
		" | " << "Position: " << this->playerDetails.position.x << " x " << this->playerDetails.position.y << '\n' <<
		" | " << "Old Direction: " << static_cast<int>(this->playerDetails.oldDirection) << '\n' <<
		" | " << "Velocity: " << this->playerDetails.velocity.x << " x " << this->playerDetails.velocity.y << '\n' <<
		" | " << "Max Velocity: " << this->playerDetails.maxVelocity << '\n' <<
		" | " << "Acceleration: " << this->playerDetails.acceleration << '\n' <<
		" | " << "Deceleration: " << this->playerDetails.deceleration << '\n' <<
		" | " << "Level: " << this->playerDetails.level << '\n' <<
		" | " << "Current HP: " << this->playerDetails.currentHP << '\n' <<
		" | " << "Max HP: " << this->playerDetails.currentHP << '\n' <<
		" | " << "Current Stamina: " << this->playerDetails.currentStamina << '\n' <<
		" | " << "Max Stamina: " << this->playerDetails.maxStamina << '\n' <<
		" | " << "Stamina Drain Factor: " << this->playerDetails.staminaDrainFactor << '\n' <<
		" | " << "Stamina Fill Factor: " << this->playerDetails.staminaFillFactor << '\n' <<
		" | " << "Current Mana: " << this->playerDetails.currentMana << '\n' <<
		" | " << "Max Mana: " << this->playerDetails.maxMana << '\n' <<
		'\n';*/

	/*Stamina Variables*/
	this->quarterMaxVelocity = this->playerDetails.maxVelocity / 4.f;

	/*Collision Variables*/
	this->enemyCollisionBool = false;
	this->doorCollision = false;
	this->doorName = " ";
	this->wallCollision = false;
}
void Player::initKeybinds(std::map<std::string, int>* supported_keys)
{
	std::ifstream ifs("Config/player_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string keyboardKey = "";

		while (ifs >> key >> keyboardKey)

			this->keybinds[key] = supported_keys->at(keyboardKey);
	}
	ifs.close();

	//Debug Tester
	for (auto i : this->keybinds)
	{
		std::cout << i.first << " " << i.second << '\n';
	}
}
void Player::initSpriteRect()
{
	this->spriteRect.setSize(sf::Vector2f(26.f, 32.f));
	this->spriteRect.setOutlineThickness(1.f);
	this->spriteRect.setOutlineColor(sf::Color::Red);
	this->spriteRect.setFillColor(sf::Color::Transparent);
	this->spriteRect.setOrigin(this->spriteRect.getGlobalBounds().width / 2.f, this->spriteRect.getGlobalBounds().height / 2.f);
	this->spriteRect.setPosition(this->playerDetails.position);
}
void Player::initSprite()
{
	if (this->playerDetails.male1Female0)
		switch (this->playerDetails.textureSwitchCounter)
		{
		case 1:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/1.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/1.png");
			sprite.setTexture(this->texture);
			break;
		case 2:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/2.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/2.png");
			sprite.setTexture(this->texture);
			break;
		case 3:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/3.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/3.png");
			sprite.setTexture(this->texture);
			break;
		case 4:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/4.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/4.png");
			sprite.setTexture(this->texture);
			break;
		case 5:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/5.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/5.png");
			sprite.setTexture(this->texture);
			break;
		case 6:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/6.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/6.png");
			sprite.setTexture(this->texture);
			break;
		case 7:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/7.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/7.png");
			sprite.setTexture(this->texture);
			break;
		case 8:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/8.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/8.png");
			sprite.setTexture(this->texture);
			break;
		case 9:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/9.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/9.png");
			sprite.setTexture(this->texture);
			break;
		case 10:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/10.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/10.png");
			sprite.setTexture(this->texture);
			break;
		case 11:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/11.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/11.png");
			sprite.setTexture(this->texture);
			break;
		case 12:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/12.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/12.png");
			sprite.setTexture(this->texture);
			break;
		case 13:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/13.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/13.png");
			sprite.setTexture(this->texture);
			break;
		case 14:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/14.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/14.png");
			sprite.setTexture(this->texture);
			break;
		case 15:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/15.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/15.png");
			sprite.setTexture(this->texture);
			break;
		case 16:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/16.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/16.png");
			sprite.setTexture(this->texture);
			break;
		case 17:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/17.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/17.png");
			sprite.setTexture(this->texture);
			break;
		case 18:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/18.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/18.png");
			sprite.setTexture(this->texture);
			break;
		case 19:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/19.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/19.png");
			sprite.setTexture(this->texture);
			break;
		case 20:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/20.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/20.png");
			sprite.setTexture(this->texture);
			break;
		case 21:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/21.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/21.png");
			sprite.setTexture(this->texture);
			break;
		case 22:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/22.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/22.png");
			sprite.setTexture(this->texture);
			break;
		case 23:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/23.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/23.png");
			sprite.setTexture(this->texture);
			break;
		case 24:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/24.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/24.png");
			sprite.setTexture(this->texture);
			break;
		case 25:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/25.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/25.png");
			sprite.setTexture(this->texture);
			break;
		case 26:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/26.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/26.png");
			sprite.setTexture(this->texture);
			break;
		case 27:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/27.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/27.png");
			sprite.setTexture(this->texture);
			break;
		case 28:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/28.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/28.png");
			sprite.setTexture(this->texture);
			break;
		case 29:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/29.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/9.png");
			sprite.setTexture(this->texture);
			break;
		case 30:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/30.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/30.png");
			sprite.setTexture(this->texture);
			break;
		case 31:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/31.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/31.png");
			sprite.setTexture(this->texture);
			break;
		case 32:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/32.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/32.png");
			sprite.setTexture(this->texture);
			break;
		case 33:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/33.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/33.png");
			sprite.setTexture(this->texture);
			break;
		case 34:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/34.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/34.png");
			sprite.setTexture(this->texture);
			break;
		case 35:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/35.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/35.png");
			sprite.setTexture(this->texture);
			break;
		case 36:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/36.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/36.png");
			sprite.setTexture(this->texture);
			break;
		case 37:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/37.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/37.png");
			sprite.setTexture(this->texture);
			break;
		case 38:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/38.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/38.png");
			sprite.setTexture(this->texture);
			break;
		case 39:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/39.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/39.png");
			sprite.setTexture(this->texture);
			break;
		case 40:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/40.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/40.png");
			sprite.setTexture(this->texture);
			break;
		case 41:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/41.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/41.png");
			sprite.setTexture(this->texture);
			break;
		case 42:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/42.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/42.png");
			sprite.setTexture(this->texture);
			break;
		case 43:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/43.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/43.png");
			sprite.setTexture(this->texture);
			break;
		case 44:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/44.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/44.png");
			sprite.setTexture(this->texture);
			break;
		case 45:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/45.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/45.png");
			sprite.setTexture(this->texture);
			break;
		case 46:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/46.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/46.png");
			sprite.setTexture(this->texture);
			break;
		case 47:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/47.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/47.png");
			sprite.setTexture(this->texture);
			break;
		case 48:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/48.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/48.png");
			sprite.setTexture(this->texture);
			break;
		case 49:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/49.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/49.png");
			sprite.setTexture(this->texture);
			break;
		case 50:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/50.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/50.png");
			sprite.setTexture(this->texture);
			break;
		case 51:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/51.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/51.png");
			sprite.setTexture(this->texture);
			break;
		case 52:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/52.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/52.png");
			sprite.setTexture(this->texture);
			break;
		case 53:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/53.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/53.png");
			sprite.setTexture(this->texture);
			break;
		case 54:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/54.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/54.png");
			sprite.setTexture(this->texture);
			break;
		case 55:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/55.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/55.png");
			sprite.setTexture(this->texture);
			break;
		case 56:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/56.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/56.png");
			sprite.setTexture(this->texture);
			break;
		case 57:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/57.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/57.png");
			sprite.setTexture(this->texture);
			break;
		case 58:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/58.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/58.png");
			sprite.setTexture(this->texture);
			break;
		case 59:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/59.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/59.png");
			sprite.setTexture(this->texture);
			break;
		case 60:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/60.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/60.png");
			sprite.setTexture(this->texture);
			break;
		case 61:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/61.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/61.png");
			sprite.setTexture(this->texture);
			break;
		case 62:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/62.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/62.png");
			sprite.setTexture(this->texture);
			break;
		case 63:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/63.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/63.png");
			sprite.setTexture(this->texture);
			break;
		case 64:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/64.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/64.png");
			sprite.setTexture(this->texture);
			break;
		case 65:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/65.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/65.png");
			sprite.setTexture(this->texture);
			break;
		case 66:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/66.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/66.png");
			sprite.setTexture(this->texture);
			break;
		case 67:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/67.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/67.png");
			sprite.setTexture(this->texture);
			break;
		case 68:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/68.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/68.png");
			sprite.setTexture(this->texture);
			break;
		case 69:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/69.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Male/69.png");
			sprite.setTexture(this->texture);
			break;
		default:
			std::cout << "ERROR::NEWCHARACTERSCREEN::void updateTexture()::Invalid Switch Entry!\n";
		}
	else if (!this->playerDetails.male1Female0)
		switch (this->playerDetails.textureSwitchCounter)
		{
		case 1:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/1.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/1.png");
			this->sprite.setTexture(this->texture);
			break;
		case 2:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/2.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/2.png");
			this->sprite.setTexture(this->texture);
			break;
		case 3:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/3.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/3.png");
			this->sprite.setTexture(this->texture);
			break;
		case 4:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/4.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/4.png");
			this->sprite.setTexture(this->texture);
			break;
		case 5:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/5.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/5.png");
			this->sprite.setTexture(this->texture);
			break;
		case 6:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/6.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/6.png");
			this->sprite.setTexture(this->texture);
			break;
		case 7:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/7.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/7.png");
			this->sprite.setTexture(this->texture);
			break;
		case 8:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/8.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/8.png");
			this->sprite.setTexture(this->texture);
			break;
		case 9:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/9.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/9.png");
			this->sprite.setTexture(this->texture);
			break;
		case 10:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/10.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/10.png");
			this->sprite.setTexture(this->texture);
			break;
		case 11:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/11.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/11.png");
			this->sprite.setTexture(this->texture);
			break;
		case 12:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/12.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/12.png");
			this->sprite.setTexture(this->texture);
			break;
		case 13:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/13.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/13.png");
			this->sprite.setTexture(this->texture);
			break;
		case 14:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/14.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/14.png");
			this->sprite.setTexture(this->texture);
			break;
		case 15:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/15.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/15.png");
			this->sprite.setTexture(this->texture);
			break;
		case 16:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/16.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/16.png");
			this->sprite.setTexture(this->texture);
			break;
		case 17:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/17.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/17.png");
			this->sprite.setTexture(this->texture);
			break;
		case 18:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/18.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/18.png");
			this->sprite.setTexture(this->texture);
			break;
		case 19:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/19.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/19.png");
			this->sprite.setTexture(this->texture);
			break;
		case 20:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/20.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/20.png");
			this->sprite.setTexture(this->texture);
			break;
		case 21:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/21.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/21.png");
			this->sprite.setTexture(this->texture);
			break;
		case 22:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/22.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/22.png");
			this->sprite.setTexture(this->texture);
			break;
		case 23:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/23.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/23.png");
			this->sprite.setTexture(this->texture);
			break;
		case 24:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/24.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/24.png");
			this->sprite.setTexture(this->texture);
			break;
		case 25:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/25.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/25.png");
			this->sprite.setTexture(this->texture);
			break;
		case 26:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/26.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/26.png");
			this->sprite.setTexture(this->texture);
			break;
		case 27:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/27.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/27.png");
			this->sprite.setTexture(this->texture);
			break;
		case 28:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/28.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/28.png");
			this->sprite.setTexture(this->texture);
			break;
		case 29:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/29.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/9.png");
			this->sprite.setTexture(this->texture);
			break;
		case 30:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/30.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/30.png");
			this->sprite.setTexture(this->texture);
			break;
		case 31:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/31.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/31.png");
			this->sprite.setTexture(this->texture);
			break;
		case 32:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/32.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/32.png");
			this->sprite.setTexture(this->texture);
			break;
		case 33:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/33.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/33.png");
			this->sprite.setTexture(this->texture);
			break;
		case 34:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/34.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/34.png");
			this->sprite.setTexture(this->texture);
			break;
		case 35:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/35.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/35.png");
			this->sprite.setTexture(this->texture);
			break;
		case 36:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/36.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/36.png");
			this->sprite.setTexture(this->texture);
			break;
		case 37:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/37.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/37.png");
			this->sprite.setTexture(this->texture);
			break;
		case 38:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/38.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/38.png");
			this->sprite.setTexture(this->texture);
			break;
		case 39:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/39.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/39.png");
			this->sprite.setTexture(this->texture);
			break;
		case 40:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/40.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/40.png");
			this->sprite.setTexture(this->texture);
			break;
		case 41:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/41.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/41.png");
			this->sprite.setTexture(this->texture);
			break;
		case 42:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/42.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/42.png");
			this->sprite.setTexture(this->texture);
			break;
		case 43:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/43.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/43.png");
			this->sprite.setTexture(this->texture);
			break;
		case 44:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/44.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/44.png");
			this->sprite.setTexture(this->texture);
			break;
		case 45:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/45.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/45.png");
			this->sprite.setTexture(this->texture);
			break;
		case 46:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/46.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/46.png");
			this->sprite.setTexture(this->texture);
			break;
		case 47:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/47.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/47.png");
			this->sprite.setTexture(this->texture);
			break;
		case 48:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/48.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/48.png");
			this->sprite.setTexture(this->texture);
			break;
		case 49:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/49.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/49.png");
			this->sprite.setTexture(this->texture);
			break;
		case 50:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/50.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/50.png");
			this->sprite.setTexture(this->texture);
			break;
		case 51:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/51.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/51.png");
			this->sprite.setTexture(this->texture);
			break;
		case 52:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/52.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/52.png");
			this->sprite.setTexture(this->texture);
			break;
		case 53:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/53.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/53.png");
			this->sprite.setTexture(this->texture);
			break;
		case 54:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/54.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/54.png");
			this->sprite.setTexture(this->texture);
			break;
		case 55:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/55.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/55.png");
			this->sprite.setTexture(this->texture);
			break;
		case 56:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/56.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/56.png");
			this->sprite.setTexture(this->texture);
			break;
		case 57:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/57.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/57.png");
			this->sprite.setTexture(this->texture);
			break;
		case 58:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/58.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/58.png");
			this->sprite.setTexture(this->texture);
			break;
		case 59:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/59.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/59.png");
			this->sprite.setTexture(this->texture);
			break;
		case 60:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/60.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/60.png");
			this->sprite.setTexture(this->texture);
			break;
		case 61:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/61.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/61.png");
			this->sprite.setTexture(this->texture);
			break;
		case 62:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/62.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/62.png");
			this->sprite.setTexture(this->texture);
			break;
		case 63:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/63.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/63.png");
			this->sprite.setTexture(this->texture);
			break;
		case 64:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/64.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/64.png");
			this->sprite.setTexture(this->texture);
			break;
		case 65:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/65.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/65.png");
			this->sprite.setTexture(this->texture);
			break;
		case 66:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/66.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/66.png");
			this->sprite.setTexture(this->texture);
			break;
		case 67:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/67.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/67.png");
			this->sprite.setTexture(this->texture);
			break;
		case 68:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/68.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/68.png");
			this->sprite.setTexture(this->texture);
			break;
		case 69:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/69.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/69.png");
			this->sprite.setTexture(this->texture);
			break;
		case 70:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/70.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/70.png");
			this->sprite.setTexture(this->texture);
			break;
		case 71:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/71.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/71.png");
			this->sprite.setTexture(this->texture);
			break;
		case 72:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/72.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/72.png");
			this->sprite.setTexture(this->texture);
			break;
		case 73:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/73.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/73.png");
			this->sprite.setTexture(this->texture);
			break;
		case 74:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/74.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/74.png");
			this->sprite.setTexture(this->texture);
			break;
		case 75:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/75.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/75.png");
			this->sprite.setTexture(this->texture);
			break;
		case 76:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/76.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/76.png");
			this->sprite.setTexture(this->texture);
			break;
		case 77:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/77.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/77.png");
			this->sprite.setTexture(this->texture);
			break;
		case 78:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/78.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/78.png");
			this->sprite.setTexture(this->texture);
			break;
		case 79:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/79.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/79.png");
			this->sprite.setTexture(this->texture);
			break;
		case 80:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/80.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/80.png");
			this->sprite.setTexture(this->texture);
			break;
		case 81:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/81.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/81.png");
			this->sprite.setTexture(this->texture);
			break;
		case 82:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/82.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/82.png");
			this->sprite.setTexture(this->texture);
			break;
		case 83:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/83.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/83.png");
			this->sprite.setTexture(this->texture);
			break;
		case 84:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/84.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/84.png");
			this->sprite.setTexture(this->texture);
			break;
		case 85:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/85.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/85.png");
			this->sprite.setTexture(this->texture);
			break;
		case 86:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/86.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/86.png");
			this->sprite.setTexture(this->texture);
			break;
		case 87:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/87.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/87.png");
			this->sprite.setTexture(this->texture);
			break;
		case 88:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/88.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/88.png");
			this->sprite.setTexture(this->texture);
			break;
		case 89:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/89.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/9.png");
			this->sprite.setTexture(this->texture);
			break;
		case 90:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/90.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/10.png");
			this->sprite.setTexture(this->texture);
			break;
		case 91:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/91.png"))
				throw("ERROR::NEWCHARACTERSCREEN::FAILED_TO_LOAD::Female/91.png");
			this->sprite.setTexture(this->texture);
			break;
		default:
			std::cout << "ERROR::NEWCHARACTERSCREEN::void updateTexture()::Invalid Switch Entry!\n";
		}
	this->spriteIntRect = sf::IntRect(32, 0, 32, 32);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->spriteIntRect);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x - 2.f, this->spriteRect.getPosition().y - 1.f));
}

/*Constructor & Destructor*/
Player::Player(std::map<std::string, int>* supported_keys, PlayerDetails player_details)
{
	this->initVariables(player_details);
	this->initKeybinds(supported_keys);
	this->initSpriteRect();
	this->initSprite();
}
Player::~Player()
{
}

/*Setters*/
void Player::setOldDirection(PlayerDirection old_direction)
{
	this->playerDetails.oldDirection = old_direction;
}
void Player::setPosition(sf::Vector2f player_position)
{
	this->spriteRect.setPosition(player_position);
}
void Player::setManaFill(float mana_fill)
{
	this->playerDetails.currentMana += mana_fill;
}
void Player::setManaDrain(float mana_drain)
{
	this->playerDetails.currentMana -= mana_drain;
}
void Player::setItemBenefits(ItemDetails item_details)
{
	switch (item_details.itemType)
	{
	case ItemType::HP_Potion:
		this->playerDetails.currentHP += item_details.hp; 
		if (this->playerDetails.currentHP > this->playerDetails.maxHP)
			this->playerDetails.currentHP = this->playerDetails.maxHP;
		break;
	case ItemType::Stamina_Potion:
		this->playerDetails.currentStamina += item_details.stamina;
		if (this->playerDetails.currentStamina > this->playerDetails.maxStamina)
			this->playerDetails.currentStamina = this->playerDetails.maxStamina;
		break;
	case ItemType::Mana_Potion:
		this->playerDetails.currentMana += item_details.mana;
		if (this->playerDetails.currentMana > this->playerDetails.maxMana)
			this->playerDetails.currentMana = this->playerDetails.maxMana;;
		break;
	default:
		std::cout << "ERROR::PLAYER::void Item::void Player::setItemBenefits(ItemDetails item_details)::Invalid Switch Entry!\n";
	}
}

/*Getters*/
std::tuple<bool, std::string> Player::getDoorInfo()
{
	return std::make_tuple(this->doorCollision, this->doorName);
}
sf::RectangleShape Player::getSpriteRect()
{
	return this->spriteRect;
}
PlayerDirection Player::getPlayerDirection()
{
	return this->playerDetails.oldDirection;
}
PlayerDetails Player::getPlayerDetails()
{
	return this->playerDetails;
}
std::tuple<float, float> Player::getMana()
{
	return std::make_tuple(this->playerDetails.currentMana, this->playerDetails.maxMana);
}

/*Collision Functions*/
void Player::tileCollision(std::tuple<bool, unsigned short, std::string_view> collision_tuple)
{
	if (std::get<0>(collision_tuple) == true && std::get<1>(collision_tuple) == TILEMAP::TileType::Wall)
	{
		this->wallCollision = true;
		std::cout << "Wall Collision: " << this->wallCollision << '\n';
	}
	else
		this->wallCollision = false;

	if (std::get<0>(collision_tuple) == true && std::get<1>(collision_tuple) == TILEMAP::TileType::Door)
	{
		this->doorCollision = true;
		std::cout << "Player/Door Collision!\n";
		this->doorName = std::get<2>(collision_tuple);

		std::cout << "Door Name: " << std::get<2>(collision_tuple) << '\n';
	}
	else
		this->doorCollision = false;


	if (this->wallCollision == true)
	{
		sf::Vector2f position = this->spriteRect.getPosition();

		if (this->playerDetails.velocity.x != 0.f)
		{
			position.x = this->oldPosition.x;
			this->playerDetails.velocity.x = 0.f;
		}

		if (this->playerDetails.velocity.y != 0.f)
		{
			position.y = this->oldPosition.y;
			this->playerDetails.velocity.y = 0.f;
		}

		this->spriteRect.setPosition(position);
	}
}
void Player::enemyCollision(std::tuple<sf::RectangleShape, float, bool> enemy_tuple)
{
	if (std::get<0>(enemy_tuple).getGlobalBounds().intersects(this->spriteRect.getGlobalBounds()))
	{
		this->enemyCollisionBool = true;
	}
	else 
		this->enemyCollisionBool = false;

	sf::Vector2f playerPosition = sf::Vector2f(this->spriteRect.getPosition()); 
	sf::Vector2f enemyPosition = sf::Vector2f(std::get<0>(enemy_tuple).getPosition()); 

	float differenceX = std::abs(playerPosition.x - enemyPosition.x); 
	float differenceY = std::abs(playerPosition.y - enemyPosition.y); 

	float deltaTime = this->hpDrainClock.getElapsedTime().asSeconds(); 
	float switchTime = 0.5f;

	if (std::get<2>(enemy_tuple) == true && (differenceX < 30.f && differenceY < 35.f))
	{
		if (deltaTime > switchTime)
		{
			if (this->playerDetails.currentHP > 0.f)
			{
				this->playerDetails.currentHP -= std::get<1>(enemy_tuple);
				std::cout << "Current HP: " << this->playerDetails.currentHP << '\n';

				if (this->playerDetails.currentHP < 0.f)
					this->playerDetails.currentHP = 0.f;

				this->hpDrainClock.restart();
			}
		}
	}

	if (this->enemyCollisionBool == true)
	{
		sf::Vector2f position = this->spriteRect.getPosition();

		if (this->playerDetails.velocity.x != 0.f)
		{
			position.x = this->oldPosition.x;
			this->playerDetails.velocity.x = 0.f;
		}

		if (this->playerDetails.velocity.y != 0.f)
		{
			position.y = this->oldPosition.y;
			this->playerDetails.velocity.y = 0.f;
		}

		this->spriteRect.setPosition(position);
	}
}

/*Update Functions*/
void Player::updateStamina()
{
	if (this->playerDetails.currentStamina > 0.f && (this->playerDirection == PlayerDirection::Up
		|| this->playerDirection == PlayerDirection::Down
		|| this->playerDirection == PlayerDirection::Left
		|| this->playerDirection == PlayerDirection::Right))
		this->playerDetails.currentStamina -= this->playerDetails.staminaDrainFactor;

	if (this->playerDetails.currentStamina < 0.f)
		this->playerDetails.currentStamina = 0.f;

	if (this->playerDetails.currentStamina == 0.f)
		this->playerDetails.maxVelocity = this->quarterMaxVelocity;
	else if (this->playerDetails.currentStamina > 0.f)
		this->playerDetails.maxVelocity = this->quarterMaxVelocity * 4.f;

	if (this->playerDetails.currentStamina < this->playerDetails.maxStamina && this->playerDirection == PlayerDirection::Idle)
		this->playerDetails.currentStamina += this->playerDetails.staminaFillFactor;

	/*std::cout << "Stamina: " << this->playerDetails.currentStamina << '\n';
	std::cout << "Max Velocity: " << this->playerDetails.maxVelocity << '\n';*/
}
void Player::updateUserInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("UP"))))
	{
		this->playerDirection = PlayerDirection::Up;
		this->playerDetails.oldDirection = PlayerDirection::Up;
		this->updateVelocity(0.f, -1.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DOWN"))))
	{
		this->playerDirection = PlayerDirection::Down;
		this->playerDetails.oldDirection = PlayerDirection::Down;
		this->updateVelocity(0.f, 1.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT"))))
	{
		this->playerDirection = PlayerDirection::Left;
		this->playerDetails.oldDirection = PlayerDirection::Left;
		this->updateVelocity(-1.f, 0.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("RIGHT"))))
	{
		this->playerDirection = PlayerDirection::Right;
		this->playerDetails.oldDirection = PlayerDirection::Right;
		this->updateVelocity(1.f, 0.f, dt);
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("UP")))
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DOWN")))
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("LEFT")))
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("RIGHT"))))
	{
		this->playerDirection = PlayerDirection::Idle;
		this->updateVelocity(0.f, 0.f, dt);
	}
}
void Player::updateVelocity(float dir_x, float dir_y, const float& dt)
{
	this->playerDetails.velocity.x += this->playerDetails.acceleration * dir_x;
	this->playerDetails.velocity.y += this->playerDetails.acceleration * dir_y;

	this->updateMovement(dt);
}
void Player::updateMovement(const float& dt)
{
	/*Up*/
	if (this->playerDetails.velocity.y < 0.f)
	{
		if (this->playerDetails.velocity.y < -this->playerDetails.maxVelocity)
			this->playerDetails.velocity.y = -this->playerDetails.maxVelocity;

		this->playerDetails.velocity.y += this->playerDetails.deceleration;

		if (this->playerDetails.velocity.y > 0.f)
			this->playerDetails.velocity.y = 0.f;
	}
	/*Down*/
	else if (this->playerDetails.velocity.y > 0.f)
	{
		if (this->playerDetails.velocity.y > this->playerDetails.maxVelocity)
			this->playerDetails.velocity.y = this->playerDetails.maxVelocity;

		this->playerDetails.velocity.y -= this->playerDetails.deceleration;

		if (this->playerDetails.velocity.y < 0.f)
			this->playerDetails.velocity.y = 0.f;
	}

	/*Left*/
	if (this->playerDetails.velocity.x < 0.f)
	{
		if (this->playerDetails.velocity.x < -this->playerDetails.maxVelocity)
			this->playerDetails.velocity.x = -this->playerDetails.maxVelocity;

		this->playerDetails.velocity.x += this->playerDetails.deceleration;

		if (this->playerDetails.velocity.x > 0.f)
			this->playerDetails.velocity.x = 0.f;
	}
	/*Right*/
	else if (this->playerDetails.velocity.x > 0.f)
	{
		if (this->playerDetails.velocity.x > this->playerDetails.maxVelocity)
			this->playerDetails.velocity.x = this->playerDetails.maxVelocity;

		this->playerDetails.velocity.x -= this->playerDetails.deceleration;

		if (this->playerDetails.velocity.x < 0.f)
			this->playerDetails.velocity.x = 0.f;
	}

	this->oldPosition = this->spriteRect.getPosition();
	this->spriteRect.move(sf::Vector2f(this->playerDetails.velocity.x * dt, this->playerDetails.velocity.y * dt));
	this->updateAnimation();
}
void Player::updateAnimation()
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
			else if (this->playerDirection == PlayerDirection::Idle)
			{
				if (this->playerDetails.oldDirection == PlayerDirection::Up)
				{
				this->spriteIntRect = idleUp;
				this->sprite.setTextureRect(this->spriteIntRect);
				}
				else if (this->playerDetails.oldDirection == PlayerDirection::Down)
				{
				this->spriteIntRect = idleDown;
				this->sprite.setTextureRect(this->spriteIntRect);
				}
				else if (this->playerDetails.oldDirection == PlayerDirection::Left)
				{
				this->spriteIntRect = idleLeft;
				this->sprite.setTextureRect(this->spriteIntRect);
				}
				else if (this->playerDetails.oldDirection == PlayerDirection::Right)
				{
				this->spriteIntRect = idleRight;
				this->sprite.setTextureRect(this->spriteIntRect);
				}
			}
	}
}
void Player::update(const float& dt)
{
	this->updateStamina();
	this->updateUserInput(dt);
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x - 2.f, this->spriteRect.getPosition().y - 1.f));
}

/*Save & Load Functions*/
void Player::saveToFile()
{
	this->playerDetails.position = this->spriteRect.getPosition();

	std::ofstream ofs("Config/player_details.ini");

	if (ofs.is_open())
	{
		/*New Character Variable*/
		ofs << this->playerDetails.name << '\n';
		ofs << this->playerDetails.textureSwitchCounter << '\n';
		ofs << this->playerDetails.male1Female0 << '\n';

		/*Position & Direction*/
		ofs << this->playerDetails.position.x << " " << this->playerDetails.position.y << '\n';
		ofs << static_cast<int>(this->playerDetails.oldDirection) << '\n';

		/*Movement Variables*/
		ofs << this->playerDetails.velocity.x << " " << this->playerDetails.velocity.y << '\n';
		ofs << this->playerDetails.maxVelocity << '\n';
		ofs << this->playerDetails.acceleration << '\n';
		ofs << this->playerDetails.deceleration << '\n';

		/*Level*/
		ofs << this->playerDetails.level << '\n';

		/*HP*/
		ofs << this->playerDetails.currentHP << '\n';
		ofs << this->playerDetails.maxHP << '\n';

		/*Stamina*/
		ofs << this->playerDetails.currentStamina << '\n';
		ofs << this->playerDetails.maxStamina << '\n';
		ofs << this->playerDetails.staminaDrainFactor << '\n';
		ofs << this->playerDetails.staminaFillFactor << '\n';

		/*Mana*/
		ofs << this->playerDetails.currentMana << '\n';
		ofs << this->playerDetails.maxMana << '\n';
	}
	ofs.close();
}

/*Render Functions*/
void Player::render(sf::RenderTarget& target)
{
	target.draw(this->spriteRect);
	target.draw(this->sprite);
}

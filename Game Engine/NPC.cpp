#include "Header.h"
#include "NPC.h"

/*Initializers*/
void NPC::initVariables(std::vector<sf::Vector2f> npc_spawn_positions, std::vector<sf::Vector2f> path_finder_markings)
{
	/*Random Number Generator Seed*/
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);

	/*Emote State*/
	this->npcDetails.emoteState = NPCEmoteStates::Default;

	/*Movement Variables*/
	this->npcDetails.velocity = sf::Vector2f(0.f, 0.f);
	this->npcDetails.maxVelocity = 384.f;
	this->npcDetails.acceleration = 26.f;
	this->npcDetails.deceleration = 19.f;

	/*Spawn Random Position Vector*/
	this->npcDetails.enemySpawnPosition = npc_spawn_positions[this->getRandomInt(0, npc_spawn_positions.size())];
	//std::cout << "Random Number: " << this->getRandomInt(0, npc_spawn_positions.size()) << '\n';

	/*Path Finder Markings*/
	this->npcDetails.pathFinderMarkings = path_finder_markings;

	/*Randomization Variables*/
	this->randomDirectionCounter = 0;
	this->randomDirectionNumber = this->getRandomInt(0, 5);

	/*Male/Female Bool*/
	this->male1Female0 = this->getRandomInt(0, 2);

	/*Item Text & Font*/
	this->character = 0;

	/*Collision Variables*/
	this->projectileCollisionBool = false;
	this->playerCollisionBool = false;
	this->alertCircleCollisionBool = false;
	this->playerCollisionBool = false;
	this->wallCollision = false;

	/*Destroy Variables*/
	this->destroy = false;

	/*AI Variables*/
	this->goingAroundWall = false;
	this->interactWithPlayer = false;
	this->talkingToPlayer = false;
	this->directionNumber = 0;
}
void NPC::initSpriteRect()
{
	/*Enemy Sprite Rect*/
	this->spriteRect.setSize(sf::Vector2f(26.f, 32.f));
	this->spriteRect.setOutlineThickness(1.f);
	this->spriteRect.setOutlineColor(sf::Color::Transparent);
	this->spriteRect.setFillColor(sf::Color::Transparent);
	this->spriteRect.setOrigin(this->spriteRect.getGlobalBounds().width / 2.f, this->spriteRect.getGlobalBounds().height / 2.f);

	/*Alert Circle*/
	this->alertCircle = sf::CircleShape(200);
	this->alertCircle.setOutlineThickness(1.f);
	this->alertCircle.setOutlineColor(sf::Color::Magenta);
	this->alertCircle.setFillColor(sf::Color::Transparent);
	this->alertCircle.setOrigin(this->alertCircle.getGlobalBounds().width / 2.f, this->alertCircle.getGlobalBounds().height / 2.f);
	this->alertCircle.setPosition(this->spriteRect.getPosition());
}
void NPC::initSprite(bool male_1_female_0, int texture_switch_number)
{
	/*Enemy Sprite*/
	this->spriteIntRect = sf::IntRect(32, 0, 32, 32);
	this->setNPC(male_1_female_0, texture_switch_number);
	this->sprite.setTextureRect(this->spriteIntRect);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x - 2.f, this->spriteRect.getPosition().y - 1.f));

	/*Emote Sprite*/
	this->emoteIntRect = sf::IntRect(0, 0, 32, 32);
	this->emoteSprite.setTextureRect(this->emoteIntRect);
	this->emoteSprite.setOrigin(this->emoteSprite.getGlobalBounds().width / 2.f, this->emoteSprite.getGlobalBounds().height / 2.f);
	this->emoteSprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y - 50.f));
}
void NPC::initText()
{
	if (!this->font.loadFromFile("Resources/Fonts/BreatheFire.ttf"))
		throw ("ERROR::NPC::FAILED_TO_LOAD:BreatheFire.ttf");

	/*Show NPC Text Bool*/
	this->showNPCText = false; 

	/*Text Shape*/
	this->textBackground.setSize(sf::Vector2f(325.f, 150.f));
	this->textBackground.setOrigin(this->textBackground.getGlobalBounds().width / 2.f, this->textBackground.getGlobalBounds().height / 2.f);
	this->textBackground.setFillColor(sf::Color(0, 0, 0, 225));
	this->textBackground.setOutlineThickness(1.f);
	this->textBackground.setOutlineColor(sf::Color::White);

	/*Text Name Shape*/
	this->textNameShape.setSize(sf::Vector2f(105.f, 30.f));
	this->textNameShape.setOrigin(this->textNameShape.getGlobalBounds().width / 2.f, this->textNameShape.getGlobalBounds().height / 2.f);
	this->textNameShape.setFillColor(sf::Color::Transparent);
	this->textNameShape.setOutlineThickness(1.f);
	this->textNameShape.setOutlineColor(sf::Color::Transparent);

	/*Text Name*/
	this->textName.setFont(font);
	this->textName.setFillColor(sf::Color::White);
	this->textName.setCharacterSize(20);
	this->textName.setString(this->npcDetails.name);
	this->textName.setOrigin(this->textName.getGlobalBounds().width / 2.f, this->textName.getGlobalBounds().height / 2.f);
	this->textName.setPosition(sf::Vector2f(this->textNameShape.getPosition().x, this->textNameShape.getPosition().y - static_cast<float>(this->textName.getCharacterSize()) / 4.f));

	/*Text Body Shape*/
	this->textBodyShape.setSize(sf::Vector2f(this->textBackground.getSize().x, this->textBackground.getSize().y - this->textNameShape.getSize().y));
	this->textBodyShape.setOrigin(this->textBodyShape.getGlobalBounds().width / 2.f, this->textBodyShape.getGlobalBounds().height / 2.f);
	this->textBodyShape.setFillColor(sf::Color::Transparent);
	this->textBodyShape.setOutlineThickness(1.f);
	this->textBodyShape.setOutlineColor(sf::Color::Transparent);

	/*Text Body*/
	this->textBody.setFont(font);
	this->textBody.setFillColor(sf::Color::White);
	this->textBody.setCharacterSize(15);
}

/*Constructor & Destructor*/
NPC::NPC(
	std::vector<sf::Vector2f> npc_spawn_positions, 
	std::vector<sf::Vector2f> path_finder_markings, 
	bool male_1_female_0, 
	int texture_switch_number, 
	std::map<std::string, std::unique_ptr<Audio>>& audio_map
)
	:Entity(audio_map)
{
	this->initVariables(npc_spawn_positions, path_finder_markings);
	this->initSpriteRect();
	this->initSprite(male_1_female_0, texture_switch_number);
	this->initText();
}
NPC::~NPC()
{
}

/*Setters*/
void NPC::setNPCPosition()
{
	this->spriteRect.setPosition(this->npcDetails.enemySpawnPosition);
}
void NPC::setNPC(bool male_1_female_0, int texture_switch_number)
{
	if (male_1_female_0)
		switch (texture_switch_number)
		{
		case 1:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/1.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/1.png");
			this->sprite.setTexture(this->texture);
			break;
		case 2:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/2.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/2.png");
			this->sprite.setTexture(this->texture);
			break;
		case 3:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/3.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/3.png");
			this->sprite.setTexture(this->texture);
			break;
		case 4:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/4.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/4.png");
			this->sprite.setTexture(this->texture);
			break;
		case 5:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/5.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/5.png");
			this->sprite.setTexture(this->texture);
			break;
		case 6:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/6.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/6.png");
			this->sprite.setTexture(this->texture);
			break;
		case 7:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/7.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/7.png");
			this->sprite.setTexture(this->texture);
			break;
		case 8:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/8.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/8.png");
			this->sprite.setTexture(this->texture);
			break;
		case 9:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/9.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/9.png");
			this->sprite.setTexture(this->texture);
			break;
		case 10:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/10.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/10.png");
			this->sprite.setTexture(this->texture);
			break;
		case 11:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/11.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/11.png");
			this->sprite.setTexture(this->texture);
			break;
		case 12:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/12.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/12.png");
			this->sprite.setTexture(this->texture);
			break;
		case 13:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/13.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/13.png");
			this->sprite.setTexture(this->texture);
			break;
		case 14:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/14.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/14.png");
			this->sprite.setTexture(this->texture);
			break;
		case 15:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/15.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/15.png");
			this->sprite.setTexture(this->texture);
			break;
		case 16:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/16.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/16.png");
			this->sprite.setTexture(this->texture);
			break;
		case 17:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/17.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/17.png");
			this->sprite.setTexture(this->texture);
			break;
		case 18:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/18.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/18.png");
			this->sprite.setTexture(this->texture);
			break;
		case 19:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/19.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/19.png");
			this->sprite.setTexture(this->texture);
			break;
		case 20:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/20.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/20.png");
			this->sprite.setTexture(this->texture);
			break;
		case 21:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/21.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/21.png");
			this->sprite.setTexture(this->texture);
			break;
		case 22:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/22.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/22.png");
			this->sprite.setTexture(this->texture);
			break;
		case 23:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/23.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/23.png");
			this->sprite.setTexture(this->texture);
			break;
		case 24:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/24.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/24.png");
			this->sprite.setTexture(this->texture);
			break;
		case 25:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/25.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/25.png");
			this->sprite.setTexture(this->texture);
			break;
		case 26:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/26.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/26.png");
			this->sprite.setTexture(this->texture);
			break;
		case 27:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/27.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/27.png");
			this->sprite.setTexture(this->texture);
			break;
		case 28:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/28.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/28.png");
			this->sprite.setTexture(this->texture);
			break;
		case 29:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/29.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/9.png");
			this->sprite.setTexture(this->texture);
			break;
		case 30:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/30.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/30.png");
			this->sprite.setTexture(this->texture);
			break;
		case 31:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/31.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/31.png");
			this->sprite.setTexture(this->texture);
			break;
		case 32:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/32.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/32.png");
			this->sprite.setTexture(this->texture);
			break;
		case 33:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/33.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/33.png");
			this->sprite.setTexture(this->texture);
			break;
		case 34:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/34.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/34.png");
			this->sprite.setTexture(this->texture);
			break;
		case 35:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/35.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/35.png");
			this->sprite.setTexture(this->texture);
			break;
		case 36:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/36.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/36.png");
			this->sprite.setTexture(this->texture);
			break;
		case 37:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/37.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/37.png");
			this->sprite.setTexture(this->texture);
			break;
		case 38:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/38.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/38.png");
			this->sprite.setTexture(this->texture);
			break;
		case 39:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/39.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/39.png");
			this->sprite.setTexture(this->texture);
			break;
		case 40:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/40.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/40.png");
			this->sprite.setTexture(this->texture);
			break;
		case 41:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/41.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/41.png");
			this->sprite.setTexture(this->texture);
			break;
		case 42:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/42.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/42.png");
			this->sprite.setTexture(this->texture);
			break;
		case 43:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/43.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/43.png");
			this->sprite.setTexture(this->texture);
			break;
		case 44:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/44.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/44.png");
			this->sprite.setTexture(this->texture);
			break;
		case 45:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/45.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/45.png");
			this->sprite.setTexture(this->texture);
			break;
		case 46:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/46.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/46.png");
			this->sprite.setTexture(this->texture);
			break;
		case 47:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/47.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/47.png");
			this->sprite.setTexture(this->texture);
			break;
		case 48:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/48.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/48.png");
			this->sprite.setTexture(this->texture);
			break;
		case 49:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/49.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/49.png");
			this->sprite.setTexture(this->texture);
			break;
		case 50:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/50.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/50.png");
			this->sprite.setTexture(this->texture);
			break;
		case 51:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/51.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/51.png");
			this->sprite.setTexture(this->texture);
			break;
		case 52:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/52.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/52.png");
			this->sprite.setTexture(this->texture);
			break;
		case 53:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/53.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/53.png");
			this->sprite.setTexture(this->texture);
			this->npcDetails.name = "Lydian: ";
			this->npcDetails.dialog1 = "The library started funding drag queen story hour.\n They said if you don't let your child\n sit on their lap, you're a bigot.\n Is that normal?\n";
			break;
		case 54:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/54.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/54.png");
			this->sprite.setTexture(this->texture);
			break;
		case 55:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/55.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/55.png");
			this->sprite.setTexture(this->texture);
			break;
		case 56:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/56.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/56.png");
			this->sprite.setTexture(this->texture);
			break;
		case 57:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/57.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/57.png");
			this->sprite.setTexture(this->texture);
			break;
		case 58:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/58.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/58.png");
			this->sprite.setTexture(this->texture);
			break;
		case 59:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/59.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/59.png");
			this->sprite.setTexture(this->texture);
			break;
		case 60:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/60.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/60.png");
			this->sprite.setTexture(this->texture);
			break;
		case 61:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/61.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/61.png");
			this->sprite.setTexture(this->texture);
			break;
		case 62:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/62.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/62.png");
			this->sprite.setTexture(this->texture);
			break;
		case 63:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/63.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/63.png");
			this->sprite.setTexture(this->texture);
			break;
		case 64:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/64.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/64.png");
			this->sprite.setTexture(this->texture);
			break;
		case 65:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/65.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/65.png");
			this->sprite.setTexture(this->texture);
			break;
		case 66:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/66.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/66.png");
			this->sprite.setTexture(this->texture);
			break;
		case 67:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/67.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/67.png");
			this->sprite.setTexture(this->texture);
			break;
		case 68:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/68.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/68.png");
			this->sprite.setTexture(this->texture);
			break;
		case 69:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Male/69.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Male/69.png");
			this->sprite.setTexture(this->texture);
			break;
		default:
			std::cout << "ERROR::NPC::void setNPC() (MALE)::Invalid Switch Entry!\n";
		}
	else if (!male_1_female_0)
		switch (texture_switch_number)
		{
		case 1:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/1.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/1.png");
			this->sprite.setTexture(this->texture);
			break;
		case 2:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/2.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/2.png");
			this->sprite.setTexture(this->texture);
			break;
		case 3:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/3.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/3.png");
			this->sprite.setTexture(this->texture);
			break;
		case 4:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/4.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/4.png");
			this->sprite.setTexture(this->texture);
			break;
		case 5:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/5.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/5.png");
			this->sprite.setTexture(this->texture);
			break;
		case 6:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/6.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/6.png");
			this->sprite.setTexture(this->texture);
			break;
		case 7:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/7.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/7.png");
			this->sprite.setTexture(this->texture);
			break;
		case 8:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/8.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/8.png");
			this->sprite.setTexture(this->texture);
			break;
		case 9:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/9.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/9.png");
			this->sprite.setTexture(this->texture);
			this->npcDetails.name = "Aeolian: ";
			this->npcDetails.dialog1 = "Wow, that's something that Joe Biden won.\n I didn't think he had a chance.\n How do you when the election with no audience?\n";
			break;
		case 10:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/10.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/10.png");
			this->sprite.setTexture(this->texture);
			break;
		case 11:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/11.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/11.png");
			this->sprite.setTexture(this->texture);
			break;
		case 12:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/12.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/12.png");
			this->sprite.setTexture(this->texture);
			break;
		case 13:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/13.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/13.png");
			this->sprite.setTexture(this->texture);
			break;
		case 14:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/14.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/14.png");
			this->sprite.setTexture(this->texture);
			break;
		case 15:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/15.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/15.png");
			this->sprite.setTexture(this->texture);
			break;
		case 16:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/16.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/16.png");
			this->sprite.setTexture(this->texture);
			break;
		case 17:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/17.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/17.png");
			this->sprite.setTexture(this->texture);
			this->npcDetails.name = "Pali: ";
			this->npcDetails.dialog1 = "I took the COVID-19 vaccine and now I feel funny.\n Once they enacted the 5G my mood has been different.\n Do you think it could have been posion?\n";
			break;
		case 18:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/18.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/18.png");
			this->sprite.setTexture(this->texture);
			break;
		case 19:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/19.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/19.png");
			this->sprite.setTexture(this->texture);
			break;
		case 20:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/20.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/20.png");
			this->sprite.setTexture(this->texture);
			break;
		case 21:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/21.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/21.png");
			this->sprite.setTexture(this->texture);
			break;
		case 22:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/22.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/22.png");
			this->sprite.setTexture(this->texture);
			break;
		case 23:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/23.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/23.png");
			this->sprite.setTexture(this->texture);
			break;
		case 24:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/24.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/24.png");
			this->sprite.setTexture(this->texture);
			break;
		case 25:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/25.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/25.png");
			this->sprite.setTexture(this->texture);
			break;
		case 26:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/26.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/26.png");
			this->sprite.setTexture(this->texture);
			break;
		case 27:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/27.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/27.png");
			this->sprite.setTexture(this->texture);
			break;
		case 28:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/28.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/28.png");
			this->sprite.setTexture(this->texture);
			break;
		case 29:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/29.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/9.png");
			this->sprite.setTexture(this->texture);
			break;
		case 30:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/30.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/30.png");
			this->sprite.setTexture(this->texture);
			break;
		case 31:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/31.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/31.png");
			this->sprite.setTexture(this->texture);
			break;
		case 32:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/32.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/32.png");
			this->sprite.setTexture(this->texture);
			break;
		case 33:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/33.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/33.png");
			this->sprite.setTexture(this->texture);
			break;
		case 34:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/34.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/34.png");
			this->sprite.setTexture(this->texture);
			break;
		case 35:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/35.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/35.png");
			this->sprite.setTexture(this->texture);
			break;
		case 36:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/36.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/36.png");
			this->sprite.setTexture(this->texture);
			break;
		case 37:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/37.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/37.png");
			this->sprite.setTexture(this->texture);
			break;
		case 38:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/38.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/38.png");
			this->sprite.setTexture(this->texture);
			break;
		case 39:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/39.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/39.png");
			this->sprite.setTexture(this->texture);
			break;
		case 40:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/40.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/40.png");
			this->sprite.setTexture(this->texture);
			break;
		case 41:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/41.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/41.png");
			this->sprite.setTexture(this->texture);
			break;
		case 42:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/42.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/42.png");
			this->sprite.setTexture(this->texture);
			break;
		case 43:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/43.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/43.png");
			this->sprite.setTexture(this->texture);
			break;
		case 44:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/44.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/44.png");
			this->sprite.setTexture(this->texture);
			break;
		case 45:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/45.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/45.png");
			this->sprite.setTexture(this->texture);
			break;
		case 46:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/46.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/46.png");
			this->sprite.setTexture(this->texture);
			break;
		case 47:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/47.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/47.png");
			this->sprite.setTexture(this->texture);
			break;
		case 48:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/48.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/48.png");
			this->sprite.setTexture(this->texture);
			break;
		case 49:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/49.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/49.png");
			this->sprite.setTexture(this->texture);
			break;
		case 50:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/50.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/50.png");
			this->sprite.setTexture(this->texture);
			break;
		case 51:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/51.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/51.png");
			this->sprite.setTexture(this->texture);
			break;
		case 52:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/52.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/52.png");
			this->sprite.setTexture(this->texture);
			break;
		case 53:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/53.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/53.png");
			this->sprite.setTexture(this->texture);
			break;
		case 54:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/54.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/54.png");
			this->sprite.setTexture(this->texture);
			break;
		case 55:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/55.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/55.png");
			this->sprite.setTexture(this->texture);
			break;
		case 56:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/56.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/56.png");
			this->sprite.setTexture(this->texture);
			break;
		case 57:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/57.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/57.png");
			this->sprite.setTexture(this->texture);
			break;
		case 58:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/58.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/58.png");
			this->sprite.setTexture(this->texture);
			break;
		case 59:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/59.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/59.png");
			this->sprite.setTexture(this->texture);
			break;
		case 60:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/60.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/60.png");
			this->sprite.setTexture(this->texture);
			break;
		case 61:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/61.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/61.png");
			this->sprite.setTexture(this->texture);
			break;
		case 62:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/62.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/62.png");
			this->sprite.setTexture(this->texture);
			break;
		case 63:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/63.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/63.png");
			this->sprite.setTexture(this->texture);
			break;
		case 64:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/64.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/64.png");
			this->sprite.setTexture(this->texture);
			break;
		case 65:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/65.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/65.png");
			this->sprite.setTexture(this->texture);
			break;
		case 66:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/66.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/66.png");
			this->sprite.setTexture(this->texture);
			break;
		case 67:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/67.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/67.png");
			this->sprite.setTexture(this->texture);
			break;
		case 68:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/68.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/68.png");
			this->sprite.setTexture(this->texture);
			break;
		case 69:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/69.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/69.png");
			this->sprite.setTexture(this->texture);
			break;
		case 70:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/70.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/70.png");
			this->sprite.setTexture(this->texture);
			break;
		case 71:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/71.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/71.png");
			this->sprite.setTexture(this->texture);
			break;
		case 72:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/72.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/72.png");
			this->sprite.setTexture(this->texture);
			break;
		case 73:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/73.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/73.png");
			this->sprite.setTexture(this->texture);
			break;
		case 74:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/74.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/74.png");
			this->sprite.setTexture(this->texture);
			break;
		case 75:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/75.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/75.png");
			this->sprite.setTexture(this->texture);
			break;
		case 76:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/76.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/76.png");
			this->sprite.setTexture(this->texture);
			break;
		case 77:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/77.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/77.png");
			this->sprite.setTexture(this->texture);
			break;
		case 78:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/78.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/78.png");
			this->sprite.setTexture(this->texture);
			break;
		case 79:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/79.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/79.png");
			this->sprite.setTexture(this->texture);
			break;
		case 80:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/80.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/80.png");
			this->sprite.setTexture(this->texture);
			break;
		case 81:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/81.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/81.png");
			this->sprite.setTexture(this->texture);
			break;
		case 82:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/82.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/82.png");
			this->sprite.setTexture(this->texture);
			break;
		case 83:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/83.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/83.png");
			this->sprite.setTexture(this->texture);
			break;
		case 84:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/84.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/84.png");
			this->sprite.setTexture(this->texture);
			break;
		case 85:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/85.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/85.png");
			this->sprite.setTexture(this->texture);
			break;
		case 86:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/86.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/86.png");
			this->sprite.setTexture(this->texture);
			break;
		case 87:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/87.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/87.png");
			this->sprite.setTexture(this->texture);
			break;
		case 88:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/88.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/88.png");
			this->sprite.setTexture(this->texture);
			break;
		case 89:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/89.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/9.png");
			this->sprite.setTexture(this->texture);
			break;
		case 90:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/90.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/10.png");
			this->sprite.setTexture(this->texture);
			break;
		case 91:
			if (!this->texture.loadFromFile("Resources/Images/Characters/Female/91.png"))
				throw("ERROR::NPC::FAILED_TO_LOAD::Female/91.png");
			this->sprite.setTexture(this->texture);
			break;
		default:
			std::cout << "ERROR::NPC::void setNPC() (FEMALE)::Invalid Switch Entry!\n";
		}
}
void NPC::setEmoteState(NPCEmoteStates emote_state)
{
	switch (emote_state)
	{
	case NPCEmoteStates::Default:
		break;
	case NPCEmoteStates::Alert_1:
		if (!this->emoteTexture.loadFromFile("Resources/Images/Emotes/alert.png"))
			throw("ERROR::NPC::FAILED_TO_LOAD::alert.png");
		emoteSprite.setTexture(this->emoteTexture);
	}
}

/*Getters*/
bool NPC::getDestroy()
{
	return this->destroy;
}
int NPC::getRandomInt(int min, int max)
{
	return rand() % max + min;
}
sf::RectangleShape NPC::getSpriteRect()
{
	return this->spriteRect;
}
std::tuple<sf::RectangleShape, float, bool> NPC::getSpriteRectDamageInteractWithPlayerBool()
{
	return std::make_tuple(this->spriteRect, this->npcDetails.damage, this->interactWithPlayer);
}



/*Collisions Functions*/
void NPC::projectileCollision(std::tuple<sf::RectangleShape, int> collision_tuple)
{
	if (std::get<0>(collision_tuple).getGlobalBounds().intersects(this->spriteRect.getGlobalBounds()))
	{
		this->projectileCollisionBool = true;
		std::cout << "Enemy/Wall Collison (from ENEMY!)\n";
	}
	else
		this->projectileCollisionBool = false;

	if (this->projectileCollisionBool)
	{
		this->npcDetails.currentHP -= std::get<1>(collision_tuple);

		if (this->npcDetails.currentHP < 0)
			this->npcDetails.currentHP = 0;

		std::cout << "Enemy HP: " << this->npcDetails.currentHP << '\n';
	}

	if (this->npcDetails.currentHP == 0)
		this->destroy = true;
}
void NPC::tileCollision(std::tuple<bool, unsigned short, std::string_view> collision_tuple)
{
	if (std::get<1>(collision_tuple) == TILEMAP::TileType::Wall || std::get<1>(collision_tuple) == TILEMAP::TileType::Invisible_Wall)
	{
		this->wallCollision = true;
		std::cout << "NPC/Wall Collision!" << '\n';
		this->randomDirectionNumber = 0;
	}
	else
		this->wallCollision = false;

	if (this->wallCollision && this->interactWithPlayer)
	{
		this->goingAroundWall = true;
		this->lastDirection = npcDetails.currentDirection;
	}

	if (this->wallCollision == true)
	{
		sf::Vector2f position = this->spriteRect.getPosition();

		if (this->npcDetails.velocity.x != 0.f)
		{
			position.x = this->oldPosition.x;
			this->npcDetails.velocity.x = 0.f;
		}

		if (this->npcDetails.velocity.y != 0.f)
		{
			position.y = this->oldPosition.y;
			this->npcDetails.velocity.y = 0.f;
		}

		this->spriteRect.setPosition(position);
	}
}
void NPC::playerCollision(sf::RectangleShape player_rect)
{
	if (this->spriteRect.getGlobalBounds().intersects(player_rect.getGlobalBounds()))
	{
		this->playerCollisionBool = true;
		
	}
	else
		this->playerCollisionBool = false;

	if (this->playerCollisionBool && this->interactWithPlayer)
		this->talkingToPlayer = true;

	if (this->playerCollisionBool == true)
	{
		sf::Vector2f position = this->spriteRect.getPosition();

		if (this->npcDetails.velocity.x != 0.f)
		{
			this->npcDetails.velocity.x = 0.f;
			position.x = this->oldPosition.x;
		}

		if (this->npcDetails.velocity.y != 0.f)
		{
			this->npcDetails.velocity.y = 0.f;
			position.y = this->oldPosition.y;
		}

		this->spriteRect.setPosition(position);
	}
}
void NPC::alertCircleCollision(sf::RectangleShape player_rect)
{
	if (this->alertCircle.getGlobalBounds().intersects(player_rect.getGlobalBounds()))
	{
		this->alertCircleCollisionBool = true;
		this->interactWithPlayer = true;
		//std::cout << "Alert Circle Player Collision Bool: " << this->alertCircleCollisionBool << '\n';
	}
	else
		this->alertCircleCollisionBool = false;

	if (this->alertCircleCollisionBool)
	{
		this->npcDetails.emoteState = NPCEmoteStates::Alert_1;
		this->setEmoteState(this->npcDetails.emoteState);
	}
	else if (!this->alertCircleCollisionBool)
	{
		this->npcDetails.emoteState = NPCEmoteStates::Default;
		this->setEmoteState(this->npcDetails.emoteState);
	}
}

/*Update Functions*/
void NPC::updateDialog()
{
	if (dialogClock.getElapsedTime().asSeconds() > 0.09 && this->character < npcDetails.dialog1.length())
	{
		this->dialogClock.restart();
		character++;
		textBody.setString(npcDetails.dialog1.substr(0, character));
		this->audioMap["NPC_TEXT_CLICK"]->play();
	}
}
void NPC::updateInteractWithPlayer(sf::RectangleShape player_rect, sf::Vector2f mouse_view, const sf::Event& smfl_events, const bool& key_time)
{
	if (this->spriteRect.getGlobalBounds().contains(mouse_view) && smfl_events.mouseButton.button == sf::Mouse::Left)
	{
		std::cout << "Clicked NPC!\n";
		this->interactWithPlayer = true;
	}

	if (this->talkingToPlayer && this->interactWithPlayer)
	{
		this->showNPCText = true;
		this->updateDialog();
	}

	float remainderX = std::abs(player_rect.getPosition().x - this->spriteRect.getPosition().x);
	float remainderY = std::abs(player_rect.getPosition().y - this->spriteRect.getPosition().y);

	if (this->talkingToPlayer && (remainderX > 20.f && remainderY > 20.f))
	{
		this->talkingToPlayer = false;
		this->interactWithPlayer = false;
		this->showNPCText = false; 
		
	if (this->character == this->npcDetails.dialog1.length())
		this->character = 0;
	}
}
void NPC::updatePath(sf::RectangleShape player_rect, const float& dt)
{
	std::vector<sf::Vector2f> closestX;
	bool swappedClosestX = false;
	do {
		swappedClosestX = false;
		for (unsigned int i = 0; i < this->npcDetails.pathFinderMarkings.size(); i++)
		{
			for (auto itj = this->npcDetails.pathFinderMarkings.begin(); itj != this->npcDetails.pathFinderMarkings.end() - 1; itj = std::next(itj))
			{
				if (std::abs(player_rect.getPosition().x - (*itj).x) > std::abs(player_rect.getPosition().x - (*std::next(itj)).x))
				{
					std::swap(*itj, *std::next(itj));
					swappedClosestX = true;
				}
			}
		}
	} while (swappedClosestX);

	closestX = this->npcDetails.pathFinderMarkings;

	std::vector<sf::Vector2f> closestY;
	bool swappedClosestY = false;
	do {
		swappedClosestY = false;
		for (unsigned int i = 0; i < this->npcDetails.pathFinderMarkings.size(); i++)
		{
			for (auto itj = this->npcDetails.pathFinderMarkings.begin(); itj != this->npcDetails.pathFinderMarkings.end() - 1; itj = std::next(itj))
			{
				if (std::abs(player_rect.getPosition().y - (*itj).y) > std::abs(player_rect.getPosition().y - (*std::next(itj)).y))
				{
					std::swap(*itj, *std::next(itj));
					swappedClosestY = true;
				}
			}
		}
	} while (swappedClosestY);

	closestY = this->npcDetails.pathFinderMarkings;

	sf::Vector2f npcPosition;

	npcPosition = this->spriteRect.getPosition();

	float remainderX_X = std::abs(npcPosition.x - closestX[0].x);
	float remainderY_Y = std::abs(npcPosition.y - closestY[0].y);


	if (this->lastDirection == NPCDirection::Left || this->lastDirection == NPCDirection::Right)
	{
		if (remainderY_Y > 10.f)
		{
			if (npcPosition.y > closestY[0].y)
			{
				this->directionNumber = 1;
				this->updateAIMovement(dt);
			}
			else if (npcPosition.y < closestY[0].y)
			{
				this->directionNumber = 2;
				this->updateAIMovement(dt);
			}
		}
		else if (remainderY_Y < 10.f)
		{
			if (npcPosition.x > closestY[0].x)
			{
				this->directionNumber = 3;
				this->updateAIMovement(dt);
			}
			else if (npcPosition.x < closestY[0].x)
			{
				this->directionNumber = 4;
				this->updateAIMovement(dt);
			}
		}
		if (std::abs(npcPosition.x - closestY[0].x) < 10.f && std::abs(npcPosition.y - closestY[0].y) < 10.f)
			this->goingAroundWall = false;
	}

	if (this->lastDirection == NPCDirection::Up || this->lastDirection == NPCDirection::Down)
	{
		if (remainderX_X > 10.f)
		{
			if (npcPosition.x > closestX[0].x)
			{
				this->directionNumber = 3;
				this->updateAIMovement(dt);
			}
			else if (npcPosition.x < closestX[0].x)
			{
				this->directionNumber = 4;
				this->updateAIMovement(dt);
			}
		}
		else if (remainderX_X < 10.f)
		{
			if (npcPosition.y > closestX[0].y)
			{
				this->directionNumber = 1;
				this->updateAIMovement(dt);
			}
			else if (npcPosition.y < closestX[0].y)
			{
				this->directionNumber = 2;
				this->updateAIMovement(dt);
			}
		}
		if (std::abs(npcPosition.x - closestX[0].x) < 10.f && std::abs(npcPosition.y - closestX[0].y) < 10.f)
			this->goingAroundWall = false;
	}
}
void NPC::updateAIDirection(sf::RectangleShape player_rect, const float& dt)
{
	sf::Vector2f playerPosition;

	playerPosition = player_rect.getPosition();

	sf::Vector2f npcPosition;

	npcPosition = this->spriteRect.getPosition();

	float remainderX = std::abs(playerPosition.x - npcPosition.x);

	if (this->goingAroundWall)
	{
		this->updatePath(player_rect, dt);

	}
	else if (!this->goingAroundWall)
	{
		if (remainderX > 20.f)
		{
			if (playerPosition.x > npcPosition.x)
			{
				this->directionNumber = 4;
				this->updateAIMovement(dt);
			}
			else if (playerPosition.x < npcPosition.x)
			{
				this->directionNumber = 3;
				this->updateAIMovement(dt);
			}
		}
		else if (remainderX < 20.f)
		{
			if (playerPosition.y > npcPosition.y)
			{
				this->directionNumber = 2;
				this->updateAIMovement(dt);
			}
			else if (playerPosition.y < npcPosition.y)
			{
				this->directionNumber = 1;
				this->updateAIMovement(dt);
			}
		}
	}
}
void NPC::updateAIMovement(const float& dt)
{
	if (this->directionNumber == 0)
	{
	this->npcDetails.currentDirection = NPCDirection::Idle;
	this->updateVelocity(0.f, 0.f, dt);
	}
	else if (this->directionNumber == 1)
	{
		this->npcDetails.currentDirection = NPCDirection::Up;
		this->npcDetails.oldDirection = NPCDirection::Up;
		this->updateVelocity(0.f, -1.f, dt);
	}
	else if (this->directionNumber == 2)
	{
		this->npcDetails.currentDirection = NPCDirection::Down;
		this->npcDetails.oldDirection = NPCDirection::Down;
		this->updateVelocity(0.f, 1.f, dt);
	}
	else if (this->directionNumber == 3)
	{
		this->npcDetails.currentDirection = NPCDirection::Left;
		this->npcDetails.oldDirection = NPCDirection::Left;
		this->updateVelocity(-1.f, 0.f, dt);
	}
	else if (this->directionNumber == 4)
	{
		this->npcDetails.currentDirection = NPCDirection::Right;
		this->npcDetails.oldDirection = NPCDirection::Right;
		this->updateVelocity(1.f, 0.f, dt);
	}
}
void NPC::updateEmoteAnimation()
{
	int intRectLeft_Start = 0;
	int intRectLeft_Middle = 32;
	int intRectLeft_End = 64;

	int intRectLeft_FrameSize = 32;

	float deltaTime = this->emoteAnimationClock.getElapsedTime().asSeconds();
	float switchTime = 0.1f;

	int counter = 0;

	if (deltaTime > switchTime)
	{
		if (this->emoteIntRect.left == intRectLeft_Start)
		{
			counter = 1;
			this->emoteIntRect.left += intRectLeft_FrameSize;
			this->emoteSprite.setTextureRect(this->emoteIntRect);
			this->emoteAnimationClock.restart();
		}
		else if (this->emoteIntRect.left == intRectLeft_Middle & counter == 1)
		{
			this->emoteIntRect.left += intRectLeft_FrameSize;
			this->emoteSprite.setTextureRect(this->emoteIntRect);
			this->emoteAnimationClock.restart();
		}
		else if (this->emoteIntRect.left == intRectLeft_Middle & counter == 0)
		{
			this->emoteIntRect.left -= intRectLeft_FrameSize;
			this->emoteSprite.setTextureRect(this->emoteIntRect);
			this->emoteAnimationClock.restart();
		}
		else if (this->emoteIntRect.left == intRectLeft_End)
		{
			counter = 0;
			this->emoteIntRect.left -= intRectLeft_FrameSize;
			this->emoteSprite.setTextureRect(this->emoteIntRect);
			this->emoteAnimationClock.restart();
		}
	}
}
void NPC::updateRandomDirection(const float& dt)
{
	if (this->randomDirectionNumber == 0)
	{
		this->npcDetails.currentDirection = NPCDirection::Idle;
		this->updateVelocity(0.f, 0.f, dt);
	}
	else if (this->randomDirectionNumber == 1)
	{
		this->npcDetails.currentDirection = NPCDirection::Up;
		this->npcDetails.oldDirection = NPCDirection::Up;
		this->updateVelocity(0.f, -1.f, dt);
	}
	else if (this->randomDirectionNumber == 2)
	{
		this->npcDetails.currentDirection = NPCDirection::Down;
		this->npcDetails.oldDirection = NPCDirection::Down;
		this->updateVelocity(0.f, 1.f, dt);
	}
	else if (this->randomDirectionNumber == 3)
	{
		this->npcDetails.currentDirection = NPCDirection::Left;
		this->npcDetails.oldDirection = NPCDirection::Left;
		this->updateVelocity(-1.f, 0.f, dt);
	}
	else if (this->randomDirectionNumber == 4)
	{
		this->npcDetails.currentDirection = NPCDirection::Right;
		this->npcDetails.oldDirection = NPCDirection::Right;
		this->updateVelocity(1.f, 0.f, dt);
	}

	this->randomDirectionCounter++;

	if (this->randomDirectionCounter > 200)
	{
		this->randomDirectionNumber = this->getRandomInt(0, 5);

		this->randomDirectionCounter = 0;
	}
}
void NPC::updateVelocity(float dir_x, float dir_y, const float& dt)
{
	this->npcDetails.velocity.x += this->npcDetails.acceleration * dir_x;
	this->npcDetails.velocity.y += this->npcDetails.acceleration * dir_y;

	this->updateMovement(dt);
}
void NPC::updateMovement(const float& dt)
{
	/*Up*/
	if (this->npcDetails.velocity.y < 0.f)
	{
		if (this->npcDetails.velocity.y < -this->npcDetails.maxVelocity)
			this->npcDetails.velocity.y = -this->npcDetails.maxVelocity;

		this->npcDetails.velocity.y += this->npcDetails.deceleration;

		if (this->npcDetails.velocity.y > 0.f)
			this->npcDetails.velocity.y = 0.f;
	}
	/*Down*/
	else if (this->npcDetails.velocity.y > 0.f)
	{
		if (this->npcDetails.velocity.y > this->npcDetails.maxVelocity)
			this->npcDetails.velocity.y = this->npcDetails.maxVelocity;

		this->npcDetails.velocity.y -= this->npcDetails.deceleration;

		if (this->npcDetails.velocity.y < 0.f)
			this->npcDetails.velocity.y = 0.f;
	}

	/*Left*/
	if (this->npcDetails.velocity.x < 0.f)
	{
		if (this->npcDetails.velocity.x < -this->npcDetails.maxVelocity)
			this->npcDetails.velocity.x = -this->npcDetails.maxVelocity;

		this->npcDetails.velocity.x += this->npcDetails.deceleration;

		if (this->npcDetails.velocity.x > 0.f)
			this->npcDetails.velocity.x = 0.f;
	}
	/*Right*/
	else if (this->npcDetails.velocity.x > 0.f)
	{
		if (this->npcDetails.velocity.x > this->npcDetails.maxVelocity)
			this->npcDetails.velocity.x = this->npcDetails.maxVelocity;

		this->npcDetails.velocity.x -= this->npcDetails.deceleration;

		if (this->npcDetails.velocity.x < 0.f)
			this->npcDetails.velocity.x = 0.f;
	}

	this->oldPosition = this->spriteRect.getPosition();
	this->spriteRect.move(sf::Vector2f(this->npcDetails.velocity.x * dt, this->npcDetails.velocity.y * dt));
	this->updateAnimation();
}
void NPC::updateAnimation()
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
		if (this->npcDetails.currentDirection == NPCDirection::Up)
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
		else if (this->npcDetails.currentDirection == NPCDirection::Down)
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
		else if (this->npcDetails.currentDirection == NPCDirection::Left)
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
		else if (this->npcDetails.currentDirection == NPCDirection::Right)
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
		else if (this->npcDetails.currentDirection == NPCDirection::Idle)
		{
			if (this->npcDetails.oldDirection == NPCDirection::Up)
			{
				this->spriteIntRect = idleUp;
				this->sprite.setTextureRect(this->spriteIntRect);
			}
			else if (this->npcDetails.oldDirection == NPCDirection::Down)
			{
				this->spriteIntRect = idleDown;
				this->sprite.setTextureRect(this->spriteIntRect);
			}
			else if (this->npcDetails.oldDirection == NPCDirection::Left)
			{
				this->spriteIntRect = idleLeft;
				this->sprite.setTextureRect(this->spriteIntRect);
			}
			else if (this->npcDetails.oldDirection == NPCDirection::Right)
			{
				this->spriteIntRect = idleRight;
				this->sprite.setTextureRect(this->spriteIntRect);
			}
		}
	}
}
void NPC::update(sf::RectangleShape player_rect, sf::Vector2f mouse_view, const sf::Event& smfl_events, const bool& key_time, const float& dt)
{
	/*Interact With Player*/
	this->updateInteractWithPlayer(player_rect, mouse_view, smfl_events, key_time);

	/*Interact With Player or Random Direction*/
	if (this->interactWithPlayer && !this->talkingToPlayer)
		this->updateAIDirection(player_rect, dt);
	else if (!this->interactWithPlayer && !this->talkingToPlayer)
		this->updateRandomDirection(dt);

	/*Alert Circle*/
	this->alertCircle.setPosition(this->spriteRect.getPosition());

	/*Emotes*/
	this->updateEmoteAnimation();
	this->emoteSprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y - 50.f));

	/*Set Sprite Position to Sprite Rect*/
	this->sprite.setPosition(sf::Vector2f(this->spriteRect.getPosition().x - 2.f, this->spriteRect.getPosition().y - 1.f));

	/*Set Text Position*/
	this->textBackground.setPosition(sf::Vector2f(this->spriteRect.getPosition().x, this->spriteRect.getPosition().y - 200.f));
	this->textNameShape.setPosition(sf::Vector2f(
		this->textBackground.getPosition().x - (this->textBackground.getSize().x / 2.f) + (this->textNameShape.getSize().x /2.f), 
		this->textBackground.getPosition().y - (this->textBackground.getSize().y / 2.f) + (this->textNameShape.getSize().y / 2.f)
	)
	);
	this->textName.setPosition(sf::Vector2f(
		this->textNameShape.getPosition().x, 
		this->textNameShape.getPosition().y - static_cast<float>(this->textName.getCharacterSize() / 4.f)
	)
	);
	this->textBodyShape.setPosition(sf::Vector2f(
		this->textBackground.getPosition().x,
		this->textBackground.getPosition().y)
	);
	this->textBody.setOrigin(this->textBody.getGlobalBounds().width / 2.f, this->textBody.getGlobalBounds().height / 2.f);
	this->textBody.setPosition(sf::Vector2f(
		this->textBodyShape.getPosition().x - (this->textBodyShape.getSize().x / 2.f) + (this->textBodyShape.getSize().x / 2.f),
		this->textBodyShape.getPosition().y - static_cast<float>(this->textBody.getCharacterSize()) / 4.f)
	);
}

/*Render Functions*/
void NPC::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	target.draw(this->spriteRect);
	//target.draw(this->alertCircle);

	if (this->alertCircleCollisionBool)
		target.draw(this->emoteSprite);

	if (this->showNPCText)
	{
		target.draw(this->textBackground);
		target.draw(this->textNameShape);
		target.draw(this->textName);
		target.draw(this->textBodyShape);
		target.draw(this->textBody);
	}
}